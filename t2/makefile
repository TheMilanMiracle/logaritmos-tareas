
WD = ./
MAIN = ${WD}main.cpp
BIN = bin

DIR = graph

DEP = ${DIR}/graph.cpp ${DIR}/heap.cpp ${DIR}/dijsktra.cpp ${DIR}/fibonacci_heap.cpp

FLAGS = -std=c++11

structure = 
v = 
e = 
n = 	

run:
	g++ ${FLAGS} ${MAIN} ${DEP} -o ${WD}${BIN}
	${WD}${BIN} "$(structure)" "${v}" "${e}" "${n}"
	rm ${WD}${BIN}

clean:
	rm -f ./*.txt rm *bin*