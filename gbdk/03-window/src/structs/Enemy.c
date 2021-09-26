#include <gb/gb.h>
#include <stdlib.h>
#include "./Enemy.h"
#include "../global.h"

Enemy *new_enemy(UINT8 char_id, UINT8 base_tile_number, UINT8 x, UINT8 y)
{
  Enemy *p = malloc(sizeof(Enemy));
  p->char_id = char_id;
  p->sprite_index = global_sprite_index;
  p->base_tile_number = base_tile_number;
  p->tile_numbers[0] = p->base_tile_number;
  p->tile_numbers[1] = p->base_tile_number + 1;
  p->x = x;
  p->y = y;
  p->width = 16;
  p->height = 8;
  set_enemy_tiles(p);
  return p;
}

void set_enemy_tiles(Enemy* enemy) {
  set_sprite_tile(global_sprite_index, enemy->tile_numbers[0]);
  set_sprite_tile(global_sprite_index + 1, enemy->tile_numbers[1]);
  global_sprite_index += 2;
  move_sprite(enemy->sprite_index, enemy->x, enemy->y);
  move_sprite(enemy->sprite_index + 1, enemy->x + 8, enemy->y);
}
