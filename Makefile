
main:
	gcc stuetzstellen.c -o stuetzstellen 
	stuetzstellen 20 -5 5 stuetzstellen.txt
	gcc newton_interpolation.c -o interpolation
	interpolation stuetzstellen.txt
	python plot.py

neville:
	gcc stuetzstellen.c -o stuetzstellen
	gcc neville-aitken.c -o neville
	stuetzstellen 5 -5 5 stuetzstellen.txt
	neville stuetzstellen.txt -6 6 200 neville-ergebnis.txt
	python neville_plot.py stuetzstellen.txt neville-ergebnis.txt