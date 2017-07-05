NAME		=	avm

SRC_NAME	=	main.cpp			\

SRC		=	$(addprefix srcs/, $(SRC_NAME))

OBJ		=	$(SRC:srcs/%.c=.obj/%.o)

CC		=	clang++

FLAGS		= 	-Wall -Werror -Wextra -std=c++11

INCLUDE		= 	-I includes

all: 		$(NAME)

$(NAME): 	$(OBJ)
		$(CC) $(OBJ) $(INCLUDE) $(FLAGS) -o $@

.obj/%.o: 	srcs/%.c
		@mkdir -p .obj/
		$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
		@rm -rf .obj/

fclean: 	clean
		@rm -rf $(NAME)

re: 		fclean all
