WD = ./
MAIN = ${WD}main.cpp
BIN = bin

DIR = ${WD}mtree

DEP = ${DIR}/mtree.cpp ${DIR}/search.cpp ${DIR}/sexton_swinbank.cpp ${DIR}/generate_points.cpp ${DIR}/ciaccia_patella.cpp 

FLAGS = -O3 -std=c++11

method =
test =

run:
	g++ ${FLAGS} ${MAIN} ${DEP} -o ${WD}${BIN}
	${WD}${BIN} $(method) ${test}
	rm ${WD}${BIN}

clean:
	rm -f *.txt rm -f *.out rm -f bin rm -f *bin*
	

