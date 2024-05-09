#include "prison.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/map_generator.h"
#include "../types.h"
#include "../constants.h"

/**
 * The Prison
 *
 *
 * While creating the map i would like to store every block inside of a linked list.
 * This way i would be able to spawn multiple blocks at the same location.
 * This could be usefull if i would like to place a torch on a wall or stuff like that
 */

block_t **create_level_map()
{
  block_t **base_map = generate_simple_map(
      PRISON_MAP_WIDTH,
      PRISON_MAP_HEIGHT,
      PRISON_MIN_ROOM_WIDTH,
      PRISON_MIN_ROOM_HEIGHT,
      PRISON_MAP_BSP_ITERATIONS);
  free_map(base_map, PRISON_MAP_HEIGHT);
}
