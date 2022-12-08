default: build

build:
	gcc -o game src/con1.c -l ncurses

run: build
	./game

