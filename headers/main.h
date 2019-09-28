#include <stdio.h>
#include <string.h>
#include <time.h>

#include "termbox.h"

#include "player.h"
#include "constants.h"
#include "bullet.h"

#define NUMBER_OF_PLAYERS 2
#define BACKGROUND_SYMBOL ' '
#define GROUND_SYMBOL '-'

/* Draw a rectangle of size widht, heigth with that has color color and fill it with symbol symbol. */
void drawRectangle(int width, int maxWidth, int height, int maxHeight, int backColor, char symbol, int symbolColor);

/* Get input from tb_event, and send corresponding action to the players
 * if the players are allowed to perform an action. */
void input(struct tb_event *ev, Player *(*players), int floor);

/* Check if a bullet is inside the hitbox of a player. */
bool checkCollision(Player *player, Bullet *bullet);

/* Draw characters from a char array of length length at position x, y on the screen. */
void drawString(char *string, int length, int x, int y);

/* Draw a victory message for the corresponding player that won the game. */
void drawVictory(int victory);
