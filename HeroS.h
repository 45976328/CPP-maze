#ifndef HEROS_H
#define HEROS_H
#include "character.h"
#include <stack>
using namespace std;

class HeroS : public character{
	bool** visited;
        int rows;
        int cols;
        stack<pair<int, int>> dfs_stack;
        public:
                HeroS(const int, const int);
                ~HeroS();
                void move(char** map);
		void moveToL(int, int);
		
};
#endif
