#ifndef SPIDER_HPP
#define SPIDER_HPP

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>

class spider {
public:
    spider(const std::string& url, int depth, const std::string& path);
    void downloadImages();

private:
    std::string url;
    int depth;
    std::string path;
    std::ofstream logFile;

    static const std::vector<std::string> validExtensions;

    void log(const std::string& message);
    std::string fetchContent(const std::string& url);
    std::vector<std::string> extractImageUrls(const std::string& content);
    std::vector<std::string> extractLinks(const std::string& content);
    void saveImage(const std::string& imageUrl);
    bool createDirectories(const std::string& path);
    std::string getImageFilename(const std::string& url);
    void processUrl(const std::string& url, int currentDepth, std::set<std::string>& visited);
};

#endif
