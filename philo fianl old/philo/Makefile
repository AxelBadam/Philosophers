# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 15:04:42 by atuliara          #+#    #+#              #
#    Updated: 2023/04/21 11:47:20 by atuliara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = main.c init.c utils.c routine.c
OBJS    = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
NAME    = philo
CC      = cc
FLAGS   = -Wall -Wextra -Werror -g
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



