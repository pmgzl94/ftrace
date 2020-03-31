##
## EPITECH PROJECT, 2020
	## cpp
## File description:
## Makefile cpp with Unit tests
##

#carefull with g++ and gcc !

SRCDIR = src/

SRC_SRC	=	\

SRC =	$(addprefix $(SRCDIR), $(SRC_SRC))

OBJ	=	$(SRC:.c=.o)

CRITDIR = tests/

CRT_SRC	=	redirect.c\

CRT = $(addprefix $(CRITDIR), $(CRT_SRC))

NAME	=	test

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) main.c
	# gcc $(SRC) main.cpp -o $(NAME) -I ./include/ -Wall -Wextra -Werror

tests_run:
		gcc $(SRC) $(CRT) -o unit_tests  -I ./include/ --coverage -lcriterion
		rm -rf *.gcda *.gcno
		./unit_tests
		gcovr

clean:
	rm -f *.o
	rm -rf *.gcda *.gcno

fclean:	clean
	rm -f $(NAME)

re:	fclean all
