#ifndef TYPES_H
#define TYPES_H

typedef struct {
  int x;
  int y;
} vector_2d_t;

typedef enum
{
  NONE,
  PATH,
  ROOM,
  WALL,
} base_block_t;

#endif