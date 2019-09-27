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

	Player *players[2];

	Player *player_1;
	player_1 = Player__create(10, 10, '!', TB_BLACK);

	Player *player_2;
	player_2 = Player__create(tb_width() - 10, 10, '!', TB_RED);

	players[0] = player_1;
	players[1] = player_2;

	struct tb_event ev;

	/* Quit loop if player presses escape key. */
	while(ev.key != TB_KEY_ESC)
	{
		tb_clear();

		int floor = tb_height() - 10.0f;

		drawBackground(tb_width(), tb_height(), BACKGROUND_COLOR);
		drawGround(tb_width(), floor + 1, tb_height(), '~', GROUND_COLOR);

		input(&ev, players, floor);

		player_1->physics(player_1, floor);
		player_1->draw(player_1);

		player_2->physics(player_2, floor);
		player_2->draw(player_2);

		/* Check if bullets hit players. */
		if(checkCollision(player_1, player_2->bullet))
			player_1->dead = true;
		if(checkCollision(player_2, player_1->bullet))
			player_2->dead = true;

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

	player_1->destroy(player_1);
	player_2->destroy(player_2);

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
	Player *player_1 = players[0];
	Player *player_2 = players[1];

	if(!player_2->dead)
	{
		switch(ev->key)
		{
			case PLAYER_2_LEFT:
			{
				player_2->moveLeft(player_2);
				break;
			}
			case PLAYER_2_RIGHT:
			{
				player_2->moveRight(player_2);
				break;
			}
			case PLAYER_2_JUMP:
			{
				player_2->jump(player_2, floor);
				break;
			}
			case PLAYER_2_SHOOT:
			{
				player_2->shoot(player_2);
				break;
			}
		}
	}

	if(!player_1->dead)
	{
		switch(ev->ch)
		{
			case PLAYER_1_LEFT:
			{
				player_1->moveLeft(player_1);
				break;
			}
			case PLAYER_1_RIGHT:
			{
				player_1->moveRight(player_1);
				break;
			}
			case PLAYER_1_JUMP:
			{
				player_1->jump(player_1, floor);
				break;
			}
			case PLAYER_1_SHOOT:
			{
				player_1->shoot(player_1);
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
