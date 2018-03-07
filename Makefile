##
## EPITECH PROJECT, 2018
## make
## File description:
## make
##

CC	=	gcc -Wall -Wextra


RM	=	rm -f

NAME	=	philo

SRC	=	philosopher.c	\
		main.c

OBJ	=	$(SRC:.c=.o)

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) -lriceferee -lpthread -L./ -o $(NAME)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
