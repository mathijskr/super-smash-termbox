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
	players[PLAYER_1] = Player__create(tb_width() - PLAYER_START_X, PLAYER_START_Y, TB_RED);
	players[PLAYER_2] = Player__create(PLAYER_START_X, PLAYER_START_Y, TB_BLACK);

	/* Needed for nanosleep. */
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = 10000000L;

	struct tb_event ev;

	int victory = -1;

	bool exitGame = false;
	bool menuOpen = false;

	int selectedItem = MENU_EXIT;

	/* Quit loop if player presses escape key. */
	while(!exitGame)
	{
		tb_clear();

		int floor = tb_height() - 5.0f;

		/* Draw background. */
		drawRectangle(0, tb_width(), 0, floor, BACKGROUND_COLOR, BACKGROUND_SYMBOL, BACKGROUND_COLOR);

		/* Draw ground. */
		drawRectangle(0, tb_width(), floor, tb_height(), GROUND_COLOR, GROUND_SYMBOL, TB_DEFAULT);

		/* Draw platforms. */
		for(int i = 0; i < level1.number_of_platforms; i++)
			Platform__draw(&level1.platforms[i]);

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
			menuOpen = true;
		}

		if(checkCollision(players[PLAYER_2], players[PLAYER_1]->bullet))
		{
			players[PLAYER_2]->dead = true;
			victory = PLAYER_2;
			menuOpen = true;
		}

		/* Check if players are standing on obstacles. */
		for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
		{
			for(int j = 0; j < level1.number_of_platforms; j++)
			{
				if(players[i]->x <= level1.platforms[j].x_r - PLAYER_SIZE_X / 2.0f &&
				   players[i]->x >= level1.platforms[j].x_l &&
				   players[i]->y < level1.platforms[j].y_u &&
				   players[i]->y > level1.platforms[j].y_d - PLAYER_SIZE_Y / 2.0f)
				{
					/* Place a player underneath or upon an object depending on their direction of vertical velocity. */
					if(players[i]->vy >= 0)
						players[i]->y = level1.platforms[j].y_d - PLAYER_SIZE_Y / 2.0f;
					else
						players[i]->y = level1.platforms[j].y_u;

					/* Cancel a player's inertia. */
					players[i]->vy = 0;
					players[i]->ay = 0;
				}
			}
		}

		if(victory != -1)
			drawVictory(victory);

		/* Handle input. */
		if(input(&ev))
			menuOpen = !menuOpen;

		int menuAction = -1;

		if(menuOpen)
		{
			menuAction = inputMenu(&ev);
			selectedItem = moveMenuCursor(menuAction, selectedItem);

			if(menuAction == MENU_SELECT)
			{
				switch(selectedItem)
				{
					case MENU_EXIT: exitGame = true; break;
					case MENU_RESTART:
					{
						/* Close victory message. */
						victory = -1;

						/* Revive players. */
						for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
							players[i]->dead = false;

						/* Close menu. */
						menuOpen = false;

						/* Reset player positions. */
						players[PLAYER_1]->x = tb_width() - PLAYER_START_X;
						players[PLAYER_2]->x = PLAYER_START_X;
						players[PLAYER_1]->y = PLAYER_START_Y;
						players[PLAYER_2]->y = PLAYER_START_Y;
					}
				}
			}

			/* Update menu. */
			drawMenu(selectedItem);
		}
		else
			inputPlayers(&ev, players, floor);

		/* Draw to screen. */
		tb_present();

		/* Sleep for 10 ms. */
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

void inputPlayers(struct tb_event *ev, Player *(*players), int floor)
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

int inputMenu(struct tb_event *ev)
{
	switch(ev->key)
	{
		case CONTROLS_MENU_DOWN: return MENU_DOWN;
		case CONTROLS_MENU_UP: return MENU_UP;
		case CONTROLS_MENU_SELECT: return MENU_SELECT;
		default: return MENU_NOTHING;
	}
}

bool input(struct tb_event *ev)
{
	if(ev->key == TOGGLE_MENU)
		return true;

	return false;
}

bool checkCollision(Player *player, Bullet *bullet)
{
	if(bullet->x >= player->x - (PLAYER_SIZE_X / 2.0f) && bullet->x <= player->x + (PLAYER_SIZE_X / 2.0f))
		if(bullet->y >= player->y - (PLAYER_SIZE_Y / 2.0f) && bullet->y <= player->y + (PLAYER_SIZE_Y / 2.0f))
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
		drawString("Player 1 ", TB_BLACK, playerStringLength, x, y, TB_WHITE);

	if(victory == PLAYER_2)
		drawString("Player 2 ", TB_BLACK, playerStringLength, x, y, TB_WHITE);

	drawString("won!", TB_BLACK, 4, x + playerStringLength, y, TB_WHITE);
}

void drawString(char *string, int color, int length, int x, int y, int backColor)
{
	for(int i = 0; i < length; i++)
		tb_change_cell(x + i, y, string[i], color, backColor);
}

int moveMenuCursor(int menuAction, int selectedItem)
{
	switch(menuAction)
	{
		case MENU_UP:
		{
			if(selectedItem == MENU_RESTART)
				selectedItem = MENU_EXIT;
			else
				selectedItem++;
			break;
		}

		case MENU_DOWN:
		{
			if(selectedItem == MENU_EXIT)
				selectedItem = MENU_RESTART;
			else
				selectedItem--;
			break;
		}
	}

	return selectedItem;
}

void drawMenu(int selectedItem)
{
	if(selectedItem == MENU_EXIT)
		drawString("Exit", TB_WHITE, 4, tb_width() / 2.0f - 2.0f, 15, TB_BLUE);
	else
		drawString("Exit", TB_WHITE, 4, tb_width() / 2.0f - 2.0f, 15, TB_BLACK);

	if(selectedItem == MENU_RESTART)
		drawString("Restart", TB_WHITE, 7, tb_width() / 2.0f - 7.0f / 2.0f, 17, TB_BLUE);
	else
		drawString("Restart", TB_WHITE, 7, tb_width() / 2.0f - 7.0f / 2.0f, 17, TB_BLACK);
}
