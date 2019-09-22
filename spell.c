#include "AppSecAssignment1/dictionary.h"
#include <string.h>

// int main(int argc, char **argv) {
// 
// 	hashmap_t hashtable[HASH_SIZE];
// 
// 	char word_list[LENGTH];
// 	char file_to_check[LENGTH];
// 
// 	strcpy(file_to_check, argv[1]);
// 	printf("%s \n", file_to_check);
// 	strcpy(word_list, argv[2]);
// 
// 	printf("[INFO] Loading dictionary");
// 	load_dictionary(word_list, hashtable);
// 
// 	// printf("[INFO] Opening next file");
// 
// 	FILE *fp1;
// 	fp1 = fopen(file_to_check, "r");
// 
// 	if (fp1 == NULL) {
// 		printf("error opening file path: %s", file_to_check);
// 		return 1;
// 	}
// 
// 	char * misspelled[MAX_MISSPELLED];
// 
// 	printf("[INFO] Checking words now.");
// 
// 	int misspelled_count = check_words(fp1, hashtable, misspelled);
// 	printf("%d", misspelled_count);
// 
// 	return 0;
// }


int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[])
{
	char c;
	char word[LENGTH + 1];
	int num_misspelled = 0;
	int index_misspelled = -1;

	int i = 0;

	while((c = fgetc(fp)) != EOF) {
		if (c == ' ' || c == '\n') {
			// TODO: remove punctuation from beginning and end of line
			word[i] = '\0';

			if (!check_word(word, hashtable)) {
				strcpy(misspelled[index_misspelled+1],word);
				num_misspelled++;
			}

			// reset
			i = 0;

		} else {
			word[i] = c;
			i++;
		}
	}
	return num_misspelled;
}


bool check_word(const char* word, hashmap_t hashtable[]) {
	printf("Checking word: %s", word);
	int hash_value = hash_function(word);

	hashmap_t entry = hashtable[hash_value];

	if (entry == '\0') {
		// there is nothing from the dictionary hashed at this location
		// so its definitely an error
		return false;
	}

	do {
		// if entry->word is the same as word
		// return true
		// otherwise move the pointer along
		if (strcmp(word, entry->word) == 0) {
		 	// If there is a match, it is spelled correctly
			return true;
		} else {
		 	// otherwise move to the next node
			entry = entry->next;
		}
	} while (entry != NULL);

	return false;
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
			word[i] = '\0';

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
	printf("closing file\n");

	fclose(fp);
	printf("Number of words processed: %d \n", word_counter);
	printf("done?\n");
	return true;
}