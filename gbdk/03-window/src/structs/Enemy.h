#ifndef ENEMY_H
#define ENEMY_H
#include <gb/gb.h>

struct enemy {
  UINT8 char_id;
  UINT8 sprite_index;
  UINT8 base_tile_number;
  UINT8 tile_numbers[4];
  UINT8 x;
  UINT8 y;
  UINT8 width;
  UINT8 height;
};

typedef struct enemy Enemy;

extern Enemy* new_enemy(UINT8 char_id, UINT8 base_tile_number, UINT8 x, UINT8 y);
extern void set_enemy_tiles(Enemy*);

#endif