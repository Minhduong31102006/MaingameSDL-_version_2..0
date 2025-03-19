#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED

#include "myLib.h"
#include "snake.h"

void tao_qua (pair <int,int> &qua, vector <pair<int,int>> v);
bool kt_ran_de_qua (pair <int,int> qua, vector <pair<int,int>> v);
void ve_qua (pair <int,int> qua,SDL_Renderer *renderer,const char *path);
bool kt_ran_an_qua( pair<int,int>qua, int x0, int y0);


#endif // FRUIT_H_INCLUDED
