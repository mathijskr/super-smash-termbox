#include "headers/menu.h"

void Menu__init(Menu *this)
{
	this->open = false;
	this->shouldExit = false;
	this->action = -1;
	this->selectedItem = MENU_EXIT;
	this->selectedLevel = 0;
	this->y = 15;
}

void Menu__draw(Menu *this, void (*drawString)(char *string, int color, int length, int x, int y, int backColor))
{
	/* Draw a UI element in the selection color if the element is selected. Draw it with the normal color if it's not selected. */

	if(this->selectedItem == MENU_EXIT)
		drawString("Exit          ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y, MENU_ITEM_COLOR_SELECTED);
	else
		drawString("Exit          ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y, MENU_ITEM_COLOR);

	if(this->selectedItem == MENU_RESTART)
		drawString("Restart       ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y - 2, MENU_ITEM_COLOR_SELECTED);
	else
		drawString("Restart       ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y - 2, MENU_ITEM_COLOR);

	if(this->selectedItem == MENU_SELECT_LEVEL)
		drawString("Switch Level  ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y - 4, MENU_ITEM_COLOR_SELECTED);
	else
		drawString("Switch Level  ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y - 4, MENU_ITEM_COLOR);
}

void Menu__moveMenuCursor(Menu *this)
{
	switch(this->action)
	{
		case MENU_UP:
		{
			if(this->selectedItem == MENU_SELECT_LEVEL)
				/* Go to the first UI element. */
				this->selectedItem = MENU_EXIT;
			else
				this->selectedItem++;
			break;
		}

		case MENU_DOWN:
		{
			if(this->selectedItem == MENU_EXIT)
				/* Go to the last UI element. */
				this->selectedItem = MENU_SELECT_LEVEL;
			else
				this->selectedItem--;
			break;
		}
	}
}

void Menu__input(Menu *this, struct tb_event *ev)
{
	switch(ev->key)
	{
		case CONTROLS_MENU_DOWN: this->action = MENU_DOWN; break;
		case CONTROLS_MENU_UP: this->action = MENU_UP; break;
		case CONTROLS_MENU_SELECT: this->action = MENU_SELECT; break;
		default: this->action = MENU_NOTHING; break;
	}
}

void Menu__update(Menu *this)
{
	Menu__moveMenuCursor(this);

	if(this->action == MENU_SELECT)
	{
		switch(this->selectedItem)
		{
			case MENU_EXIT: this->shouldExit = true; break;
			case MENU_RESTART:
			{
				this->shouldRestart = true;
				this->open = false;

				break;
			}
			case MENU_SELECT_LEVEL:
			{
				if(this->selectedLevel == 0)
					this->selectedLevel = 1;
				else
					this->selectedLevel = 0;

				this->shouldRestart = true;
				this->open = false;

				break;
			}
		}
	}

}
