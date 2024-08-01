/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:25:35 by caalbert          #+#    #+#             */
/*   Updated: 2024/08/01 17:38:25 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spider.hpp"
#include <iostream>
#include <cstring>

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " [options] URL\n"
              << "Options:\n"
              << "  -r             Recursively download images\n"
              << "  -l [N]         Specify the maximum depth level for recursive download (default: 5)\n"
              << "  -p [PATH]      Specify the path to save downloaded files (default: ./data/)\n";
}

int main(int argc, char* argv[]) {
    std::string url;
    int depth = 5; // Default depth
    std::string path = "./data/"; // Default path
    bool recursive = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-r") == 0) {
            recursive = true;
        } else if (strcmp(argv[i], "-l") == 0) {
            if (i + 1 < argc) {
                depth = std::atoi(argv[++i]);
            } else {
                std::cerr << "Option -l requires an argument" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-p") == 0) {
            if (i + 1 < argc) {
                path = argv[++i];
            } else {
                std::cerr << "Option -p requires an argument" << std::endl;
                return 1;
            }
        } else {
            url = argv[i];
        }
    }

    if (url.empty()) {
        std::cerr << "URL is required" << std::endl;
        return 1;
    }

    try {
        spider mySpider(url, depth, path);
        mySpider.downloadImages();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
