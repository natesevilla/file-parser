CC = g++
CCFLAGS = -g -O3 -Wall
TORM = macroPP macroPP.o file_parser.o

macroPP: macroPP.cpp file_parser.o
	${CC} ${CCFLAGS} -o macroPP macroPP.cpp file_parser.o

macroPP.o: macroPP.h macroPP_error_exception.h
	${CC} ${CCFLAGS} -c macroPP.cpp

file_parser.o: file_parser.h file_parser.cc file_parse_exception.h
	${CC} ${CCFLAGS} -c file_parser.cc

clean:
	rm -f ${TORM}
