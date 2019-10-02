#ifndef MENU_H_
#define MENU_H_

#define TOGGLE_MENU TB_KEY_ESC
#define CONTROLS_MENU_DOWN TB_KEY_ARROW_DOWN
#define CONTROLS_MENU_UP TB_KEY_ARROW_UP
#define CONTROLS_MENU_SELECT TB_KEY_ENTER

#define MENU_NOTHING -1
#define MENU_DOWN 0
#define MENU_UP 1
#define MENU_SELECT 2
#define MENU_EXIT 3
#define MENU_RESTART 4
#define MENU_SELECT_LEVEL 5

#define MENU_ITEM_COLOR TB_BLACK
#define MENU_ITEM_COLOR_SELECTED TB_BLUE

#include <stdbool.h>
#include "termbox.h"

typedef struct Menu Menu;

/* Draw all UI elements from the menu using a draw method provided by drawString. */
void Menu__draw(Menu *this, void (*drawString)(char *string, int color, int length, int x, int y, int backColor));

/* Move the selection up or down. */
void Menu__moveMenuCursor(Menu *this);

/* Initialize the menu with default values. */
void Menu__init(Menu *this);

/* Handle input from a player using the menu. */
void Menu__input(Menu *this, struct tb_event *ev);

/* Update the menu depending on the input processed by de Menu__input method. */
void Menu__update(Menu *this);

struct Menu
{
	bool open;
	bool shouldExit;
	bool shouldRestart;
	int action;
	int selectedItem;
	int selectedLevel;
	int y;
};

#endif
