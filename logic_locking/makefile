CC=g++
#LDFLAGS=-std=c++11  -I /usr/local/include/boost/ -lm -O3 
LDFLAGS=-std=c++11 -lm -g
#LDFLAGS=-lm -O3 
SOURCES= ./src/node.cpp ./src/encryption.cpp ./src/main.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=logic_lock.o
INCLUDES=./src/inc/*

all: $(SOURCES) bin/$(EXECUTABLE)

bin/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o:  %.c  ${INCLUDES}
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o bin/$(EXECUTABLE)
