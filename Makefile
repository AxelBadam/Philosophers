# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 15:04:42 by atuliara          #+#    #+#              #
#    Updated: 2023/07/14 13:42:55 by atuliara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = main.c init.c utils.c routine.c utils2.c
OBJS    = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
NAME    = philo
CC      = cc
FLAGS   = -Wall -Wextra -Werror -O3
HEADER  = philo.h
OBJDIR  = obj

all:    $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

$(OBJS): | $(OBJDIR)
$(OBJDIR)/%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus



