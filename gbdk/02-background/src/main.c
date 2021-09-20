#include <gb/gb.h>
#include <stdio.h>
#include "Characters.c"
#include "Backgrounds.c"
#include "StageMap.c"

#define STAGE_WIDTH 32

BOOLEAN is_end = FALSE;
UINT8 player_pos[2] = {0};
UINT8 friend_pos[2] = {0};

BOOLEAN is_colliding_friend()
{
  return ((player_pos[0] >= friend_pos[0] && player_pos[0] <= friend_pos[0] + 8) && (player_pos[1] >= friend_pos[1] && player_pos[1] <= friend_pos[1] + 8)) || ((friend_pos[0] >= player_pos[0] && friend_pos[0] <= player_pos[0] + 8) && (friend_pos[1] >= player_pos[1] && friend_pos[1] <= player_pos[1] + 8));
}

BOOLEAN is_colliding(UINT8 next_player_x, UINT8 next_player_y)
{
  // 画面端
  if (next_player_x - 1 >= 160 || next_player_x - 1 <= 1 || next_player_y - 1 >= 152 || next_player_y - 1 <= 16) {
    return TRUE;
  }

  UINT16 grid_X;
  UINT16 grid_Y;
  UINT16 tile_index;
  BOOLEAN result = FALSE;
  UINT8 i;

  for (i = 0; i < 8; i++) {
    grid_X = (next_player_x - 8 + i) / 8;
    grid_Y = (next_player_y - 16 + i) / 8;
    tile_index = STAGE_WIDTH * grid_Y + grid_X;
    if (StageMap[tile_index] != 0x00) {
      result = TRUE;
    }
  }

  return result;
}

void main()
{
  set_sprite_data(0, 2, Charcters);
  set_bkg_data(0, 2, Backgrounds);
  set_bkg_tiles(0, 0, 32, 32, StageMap);

  // 主人公
  set_sprite_tile(0, 0);
  player_pos[0] = 16;
  player_pos[1] = 24; 
  move_sprite(0, player_pos[0], player_pos[1]);

  // フレンド
  set_sprite_tile(1, 1);
  friend_pos[0] = 152;
  friend_pos[1] = 144;
  move_sprite(1, friend_pos[0], friend_pos[1]);
  
  SHOW_BKG;
  SHOW_SPRITES;

  while (!is_end)
  {
    UINT8 joypad_control = joypad();

    if (joypad_control & J_UP)
    {
      if (!is_colliding(player_pos[0], player_pos[1] - 1))
      {
        player_pos[1]--;
        move_sprite(0, player_pos[0], player_pos[1]);
      }
    }
    else if (joypad_control & J_DOWN)
    {
      if (!is_colliding(player_pos[0], player_pos[1] + 1))
      {
        player_pos[1]++;
        move_sprite(0, player_pos[0], player_pos[1]);
      }
    }
    if (joypad_control & J_RIGHT)
    {
      if (!is_colliding(player_pos[0] + 1, player_pos[1]))
      {
        player_pos[0]++;
        move_sprite(0, player_pos[0], player_pos[1]);
      }
    }
    else if (joypad_control & J_LEFT)
    {
      if (!is_colliding(player_pos[0] - 1, player_pos[1]))
      {
        player_pos[0]--;
        move_sprite(0, player_pos[0], player_pos[1]);
      }
    }

    is_end = is_colliding_friend();

    wait_vbl_done();
  }
  printf("GAME CLEAR");
}