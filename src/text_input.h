#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

typedef struct {
	char buff[33];
	int count;
} TextInput ;

TextInput text_input_init();
void text_input_update(TextInput *text_input);
void text_input_draw(TextInput *text_input);

#endif // TEXT_INPUT_H
