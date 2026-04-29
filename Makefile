#
## EPITECH PROJECT, 2026
## my_top
## File description:
## Makefile my_top
#

SRC = src/*.c src/utils/*.c src/components/*.c

NAME = my_top

all	:	$(NAME)

$(NAME):
	clang -o $(NAME) $(SRC) -lncurses

clean:
	rm -f *.o include/*.pch src/*~ src/components/*~ src/utils/*~ *.pch
	rm -f *~ *Zone.Identifier

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind:
	clang -o $(NAME) $(SRC) -lncurses -g3
