set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output outfile
set title title_text
set xlabel "Tempo (s)"
set ylabel "Theta (rad)"
set key top right
plot datafile using 1:2 with lines linecolor "blue" title "Numerico", \
     datafile using 1:3 with lines dashtype 2 linecolor "red" title "Analitico"
