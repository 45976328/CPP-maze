#ifndef HEROG_H
#define HEROG_H
#include "character.h"
#include <stack>

using namespace std;
class HeroG : public character{
	bool** visited;
	int rows;
	int cols;
	stack<pair<int, int>> dfs_stack;
	public:
		HeroG(const int, const int); 
		~HeroG();
		void move(char** map);
		void moveToL(int, int);
};
#endif
