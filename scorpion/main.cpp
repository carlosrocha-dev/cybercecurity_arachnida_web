#include <iostream>
#include <vector>
#include "scorpion.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [option] FILE [FILE2 ...] [key value]" << std::endl;
        std::cerr << "Options:" << std::endl;
        std::cerr << "  -l          List metadata" << std::endl;
        std::cerr << "  -m KEY VAL  Modify metadata" << std::endl;
        std::cerr << "  -d KEY      Delete metadata" << std::endl;
        return 1;
    }

    std::string option = argv[1];
    std::vector<std::string> files;
    std::string key, value;

    if (option == "-l") {
        for (int i = 2; i < argc; ++i) {
            files.push_back(argv[i]);
        }
    } else if (option == "-m" && argc >= 5) {
        files.push_back(argv[2]);
        key = argv[3];
        value = argv[4];
    } else if (option == "-d" && argc >= 4) {
        files.push_back(argv[2]);
        key = argv[3];
    } else {
        std::cerr << "Invalid option or insufficient arguments." << std::endl;
        return 1;
    }

    Scorpion scorpion;
    if (option == "-l") {
        scorpion.parseFiles(files);
    } else if (option == "-m") {
        scorpion.modifyMetadata(files[0], key, value);
    } else if (option == "-d") {
        scorpion.deleteMetadata(files[0], key);
    }

    return 0;
}
