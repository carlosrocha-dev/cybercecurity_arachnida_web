# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 15:03:43 by caalbert          #+#    #+#              #
#    Updated: 2024/08/01 17:01:19 by caalbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
INCLUDES = -I/usr/include/x86_64-linux-gnu -I/usr/include
LDFLAGS = -lexiv2
TARGET = scorpion
SRC = scorpion.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
DOCKER_IMAGE = scorpion
DOCKER_CONTAINER = scorpion-container

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

docker-build: docker-stop docker-clean
	docker build -t $(DOCKER_IMAGE) .

docker-run:
	docker run --rm -it --name $(DOCKER_CONTAINER) $(DOCKER_IMAGE)

docker-clean:
	docker rmi -f $(DOCKER_IMAGE) || true

docker-stop:
	docker stop $(DOCKER_CONTAINER) || true
	docker rm $(DOCKER_CONTAINER) || true

run: docker-build docker-run
