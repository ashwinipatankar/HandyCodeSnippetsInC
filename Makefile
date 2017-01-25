#compiler

#compiler options
OPTS=-c -Wall
#source files
SRC= \
	src

INCLUDES=\
	include

INC = $(patsubst %,-I%,$(INCLUDES))

ifdef PTHREAD
SOURCES=src/template_pthread.c
LIBS=-lpthread
EXECUTABLE=./bin/threadex
endif

ifdef TCPSOCKET
SOURCES=src/template_tcpsocket.c
LIBS=-lpthread
EXECUTABLE=./bin/tcpsockex
endif

ifdef FILEIO
SOURCES=src/template_fileoperations.c
LIBS=-lpthread
EXECUTABLE=./bin/fileioex
endif

ifdef LOOKUPTABLE
SOURCES=src/doublelookuptable.c
LIBS=
EXECUTABLE=./bin/lookupex
endif

ifdef UTILITY
SOURCES= src/utility_functions.c src/template_utilityfunctions.c
LIBS=
EXECUTABLE=./bin/utility
endif

#SOURCES=$(wildcard *.c $(SRC)/*.c )
CFLAGS= $(INC)
CC=gcc $(CFLAGS)
#object files
OBJECTS=$(SOURCES:.c=.o)
#sdl-config or any other library here.
#``- ensures that the command between them is executed, and the result is put into LIBS
LIBS+=#`--cflags --libs`
#executable filename
#EXECUTABLE=./bin/hello
#Special symbols used:
#$^ - is all the dependencies (in this case =$(OBJECTS) )
#$@ - is the result name (in this case =$(EXECUTABLE) )

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LINK.o) $^ -o $@ $(LIBS)

clean:
	@find . -name "*.o" -exec rm '{}' \;
	rm -rf bin
	mkdir bin
