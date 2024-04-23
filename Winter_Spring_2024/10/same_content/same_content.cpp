#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <openssl/sha.h>


std::unordered_map<std::string, std::filesystem::path> hashes;

// к сожалению у openssl много звезд на гитхабе, но довольно старый стандарт и без макросов не обойтись
std::string to_sha256(const std::string& str) {

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX to_sha256;
    SHA256_Init(&to_sha256);
    SHA256_Update(&to_sha256, str.c_str(), str.size());
    SHA256_Final(hash, &to_sha256);

    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

void transform_duplicates(const std::filesystem::path& path) {

    for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {

        if (std::filesystem::is_regular_file(entry)) {

            std::ifstream file(entry.path(), std::ios::binary);

            if (file) {

                std::stringstream ss;
                ss << file.rdbuf();
                std::string content = ss.str();
                std::string hash = to_sha256(content);

                if (hashes.find(hash) != hashes.end()) {

                    std::filesystem::remove(entry);
                    std::filesystem::create_symlink(hashes[hash], entry);

                } else {
        
                    hashes[hash] = entry;
                }
            }
        }
    }
}

int main() {

    std::string path;
    std::cin >> path;
    transform_duplicates(path);
    
}