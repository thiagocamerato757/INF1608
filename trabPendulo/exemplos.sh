#!/bin/bash

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

echo "NOTA: O programa atual executa experimentos automatizados."
echo "Para ver todos os experimentos, execute: ./pendulo"
echo ""
echo "================================================"
echo ""

echo "=== Exemplo 1: Executar todos os experimentos ==="
echo "Comando: ./pendulo"
echo ""
echo "Executa automaticamente:"
echo "  - Experimentos com θ₀ = 5°, 10°, 30°, 45°, 60°, 90°, 120°, 150°"
echo "  - Comparação de métodos (analítico, h=0.01, 0.001, 0.0001, adaptativo)"
echo "  - Geração de dados para plotagem externa"
echo "  - Determinação do ângulo máximo para erro < 0.001"
echo ""
read -p "Pressione ENTER para executar os experimentos completos (Ctrl+C para cancelar)..."
./pendulo

echo ""
echo "================================================"
echo "Dados gerados em data/"
echo "  - comparacao_theta10.txt"
echo "  - comparacao_theta45.txt"
echo "  - comparacao_theta90.txt"
echo ""
echo "Formato dos arquivos:"
echo "  t(s)  theta_num(rad)  theta_anal(rad)  diferenca(rad)"
echo ""
echo "Para ver ajuda:"
echo "  ./pendulo --help"
echo ""
echo "Para executar testes de validação:"
echo "  make test && ./test_rk4"
echo "================================================"

