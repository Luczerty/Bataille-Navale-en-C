all: exec

main.o: main.c function.h
	gcc -c main.c -o main.o

computer.o: computer.c function.h
	gcc -c computer.c -o computer.o  

play.o: play.c function.h
	gcc -c play.c -o play.o

exec: main.o play.o computer.o
	gcc main.o play.o computer.o -o exec