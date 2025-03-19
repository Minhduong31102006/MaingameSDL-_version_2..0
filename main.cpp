#include "myLib.h"
#include "snake.h"
#include "fruit.h"

int main(int argc, char* argv[]) {
    SDL_Window* window = initSDL("GameSnake.2.0");
    SDL_Renderer* renderer = createRenderer(window);
    srand(time(NULL));

    showMenu(renderer);

    SDL_Texture* background = loadTexture("image\\background\\main_background.jpg", renderer);
    if (!background) return -1;

    bool running = true;
    bool gameover = false;
    SDL_Event event;

    Direction dir = RIGHT;

    int x = START_LOCATION_SNAKE_X;
    int y = START_LOCATION_SNAKE_Y;

    vector <pair<int,int>> snake(MAX);
    pair <int,int> fruit;

    khoi_tao_ran(snake,x,y);
    tao_qua(fruit,snake);


    while (running) {
        // Kiểm tra sự kiện thoát chương trình
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            else if (event.type == SDL_KEYDOWN)
            {
                kt_huong(event,dir);
            }
        }

        // Cập nhật vị trí
        cap_nhat_vi_tri(dir,x,y);

        // Nếu đi ra khỏi màn hình, quay lại từ đầu
        xu_li_ra_khoi_man_hinh(x,y);

        SDL_RenderClear(renderer);
        // Vẽ ảnh nền (thay vì xóa toàn bộ màn hình)
        SDL_RenderCopy(renderer, background, NULL, NULL);

        // Vẽ lưới
        ve_luoi(renderer);

        xu_li_ran(fruit, snake,x,y);

        gameover = kt_ran_cham_duoi(snake);

        running = gameover && running;

        ve_qua(fruit,renderer,"image\\Snake\\fruit.png");

        ve_ran(snake,renderer,"image\\Snake\\snake_green_head.png","image\\Snake\\body_green.png","image\\Snake\\last_tail_green.png","image\\Snake\\curve_green.png",dir);

        SDL_RenderPresent(renderer);

        SDL_Delay(DELAY_TIME);
    }

    //waitUntilKeyPressed();

    showGameOver(renderer);

    Free(window,renderer,background);

    return 0;
}

