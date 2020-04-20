##
## EPITECH PROJECT, 2020
## cpp
## File description:
## Makefile cpp with Unit tests
##

SRCDIR = src/

SRC_SRC	=	main.c					\
			strace.c				\
			check_args.c			\
			get_args.c				\
			trace_program.c			\
			trace_pid.c				\
			trace_functions.c		\
			display.c				\
			display_flag_s.c		\
			display_array.c			\
			get_fcts.c				\
			symbol_s_fcts.c			\
			fct_list.c				\
			near_call.c				\
			return.c				\


SRC =	$(addprefix $(SRCDIR), $(SRC_SRC))

OBJ	=	$(SRC:.c=.o)

CRITDIR = tests/

CRT_SRC	=	test.c		\
			test1.c		\
			read_tab.c	\

CRT = $(addprefix $(CRITDIR), $(CRT_SRC))

NAME	=	ftrace

CPPFLAGS	+=	-I include -I liblkl/include/ -lelf -g

all:	$(NAME)

# c.o:
# 	gcc -c $(SRC) -I include

$(NAME):	$(OBJ)
	$(MAKE) -C liblkl
	gcc -o $(NAME) $(OBJ) $(CPPFLAGS) -L ./liblkl -llkl
	# gcc -c $(SRC) -lelf -I include

tests_run:
		gcc $(filter-out src/main.c, $(SRC)) $(CRT) -o unit_tests  -I ./include/ --coverage -lcriterion
		./unit_tests
		gcovr --exclude tests
		gcovr --exclude tests -b
		rm unit_tests

clean:
	$(MAKE) -C liblkl clean
	rm -f $(OBJ)
	rm -rf *.o *.gc* *vg* unit_tests

fclean:	clean
	$(MAKE) -C liblkl fclean
	rm -f $(NAME)

re:	fclean all
	$(MAKE) -C liblkl re
