BIN_PATH=bin
BUILD_PATH=build
PROJECT_NAME=lab2
SRC_PATH=src
INCLUDE_PATH=include

CXX=g++
DEBUG=0
CXXFLAGS=-Wall -O2 -g -I$(INCLUDE_PATH)/ -D DEBUG=$(DEBUG)

all: makedirs build

makedirs:
	@mkdir -p $(BIN_PATH) $(BUILD_PATH)

%.o: $(SRC_PATH)/%.cpp $(INCLUDE_PATH)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $(BUILD_PATH)/$@

build: uli.o bitarr.o
	$(CXX) $(CXXFLAGS) main.cpp $(addprefix $(BUILD_PATH)/, $^) -o $(BIN_PATH)/$(PROJECT_NAME)

clean:
	@rm $(BUILD_PATH)/*.o

run:
	./$(BIN_PATH)/$(PROJECT_NAME)
