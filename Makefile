
main:
	gcc stuetzstellen.c -o stuetzstellen 
	stuetzstellen 20 -5 5 stuetzstellen.txt
	gcc newton_interpolation.c -o interpolation
	interpolation stuetzstellen.txt
	python plot.py
