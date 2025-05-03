# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 12:44:18 by llacsivy          #+#    #+#              #
#    Updated: 2025/05/03 14:56:53 by llacsivy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= RPN
CPP				:= c++
CPPFLAGS		:= -Wextra -Wall -Werror -std=c++17

SRCS			:= 	main.cpp \
					RPN.cpp

OBJS			:=	${SRCS:.cpp=.o}

all : $(NAME)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re