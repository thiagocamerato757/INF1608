#!/bin/bash

# Diretório de dados e de plots
DATA_DIR="data"
PLOT_DIR="plots"

# Cria o diretório de plots se ele não existir
mkdir -p $PLOT_DIR

# Itera sobre todos os arquivos .txt no diretório de dados
for datafile in $DATA_DIR/*.txt; do
  # Extrai o nome base do arquivo (sem extensão e diretório)
  basename=$(basename "$datafile" .txt)
  
  # Define o nome do arquivo de saída e o título do gráfico
  outfile="$PLOT_DIR/${basename}.png"
  title="Comparacao para ${basename}"
  
  # Executa o gnuplot
  gnuplot -e "datafile='$datafile'" -e "outfile='$outfile'" -e "title_text='$title'" plot.gp
done

echo "Graficos gerados em $PLOT_DIR"
