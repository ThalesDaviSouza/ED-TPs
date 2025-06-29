# Configurações do compilador
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS := 

# Diretórios
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Arquivos fonte
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TARGET := $(BIN_DIR)/tp3.exe

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

# Regras para compilar cada arquivo objeto
$(OBJ_DIR)/avl_tree.o: $(SRC_DIR)/avl_tree.cpp include/avl_tree.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/list.o: $(SRC_DIR)/list.cpp include/list.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/event.o: $(SRC_DIR)/event.cpp include/event.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/package.o: $(SRC_DIR)/package.cpp include/package.hpp include/list.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/client.o: $(SRC_DIR)/client.cpp include/client.hpp include/list.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/logistics_system.o: $(SRC_DIR)/logistics_system.cpp include/logistics_system.hpp include/avl_tree.hpp include/event.hpp include/package.hpp include/client.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp include/logistics_system.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
