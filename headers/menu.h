#ifndef MENU_H_
#define MENU_H_

#include <stdbool.h>
#include "termbox.h"

enum CONTROLS { TOGGLE_MENU = TB_KEY_ESC, DOWN_KEY = TB_KEY_ARROW_DOWN,
		UP_KEY = TB_KEY_ARROW_UP, SELECT_KEY = TB_KEY_ENTER };

enum MENU_ITEM { EXIT, RESTART, SWITCH_LEVEL };
enum MENU_ACTION { DOWN, UP, SELECT, NOTHING };

enum COLOR { ITEM = TB_BLACK, ITEM_SELECTED = TB_BLUE };

typedef struct Menu Menu;

/* Draw all UI elements from the menu using a draw method provided by drawString. */
void Menu__draw(Menu *this, void (*drawString)(char *string, int color,
		int length, int x, int y, int backColor));

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
