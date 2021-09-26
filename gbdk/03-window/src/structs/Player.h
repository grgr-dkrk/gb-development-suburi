#ifndef PLAYER_H
#define PLAYER_H
#include <gb/gb.h>

struct player {
  UINT8 char_id;
  UINT8 sprite_index;
  UINT8 base_tile_number;
  UINT8 tile_numbers[4];
  UINT8 x;
  UINT8 y;
  UINT8 width;
  UINT8 height;
};

typedef struct player Player;

extern Player* new_player(UINT8 x, UINT8 y);
extern void set_player_tiles(Player*);

#endif