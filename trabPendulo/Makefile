CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
LDFLAGS = -lm

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
DATA_DIR = data

# Arquivos fonte
SOURCES = $(SRC_DIR)/runge_kutta.c
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Executáveis
MAIN = pendulo
TEST = test_rk4

.PHONY: all clean test dirs plot

all: dirs $(MAIN)

dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(DATA_DIR)
	@mkdir -p plots

# Compilar programa principal
$(MAIN): $(OBJECTS) $(BUILD_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "✓ Executável $(MAIN) criado com sucesso!"

# Compilar testes
test: dirs $(OBJECTS) $(BUILD_DIR)/test_rk4.o
	$(CC) $(CFLAGS) $(OBJECTS) $(BUILD_DIR)/test_rk4.o -o $(TEST) $(LDFLAGS)
	@echo "✓ Executável de teste $(TEST) criado com sucesso!"
	@echo "Execute com: ./$(TEST)"

# Regras de compilação
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test_rk4.o: $(TEST_DIR)/test_rk4.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Executar testes
run-test: test
	./$(TEST)

# Executar programa principal
run: $(MAIN)
	./$(MAIN)

# Limpar arquivos compilados
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(MAIN) $(TEST)
	@echo "✓ Arquivos de compilação removidos"

# Limpar tudo incluindo dados e plots
clean-all: clean
	rm -rf $(DATA_DIR)/*
	rm -rf plots/*
	@echo "✓ Dados e plots removidos"

.PHONY: plot
plot:
	@bash plotar_graficos.sh
