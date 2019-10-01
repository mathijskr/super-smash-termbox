#include "headers/platform.h"

void drawRectangle(int x_l, int x_r, int y_d, int y_u, int backColor, char symbol, int symbolColor)
{
	for(int y = y_d; y < y_u; y++)
		for(int x = x_l; x < x_r; x++)
			tb_change_cell(x, y, symbol, symbolColor, backColor);
}

void Platform__draw(Platform *this)
{
	drawRectangle(this->x_l, this->x_r, this->y_d, this->y_u, this->color, ' ', this->color);
}
