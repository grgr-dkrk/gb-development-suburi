#include <gb/gb.h>
#include "Characters.c"
#include "Backgrounds.c"
#include "StageMap.c"

#define JUMP_ACC_DEFAULT 12

UINT8 player_pos[2] = {0};
BOOLEAN is_jumping = FALSE;
INT8 jump_gravity = -1;
INT8 jump_acc = JUMP_ACC_DEFAULT;

BOOLEAN is_colliding(UINT8 next_player_x)
{
  return next_player_x - 1 >= 160 || next_player_x <= 7;
}

void play_jump_sound()
{
  NR10_REG = 0x37;
  NR11_REG = 0x8C;
  NR12_REG = 0x93;
  NR13_REG = 0x41;
  NR14_REG = 0x86;
}

void jump()
{
  jump_acc += jump_gravity;
  player_pos[1] -= jump_acc;

  if (player_pos[1] >= 143)
  {
    is_jumping = FALSE;
    jump_acc = JUMP_ACC_DEFAULT;
    move_sprite(0, player_pos[0], 144);
    return;
  }
  move_sprite(0, player_pos[0], player_pos[1]);
}

void main()
{
  NR52_REG = 0x80;
  NR50_REG = 0x77;
  NR51_REG = 0xFF;

  set_sprite_data(0, 2, Charcters);
  set_bkg_data(0, 2, Backgrounds);
  set_bkg_tiles(0, 0, 32, 32, StageMap);

  set_sprite_tile(0, 0);
  player_pos[0] = 16;
  player_pos[1] = 144;
  move_sprite(0, player_pos[0], player_pos[1]);

  SHOW_BKG;
  SHOW_SPRITES;

  while (1)
  {
    UINT8 joypad_control = joypad();
    if (joypad_control & J_RIGHT)
    {
      if (!is_colliding(player_pos[0] + 1))
      {
        player_pos[0]++;
        move_sprite(0, player_pos[0], player_pos[1]);
      }
    }
    else if (joypad_control & J_LEFT)
    {
      if (!is_colliding(player_pos[0] - 1))
      {
        player_pos[0]--;
        move_sprite(0, player_pos[0], player_pos[1]);
      }
    }
    if (is_jumping)
    {
      jump();
    }
    else if (joypad_control & J_A)
    {
      is_jumping = TRUE;
      play_jump_sound();
      jump();
    }

    wait_vbl_done();
  }
}