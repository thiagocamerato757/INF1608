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

# Gerar gráficos
echo "========================================================"
echo "3. Gerando gráficos..."
echo ""
if ! command -v gnuplot &> /dev/null
then
    echo "gnuplot não foi encontrado, pulando a geração de gráficos."
    echo "Para gerar os gráficos, instale o gnuplot com o comando:"
    echo "sudo apt-get install gnuplot"
else
    bash plotar_graficos.sh
fi
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
echo "Gráficos gerados:"
echo "  - plots/comparacao_theta10.png"
echo "  - plots/diferenca_theta10.png"
echo "  - plots/comparacao_theta45.png"
echo "  - plots/diferenca_theta45.png"
echo "  - plots/comparacao_theta90.png"
echo "  - plots/diferenca_theta90.png"
echo ""
echo "Documentação:"
echo "  - docs/RELATORIO.md (relatório técnico)"
echo ""
echo "✓ Projeto concluído com sucesso!"
echo "========================================================"
