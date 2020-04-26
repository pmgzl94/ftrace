##
## EPITECH PROJECT, 2019
## tetris
## File description:
## Makefile lib
##

SRCDIR	=	src/

SRC_SRC	=		rotate_linked_list.c	\
				add_element.c			\
				swap_element.c			\
				insert_element.c		\
				list_to_array.c			\
				remove_element.c		\
				return_address.c		\
				return_size.c			\
				complete_chained_list.c	\
				filter_list.c			\

SRC		=	$(addprefix $(SRCDIR), $(SRC_SRC))

OBJ		= 	$(SRC:.c=.o)

CRITDIR		=	tests/

CRIT_SRC	= 	\

CRIT		=	$(addprefix $(CRITDIR), $(CRIT_SRC))

NAME		=	liblkl.a

CPPFLAGS        +=      -I include

all:		$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

tests_run:
	gcc -o unit_tests $(SRC) $(CRIT) -g3 --coverage -lcriterion $(CPPFLAGS)
	./unit_tests
	gcovr
	rm unit_tests
	rm *.gcno
	rm *.gcda

re:	fclean	all
