all: picalc

picalc: libcalc src/control.c
		mkdir -p bin
		gcc src/control.c -lpthread lib/calculator.o -o bin/picalc

libcalc: src/calculator.c
		mkdir -p lib
		gcc src/calculator.c -c -o lib/calculator.o

clean:
		rm -rf lib/*.o bin/picalc
