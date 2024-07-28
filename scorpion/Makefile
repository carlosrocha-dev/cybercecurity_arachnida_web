# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 15:03:43 by caalbert          #+#    #+#              #
#    Updated: 2024/07/28 17:15:13 by caalbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# scorpion/Makefile
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main_scorpion.cpp scorpion.cpp ../utils.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = scorpion

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) -lexiv2

clean:
	$(RM) $(OBJS) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
