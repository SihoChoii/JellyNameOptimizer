#include "chatgpt_api.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <curl/curl.h>
#include "nlohmann/json.hpp" // Include nlohmann::json header

using json = nlohmann::json;

// Callback function for libcurl to write response data into a std::string.
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string chatGPTRename(const std::string &fileName, const std::string &apiKey) {
    const std::string apiUrl = "https://api.openai.com/v1/chat/completions";
    std::string responseString;
    
    CURL* curl = nullptr;
    CURLcode res;
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL." << std::endl;
        return fileName; // fallback to original name
    }
    
    // Set up HTTP headers.
    struct curl_slist* headers = nullptr;
    std::string authHeader = "Authorization: Bearer " + apiKey;
    headers = curl_slist_append(headers, authHeader.c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Create the JSON payload for the API request.
    json j;
    j["model"] = "gpt-4o-mini";
    j["messages"] = json::array({
        {
            {"role", "system"},
            {"content", "You are an expert in renaming anime files for media servers. "
                        "Rename the file using the format: 'Anime Title - SxxExx - Episode Title.mkv'."}
        },
        {
            {"role", "user"},
            {"content", "Please rename the following file to the proper format: " + fileName}
        }
    });
    std::string requestBody = j.dump();

    // Set curl options.
    curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

    // Perform the API call.
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL Error: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        curl_global_cleanup();
        return fileName; // fallback to original name
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    curl_global_cleanup();

    // Parse the JSON response.
    try {
        json jsonResponse = json::parse(responseString);
        if (jsonResponse.contains("choices") && !jsonResponse["choices"].empty()) {
            std::string newName = jsonResponse["choices"][0]["message"]["content"];
            // Clean up extraneous whitespace/newlines.
            std::istringstream iss(newName);
            std::string cleanedName;
            std::getline(iss, cleanedName);
            if (!cleanedName.empty())
                return cleanedName;
        }
    } catch (const std::exception &e) {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
    }
    
    // Fallback: if any error occurs, return the original file name.
    return fileName;
}