all: dictionary.o spell.o
	gcc -Wall -o spell_check spell.o dictionary.o

dictionary.o: AppSecAssignment1/dictionary.c
	gcc -Wall -c AppSecAssignment1/dictionary.c AppSecAssignment1/dictionary.h

spell.o: spell.c
	gcc -Wall -c spell.c 

run: clean all
	./spell_check something.txt wordlist.txt

clean:
	rm dictionary.o spell.o
	rm spell_check

getlib:
	git submodule update --rebase --remote
