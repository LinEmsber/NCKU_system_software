reset
set xlabel 'numerical distribution'
set ylabel 'time'
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'
set xtic 2000
plot [:][:0.0000003]'byte.txt' using 2 with linespoints title 'byte',\
'harley.txt' using 2 with linespoints title 'harley',\

