all: picalc

picalc: libcalc src/control.c
<<<<<<< HEAD
		mkdir -p bin/
		gcc src/control.c -lpthread lib/pi.o -o bin/picalc -Wall
		
dummy: libdummy src/control.c
		mkdir -p bin/
		gcc src/control.c -lpthread lib/calculator.o -o bin/dummy -Wall

libdummy: src/calculator.c
		mkdir -p lib/
		gcc src/calculator.c -c -o lib/calculator.o -Wall
		
libpi: src/pi.c
		mkdir -p lib/
		gcc src/pi.c -c -o lib/pi.o -Wall
=======
		mkdir -p bin
		gcc src/control.c -lpthread lib/calculator.o -o bin/picalc

libcalc: src/calculator.c
		mkdir -p lib
		gcc src/calculator.c -c -o lib/calculator.o
>>>>>>> FETCH_HEAD

clean:
		rm -rf lib/pi.o lib/calculator.o bin/picalc bin/dummy
