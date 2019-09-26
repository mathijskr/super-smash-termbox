#include <stdio.h>
#include <string.h>

#include "termbox.h"

#define BACKGROUND_COLOR TB_GREEN
#define SCREEN_HEIGHT 200
#define SCREEN_WIDTH 200

void drawBackground(int width, int heigth, int color)
{
	for(int y = 0; y < heigth; y++)
		for(int x = 0; x < heigth; x++)
			tb_change_cell(x, y, ' ', TB_DEFAULT, BACKGROUND_COLOR);
}


int main(int argv, char **argc)
{
	(void)argc; (void)argv;

	int code = tb_init();

	/* Check if termbox was initialized. */
	if (code < 0)
	{
		fprintf(stderr, "termbox init failed, code: %d\n", code);
		return -1;
	}

	tb_select_input_mode(TB_INPUT_ESC);
	tb_select_output_mode(TB_OUTPUT_NORMAL);
	tb_clear();

	int x = 100, y = 10;

	struct tb_event ev;

	/* Quit loop if player presses escape key. */
	while(ev.key != TB_KEY_ESC)
	{
		tb_clear();

		drawBackground(SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);

		if(ev.key == TB_KEY_ARROW_LEFT)
			x--;

		tb_poll_event(&ev);

		tb_change_cell(x, y, '*', TB_RED, BACKGROUND_COLOR);

		tb_present();
	}

	tb_shutdown();
	return 0;
}
