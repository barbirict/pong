# tukaj napisite seznam izvornih datotek, samo .c dokumente
SOURCE_FILE_LIST = main.cpp 
# tukaj napisite zeljeno ime programa
TARGET = main

# tukaj lahko izberete drug prevajalnik
# ce zelite uporabljati C++ zamenjajte 
# gcc z g++
CC = g++

# tukaj bomo kasneje vnesli dodatne knjiznice
LIBRARIES =-lncurses

CFLAGS = -Wall -std=c++11 -pthread
CXXFLAGS= -Wall -std=c++11 -pthread
OBJECTS = $(SOURCE_FILE_LIST:.cpp=.o)
all: $(OBJECTS)
	$(CC) $(CXXFLAGS) $^ -o $(TARGET) $(LIBRARIES)
debug: CFLAGS += -g 
debug: all
clean:
	rm -f $(TARGET) $(OBJECTS)

