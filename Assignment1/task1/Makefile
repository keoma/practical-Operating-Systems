all: picalc

picalc: libpi src/control.c
		mkdir -p bin
		gcc src/control.c -lpthread lib/pi.o -o bin/picalc
		
dummy: libdummy src/control.c
		mkdir -p bin

libdummy: src/calculator.c
		mkdir -p lib
		gcc src/calculator.c -c -o lib/calculator.o

libpi: src/pi.c
		mkdir -p lib

clean:
		rm -rf lib/pi.o bin/picalc
