

CC = g++ -std=c++17

all: seabattle

seabattle: main.o field.o ship.o cell.o
	$(CC) main.o field.o ship.o cell.o -o seabattle.exe

main.o: main.cpp
	$(CC) -c main.cpp

field.o: field.cpp
	$(CC) -c field.cpp

ship.o: ship.cpp
	$(CC) -c ship.cpp

cell.o: cell.cpp
	$(CC) -c cell.cpp

clean:
	rm -rf *.o seabattle.exe


// g++ -std=c++17 field.h main.cpp field.cpp ship.cpp cell.cpp -o seabattle.exe

// g++ -std=c++17 -fdiagnostics-color=always -g field.h main.cpp field.cpp ship.cpp cell.cpp -o seabattle.exe