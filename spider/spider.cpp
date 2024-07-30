/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:03:26 by caalbert          #+#    #+#             */
/*   Updated: 2024/07/30 18:51:46 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spider.hpp"
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>

spider::spider(const std::string& url, int depth, const std::string& path)
    : url(url), depth(depth), path(path) {
    if (!createDirectories(path)) {
        std::cerr << "Failed to create directories for path: " << path << std::endl;
    }
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string spider::fetchContent(const std::string& url) {
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

std::vector<std::string> spider::extractImageUrls(const std::string& content) {
    std::vector<std::string> imageUrls;
    size_t pos = 0;
    while ((pos = content.find("src=\"", pos)) != std::string::npos) {
        pos += 5;  // skip past "src=\""
        size_t end = content.find("\"", pos);
        std::string url = content.substr(pos, end - pos);
        imageUrls.push_back(url);
        pos = end;
    }
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
            curl_easy_perform(curl);
            fclose(fp);
        }
        curl_easy_cleanup(curl);
    }
}

bool spider::createDirectories(const std::string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) == -1) {
        if (mkdir(path.c_str(), 0777) != 0) {
            std::cerr << "Failed to create directory: " << path << std::endl;
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
    std::string content = fetchContent(url);
    auto imageUrls = extractImageUrls(content);
    auto links = extractLinks(content);
    for (const auto& imageUrl : imageUrls) {
        saveImage(imageUrl);
    }
    for (const auto& link : links) {
        processUrl(link, currentDepth + 1, visited);
    }
}
