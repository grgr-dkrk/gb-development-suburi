#include <gb/gb.h>
#include <stdlib.h>
#include "./Player.h"
#include "../global.h"

Player *new_player(UINT8 x, UINT8 y)
{
  Player *p = malloc(sizeof(Player));
  p->sprite_index = global_sprite_index;
  p->base_tile_number = 0;
  p->tile_numbers[0] = p->base_tile_number;
  p->tile_numbers[1] = p->base_tile_number + 1;
  p->tile_numbers[2] = p->base_tile_number + 2;
  p->tile_numbers[3] = p->base_tile_number + 3;
  p->x = x;
  p->y = y;
  p->width = 16;
  p->height = 16;
  set_player_tiles(p);
  return p;
}

void set_player_tiles(Player* player) {
  set_sprite_tile(player->sprite_index, player->tile_numbers[0]);
  set_sprite_tile(player->sprite_index + 1, player->tile_numbers[1]);
  set_sprite_tile(player->sprite_index + 2, player->tile_numbers[2]);
  set_sprite_tile(player->sprite_index + 3, player->tile_numbers[3]);
  global_sprite_index += 4;
  move_sprite(player->sprite_index, player->x, player->y);
  move_sprite(player->sprite_index + 1, player->x, player->y + 8);
  move_sprite(player->sprite_index + 2, player->x + 8, player->y);
  move_sprite(player->sprite_index + 3, player->x + 8, player->y + 8);
}
