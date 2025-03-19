#include "myLib.h"

int SL = 7;

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL(const char* WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT || e.type == SDL_MOUSEBUTTONDOWN) )
            return;
        SDL_Delay(100);
    }
}

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    if (!texture) std::cerr << "Loi tai anh: " << IMG_GetError() << std::endl;
    return texture;
};

void Free (SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


void cap_nhat_vi_tri(Direction dir, int &x, int &y)
{
    switch(dir)
        {
        case UP:
            {
                y--;
                return;
            }
        case DOWN:
            {
                y++;
                return;
            }
        case LEFT:
            {
                x--;
                return;
            }
        case RIGHT:
            {
                x++;
                return;
            }
        }
}

void xu_li_ra_khoi_man_hinh (int &x, int &y)
{
    if (x >= SCREEN_WIDTH / CELL_SIZE)
    {
        x = 0;
        return;
    }

    else if (y >= SCREEN_HEIGHT / CELL_SIZE)
    {
        y = 0;
        return;
    }

    else if (x < 0)
    {
        x = SCREEN_WIDTH / CELL_SIZE - 1;
        return;
    }
    else if (y < 0)
    {
        y = SCREEN_HEIGHT / CELL_SIZE - 1;
        return;
    }
}

void ve_luoi (SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    for (int i = 0; i <= SCREEN_WIDTH; i += CELL_SIZE)
    {
        SDL_RenderDrawLine(renderer, i, 0, i, SCREEN_HEIGHT);
    }
    for (int i = 0; i <= SCREEN_HEIGHT; i += CELL_SIZE)
    {
        SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i);
    }
}

void kt_huong (SDL_Event event, Direction &dir)
{
    if (event.key.keysym.sym == SDLK_LEFT && dir != RIGHT)
    {
        dir = LEFT;
    }
    else if (event.key.keysym.sym == SDLK_RIGHT && dir != LEFT)
    {
        dir = RIGHT;
    }
    else if (event.key.keysym.sym == SDLK_UP && dir != DOWN)
    {
        dir =UP;
    }
    else if (event.key.keysym.sym == SDLK_DOWN && dir != UP)
    {
        dir = DOWN;
    }
}

void showMenu(SDL_Renderer *renderer)
{
    SDL_Texture* menu = loadTexture ("image\\Menu\\menu.png", renderer);
    SDL_RenderCopy(renderer, menu, NULL, NULL );

    SDL_Rect rect = {START_BUTTON_CLASSIC_X*CELL_SIZE, START_BUTTON_CLASSIC_Y*CELL_SIZE, BUTTON_WIDTH*CELL_SIZE, BUTTON_HEIGHT*CELL_SIZE};

    SDL_Texture *button = loadTexture ("image\\Menu\\button_classic.png", renderer);
    SDL_RenderCopy(renderer, button, NULL, &rect);
    SDL_RenderPresent(renderer);

    //waitUntilKeyPressed();

    waitUntilMousePressedIntoRectangle(renderer, rect);

    SDL_DestroyTexture(menu);
}

void showGameOver(SDL_Renderer *renderer)
{
    SDL_Texture* game_over = loadTexture ("image\\Menu\\game_over.png", renderer);
    SDL_RenderCopy(renderer, game_over, NULL, NULL );
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
    SDL_DestroyTexture(game_over);
}

void waitUntilMousePressedIntoRectangle (SDL_Renderer *renderer, SDL_Rect rect)
{
    SDL_Event event;
    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) return;
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x;
                int y = event.button.y;
                if ((x >= rect.x && x <= rect.x+rect.w) && (y >= rect.y && y <= rect.y+ rect.h))
                {
                    return;
                }
            }
        }
        SDL_Delay(DELAY_TIME);
    }
}
