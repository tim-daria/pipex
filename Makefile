# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 12:41:15 by dtimofee          #+#    #+#              #
#    Updated: 2025/04/02 12:32:27 by dtimofee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = pipex
NAME_BONUS = pipex_bonus
SRCS = check.c set_path.c utils.c child_and_parent.c pipex.c
BONUS_SRCS = check.c set_path.c utils.c child_and_parent.c pipex_bonus.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT_FOLDER = ./Libft
LIBFT_ARCHIVE = libft.a
LIBFT_LIB = ft
LIBFT = $(LIBFT_FOLDER)/$(LIBFT_ARCHIVE)

all: $(NAME)

$(LIBFT):
	make bonus -C $(LIBFT_FOLDER)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -g $(OBJS) -o $(NAME) -L$(LIBFT_FOLDER) -l$(LIBFT_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) -g $(BONUS_OBJS) -o $(NAME_BONUS) -L$(LIBFT_FOLDER) -l$(LIBFT_LIB)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	make fclean -C $(LIBFT_FOLDER)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
