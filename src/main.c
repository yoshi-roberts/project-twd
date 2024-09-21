#include "game.h"
#include "interface.h"
#include <stdio.h>

int main(int argc, char** argv) {

	WordList words;

	game_init();

	word_list_init(&words);
	printf("%s", words.easy[12]);

	game_update();
	game_shutdown();

	word_list_destroy(&words);

    return 0;
}
