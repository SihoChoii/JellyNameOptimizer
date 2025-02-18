#include "api_manager.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

std::string readAPIKeyFromFile(const std::string& filename) {
    try {
        std::ifstream infile(filename);
        if (!infile) {
            std::cerr << "Error: Unable to open API key file: " << filename << "\n";
            return "";
        }
        std::string key;
        std::getline(infile, key);
        infile.close();
        return key;
    } catch (const std::exception &e) {
        std::cerr << "Exception reading API key file: " << e.what() << "\n";
        return "";
    }
}

bool storeAPIKeyToFile(const std::string& filename, const std::string& apiKey) {
    try {
        std::ofstream outfile(filename);
        if (!outfile) {
            std::cerr << "Error: Unable to create file: " << filename << "\n";
            return false;
        }
        outfile << apiKey;
        outfile.close();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Exception writing API key to file: " << e.what() << "\n";
        return false;
    }
}

std::string getAPIKey(const std::string& filename) {
    std::string key;
    if (fs::exists(filename)) {
        key = readAPIKeyFromFile(filename);
        if (key.empty()) {
            std::cerr << "API key file exists but is empty.\n";
        }
    }
    if (key.empty()) {
        std::cout << "Enter your OpenAI API Key: ";
        std::getline(std::cin, key);
        if (key.empty()) {
            std::cerr << "No API key entered, exiting.\n";
            std::exit(EXIT_FAILURE);
        }
        if (!storeAPIKeyToFile(filename, key)) {
            std::cerr << "Failed to store the API key. Exiting.\n";
            std::exit(EXIT_FAILURE);
        }
    }
    return key;
}
