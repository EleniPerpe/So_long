# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 15:13:49 by eperperi          #+#    #+#              #
#    Updated: 2024/05/16 16:18:53 by eperperi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	so_long

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
MLXFLAGS	=	-lglfw -L "$(HOME)/.brew/opt/glfw/lib/"

GREEN	=	\033[0;32m
CYAN	=	\033[0;36m
WHITE	=	\033[0m

SRC_DIR	=	./srcs/
OBJ_DIR	=	./objs/

SRC		=	$(SRC_DIR)so_long.c \
			
OBJ		=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
LIB		=	Libft/libft.a
MLX42	=	libmlx42.a

$(NAME): $(MLX42) $(OBJ)
		@cd Libft && make
		@$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(MLX42) $(OBJ) $(LIB)
		@echo "$(GREEN)so_long compiled!$(WHITE)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX42):
	@if [ ! -d "./MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build
	@cd MLX42 && cmake --build build -j4

all:	$(MLX42) $(NAME)

cleanmlx:
		@rm -rf MLX42
		@echo "$(CYAN)MLX42 folder is deleted!$(WHITE)"
		
clean:	
		@cd Libft && make clean
		@rm -rf $(OBJ_DIR)
		@echo "$(CYAN)object files cleaned!$(WHITE)"

fclean:	
		@cd Libft && make clean
		@rm -rf $(OBJ_DIR)
		@cd Libft && make fclean
		@rm -f $(NAME)
		@echo "$(CYAN)Executable and object files cleaned!$(WHITE)"

cleanEverything:
		@rm -rf MLX42
		@cd Libft && make clean
		@rm -rf $(OBJ_DIR)
		@cd Libft && make fclean
		@rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean cleanmlx cleanEverything re