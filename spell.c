#include "AppSecAssignment1/dictionary.h"
#include <string.h>

int main(int argc, char **argv) {

	hashmap_t hashtable[HASH_SIZE];

	char word_list[LENGTH];
	char file_to_check[LENGTH];

	strcpy(file_to_check, argv[1]);
	strcpy(word_list, argv[2]);

	if (!load_dictionary(word_list, hashtable)) {
		printf("oops\n");
		return 1;
	};

	FILE *fp;
	fp = fopen(file_to_check, "r");

	if (fp == NULL) {
		printf("error opening file path: %s", file_to_check);
		return 1;
	}

	char * misspelled[MAX_MISSPELLED];

	int misspelled_count = check_words(fp, hashtable, misspelled);
	printf("%d", misspelled_count);

	return 0;
}


int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[])
{
	char c;
	char word[LENGTH + 1];

	int i = 0;

	while((c = fgetc(fp)) != EOF) {
		if (c == ' ' || c == '\n') {
			word[i + 1] = '\0';
		}
	}

	return 0;
}

/** Loads the dictionary and process words to add them to the hashtable
 * 
 *  Steps:
 * 		1. Open the file
 * 		2a. Parse for words
 * 		2b. Calculate the hash of each word
 * 
 */
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{
	// Step 1: Open the file
	FILE *fp;
	fp = fopen(dictionary_file, "r");

	if (fp == NULL) {
		printf("error opening file path: %s", dictionary_file);
		return false;
	}

	// Step 2: hash word and load it into the hashmap
	char c;
	char word[LENGTH + 1];

	int i = 0;
	int word_counter = 0;

	// TODO: guard against word length > LENGTH
	int c_counter = 0;

	memset(hashtable, '\0', HASH_SIZE);

	while((c = fgetc(fp)) != EOF) {
		if (c == ' ' || c == '\n') {
			// generate hash
			int hash_value = hash_function(word);

			// generate node type to add in array
			word[i + 1] = '\0';

			node n;

			strcpy(n.word, word);
			n.next = NULL;

			// add to array
			if (hashtable[hash_value] !=  '\0') {
				n.next = hashtable[hash_value];
			} 
			hashtable[hash_value] = &n;

			// printf("%s\n", hashtable[hash_value]->word);
			
			// reset
			i = 0;

			// increment to continue
			word_counter++;
		} else {
			word[i] = c;
			c_counter++;
			i++;
		}
	}
	fclose(fp);
	printf("Number of words processed: %d\n", word_counter);
	return true;
}