#!/bin/bash

DATA_DIR="data"
PLOT_DIR="plots"

mkdir -p $PLOT_DIR

for datafile in $DATA_DIR/comparacao_*.txt; do
  angle=$(echo "$datafile" | grep -o -E '[0-9]+')

  # Gráfico de Comparação
  outfile_comp="$PLOT_DIR/comparacao_theta${angle}.png"
  title_comp="Comparação de Soluções - θ₀ = ${angle}°"
  gnuplot -e "datafile='$datafile'" -e "outfile='$outfile_comp'" -e "title_text='$title_comp'" plot_comparacao.gp

  # Gráfico de Diferença
  outfile_diff="$PLOT_DIR/diferenca_theta${angle}.png"
  title_diff="Diferença entre Soluções - θ₀ = ${angle}°"
  gnuplot -e "datafile='$datafile'" -e "outfile='$outfile_diff'" -e "title_text='$title_diff'" plot_diferenca.gp
done

echo "Graficos gerados em $PLOT_DIR"
