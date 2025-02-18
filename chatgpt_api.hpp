#ifndef CHATGPT_API_HPP
#define CHATGPT_API_HPP

#include <string>

// Sends a request to the ChatGPT API to generate a new file name based on the original.
// Returns the new file name on success or the original file name on error.
std::string chatGPTRename(const std::string &fileName, const std::string &apiKey);

#endif // CHATGPT_API_HPP
