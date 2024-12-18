#include <stdio.h>
#include <string.h>
#include "text_input.h"
#include "../lib/raylib/src/raylib.h"
#include "wordlist.h"

TextInput text_input_new(char (*list)[WORD_MAX_LEN]) {

	TextInput text_input;
	memset(text_input.buff, 0, sizeof(char) * WORD_MAX_LEN);

	text_input.target = wordlist_get(list);
	text_input.buff[WORD_MAX_LEN] = '\0';
	text_input.count = 0;
	text_input.list = list;

	return text_input;
}

void text_input_reset(TextInput *text_input) {
	memset(text_input->buff, 0, sizeof(char) * WORD_MAX_LEN);
	text_input->target = wordlist_get(text_input->list);
	text_input->buff[WORD_MAX_LEN] = '\0';
	text_input->count = 0;
}

bool text_input_update(TextInput *text_input) {

	int key = GetCharPressed();

	while (key > 0) {
	
		if ((key >= 32) && (key <= 125) && (text_input->count < 32)) {

			if ((char)key != text_input->target[text_input->count]) {
				break;
			}

			text_input->buff[text_input->count] = (char)key;
			text_input->buff[text_input->count+1] = '\0';
			text_input->count++;
		}

		key = GetCharPressed();
	}

	if (IsKeyPressed(KEY_BACKSPACE)) {
		text_input->count--;
		if (text_input->count < 0) text_input->count = 0;
		text_input->buff[text_input->count] = '\0';
	}

	if (text_input->count == strlen(text_input->target) - 1) {
		return true;
	}

	return false;
}

void text_input_draw(TextInput *text_input, int x, int y) {

	int size = MeasureText(text_input->target, 10);

	int xp = x - (size / 2);
	int yp = y - (10 / 2);

	DrawText(text_input->target, xp, yp, 10, WHITE);
	DrawText( text_input->buff, xp, yp, 10, DARKPURPLE);
}
