#ifndef MAZE_H
#define MAZE_H
#include <ncurses.h>

class maze{
	char** map;
	int rows;
	int cols;
	public:
		maze(char* filename, const int rows, const int cols);
		~maze();
		void clearWalls(WINDOW* win);
		char **GetMap(){return map;};
};
#endif
