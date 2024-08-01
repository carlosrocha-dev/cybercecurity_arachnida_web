#include "scorpion.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <exiv2/exiv2.hpp>

scorpion::scorpion() {
    logFile.open("scorpion.log");
    if (!logFile) {
        std::cerr << "Failed to open log file." << std::endl;
    }
}

void scorpion::log(const std::string& message) {
    if (logFile) {
        logFile << message << std::endl;
    }
    std::cout << message << std::endl;
}

void scorpion::parseFiles(const std::vector<std::string>& files) {
    for (const auto& file : files) {
        std::string metadata = readMetadata(file);
        if (metadata.empty()) {
            log("No metadata found for file " + file);
            continue;
        }
        log("Metadata for " + file + ":\n" + metadata);
    }
}

void scorpion::modifyMetadata(const std::string& file, const std::string& key, const std::string& value) {
    try {
        log("Opening file: " + file);
        auto image = Exiv2::ImageFactory::open(file);
        image->readMetadata();
        log("Reading metadata from file: " + file);

        auto& exifData = image->exifData();
        Exiv2::ExifKey exifKey(key);
        auto pos = exifData.findKey(exifKey);

        if (pos != exifData.end()) {
            log("Updating existing metadata: " + key + " to " + value);
            pos->setValue(value);
        } else {
            log("Adding new metadata: " + key + " to " + value);
            Exiv2::Exifdatum datum(exifKey);
            datum.setValue(value);
            exifData.add(datum);
        }

        image->setExifData(exifData);
        image->writeMetadata();
        log("Writing metadata to file: " + file);
    } catch (const Exiv2::Error& e) {
        log("Error modifying metadata in file " + file + ": " + e.what());
    }
}

void scorpion::deleteMetadata(const std::string& file, const std::string& key) {
    try {
        log("Opening file: " + file);
        auto image = Exiv2::ImageFactory::open(file);
        image->readMetadata();

        auto& exifData = image->exifData();
        auto it = exifData.findKey(Exiv2::ExifKey(key));
        if (it != exifData.end()) {
            exifData.erase(it);
            log("Deleted metadata key: " + key);
        } else {
            log("Metadata key not found: " + key);
        }

        image->setExifData(exifData);
        image->writeMetadata();
        log("Writing metadata to file: " + file);
    } catch (const Exiv2::Error& e) {
        log("Error deleting metadata in file " + file + ": " + e.what());
    }
}

std::string scorpion::readMetadata(const std::string& file) {
    try {
        log("Opening file: " + file);
        auto image = Exiv2::ImageFactory::open(file);
        image->readMetadata();

        auto& exifData = image->exifData();
        if (exifData.empty()) {
            log("No Exif data found in file: " + file);
            return "";
        }

        std::ostringstream metadataStream;
        for (const auto& md : exifData) {
            metadataStream << md.key() << " " << md.value() << "\n";
        }
        return metadataStream.str();
    } catch (const Exiv2::Error& e) {
        log("Error reading metadata from file " + file + ": " + e.what());
        return "";
    }
}

void scorpion::writeMetadata(const std::string& file, const std::string& metadata) {
    try {
        log("Opening file: " + file);
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
        log("Writing metadata to file: " + file);
    } catch (const Exiv2::Error& e) {
        log("Error writing metadata to file " + file + ": " + e.what());
    }
}
