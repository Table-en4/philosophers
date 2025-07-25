# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 17:37:53 by molapoug          #+#    #+#              #
#    Updated: 2025/07/09 11:20:52 by molapoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -lpthread

LIBFT = libft/
FT_PRINTF = ft_printf/

LIBFT_A = $(LIBFT)libft.a
FTPRINTF_A = $(FT_PRINTF)libftprintf.a

RM = rm -f

SRC = philo.c utils.c test.c
OBJ = $(SRC:.c=.o)

BONUS_SRC = philo.c utils.c

BONUS_OBJ = $(BONUS_SRC:.c=.o)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(FTPRINTF_A)
	@echo "$(YELLOW)😎🤙 Linking executable$(PURPLE) $(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT) -lft -L$(FT_PRINTF) -lftprintf -o $(NAME)

bonus: $(BONUS_OBJ) $(LIBFT_A) $(FTPRINTF_A)
	@echo "$(YELLOW)💪 Compiling bonus version$(NC)"
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -L$(LIBFT) -lft -L$(FT_PRINTF) -lftprintf -o $(NAME)

%.o: %.c philo.h
	@echo "$(CYAN)🔥 Compiling$(GREEN) $<$(NC)"
	@$(CC) $(CFLAGS) -I$(LIBFT) -I$(FT_PRINTF) -c $< -o $@

$(LIBFT_A):
	@make -C $(LIBFT)

$(FTPRINTF_A):
	@make -C $(FT_PRINTF)

clean:
	@echo "$(CYAN)🧹 Cleaning object files$(NC)"
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@make -C $(LIBFT) clean
	@make -C $(FT_PRINTF) clean

fclean: clean
	@echo "$(CYAN)🚮 Cleaning$(RED) $(NAME)$(NC)"
	@$(RM) $(NAME)
	@make -C $(LIBFT) fclean
	@make -C $(FT_PRINTF) fclean

re: fclean all

.PHONY: all clean fclean re bonus
