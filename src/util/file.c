#include "file.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "globals.h"

SDL_Texture *load_texture(char *filename)
{
  printf("Loading Image: %s\n", filename);
  SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
  if (!texture)
  {
    printf("Error while trying to load Image %s. SDL_Error: %s", filename, SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return texture;
}
