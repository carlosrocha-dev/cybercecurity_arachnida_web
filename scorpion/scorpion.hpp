/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scorpion.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:04:04 by caalbert          #+#    #+#             */
/*   Updated: 2024/07/30 13:04:05 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scorpion.hpp"
#include <exiv2/exiv2.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

Scorpion::Scorpion() {}

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

std::string Scorpion::readMetadata(const std::string& file) {
    try {
        auto image = Exiv2::ImageFactory::open(file);
        assert(image.get() != 0);
        image->readMetadata();

        Exiv2::ExifData& exifData = image->exifData();
        if (exifData.empty()) {
            std::cerr << "No EXIF data found in file: " << file << std::endl;
            return "";
        }

        std::stringstream metadata;
        for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != exifData.end(); ++i) {
            metadata << i->key() << " " << i->value() << "\n";
        }
        return metadata.str();
    } catch (Exiv2::AnyError& e) {
        std::cerr << "Error reading metadata from file " << file << ": " << e.what() << std::endl;
        return "";
    }
}

void Scorpion::modifyMetadata(const std::string& file, const std::string& key, const std::string& value) {
    try {
        auto image = Exiv2::ImageFactory::open(file);
        assert(image.get() != 0);
        image->readMetadata();

        Exiv2::ExifKey exifKey(key);
        Exiv2::ExifData& exifData = image->exifData();
        Exiv2::Exifdatum& datum = exifData[exifKey];
        datum.setValue(value);

        image->writeMetadata();
    } catch (Exiv2::AnyError& e) {
        std::cerr << "Error modifying metadata in file " << file << ": " << e.what() << std::endl;
    }
}

void Scorpion::deleteMetadata(const std::string& file, const std::string& key) {
    try {
        auto image = Exiv2::ImageFactory::open(file);
        assert(image.get() != 0);
        image->readMetadata();

        Exiv2::ExifData& exifData = image->exifData();
        Exiv2::ExifData::iterator pos = exifData.findKey(Exiv2::ExifKey(key));
        if (pos != exifData.end()) {
            exifData.erase(pos);
            image->writeMetadata();
        }
    } catch (Exiv2::AnyError& e) {
        std::cerr << "Error deleting metadata in file " << file << ": " << e.what() << std::endl;
    }
}
