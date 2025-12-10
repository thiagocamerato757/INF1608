# Configura o terminal para saida em PNG
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'

# Configura o nome do arquivo de saida
set output outfile

# Configura o titulo do grafico
set title title_text

# Configura os rotulos dos eixos
set xlabel "Tempo (s)"
set ylabel "Theta (rad)"

# Configura a legenda
set key top right

# Plota os dados
plot datafile using 1:2 with lines title "Numerico", \
     datafile using 1:3 with lines title "Analitico"

