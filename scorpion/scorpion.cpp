#include "scorpion.hpp"
#include <iostream>
#include <exiv2/exiv2.hpp>

void Scorpion::parseFiles(const std::vector<std::string>& files) {
    for (size_t i = 0; i < files.size(); ++i) {
        try {
            Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(files[i]);
            image->readMetadata();
            Exiv2::ExifData &exifData = image->exifData();
            if (exifData.empty()) {
                std::cerr << files[i] << ": no Exif data found in the file" << std::endl;
                continue;
            }
            std::cout << "Metadata for " << files[i] << ":\n";
            for (Exiv2::ExifData::const_iterator md = exifData.begin(); md != exifData.end(); ++md) {
                char buf[200];
                snprintf(buf, sizeof(buf), "%-44s    %s", md->key().c_str(), md->value().toString().c_str());
                std::cout << buf << std::endl;
            }
        } catch (Exiv2::BasicError<char>& e) {
            std::cerr << "Error reading metadata from " << files[i] << ": " << e.what() << std::endl;
        }
    }
}

void Scorpion::modifyMetadata(const std::string& file, const std::string& key, const std::string& value) {
    try {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(file);
        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();
        exifData[key] = value;
        image->setExifData(exifData);
        image->writeMetadata();
    } catch (Exiv2::BasicError<char>& e) {
        std::cerr << "Error modifying metadata in " << file << ": " << e.what() << std::endl;
    }
}

void Scorpion::deleteMetadata(const std::string& file, const std::string& key) {
    try {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(file);
        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();
        Exiv2::ExifData::iterator pos = exifData.findKey(Exiv2::ExifKey(key));
        if (pos != exifData.end()) {
            exifData.erase(pos);
        }
        image->setExifData(exifData);
        image->writeMetadata();
    } catch (Exiv2::BasicError<char>& e) {
        std::cerr << "Error deleting metadata in " << file << ": " << e.what() << std::endl;
    }
}
