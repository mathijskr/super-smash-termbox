#include "headers/stageobject.h"

/* Initialize player. */
void Stageobject__init(Stageobject *this, int x_l, int x_r, int y_d, int y_u, int color)
{
	this->x_l = x_l;
	this->x_r = x_r;

	this->y_d = y_d;
	this->y_u = y_u;

	this->color = color;
}

/* Construct a new stageobject. */
Stageobject* Stageobject__create(int x_l, int x_r, int y_d, int y_u, int color)
{
	/* Allocate memory. */
	struct Stageobject* result = (struct Stageobject*) malloc(sizeof(struct Stageobject));

	/* Set function pointers. */
	result->init = Stageobject__init;
	result->draw = Stageobject__draw;
	result->destroy = Stageobject__destroy;

	/* Initialize a new stageobject. */
	result->init(result, x_l, x_r, y_d, y_u, color);

	return result;
}

void drawRectangle(int x_l, int x_r, int y_d, int y_u, int backColor, char symbol, int symbolColor)
{
	for(int y = y_d; y < y_u; y++)
		for(int x = x_l; x < x_r; x++)
			tb_change_cell(x, y, symbol, symbolColor, backColor);
}

void Stageobject__draw(Stageobject *this)
{
	drawRectangle(this->x_l, this->x_r, this->y_d, this->y_u, this->color, ' ', this->color);
}

void Stageobject__destroy(Stageobject *this)
{
	if(this)
		free(this);
}
