#include <stdlib.h>
#include "termbox.h"

typedef struct Player Player;

void Player__init(Player* this, int x, int y, char symbol);
Player* Player__create(int x, int y, char symbol);
void Player__input(Player* this, int input);
void Player__destroy(Player* this);

struct Player
{
	int x;
	int y;
	char symbol;

	void (*init)(Player* this, int x, int y, char symbol);
	void (*input)(Player* this, int input);
	void (*destroy)(Player* this);
};
