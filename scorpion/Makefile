# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 15:03:43 by caalbert          #+#    #+#              #
#    Updated: 2024/07/30 00:06:07 by caalbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
INCLUDES = -I/usr/include/x86_64-linux-gnu -I.
LDFLAGS = -lcurl -lexiv2
TARGET = scorpion
SRC = scorpion.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
DOCKER_IMAGE = scorpion

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
