# 1. Terminal con 'noenhanced' para que los guiones bajos no rompan el texto
set terminal pngcairo size 1200,800 font "Verdana,13" noenhanced
set output 'grafico_perfecto.png'

# 2. Desactivar explícitamente el modo enhanced por si acaso
set termoption noenhanced

# 3. Márgenes suficientes para los nombres largos
set bmargin 15
set lmargin 12

# 4. Ajuste crítico de las etiquetas
# 'right' ancla el final del texto al eje.
# 'offset 0,-1' lo baja para que no toque las barras.
set xtics rotate by -45 right offset 0,-1

# 5. Estética general
set title 'Top 10 Actividades' font "Verdana,22" offset 0,1
set ylabel 'Plazas Ocupadas' font "Verdana,14"
set grid y lc rgb "#eeeeee"
set style fill solid 0.8 border -1
set boxwidth 0.7

# 6. Dibujar
plot 'top_actividades.dat' using 2:xtic(1) with boxes lc rgb "#7fb3d5" notitle
