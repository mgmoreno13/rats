compilar: 
	gcc -g -o ex cut.c proyecto.c memo.c aleatorio.c metrica.c genetico.c -std=c99 -lm 
	./ex
makehelp:
	@echo compilar: make -f Makefile compilar
	


