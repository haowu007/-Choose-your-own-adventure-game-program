CFLAGS=-std=gnu99 -Werror -pedantic -Wall
test:maxSeq.o test-subseq.o
	gcc $(CFLAGS) -o test maxSeq.o test-subseq.o
maxSeq.o:maxSeq.c 
	gcc $(CFLAGS) -c maxSeq.c
test-subseq.o:test-subseq.c 
	gcc $(CFLAGS) -c test-subseq.c
.PHONY: clean
clean:
	rm -f test *.c~ *.o *.h~
depend:
	makedepend maxSeq.o test-Subseq.o
