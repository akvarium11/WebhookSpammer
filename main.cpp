#include <iostream>
#include <string>
#include <curl/curl.h>

int main(int argc, char* argv[]) {
    std::string webhook_url;
    std::string content;
    std::string username;
    std::string avatar_url;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-webhook" || arg == "--webhook") {
            if (i + 1 < argc) { webhook_url = argv[++i]; }
        }
        else if (arg == "-c" || arg == "--c" || arg == "-content" || arg == "--content") {
            if (i + 1 < argc) { content = argv[++i]; }
        }
        else if (arg == "-u" || arg == "--u" || arg == "-user" || arg == "--user") {
            if (i + 1 < argc) { username = argv[++i]; }
        }
        else if (arg == "-a" || arg == "--a" || arg == "-avatar" || arg == "--avatar") {
            if (i + 1 < argc) { avatar_url = argv[++i]; }
        }
    }

    // Ask for missing parameters in console
    if (webhook_url.empty()) {
        std::cout << "Enter Discord webhook URL: ";
        std::getline(std::cin, webhook_url);
    }
    if (content.empty()) {
        std::cout << "Enter message content: ";
        std::getline(std::cin, content);
    }
    if (username.empty()) {
        std::cout << "Enter username: ";
        std::getline(std::cin, username);
    }
    if (avatar_url.empty()) {
        std::cout << "Enter avatar URL: ";
        std::getline(std::cin, avatar_url);
    }

    if (webhook_url.empty()) {
        std::cerr << "Error: Webhook URL is required!" << std::endl;
        return 1;
    }

    std::string json =
        R"({"content": ")" + content +
        R"(", "username": ")" + username +
        R"(", "avatar_url": ")" + avatar_url + R"("})";

    // Send via curl
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL" << std::endl;
        return 1;
    }

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, webhook_url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    while(true) CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return 0;
}