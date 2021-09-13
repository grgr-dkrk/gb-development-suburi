#include <gb/gb.h>
#include <stdio.h>
#include "characters.c"

BOOLEAN is_end = FALSE;
UINT8 player_pos[2] = {0};
UINT8 friend_pos[2] = {0};

BOOLEAN is_colliding_friend()
{
  return ((player_pos[0] >= friend_pos[0] && player_pos[0] <= friend_pos[0] + 8) && (player_pos[1] >= friend_pos[1] && player_pos[1] <= friend_pos[1] + 8)) || ((friend_pos[0] >= player_pos[0] && friend_pos[0] <= player_pos[0] + 8) && (friend_pos[1] >= player_pos[1] && friend_pos[1] <= player_pos[1] + 8));
}

BOOLEAN is_colliding_x(BYTE delta)
{
  if (delta > 0)
  {
    return player_pos[0] >= 160;
  }
  else
  {
    return player_pos[0] <= 8;
  }
}

BOOLEAN is_colliding_y(BYTE delta)
{
  if (delta > 0)
  {
    return player_pos[1] >= 152;
  }
  else
  {
    return player_pos[1] <= 16;
  }
}

void main()
{
  set_sprite_data(0, 6, Charcters);

  // 主人公
  set_sprite_tile(0, 0);
  player_pos[0] = 8;
  player_pos[1] = 16;
  move_sprite(0, player_pos[0], player_pos[1]);

  // フレンド
  set_sprite_tile(1, 5);
  friend_pos[0] = 160;
  friend_pos[1] = 152;
  move_sprite(1, friend_pos[0], friend_pos[1]);

  SHOW_SPRITES;

  while (!is_end)
  {
    UINT8 joypad_control = joypad();

    if (joypad_control & J_UP)
    {
      if (!is_colliding_y(-1))
      {
        player_pos[1]--;
        move_sprite(0, player_pos[0], player_pos[1]);
      }
    }
    else if (joypad_control & J_DOWN)
    {
      if (!is_colliding_y(1))
      {
        player_pos[1]++;
        move_sprite(0, player_pos[0], player_pos[1]);
      }
    }
    if (joypad_control & J_RIGHT)
    {
      if (!is_colliding_x(1))
      {
        player_pos[0]++;
        move_sprite(0, player_pos[0], player_pos[1]);
      }
    }
    else if (joypad_control & J_LEFT)
    {
      if (!is_colliding_x(-1))
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