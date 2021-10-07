/* Copyright 2021 @waffle#0007
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

#include "waffle.h"
#ifdef OLED_ENABLE
extern uint8_t num_keypresses = 0;
extern uint8_t current_frame = 0;
#endif

const uint16_t PROGMEM ru_combo[] = {KC_R, KC_U, COMBO_END};
const uint16_t PROGMEM gh_combo[] = {KC_G, KC_H, COMBO_END};
const uint16_t PROGMEM vm_combo[] = {KC_V, KC_M, COMBO_END};
const uint16_t PROGMEM cm_combo[] = {KC_C, KC_M, COMBO_END};
const uint16_t PROGMEM ty_combo[] = {KC_T, KC_Y, COMBO_END};
const uint16_t PROGMEM bn_combo[] = {KC_B, KC_N, COMBO_END};
const uint16_t PROGMEM fj_combo[] = {KC_F, KC_J, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM vb_combo[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM click_combo[] = {KC_X, KC_C, COMBO_END};
#ifdef OLED_ENABLE
const uint16_t PROGMEM flwr_combo[] = {KC_SPC, KC_ENT, COMBO_END};
#endif

combo_t key_combos[COMBO_COUNT] = {
#ifdef OLED_ENABLE
[FLWR_RESET] = COMBO_ACTION(flwr_combo),
#endif
[RU_ENT] = COMBO(ru_combo, KC_ENT),
[GH_QUOT] = COMBO(gh_combo, KC_QUOT),
[VM_QUES] = COMBO(vm_combo, KC_QUES),
[CM_DQUO] = COMBO(cm_combo, KC_DQUO),
[TY_COLN] = COMBO(ty_combo, KC_COLN),
[BN_UNDS] = COMBO(bn_combo, KC_UNDS),
[FJ_MINS] = COMBO(fj_combo, KC_MINS),
[CV_SCLN] = COMBO(cv_combo, KC_SCLN),
[DF_BTN1] = COMBO(df_combo, KC_BTN1),
[JK_BTN2] = COMBO(jk_combo, KC_BTN2),
[VB_WHD] = COMBO(vb_combo, KC_WH_U),
[NM_WHU] = COMBO(nm_combo, KC_WH_D),
[SD_MSD] = COMBO(sd_combo, KC_MS_D),
[KL_MSU] = COMBO(kl_combo, KC_MS_U),
[XC_CLICK] = COMBO_ACTION(click_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case XC_CLICK:
            if (pressed) {
                register_code(KC_TAB);
                register_code(KC_ENT);
                unregister_code(KC_TAB);
                unregister_code(KC_ENT);
                register_code(KC_ENT);
                unregister_code(KC_ENT);
            }
            break;

#ifdef OLED_ENABLE
        case FLWR_RESET:
            if (pressed) {
                num_keypresses = 0;
                current_frame = 0;
            }
            break;
#endif
    }
}
