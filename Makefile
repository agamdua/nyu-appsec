all: dictionary.o spell.o
	gcc -Wall -g -o spell_check spell.o dictionary.o

dictionary.o: AppSecAssignment1/dictionary.c
	gcc -Wall -g -c AppSecAssignment1/dictionary.c dictionary.h

spell.o: spell.c
	gcc -Wall -g -c spell.c 

run: clean all
	./spell_check something.txt wordlist.txt

test.o: test_main.c
	gcc -Wall -c test_main.c

test: dictionary.o spell.o test_main.o
	gcc -Wall -g -o test_main test_main.o spell.o dictionary.o -lcheck -lm  -lpthread
	./test_main

clean:
	rm dictionary.o spell.o
	rm spell_check

getlib:
	git submodule update --rebase --remote
