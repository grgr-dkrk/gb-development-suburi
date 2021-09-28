#include <gb/gb.h>
#include <stdio.h>
#include "structs/Player.h"
#include "structs/Enemy.h"
#include "Sprites.c"
#include "Backgrounds.c"
#include "StageMap.c"
#include "HUDMaterials.c"
#include "Window.c"

// STAT 割り込み時にウィンドウを隠す
void interruptLCD()
{
  while(STAT_REG & 3); // HBlank まで待つ
  HIDE_WIN;
}

// VBlank 時にウィンドウを表示する
void interruptVBL() {
  SHOW_WIN;
}

void main()
{
  // STAT_REG = 0x40; // LYC を有効にする
  // LYC_REG = 0x07;  // 8 番目の直前の行

  disable_interrupts();
  
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

  // ハンドラと、割り込みの設定
  // add_LCD(interruptLCD);
  add_VBL(interruptVBL);
  set_interrupts(VBL_IFLAG | LCD_IFLAG);
  enable_interrupts();

  while (1)
  {
    wait_vbl_done();
  }
}