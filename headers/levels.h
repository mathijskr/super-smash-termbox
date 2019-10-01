#ifndef LEVELS_H_
#define LEVELS_H_

#include "platform.h"
#include "termbox.h"

typedef struct Level Level;

struct Level
{
	int number_of_platforms;

	Platform platforms[];
};

Level level1 =
{
	5,
	{
		{ 10, 30, 45, 47, TB_YELLOW},
		{ 70, 90, 45, 47, TB_WHITE},
		{ 35, 65, 35, 37, TB_BLACK},
		{ 10, 30, 25, 27, TB_RED},
		{ 70, 90, 25, 27, TB_BLUE},
	}
};

#endif
