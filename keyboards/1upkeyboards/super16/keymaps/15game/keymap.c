/* Copyright 2020 Sam Reinehr
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
#include QMK_KEYBOARD_H
enum my_keycodes {
		 K00 = SAFE_RANGE,K01,
		 K02,
		 K03,
		 K04,
		 K05,
		 K06,
		 K07,
		 K08,
		 K09,
		 K10,
		 K11,
		 K12,
		 K13,
		 K14,
		 K15,
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_4x4( /* Base */
      K00,K01,K02,K03,
      K04,K05,K06,K07,
      K08,K09,K10,K11,
      K12,K13,K14,K15
  )
};
uint8_t current = 0;

const uint8_t r[16]=
  {0x00,
   0xFF,0xFF,0xFF,0xCC,0x66,
   0x00,0x00,0x00,0x00,0x00,
   0x00,0x66,0xCC,0xFF,0xFF};
const uint8_t g[16]=
  {0x00,
   0x00,0x66,0xCC,0xFF,0xFF,
   0xFF,0xFF,0xFF,0xCC,0x66,
   0x00,0x00,0x00,0x00,0x00};
const uint8_t b[16]=
  {0x00,
   0x00,0x00,0x00,0x00,0x00,
   0x00,0x66,0xCC,0xFF,0xFF,
   0xFF,0xFF,0xFF,0xCC,0x66};
uint8_t pos[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
uint8_t remap[16]={0,1,2,3,7,6,5,4,8,9,10,11,15,14,13,12};
void refresh_leds(void){
  for(uint8_t index = 0;index<16;++index){
    uint8_t j = pos[index];
    setrgb(r[j],g[j],b[j],(LED_TYPE*)&led[remap[index]]);
  }
  rgblight_set();
}
void keyboard_post_init_user(void){
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_enable_noeeprom();
  refresh_leds();
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t offset=keycode-K00;
  uint8_t x = offset & 0x03;
  uint8_t y = (offset & 0x0C)>>2;
  if((x>0 && 0==pos[offset-1])
     ||(y>0 && 0==pos[offset-4])
     ||(x<3 && 0==pos[offset+1])
     ||(y<3 && 0==pos[offset+4])){
    pos[current]=pos[offset];
    pos[offset]=0;
    current=offset;
  }
  refresh_leds();
  return false;
}
