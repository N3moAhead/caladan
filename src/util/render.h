#ifndef RENDER_H
#define RENDER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../types.h"

void blit(SDL_Rect dest, SDL_Texture *texture);
void render_text(char *text, vector_2d_t pos, SDL_Color color);
void render_animated_text(char *text, vector_2d_t pos, SDL_Color color, int anima_val);

#endif
