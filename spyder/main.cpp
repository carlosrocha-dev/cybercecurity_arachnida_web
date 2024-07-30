/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:25:35 by caalbert          #+#    #+#             */
/*   Updated: 2024/07/30 00:09:20 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
INCLUDES = -I/usr/include/x86_64-linux-gnu
LDFLAGS = -lcurl
TARGET = spider
SRC = spider.cpp main.cpp utils.cpp
OBJ = $(SRC:.cpp=.o)
DOCKER_IMAGE = spider

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

docker-build:
	docker build -t $(DOCKER_IMAGE) .

docker-run:
	docker run --rm -it $(DOCKER_IMAGE) /bin/bash

run: docker-build docker-run
