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
#ifndef TETRIS_TEXT_H
#define TETRIS_TEXT_H

//// to implement
void tetris_send_up(void);
void tetris_send_left(void);
void tetris_send_down(void);
void tetris_send_right(void);

void tetris_send_backspace(void);
void tetris_send_delete(void);

void tetris_send_string(const char *s);

void tetris_send_newline(void);

// return = meaning
// 0 = no keys pressed
// 1 = up
// 2 = left
// 3 = down
// 4 = right
int tetris_get_keypress(void);

//// to call
void tetris_start(uint8_t seed);
// returns 0 when game is over
int tetris_tick(int ms_since_previous_tick);

#endif
