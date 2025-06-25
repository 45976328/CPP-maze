#ifndef CHARACTER_H
#define CHARACTER_H
#include <ncurses.h>

class character{
	protected:
		int x;
		int y;
	public:
		bool isCaged;
		bool hasKey;
		bool onLadder;
		bool released;
		bool HeroesMet;
		char symbol;
		character(char);
		void randomPosition(char**, const int, const int);
		int getX() const {return x;};
		int getY() const {return y;};
};
#endif
