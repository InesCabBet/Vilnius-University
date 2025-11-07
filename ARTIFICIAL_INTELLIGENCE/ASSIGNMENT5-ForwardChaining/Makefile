# Makefile para ASSIGNMENT5-ForwardChaining
# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Carpetas
SRC_DIR = .
OBJ_DIR = build

# Archivos fuente y objetos
SRC = main.cc $(SRC_DIR)/FileParser.cc $(SRC_DIR)/forwardChaining.cc $(SRC_DIR)/Rule.cc $(SRC_DIR)/utils.cc
OBJ = $(patsubst %.cc, $(OBJ_DIR)/%.o, $(notdir $(SRC)))

# Ejecutable final
TARGET = fc

# Regla principal
all: $(TARGET)

# Enlazado final
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ)))

# Compilación de los .o en build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilación especial del main fuera de src/
$(OBJ_DIR)/main.o: main.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear carpeta build si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpieza
clean:
	rm -rf $(OBJ_DIR)

distclean: clean
	rm -f $(TARGET) *~

# Ejecución rápida
run: $(TARGET)
	./$(TARGET) input1.txt



