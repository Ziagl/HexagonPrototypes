EXE=engine
BIN=bin
SRC=src
OBJ=$(BIN)/app.o $(BIN)/field.o $(BIN)/map.o
LIBS=clanApp clanDisplay clanCore clanGL

PACKAGES = $(patsubst %,%-4.1,$(LIBS))
# CXXFLAGS += `pkg-config --cflags $(PACKAGES)` -mthreads
CXXFLAGS += `pkg-config --cflags $(PACKAGES)` -pthread -ggdb -std=c++17
LDFLAGS += -ldl

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXE) `pkg-config --libs $(PACKAGES)` $(EXTRA_LIBS)

clean:
	rm -f $(BIN)/* $(EXE)

$(BIN)/%.o : $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
