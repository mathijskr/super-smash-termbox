#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "termbox.h"

#include "player.h"
#include "constants.h"
#include "bullet.h"
#include "platform.h"
#include "levels.h"

#define NUMBER_OF_PLAYERS 2

#define BACKGROUND_SYMBOL ' '
#define GROUND_SYMBOL '-'

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

/* Draw a rectangle of size widht, heigth with that has color color and fill it with symbol symbol. */
void drawRectangle(int width, int maxWidth, int height, int maxHeight, int backColor, char symbol, int symbolColor);

/* Process the player's input in the menu UI, can return up, down or select,
 * indicating wheter the player wants to move up or down in the menu, or wants to execute the higlighted action. */
int inputMenu(struct tb_event *ev);

/* Process the player's input in the game. */
void inputPlayers(struct tb_event *ev, Player *(*players), int floor);

/* Checks if the key bound to opening the menu is pressed. */
bool input(struct tb_event *ev);

/* Check if a bullet is inside the hitbox of a player. */
bool checkCollision(Player *player, Bullet *bullet);

/* Draw characters from a char array of length length at position x, y on the screen.
 * Color specifies the text color, backColor specifies the color of the background behind the characters*/
void drawString(char *string, int color, int length, int x, int y, int backColor);

/* Move the cursor in the menu up or down so that a different action is selected. */
int moveMenuCursor(int menuAction, int selectedItem, int selectedLevel);

/* Draw a UI for the menu. */
void drawMenu(int selectedItem, int selectedLevel);

/* Draw a victory message for the corresponding player that won the game. */
void drawVictory(int victory);

void restart(int *victory, Player *(*players)[NUMBER_OF_PLAYERS], bool *menuOpen);
