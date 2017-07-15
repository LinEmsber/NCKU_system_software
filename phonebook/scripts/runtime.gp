reset
set ylabel 'time(sec)'
set style fill solid
set key right top
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:0.001]'output.txt' using 2:xtic(1) with histogram title 'original', \
'' using 3:xtic(1) with histogram title 'small structure'  , \
'' using 4:xtic(1) with histogram title 'list2bst'  , \
'' using 5:xtic(1) with histogram title 'hash'  , \
'' using ($0-0.2):($2+0.00006):2 with labels title ' ' textcolor lt 1, \
'' using ($0+0.0):($3+0.00006):3 with labels title ' ' textcolor lt 2, \
'' using ($0+0.3):($4+0.00006):4 with labels title ' ' textcolor lt 3, \
'' using ($0+0.6):($5+0.00004):5 with labels title ' ' textcolor lt 4
