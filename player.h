#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdlib.h>
#include "termbox.h"

#include "constants.h"

typedef struct Player Player;

void Player__init(struct Player* this, int x, int y, char symbol, int color);
Player* Player__create(int x, int y, char symbol, int color);
void Player__physics(Player *this, int floor);
void Player__input(Player* this, int input, int floor);
void Player__draw(Player *player);
void Player__destroy(Player* this);

static const char Player__graphics[3][3] =
{
	' ', '0', ' ',
	'-', '|', '-',
	'/', ' ', '\\'
};

struct Player
{
	/* X position, speed, acceleration. */
	float x;
	float vx;
	float ax;

	/* Y position, speed, acceleration. */
	float y;
	float vy;
	float ay;

	char symbol;
	float jumpPower;

	int color;

	void (*init)(Player* this, int x, int y, char symbol, int color);
	void (*input)(Player* this, int input, int floor);
	void (*physics)(Player *this, int floor);
	void (*draw)(Player *this);
	void (*destroy)(Player* this);
};

#endif
