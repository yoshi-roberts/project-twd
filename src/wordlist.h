#ifndef WORDLIST_H
#define WORDLIST_H

#define WORDLIST_MAX_WORDS 128
#define WORD_MAX_LEN 32

typedef struct {
	char easy[WORDLIST_MAX_WORDS][WORD_MAX_LEN];
	char normal[WORDLIST_MAX_WORDS][WORD_MAX_LEN];
	char hard[WORDLIST_MAX_WORDS][WORD_MAX_LEN];
} WordList;

WordList wordlist_init();
char* wordlist_get(char (*list)[WORD_MAX_LEN]);
void _read_file(char (*list)[WORD_MAX_LEN], const char *path);

#endif // WORDLIST_H
