#include <stdio.h>
#include "wordlist.h"
#include "log.h"

WordList wordlist_init() {

	WordList words;

	_get_words(words.easy, "src/words/easy.txt");
	_get_words(words.normal, "src/words/normal.txt");
	_get_words(words.hard, "src/words/hard.txt");

	return words;
}

void _get_words(char (*list)[WORD_MAX_LEN], const char *path) {

	FILE *file;
	file = fopen(path, "r");

	if (file == NULL) {
		log_error("Could not open file: %s", path);
		return;
	}

	int line = 0;

	while (!feof(file) && !ferror(file)) {
		if (fgets(list[line], WORD_MAX_LEN, file) != NULL) {
			line++;
		}
	}

	fclose(file);
}
