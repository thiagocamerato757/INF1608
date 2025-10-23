CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lm
TARGET = simula
SOURCES = main.c massamola.c
HEADERS = massamola.h
OUTPUT = output.txt

all: $(TARGET) $(OUTPUT)

$(TARGET): $(SOURCES) $(HEADERS)
	@$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

$(OUTPUT): $(TARGET)
	@./$(TARGET) > $(OUTPUT)
	@echo "output.txt gerado com sucesso!"

clean:
	rm -f $(TARGET) $(OUTPUT)

.PHONY: all clean
