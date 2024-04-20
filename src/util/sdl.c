#include "sdl.h"
#include "globals.h"
#include "../constants.h"
#include "../types.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/** INIT */

static void init_sdl_window()
{
  window = SDL_CreateWindow(
      "Caladan",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      SDL_WINDOW_RESIZABLE);
  if (!window)
  {
    printf("Error while trying to craete a new SDL Window! SDL_Error: %s \n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
};

static void init_sdl_renderer()
{
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer)
  {
    printf("Error while trying to create a new SDL Renderer! SDL_Error: %s \n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

static void init_font()
{
  if (TTF_Init() != 0)
  {
    printf("Error while trying to setup TTF! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  font = TTF_OpenFont("asset/font/font.ttf", 80);
  if (!font)
  {
    printf("Error while trying to load the font! %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void init_sdl()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("Error while trying to setup Sdl! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
  {
    printf("Error while trying to init SDL_Image! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  init_sdl_window();
  init_sdl_renderer();
  init_font();
};

/** MAIN LOOP HELPER */

void cap_frame_rate(long *then, float *remainder, int fps)
{
  long wait, frame_time;
  wait = ((int)1000 / fps) + *remainder;
  *remainder -= (int)*remainder;
  frame_time = SDL_GetTicks() - *then;
  wait -= frame_time;
  if (wait < 1)
  {
    wait = 1;
  }
  SDL_Delay(wait);
  *remainder += 0.667;
  *then = SDL_GetTicks();
}

void prepare_scene()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void present_scene()
{
  SDL_RenderPresent(renderer);
}