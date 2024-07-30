/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:03:26 by caalbert          #+#    #+#             */
/*   Updated: 2024/07/30 13:03:27 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Spider.hpp"
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

Spider::Spider(const std::string& url, int depth, const std::string& path)
    : url(url), depth(depth), path(path) {
    if (!fs::exists(path) && !fs::create_directories(path)) {
        std::cerr << "Failed to create directories for path: " << path << std::endl;
    }
}

size_t Spider::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string Spider::fetchContent(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

std::vector<std::string> Spider::extractImageUrls(const std::string& content) {
    std::vector<std::string> imageUrls;
    std::string::size_type pos = 0, end;
    while ((pos = content.find("src=\"", pos)) != std::string::npos) {
        pos += 5; // skip past "src=\""
        end = content.find("\"", pos);
        std::string url = content.substr(pos, end - pos);
        if (isImage(url)) {
            imageUrls.push_back(url);
        }
        pos = end;
    }
    return imageUrls;
}

std::vector<std::string> Spider::extractLinks(const std::string& content) {
    std::vector<std::string> links;
    std::string::size_type pos = 0, end;
    while ((pos = content.find("href=\"", pos)) != std::string::npos) {
        pos += 6; // skip past "href=\""
        end = content.find("\"", pos);
        std::string url = content.substr(pos, end - pos);
        links.push_back(url);
        pos = end;
    }
    return links;
}

void Spider::saveImage(const std::string& imageUrl) {
    CURL* curl;
    FILE* fp;
    std::string filename = path + "/" + fs::path(imageUrl).filename().string();
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

void Spider::processUrl(const std::string& url, int currentDepth, std::set<std::string>& visited) {
    if (currentDepth > depth || visited.find(url) != visited.end()) {
        return;
    }
    visited.insert(url);
    std::string content = fetchContent(url);
    auto imageUrls = extractImageUrls(content);
    auto links = extractLinks(content);

    for (const auto& img_url : imageUrls) {
        saveImage(img_url);
    }
    for (const auto& link : links) {
        processUrl(link, currentDepth + 1, visited);
    }
}

void Spider::downloadImages() {
    std::set<std::string> visited;
    processUrl(url, 0, visited);
}
