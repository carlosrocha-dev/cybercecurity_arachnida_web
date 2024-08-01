#include "scorpion.hpp"
#include <iostream>
#include <vector>
#include <cstring>

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " [options] FILE1 [FILE2 ...]\n"
              << "Options:\n"
              << "  -m <file> <key> <value>  Modify metadata\n"
              << "  -d <file> <key>          Delete metadata\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    scorpion sc;
    std::vector<std::string> files;
    std::string file, key, value;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-m") == 0) {
            if (i + 3 < argc) {
                file = argv[++i];
                key = argv[++i];
                value = argv[++i];
                sc.modifyMetadata(file, key, value);
                return 0;
            } else {
                std::cerr << "Option -m requires <file> <key> <value>" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-d") == 0) {
            if (i + 2 < argc) {
                file = argv[++i];
                key = argv[++i];
                sc.deleteMetadata(file, key);
                return 0;
            } else {
                std::cerr << "Option -d requires <file> <key>" << std::endl;
                return 1;
            }
        } else {
            files.push_back(argv[i]);
        }
    }

    if (!files.empty()) {
        sc.parseFiles(files);
    } else {
        printUsage(argv[0]);
        return 1;
    }

    return 0;
}
