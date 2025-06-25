#include <fstream>
#include <iostream>
#include <string>
#include <ncurses.h>
#include "maze.h"
#include <unistd.h>
using namespace std;

maze::maze (char *filename, const int rows, const int cols){
	this->rows = rows;
	this->cols = cols;

	map = new char*[rows];
	for(int i=0; i< rows; i++){
		map[i] = new char[cols];
	}
	ifstream file (filename);
	if (!file) {
      		cerr << "Σφάλμα κατά το άνοιγμα του αρχείου: " << filename << endl;
        	exit(1);
    	}

	string line;
	int r=0;
	while (getline(file,line) && r < rows ){
		for (int c = 0; c < cols && c < line.size(); c++) {
            		map[r][c] = line[c];
        	}
        	r++;
	}
	file.close();
	
}
maze::~maze() {
    for (int i = 0; i < rows; i++) {
        delete[] map[i];
    }
    delete[] map;
}

void maze::clearWalls(WINDOW* win) {
    for (int i = 1; i < rows - 1; ++i) {         // αγνοεί την 1η και τελευταία γραμμή
        for (int j = 1; j < cols - 1; ++j) {     // αγνοεί την 1η και τελευταία στήλη
            if (map[i][j] == '*') {
                map[i][j] = ' ';                // αφαίρεση τοίχου
                mvwaddch(win, i, j, ' ');       // εμφάνιση στην οθόνη
                wrefresh(win);                  // ανανέωση
                usleep(10000);                   // καθυστέρηση
            }
        }
    }

    mvwprintw(win, rows+5, 2, "WALLS CLEARED");
    wrefresh(win);
}

