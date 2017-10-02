/* Copyright 2017 Dan Amlund Thomsen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#include "tetris_text.h"

static char empty_piece[7][7] = { { 0, 0, 0, 0, 0, 0, 0 },
                                  { 0, 0, 0, 0, 0, 0, 0 },
                                  { 0, 0, 0, 0, 0, 0, 0 },
                                  { 0, 0, 0, 0, 0, 0, 0 },
                                  { 0, 0, 0, 0, 0, 0, 0 },
                                  { 0, 0, 0, 0, 0, 0, 0 },
                                  { 0, 0, 0, 0, 0, 0, 0 } };

static char temp_piece[7][7];

static int curx = 0;
static int cury = 0;

static void clear_piece(char piece[7][7]) {
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 7; x++) {
      piece[x][y] = 0;
    }
  }
}

static void copy_piece_from_to(char from[7][7], char to[7][7]) {
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 7; x++) {
      to[x][y] = from[x][y];
    }
  }
}

static void rotate_piece(char piece[7][7]) {
  // transpose
  for (int y = 0; y < 7; y++) {
    for (int x = y + 1; x < 7; x++) {
      char tmp = piece[y][x];
      piece[y][x] = piece[x][y];
      piece[x][y] = tmp;
    }
  }

  // reverse rows
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 3; x++) {
      char tmp = piece[y][6 - x];
      piece[y][6 - x] = piece[y][x];
      piece[y][x] = tmp;
    }
  }
}

static char get_shape_char(int shape) {
  switch (shape) {
  case 0: return 'I';
  case 1: return 'J';
  case 2: return 'L';
  case 3: return 'O';
  case 4: return 'S';
  case 5: return 'T';
  case 6: return 'Z';
  }
  return 'Q';
}

static void set_piece(char piece[7][7], int shape, int rotation) {
  clear_piece(piece);
  switch (shape) {
  case 0:
    if (rotation % 2 == 0) {
      // xxXx
      piece[3][1] = 1;
      piece[3][2] = 1;
      piece[3][3] = 1;
      piece[3][4] = 1;
    } else {
      // x
      // x
      // X
      // x
      piece[1][3] = 1;
      piece[2][3] = 1;
      piece[3][3] = 1;
      piece[4][3] = 1;
    }
    break;
  case 1:
    // xXx
    //   x
    piece[3][2] = 1;
    piece[3][3] = 1;
    piece[3][4] = 1;
    piece[4][4] = 1;
    for (int i = 0; i < rotation; i++) {
      rotate_piece(piece);
    }
    break;
  case 2:
    // xXx
    // x
    piece[3][2] = 1;
    piece[3][3] = 1;
    piece[3][4] = 1;
    piece[4][2] = 1;
    for (int i = 0; i < rotation; i++) {
      rotate_piece(piece);
    }
    break;
  case 3:
    // xX
    // xx
    piece[3][2] = 1;
    piece[3][3] = 1;
    piece[4][2] = 1;
    piece[4][3] = 1;
    break;
  case 4:
    if (rotation % 2 == 0) {
      // xX
      //  xx
      piece[3][2] = 1;
      piece[3][3] = 1;
      piece[4][3] = 1;
      piece[4][4] = 1;
    } else {
      //  x
      // xX
      // x
      piece[2][3] = 1;
      piece[3][2] = 1;
      piece[3][3] = 1;
      piece[4][2] = 1;
    }
    break;
  case 5:
    // xXx
    //  x
    piece[3][2] = 1;
    piece[3][3] = 1;
    piece[3][4] = 1;
    piece[4][3] = 1;
    for (int i = 0; i < rotation; i++) {
      rotate_piece(piece);
    }
    break;
  case 6:
    if (rotation % 2 == 0) {
      //  Xx
      // xx
      piece[3][3] = 1;
      piece[3][4] = 1;
      piece[4][2] = 1;
      piece[4][3] = 1;
    } else {
      // x
      // Xx
      //  x
      piece[2][3] = 1;
      piece[3][3] = 1;
      piece[3][4] = 1;
      piece[4][4] = 1;
    }
    break;
  }
}

static void send_deletes(int deletes) {
  for (int i = 0; i < deletes; i++) {
    tetris_send_delete();
  }
}

static void send_backspaces(int backspaces) {
  for (int i = 0; i < backspaces; i++) {
    tetris_send_backspace();
    curx--;
  }
}

static void send_goto_xy(int x, int y) {
  while (curx < x) {
    tetris_send_right();
    curx++;
  }
  while (curx > x) {
    tetris_send_left();
    curx--;
  }
  while (cury < y) {
    tetris_send_down();
    cury++;
  }
  while (cury > y) {
    tetris_send_up();
    cury--;
  }
}

static void draw_row(char c, const char oldrow[7], const char newrow[7], int x, int y) {
  char str[2] = { c, 0 };
  char row_is_del[7] = { 0 };
  int first = -1;
  int last = -1;
  for (int px = 0; px < 7; px++) {
    if (oldrow[px] && !newrow[px]) {
      row_is_del[px] = 1;
    }
    if (newrow[px] || oldrow[px]) {
      if (first == -1) first = px;
      last = px;
    }
  }

  if (first >= 0) {
    if (curx > x + last + 1) {
      send_goto_xy(x + last + 1, cury);
    }
    if (curx < x + first) {
      send_goto_xy(x + first, cury);
    }
    send_goto_xy(curx, y);
    send_deletes((x + last + 1) - curx);
    send_backspaces(curx - (x + first));
    for (int i = first; i <= last; i++) {
      if (row_is_del[i]) {
        tetris_send_string(".");
      } else {
        tetris_send_string(str);
      }
      curx++;
    }
  }
}

static void move_piece_from_to(char from[7][7], char to[7][7], int xadd, int yadd) {
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 7; x++) {
      if (x + xadd >= 0 && x + xadd < 7 && y + yadd >= 0 && y + yadd < 7) {
        to[y][x] = from[y + yadd][x + xadd];
      } else {
        to[y][x] = 0;
      }
    }
  }
}

static void draw_piece(char c, int x, int y, char oldpiece[7][7], char piece[7][7]) {
  for (int py = 0; py < 7; py++) {
    draw_row(c, oldpiece[py], piece[py], x, y + py);
  }
}

static void draw_piece_moved(char c, int x, int y, char piece[7][7], int oldxadd, int oldyadd) {
  move_piece_from_to(piece, temp_piece, oldxadd, oldyadd);
  draw_piece(c, x, y, temp_piece, piece);
}

static int is_piece_hitting(char board[20][10], char piece[7][7], int x, int y) {
  for (int py = 0; py < 7; py++) {
    for (int px = 0; px < 7; px++) {
      if (piece[py][px] &&
          (px + x >= 10 || px + x < 0
           || py + y >= 20 || py + y < 0
           || board[py + y][px + x])) {
        return 1;
      }
    }
  }
  return 0;
}

static void add_piece_to_board(char piece[7][7], char board[20][10], int x, int y) {
  for (int py = 0; py < 7; py++) {
    for (int px = 0; px < 7; px++) {
      if (piece[py][px]) {
        board[py + y][px + x] = piece[py][px];
      }
    }
  }
}

static void draw_board_line(void) {
  //send_string("l          l");
  tetris_send_string("l..........l");
  tetris_send_newline();
}
static void init(void) {
  for (int i = 0; i < 20; i++) {
    draw_board_line();
  }
  tetris_send_string("doooooooooob");
  curx = 12;
  cury = 20;
}

static int get_piece_min_y(char piece[7][7]) {
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 7; x++) {
      if (piece[y][x])
        return y;
    }
  }
  return 0;
}

static int clear_lines(char board[20][10]) {
  int cleared_lines = 0;
  for (int y = 19; y >= 0; y--) {
    char isfull = 1;
    for (int x = 0; x < 10; x++) {
      if (!board[y][x]) {
        isfull = 0;
      }
    }
    if (isfull) {
      // delete clear line
      send_goto_xy(12, y);
      send_backspaces(12); // delete line contents
      // delete newline
      tetris_send_backspace();
      cury--;
      curx = 12;
      cleared_lines++;
    } else {
      if (cleared_lines > 0) {
        // move cleared lines down on board
        for (int x = 0; x < 10; x++) {
          board[y + cleared_lines][x] = board[y][x];
        }
      }
    }
  }
  // clear cleared top lines
  for (int y = 0; y < cleared_lines; y++) {
    for (int x = 0; x < 10; x++) {
      board[y][x] = 0;
    }
  }
  if (cleared_lines > 0) {
    send_goto_xy(0, 0);
    for (int i = 0; i < cleared_lines; i++) {
      draw_board_line();
      curx = 0;
      cury++;
    }
  }
  return cleared_lines;
}

static uint8_t myrandom(uint8_t seed) {
  uint8_t out = seed >> 1;
  if (seed & 1) {
    out = out ^ 0xB8;
  }
  return out;
}

static char piece[7][7];
static char board[20][10];
static uint8_t r;
static int score;
static int x;
static int y;
static int shape;
static int rotation;
static int time;
static int next_down;
static int down_delay;
static int first_run;
static int game_over;

void tetris_start(uint8_t seed) {
  for (int y = 0; y < 20; y++) {
    for (int x = 0; x < 10; x++) {
      board[y][x] = 0;
    }
  }

  clear_piece(piece);

  init();

  game_over = 0;
  
  r = seed;
  score = 0;
  
  copy_piece_from_to(empty_piece, piece);
  x = 0;
  y = 0;
  shape = 0;
  rotation = 0;
  time = 0;
  next_down = 0;
  down_delay = -1;
  first_run = 1;
}

int tetris_tick(int ms_since_previous_tick) {
  if (game_over) {
    return 0;
  }
      
  time += ms_since_previous_tick;
  
  if (first_run || time > next_down) {
    if (first_run || is_piece_hitting(board, piece, x, y + 1)) {
      first_run = 0;
      add_piece_to_board(piece, board, x, y);

      score += clear_lines(board);

      down_delay = 500 - score * 10;
      if (down_delay < 100) {
        down_delay = 100;
      }
        
      rotation = 0;
      shape = r % 7;
      r = myrandom(r);
      set_piece(piece, shape, rotation);
      
      x = 1;
      y = - get_piece_min_y(piece);
      draw_piece_moved(get_shape_char(shape), 1 + x, y, piece, 0, 0);

      if (is_piece_hitting(board, piece, x, y)) {
        game_over = 1;
        send_goto_xy(12, 10);
        tetris_send_string(" game over");
        tetris_send_down();
        tetris_send_string(" score ");
        char tmp[10];
        sprintf(tmp, "%d", score);
        tetris_send_string(tmp);
        return 0;
      }
    } else {
      y++;
      draw_piece_moved(get_shape_char(shape), 1 + x, y, piece, 0, +1);
    }
    next_down = time + down_delay;
  } else {
      
    switch (tetris_get_keypress()) {
    case 1: { // up
      int oldrotation = rotation;
      rotation = (rotation + 1) % 4;
      copy_piece_from_to(piece, temp_piece);
      set_piece(piece, shape, rotation);
      if (is_piece_hitting(board, piece, x, y)) {
        rotation = oldrotation;
        set_piece(piece, shape, rotation);
      } else {
        draw_piece(get_shape_char(shape), 1 + x, y, temp_piece, piece);
      }
      break;
    }
    case 2: // left
      if (!is_piece_hitting(board, piece, x - 1, y)) {
        x--;
        draw_piece_moved(get_shape_char(shape), 1 + x, y, piece, -1, 0);
      }
      break;
    case 3: {// down
      int starty = y;
      while (!is_piece_hitting(board, piece, x, y + 1)) {
        y++;
      }

      draw_piece(get_shape_char(shape), x + 1, starty, piece, empty_piece);
      draw_piece(get_shape_char(shape), x + 1, y, empty_piece, piece);

      next_down = time + down_delay;
      break;
    }
    case 4: // right
      if (!is_piece_hitting(board, piece, x + 1, y)) {
        x++;
        draw_piece_moved(get_shape_char(shape), 1 + x, y, piece, 1, 0);
      }
      break;
    }
  }
  return 1;
}
