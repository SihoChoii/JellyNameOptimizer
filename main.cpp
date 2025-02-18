#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include "api_manager.hpp"
#include "chatgpt_api.hpp"
#include "file_utils.hpp"

namespace fs = std::filesystem;

int main() {
    std::cout << "=== Anime Auto-Renamer ===\n\n";

    // Retrieve the API key (stored in "apikey.txt").
    const std::string apiKeyFile = "apikey.txt";
    std::string apiKey = getAPIKey(apiKeyFile);
    if (apiKey.size() < 10) {
        std::cerr << "The provided API key appears to be invalid. Exiting.\n";
        return EXIT_FAILURE;
    }

    // Define the directory to scan (using current directory) and video file extensions.
    fs::path directory = fs::current_path();
    std::vector<std::string> videoExtensions = {".mkv", ".mp4", ".avi", ".mov"};
    std::vector<FileRenameInfo> filesToRename = scanForAnimeFiles(directory, videoExtensions);

    if (filesToRename.empty()) {
        std::cout << "\nNo anime video files found in the directory.\n";
        return 0;
    }

    // Process each file: display found file and request a new name from the ChatGPT API.
    std::cout << "\nScanning directory for anime files...\n\n";
    for (auto &info : filesToRename) {
        std::cout << "Found: " << info.originalPath.filename().string() << "\n";
        info.newFileName = chatGPTRename(info.originalPath.filename().string(), apiKey);
    }

    // Display a preview of the name changes.
    std::cout << "\nPreview of Files to be Renamed:\n\n";
    for (const auto &info : filesToRename) {
        std::cout << "File: \"" << info.originalPath.filename().string() << "\"\n"
                  << " -> \"" << info.newFileName << "\"\n\n";
    }

    // Ask the user for confirmation.
    std::string userInput;
    std::cout << "Do you want to rename these files? (yes/no): ";
    std::getline(std::cin, userInput);
    std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);

    if (userInput == "yes" || userInput == "y") {
        // Rename each file.
        for (const auto &info : filesToRename) {
            renameFile(info);
        }
        std::cout << "\nAll files processed.\n";
    } else {
        std::cout << "No changes made. Exiting.\n";
    }

    std::cout << "\nPress Enter to close...";
    std::getline(std::cin, userInput);
    return 0;
}
