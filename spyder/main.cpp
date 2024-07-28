#include <iostream>
#include "spyder.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [-l N] [-p PATH] URL" << std::endl;
        return 1;
    }

    int depth = 5;
    std::string path = "./data/";
    std::string url;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-l") {
            if (i + 1 < argc) {
                depth = stringToInt(argv[++i]);
            }
        } else if (arg == "-p") {
            if (i + 1 < argc) {
                path = argv[++i];
            }
        } else {
            url = arg;
        }
    }

    if (url.empty()) {
        std::cerr << "URL is required." << std::endl;
        return 1;
    }

    Spyder spyder(url, depth, path);
    spyder.downloadImages();

    return 0;
}
