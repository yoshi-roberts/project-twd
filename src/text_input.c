#include <string.h>
#include "text_input.h"
#include "../lib/raylib/src/raylib.h"

TextInput text_input_init(char target[WORD_MAX_LEN]) {

	TextInput text_input;
	memset(text_input.buff, 0, sizeof(char) * WORD_MAX_LEN);

	text_input.target = target;
	text_input.buff[WORD_MAX_LEN] = '\0';
	text_input.count = 0;

	return text_input;
}

void text_input_update(TextInput *text_input) {

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
}

void text_input_draw(TextInput *text_input) {

	DrawText(text_input->target, 0, 0, 10, GRAY);
	DrawText(text_input->buff, 0, 0, 10, BLACK);
}
