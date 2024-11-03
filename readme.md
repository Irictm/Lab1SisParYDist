# Algunos scripts utiles

Para construir el proyecto:

make main


Para visualizar los puntos leidos se puede usar:

./main -i archivo.fits -e 2 > scatter.txt
py drawpoints.py


Para visualizar las elipses encontradas:

./main -i archivo.fits -a 10 -b 100 -r 0.35 > ellipses.txt
py drawellipse.py