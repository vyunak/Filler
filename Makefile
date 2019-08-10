# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vyunak <vyunak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 22:20:49 by vyunak            #+#    #+#              #
#    Updated: 2019/04/10 17:08:47 by vyunak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = vyunak.filler
FILES = filler.c filler_part_2.c
SRC = $(addprefix src/, $(FILES))
OBJ = $(SRC:src/%.c=.obj/%.o)
FLAGS = -Wall -Werror -Wextra
LIBCOM = -L libft -lft
INCLUDE = -I includes/filler.h -I libft/libft.h

all: $(NAME)

$(NAME): $(SRC) $(OBJ) lib
	@gcc $(OBJ) $(INCLUDE) $(FLAGS) $(LIBCOM) -o $(NAME)

.obj/%.o: src/%.c
	@mkdir -p .obj/
	@gcc $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf .obj/
	@make clean -C libft/

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft/

re: fclean all

lib:
	@make -C libft

relib:
	@make re -C libft

.PHONY: clean fclean all re