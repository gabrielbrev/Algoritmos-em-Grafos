# Definindo o compilador e as flags de compilação
CXX = g++
CXXFLAGS = -std=c++17 -Isrc/utils -Wall -Wextra -O2

# Definindo os arquivos fonte e os executáveis
SRC = $(wildcard src/*.cpp)
EXE = $(patsubst src/%.cpp,%,$(SRC))
OUTPUT_DIR = output

# Arquivos de utilitários e objetos
UTILS_SRC = src/utils/graph.cpp src/utils/digraph.cpp
UTILS_OBJ = $(UTILS_SRC:.cpp=.o)

# Garante a criação da pasta de saída
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Regra para compilar qualquer arquivo .cpp dentro de src/
%: src/%.cpp $(UTILS_OBJ) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(OUTPUT_DIR)/$@
	$(MAKE) clean

# Compilação dos arquivos .cpp em arquivos objetos .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(UTILS_OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos objetos gerados
clean:
	rm -f src/*.o src/utils/*.o

# Reset: remove todos os executáveis da pasta output
reset:
	rm -f $(OUTPUT_DIR)/*