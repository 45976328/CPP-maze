#ifndef ITEM_H
#define ITEM_H
#include <random>
class Item{
        int x;
        int y;
        public:
        	char symbol;
		Item(char s){symbol=s;}
                void randomPosition(char** map, const int rows, const int cols){
                        do{
                                x = 7 + (rand() % (cols - 14) ); // cols
                                y = 7 + (rand() % (rows - 14) ); // rows
                        }while(map[y][x] != ' ');
                }

                int getX()const{return x;}
                int getY()const{return y;}
};
#endif

