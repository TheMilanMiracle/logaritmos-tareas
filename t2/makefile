FLAGS = -std=c++11

run:
	g++ ${FLAGS} test.cpp -o ./bin
	./bin
	rm ./bin

run-san:
	g++ ${FLAGS} -fsanitize=address test.cpp -o ./bin
	./bin
	rm ./bin

gdb:
	g++ ${FLAGS} test.cpp -o ./bin
	gdb ./bin
	rm ./bin