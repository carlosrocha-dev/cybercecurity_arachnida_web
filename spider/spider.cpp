#include "spider.hpp"
#include <curl/curl.h>
#include <sys/stat.h>
#include <sys/types.h>

spider::spider(const std::string& url, int depth, const std::string& path)
    : url(url), depth(depth), path(path) {
    logFile.open("spider.log");
    if (!logFile) {
        std::cerr << "Failed to open log file." << std::endl;
    }
    log("Starting spider with URL: " + url + ", Depth: " + std::to_string(depth) + ", Path: " + path);
    if (!createDirectories(path)) {
        log("Failed to create directories for path: " + path);
    }
}

void spider::log(const std::string& message) {
    if (logFile) {
        logFile << message << std::endl;
    }
    std::cout << message << std::endl;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string spider::fetchContent(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            log("Failed to fetch content from URL: " + url + ", Error: " + std::string(curl_easy_strerror(res)));
        }
        curl_easy_cleanup(curl);
    } else {
        log("Failed to initialize CURL for URL: " + url);
    }
    return readBuffer;
}

std::vector<std::string> spider::extractImageUrls(const std::string& content) {
    std::vector<std::string> imageUrls;
    std::vector<std::string> validExtensions = { ".jpg", ".jpeg", ".png", ".gif", ".bmp" };
    size_t pos = 0;
    while ((pos = content.find("src=\"", pos)) != std::string::npos) {
        pos += 5;  // skip past "src=\""
        size_t end = content.find("\"", pos);
        std::string url = content.substr(pos, end - pos);
        for (const auto& ext : validExtensions) {
            if (url.find(ext) != std::string::npos) {
                imageUrls.push_back(url);
                break;
            }
        }
        pos = end;
    }
    log("Extracted " + std::to_string(imageUrls.size()) + " image URLs.");
    return imageUrls;
}

std::vector<std::string> spider::extractLinks(const std::string& content) {
    std::vector<std::string> links;
    size_t pos = 0;
    while ((pos = content.find("href=\"", pos)) != std::string::npos) {
        pos += 6;  // skip past "href=\""
        size_t end = content.find("\"", pos);
        std::string url = content.substr(pos, end - pos);
        links.push_back(url);
        pos = end;
    }
    log("Extracted " + std::to_string(links.size()) + " links.");
    return links;
}

void spider::saveImage(const std::string& imageUrl) {
    CURL* curl;
    FILE* fp;
    std::string filename = path + "/" + getImageFilename(imageUrl);
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename.c_str(), "wb");
        if (fp) {
            curl_easy_setopt(curl, CURLOPT_URL, imageUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                log("Failed to save image from URL: " + imageUrl + ", Error: " + std::string(curl_easy_strerror(res)));
            }
            fclose(fp);
        } else {
            log("Failed to open file for writing: " + filename);
        }
        curl_easy_cleanup(curl);
    } else {
        log("Failed to initialize CURL for image URL: " + imageUrl);
    }
}

bool spider::createDirectories(const std::string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) == -1) {
        if (mkdir(path.c_str(), 0777) != 0) {
            log("Failed to create directory: " + path);
            return false;
        }
    }
    return true;
}

std::string spider::getImageFilename(const std::string& url) {
    size_t lastSlash = url.find_last_of("/");
    if (lastSlash != std::string::npos) {
        return url.substr(lastSlash + 1);
    }
    return "";
}

void spider::downloadImages() {
    std::set<std::string> visited;
    processUrl(url, 0, visited);
}

void spider::processUrl(const std::string& url, int currentDepth, std::set<std::string>& visited) {
    if (currentDepth > depth || visited.find(url) != visited.end()) {
        return;
    }
    visited.insert(url);
    log("Processing URL: " + url + " at depth: " + std::to_string(currentDepth));
    std::string content = fetchContent(url);
    if (content.empty()) {
        log("No content fetched from URL: " + url);
        return;
    }
    auto imageUrls = extractImageUrls(content);
    auto links = extractLinks(content);
    for (const auto& imageUrl : imageUrls) {
        saveImage(imageUrl);
    }
    for (const auto& link : links) {
        processUrl(link, currentDepth + 1, visited);
    }
}
