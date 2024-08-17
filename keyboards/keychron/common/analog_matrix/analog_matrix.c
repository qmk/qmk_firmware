/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "analog_matrix.h"
#include "keymap_introspection.h"
#include "raw_hid.h"
#include "eeprom.h"
#include "eeprom_he.h"
#include "usb_main.h"
#include <stdio.h>
#include "profile.h"
#include "sqrt.h"
#include "game_controller_common.h"

#ifndef CAL_SAMPL_CNT
#    define CAL_SAMPL_CNT 8
#endif

#ifndef REF_ZERO_TRAVEL
#    define REF_ZERO_TRAVEL 3121
#endif
#ifndef REF_FULL_TRAVEL
#    define REF_FULL_TRAVEL 1940
#endif
#define REF_RANGE (REF_ZERO_TRAVEL - REF_FULL_TRAVEL)

#ifndef CONST_A1
#    define CONST_A1 426.88962
#endif
#ifndef CONST_B1
#    define CONST_B1 -0.48358
#endif
#ifndef CONST_C1
#    define CONST_C1 2.04637e-4
#endif
#ifndef CONST_D1
#    define CONST_D1 -2.99368e-8
#endif

#define TRAVEL_POLYNOMIAL(x) (CONST_A1 + CONST_B1 * x + CONST_C1 * x * x + CONST_D1 * x * x * x)

enum {
    CALIB_OFF = 0,
    CALIB_ZERO_TRAVEL_POWER_ON,
    CALIB_ZERO_TRAVEL_MANUAL,
    CALIB_FULL_TRAVEL_MANUAL,
    CALIB_SAVE_AND_EXIT,
    CALIB_CLEAR,
    CALIB_MAX,
};

enum {
    CALI_ZERO_TRAVEL = 0x01 << 0,
    CALI_FULL_TRAVEL = 0x01 << 1,
};

enum {
    AUTO_CALIB_OFF = 0,
    AUTO_CALIB_NEXT_LOOP,
    AUTO_CALIB_ZERO_TRAVEL,
    AUTO_CALIB_FULL_TRAVEL,
    AUTO_CALIB_FINISHED,
};

enum {
    AMC_GET_VERSION = 0x01,

    AMC_GET_PROFILES_INFO = 0x10,
    AMC_SELECT_PROFILE,
    AMC_GET_PROFILE_RAW,
    AMC_SET_PROFILE_NAME,
    AMC_SET_TRAVAL,
    AMC_SET_ADVANCE_MODE,
    AMC_CLEAR_PROFILE = 0x1E,
    AMC_SAVE_PROFILE  = 0x1F,

    AMC_GET_CURVE = 0x20,
    AMC_SET_CURVE,
    AMC_GET_GAME_CONTROLLER_MODE,
    AMC_SET_GAME_CONTROLLER_MODE,

    AMC_GET_REALTIME_TRAVEL = 0x30,

    AMC_CALIBRATE = 0x40,
    AMC_GET_CALIBRATE_STATE,
    AMC_GET_CALIBRATED_VALUE,
};

extern const matrix_row_t analog_matrix_mask[];

extern bool regular_trigger_action(analog_key_t *key);
extern bool okmc_action(analog_key_t *key);
extern bool rapid_trigger_action(analog_key_t *key);
extern bool toggle_action(analog_key_t *key);
extern bool xinput_update(analog_key_t *key);
extern bool joystick_update(analog_key_t *key);

static calibrated_value_t calib_values[MATRIX_ROWS][MATRIX_COLS];
static calibrated_value_t saved_calib_values[MATRIX_ROWS][MATRIX_COLS];
static analog_key_t       analog_key_matrix[MATRIX_ROWS][MATRIX_COLS];

static uint16_t      calibrate_values[MATRIX_ROWS][MATRIX_COLS][CAL_SAMPL_CNT];
static calibration_t auto_calib[MATRIX_ROWS][MATRIX_COLS];
static uint8_t       cali_state = CALIB_OFF;
static uint8_t       last_cali_state;
static uint8_t       cur_calib = 0;
traval_config_t      regular;
static float         scale_factor[MATRIX_ROWS][MATRIX_COLS];
static matrix_row_t  calib_state_matrix[MATRIX_ROWS];

uint8_t calibrated, rapid_actuation, rapid_sensitivity;

static uint32_t calib_ind_timer = 0;
static uint8_t  last_calib_row  = 0xFF;
static uint8_t  last_calib_col  = 0xFF;

uint32_t debug_interval = 0;

static uint8_t convert_to_travel(uint8_t row, uint8_t col, uint16_t value) {
#define DEAD_ZONE 30
    uint16_t travel;
    int16_t  delta = calib_values[row][col].zero_travel - DEAD_ZONE - value;

    if (delta < 0) delta = 0;

    calibrated_value_t *p_calib = &calib_values[row][col];

    int16_t offset = p_calib->zero_travel - REF_ZERO_TRAVEL;
    uint16_t x = value - offset;

    if (x > REF_ZERO_TRAVEL) x = REF_ZERO_TRAVEL;
    travel = (uint16_t)((TRAVEL_POLYNOMIAL(x) - TRAVEL_POLYNOMIAL(REF_ZERO_TRAVEL)) * scale_factor[row][col] * TRAVEL_SCALE + 0.5);
    if (travel > (FULL_TRAVEL_UNIT + 1) * TRAVEL_SCALE - 1) travel = (FULL_TRAVEL_UNIT + 1) * TRAVEL_SCALE - 1;

    return travel & 0xFF;
}

void update_key_config(uint8_t row, uint8_t col) {
    analog_key_t            *p_key;
    analog_key_config_t     *p_key_cfg;
    analog_matrix_profile_t *cur_prof = profile_get_current();

    p_key     = &analog_key_matrix[row][col];
    p_key_cfg = &cur_prof->key_config[row][col];
    // For debug purpose
    p_key->r = row;
    p_key->c = col;

    // Update basic mode
    if (p_key_cfg->mode == AKM_GLOBAL)
        p_key->mode = cur_prof->global.mode;
    else
        p_key->mode = p_key_cfg->mode;

    //  Override mode if advance mode setting exists
    if (p_key_cfg->adv_mode != 0) {
        p_key->mode = p_key_cfg->adv_mode;
    }

    // Update actuaction point
    if (p_key_cfg->act_pt == 0)
        p_key->regular.actn_pt = cur_prof->global.act_pt;
    else
        p_key->regular.actn_pt = p_key_cfg->act_pt;

    // Update deactuaction point
    p_key->regular.deactn_pt = p_key->regular.actn_pt - 3 > 0 ? p_key->regular.actn_pt - 3 : 0;

    // Update rapid trigger sensitivity
    if (p_key_cfg->rpd_trig_sen == 0)
        p_key->rpd_trig_sen = cur_prof->global.rpd_trig_sen;
    else
        p_key->rpd_trig_sen = p_key_cfg->rpd_trig_sen;

    // Update rapid trigger release sensitivity
    if (p_key_cfg->rpd_trig_sen_deact == 0)
        p_key->rpd_trig_sen_rls = cur_prof->global.rpd_trig_sen_deact == 0 ? cur_prof->global.rpd_trig_sen : cur_prof->global.rpd_trig_sen_deact;
    else
        p_key->rpd_trig_sen_rls = p_key_cfg->rpd_trig_sen_deact;

    /* Scale by TRAVEL_SCALE */
    p_key->regular.actn_pt *= TRAVEL_SCALE;
    p_key->regular.deactn_pt *= TRAVEL_SCALE;
    p_key->rpd_trig_sen *= TRAVEL_SCALE;
    p_key->rpd_trig_sen_rls *= TRAVEL_SCALE;

    // Update advance mode information
    if (p_key_cfg->adv_mode == AKM_DKS && p_key_cfg->okmc_idx < OKMC_COUNT) {
        p_key->okmc_idx = p_key_cfg->okmc_idx;
    } else if (p_key_cfg->adv_mode == AKM_GAMEPAD && p_key_cfg->js_axis < GC_BUTTON_MAX && p_key_cfg->js_axis != GC_MAX) {
        p_key->js_axis = p_key_cfg->js_axis;
    } else if (p_key_cfg->adv_mode == AKM_TOGGLE) {
        p_key->hold = 0;
    } else
        p_key_cfg->adv_mode = 0;
}

void update_travel_configs(void) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            update_key_config(r, c);
        }
    }
}

static void update_default_travel(void) {
    // clang-format off
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            if ((analog_matrix_mask[r] & (0x01<<c)) == 0) continue;

            if (saved_calib_values[r][c].zero_travel == 0)
                saved_calib_values[r][c].zero_travel = DEFAULT_ZERO_TRAVEL_VALUE;

            if (saved_calib_values[r][c].full_travel == 0)
                saved_calib_values[r][c].full_travel = saved_calib_values[r][c].zero_travel - DEFAULT_FULL_RANGE;
        }
    }
    // clang-format off
}

static inline void update_scale_factor(uint8_t row, uint8_t col) {
    calibrated_value_t *p_calib = &calib_values[row][col];

    if (calibrated | CALI_FULL_TRAVEL) {
        int16_t offset      = p_calib->zero_travel - REF_ZERO_TRAVEL;
        uint16_t x          = p_calib->full_travel - offset;

        float    full_travel = (TRAVEL_POLYNOMIAL(x) - TRAVEL_POLYNOMIAL(REF_ZERO_TRAVEL));
        scale_factor[row][col]   = FULL_TRAVEL_UNIT / full_travel;
    } else
        scale_factor[row][col] = 1.0f;

}

static void update_scale_factors(void) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            update_scale_factor(r, c);

        }
    }
}

static void save_calibration_value(uint8_t row, uint8_t col) {
    static uint8_t eeprom_calibrated;

    if (eeprom_calibrated != calibrated) {
        eeprom_calibrated = calibrated;
        he_eeprom_write_block(&calibrated, (void *)(EXTERNAL_EEPROM_OFFSET + OFFSET_CALIBRATION), 1);
    }

    uint32_t offset = (&saved_calib_values[row][col]-&saved_calib_values[0][0])* sizeof(saved_calib_values[0][0]);
    he_eeprom_write_block(&saved_calib_values[row][col], (void *)(EXTERNAL_EEPROM_OFFSET + CALIBRATED_CONFIG_START + offset), sizeof(saved_calib_values[0][0]));

    // Save a copy to emulated EEPROM
    if (!eeconfig_is_kb_datablock_valid()) eeprom_update_dword(EECONFIG_KEYBOARD, (EECONFIG_KB_DATA_VERSION));

    uint32_t addr = EECONFIG_BASE_SIZE + OFFSET_CALIBRATION;
    eeprom_update_byte((uint8_t *)addr, calibrated);

    addr = EECONFIG_BASE_SIZE + CALIBRATED_CONFIG_START + offset;
    eeprom_update_block(&saved_calib_values[row][col], (uint8_t *)addr, sizeof(saved_calib_values[0][0]));
}

static void save_calibration_values(void) {
    // Save to external EEPROM
    static uint8_t eeprom_calibrated;

    if (eeprom_calibrated != calibrated) {
        eeprom_calibrated = calibrated;
        he_eeprom_write_block(&calibrated, (void *)(EXTERNAL_EEPROM_OFFSET + OFFSET_CALIBRATION), 1);
    }

    he_eeprom_write_block(saved_calib_values, (void *)(EXTERNAL_EEPROM_OFFSET + CALIBRATED_CONFIG_START), sizeof(saved_calib_values));

    // Save a copy to emulate EEPROM
    if (!eeconfig_is_kb_datablock_valid()) eeprom_update_dword(EECONFIG_KEYBOARD, (EECONFIG_KB_DATA_VERSION));

    uint32_t addr = EECONFIG_BASE_SIZE + OFFSET_CALIBRATION;
    eeprom_update_byte((uint8_t *)addr, calibrated);

    addr = EECONFIG_BASE_SIZE + CALIBRATED_CONFIG_START;
    eeprom_update_block(saved_calib_values, (uint8_t *)addr, sizeof(saved_calib_values));

    update_default_travel();
    update_travel_configs();
    update_scale_factors();
}

static bool calibrate(void) {
    static uint32_t calib_timer = 0;

    if (cali_state == CALIB_OFF) return false;

    bool update = false;

    if (cali_state == CALIB_FULL_TRAVEL_MANUAL) {
        bool done = true;

        for (uint8_t r = 0; r < MATRIX_ROWS; r++)
            for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                if ((analog_matrix_mask[r] & (0x01<<c)) == 0) continue;

                uint32_t sum = 0;
                for (uint8_t i=0; i<CAL_SAMPL_CNT; i++) {
                    if (calibrate_values[r][c][cur_calib] > VALID_ANALOG_RAW_VALUE_MIN)
                        sum += calibrate_values[r][c][cur_calib];
                    else {
                        sum = 0;
                        break;
                    }
                }

                if (sum) {
                    uint16_t avg = sum/CAL_SAMPL_CNT;
                    // clang-format off
                    if ((calib_values[r][c].full_travel == 0 && avg < calib_values[r][c].zero_travel - DEFAULT_FULL_RANGE + 100) ||
                        (calib_values[r][c].full_travel != 0 && avg + BOTTOM_JITTER < calib_values[r][c].full_travel)) {
                        // clang-format on
                        saved_calib_values[r][c].zero_travel = calib_values[r][c].zero_travel;
                        saved_calib_values[r][c].full_travel = calib_values[r][c].full_travel = avg + BOTTOM_JITTER;

                        calib_state_matrix[r] |= (0x01 << c);
                        calib_ind_timer = timer_read32();
                        last_calib_row  = r;
                        last_calib_col  = c;
                    }
                }

                // Check if calibration is finished
                if (calib_values[r][c].full_travel == 0) {
                    done = false;
                }
            }

        if (++cur_calib >= CAL_SAMPL_CNT) cur_calib = 0;

        // Set the timer to delay exit calibrating so that we can get enough samples of last key
        if (done && calib_timer == 0) calib_timer = timer_read32();

        if (calib_timer && timer_elapsed32(calib_timer) > 3000) {
            calib_timer = 0;
            update      = true;
            calibrated |= CALI_FULL_TRAVEL;
            profile_indication_enable();
        }
        if (!update) return false;
    } else if (cali_state == CALIB_ZERO_TRAVEL_POWER_ON || cali_state == CALIB_ZERO_TRAVEL_MANUAL) {
        if (cur_calib + 1 < CAL_SAMPL_CNT) {
            ++cur_calib;
            return false;
        }

        bool valid = true;

        for (uint8_t r = 0; r < MATRIX_ROWS; r++)
            for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                if ((analog_matrix_mask[r] & (0x01 << c)) == 0) continue;

                uint32_t sum = 0;
                for (uint8_t i = 0; i < CAL_SAMPL_CNT; i++)
                    sum += calibrate_values[r][c][i];

                uint16_t avg_val = sum / CAL_SAMPL_CNT;

                // Check validity
                if (avg_val > VALID_ANALOG_RAW_VALUE_MAX || avg_val < DEFAULT_ZERO_TRAVEL_VALUE - DEFAULT_FULL_RANGE / 5) {
                    valid = false;
                    if (avg_val < DEFAULT_ZERO_TRAVEL_VALUE - DEFAULT_FULL_RANGE / 5 && cali_state == CALIB_ZERO_TRAVEL_POWER_ON) {
                        auto_calib[r][c].pressed = true;
                    }
                } else {
                    // new_calibrated_value[r][c] = avg_val;
                    avg_val -= ZERO_TRAVEL_DEAD_ZONE;
                    if (abs(avg_val - calib_values[r][c].zero_travel) > 30) {
                        auto_calib[r][c].new_calib_value = true;
                        // Update calibration value
                        calib_values[r][c].zero_travel = avg_val;

                        if (cali_state == CALIB_ZERO_TRAVEL_POWER_ON) calib_values[r][c].full_travel = avg_val - DEFAULT_FULL_RANGE;
                    }
                }
            }

        if (cali_state == CALIB_ZERO_TRAVEL_MANUAL) {
            cali_state = CALIB_FULL_TRAVEL_MANUAL;
        } else if (valid && (calibrated & CALI_ZERO_TRAVEL) == 0) {
            for (uint8_t r = 0; r < MATRIX_ROWS; r++)
                for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                    saved_calib_values[r][c].zero_travel = calib_values[r][c].zero_travel;
                }

            update = true;
        }

        if (valid)
            calibrated |= CALI_ZERO_TRAVEL;
        else
            cali_state = CALIB_OFF;
    } else if (cali_state == CALIB_SAVE_AND_EXIT) {
        if (last_cali_state == CALIB_FULL_TRAVEL_MANUAL) {
            update = true;
            for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
                for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                    if ((analog_matrix_mask[r] & (0x01 << c)) && calib_values[r][c].full_travel == 0) {
                        calib_values[r][c].full_travel = saved_calib_values[r][c].full_travel;
                    }
                }
            }
        }
        cali_state = CALIB_OFF;
    }

    if (update) {
        save_calibration_values();

        switch (cali_state) {
            case CALIB_ZERO_TRAVEL_POWER_ON:
            case CALIB_FULL_TRAVEL_MANUAL:
                cali_state = CALIB_OFF;
                break;

            default:
                break;
        }

    } else if (cali_state == CALIB_ZERO_TRAVEL_POWER_ON) {
        cali_state = CALIB_OFF;
    }

    return true;
}

void calibration_validate(void) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++)
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            if ((analog_matrix_mask[r] & (0x01 << c)) == 0) continue;

            if (saved_calib_values[r][c].zero_travel < DEFAULT_ZERO_TRAVEL_VALUE - DEFAULT_FULL_RANGE / 5) {
                saved_calib_values[r][c].zero_travel = DEFAULT_ZERO_TRAVEL_VALUE;
                saved_calib_values[r][c].full_travel = saved_calib_values[r][c].zero_travel - DEFAULT_FULL_RANGE;
            }
        }
}

void auto_calibration_init(void) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++)
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            memset(&auto_calib[r][c], 0, sizeof(auto_calib[0][0]));
        }
}

void auto_caliration_check(uint8_t row, uint8_t col, uint16_t value) {
    calibration_t *p = &auto_calib[row][col];

    switch (p->state) {
        case AUTO_CALIB_OFF:
            if (p->pressed) {
                if (value > DEFAULT_ZERO_TRAVEL_VALUE - DEFAULT_FULL_RANGE / 5) {
                    p->pressed = false;
                } else
                    return;
            }
            p->state      = AUTO_CALIB_NEXT_LOOP; // fall through
            p->confidence = 0;
            break;

        case AUTO_CALIB_NEXT_LOOP:
            if (value < AUTO_CALIB_FULL_TRAVEL_THRESHOLD_VALUE) {
                p->value.full_travel = value;
                p->state             = AUTO_CALIB_FULL_TRAVEL;
                p->full_travel_time  = timer_read32();
            }
            break;

        case AUTO_CALIB_ZERO_TRAVEL:
            if (value > p->value.zero_travel) {
                // Key continues releasing
                p->value.zero_travel = value;
                p->cycle             = 0;
            } else if (abs(p->value.zero_travel - value) <= AUTO_CALIB_ZERO_TRAVEL_JITTER_VALUE) {
                //  Add the data to buffer
                calibrate_values[row][col][p->cycle++] = value;
                if (p->cycle >= CAL_SAMPL_CNT) {
                    if (timer_elapsed32(p->full_travel_time) < AUTO_CALIB_VALID_RELASING_TIME) {
                        uint32_t avg_val = 0;
                        for (uint8_t i = 0; i < CAL_SAMPL_CNT; i++)
                            avg_val += calibrate_values[row][col][i];

                        avg_val /= CAL_SAMPL_CNT;
                        avg_val -= ZERO_TRAVEL_DEAD_ZONE;

                        p->value.zero_travel = avg_val;

                        // Update confidence
                        if (avg_val - p->value.full_travel > 1100) {
                            p->confidence += p->calibrated ? 12 : 6;
                        } else if (avg_val - p->value.full_travel > 1000) {
                            p->confidence += p->calibrated ? 4 : 3;
                        } else if (avg_val - p->value.full_travel > 900) {
                            p->confidence += p->calibrated ? 3 : 2;
                        }
                    }

                    p->state = AUTO_CALIB_NEXT_LOOP;
                }
            } else {
                p->state = AUTO_CALIB_NEXT_LOOP;
            }

            if (p->confidence >= 12) {
                p->state = AUTO_CALIB_FINISHED;

                if (abs(p->value.zero_travel - calib_values[row][col].zero_travel) > 10 || abs(p->value.full_travel + BOTTOM_JITTER - calib_values[row][col].full_travel) > 30) {
                    calib_values[row][col].zero_travel = p->value.zero_travel;
                    calib_values[row][col].full_travel = p->value.full_travel + BOTTOM_JITTER;

                    if (abs(saved_calib_values[row][col].zero_travel - calib_values[row][col].zero_travel) > 15 || abs(saved_calib_values[row][col].full_travel - calib_values[row][col].full_travel) > 50) {
                        /* Save */
                        saved_calib_values[row][col].zero_travel = calib_values[row][col].zero_travel;
                        saved_calib_values[row][col].full_travel = calib_values[row][col].full_travel;
                        save_calibration_value(row, col);
                    } else {
                        calib_values[row][col].full_travel = p->value.full_travel - 15;
                    }

                    update_default_travel();
                    update_travel_configs();
                    update_scale_factors();
                }
            }
            break;

        case AUTO_CALIB_FULL_TRAVEL:
            if (value < p->value.full_travel) {
                // Key continues pressing
                p->value.full_travel = value;
                p->full_travel_time  = timer_read32();
            } else if (value - p->value.full_travel <= AUTO_CALIB_FULL_TRAVEL_JITTER_VALUE) {
                // Key is still pressed, we encounter system noise value jitter, just update the time
                p->full_travel_time = timer_read32();
            } else if (value - p->value.full_travel > AUTO_CALIB_ZERO_TRAVEL_THRESHOLD_VALUE) {
                // Key releasing detected
                p->value.zero_travel = value;
                p->state             = AUTO_CALIB_ZERO_TRAVEL;
                p->cycle             = 0;
            }
            break;

        case AUTO_CALIB_FINISHED:
            if (value > p->value.zero_travel + 50) p->state = AUTO_CALIB_OFF;
            break;

        default:
            break;
    }
}

void analog_matrix_eeconfig_init(void) {
    bool reset_profiles = false;
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
        reset_profiles = true;
    }

    profile_init(reset_profiles);

    uint8_t *buf = (uint8_t *)malloc(EECONFIG_KB_DATA_SIZE);
    memset(buf, 0, EECONFIG_KB_DATA_SIZE);

    eeconfig_read_kb_datablock(buf);

    // Load curve points
    point_t curve[CURVE_POINTS_COUNT];
    memcpy(curve, buf + OFFSET_CURVE_PTS_START, CURVE_POINTS_COUNT * SIZE_OF_POINT_T);
    game_controller_curve_init(curve);
    game_controller_mode_init(buf[OFFSET_GAME_CONTROLLER_MODE_START]);

    // Load calibration data
    calibrated = buf[OFFSET_CALIBRATION];
    memset(calib_values, 0, sizeof(calib_values));
    memset(saved_calib_values, 0, sizeof(saved_calib_values));

    if (calibrated) {
        memcpy(saved_calib_values, buf + CALIBRATED_CONFIG_START, sizeof(saved_calib_values));
    } else {
        uint32_t buf;
        he_eeprom_read_block(&buf, 0, 4); // Magic number

        if (buf != VENDOR_ID) {
            he_eeprom_driver_erase();
            buf = VENDOR_ID;
            he_eeprom_write_block(&buf, 0, 4);
            // cali_state = CALIB_ZERO_TRAVEL;
        } else {
            he_eeprom_read_block(&calibrated, (void *)(EXTERNAL_EEPROM_OFFSET + OFFSET_CALIBRATION), 1);
            if (calibrated) {
                he_eeprom_read_block(saved_calib_values, (void *)(EXTERNAL_EEPROM_OFFSET + CALIBRATED_CONFIG_START), sizeof(calib_values));
                // Save to emulated EEPROM
                uint32_t addr = EECONFIG_BASE_SIZE + OFFSET_CALIBRATION;
                eeprom_update_byte((uint8_t *)addr, calibrated);

                addr = EECONFIG_BASE_SIZE + CALIBRATED_CONFIG_START;
                eeprom_update_block(saved_calib_values, (uint8_t *)addr, sizeof(saved_calib_values));
            }
        }
    }

    if (calibrated) {
        calibration_validate();
        update_default_travel();
    }
    memcpy(calib_values, saved_calib_values, sizeof(saved_calib_values));

    // Load actuation/deacuation dat
    memset(analog_key_matrix, 0, sizeof(analog_key_matrix));
    update_travel_configs();
    update_scale_factors();

    auto_calibration_init();
    cali_state = CALIB_ZERO_TRAVEL_POWER_ON;

    free(buf);
}

void analog_matrix_init(void) {
    he_eeprom_driver_init();

    analog_matrix_eeconfig_init();

    cur_calib = 0;
    memset(calibrate_values, 0, MATRIX_ROWS * MATRIX_COLS * CAL_SAMPL_CNT * sizeof(calibrate_values[0][0][0]));

    // 解决 boot magic 扫描无效, TODO: 这里会增加启动时间
    for (uint8_t i = 0; i < CAL_SAMPL_CNT; i++)
        matrix_scan();
}

bool update_raw_value(uint8_t row, uint8_t col, uint16_t value) {
    if (value < VALID_ANALOG_RAW_VALUE_MIN || value > VALID_ANALOG_RAW_VALUE_MAX) return false;

    if (cali_state) {
        calibrate_values[row][col][cur_calib] = value;
        analog_key_matrix[row][col].value     = value; // for debug
        return false;
    }
    auto_caliration_check(row, col, value);

    analog_key_t *k = &analog_key_matrix[row][col];

    if (abs(k->last_val - value) < 5) return false;

    k->last_val = value;
    k->value    = value;
    k->travel   = convert_to_travel(row, col, value);

    if (k->travel == k->last_travel) return false;

    k->last_travel = k->travel;

    bool ret = false;

    switch (k->mode) {
        case AKM_RAPID:
            ret = rapid_trigger_action(k);
            break;
        case AKM_DKS:
            ret = okmc_action(k);
            break;
        case AKM_GAMEPAD:
#if defined(XINPUT_ENABLE)
#    if defined(JOYSTICK_ENABLE)
            if (game_controller_xinput_enabled())
#    endif
                ret = xinput_update(k);

#    if defined(JOYSTICK_ENABLE)
            else
#    endif
#endif
#ifdef JOYSTICK_ENABLE
                ret = joystick_update(k);
#endif
            break;
        case AKM_TOGGLE:
            ret = toggle_action(k);
            break;
        default:
            ret = regular_trigger_action(k);
            break;
    }

    return ret;
}

uint8_t analog_matrix_get_key_mode(uint8_t row, uint8_t col) {
    return analog_key_matrix[row][col].mode;
}

bool analog_matrix_get_key_state(uint8_t row, uint8_t col) {
    analog_key_t *k = &analog_key_matrix[row][col];

    switch (k->mode) {
        case AKM_REGULAR: // fall through
            return (k->state == AKS_REGULAR_PRESSED);

        case AKM_RAPID:
            return (k->state == AKS_REGULAR_PRESSED || k->state == AKS_RAPID_PRESSED);

        case AKM_GAMEPAD:
            return (game_controller_type_enabled() && k->state == AKS_REGULAR_PRESSED);

        case AKM_TOGGLE:
            return k->hold;

        default:
            return false;
    }
}

uint16_t pos2actuation(uint8_t row, uint8_t col, uint8_t point) {
    return 2000;
}

bool set_calibrate(uint8_t *data) {
    uint8_t new_cali_state = data[0];

    switch (new_cali_state) {
        case CALIB_ZERO_TRAVEL_MANUAL:
            cali_state = data[0];
            cur_calib  = 0;
            memset(calibrate_values, 0, MATRIX_ROWS * MATRIX_COLS * CAL_SAMPL_CNT * sizeof(calibrate_values[0][0][0]));
            calib_ind_timer = 0;

            memset(calib_values, 0, sizeof(calib_values));
            memset(calib_state_matrix, 0, sizeof(calib_state_matrix));
            break;

        case CALIB_SAVE_AND_EXIT:
            if (cali_state == CALIB_ZERO_TRAVEL_MANUAL || cali_state == CALIB_FULL_TRAVEL_MANUAL) {
                last_cali_state = cali_state;
                cali_state      = data[0];
            }
            break;

        default:
            return false;
    }

    return true;
}

bool get_realtime_travel(uint8_t *data) {
    uint8_t             i   = 0;
    uint8_t             row = data[0];
    uint8_t             col = data[1];
    extern matrix_row_t raw_matrix[MATRIX_ROWS];

    if (row >= MATRIX_ROWS || col >= MATRIX_COLS) return false;

    data[i++] = analog_key_matrix[row][col].travel / TRAVEL_SCALE;
    data[i++] = analog_key_matrix[row][col].travel;
    data[i++] = analog_key_matrix[row][col].value & 0xFF;
    data[i++] = (analog_key_matrix[row][col].value >> 8) & 0xFF;
    data[i++] = calib_values[row][col].zero_travel & 0xFF;
    data[i++] = (calib_values[row][col].zero_travel >> 8) & 0xFF;
    data[i++] = calib_values[row][col].full_travel & 0xFF;
    data[i++] = (calib_values[row][col].full_travel >> 8) & 0xFF;
    data[i++] = raw_matrix[row] & (0x01 << col) ? 0x11 : 0x10;

    return true;
}

void analog_matrix_task(void) {
    calibrate();
    profile_indication_timer_check();
#ifdef JOYSTICK_ENABLE
    extern void joystick_task(void);
    joystick_task();
#endif
#ifdef XINPUT_ENABLE
    extern void xinput_task(void);
    xinput_task();
#endif
}

static void get_calibrate_state(uint8_t *data) {
    uint32_t rows[MATRIX_ROWS] = {0};

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        rows[r] = calib_state_matrix[r];
    }

    data[0] = calibrated;
    data[1] = cali_state;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++)
        memcpy(data + 2 + i * 3, &rows[i], 3);
}

static bool get_calibrated_value(uint8_t row, uint8_t col, uint8_t *data) {
    uint8_t i = 0;

    if (row == 0xFF && col == 0xFF) {
        data[i++] = MATRIX_ROWS;
        data[i++] = 0;
        data[i++] = MATRIX_COLS;
        data[i++] = 0;
    } else if (row >= MATRIX_ROWS || col >= MATRIX_COLS)
        return false;

    if (analog_matrix_mask[row] & (0x01 << col)) {
        data[i++] = saved_calib_values[row][col].zero_travel & 0xFF;
        data[i++] = (saved_calib_values[row][col].zero_travel >> 8) & 0xFF;
        data[i++] = saved_calib_values[row][col].full_travel & 0xFF;
        data[i++] = (saved_calib_values[row][col].full_travel >> 8) & 0xFF;
    } else {
        memset(data + i, 0, 4);
        i += 4;
    }
    memcpy(&data[i], &scale_factor[row][col], sizeof(float));
    i += sizeof(float);

    return true;
}

void analog_matrix_rx(uint8_t *data, uint8_t length) {
    if (data[0] != 0xA9) return;

    uint8_t cmd     = data[1];
    bool    success = true;

    switch (cmd) {
        case AMC_GET_VERSION:
            data[2] = KC_ANALOG_MATRIX_VERSION & 0xFF;
            break;

        case AMC_GET_PROFILES_INFO:
            data[2] = profile_get_current_index();
            data[3] = PROFILE_COUNT;
            data[4] = PROFILE_SIZE & 0xFF;
            data[5] = (PROFILE_SIZE >> 8) & 0xFF;
            break;

        case AMC_GET_PROFILE_RAW: {
            uint8_t  index  = data[2];
            uint16_t offset = (data[4] << 8) | data[3];
            uint8_t  size   = data[5];
            success         = profile_get_raw_data(index, offset, size, &data[6]);
        } break;

        case AMC_SET_PROFILE_NAME:
            success = profile_set_name(data[2], data[3], &data[4]);
            data[2] = success ? 0 : 1;
            break;

        case AMC_SELECT_PROFILE:
            success = profile_select(data[2], false);
            data[2] = success ? 0 : 1;
            break;

        case AMC_SET_TRAVAL: {
            uint8_t  profile               = data[2];
            uint8_t  mode                  = data[3];
            uint8_t  act_pt                = data[4];
            uint8_t  sens                  = data[5];
            uint8_t  rls_sens              = data[6];
            bool     entire                = data[7];
            uint32_t row_mask[MATRIX_ROWS] = {0};
            if (!entire) {
                for (uint8_t i = 0, j = 8; i < MATRIX_ROWS; i++, j += 3) {
                    memcpy(&row_mask[i], &data[j], 3);
                }
            }

            success = profile_set_traval(profile, mode, act_pt, sens, rls_sens, entire, row_mask);
            data[2] = success ? 0 : 1;
        } break;

        case AMC_SET_ADVANCE_MODE:
            success = profile_set_adv_mode(&data[2]);
            break;

        case AMC_GET_REALTIME_TRAVEL:
            success = get_realtime_travel(&data[2]);
            break;

        case AMC_SAVE_PROFILE:
            success = profile_save(data[2]);
            data[2] = success ? 0 : 1;
            break;

        case AMC_GET_CURVE:
            game_controller_get_curve(&data[2]);
            break;

        case AMC_SET_CURVE:
            success = game_controller_set_curve((point_t *)&data[2]);
            data[2] = success ? 0 : 1;
            break;

        case AMC_GET_GAME_CONTROLLER_MODE:
            success = game_controller_mode_get(&data[2]);
            data[2] = success ? 0 : 1;
            break;

        case AMC_SET_GAME_CONTROLLER_MODE:
            success = game_controller_mode_set(data[2]);
            break;

        case AMC_CALIBRATE:
            success = set_calibrate(&data[2]);
            data[2] = success ? 0 : 1;
            break;

        case AMC_GET_CALIBRATE_STATE:
            get_calibrate_state(&data[2]);
            break;

        case AMC_GET_CALIBRATED_VALUE:
            success = get_calibrated_value(data[2], data[3], &data[5]);
            data[4] = success ? 0 : 1;
            break;
    }

    raw_hid_send(data, length);
}

void analog_matrix_indicator(void) {
    if (cali_state == CALIB_FULL_TRAVEL_MANUAL) {
        rgb_matrix_set_color_all(255, 0, 150);

        for (uint8_t r = 0; r < MATRIX_ROWS; r++)
            for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                if ((analog_matrix_mask[r] & (0x01 << c)) == 0) continue;

                // clang-format off
                if (calib_state_matrix[r] & (0x01 << c)) {
                    // clang-format on
                    if (last_calib_row == r && last_calib_col == c && timer_elapsed32(calib_ind_timer) < 500) continue;

                    uint8_t index = g_led_config.matrix_co[r][c];
                    rgb_matrix_set_color(index, 0, 255, 0);
                }
            }
        return;
    }
    profile_indication();
}
