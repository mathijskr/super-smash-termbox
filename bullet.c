#include "bullet.h"

void Bullet__init(Bullet *this, char symbol, int color)
{
	this->exists = false;

	this->x = 0.0f;
	this->vx = 0.0f;
	this->ay = 0.0f;
	this->y = 0.0f;
	this->vy = 0.0f;
	this->ay = 0.0f;
	this->symbol = symbol;
	this->color = color;
}
void Bullet__shoot(Bullet *this, float x, float y, int direction)
{
	this->exists = true;
	this->x = x;
	this->y = y;

	this->vx = BULLET_SPEED * direction;
	this->ay = GRAVITY;
}

/* Construct a new bullet. */
Bullet* Bullet__create(char symbol, int color)
{
	/* Allocate memory. */
	struct Bullet* result = (struct Bullet*) malloc(sizeof(struct Bullet));

	/* Set function pointers. */
	result->init = Bullet__init;
	result->draw = Bullet__draw;
	result->update = Bullet__update;
	result->shoot = Bullet__shoot;
	result->destroy = Bullet__destroy;

	/* Initialize a new bullet. */
	result->init(result, symbol, color);

	return result;
}

void Bullet__update(Bullet *this)
{
	this->x += this->vx;
	this->y += this->vy;

	this->vx += this->ax;
	this->vy += this->ay;

	/* Bullet out of bounds. */
	if(this->x > tb_width() || this->x < -tb_width() || this->y > tb_height())
	{
		this->exists = false;
		this->vx = 0;
		this->vy = 0;
		this->ax = 0;
		this->ay = 0;
	}
}

void Bullet__draw(Bullet *this)
{
	tb_change_cell(this->x, this->y, this->symbol, this->color, BACKGROUND_COLOR);
}


void Bullet__destroy(Bullet *this)
{
	if(this)
		free(this);
}
