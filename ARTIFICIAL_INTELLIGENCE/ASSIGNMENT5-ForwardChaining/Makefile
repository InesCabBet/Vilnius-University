# Makefile para ASSIGNMENT5-ForwardChaining
# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Carpetas
SRC_DIR = src/
OBJ_DIR = build

# Archivos fuente y objetos
SRC = $(SRC_DIR)/main.cc $(SRC_DIR)/FileParser.cc $(SRC_DIR)/forwardChaining.cc $(SRC_DIR)/Rule.cc $(SRC_DIR)/utils.cc
OBJ = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRC))

# Nombre del ejecutable
TARGET = fc

# Regla principal
all: $(TARGET)

# Enlazado final
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla genérica para compilar cada .cc en build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear carpeta build si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpieza
clean:
	rm -rf $(OBJ_DIR)

distclean: clean
	rm -f $(TARGET) *~


