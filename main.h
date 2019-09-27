#include <stdio.h>
#include <string.h>

#include "termbox.h"

#include "player.h"
#include "constants.h"

void drawBackground(int width, int heigth, int color);
void drawGround(int width, int height, int maxHeight, char symbol, int color);
void input(struct tb_event *ev, Player *(*players), int floor);
