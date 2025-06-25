#include <iostream>
#include <ncurses.h>
#include "maze.h"
#include "HeroG.h"
#include "HeroS.h"
#include "Render.h"
#include "Item.h"
using namespace std;

int main(int argc, char* argv[]) {
	const int cols = 31;
	const int rows = 21;
	if (argc < 2) {
        	cout << "Χρήση: ./maze_program <όνομα αρχείου>\n";
	        return 1;
	}

	// Εκκίνηση ncurses
	initscr();
	noecho();
	curs_set(FALSE);

	// Τυχαίος seed
	srand(time(NULL));
	
	// Φόρτωση λαβυρίνθου
	maze* m = new maze(argv[1], rows, cols);
	
	// Δημιουργία αντικειμένων
	HeroG* g = new HeroG(rows,cols);
	g->randomPosition(m->GetMap(), rows, cols);
	
	HeroS* s = new HeroS(rows,cols);
	s->randomPosition(m->GetMap(), rows, cols);

	Item* key = new Item('K');
	key->randomPosition(m->GetMap(), rows, cols);
	
	Item* ladder = new Item('L');
	ladder->randomPosition(m->GetMap(), rows, cols);
	
	Item* trap = new Item('T');
	trap->randomPosition(m->GetMap(), rows, cols);

	// Εκκίνηση Render loop
	Render* r = new Render(stdscr, m, g, s, key, ladder, trap);
	r->runLoop(1000, rows, cols);
	
	// Καθάρισμα
	endwin();
	delete m;
	delete g;
	delete s;
	delete key;
	delete ladder;
	delete trap;
    	delete r;

    	return 0;
}

