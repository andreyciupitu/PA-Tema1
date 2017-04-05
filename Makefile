CC=g++
CFLAGS=-g -Wall -c

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)
EXECUTABLES=$(SOURCES:%.cpp=%)

build: $(EXECUTABLES)
	
$(EXECUTABLES):%: %.o
	$(CC) $< -o $@

$(OBJECTS):%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

run-p1: points
	./points

run-p2: adn
	./adn

run-p3: stropitori
	./stropitori

run-p4: warriors
	./warriors

clean:
	rm -f $(EXECUTABLES) $(OBJECTS)
