#include "fruit.h"

void tao_qua (pair <int,int> &qua, vector <pair<int,int>> v)
{
    do
    {
        qua.first = rand()%(SCREEN_WIDTH/CELL_SIZE-1);
        qua.second = rand()%(SCREEN_HEIGHT/CELL_SIZE-1);
    }while(kt_ran_de_qua(qua,v));
}
bool kt_ran_de_qua (pair <int,int> qua, vector <pair<int,int>> v)
{
    for (int i=0 ;i< SL ;i++)
    {
        if (qua.first == v[i].first && qua.second == v[i].second)
        {
            return true;
        }
    }
    return false;
}
void ve_qua ( pair <int,int> qua,SDL_Renderer *renderer,const char *path)
{
    SDL_Texture *texture;
    texture = loadTexture (path,renderer);
    SDL_Rect rect = {qua.first*CELL_SIZE,qua.second*CELL_SIZE,CELL_SIZE,CELL_SIZE};
    SDL_RenderCopy(renderer,texture,NULL,&rect);
    SDL_DestroyTexture(texture);
}

bool kt_ran_an_qua( pair<int,int>qua, int x0, int y0)
{
    if (qua.first == x0 && qua.second == y0)
    {
        return true;
    }
    return false;
}
