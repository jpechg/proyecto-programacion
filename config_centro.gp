set title 'Evolucion de Ocupacion: Gallur'
set xlabel 'Muestras / Actividades'
set ylabel 'Plazas Ocupadas'
set grid
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5
plot 'centro_especifico.dat' with linespoints ls 1 title 'Ocupacion'
pause -1 'Pulsa Enter para cerrar'
