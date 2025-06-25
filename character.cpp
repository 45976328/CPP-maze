#include "character.h"
#include <ncurses.h>
#include <random>

character::character(char sym){
	symbol = sym;
	isCaged=false;
	hasKey=false;
	onLadder=false;
	released = false;
	HeroesMet = false;
}
void character::randomPosition(char** map, const int rows, const int cols){
	do{
		x = 7 + (rand() % (cols - 14) ); // cols - 14
		y = 7 + (rand() % (rows - 14) ); // rows -14
	}while(map[y][x] != ' ');	
}
