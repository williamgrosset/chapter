.phony setup:
setup: main.cpp
		g++ -I. main.cpp -std=c++11 -o chapter.o

run: chapter.o
		./chapter.o

.phony clean:
		rm -rf *.o
