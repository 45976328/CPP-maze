#include "Render.h"
#include <unistd.h>
#include <ncurses.h>

Render::Render(WINDOW* w, maze* maze, HeroG* greg, HeroS* S, Item* key, Item* ladder, Item* trap) {
    	win = w;
    	m = maze;
    	g = greg;
	s = S;
    	k = key;
    	l = ladder;
	t = trap;
}

void Render::runLoop(int maxSeconds, const int rows, const int cols) {
	nodelay(win, TRUE); // non-blocking getch()

    	for (int z = 0; z < maxSeconds; ++z) {
       		werase(win); // καθάρισε την οθόνη
        	
		// Εμφάνισε τον λαβύρινθο
        	char** map = m->GetMap();
        	for (int i = 0; i < rows; i++) {
            		for (int j = 0; j < cols; j++) {
                		mvwaddch(win, i, j, map[i][j]);
            		}
        	}


		if (g->getX() == s->getX() && g->getY() == s->getY() ) {

			if(!(s->isCaged || g->isCaged) || s->released || g->released){
				mvwprintw(win, rows+4, 2, "MEETING DETECTED");
				wrefresh(win);
			    	m->clearWalls(win);
				s->HeroesMet = true;
				g->HeroesMet = true;
			}
		}



		if (g->getY() == t->getY() && g->getX() == t->getX() && !g->released){
			if(!s->isCaged){
				g->isCaged = true;
				t->symbol = 'C';
			}else if ( g->hasKey){
				g->isCaged = false;
				s->isCaged = false;
				g->released = true;
				s->released = true; //it takes one round to release
			}else{ g->move(map);}
		}else if(g->getY() == k->getY() && g->getX() == k->getX() && !s->hasKey){
				g->hasKey = true;
				g->move(map);
		}else if (g->getY() == l->getY() && g->getX() == l->getX()){
			g->onLadder = true;
			g->move(map);
		}else{
			if(g->HeroesMet || s->HeroesMet){
				g->moveToL(l->getY(), l->getX());  // Κίνηση του G προς τη σκάλα
		}else{	 g->move(map);} 
		}
		

		if(s->getY() == t->getY() && s->getX() == t->getX() && !s->released){
			if( !g->isCaged){
				s->isCaged = true;
				t->symbol = 'C';
			}else if( s->hasKey){
				s->isCaged = false;
				g->isCaged = false;
				g->released = true;
				s->released = true; //it takes one round to release
			}else{s->move(map);}
		}else if (s->getY() == k->getY() && s->getX() == k->getX() && !g->hasKey){
			s->hasKey = true;
			s->move(map);
		}else if (s->getY() == l->getY() && s->getX() == l->getX()){
			s->onLadder = true;		
			s->move(map);
		}else{ 
			if (s->HeroesMet || g->HeroesMet){
				s->moveToL(l->getY(), l->getX());  // Κίνηση του G προς τη σκάλα
			}else{	s->move(map);}
		}	
	        // Εμφάνισε αντικείμενα
	        mvwaddch(win, g->getY(), g->getX(), g->symbol);
	        mvwaddch(win, s->getY(), s->getX(), s->symbol);
		if( !g->hasKey && !s->hasKey){
		        mvwaddch(win, k->getY(), k->getX(), k->symbol); } // if key is taken by a hero dont show it on the map
	        mvwaddch(win, l->getY(), l->getX(), l->symbol);
		if( !s->released || !g->released){
			mvwaddch(win, t->getY(), t->getX(), t->symbol); //if the a hero was released there are no more cages
		}


        	// Εμφάνισε χρόνο
        	mvwprintw(win, rows+1, 2, " Time: %d / %d", z, maxSeconds);
	       
 		mvwprintw(win, rows+2, 2, "G: (%d,%d) Key:%d Caged:%d Released:%d Ladder:%d",g->getX(), g->getY(), g->hasKey, g->isCaged, g->released, g->onLadder);

		mvwprintw(win, rows+3, 2, "S: (%d,%d) Key:%d Caged:%d Released:%d Ladder:%d",s->getX(), s->getY(), s->hasKey, s->isCaged, s->released, s->onLadder);

		if (s->onLadder && g->onLadder) {
    			mvwprintw(win, rows + 6, 2, "Happy End!");
    			wrefresh(win);			
		}

		wrefresh(win); // εμφάνισε τα πάντα
	
	        // Τερματισμός αν πατηθεί πλήκτρο
	        int ch = wgetch(win);
	        if (ch != ERR) break;
	
	        usleep(300000);
	    }
}

