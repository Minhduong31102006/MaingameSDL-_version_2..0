#include "snake.h"

void khoi_tao_ran(vector <pair<int,int>> &v, int x0, int y0)
{
    int i =0;
    while (i < SL)
    {
        v[i].first = x0;
        v[i].second = y0;
        x0--;
        i++;
    }
}

void ve_ran(vector<pair<int, int>> v, SDL_Renderer *renderer,const char *path_head, const char *path_body, const char *path_tail, const char *path_corner, Direction dir) {
    SDL_Texture *texture;

    for (size_t i = 0; i < SL; i++)
    {
        double angle = 0.0;
        SDL_Point center = {CELL_SIZE / 2, CELL_SIZE / 2}; // Tâm xoay
        SDL_Rect rect = { v[i].first * CELL_SIZE, v[i].second * CELL_SIZE, CELL_SIZE, CELL_SIZE };

        // Xử lý đầu rắn
        if (i == 0) {
            texture = loadTexture(path_head, renderer);
            switch (dir) {
                case RIGHT: angle = 0; break;
                case LEFT: angle = 180; break;
                case UP: angle = 270; break;
                case DOWN: angle = 90; break;
            }
        }
        // Xử lý đuôi rắn
        else if (i == SL - 1) {
            texture = loadTexture(path_tail, renderer);
            pair<int, int> beforeTail = v[i - 1];

            if (beforeTail.first < v[i].first)
            {
                if (dir == RIGHT && beforeTail.first == 0)
                {
                    angle = 0;
                }
                else angle = 180;
            }
            else if (beforeTail.first > v[i].first)
            {
                if (dir == LEFT && beforeTail.first == SCREEN_WIDTH/CELL_SIZE-1)
                {
                    angle = 180;
                }
                else angle = 0;
            }

            else if (beforeTail.second < v[i].second)
            {
                if (dir == DOWN && beforeTail.second == 0)
                {
                    angle = 90;
                }
                else angle = 270;
            }

            else if (beforeTail.second > v[i].second)
            {
                if (dir == UP && beforeTail.second == SCREEN_HEIGHT/CELL_SIZE-1)
                {
                    angle = 270;
                }
                else angle = 90;
            }
        }
        // Xử lý thân rắn
        else {
            pair<int, int> prev = v[i - 1]; // Vị trí trước đó
            pair<int, int> next = v[i + 1]; // Vị trí tiếp theo

            // Nếu là đoạn thân thẳng
            if (prev.first == next.first) { // Cùng cột => đi dọc
                texture = loadTexture(path_body, renderer);
                angle = 90;
            }
            else if (prev.second == next.second) { // Cùng hàng => đi ngang
                texture = loadTexture(path_body, renderer);
                angle = 0;
            }
            // Nếu là đoạn bo góc
            else {
                texture = loadTexture(path_corner, renderer);

                if ((prev.first < v[i].first && next.second < v[i].second) || (next.first < v[i].first && prev.second < v[i].second)) {
                    if ((prev.second == 0 && next.second == SCREEN_HEIGHT/CELL_SIZE -1)|| ( prev.second == SCREEN_HEIGHT/CELL_SIZE -1 && next.second == 0))
                    {
                        angle = 270;
                    }
                    else if ((prev.first == 0 && next.first == SCREEN_HEIGHT/CELL_SIZE -1) || (prev.first == SCREEN_HEIGHT/ CELL_SIZE-1 && next .first == 0))
                    {
                        angle = 90;
                    }
                    else angle = 0;
                }
                else if ((prev.first > v[i].first && next.second < v[i].second) || (next.first > v[i].first && prev.second < v[i].second)) {
                    if ((prev.second == 0 && next.second == SCREEN_HEIGHT/CELL_SIZE -1)|| ( prev.second == SCREEN_HEIGHT/CELL_SIZE -1 && next.second == 0))
                    {
                        angle = 180;
                    }
                    else if ((prev.first == 0 && next.first == SCREEN_HEIGHT/CELL_SIZE -1) || (prev.first == SCREEN_HEIGHT/ CELL_SIZE-1 && next .first == 0))
                    {
                        angle = 0;
                    }
                    else angle = 90;
                }
                else if ((prev.first < v[i].first && next.second > v[i].second) || (next.first < v[i].first && prev.second > v[i].second)) {
                    if ((prev.second == 0 && next.second == SCREEN_HEIGHT/CELL_SIZE -1)|| ( prev.second == SCREEN_HEIGHT/CELL_SIZE -1 && next.second == 0))
                    {
                        angle = 0;
                    }
                    else if ((prev.first == 0 && next.first == SCREEN_HEIGHT/CELL_SIZE -1) || (prev.first == SCREEN_HEIGHT/ CELL_SIZE-1 && next .first == 0))
                    {
                        angle = 180;
                    }
                    else angle = 270;
                }
                else if ((prev.first > v[i].first && next.second > v[i].second) || (next.first > v[i].first && prev.second > v[i].second)) {
                    if ((prev.second == 0 && next.second == SCREEN_HEIGHT/CELL_SIZE -1)|| ( prev.second == SCREEN_HEIGHT/CELL_SIZE -1 && next.second == 0))
                    {
                        angle = 90;
                    }
                    else if ((prev.first == 0 && next.first == SCREEN_HEIGHT/CELL_SIZE -1) || (prev.first == SCREEN_HEIGHT/ CELL_SIZE-1 && next .first == 0))
                    {
                        angle = 270;
                    }
                    else angle = 180;
                }
            }
        }

        SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, &center, SDL_FLIP_NONE);
        SDL_DestroyTexture(texture);
    }
}

void xu_li_ran(pair<int,int> &qua, vector <pair<int,int>> &v, int x0, int y0)
{
    if (!kt_ran_an_qua(qua,v[0].first,v[0].second))
    {
        v.pop_back();
        SL--;
    }
    else
    {
        tao_qua(qua,v);
    }

    v.insert(v.begin(),{x0,y0});
    SL++;
}

bool kt_ran_cham_duoi(vector <pair<int,int>> v)
{
    for (int i = 1 ;i < SL;i++)
    {
        if (v[0].first == v[i].first && v[0].second == v[i].second)
            return false;
    }
    return true;
}
