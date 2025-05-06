# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 12:44:18 by llacsivy          #+#    #+#              #
#    Updated: 2025/05/06 18:08:46 by llacsivy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= PmergeMe
CPP				:= c++
CPPFLAGS		:= -Wextra -Wall -Werror -Wshadow -std=c++17

SRCS			:= 	main.cpp \
					PmergeMe.cpp \
					vecFcts.cpp

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