#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include "wordlist.h"

typedef struct {
	char *target;
	char buff[WORD_MAX_LEN + 1];
	int count;
} TextInput ;

TextInput text_input_new(char (*list)[WORD_MAX_LEN]);
void text_input_update(TextInput *text_input);
void text_input_draw(TextInput *text_input, int x, int y);
void text_input_reset(TextInput *text_input);

#endif // TEXT_INPUT_H
