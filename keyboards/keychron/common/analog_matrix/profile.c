/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
 
#include "quantum.h"
#include "keychron_common.h"
#include "analog_matrix.h"
#include "game_controller_common.h"

#ifdef ANANLOG_MATRIX
#    ifndef PROF_TRIG_KEY_ROW
#        define PROF_TRIG_KEY_ROW 2
#    endif

#    ifndef PROF_TRIG_KEY_COL
#        define PROF_TRIG_KEY_COL 10
#    endif

#    ifndef PROF_1_KEY_ROW
#        define PROF_1_KEY_ROW 4
#    endif

#    ifndef PROF_1_KEY_COL
#        define PROF_1_KEY_COL 2
#    endif

#    ifndef PROF_2_KEY_ROW
#        define PROF_2_KEY_ROW 4
#    endif

#    ifndef PROF_2_KEY_COL
#        define PROF_2_KEY_COL 3
#    endif

#    ifndef PROF_3_KEY_ROW
#        define PROF_3_KEY_ROW 4
#    endif

#    ifndef PROF_3_KEY_COL
#        define PROF_3_KEY_COL 4
#    endif

#    define KEY_MASK(r, c) (virtual_matrix[r] & (1 << c))

enum {
    ADV_MODE_CLEAR = 0,
    ADV_MODE_OKMC,
    ADV_MODE_GAME_CONTROLLER,
    ADV_MODE_TOGGLE,
};

extern uint8_t            profile_gobal_mode[PROFILE_COUNT];
extern uint16_t           default_profiles[PROFILE_COUNT][MATRIX_ROWS][MATRIX_COLS];

static analog_matrix_profile_t  profile[PROFILE_COUNT];
static uint8_t                  current_profile_index;
static analog_matrix_profile_t *cur_prof   = &profile[0]; // current profile
uint8_t                         prof_combo = 0;
static uint8_t  prof_ind_state = 0;
static uint32_t pro_ind_timer  = 0;

void profile_init(bool reset) {
    if (reset) {
        // Write default profile setting
        for (uint8_t i = 0; i < PROFILE_COUNT; i++) {
            memset(&profile[i], 0, sizeof(profile[0]));
            // Default setting
            profile[i].global.mode               = profile_gobal_mode[i];
            profile[i].global.act_pt             = DEFAULT_ACTUATION_POINT;
            profile[i].global.rpd_trig_sen_deact = profile[i].global.rpd_trig_sen = DEFAULT_RAPID_TRIGGER_SENSITIVITY;

            for (uint8_t r = 0; r < MATRIX_ROWS; r++)
                for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                    profile[i].key_config[r][c].mode     = default_profiles[i][r][c] & 0x3;
                    profile[i].key_config[r][c].adv_mode = (default_profiles[i][r][c] >> 2) & 0x07;
                    if (profile[i].key_config[r][c].adv_mode == AKM_GAMEPAD) {
                        profile[i].key_config[r][c].js_axis = default_profiles[i][r][c] >> 5;
                    }
                }

            uint32_t addr = EECONFIG_BASE_SIZE + OFFSET_PROFILES_START + i * sizeof(analog_matrix_profile_t);
            eeprom_update_block(&profile[i], (uint8_t *)addr, sizeof(profile[0]));
        }
    } else {
        uint8_t *buf = (uint8_t *)malloc(EECONFIG_KB_DATA_SIZE);
        memset(buf, 0, EECONFIG_KB_DATA_SIZE);

        eeconfig_read_kb_datablock(buf);

        current_profile_index = buf[OFFSET_CURRENT_PROFILE];
        if (current_profile_index >= PROFILE_COUNT) current_profile_index = 0;

        cur_prof = &profile[current_profile_index];

        // Load profile data
        memcpy(profile, buf + OFFSET_PROFILES_START, PROFILE_SIZE * PROFILE_COUNT);

        for (uint8_t i = 0; i < PROFILE_COUNT; i++) {
            if (profile[i].global.mode == 0) profile[i].global.mode = profile_gobal_mode[i]; // global mode can't be 0

            // Resotre to default if not in valid range
            if (profile[i].global.act_pt == 0 || profile[i].global.act_pt > 40) profile[i].global.act_pt = DEFAULT_ACTUATION_POINT;
            if (profile[i].global.rpd_trig_sen == 0 || profile[i].global.rpd_trig_sen > 39) profile[i].global.rpd_trig_sen = DEFAULT_RAPID_TRIGGER_SENSITIVITY;
            if (profile[i].global.rpd_trig_sen_deact == 0 || profile[i].global.rpd_trig_sen > 39) profile[i].global.rpd_trig_sen_deact = profile[i].global.rpd_trig_sen;
        }

        free(buf);
    }
}

analog_matrix_profile_t *profile_get(uint8_t index) {
    return &profile[index];
}

analog_matrix_profile_t *profile_get_current(void) {
    return cur_prof;
}

uint8_t profile_get_current_index(void) {
    return current_profile_index;
}

bool profile_select(uint8_t prof_idx, bool indication) {
    if (prof_idx >= PROFILE_COUNT) return false;

    if (prof_idx != current_profile_index) {
        current_profile_index = prof_idx;

        cur_prof = &profile[prof_idx];
        update_travel_configs();

        eeprom_update_dword(EECONFIG_KEYBOARD, (EECONFIG_KB_DATA_VERSION));
        uint32_t addr = EECONFIG_BASE_SIZE + OFFSET_CURRENT_PROFILE;
        eeprom_update_block(&prof_idx, (uint8_t *)addr, 1);
    }
    if (indication) {
#    ifdef LED_MATRIX_ENABLE
        if (!led_matrix_is_enabled()) led_matrix_enable_noeeprom();
#    endif
#    ifdef RGB_MATRIX_ENABLE
        if (!rgb_matrix_is_enabled()) rgb_matrix_enable_noeeprom();
#    endif
        pro_ind_timer  = timer_read32();
        prof_ind_state = 0x86;
    }

    return true;
}

bool profile_get_raw_data(uint8_t prof_idx, uint16_t offset, uint8_t size, uint8_t *data) {
    if (prof_idx >= PROFILE_COUNT || offset + size > sizeof(profile)) return false;

    memset(data, 0, size);
    
    if (offset + size > PROFILE_SIZE) size = PROFILE_SIZE - offset;
    memcpy(data, (uint8_t *)(&profile[prof_idx]) + offset, size);
    
    return true;
}

bool profile_set_traval(uint8_t prof_idx, uint8_t mode, uint8_t act_pt, uint8_t sens, uint8_t rls_sens, bool global, uint32_t row[]) {

    analog_matrix_profile_t *prof = profile_get(prof_idx);

    // Check validity
    if (prof_idx >= PROFILE_COUNT || mode > AKM_RAPID || act_pt < 0 || act_pt > 39 || (global && mode == AKM_GLOBAL)) return false;

    if (global) {
        prof->global.mode               = mode;
        prof->global.act_pt             = act_pt;
        prof->global.rpd_trig_sen       = sens;
        prof->global.rpd_trig_sen_deact = rls_sens;
        memset(row, 0xFF, sizeof(row[0]) * MATRIX_ROWS);
    } else {
        for (uint8_t r = 0; r < MATRIX_ROWS; r++)
            for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                if (row[r] & (0x01 << c)) {
                    prof->key_config[r][c].mode   = mode;
                    prof->key_config[r][c].act_pt = act_pt;
                    prof->key_config[r][c].rpd_trig_sen       = sens;
                    prof->key_config[r][c].rpd_trig_sen_deact = rls_sens;

                    if (prof_idx == profile_get_current_index()) update_key_config(r, c);
                }
            }
    }

    return true;
}

bool profile_set_adv_mode(uint8_t *data) {
    uint8_t prof_idx = data[0];
    if (prof_idx >= PROFILE_COUNT) return false;

    uint8_t mode  = data[1];
    uint8_t row   = data[2];
    uint8_t col   = data[3];
    uint8_t index = data[4];

    if (row >= MATRIX_ROWS || col >= MATRIX_COLS) return false;

    okmc_config_t okmc_config;
    memset(&okmc_config, 0, sizeof(okmc_config));
    analog_matrix_profile_t *prof = profile_get(prof_idx);
    analog_key_config_t *p_key_cfg = &prof->key_config[row][col];

    switch (mode) {
        case ADV_MODE_CLEAR:
            p_key_cfg->adv_mode      = 0;
            p_key_cfg->adv_mode_data = 0;
            break;

        case ADV_MODE_OKMC:
            if (index >= OKMC_COUNT) return false;

            okmc_config.travel.shallow_act   = data[5];
            okmc_config.travel.shallow_deact = data[6];
            okmc_config.travel.deep_act      = data[7];
            okmc_config.travel.deep_deact    = data[8];
            memcpy(okmc_config.keycode, &data[9], sizeof(okmc_config.keycode));
            memcpy(okmc_config.action, &data[17], sizeof(okmc_config.action));

            prof->okmc[index]    = okmc_config;
            p_key_cfg->adv_mode = AKM_DKS;
            p_key_cfg->okmc_idx  = index;
            break;

        case ADV_MODE_GAME_CONTROLLER:
            if (index >= GC_BUTTON_MAX) return false;

            p_key_cfg->adv_mode = AKM_GAMEPAD;
            p_key_cfg->js_axis  = index;
            break;

        case ADV_MODE_TOGGLE:
            p_key_cfg->adv_mode      = AKM_TOGGLE;
            p_key_cfg->adv_mode_data = 0;
            break;

        default:
            return false;
    }

    if (prof_idx == profile_get_current_index()) update_key_config(row, col);

    return true;
}

bool profile_save(uint8_t prof_index) {
    if (prof_index >= PROFILE_COUNT) return false;

    analog_matrix_profile_t *prof = &profile[prof_index];
    uint32_t addr = EECONFIG_BASE_SIZE + OFFSET_PROFILES_START + prof_index * sizeof(analog_matrix_profile_t);
    
    if (!eeconfig_is_kb_datablock_valid()) eeprom_update_dword(EECONFIG_KEYBOARD, (EECONFIG_KB_DATA_VERSION));
    eeprom_update_block(prof, (uint8_t *)addr, sizeof(analog_matrix_profile_t));

    return true;
}

void process_profile_select_combo(void) {
    extern matrix_row_t virtual_matrix[MATRIX_ROWS];

    if (prof_combo & KEY_PRESS_FN) {
        if ((prof_combo & KEY_PRESS_P) == 0 && KEY_MASK(PROF_TRIG_KEY_ROW, PROF_TRIG_KEY_COL)) {
            prof_combo |= KEY_PRESS_P;
        } else if ((prof_combo & KEY_PRESS_P) && KEY_MASK(PROF_TRIG_KEY_ROW, PROF_TRIG_KEY_COL) == 0) {
            prof_combo &= ~KEY_PRESS_P;
        }

        if ((prof_combo & KEY_PRESS_PROF_COMBO) == KEY_PRESS_PROF_COMBO) {
            if (KEY_MASK(PROF_1_KEY_ROW, PROF_1_KEY_COL)) {
                profile_select(0, true);
            } else if (KEY_MASK(PROF_2_KEY_ROW, PROF_2_KEY_COL)) {
                profile_select(1, true);
            } else if (KEY_MASK(PROF_3_KEY_ROW, PROF_3_KEY_COL)) {
                profile_select(2, true);
            }
        }
    }
}

bool profile_set_name(uint8_t prof_idx, uint8_t len, uint8_t *name) {
    if (prof_idx >= PROFILE_COUNT || len > 28) return false;

    memset(profile[prof_idx].name, 0, PROFILE_NAME_LEN);
    memcpy(profile[prof_idx].name, name, len);

    return true;
}

bool process_record_profile(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PROF1:
        case PROF2:
        case PROF3:
            if (record->event.pressed) profile_select(keycode - PROF1, true);
            return false;  // Skip all further processing of this key

        case MO(0)... MO(15):
            if (record->event.pressed)
                prof_combo |= KEY_PRESS_FN;
            else
                prof_combo &= ~KEY_PRESS_FN;
            break;

        default:
            break;
    }

    return true;
}

void profile_indication_enable(void) {
    pro_ind_timer  = timer_read32();
    prof_ind_state = 1;
}

void profile_indication_timer_check(void) {
    if (pro_ind_timer && timer_elapsed32(pro_ind_timer) > 500) {
        if ((prof_ind_state++ & 0xF) > 6) {
            pro_ind_timer = prof_ind_state = 0;

#ifdef LED_MATRIX_ENABLE
            if (!led_matrix_is_enabled()) led_matrix_disable_noeeprom();
#endif
#ifdef RGB_MATRIX_ENABLE
            eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config));
            if (!rgb_matrix_config.mode) {
                eeconfig_update_rgb_matrix_default();
            }

            if (!rgb_matrix_is_enabled()) rgb_matrix_disable_noeeprom();
#endif
        } else {
            pro_ind_timer = timer_read32();
        }
    }
}

void profile_indication(void) {
    if (prof_ind_state) {
        static uint8_t prof_led_list[3] = PROFILE_LED_MATRIX_LIST;
        rgb_matrix_set_color_all(prof_ind_state % 2 ? 0 : 255, 0, 0);
        if (prof_ind_state & 0x80) {
            rgb_matrix_set_color(prof_led_list[current_profile_index], prof_ind_state % 2 ? 0 : 255, prof_ind_state % 2 ? 0 : 255, prof_ind_state % 2 ? 0 : 255);
        }
    }
}
#endif
