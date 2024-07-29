# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 10:25:35 by caalbert          #+#    #+#              #
#    Updated: 2024/07/28 19:07:52 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# spyder/Makefile
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I..

SRCS = main_spyder.cpp spyder.cpp ../utils.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = spyder

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) -lcurl

clean:
	$(RM) $(OBJS) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

