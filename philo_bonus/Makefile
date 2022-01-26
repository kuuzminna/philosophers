# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggrapefr <ggrapefr@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 22:12:16 by ggrapefr          #+#    #+#              #
#    Updated: 2022/01/26 22:13:35 by ggrapefr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
EOC			=	"\033[0;0m"

NAME = philo_bonus

SRCS =  $(shell find sources -type f -name "*.c")
OBJS = $(SRCS:.c=.o)

INCLUDES = -I ./includes

RM = rm -rf
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo $(GREEN)"----- $(NAME) compiling finished! -----" $(EOC)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) $< -c -o $@

clean :
	@echo $(YELLOW) "Cleaning object files..." $(EOC)
	@$(RM)  $(shell find sources -type f -name "*.o")
	@echo $(RED) "----- Removed object files -----" $(EOC)
	
fclean : clean
	@echo $(YELLOW) "Removing $(NAME)..." $(EOC)
	@$(RM) $(NAME)
	@echo $(RED) "----- Removed binary files -----" $(EOC)

re : fclean all

.PHONY: all clean fclean re

norm:
	@norminette -R CheckForbiddenSourceHeader