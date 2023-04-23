
main:
	gcc runge.c -o runge -lm
	runge 5
	python plot.py
