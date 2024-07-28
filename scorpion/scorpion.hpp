#ifndef SCORPION_HPP
#define SCORPION_HPP

#include <string>
#include <vector>

class Scorpion {
public:
    void parseFiles(const std::vector<std::string>& files);
    void modifyMetadata(const std::string& file, const std::string& key, const std::string& value);
    void deleteMetadata(const std::string& file, const std::string& key);
};

#endif // SCORPION_HPP
