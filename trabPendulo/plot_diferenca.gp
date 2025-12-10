set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output outfile
set title title_text
set xlabel "Tempo (s)"
set ylabel "Diferenca (rad)"
set key top right
plot datafile using 1:(abs($2-$3)) with lines title "|Numerico - Analitico|"
