#!/bin/bash

# Script para executar e apresentar resultados do projeto

echo "========================================================"
echo "  SIMULAÇÃO DE PÊNDULO - MÉTODO RUNGE-KUTTA 4ª ORDEM  "
echo "  INF1608 - Análise Numérica                          "
echo "========================================================"
echo ""

# Verificar se o executável existe, caso contrário compilar
if [ ! -f "./pendulo" ]; then
    echo "Compilando programa..."
    make clean && make
    echo ""
fi

# Executar testes
echo "1. Executando testes de validação..."
echo ""
./test_rk4
echo ""

# Executar experimentos completos
echo "========================================================"
echo "2. Executando experimentos completos..."
echo ""
./pendulo

echo ""
echo "========================================================"
echo "  RESULTADOS DISPONÍVEIS"
echo "========================================================"
echo ""
echo "Dados numéricos gerados:"
echo "  - data/comparacao_theta10.txt"
echo "  - data/comparacao_theta45.txt"
echo "  - data/comparacao_theta90.txt"
echo ""
echo "Documentação:"
echo "  - docs/RELATORIO.md (relatório técnico)"
echo ""
echo "✓ Projeto concluído com sucesso!"
echo "✓ Os dados estão prontos para plotagem externa (adicionar a parte de plotagem dps)"
echo "========================================================"
