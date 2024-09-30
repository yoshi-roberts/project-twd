#include <stdio.h>
#include "../lib/raylib/src/raylib.h"
#include "wordlist.h"
#include "log.h"

WordList wordlist_init() {

	WordList words;

	_read_file(words.easy, "src/words/easy.txt");
	_read_file(words.normal, "src/words/normal.txt");
	_read_file(words.hard, "src/words/hard.txt");

	return words;
}

char* wordlist_get(char (*list)[32]) {
	return list[GetRandomValue(0, WORDLIST_MAX_WORDS)];
}

void _read_file(char (*list)[WORD_MAX_LEN], const char *path) {

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
