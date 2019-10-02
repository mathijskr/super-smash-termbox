#include "headers/menu.h"

void Menu__draw(void (*drawString)(char *string, int color, int length, int x, int y, int backColor), int selectedItem, int selectedLevel)
{
	if(selectedItem == MENU_EXIT)
		drawString("Exit          ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, 19, TB_BLUE);
	else
		drawString("Exit          ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, 19, TB_BLACK);

	if(selectedItem == MENU_RESTART)
		drawString("Restart       ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, 17, TB_BLUE);
	else
		drawString("Restart       ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, 17, TB_BLACK);

	if(selectedItem == MENU_SELECT_LEVEL)
		drawString("Switch Level  ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, 15, TB_BLUE);
	else
		drawString("Switch Level  ", TB_WHITE, 14, tb_width() / 2.0f - 7.0f, 15, TB_BLACK);
}

int Menu__moveMenuCursor(int menuAction, int selectedItem, int selectedLevel)
{
	switch(menuAction)
	{
		case MENU_UP:
		{
			if(selectedItem == MENU_SELECT_LEVEL)
				selectedItem = MENU_EXIT;
			else
				selectedItem++;
			break;
		}

		case MENU_DOWN:
		{
			if(selectedItem == MENU_EXIT)
				selectedItem = MENU_SELECT_LEVEL;
			else
				selectedItem--;
			break;
		}
	}

	return selectedItem;
}

void Menu__init(Menu *menu)
{
	menu->open = false;
	menu->action = -1;
	menu->selectedItem = MENU_EXIT;
}
