##
## EPITECH PROJECT, 2018
## make
## File description:
## make
##

CC	=	gcc -Wall -Wextra


RM	=	rm -f

NAME	=	philosopher

SRC	=	philosopher.c

OBJ	=	$(SRC:.c=.o)

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) -pthread -lpthread

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
