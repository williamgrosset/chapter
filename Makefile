.phony setup:
setup: main.cpp
	g++ main.cpp -std=c++11 -lcurl -o chapter.o

.phony clean:
	rm -rf *.o
