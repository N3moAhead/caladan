
#include "map_generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../types.h"

static block_t **malloc_map(int width, int height)
{
  block_t **new_map = (block_t **)malloc(height * sizeof(block_t *));
  if (new_map == NULL)
  {
    printf("ERROR Could not malloc inside of malloc_map");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < height; i++)
  {
    new_map[i] = (block_t *)malloc(width * sizeof(block_t));
    if (new_map[i] == NULL)
    {
      printf("ERROR: Could not malloc inside of malloc_map");
      exit(EXIT_FAILURE);
    }
  }
  return new_map;
}

static block_t **init_map(int width, int height)
{
  block_t **new_map = malloc_map(width, height);
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      new_map[row][col] = NONE;
    }
  }
  return new_map;
}

static int rand_bsp_number(int value, int min_value)
{
  int divisor = (value - (2 * min_value));
  return divisor > 0 ? (rand() % divisor) + 1 : 1;
}

/**
 * Add rooms and paths to a map using the bsp method
 * map - the map where new rooms will be added
 * lx  - low boundary on the x axis
 * hx  - high boundary on the x axis
 * ly  - low boundary on the y axis
 * hy  - high boundary on the y axis
 *
 * The generated map will be far from perfect.
 * But i think with some adjustment later on its a
 * good point to start from!
 */
static void bsp(block_t **map, int depth, int lx, int hx, int ly, int hy, int min_width, int min_height)
{
  int width = hx - lx;
  int height = hy - ly;
  if (width < min_width || height < min_height)
    return;
  if (depth == 0)
  {
    for (int row = ly; row < hy; row++)
    {
      for (int col = lx; col < hx; col++)
      {
        map[row][col] = ROOM;
      }
    }
    return;
  }

  char split_horizontal = width < height;
  int split_position = 1;
  int space_between_rooms = 1;
  // Calculate the new position for splitting
  if (split_horizontal)
    split_position = ly + min_height + rand_bsp_number(height, min_height);
  else
    split_position = lx + min_width + rand_bsp_number(width, min_width);

  // Split the current place decide randomly if it should be splitted horizontal or vertical
  if (split_horizontal)
  {
    for (int i = ly; i < hy; i++)
    {
      int half_width = (int)width / 2;
      map[i][lx + half_width] = PATH;
    }
    // upper room
    bsp(map, depth - 1, lx, hx, ly, split_position, min_width, min_height);
    // lower room
    bsp(map, depth - 1, lx, hx, split_position + space_between_rooms, hy, min_width, min_height);
  }
  else
  {
    int half_height = (int)height / 2;
    for (int i = lx; i < hx; i++)
    {
      map[ly + half_height][i] = PATH;
    }
    // left room
    bsp(map, depth - 1, lx, split_position, ly, hy, min_width, min_height);
    // right room
    bsp(map, depth - 1, split_position + space_between_rooms, hx, ly, hy, min_width, min_height);
  }
}

// Returns an array of  8 base blocks that souround the given position
// If the given position is on the edge of the map the function will return NONE for
// The Blocks that are out of bounds. The block will be returned beginning from the top one
// And then added clockwise to the returned array. The returned array must be freed after usage!
static block_t *get_surrounding_blocks(block_t **map, vector_2d_t pos, int map_width, int map_height)
{
  block_t *surrounding_blocks = (block_t *)malloc(8 * sizeof(block_t));
  // TOP
  surrounding_blocks[0] = pos.y - 1 >= 0 ? map[pos.y - 1][pos.x] : NONE;
  // TOP Right
  surrounding_blocks[1] = pos.y - 1 >= 0 && pos.x + 1 < map_width ? map[pos.y - 1][pos.x + 1] : NONE;
  // Right
  surrounding_blocks[2] = pos.x + 1 < map_width ? map[pos.y][pos.x + 1] : NONE;
  // Bottom Right
  surrounding_blocks[3] = pos.x + 1 < map_width && pos.y + 1 < map_height ? map[pos.y + 1][pos.x + 1] : NONE;
  // Bottom
  surrounding_blocks[4] = pos.y + 1 < map_height ? map[pos.y + 1][pos.x] : NONE;
  // Bottom Left
  surrounding_blocks[5] = pos.y + 1 < map_height && pos.x - 1 >= 0 ? map[pos.y + 1][pos.x - 1] : NONE;
  // Left
  surrounding_blocks[6] = pos.x - 1 >= 0 ? map[pos.y][pos.x - 1] : NONE;
  // Top Left
  surrounding_blocks[7] = pos.x - 1 >= 0 && pos.y - 1 >= 0 ? map[pos.y - 1][pos.x - 1] : NONE;

  return surrounding_blocks;
}

// Removes every path thats leading into nothing
static void refine_map(block_t **map, int width, int height)
{
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      block_t *surr_blocks = get_surrounding_blocks(map, (vector_2d_t){.x = col, .y = row }, width, height);
      int path_count = 0;
      int room_count = 0;
      int none_count = 0;
      for (int i = 0; i < 8; i++)
      {
        if (surr_blocks[i] == PATH)
        {
          path_count++;
        }
        else if (surr_blocks[i]  == ROOM)
        {
          room_count++;
        }
        else if (surr_blocks[i] == NONE)
        {
          none_count++;
        }
      }
      if (map[row][col] == NONE)
      {
        if (room_count >= 0 || path_count >= 0)
        {
          map[row][col] = WALL;
        }
      }
      if (map[row][col] == PATH)
      {
        // I have to add multiple cases for this one depending on if the room is located on an edge or on a room
        if ((room_count < 4 && path_count < 1) || (room_count < 2 && path_count < 2))
        {
          // Remove the usless path
          map[row][col] = NONE;
          // Return to the last row and the beginning of the cols
          // to catch the next useless path in our way
          row = row > 2 ? row - 2 : 0;
          col = 0;
        }
      }
      free(surr_blocks);
    }
  }
}

void free_map(block_t **map, int height)
{
  for (int i = 0; i < height; i++)
  {
    free(map[i]);
  }
  free(map);
}

/**
 * Will generate a simple map using binary space partitioning
 * The map will be composed of base_blocks_t
 * After generating the map the map should be remoddeld to match the wanted
 * level style
*/
block_t **generate_simple_map(int width, int height, int min_room_width, int min_room_height, int iterations)
{
  // You can set the seed to a specific number to set a specific map layout
  srand(time(NULL));
  block_t **new_map = init_map(width, height);
  bsp(new_map, iterations, 1, width - 1, 1, height - 1, min_room_width, min_room_height);
  refine_map(new_map, width, height);
  return new_map;
}

// // Debug print map to terminal
// void print_map(block_t **map, int width, int height)
// {
//   for (int i = 0; i < width; i++)
//   {
//     printf("%2d", i);
//   }
//   printf("\n");
//   for (int row = 0; row < height; row++)
//   {
//     printf("row: %2d ", row);
//     for (int col = 0; col < width; col++)
//     {
//       switch (map[row][col])
//       {
//       case NONE:
//         printf("  ");
//         break;
//       case ROOM:
//         printf("\033[0;35m██\033[0;37m");
//         break;
//       case WALL:
//         printf("\033[0;32m██\033[0;37m");
//         break;
//       case PATH:
//         printf("\033[0;31m██\033[0;37m");
//         break;
//       }
//     }
//     printf("\n");
//   }
// }