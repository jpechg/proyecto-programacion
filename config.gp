set title 'Top 10 Centros con Mayor Ocupacion'
set ylabel 'Plazas Ocupadas (Total)'
set style fill solid 0.7 border -1
set xtics rotate by -45
set bmargin 10
plot 'ranking.dat' using 2:xtic(1) with boxes title 'Ocupacion'
pause -1 'Pulsa Enter para cerrar'
