#ifndef BULLET_H_
#define BULLET_H_

#include <stdlib.h>
#include <stdbool.h>

#include "termbox.h"
#include "constants.h"

#define BULLET_SPEED 2.0f

typedef struct Bullet Bullet;

void Bullet__init(Bullet *this, char symbol, int color);

/* Allocate memory for the bullet and let the function pointers point to the correct functions. */
Bullet* Bullet__create(char symbol, int color);

/* Create a new bullet at position x, y and set it's x velocity to BULLET_SPEED * direction. */
void Bullet__shoot(Bullet *this, float x, float y, int direction);

/* Update the bullet's position and speed. */
void Bullet__update(Bullet *this);

void Bullet__draw(Bullet *this);
void Bullet__destroy(Bullet *this);

struct Bullet
{
	/* If !exists, allow the player to shoot a new bullet. */
	bool exists;

	float x, vx, ax;
	float y, vy, ay;

	char symbol;
	int color;

	void (*destroy)(Bullet *this);
	void (*init)(Bullet *this, char symbol, int color);
	void (*shoot)(Bullet *this, float x, float y, int direction);
	void (*update)(Bullet *this);
	void (*draw)(Bullet *this);
};

#endif
