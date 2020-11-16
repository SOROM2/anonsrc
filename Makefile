CFLAGS=-std=c++17
SOURCES=src/*.cpp
OUTFILE=anonsrc

.PHONY: clean

all: ${SOURCES}
	clang++ ${SOURCES} ${CFLAGS} -o ${OUTFILE}

clean:
	rm -f ${OUTFILE}

