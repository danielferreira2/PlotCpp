# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Bibliotecas SFML
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Nome do executável e diretórios
SRC_DIR = .
OBJ_DIR = Obj
BIN_DIR = Bin
INC_DIR = .
EXEC_NAME = exec
EXEC = $(BIN_DIR)/$(EXEC_NAME)

# Encontrar todos os arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regra padrão
all: $(EXEC)

# Linkagem do executável
$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Compilação dos arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $@ -c $<

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild
rebuild: clean all run

# Executar o programa
run:
	./$(EXEC)
