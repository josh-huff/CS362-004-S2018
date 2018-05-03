CFLAGS = -Wall -fpic -coverage -lm
	
testme: testme.c
	gcc -o testme -g  testme.c $(CFLAGS) 

clean:
	rm -f testme.o testme testme.c.gcov testme.gcda testme.gcno
