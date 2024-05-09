#ifndef TYPES_H
#define TYPES_H

typedef struct {
  int x;
  int y;
} vector_2d_t;

// The tile type each map consists of
typedef enum {
  NONE,
  /** WALLS */
  WALL,
  WALL_VERTICAL,
  WALL_HORIZONTAL,
  // A wall that connects the bottom side with the right side
  WALL_EDGE_BOT_RIGHT,
  // A wall that connects the bottom side with the left side
  WALL_EDGE_BOT_LEFT,
  // A wall that connects the top side with the left side
  WALL_EDGE_TOP_LEFT,
  // A wall that connects the top side with the right side
  WALL_EDGE_TOP_RIGHT,
  // A wall without connected walls arround it it will look like a column
  WALL_CENTER,

  /** FLOORS */
  PATH,
  ROOM,
} block_t;

// Linked list node for Prison Dungeon Blocks
typedef struct pd_block_node {
  block_t block;
  struct pd_block_node *next;
} pd_block_node_t;

#endif