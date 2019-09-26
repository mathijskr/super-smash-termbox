#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdlib.h>
#include "termbox.h"

#include "constants.h"

typedef struct Player Player;

void Player__init(Player* this, int x, int y, char symbol);
Player* Player__create(int x, int y, char symbol);
void Player__input(Player* this, int input, int floor);
void Player__physics(Player *this, int floor);
void Player__destroy(Player* this);

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

	void (*init)(Player* this, int x, int y, char symbol);
	void (*input)(Player* this, int input, int floor);
	void (*physics)(Player *this, int floor);
	void (*destroy)(Player* this);
};

#endif
