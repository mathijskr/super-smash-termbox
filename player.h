#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdlib.h>
#include "termbox.h"

#include "constants.h"
#include "bullet.h"

#define PLAYER_2_LEFT TB_KEY_ARROW_LEFT
#define PLAYER_2_RIGHT TB_KEY_ARROW_RIGHT
#define PLAYER_2_JUMP TB_KEY_SPACE
#define PLAYER_2_SHOOT TB_KEY_ENTER

#define PLAYER_1_LEFT 'a'
#define PLAYER_1_RIGHT 'd'
#define PLAYER_1_JUMP 'q'
#define PLAYER_1_SHOOT 'e'

#define JUMP_POWER 2.0f

typedef struct Player Player;

void Player__init(struct Player* this, int x, int y, char symbol, int color);
Player* Player__create(int x, int y, char symbol, int color);
void Player__physics(Player *this, int floor);
void Player__moveLeft(Player *this);
void Player__moveRight(Player *this);
void Player__jump(Player *this, int floor);
void Player__draw(Player *player);
void Player__shoot(Player *this);
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
	float x, vx, ax;

	/* Y position, speed, acceleration. */
	float y, vy, ay;

	int direction;

	char symbol;

	int JUMP;
	int LEFT;
	int RIGHT;

	int color;

	Bullet *bullet;

	void (*init)(Player* this, int x, int y, char symbol, int color);
	void (*physics)(Player *this, int floor);
	void (*moveLeft)(Player *this);
	void (*moveRight)(Player *this);
	void (*jump)(Player *this, int floor);
	void (*shoot)(Player *this);
	void (*draw)(Player *this);
	void (*destroy)(Player* this);
};

#endif
