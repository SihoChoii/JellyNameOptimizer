#ifndef API_MANAGER_HPP
#define API_MANAGER_HPP

#include <string>

// Reads the API key from a file. Returns an empty string on error.
std::string readAPIKeyFromFile(const std::string& filename);

// Stores the API key to a file. Returns true on success.
bool storeAPIKeyToFile(const std::string& filename, const std::string& apiKey);

// Retrieves the API key: if the key file doesn't exist or is empty, prompts the user,
// stores it, and then returns the key.
std::string getAPIKey(const std::string& filename);

#endif // API_MANAGER_HPP
