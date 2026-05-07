set terminal pngcairo size 1200,800 font 'Verdana,13' noenhanced
set output "grafico.png"
set title 'Top 10 Actividades en Gallur' font 'Verdana,22' offset 0,1
set ylabel 'Plazas Ocupadas' font 'Verdana,14'
set bmargin 15
set lmargin 12
set xtics rotate by -45 left font 'Verdana,12' offset 0,0
set grid y lc rgb '#eeeeee'
set style fill solid 0.8 border -1
set boxwidth 0.7
plot 'top_actividades.dat' using 2:xtic(1) with boxes lc rgb '#7fb3d5' notitle
