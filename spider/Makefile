# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 10:25:35 by caalbert          #+#    #+#              #
#    Updated: 2024/08/01 09:05:54 by caalbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
INCLUDES = -I/usr/include/x86_64-linux-gnu
LDFLAGS = -lcurl
TARGET = spider
SRC = spider.cpp main.cpp utils.cpp
OBJ = $(SRC:.cpp=.o)
DOCKER_IMAGE = spider
DOCKER_CONTAINER = spider-container

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
