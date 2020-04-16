/*
Copyright 2019 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "keycode.h"
#include "keycode_str_converter.h"
#include "config_file_util.h"

#include "bmp_extended_keycode_converter.h"
#include "bmp_custom_keycode.h"

void json_to_keymap_init(json_keymap_convert_inst_t* const inst, uint16_t* keymap, uint32_t keymap_len) {
    inst->keymap     = keymap;
    inst->keymap_idx = 0;
    inst->keymap_len = keymap_len;
    inst->locale     = LOCALE_US;
    memset(inst->tail, 0, sizeof(inst->tail));
    memset(inst->layout_name, 0, sizeof(inst->layout_name));
}

static uint16_t register_ex_kc(json_keymap_convert_inst_t* const inst, bmp_ex_keycode_t const* const ek) {
    for (int idx = 0; idx < BMP_EX_KC_LEN; idx++) {
        if (inst->bmp_ek[idx].byte[0] == 0) {
            memcpy(&inst->bmp_ek[idx], ek, sizeof(bmp_ex_keycode_t));
            return EXKC_START + idx;
        } else if (memcmp(&inst->bmp_ek[idx], ek, sizeof(bmp_ex_keycode_t)) == 0) {
            return EXKC_START + idx;
        }
    }

    return KC_NO;
}

int32_t get_val_string(const char* json, const char* key, const char** val, uint32_t* len);

// Return quantum keycode from json strings.
// inst->tail contains partial string if quotation is not closed
int32_t json_to_keymap_conv(json_keymap_convert_inst_t* const inst, const char* json) {
    const char* str;
    const char* str2;
    const char* str3;
    uint32_t    name_len;
    uint32_t    layout_name_len;

    inst->ek_num = 0;

    if ((inst->keymap_idx == 0) && inst->tail[0] == '\0') {
        str = strstr(json, "\"keyboard\"");
        if (str != NULL) {
            get_val_string(str, "keyboard", &str2, &name_len);
            if (name_len + 1 < 32) {
                strncat(inst->layout_name, str2, name_len);
                strcat(inst->layout_name, ":");
            }
        }

        str = strstr(json, "\"layout\"");
        if (str != NULL) {
            get_val_string(str, "layout", &str2, &layout_name_len);
            if (layout_name_len == 0 && name_len + 1 + 6 < LAYOUT_NAME_MAXLEN) {
                strcat(inst->layout_name, "LAYOUT");
            } else if (name_len + layout_name_len + 1 < LAYOUT_NAME_MAXLEN) {
                strncat(inst->layout_name, str2, layout_name_len);
                inst->layout_name[name_len + layout_name_len + 1] = '\0';
            }
        } else {
            strcat(inst->layout_name, "LAYOUT");
        }

        str = strstr(json, "\"layers\"");
        if (str == NULL) {
            return 1;
        }
        str = strstr(str, "[");
        str = strstr(str + 1, "[");
    } else if (inst->tail[0] != '\0') {
        str2 = strchr(json, '\"');
        if (str2 == NULL) {
            return 1;
        }
        strncat(inst->tail, json, sizeof(inst->tail) - strlen(inst->tail) - 1);
        str3 = inst->tail;
        do {
            str3 = strchr(str3 + 1, '\"');  // skip first dbqt and search
        } while ((*(str3 - 1) == '\\') && (*(str3 - 2) != '\\'));
        uint16_t kc = str2quantum_keycode_locale(inst->tail + 1, str3 - inst->tail - 1,
                                                 inst->locale);  // skip "

        if (inst->keymap_idx >= inst->keymap_len) {
            return 1;
        }
        inst->keymap[inst->keymap_idx++] = kc;

        str = str2 + 1;
    } else {
        str = json;
    }

    if (str == NULL) {
        return 1;
    }

    while (1) {
        str = strchr(str, '\"');  // find first double quotation
        if (str == NULL) {
            inst->tail[0] = '\0';
            break;
        }
        str++;

        str2 = str - 1;
        do {
            str2 = strchr(str2 + 1, '\"');
            if (str2 == NULL) {
                break;
            }
        } while ((*(str2 - 1) == '\\') && (*(str2 - 2) != '\\'));

        if (str2 == NULL) {
            strncpy(inst->tail, str - 1, sizeof(inst->tail));
            break;
        }

        uint16_t kc = str2quantum_keycode_locale(str, str2 - str, inst->locale);

        if (kc == EXKC_START) {
            bmp_ex_keycode_t ek;
            str2bmp_ex_keycode_locale(&ek, str, str2 - str, inst->locale);
            kc = register_ex_kc(inst, &ek);
            if (kc != KC_NO) {
                inst->ek_num = inst->ek_num > (kc - EXKC_START + 1) ? inst->ek_num : (kc - EXKC_START + 1);
            }
        }

        if (kc == KC_NO && memcmp(str, "author", 6) == 0) {
            // layer array is closed. stop parsing
            return 0;
        }

        if (inst->keymap_idx >= inst->keymap_len) {
            return 1;
        }

        inst->keymap[inst->keymap_idx++] = kc;
        str                              = str2 + 1;
    }

    return 0;
}

void keymap_to_json_init(keymap_json_convert_inst_t* const inst, const uint16_t* keymap, uint32_t keymap_len) {
    inst->keymap     = keymap;
    inst->keymap_idx = 0;
    inst->keymap_len = keymap_len;
    inst->locale     = LOCALE_US;
    inst->use_ascii  = 0;
}

#define PUT_TAIL_AND_RETURN(inst, str, len) \
    {}

void keymap_to_json_conv(keymap_json_convert_inst_t* const inst, char* json, uint32_t len, uint32_t key_num) {
    char*   dst = json;
    char    str[64];
    uint8_t key_strlen;
    for (; inst->keymap_idx < inst->keymap_len; inst->keymap_idx++) {
        uint16_t kc = inst->keymap[inst->keymap_idx];
        if (EXKC_START <= kc && kc <= EXKC_END) {
            key_strlen = bmp_ex_keycode2str_locale(&inst->bmp_ek[kc - EXKC_START], str, sizeof(str), inst->locale, inst->use_ascii);
        } else {
            key_strlen = quantum_keycode2str_locale(inst->keymap[inst->keymap_idx], str, sizeof(str), inst->locale, inst->use_ascii);
        }

        if (key_strlen + 6 > len) {
            break;
        } else {
            len -= key_strlen + 2;
        }

        if (inst->keymap_idx % (key_num) == 0) {
            if (inst->keymap_idx == 0) {
                *(dst++) = '[';
                *(dst++) = '[';
                len -= 2;
            } else {
                *(dst++) = ']';
                *(dst++) = ',';
                *(dst++) = '[';
                len -= 3;
            }
        }

        *(dst++) = '\"';
        for (int i = 0; i < key_strlen; i++) {
            *(dst++) = str[i];
        }
        *(dst++) = '\"';
        if ((inst->keymap_idx + 1) % (key_num) != 0) {
            *(dst++) = ',';
            len--;
        }
    }
    if (len) {
        if (inst->keymap_idx < inst->keymap_len) {
            memset(dst, ' ', len);
        } else {
            *(dst++) = ']';
            *(dst++) = ']';
            memset(dst, '\0', len - 2);
        }
    }
}

void keymap_to_json_conv_layout(keymap_json_convert_inst_t* const inst, char* json, uint32_t len, uint8_t const* const layout) {
    char*          dst = json;
    char           str[64];
    uint8_t        key_strlen;
    const uint8_t* matrix_pos = layout;
    uint16_t       kc;
    for (; inst->keymap_idx < inst->keymap_len; inst->keymap_idx++, matrix_pos++) {
        kc = inst->keymap[inst->keymap_idx];
        if (EXKC_START <= kc && kc <= EXKC_END) {
            key_strlen = bmp_ex_keycode2str_locale(&inst->bmp_ek[kc - EXKC_START], str, sizeof(str), inst->locale, inst->use_ascii);
        } else {
            key_strlen = quantum_keycode2str_locale(kc, str, sizeof(str), inst->locale, inst->use_ascii);
        }
        if (key_strlen + 7 > len) {
            break;
        } else {
            len -= key_strlen + 2;
        }
        if (inst->keymap_idx == 0) {
            *(dst++) = '[';
            *(dst++) = '[';
            len -= 2;
        }
        if (*matrix_pos == 0xFF) {
            {
                strcpy(dst, "],\r\n\r\n[");
                dst += 7;
                len -= 7;
                matrix_pos = layout;
            }
        }

        *(dst++) = '\"';
        for (int i = 0; i < key_strlen; i++) {
            *(dst++) = str[i];
        }
        *(dst++) = '\"';
        if (*(matrix_pos + 1) != 0xFF) {
            *(dst++) = ',';
            len--;
        }
        if (*(matrix_pos + 1) == 0x00) {
            *(dst++) = '\r';
            len--;
            *(dst++) = '\n';
            len--;
            matrix_pos++;  // skip zero
        }
    }
    if (len) {
        if (inst->keymap_idx < inst->keymap_len) {
            memset(dst, ' ', len);
        } else {
            *(dst++) = ']';
            *(dst++) = ']';
            memset(dst, '\0', len - 2);
        }
    }
}

int32_t get_val_string(const char* json, const char* key, const char** val, uint32_t* len) {
    const char* str;
    const char* str2;
    if (key != NULL) {
        str = strstr(json, key);
        if (str == NULL) {
            // key is not found
            return 1;
        }
        str += strlen(key) + 1;
    } else {
        str = json;
    }

    str = strchr(str, '\"');
    if (str == NULL) {
        // key is not found
        return 1;
    }

    str++;  // skip dqt
    str2 = str - 1;
    do {
        str2 = strchr(str2 + 1, '\"');
        if (str2 == NULL) {
            // quotation is not closed
            return 1;
        }
    } while (*(str2 - 1) == '\\');

    *len = str2 - str;
    *val = str;

    return 0;
}

int32_t get_val_int(const char* json, const char* key, int32_t* const val) {
    char* str;
    char* str2;
    str = strstr(json, key);
    if (str == NULL) {
        // key is not fount
        return 1;
    }
    str += strlen(key) + 1;
    str = strchr(str, ':') + 1;

    // skip space
    while (*str == ' ' || *str == '\t') {
        str++;
    }

    str2 = str;
    for (;; str2++) {
        if (*str2 >= '0' && *str2 <= '9') {
            continue;
        } else if (*str2 == '\0') {
            // incomplete number string
            return 1;
        } else {
            break;
        }
    }

    *val = atoi(str);

    return 0;
}

int32_t get_val_u8(const char* json, const char* key, uint8_t* const val) {
    int32_t int_val, res;
    res  = get_val_int(json, key, &int_val);
    *val = int_val;
    return res;
}

int32_t get_val_u8array(const char* json, const char* key, uint8_t* array, uint32_t* const len) {
    char* str;
    char* str2;

    str = strstr(json, key);
    if (str == NULL) {
        // key is not found
        return 1;
    }
    str += strlen(key) + 1;
    str  = strchr(str, '[') + 1;
    str2 = strchr(str, ']');

    if (str2 == NULL) {
        // array is not closed
        return 1;
    }

    int32_t idx = 0;
    for (idx = 0; str < str2 && idx < *len && str != NULL; idx++) {
        array[idx] = atoi(str);
        str        = strchr(str, ',') + 1;
    }

    *len = idx;

    return 0;
}

void json_to_config_conv_inst_init(json_config_convert_inst_t* const inst, bmp_api_config_t* const config) {
    inst->config = config;
    memset(inst->config, 0, sizeof(*inst->config));
    memset(inst->tail, 0, sizeof(inst->tail));
}

#define SEEK_KEY(str, key)      \
    {                           \
        str = strstr(str, key); \
        if (str != NULL) {      \
            str += strlen(key); \
        }                       \
    }

#define SEEK_KEY_OR_RETURN(str, key) \
    {                                \
        str = strstr(str, key);      \
        if (str == NULL) {           \
            return 1;                \
        }                            \
    }

int32_t json_to_config_conv(json_config_convert_inst_t* const inst, const char* json) {
    const char* str;
    const char* string_val;
    uint32_t    len = 0;
    int32_t     res;

    str = strstr(json, "config");
    if (str == NULL) {
        return 1;
    }

    SEEK_KEY_OR_RETURN(str, "version");
    get_val_int(str, "version", (int32_t*)&inst->config->version);
    SEEK_KEY_OR_RETURN(str, "device_info");
    res = get_val_string(str, "vid", &string_val, &len);
    if (res) {
        return 1;
    }
    str                           = string_val;
    inst->config->device_info.vid = strtol(string_val + 2, NULL, 16);  // skip "

    res = get_val_string(str, "pid", &string_val, &len);
    if (res) {
        return 1;
    }
    str                           = string_val;
    inst->config->device_info.pid = strtol(string_val + 2, NULL, 16);  // skip "

    res = get_val_string(str, "name", &string_val, &len);
    if (res) {
        return 1;
    }
    str = string_val;
    strncpy(inst->config->device_info.name, string_val, len);

    res = get_val_string(str, "manufacture", &string_val, &len);
    if (res) {
        return 1;
    }
    str = string_val;
    strncpy(inst->config->device_info.manufacture, string_val, len);

    res = get_val_string(str, "description", &string_val, &len);
    if (res) {
        return 1;
    }
    str = string_val;
    strncpy(inst->config->device_info.description, string_val, len);

    SEEK_KEY_OR_RETURN(str, "matrix");
    res = get_val_u8(str, "rows", &inst->config->matrix.rows);
    if (res) {
        return 1;
    }
    res = get_val_u8(str, "cols", &inst->config->matrix.cols);
    if (res) {
        return 1;
    }
    res = get_val_u8(str, "device_rows", &inst->config->matrix.device_rows);
    if (res) {
        return 1;
    }
    res = get_val_u8(str, "device_cols", &inst->config->matrix.device_cols);
    if (res) {
        return 1;
    }
    res = get_val_u8(str, "debounce", &inst->config->matrix.debounce);
    if (res) {
        return 1;
    }
    res = get_val_u8(str, "is_left_hand", &inst->config->matrix.is_left_hand);
    if (res) {
        return 1;
    }
    res = get_val_u8(str, "diode_direction", &inst->config->matrix.diode_direction);
    if (res) {
        return 1;
    }
    len = sizeof(inst->config->matrix.row_pins);
    res = get_val_u8array(str, "row_pins", inst->config->matrix.row_pins, &len);
    if (res) {
        return 1;
    }
    len = sizeof(inst->config->matrix.col_pins);
    res = get_val_u8array(str, "col_pins", inst->config->matrix.col_pins, &len);
    if (res) {
        return 1;
    }
    len = sizeof(inst->config->matrix.layout);
    res = get_val_u8array(str, "layout", inst->config->matrix.layout, &len);
    if (res) {
        return 1;
    }
    if (len + 1 < sizeof(inst->config->matrix.layout)) {
        inst->config->matrix.layout[len] = 0xFF;
    }

    res = get_val_string(str, "mode", &string_val, &len);
    if (res) {
        return 1;
    }
    if (strncmp(string_val, "SPLIT_MASTER", sizeof("SPLIT_MASTER") - 1) == 0) {
        inst->config->mode = SPLIT_MASTER;
    } else if (strncmp(string_val, "SPLIT_SLAVE", sizeof("SPLIT_SLAVE") - 1) == 0) {
        inst->config->mode = SPLIT_SLAVE;
    } else {
        inst->config->mode = SINGLE;
    }

    // optional
    res = get_val_int(str, "startup", (int32_t*)&inst->config->startup);

    SEEK_KEY_OR_RETURN(str, "peripheral");
    res = get_val_int(str, "max_interval", (int32_t*)&inst->config->param_peripheral.max_interval);
    if (res) {
        return 1;
    }
    res = get_val_int(str, "min_interval", (int32_t*)&inst->config->param_peripheral.min_interval);
    if (res) {
        return 1;
    }
    res = get_val_int(str, "slave_latency", (int32_t*)&inst->config->param_peripheral.slave_latency);
    if (res) {
        return 1;
    }

    SEEK_KEY_OR_RETURN(str, "central");
    res = get_val_int(str, "max_interval", (int32_t*)&inst->config->param_central.max_interval);
    if (res) {
        return 1;
    }
    res = get_val_int(str, "min_interval", (int32_t*)&inst->config->param_central.min_interval);
    if (res) {
        return 1;
    }
    res = get_val_int(str, "slave_latency", (int32_t*)&inst->config->param_central.slave_latency);
    if (res) {
        return 1;
    }

    SEEK_KEY_OR_RETURN(str, "led");
    res = get_val_int(str, "pin", (int32_t*)&inst->config->led.pin);
    if (res) {
        return 1;
    }
    res = get_val_int(str, "num", (int32_t*)&inst->config->led.num);
    if (res) {
        return 1;
    }

    SEEK_KEY_OR_RETURN(str, "keymap");
    res                         = get_val_string(str, "locale", &string_val, &len);
    inst->config->keymap.locale = str2locale(string_val);
    if (res) {
        return 1;
    }
    res = get_val_u8(str, "use_ascii", (uint8_t*)&inst->config->keymap.use_ascii);
    if (res) {
        return 1;
    }

    // option
    len = sizeof(inst->config->reserved);
    res = get_val_u8array(str, "reserved", inst->config->reserved, &len);

    return 0;
}

int32_t config_to_json_conv(bmp_api_config_t const* const config, char* str, uint32_t len) {
    char     row_pins[100];
    char     col_pins[100];
    char     reserved[100];
    char     layout[1024];
    char     mode[16];
    char     str_locale[16];
    char*    str2;
    uint32_t written;

    row_pins[0] = '\0';
    col_pins[0] = '\0';

    str2 = row_pins;
    for (int i = 0; i < sizeof(config->matrix.row_pins); i++) {
        if (config->matrix.row_pins[i] == 0) {
            break;
        }
        written = snprintf(str2, sizeof(row_pins), "%d,", config->matrix.row_pins[i]);
        str2 += written;
    }
    if (str2 > row_pins) {
        *(str2 - 1) = '\0';  // delete last comma
    }

    str2 = col_pins;
    for (int i = 0; i < sizeof(config->matrix.col_pins); i++) {
        if (config->matrix.col_pins[i] == 0) {
            break;
        }
        written = snprintf(str2, sizeof(col_pins), "%d,", config->matrix.col_pins[i]);
        str2 += written;
    }
    if (str2 > col_pins) {
        *(str2 - 1) = '\0';  // delete last comma
    }
    str2 = layout;
    for (int i = 0; i < sizeof(config->matrix.layout); i++) {
        if (config->matrix.layout[i] == 0xFF) {
            break;
        }
        written = snprintf(str2, sizeof(layout), "%3d,", config->matrix.layout[i]);
        str2 += written;
        if (config->matrix.layout[i] == 0x00) {
            written = snprintf(str2, sizeof(layout), "\r\n");
            str2 += written;
        }
    }
    if (str2 > layout) {
        *(str2 - 1) = '\0';  // delete last comma
    }

    str2 = reserved;
    for (int i = 0; i < sizeof(config->reserved) / sizeof(config->reserved[0]); i++) {
        written = snprintf(str2, sizeof(reserved), "%d,", config->reserved[i]);
        str2 += written;
    }
    if (str2 > reserved) {
        *(str2 - 1) = '\0';  // delete last comma
    }

    if (config->mode == SPLIT_MASTER) {
        strncpy(mode, "SPLIT_MASTER", sizeof(mode));
    } else if (config->mode == SPLIT_SLAVE) {
        strncpy(mode, "SPLIT_SLAVE", sizeof(mode));
    } else {
        strncpy(mode, "SINGLE", sizeof(mode));
    }

    locale2str(config->keymap.locale, str_locale, sizeof(str_locale));

    snprintf(str, len,
             "{\"config\":{\"version\":%lu,\r\n\"device_info\":"
             "{\"vid\":\"0x%04lx\",\"pid\":\"0x%04lx\",\"name\":\"%s\",\"manufacture\":\"%s\",\"description\":\"%s\"},\r\n"
             "\"matrix\":{\"rows\":%hu,\"cols\":%hu,\"device_rows\":%hu,\"device_cols\":%hu,\"debounce\":%hu,\"is_left_hand\":%hu,\"diode_direction\":%hu,\"row_pins\":[%s],\"col_pins\":[%s],\r\n\"layout\":[\r\n%s]},\r\n"
             "\"mode\":\"%s\",\"startup\":%d,\r\n"
             "\"peripheral\":{\"max_interval\":%lu,\"min_interval\":%lu,\"slave_latency\":%lu},\r\n"
             "\"central\":{\"max_interval\":%lu,\"min_interval\":%lu,\"slave_latency\":%lu},\r\n"
             "\"led\":{\"pin\":%d,\"num\":%d},\r\n"
             "\"keymap\":{\"locale\":\"%s\",\"use_ascii\":%d},\r\n"
             "\"reserved\":[%s]}}",
             config->version, (uint32_t)config->device_info.vid, (uint32_t)config->device_info.pid, config->device_info.name, config->device_info.manufacture, config->device_info.description, config->matrix.rows, config->matrix.cols, config->matrix.device_rows, config->matrix.device_cols, config->matrix.debounce, config->matrix.is_left_hand, config->matrix.diode_direction, row_pins, col_pins, layout, mode, config->startup, config->param_peripheral.max_interval, config->param_peripheral.min_interval, config->param_peripheral.slave_latency, config->param_central.max_interval, config->param_central.min_interval, config->param_central.slave_latency, config->led.pin, config->led.num, str_locale, config->keymap.use_ascii, reserved);
    return 0;
}

int32_t get_config_from_stream(json_config_convert_inst_t* const inst, const char* str, const char last_char, uint32_t len, bool exit_flag) { return 0; }

int32_t get_keymap_from_stream(json_keymap_convert_inst_t* const inst, const char* str, const char last_char, uint32_t len, bool exit_flag) {
    json_to_keymap_conv(inst, str);

    if (exit_flag) {
        char last_str[2];
        last_str[0] = last_char;
        last_str[1] = '\0';
        json_to_keymap_conv(inst, last_str);
    } else if (inst->tail[0] != 0) {
        if (last_char == '\"') {
            json_to_keymap_conv(inst, "\"");
        } else {
            uint32_t tail_len = strlen(inst->tail);
            if (tail_len >= sizeof(inst->tail)) {
                return 1;
            }
            inst->tail[tail_len]     = last_char;
            inst->tail[tail_len + 1] = '\0';
        }
    } else if (last_char == '\"') {
        inst->tail[0] = '\"';
        inst->tail[1] = '\0';
    }

    return 0;
}

int32_t is_json_closed(const char* json, uint32_t len) {
    int32_t open_cnt  = 0;
    int32_t close_cnt = 0;
    int32_t in_string = 0;
    int32_t in_escape = 0;
    for (int i = 0; i < len && json[i] != '\0'; i++) {
        if (!in_escape) {
            if (json[i] == '\\') {
                in_escape = 1;
                continue;
            }
        }

        if (in_string) {
            if (!in_escape && json[i] == '\"') {
                in_string = 0;
            }
        } else {
            if (!in_escape && json[i] == '{') {
                open_cnt++;
            } else if (!in_escape && json[i] == '}') {
                if (++close_cnt > open_cnt) {
                    return -1;
                }
            } else if (!in_escape && json[i] == '\"') {
                in_string = 1;
            }
        }

        if (in_escape) {
            in_escape = 0;
        }
    }

    if (open_cnt > 0 && open_cnt == close_cnt) {
        return 0;
    } else {
        return 1;
    }
}

extern bmp_ex_keycode_t bmp_ex_keycodes[];
uint32_t                json_to_tapping_term_config_conv(const char* json, bmp_qmk_config_t* conf, KEYMAP_LOCALE locale) {
    const char* pstr;
    const char* pstr2;
    uint32_t    keylen;
    uint32_t    res = 0;
    int         i;

    pstr2 = json;
    SEEK_KEY_OR_RETURN(pstr2, "\"tapping_term\"");
    pstr2 += sizeof("\"tapping_term\"");
    for (i = 0; i < sizeof(conf->tapping_term) / sizeof(conf->tapping_term[0]) && res == 0; i++) {
        res = get_val_string(pstr2, NULL, &pstr, &keylen);
        if (res == 0) {
            conf->tapping_term[i].qkc = str2quantum_keycode_locale(pstr, keylen, locale);

            if (conf->tapping_term[i].qkc == EXKC_START) {
                bmp_ex_keycode_t           ek;
                json_keymap_convert_inst_t inst;
                inst.bmp_ek = bmp_ex_keycodes;
                str2bmp_ex_keycode_locale(&ek, pstr, keylen, locale);
                conf->tapping_term[i].qkc = register_ex_kc(&inst, &ek);
            }

            pstr                               = strchr(pstr, ':') + 1;
            conf->tapping_term[i].tapping_term = atoi(pstr);
            pstr2                              = pstr;
        } else {
            return i;
        }
    }
    return i;
}

void tapping_term_config_to_json_conv(bmp_qmk_config_t const* const conf, char* json, uint32_t json_len, KEYMAP_LOCALE locale, bool use_ascii) {
    char     key_str[32];
    uint32_t written = 0;
    uint16_t kc;

    written = snprintf(json, json_len, "{\"tapping_term\":{\r\n\t");
    json += written;
    json_len -= written;
    for (int i = 0; i < 16 && json_len > 0; i++) {
        kc = conf->tapping_term[i].qkc;
        if (EXKC_START <= kc && kc <= EXKC_END) {
            bmp_ex_keycode2str_locale(&bmp_ex_keycodes[kc - EXKC_START], key_str, sizeof(key_str), locale, use_ascii);
        } else {
            quantum_keycode2str_locale(conf->tapping_term[i].qkc, key_str, sizeof(key_str), locale, use_ascii);
        }
        written = snprintf(json, json_len, "\"%s\":%d,\r\n\t", key_str, conf->tapping_term[i].tapping_term);
        json += written;
        json_len -= written;

        if (conf->tapping_term[i].qkc == 0) {
            break;
        }
    }

    // remove trailing comma and close bracket
    written = snprintf(json - 4, json_len, "\r\n}}");
}
