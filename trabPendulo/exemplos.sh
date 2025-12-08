#!/bin/bash

# Script de exemplo para executar simulações do pêndulo
# Pessoa 1 - Implementação Numérica

echo "================================================"
echo "  Exemplos de Simulação - Pêndulo com RK4     "
echo "================================================"
echo ""

# Verificar se o programa está compilado
if [ ! -f "./pendulo" ]; then
    echo "Compilando programa..."
    make clean && make
    echo ""
fi

echo "=== Exemplo 1: Valores padrão ==="
echo "Comando: ./pendulo"
echo ""
./pendulo
echo ""

echo "=== Exemplo 2: Pequeno ângulo (10°) ==="
echo "Comando: ./pendulo 10 0 10 1000"
echo ""
./pendulo 10 0 10 1000 | tail -8
echo ""

echo "=== Exemplo 3: Grande ângulo (90°) ==="
echo "Comando: ./pendulo 90 0 15 2000"
echo ""
./pendulo 90 0 15 2000 | tail -8
echo ""

echo "=== Exemplo 4: Com velocidade inicial ==="
echo "Comando: ./pendulo 45 2.0 10 1000"
echo ""
./pendulo 45 2.0 10 1000 | tail -8
echo ""

echo "================================================"
echo "Dados salvos em data/"
echo "  - pendulo_data.txt"
echo "  - energia.txt"
echo ""
echo "Para ver ajuda:"
echo "  ./pendulo --help"
echo "================================================"
