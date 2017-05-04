EXEC_NAME = text_hash
BIN_FOLDER = bin
SRC_FOLDER = src
SRC = Main.cpp word_table.cpp
SRC_FILES = $(addprefix $(SRC_FOLDER)/, $(SRC))
OBJ_FOLDER = obj
OBJ = $(SRC:.cpp=.o)
OBJ_FILES = $(addprefix $(OBJ_FOLDER)/, $(OBJ))
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror #-Wextra
#LDLIBS = 

.PHONY: all clean veryclean

all: $(BIN_FOLDER)/$(EXEC_NAME)

$(BIN_FOLDER)/$(EXEC_NAME): $(OBJ_FILES) | $(BIN_FOLDER)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp | $(OBJ_FOLDER)
	$(CXX) $(CXXFLAGS) -c -o $@ $^

$(BIN_FOLDER) $(OBJ_FOLDER):
	@mkdir -p $@

clean:
	rm -rf $(OBJ_FOLDER)

veryclean: clean
	rm -rf $(BIN_FOLDER)
