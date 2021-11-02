CXX=g++
DEBUG=0
CXXFLAGS=-Wall -O2 -g -I./include/ -D DEBUG=$(DEBUG)
PROJECT_NAME=lab2

all: dirs build run

dirs:
	mkdir -p ./bin/ ./build/

%.o: src/%.cpp include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o ./build/$@

build: uli.o bitarr.o
	$(CXX) $(CXXFLAGS) main.cpp $(addprefix build/, $^) -o ./bin/$(PROJECT_NAME)

clean:
	rm ./build/*.o

run:
	./bin/$(PROJECT_NAME)
