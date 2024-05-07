CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SF = -fsanitize=leak,address

all: tetris test gcov_report

lib:
	sudo apt install libncursesw5-dev
tetris: brick_game/tetris/tetris.c ./gui/cli/view.c
	$(CC) $(CFLAGS) brick_game/tetris/tetris.c ./gui/cli/view.c -lncurses -o tetris

test: brick_game/tetris/tetris.c ./gui/cli/view.c
	$(CC) -g $(CFLAGS) -fprofile-arcs -ftest-coverage brick_game/tetris/tetris.c ./gui/cli/view.c -lncurses -o tetris

gcov_report: test
	chmod +x ./tetris
	mkdir -p gcov-report
	cp tetris-tetris.gcno brick_game/tetris/tetris.gcno
	cp tetris-view.gcno ./gui/cli/view.gcno
	./tetris
	gcov -r brick_game/tetris/tetris.c ./gui/cli/view.c
	gcovr -r . --html --html-details -o gcov-report/index.html
	open ./gcov-report/index.html

clean:
	rm *.gcno *.gcda *.gcov
	rmdir gcov_report
	rm *.html

install: tetris

uninstall: clean

dvi: tetris

dist: tetris