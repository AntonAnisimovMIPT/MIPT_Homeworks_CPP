#include <iostream>
#include <filesystem>

void renameFilesInDirectory(const std::string& directoryPath, const std::string& regist = "up") {

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (std::filesystem::is_regular_file(entry)) {

            std::filesystem::path path = entry.path();
            std::string name = path.filename().string();

            if (regist == "up") {
                for (char& c : name) {
                    if (std::islower(c)) {
                        c = std::toupper(c);
                    }
                }
            }
            else if (regist == "low") {
                for (char& c : name) {
                    if (std::isupper(c)) {
                        c = std::tolower(c);
                    }
                }
            }
            

            std::filesystem::path replaced = path;
            replaced.replace_filename(name);
            std::filesystem::rename(path, replaced);

        }
    }
}

int main() {

    std::string path;
    std::cin >> path;
    renameFilesInDirectory(path, "low");
    
}
