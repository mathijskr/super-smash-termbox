#include "player.h"

/* Initialize player. */
void Player__init(struct Player* this, int x, int y, char symbol)
{
	this->x = x;
	this->y = y;

	this->vx = 0.0f;
	this->vy = 0.0f;

	this->ax = 0.0f;
	this->ay = 0.0f;

	this->symbol = symbol;

	this->jumpPower = 3.0f;
}

/* Construct a new player. */
Player* Player__create(int x, int y, char symbol)
{
	/* Allocate memory. */
	struct Player* result = (struct Player*) malloc(sizeof(struct Player));

	/* Set function pointers. */
	result->init = Player__init;
	result->input = Player__input;
	result->physics = Player__physics;
	result->destroy = Player__destroy;

	/* Initialize a new player. */
	result->init(result, x, y, symbol);

	return result;
}

void Player__physics(Player *this, int floor)
{
	/* Let player fall down. */
	if(this->y < floor)
		this->ay = GRAVITY;

	/* Increase or decrease speed. */
	this->vx += this->ax;
	this->vy += this->ay;

	/* Increase or decrease position. */
	this->x += this->vx;
	this->y += this->vy;

	if(this->y >= floor)
	{
		this->vy = 0.0f;
		this->ay = 0.0f;

		this->y = floor;
	}
}

/* Process player input. */
void Player__input(Player *this, int input, int floor)
{
	if(input == TB_KEY_ARROW_LEFT)
		this->x--;

	if(input == TB_KEY_ARROW_RIGHT)
		this->x++;

	if(input == TB_KEY_SPACE && this->y >= floor - 0.001f)
		this->vy -= this->jumpPower;
}

/* Destructor. */
void Player__destroy(Player* this)
{
	if(this)
		free(this);
}
