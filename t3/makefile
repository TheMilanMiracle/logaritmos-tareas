LIB =./lib/boost_1_85_0

BIN = ./bin
DIR = ./bloom
DEP = ${DIR}/get_name_list.cpp ${DIR}/search.cpp ${DIR}/bloom-filter.cpp

N =
P =
M =
K =

run:
	g++ -I ${LIB} ${DEP} main.cpp -o ${BIN}
	${BIN} ${N} ${P} ${M} ${K}
	rm ${BIN}