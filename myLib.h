#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define MAX 100

using namespace std;

//screen
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int CELL_SIZE = 40;
const int DELAY_TIME = 100;

// Số lượng rắn
extern int SL;

//snake
const int START_LOCATION_SNAKE_X = 5;
const int START_LOCATION_SNAKE_Y = 5;

// nút bấm
const int START_BUTTON_CLASSIC_X = 7;
const int START_BUTTON_CLASSIC_Y = 8;
const int START_BUTTON_MEDIUM_X = 7;
const int START_BUTTON_MEDIUM_Y = 11;
const int START_BUTTON_HARD_X = 7;
const int START_BUTTON_HARD_Y = 14;
const int BUTTON_WIDTH = 6;
const int BUTTON_HEIGHT = 3;

enum Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
};

//hàm SDL
void logErrorAndExit(const char* msg, const char* error);
SDL_Window* initSDL(const char* WINDOW_TITLE);
SDL_Renderer* createRenderer(SDL_Window* window);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
void Free (SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);

// các hàm xử lí rắn
void cap_nhat_vi_tri(Direction dir, int &x, int &y);
void xu_li_ra_khoi_man_hinh (int &x, int &y);
void ve_luoi (SDL_Renderer *renderer);
void kt_huong (SDL_Event event, Direction &dir);

// các hàm hiển thị menu và gameover

void showMenu(SDL_Renderer *renderer);
void showGameOver(SDL_Renderer *renderer);
void waitUntilMousePressedIntoRectangle (SDL_Renderer *renderer, SDL_Rect rect);


#endif // MYLIB_H_INCLUDED
