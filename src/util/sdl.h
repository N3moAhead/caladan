#ifndef SDL_H
#define SDL_H

void init_sdl();
void cap_frame_rate(long *then, float *remainder, int fps);
void prepare_scene();
void present_scene();

#endif
