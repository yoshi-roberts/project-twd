#include <stdio.h>
#include <string.h>
#include <math.h>
#include "text_input.h"
#include "../lib/raylib/src/raylib.h"
#include "assets.h"
#include "wordlist.h"

TextInput text_input_init(char (*list)[WORD_MAX_LEN]) {

	TextInput text_input;
	memset(text_input.buff, 0, sizeof(char) * WORD_MAX_LEN);

	text_input.target = wordlist_get(list);
	text_input.buff[WORD_MAX_LEN] = '\0';
	text_input.count = 0;

	return text_input;
}

void text_input_reset(TextInput *text_input) {
	memset(text_input->buff, 0, sizeof(char) * WORD_MAX_LEN);
	text_input->buff[WORD_MAX_LEN] = '\0';
	text_input->count = 0;
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

	Asset *fnt = assets_get("assets/fonts/monogram.ttf");

	Vector2 size = MeasureTextEx(fnt->data.font, text_input->target, 12, 2);
	Vector2 pos = {
   		floor((480 / 2.0f) - (size.x / 2)),
		floor((270 / 3.0f) - (size.y / 2)),
	};
	

	DrawTextEx(
		fnt->data.font,
		text_input->target,
		pos,
		12,
		2,
		WHITE
	);
	DrawTextEx(
		fnt->data.font,
		text_input->buff,
		pos,
		12,
		2,
		DARKPURPLE
	);
}
