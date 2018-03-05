##
## EPITECH PROJECT, 2018
## make
## File description:
## make
##

CC	=	gcc -Wall -Wextra


RM	=	rm -f

NAME	=	philo

SRC	=	philosopher.c

OBJ	=	$(SRC:.c=.o)

LD_LIBRARY_PATH = ./libriceferee.so

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) -lpthread -o $(NAME)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
