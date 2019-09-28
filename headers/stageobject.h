#ifndef STAGEOBJECT_H_
#define STAGEOBJECT_H_

#include <stdlib.h>
#include "termbox.h"

typedef struct Stageobject Stageobject;

void drawRectangle(int x_l, int x_r, int y_d, int y_u, int backColor, char symbol, int symbolColor);
void Stageobject__init(Stageobject *this, int x_l, int x_r, int y_d, int y_u, int color);
Stageobject* Stageobject__create(int x_l, int x_r, int y_d, int y_u, int color);
void Stageobject__draw(Stageobject *this);
void Stageobject__destroy(Stageobject *this);

struct Stageobject
{
	/* X left and right. */
	int x_l, x_r;

	/* Y up and down. */
	int y_d, y_u;

	int color;

	void (*init)(Stageobject* this, int x_l, int x_r, int y_d, int y_u, int color);
	void (*draw)(Stageobject *this);
	void (*destroy)(Stageobject* this);
};

#endif
