# Definindo o compilador e as flags de compilação
CXX = g++
CXXFLAGS = -std=c++17 -Iutils -Wall -Wextra -O2

# Definindo os arquivos fonte e os executáveis
SRC = $(wildcard *.cpp)
EXE = $(SRC:.cpp=)
OUTPUT_DIR = output

# Arquivos de utilitários e objetos
UTILS_SRC = utils/graph.cpp
UTILS_OBJ = $(UTILS_SRC:.cpp=.o)

# Garante a criação da pasta de saída
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Regra para compilar qualquer arquivo .cpp
%: %.cpp $(UTILS_OBJ) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(OUTPUT_DIR)/$@
	$(MAKE) clean

# Compilação dos arquivos .cpp em arquivos objetos .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(UTILS_OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos objetos gerados
clean:
	rm -f *.o utils/*.o

# Reset: remove todos os executáveis da pasta output
reset:
	rm -f $(OUTPUT_DIR)/*