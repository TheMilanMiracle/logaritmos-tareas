DIR = graph

DEP = ${DIR}/graph.cpp ${DIR}/heap.cpp ${DIR}/dijsktra.cpp ${DIR}/fibonacci_heap.cpp

FLAGS = -std=c++11 -O

run:
	g++ ${FLAGS} main.cpp ${DEP} -o ./bin
	./bin
	rm ./bin

run-san:
	g++ ${FLAGS} -fsanitize=address test.cpp -o ./bin
	./bin
	rm ./bin

gdb:
	g++ ${FLAGS} -g -D_GLIBCXX_DEBUG main.cpp ${DEP} -o ./bin
	gdb ./bin
	rm ./bin