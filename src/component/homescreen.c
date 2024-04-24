#include "homescreen.h"
#include <SDL2/SDL.h>
#include "../util/sdl.h"
#include "../util/render.h"


// Test Function to exit the game loop
char quitted_game()
{
  SDL_Event event;
  char quitted_game = 0;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      quitted_game = 1;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        quitted_game = 1;
        break;
      }
    default:
      break;
    }
  }

  return quitted_game;
}

void homescreen()
{
  long then = SDL_GetTicks();
  float remainder = 0;
  while (!quitted_game())
  {
    prepare_scene();
    render_text("Welcome to Caladan!", (vector_2d_t){.x = 90, .y = 300}, (SDL_Color){255, 255, 255, 255});
    present_scene();
    cap_frame_rate(&then, &remainder, 1);
  }
}