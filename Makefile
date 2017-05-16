deuizdivac: main.o groom.o bride.o	registar.o
	gcc main.o bride.o groom.o	registar.o -o deuizdivac	-lpthread

main.o: main.c  global.h
	gcc -c main.c

groom.o: groom.c groom.h
	gcc -c groom.c

bride.o: bride.c bride.h
	gcc -c bride.c

registar.o:	registar.c	registar.h
	gcc	-c	registar.c

clean:
	rm *.o output
