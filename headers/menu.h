#ifndef MENU_H_
#define MENU_H_

#define MENU_NOTHING -1
#define MENU_DOWN 0
#define MENU_UP 1
#define MENU_SELECT 2
#define MENU_EXIT 3
#define MENU_RESTART 4
#define MENU_SELECT_LEVEL 5

#include <stdbool.h>
#include "termbox.h"

typedef struct Menu Menu;

void Menu__draw(void (*drawString)(char *string, int color, int length, int x, int y, int backColor), int selectedItem, int selectedLevel);
int Menu__moveMenuCursor(int menuAction, int selectedItem, int selectedLevel);
void Menu__init(Menu *menu);

struct Menu
{
	bool open;
	int action;
	int selectedItem;
};

#endif
