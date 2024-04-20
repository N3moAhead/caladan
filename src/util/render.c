#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "globals.h"
#include "../types.h"

// Display a texture on the window
void blit(SDL_Rect dest, SDL_Texture *texture)
{
  SDL_RenderCopy(renderer, texture, NULL, &dest);
}

// Display text on the window
void render_text(char *text, vector_2d_t pos, SDL_Color color)
{
  SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect dest = {.x = pos.x, .y = pos.y, .w = surface->w, .h = surface->h};
  SDL_RenderCopy(renderer, texture, NULL, &dest);
}
