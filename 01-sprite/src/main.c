#include <gb/gb.h>
#include <stdio.h>
#include "characters.c"
#include "constants.h"

BOOLEAN is_end = FALSE;
UINT8 player_pos[2] = {0};
UINT8 friend_pos[2] = {0};

void main()
{
  disable_interrupts(); // 割り込み無効

  set_sprite_data(0, 6, Charcters);
  set_sprite_tile(0, 0); // スプライト番号 0 にタイル 0 を設定（つまり番号 0 は主人公）
  set_sprite_tile(1, 5); // スプライト番号 1 にタイル 4 を設定（つまり番号 1 はフレンド）

  // プレイヤー位置の初期化
  player_pos[0] = 8;
  player_pos[1] = 16;
  move_sprite(0, player_pos[0], player_pos[1]);

  // フレンド位置の初期化
  friend_pos[0] = 160;
  friend_pos[1] = 152;
  move_sprite(1, friend_pos[0], friend_pos[1]);

  SHOW_SPRITES; // スプライトを表示
  DISPLAY_ON;   // ディスプレイをオンにする

  enable_interrupts(); // 割り込み再開

  while (!is_end)
  {
    UINT8 joypad_control = joypad();

    // キャラクターの操作
    if (joypad_control & J_UP)
    {
      set_sprite_tile(0, 1);                        // 上向きにする
      player_pos[1]--;                              // プレイヤーの Y 軸を -1 する
      move_sprite(0, player_pos[0], player_pos[1]); // スプライト番号 0 を動かす
    }
    else if (joypad_control & J_DOWN)
    {
      set_sprite_tile(0, 2);
      player_pos[1]++;
      move_sprite(0, player_pos[0], player_pos[1]);
    }
    else if (joypad_control & J_RIGHT)
    {
      set_sprite_tile(0, 3);
      player_pos[0]++;
      move_sprite(0, player_pos[0], player_pos[1]);
    }
    else if (joypad_control & J_LEFT)
    {
      set_sprite_tile(0, 4);
      player_pos[0]--;
      move_sprite(0, player_pos[0], player_pos[1]);
    }
    else
    {
      set_sprite_tile(0, 0);
    }

    // プレイヤーとお友達の座標を見て衝突判定。あれば is_end フラグを TRUE にする
    if (
        (player_pos[0] >= friend_pos[0] && player_pos[0] <= friend_pos[0] + 8) && (player_pos[1] >= friend_pos[1] && player_pos[1] <= friend_pos[1] + 8) || (friend_pos[0] >= player_pos[0] && friend_pos[0] <= player_pos[0] + 8) && (friend_pos[1] >= player_pos[1] && friend_pos[1] <= player_pos[1] + 8)
      )
    {
      is_end = TRUE;
    }

    wait_vbl_done(); // 垂直ブランク割り込み（VBL）が終了するまで待つ
  }
  printf("THE END");
}