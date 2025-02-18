#include "file_utils.hpp"
#include <iostream>
#include <algorithm>

std::vector<FileRenameInfo> scanForAnimeFiles(const fs::path &directory, const std::vector<std::string>& videoExtensions) {
    std::vector<FileRenameInfo> files;
    try {
        for (const auto &entry : fs::directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                fs::path filePath = entry.path();
                std::string ext = filePath.extension().string();
                // Convert extension to lowercase.
                std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c){ return std::tolower(c); });
                if (std::find(videoExtensions.begin(), videoExtensions.end(), ext) != videoExtensions.end()) {
                    files.push_back({filePath, ""});
                }
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error scanning directory: " << e.what() << "\n";
    }
    return files;
}

bool renameFile(const FileRenameInfo &fileInfo) {
    try {
        fs::path newPath = fileInfo.originalPath.parent_path() / fileInfo.newFileName;
        fs::rename(fileInfo.originalPath, newPath);
        std::cout << "Renamed: " << fileInfo.originalPath.filename().string()
                  << " -> " << newPath.filename().string() << "\n";
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error renaming file " << fileInfo.originalPath.filename().string()
                  << ": " << e.what() << "\n";
        return false;
    }
}
