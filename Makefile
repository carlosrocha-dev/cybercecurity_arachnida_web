# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 16:06:14 by caalbert          #+#    #+#              #
#    Updated: 2024/07/28 19:18:43 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile

build_docker:
	docker-compose build

up_docker:
	docker-compose up -d

exec_docker:
	@echo "Verificando se o contêiner está em execução..."
	@docker-compose ps | grep scorpion_spyder_container || (echo "Erro: Contêiner não está em execução." && exit 1)
	@echo "Acessando o contêiner..."
	docker-compose exec scorpion_spyder_container /bin/bash || (echo "Erro: Falha ao acessar o contêiner." && exit 1)

clean_docker:
	docker-compose down
