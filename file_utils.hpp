#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

// Structure holding file information and its new name.
struct FileRenameInfo {
    fs::path originalPath;
    std::string newFileName;
};

// Scans the specified directory for files with the given video extensions.
std::vector<FileRenameInfo> scanForAnimeFiles(const fs::path &directory, const std::vector<std::string>& videoExtensions);

// Renames the file based on the FileRenameInfo structure.
// Returns true on success.
bool renameFile(const FileRenameInfo &fileInfo);

#endif // FILE_UTILS_HPP
