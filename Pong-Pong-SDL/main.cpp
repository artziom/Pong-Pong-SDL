#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\r\n";
    success = false;
  } else {
    window = SDL_CreateWindow("Pong-Pong-SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\r\n";
      success = false;
    } else {

      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      if (renderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\r\n";
        success = false;
      } else {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      }
    }
  }

  return success;
}

bool loadMedia() {
  bool success = true;
  return success;
}

void close() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = NULL;
  renderer = NULL;

  SDL_Quit();
}

void clearScreen() {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
}

void draw() {
  SDL_Rect rect = {(SCREEN_WIDTH / 2) - 25, (SCREEN_HEIGHT / 2) - 25, 50, 50};
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(renderer, &rect);
}

void update() { SDL_RenderPresent(renderer); }

int main(int argc, char *args[]) {
  std::cout << "Hello World!\r\n";

  if (!init()) {
    std::cout << "Failed to initialize!\r\n";
  } else {
    if (!loadMedia()) {
      std::cout << "Failed to load media!\r\n";
    } else {

      bool quit = false;

      SDL_Event e;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            std::cout << "Quit\r\n";
            quit = true;
          }
        }

        clearScreen();
        draw();
        update();
      }
    }
  }

  close();

  return 0;
}
