RINC=include

CXX=g++
CXXFLAGS=-std=c++11 -O3	 -Wall -pedantic -I$(RINC)
LDFLAGS=-std=c++11 -I$(RINC)

EXEC=shfs
SRC=$(wildcard *.cpp) \
	$(wildcard $(RINC)/*.cpp)
OBJ=$(SRC:.cpp=.o)
DEP=$(wildcard $(RINC)/*.hpp) \

all: $(EXEC)

default: $(EXEC)

$(EXEC): $(OBJ) $(DEP)
	$(CXX) $^ $(LDFLAGS)  -o $(EXEC)
	rm -dfr $(OBJ)
	@echo "number of lines:"
	@cat include/*.cpp include/*.hpp include/*.tpp *.cpp | wc -l

%.o: %.cpp %.hpp 
	$(CXX) $(CXXFLAGS) -c -o $@  $<

.PHONY: clean
clean:
	rm -dfr $(OBJ) $(EXEC)
