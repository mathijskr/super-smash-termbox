#include "main.h"

int main(int argv, char **argc)
{
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

	/* Create new players. */
	Player *players[NUMBER_OF_PLAYERS];
	players[PLAYER_1] = Player__create(tb_width() - PLAYER_START_X, PLAYER_START_Y, '!', TB_RED);
	players[PLAYER_2] = Player__create(PLAYER_START_X, PLAYER_START_Y, '!', TB_BLACK);

	struct tb_event ev;

	int victory = -1;

	/* Quit loop if player presses escape key. */
	while(ev.key != TB_KEY_ESC)
	{
		tb_clear();

		int floor = tb_height() - 10.0f;

		drawBackground(tb_width(), tb_height(), BACKGROUND_COLOR);
		drawGround(tb_width(), floor + 1, tb_height(), '~', GROUND_COLOR);

		if(victory != -1)
			drawVictory(victory);

		/* Handle input. */
		input(&ev, players, floor);

		/* Update and draw all players. */
		for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
		{
			players[i]->physics(players[i], floor);
			players[i]->draw(players[i]);
		}

		/* Check if bullets hit players. */
		if(checkCollision(players[PLAYER_1], players[PLAYER_2]->bullet))
		{
			players[PLAYER_1]->dead = true;
			victory = PLAYER_1;
		}
		if(checkCollision(players[PLAYER_2], players[PLAYER_1]->bullet))
		{
			players[PLAYER_2]->dead = true;
			victory = PLAYER_2;
		}

		/* Draw to screen. */
		tb_present();

		/* Sleep for 10 ms. */
		struct timespec tim, tim2;
		tim.tv_sec = 0;
		tim.tv_nsec = 10000000L;
		nanosleep(&tim, &tim2);

		/* Update input with a timeout of n ms. */
		tb_peek_event(&ev, 0);
	}

	/* Clean up. */
	players[0]->destroy(players[0]);
	players[1]->destroy(players[1]);

	tb_shutdown();
	return 0;
}

/* Make the background a constant color. */
void drawBackground(int width, int heigth, int color)
{
	for(int y = 0; y < heigth; y++)
		for(int x = 0; x < width; x++)
			tb_change_cell(x, y, ' ', TB_DEFAULT, BACKGROUND_COLOR);
}

void drawGround(int width, int height, int maxHeight, char symbol, int color)
{
	for(int y = height; y < maxHeight; y++)
		for(int x = 0; x < width; x++)
			tb_change_cell(x, y, symbol, TB_DEFAULT, GROUND_COLOR);
}

void input(struct tb_event *ev, Player *(*players), int floor)
{
	if(!players[PLAYER_1]->dead)
	{
		switch(ev->key)
		{
			case PLAYER_1_LEFT:
			{
				if(players[PLAYER_1]->x > 0)
					players[PLAYER_1]->moveLeft(players[PLAYER_1]);
				break;
			}
			case PLAYER_1_RIGHT:
			{
				if(players[PLAYER_1]->x < tb_width() - PLAYER_SIZE_X)
					players[PLAYER_1]->moveRight(players[PLAYER_1]);
				break;
			}
			case PLAYER_1_JUMP:
			{
				players[PLAYER_1]->jump(players[PLAYER_1], floor);
				break;
			}
			case PLAYER_1_SHOOT:
			{
				players[PLAYER_1]->shoot(players[PLAYER_1]);
				break;
			}
		}
	}

	if(!players[PLAYER_2]->dead)
	{
		switch(ev->ch)
		{
			case PLAYER_2_LEFT:
			{
				if(players[PLAYER_2]->x > 0)
					players[PLAYER_2]->moveLeft(players[PLAYER_2]);
				break;
			}
			case PLAYER_2_RIGHT:
			{
				if(players[PLAYER_2]->x < tb_width() - PLAYER_SIZE_X)
					players[PLAYER_2]->moveRight(players[PLAYER_2]);
				break;
			}
			case PLAYER_2_JUMP:
			{
				players[PLAYER_2]->jump(players[PLAYER_2], floor);
				break;
			}
			case PLAYER_2_SHOOT:
			{
				players[PLAYER_2]->shoot(players[PLAYER_2]);
				break;
			}
		}
	}
}

bool checkCollision(Player *player, Bullet *bullet)
{
	if(bullet->x >= player->x - (player->size_x / 2.0f) && bullet->x <= player->x + (player->size_x / 2.0f))
		if(bullet->y >= player->y - (player->size_y / 2.0f) && bullet->y <= player->y + player->size_y / 2.0f)
			return true;

	return false;
}

void drawVictory(int victory)
{
	int playerStringLength = 9;
	int totalLength = playerStringLength + 4;

	int x = tb_width() / 2.0f - totalLength / 2.0f;
	int y = 10;

	if(victory == PLAYER_1)
		drawString("Player 1 ", playerStringLength, x, y);

	if(victory == PLAYER_2)
		drawString("Player 2 ", playerStringLength, x, y);

	drawString("won!", 4, x + playerStringLength, y);
}

void drawString(char *string, int length, int x, int y)
{
	for(int i = 0; i < length; i++)
		tb_change_cell(x + i, y, string[i], TB_BLACK, TB_WHITE);
}
