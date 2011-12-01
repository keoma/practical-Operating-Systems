all: picalc

picalc: libpi src/control.c
		mkdir -p bin
		gcc src/control.c -lpthread lib/pi.o -o bin/picalc -Wall
		
dummy: libdummy src/control.c
		mkdir -p bin
		gcc src/control.c -lpthread lib/dummy.o -o bin/dummy -Wall

libdummy: src/calculator.c
		mkdir -p lib
		gcc src/calculator.c -c -o lib/dummy.o -Wall

libpi: src/pi.c
		mkdir -p lib
		gcc src/pi.c -c -o lib/pi.o -Wall

clean:
		rm -rf lib/pi.o lib/dummy.o bin/picalc bin/dummy
