#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <stdlib.h>
#include "termbox.h"

typedef struct Platform Platform;

void drawRectangle(int x_l, int x_r, int y_d, int y_u, int backColor, char symbol, int symbolColor);
void Platform__draw(Platform *this);

struct Platform
{
	/* X left and right. */
	int x_l, x_r;

	/* Y up and down. */
	int y_d, y_u;

	int color;
};

#endif
