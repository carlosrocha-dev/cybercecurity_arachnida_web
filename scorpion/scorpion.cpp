#include "scorpion.hpp"
#include <iostream>
#include <exiv2/exiv2.hpp>

void Scorpion::parseFiles(const std::vector<std::string>& files) {
    for (size_t i = 0; i < files.size(); ++i) {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(files[i]);
        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()) {
            std::string error(files[i]);
            error += ": no Exif data found in the file";
            throw Exiv2::Error(1, error);
        }
        std::cout << "Metadata for " << files[i] << ":\n";
        for (Exiv2::ExifData::const_iterator md = exifData.begin(); md != exifData.end(); ++md) {
            char buf[200];
            snprintf(buf, sizeof(buf), "%-44s    %s", md->key().c_str(), md->value().toString().c_str());
            std::cout << buf << std::endl;
        }
    }
}

void Scorpion::modifyMetadata(const std::string& file, const std::string& key, const std::string& value) {
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(file);
    image->readMetadata();
    Exiv2::ExifData &exifData = image->exifData();
    exifData[key] = value;
    image->setExifData(exifData);
    image->writeMetadata();
}

void Scorpion::deleteMetadata(const std::string& file, const std::string& key) {
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(file);
    image->readMetadata();
    Exiv2::ExifData &exifData = image->exifData();
    exifData.erase(key);
    image->setExifData(exifData);
    image->writeMetadata();
}
