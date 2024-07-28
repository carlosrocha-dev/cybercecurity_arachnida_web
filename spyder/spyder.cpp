#include "spyder.hpp"
#include <iostream>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fstream>

Spyder::Spyder(const std::string& url, int depth, const std::string& path)
    : url(url), depth(depth), path(path) {
    if (!createDirectories(path)) {
        std::cerr << "Failed to create directories for path: " << path << std::endl;
    }
}

void Spyder::downloadImages() {
    std::set<std::string> visited;
    processUrl(url, 0, visited);
}

void Spyder::processUrl(const std::string& url, int currentDepth, std::set<std::string>& visited) {
    if (currentDepth > depth || visited.find(url) != visited.end()) {
        return;
    }

    std::cout << "Processing URL: " << url << " at depth: " << currentDepth << std::endl;
    visited.insert(url);
    std::string content = fetchContent(url);
    std::vector<std::string> imageUrls = extractImageUrls(content);
    std::vector<std::string> links = extractLinks(content);

    std::cout << "Found " << imageUrls.size() << " images and " << links.size() << " links." << std::endl;

    for (size_t i = 0; i < imageUrls.size(); ++i) {
        std::cout << "Saving image: " << imageUrls[i] << std::endl;
        saveImage(imageUrls[i]);
    }

    for (size_t i = 0; i < links.size(); ++i) {
        processUrl(links[i], currentDepth + 1, visited);
    }
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string Spyder::fetchContent(const std::string& url) {
    CURL* curl;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

std::vector<std::string> Spyder::extractImageUrls(const std::string& content) {
    std::vector<std::string> imageUrls;
    std::string::size_type pos = 0;
    while ((pos = content.find("http", pos)) != std::string::npos) {
        std::string::size_type end = content.find_first_of(" \"'>", pos);
        if (end == std::string::npos) break;
        std::string url = content.substr(pos, end - pos);
        if (url.find(".jpg") != std::string::npos ||
            url.find(".jpeg") != std::string::npos ||
            url.find(".png") != std::string::npos ||
            url.find(".gif") != std::string::npos ||
            url.find(".bmp") != std::string::npos) {
            imageUrls.push_back(url);
        }
        pos = end;
    }
    return imageUrls;
}

std::vector<std::string> Spyder::extractLinks(const std::string& content) {
    std::vector<std::string> links;
    std::string::size_type pos = 0;
    while ((pos = content.find("href=\"", pos)) != std::string::npos ||
           (pos = content.find("src=\"", pos)) != std::string::npos) {
        pos += 6; // Skip past href=" or src="
        std::string::size_type end = content.find_first_of("\"", pos);
        if (end == std::string::npos) break;
        std::string url = content.substr(pos, end - pos);
        if (url.find("http") == 0) {
            links.push_back(url);
        }
        pos = end;
    }
    return links;
}

void Spyder::saveImage(const std::string& imageUrl) {
    std::string fileName = path + "/" + imageUrl.substr(imageUrl.find_last_of('/') + 1);
    CURL* curl;
    FILE* fp;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(fileName.c_str(), "wb");
        if (fp) {
            curl_easy_setopt(curl, CURLOPT_URL, imageUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            CURLcode res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                std::cerr << "Failed to save image: " << imageUrl << " Error: " << curl_easy_strerror(res) << std::endl;
            }
            curl_easy_cleanup(curl);
            fclose(fp);
        } else {
            std::cerr << "Failed to open file: " << fileName << std::endl;
        }
    } else {
        std::cerr << "Failed to initialize curl for: " << imageUrl << std::endl;
    }
}

bool Spyder::createDirectories(const std::string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) != 0) {
        if (mkdir(path.c_str(), 0777) != 0) {
            return false;
        }
    }
    return true;
}
