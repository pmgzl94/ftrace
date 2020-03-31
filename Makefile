##
## EPITECH PROJECT, 2020
	## cpp
## File description:
## Makefile cpp with Unit tests
##

SRCDIR = src/

SRC_SRC	=	main.c					\
			strace.c				\
			check_args.c				\
			get_args.c				\
			trace_program.c				\
			trace_pid.c				\
			trace_functions.c		\
			display.c				\
			display_flag_s.c		\
			display_array.c\


SRC =	$(addprefix $(SRCDIR), $(SRC_SRC))

OBJ	=	$(SRC:.c=.o)

CRITDIR = tests/

CRT_SRC	=	test.c		\
			test1.c		\
			read_tab.c	\

CRT = $(addprefix $(CRITDIR), $(CRT_SRC))

NAME	=	ftrace

CPPFLAGS	+=	-I include -lelf

all:	$(NAME)

# c.o:
# 	gcc -c $(SRC) -I include

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CPPFLAGS)
	# gcc -c $(SRC) -lelf -I include

tests_run:
		gcc $(filter-out src/main.c, $(SRC)) $(CRT) -o unit_tests  -I ./include/ --coverage -lcriterion
		./unit_tests
		gcovr --exclude tests
		gcovr --exclude tests -b
		rm unit_tests

clean:
	rm -f $(OBJ)
	rm -rf *.o *.gc* *vg* unit_tests

fclean:	clean
	rm -f $(NAME)

re:	fclean all
