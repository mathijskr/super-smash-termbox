#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdlib.h>
#include "termbox.h"

#include "constants.h"
#include "bullet.h"

#define PLAYER_1 0
#define PLAYER_2 1

#define PLAYER_1_LEFT TB_KEY_ARROW_LEFT
#define PLAYER_1_RIGHT TB_KEY_ARROW_RIGHT
#define PLAYER_1_JUMP TB_KEY_SPACE
#define PLAYER_1_SHOOT TB_KEY_ENTER

#define PLAYER_2_LEFT 'a'
#define PLAYER_2_RIGHT 'd'
#define PLAYER_2_JUMP 'q'
#define PLAYER_2_SHOOT 'e'

#define JUMP_POWER 0.5f

#define PLAYER_SIZE_X 3.0f
#define PLAYER_SIZE_Y 6.0f

#define PLAYER_START_X 10
#define PLAYER_START_Y 10

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

static const char Player__graphics_dead[3][3] =
{
	'\\', ' ', '/',
	' ', 'X', ' ',
	'/', ' ', '\\'
};

struct Player
{
	bool dead;

	/* X position, speed, acceleration. */
	float x, vx, ax;

	/* Y position, speed, acceleration. */
	float y, vy, ay;

	float size_x, size_y;

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
