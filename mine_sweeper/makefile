mine_sweeper.out: setup.o play.o print_board.o gameover.o
	gcc -g -Wall -Werror -o mine_sweeper.out setup.o play.o print_board.o gameover.o

setup.o: setup.c play.c mine_sweeper.h
	gcc -g -Wall -Werror -c setup.c

play.o: play.c print_board.c gameover.c mine_sweeper.h
	gcc -g -Wall -Werror -c play.c

print_board.o: print_board.c mine_sweeper.h
	gcc -g -Wall -Werror -c print_board.c

gameover.o: gameover.c print_board.c mine_sweeper.h
	gcc -g -Wall -Werror -c gameover.c

clean:
	rm -fr *.o *.out
