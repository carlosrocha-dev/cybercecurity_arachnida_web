# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 16:06:14 by caalbert          #+#    #+#              #
#    Updated: 2024/07/28 16:06:15 by caalbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DOCKER_COMPOSE = docker-compose
DOCKER_COMPOSE_FILE = docker-compose.yml

all: build_docker run_docker

build_docker:
	$(DOCKER_COMPOSE) -f $(DOCKER_COMPOSE_FILE) build

run_docker:
	$(DOCKER_COMPOSE) -f $(DOCKER_COMPOSE_FILE) up -d

down_docker:
	$(DOCKER_COMPOSE) -f $(DOCKER_COMPOSE_FILE) down

build_spyder:
	$(MAKE) -C spyder

build_scorpion:
	$(MAKE) -C scorpion

clean_spyder:
	$(MAKE) -C spyder clean

clean_scorpion:
	$(MAKE) -C scorpion clean

clean: clean_spyder clean_scorpion

re: clean all

.PHONY: all build_docker run_docker down_docker build_spyder build_scorpion clean_spyder clean_scorpion clean re
