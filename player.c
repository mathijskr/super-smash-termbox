#include "player.h"

/* Initialize player. */
void Player__init(struct Player* this, int x, int y, char symbol)
{
	this->x = x;
	this->y = y;
	this->symbol = symbol;
	this->init = &Player__init;
	this->input = &Player__input;
}

/* Construct a new player. */
Player* Player__create(int x, int y, char symbol)
{
	/* Allocate memory. */
	struct Player* result = (struct Player*) malloc(sizeof(struct Player));

	/* Set function pointers. */
	result->init = Player__init;
	result->input = Player__input;
	result->destroy = Player__destroy;

	/* Initialize a new player. */
	result->init(result, x, y, symbol);

	return result;
}

/* Process player input. */
void Player__input(Player *this, int input)
{
	if(input == TB_KEY_ARROW_LEFT)
		this->x--;

	if(input == TB_KEY_ARROW_RIGHT)
		this->x++;

	if(input == TB_KEY_ARROW_DOWN)
		this->y++;

	if(input == TB_KEY_ARROW_UP)
		this->y--;
}

/* Destructor. */
void Player__destroy(Player* this)
{
	if(this)
		free(this);
}
