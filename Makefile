CFLAGS=-std=c++17
SOURCES=src/*.cpp
OUTFILE=anonsrc
OUTIMG=out.ppm

.PHONY: run clean

all: ${SOURCES}
	clang++ ${SOURCES} ${CFLAGS} -o ${OUTFILE}

gimp:
	./${OUTFILE} ${SOURCES} > ${OUTIMG}
	gimp ${OUTIMG} && rm -f ${OUTIMG}

clean:
	rm -f ${OUTFILE}
	rm -f ${OUTIMG}

