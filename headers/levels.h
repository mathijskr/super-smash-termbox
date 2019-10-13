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
	5, /* Numer of platforms. */
	{
		/*X1  X2  Y1  Y2  Color		*/
		{ 10, 30, 45, 47, TB_YELLOW},	/* Platform 1 */
		{ 70, 90, 45, 47, TB_WHITE},	/* Platform 2 ...*/
		{ 35, 65, 35, 37, TB_BLACK},
		{ 10, 30, 25, 27, TB_RED},
		{ 70, 90, 25, 27, TB_BLUE},
	}
};

Level level2 =
{
	5, /* Numer of platforms. */
	{
		/*X1  X2  Y1  Y2  Color		*/
		{ 10, 30, 45, 47, TB_YELLOW},	/* Platform 1 */
		{ 70, 90, 45, 47, TB_WHITE},    /* Platform 2 ...*/
		{ 35, 45, 35, 37, TB_RED},
		{ 55, 65, 35, 37, TB_BLUE},
		{ 45, 55, 25, 27, TB_BLACK},
	}
};

#endif
