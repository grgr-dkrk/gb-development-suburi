#include <gb/gb.h>
#include <stdio.h>
#include "structs/Player.h"
#include "structs/Enemy.h"
#include "Sprites.c"
#include "Backgrounds.c"
#include "StageMap.c"
#include "HUDMaterials.c"
#include "Window.c"

void interruptLCD()
{
  HIDE_WIN;
}

void main()
{
  // STAT_REG = 0x40;
  // LYC_REG = 8;
  
  set_sprite_data(0, 11, Sprites);
  set_bkg_data(0, 2, Backgrounds);
  set_bkg_data(2, 16, HUDMaterials);
  set_bkg_tiles(0, 0, 20, 18, StageMap);
  Player *player = new_player(64, 128);
  Enemy *enemy = new_enemy(0, 8, 56, 56);

  // 横ウィンドウ（下）
  // set_win_tiles(0, 0, 20, 1, Window);
  // move_win(0, 136);

  // 縦ウィンドウ（右）
  set_win_tiles(0, 0, 5, 20, WindowVertical);
  move_win(127, 0);

  // 横ウィンドウ（上） ※割り込みで対応
  // set_win_tiles(0, 0, 20, 1, Window);
  // move_win(7, 0);

  // 縦ウィンドウ（左）
  // set_win_tiles(0, 0, 5, 20, WindowVertical);
  // move_win(7, 0);

  SHOW_BKG;
  SHOW_SPRITES;

  // add_LCD(interruptLCD);
  // set_interrupts(VBL_IFLAG | LCD_IFLAG);
  // enable_interrupts();

  while (1)
  {
    SHOW_WIN;
    wait_vbl_done();
  }
}