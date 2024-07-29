# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 15:03:43 by caalbert          #+#    #+#              #
#    Updated: 2024/07/28 19:07:26 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# scorpion/Makefile
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I.. -I/usr/include

SRCS = main_scorpion.cpp scorpion.cpp ../utils.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = scorpion

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) -L/usr/lib -lexiv2

clean:
	$(RM) $(OBJS) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re