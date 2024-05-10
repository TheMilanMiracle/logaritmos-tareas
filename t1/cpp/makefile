DIR = ./mtree

DEP = ${DIR}/mtree.cpp ${DIR}/search.cpp ${DIR}/sexton_swinbank.cpp ${DIR}/generate_points.cpp ${DIR}/ciaccia_patella.cpp 

TRH = -Wall -Werror


search-test:
	
	g++ ./search-test.cpp ${DEP} -o ./bin
	./bin
	rm ./bin

main:
	rm -f ./results.txt
	g++ ./main.cpp ${DEP} -o ./bin
	./bin
	rm ./bin

main-O:
	g++ -O3 ./main.cpp ${DEP} -o ./bin14
	./bin14



debug:
	clear
	g++ ./main.cpp ${DEP} -g -D_GLIBCXX_DEBUG -Wall -Werror -o ./bin
	./bin
	rm ./bin

val:
	g++ -O1 ./main.cpp ${DEP} -o ./bin
	valgrind --leak-check=full ./bin

gdb:
	clear
	g++ ./main.cpp ${DEP} -g -D_GLIBCXX_DEBUG -o ./bin
	gdb ./bin
	rm ./bin

clean:
	rm -f *.txt rm -f *.out rm -f bin rm -f *bin*
	
	

