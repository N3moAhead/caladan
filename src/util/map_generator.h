#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H
#include "../types.h"

block_t **generate_simple_map(int width, int height, int min_room_width, int min_room_height, int iterations);
void free_map(block_t **map, int height);

#endif