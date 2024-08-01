/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:25:35 by caalbert          #+#    #+#             */
/*   Updated: 2024/08/01 08:51:19 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spider.hpp"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    std::string url;
    int depth = 5;
    std::string path = "./data/";
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

    spider mySpider(url, depth, path);
    mySpider.downloadImages();

    return 0;
}
