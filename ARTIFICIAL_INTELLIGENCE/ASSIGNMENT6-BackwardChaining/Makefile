# === CONFIGURACIÓN ===
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
SRC_DIR := src
BUILD_DIR := build
TARGET := bc   # ejecutable en la carpeta raíz

# === ARCHIVOS ===
SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS := $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(SRCS))

# === REGLAS ===
all: $(TARGET)

# Ejecutable principal (en la raíz)
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilación de cada archivo fuente
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar compilados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Ejecutar el programa con un input (por ejemplo: make run FILE=input1.txt)
run: all
	@./$(TARGET) $(FILE)

# === UTILIDADES ===
.PHONY: all clean run


