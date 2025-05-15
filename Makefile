main: main.c
	@echo "Executing compilation..."
	gcc -o gol main.c conway.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	@echo "Compilation finished."
clean: 
	rm -f gof
debug: main.c
	gcc -o gol_debug main.c conway.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g
	gbd ./gol_debug
	rm -f gol_debug
run: main
	@echo "Executing gol..."
	./gol