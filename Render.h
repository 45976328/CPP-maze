#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>
#include "maze.h"
#include "character.h"
#include "HeroG.h"
#include "HeroS.h"
#include "Item.h"

class Render {
    	WINDOW* win;
    	maze* m;
    	HeroG* g;
	HeroS* s;
    	Item* k;
	Item* l;
	Item* t;
	public:
	    Render(WINDOW* w, maze* maze, HeroG* greg, HeroS* S, Item* key, Item* ladder, Item* trap);
	    void runLoop(int maxSeconds, const int rows, const int cols);
};

#endif

