#ifndef SPIDER_HPP
#define SPIDER_HPP

#include <string>
#include <vector>
#include <set>

class spider {
public:
    spider(const std::string& url, int depth, const std::string& path);
    void downloadImages();

private:
    void processUrl(const std::string& url, int currentDepth, std::set<std::string>& visited);
    std::string fetchContent(const std::string& url);
    std::vector<std::string> extractImageUrls(const std::string& content);
    std::vector<std::string> extractLinks(const std::string& content);
    void saveImage(const std::string& imageUrl);
    bool createDirectories(const std::string& path);
    std::string getImageFilename(const std::string& url);

    std::string url;
    int depth;
    std::string path;
};

#endif // SPIDER_HPP
