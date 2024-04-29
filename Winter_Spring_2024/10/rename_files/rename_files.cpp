#include <iostream>
#include <filesystem>
#include <algorithm>

void renameFilesInDirectory(const std::string_view directoryPath, const std::string_view regist = "up") {

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (std::filesystem::is_regular_file(entry)) {

            auto path = entry.path();
            auto name = path.filename().string();

            if (regist == "up") {
                std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::toupper(c); });
            }
            else if (regist == "low") {
                std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
            }
            

            auto replaced = path;
            replaced.replace_filename(name);
            std::filesystem::rename(path, replaced);

        }
    }
}

int main() {

    std::string path;
    std::cin >> path;
    std::string reg;
    std::cin >> reg;
    renameFilesInDirectory(path, reg);
    
}
