#ifndef SCORPION_HPP
#define SCORPION_HPP

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exiv2/exiv2.hpp>

class scorpion {
public:
    scorpion();
    void parseFiles(const std::vector<std::string>& files);
    void modifyMetadata(const std::string& file, const std::string& key, const std::string& value);
    void deleteMetadata(const std::string& file, const std::string& key);
    std::string readMetadata(const std::string& file);
    void writeMetadata(const std::string& file, const std::string& metadata);

private:
    void log(const std::string& message);
    std::ofstream logFile;
};

#endif // SCORPION_HPP
