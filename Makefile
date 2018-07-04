.phony setup:
setup: main.cpp
		g++ -std=c++11 lib/*/*.cpp jamspell/*.cpp contrib/*/*.cc contrib/*/*.cpp main.cpp -lboost_regex -I "./" -o chapter.o

run: chapter.o
		./chapter.o

.phony clean:
		rm -rf *.o
