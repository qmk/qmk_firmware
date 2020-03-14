/* Copyright 2018-2019 Bottilabo <@bottilabo>
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

bool naginata_type(void);
void naginata_clear(void);

void naginata_mode(uint16_t, keyrecord_t *);

void naginata_on(void);
void naginata_off(void);
bool naginata_state(void);

bool process_naginata(uint16_t, keyrecord_t *);
void set_naginata(uint8_t);


void IM_NAGINATA_enable(uint8_t modef);
uint16_t naginata_transkeycode_keycode(uint16_t kc);

#ifndef NAGINATA_TERM
#define NAGINATA_TERM STKIN_TERM
#endif
    
#define IM_NAGINATA_PROC  if( ! process_naginata(keycode,record) ) return false;
