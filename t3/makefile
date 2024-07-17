BIN = ./bin
DIR = ./bloom
DEP = ${DIR}/get_name_list.cpp ${DIR}/search.cpp ${DIR}/bloom-filter.cpp

N =
P =
M =

run:
	g++ main.cpp ${DEP} -o ${BIN}
	${BIN} ${N} ${P} ${M}
	rm ${BIN}