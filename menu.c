#include "headers/menu.h"

void Menu__init(Menu *this)
{
	this->open = false;
	this->shouldExit = false;
	this->action = -1;
	this->selectedItem = EXIT;
	this->selectedLevel = 0;
	this->y = 15;
}

void Menu__draw(Menu *this, void (*drawString)(char *string, int color, int length, int x, int y, int backColor))
{
	/* Draw a UI element in the selection color if the element is selected. Draw it with the normal color if it's not selected. */

	if(this->selectedItem == EXIT)
		drawString("Exit          ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y, ITEM_SELECTED);
	else
		drawString("Exit          ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y, ITEM);

	if(this->selectedItem == RESTART)
		drawString("Restart       ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y - 2, ITEM_SELECTED);
	else
		drawString("Restart       ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y - 2, ITEM);

	if(this->selectedItem == SWITCH_LEVEL)
		drawString("Switch Level  ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y - 4, ITEM_SELECTED);
	else
		drawString("Switch Level  ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, this->y - 4, ITEM);
}

void Menu__moveMenuCursor(Menu *this)
{
	switch(this->action)
	{
		case UP:
		{
			if(this->selectedItem == SELECT)
				/* Go to the first UI element. */
				this->selectedItem = EXIT;
			else
				this->selectedItem++;
			break;
		}

		case DOWN:
		{
			if(this->selectedItem == EXIT)
				/* Go to the last UI element. */
				this->selectedItem = SWITCH_LEVEL;
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
		case DOWN_KEY: this->action = DOWN; break;
		case UP_KEY: this->action = UP; break;
		case SELECT_KEY: this->action = SELECT; break;
		default: this->action = NOTHING; break;
	}
}

void Menu__update(Menu *this)
{
	Menu__moveMenuCursor(this);

	if(this->action == SELECT)
	{
		switch(this->selectedItem)
		{
			case EXIT: this->shouldExit = true; break;
			case RESTART:
			{
				this->shouldRestart = true;
				this->open = false;

				break;
			}
			case SWITCH_LEVEL:
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
