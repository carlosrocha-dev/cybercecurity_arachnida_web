#include "scorpion.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <exiv2/exiv2.hpp>

void Scorpion::parseFiles(const std::vector<std::string>& files) {
    for (const auto& file : files) {
        std::string metadata = readMetadata(file);
        if (metadata.empty()) {
            std::cerr << "No metadata found for file " << file << std::endl;
            continue;
        }
        std::cout << "Metadata for " << file << ":\n" << metadata << std::endl;
    }
}

void Scorpion::modifyMetadata(const std::string& file, const std::string& key, const std::string& value) {
    try {
        std::cout << "Opening file: " << file << std::endl;
        auto image = Exiv2::ImageFactory::open(file);
        image->readMetadata();
        std::cout << "Reading metadata from file: " << file << std::endl;

        auto& exifData = image->exifData();
        Exiv2::ExifKey exifKey(key);
        Exiv2::Exifdatum datum(exifKey);
        datum.setValue(value);
        exifData.add(datum);

        std::cout << "Setting metadata: " << key << " to " << value << std::endl;
        image->setExifData(exifData);
        image->writeMetadata();
        std::cout << "Writing metadata to file: " << file << std::endl;
    } catch (const Exiv2::Error& e) {
        std::cerr << "Error modifying metadata in file " << file << ": " << e.what() << std::endl;
    }
}

void Scorpion::deleteMetadata(const std::string& file, const std::string& key) {
    try {
        auto image = Exiv2::ImageFactory::open(file);
        image->readMetadata();

        auto& exifData = image->exifData();
        auto it = exifData.findKey(Exiv2::ExifKey(key));
        if (it != exifData.end()) {
            exifData.erase(it);
        }

        image->setExifData(exifData);
        image->writeMetadata();
    } catch (const Exiv2::Error& e) {
        std::cerr << "Error deleting metadata in file " << file << ": " << e.what() << std::endl;
    }
}

std::string Scorpion::readMetadata(const std::string& file) {
    try {
        auto image = Exiv2::ImageFactory::open(file);
        image->readMetadata();

        auto& exifData = image->exifData();
        if (exifData.empty()) {
            std::cerr << "No Exif data found in file: " << file << std::endl;
            return "";
        }

        std::ostringstream metadataStream;
        for (const auto& md : exifData) {
            metadataStream << md.key() << " " << md.value() << "\n";
        }
        return metadataStream.str();
    } catch (const Exiv2::Error& e) {
        std::cerr << "Error reading metadata from file " << file << ": " << e.what() << std::endl;
        return "";
    }
}

void Scorpion::writeMetadata(const std::string& file, const std::string& metadata) {
    try {
        auto image = Exiv2::ImageFactory::open(file);
        image->readMetadata();

        auto& exifData = image->exifData();
        std::istringstream metadataStream(metadata);
        std::string line;
        while (std::getline(metadataStream, line)) {
            std::istringstream lineStream(line);
            std::string key;
            std::string value;
            lineStream >> key;
            std::getline(lineStream, value);
            Exiv2::ExifKey exifKey(key);
            Exiv2::Exifdatum datum(exifKey);
            datum.setValue(value);
            exifData.add(datum);
        }

        image->setExifData(exifData);
        image->writeMetadata();
        std::cout << "Writing metadata to file: " << file << std::endl;
    } catch (const Exiv2::Error& e) {
        std::cerr << "Error writing metadata to file " << file << ": " << e.what() << std::endl;
    }
}
