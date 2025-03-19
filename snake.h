#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "myLib.h"
#include "fruit.h"


void khoi_tao_ran(vector <pair<int,int>> &v, int x0, int y0);
void ve_ran(vector<pair<int, int>> v, SDL_Renderer *renderer, const char *path_head, const char *path_body, const char *path_tail, const char *path_corner, Direction dir);
void xu_li_ran(pair<int,int> &qua, vector <pair<int,int>> &v, int x0, int y0);
bool kt_ran_cham_duoi(vector <pair<int,int>> v);



#endif // SNAKE_H_INCLUDED
