CC=g++
CFLAGS=-c -Wall
LDFLAGS= -Bstatic -lrt -lpthread -Bdynamic -lhamlib
SOURCES=main.cpp serial.cpp library.cpp work.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=run
HEADERS= serial.h library.h

all: $(SOURCES) $(EXECUTABLE) $(HEADERS)


$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm *.o

