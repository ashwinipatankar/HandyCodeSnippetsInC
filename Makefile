#compiler

#compiler options
OPTS=-c -Wall
#source files
SRC= \
	src

INCLUDES=\
	include

INC = $(patsubst %,-I%,$(INCLUDES))
SOURCES=$(wildcard *.c $(SRC)/*.c )
CFLAGS= $(INC)
CC=gcc $(CFLAGS)
#object files
OBJECTS=$(SOURCES:.c=.o)
#sdl-config or any other library here.
#``- ensures that the command between them is executed, and the result is put into LIBS
LIBS=#`--cflags --libs`
#executable filename
EXECUTABLE=./bin/hello
#Special symbols used:
#$^ - is all the dependencies (in this case =$(OBJECTS) )
#$@ - is the result name (in this case =$(EXECUTABLE) )

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LINK.o) $^ -o $@ $(LIBS)

clean:
	rm $(EXECUTABLE) $(OBJECTS)
