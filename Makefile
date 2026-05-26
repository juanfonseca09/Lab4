# Variables
CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -Iinclude
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN = main

# Busca todos los .cpp en src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# Reemplaza src/*.cpp por obj/*.o
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Regla por defecto
all: $(BIN)

# Compilación final
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilación de cada .cpp a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorio obj si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpieza
clean:
	rm -rf $(OBJ_DIR) *.o $(BIN)

# Test con valgrind
test: $(BIN)
	valgrind ./$(BIN)

.PHONY: all clean test