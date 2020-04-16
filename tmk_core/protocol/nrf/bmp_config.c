/*
Copyright 2020 Sekigon

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


#include "apidef.h"
#include "bmp.h"
#include "bmp_config.h"

#ifndef TAPPING_TERM
#    define TAPPING_TERM 200
#endif

static char                 config_string[2048];
static char                 keymap_string[10 * 1024];
static bmp_qmk_config_t     bmp_qmk_config;
static char                 qmk_config_string[1024];
static bmp_encoder_config_t bmp_encoder_config;
static char                 encoder_config_string[1024];

bmp_ex_keycode_t bmp_ex_keycodes[BMP_EX_KC_LEN];
uint32_t         bmp_ex_keycode_num;

const bmp_encoder_config_t *get_bmp_encoder_config() {
    return &bmp_encoder_config;
}
const char *get_keymap_string() { return keymap_string; }
const char *get_config_string() { return config_string; }
const char *get_encoder_string() { return encoder_config_string; }

char *strnstr(const char *haystack, const char *needle, size_t len) {
    int    i;
    size_t needle_len;

    needle_len = strnlen(needle, len);

    if (needle_len == 0) {
        return (char *)haystack;
    }

    for (i = 0; i <= (int)(len - needle_len); i++) {
        if ((haystack[0] == needle[0]) &&
            (strncmp(haystack, needle, needle_len) == 0)) {
            return (char *)haystack;
        }

        haystack++;
    }
    return NULL;
}

const char *strnchr(const char *haystack, char needle, size_t len) {
    int i;
    for (i = 0; i < len; i++) {
        if (haystack[i] == needle) {
            return &haystack[i];
        } else if (haystack[i] == '\0') {
            return NULL;
        }
    }
    return NULL;
}

int parse_config(void) {
    bmp_api_config_t           config;
    json_config_convert_inst_t inst;
    json_to_config_conv_inst_init(&inst, &config);
    int32_t res = json_to_config_conv(&inst, config_string);
    if (res) {
        BMPAPI->logger.info("Failed to parse config");
        return 1;
    } else {
        if (BMPAPI->app.set_config(&config) == BMP_OK) {
            matrix_init();
            BMPAPI->logger.info("Update config");
        } else {
            BMPAPI->logger.info("Invalid config");
            return 2;
        }
    }

    return 0;
}

void save_config(void) { BMPAPI->app.save_file(0); }

int parse_keymap(void) {
    uint16_t                   keymap[512];
    json_keymap_convert_inst_t inst;
    json_to_keymap_init(&inst, keymap, sizeof(keymap) / sizeof(keymap[0]));
    inst.locale = BMPAPI->app.get_config()->keymap.locale;
    inst.bmp_ek = bmp_ex_keycodes;
    memset(bmp_ex_keycodes, 0, sizeof(bmp_ex_keycodes));

    if (json_to_keymap_conv(&inst, keymap_string) == 0) {
        xprintf("Update keymap. length:%d\n", inst.keymap_idx);
        xprintf("%d extended keycodes are found\n", inst.ek_num);
        xprintf("keyboard:%s\n", inst.layout_name);
        BMPAPI->app.set_keymap(keymap, inst.keymap_idx, inst.layout_name);
        bmp_ex_keycode_num = inst.ek_num;
    } else {
        BMPAPI->logger.info("Invalid keymap");
        return 1;
    }

    return 0;
}

void save_keymap(void) {
    BMPAPI->app.save_file(1);
    save_ex_keycode_file();
}

int parse_qmk_config(void) {
    uint32_t res = json_to_tapping_term_config_conv(
        qmk_config_string, &bmp_qmk_config,
        BMPAPI->app.get_config()->keymap.locale);

    if (res == 0) {
        BMPAPI->logger.info("Failed to update tapping term");

        return 1;
    }

    BMPAPI->logger.info("Update tapping term");

    // copy settings to bootloader region
    bmp_qmk_config_t *p_qmk_config;
    uint32_t          qmk_config_file_len;
    BMPAPI->app.get_file(QMK_RECORD, (uint8_t **)&p_qmk_config,
                         &qmk_config_file_len);
    if (p_qmk_config == NULL) {
        BMPAPI->app.save_file(QMK_RECORD);
        BMPAPI->app.get_file(QMK_RECORD, (uint8_t **)&p_qmk_config,
                             &qmk_config_file_len);
        if (p_qmk_config == NULL) return 1;
    }

    memcpy(p_qmk_config, &bmp_qmk_config, sizeof(bmp_qmk_config));

    return 0;
}

void save_qmk_config(void) {
    int res = save_tapping_term_file();
    if (res == 0) {
        BMPAPI->logger.info("Tapping term saved");
    } else {
        BMPAPI->logger.info("Failed to save tapping term");
    }
}

int parse_encoder_config(void) {
    memset(&bmp_encoder_config, 0, sizeof(bmp_encoder_config));
    json_to_encoder_config(&bmp_encoder_config, encoder_config_string,
                           BMPAPI->app.get_config()->keymap.locale);

    // copy settings to bootloader region
    bmp_encoder_config_t *p_encoder_config;
    uint32_t              encoder_config_file_len;
    BMPAPI->app.get_file(BMP_ENC_RECORD, (uint8_t **)&p_encoder_config,
                         &encoder_config_file_len);
    if (p_encoder_config == NULL) {
        BMPAPI->app.save_file(BMP_ENC_RECORD);
        BMPAPI->app.get_file(BMP_ENC_RECORD, (uint8_t **)&p_encoder_config,
                             &encoder_config_file_len);
        if (p_encoder_config == NULL) return 1;
    }

    memcpy(p_encoder_config, &bmp_encoder_config, sizeof(bmp_encoder_config));

    return 0;
}

void save_encoder_config(void) {
    int res = BMPAPI->app.save_file(BMP_ENC_RECORD);
    if (res == 0) {
        xprintf("Succeed to save encoder config");
    } else {
        xprintf("Failed to save encoder config");
    }
}

const file_string_parser_setting_t file_string_parser_setting[] = {
    {.key        = "\"config\"",
     .string_dst = config_string,
     .dst_len    = sizeof(config_string),
     parse_config,
     save_config},
    {.key        = "\"layers\"",
     .string_dst = keymap_string,
     .dst_len    = sizeof(keymap_string),
     parse_keymap,
     save_keymap},
    {.key        = "\"tapping_term\"",
     .string_dst = qmk_config_string,
     .dst_len    = sizeof(qmk_config_string),
     parse_qmk_config,
     save_qmk_config},
    {.key        = "\"encoder\"",
     .string_dst = encoder_config_string,
     .dst_len    = sizeof(encoder_config_string),
     parse_encoder_config,
     save_encoder_config}};

static file_string_parser_t parser = {NULL, 0};

void set_parser(parser_type_t parser_type) {
    if (parser_type >= PARSER_NONE) {
        parser.setting   = NULL;
        parser.write_idx = 0;
    } else {
        parser.setting   = &file_string_parser_setting[parser_type];
        parser.write_idx = 0;
    }
}

file_string_parser_t *get_parser() { return &parser; }

int stream_write_callback(const uint8_t *dat, uint32_t len) {
    char *   dst        = NULL;
    uint32_t dst_len    = 0;
    int32_t  json_close = -1;

    if (parser.setting == NULL) {
        for (int i = 0; i < sizeof(file_string_parser_setting) /
                                sizeof(file_string_parser_setting[0]);
             i++) {
            if (strnstr((const char *)dat, file_string_parser_setting[i].key,
                        len) != NULL) {
                set_parser(i);
                dst = parser.setting->string_dst;
                memcpy(dst, dat, len);
                parser.write_idx = len;
                dprintf("Match key: %s\r\n", parser.setting->key);
            }
        }
    } else {
        dst     = parser.setting->string_dst;
        dst_len = parser.setting->dst_len;

        if (parser.write_idx + len + 1 > dst_len) {
            // buffer overflow
            parser.write_idx = 0;
            set_parser(PARSER_NONE);

            return 2;
        }
        memcpy(dst + parser.write_idx, dat, len);
        parser.write_idx += len;
    }

    if (parser.setting != NULL) {
        json_close = is_json_closed((const char *)dst, parser.write_idx);
        if (json_close == 0) {
            dst[parser.write_idx] = '\0';
            int res               = parser.setting->parse();
            parser.write_idx      = 0;
            BMPAPI->logger.info("Received json");

            return res == 0 ? 0 : 1;
        } else if (json_close == -1) {
            parser.write_idx = 0;
            set_parser(PARSER_NONE);
            BMPAPI->logger.info("Invalid json");

            return 1;
        }
    }

    // continue
    return -1;
}

bmp_error_t msc_write_callback(const uint8_t *dat, uint32_t len) {
    int res = stream_write_callback(dat, len);

    if (res == 0) {
        if (parser.setting != NULL) {
            parser.setting->save();
        }
        set_parser(PARSER_NONE);
    } else if (res == 2) {
        set_parser(PARSER_NONE);
        return BMP_INVALID_PARAM;
    }

    return BMP_OK;
}

bmp_error_t webnus_write_callback(const uint8_t *dat, uint32_t len) {
    if (strnstr((const char *)dat, "show keymap", len) != NULL) {
        BMPAPI->web_config.set_send_buffer(
            (uint8_t *)keymap_string,
            strlen(keymap_string) +
                1);  // send keymap string with null character
    } else if (strnstr((const char *)dat, "show config", len) != NULL) {
        BMPAPI->web_config.set_send_buffer(
            (uint8_t *)config_string,
            strlen(config_string) +
                1);  // send keymap string with null character
    } else if (strnstr((const char *)dat, "show tapping term", len) != NULL) {
        // TODO implement
        // BMPAPI->web_config.set_send_buffer((uint8_t*)config_string,
        //   strlen(config_string) + 1); // send keymap string with null
        //   character
    } else {
        msc_write_callback(dat, len);
    }
    return BMP_OK;
}

static inline void update_config_string(bmp_api_config_t const *config,
                                        char *str, uint32_t len) {
    config_to_json_conv(config, str, len);
    BMPAPI->usb.create_file("CONFIG  JSN", (uint8_t *)str, strlen(str));
}

static inline void update_keymap_string(
    bmp_api_config_t const *config, char *str, uint32_t len,
    bmp_api_keymap_info_t const *const keymap_info) {
    keymap_json_convert_inst_t keymap_conv_inst;
    keymap_to_json_init(&keymap_conv_inst, keymap_info->array,
                        keymap_info->len);
    keymap_conv_inst.locale    = config->keymap.locale;
    keymap_conv_inst.use_ascii = config->keymap.use_ascii;
    keymap_conv_inst.bmp_ek    = bmp_ex_keycodes;

    char        keyboard_name[32] = {0};
    char        layout_name[32]   = {0};
    const char *delimiter         = strnchr(keymap_info->layout_name, ':', 32);

    if (delimiter != NULL) {
        memcpy(keyboard_name, keymap_info->layout_name,
               delimiter - keymap_info->layout_name);

        strncpy(layout_name, delimiter + 1, sizeof(layout_name));
    } else {
        strcpy(keyboard_name, config->device_info.name);
        strcpy(layout_name, keymap_info->layout_name);
    }

    strcpy(str, "{\"keyboard\":\"");
    strcat(str, keyboard_name);

    strcat(str, "\",\r\n\"keymap\":\"");
    strcat(str, "\",\r\n\"layout\":\"");
    strcat(str, layout_name);

    strcat(str, "\",\r\n\"layers\":\r\n");
    uint32_t header_len = strlen(str);

    keymap_to_json_conv_layout(&keymap_conv_inst, str + header_len,
                               len - header_len, config->matrix.layout);
    strcat(str, "}");
    BMPAPI->usb.create_file("KEYMAP  JSN", (uint8_t *)str, strlen(str));
}

static inline void update_tapping_term_string(bmp_api_config_t const *config,
                                              char *str, uint32_t len) {
    tapping_term_config_to_json_conv(&bmp_qmk_config, str, len,
                                     config->keymap.locale,
                                     config->keymap.use_ascii);
    BMPAPI->usb.create_file("TAPTERM JSN", (uint8_t *)str, strlen(str));
}

static inline void update_ecoder_config_string(bmp_encoder_config_t const *config,
                                              char *str, uint32_t len) {
    encoder_config_to_json(config, str, len);
    BMPAPI->usb.create_file("ENCODER JSN", (uint8_t *)str, strlen(str));
}

__attribute__((weak)) void create_user_file() {}

static const char bmp_version_info[] = "API version: " STR(
    API_VERSION) "\n"
                 "Config version: " STR(
                     CONFIG_VERSION) "\n"
                                     "Build from: " STR(
                                         GIT_DESCRIBE) "\n"
                                                       "Build Target: " STR(
                                                           TARGET);
static inline void create_info_file() {
    BMPAPI->usb.create_file("VERSION TXT", (uint8_t *)bmp_version_info,
                            strlen(bmp_version_info));
}

const char *bmp_get_version_info() { return bmp_version_info; }

static inline void create_index_html() {
    static const char index_html[] =
        "<meta http-equiv=\"refresh\" "
        "content=\"0;URL=\'https://github.com/sekigon-gonnoc/BLE-Micro-Pro/"
        "tree/master/AboutDefaultFirmware\'\"/>";
    BMPAPI->usb.create_file("INDEX   HTM", (uint8_t *)index_html,
                            strlen(index_html));
}

int load_eeprom_emulation_file() {
    uint8_t *eeprom_buffer;
    uint32_t eeprom_buffer_length;
    eeprom_get_buffer_addr(&eeprom_buffer, &eeprom_buffer_length);
    if (eeprom_buffer == NULL) {
        return 1;
    }

    uint8_t *eeprom_file;
    uint32_t eeprom_file_length;
    BMPAPI->app.get_file(QMK_EE_RECORD, &eeprom_file, &eeprom_file_length);
    if (eeprom_file == NULL) {
        BMPAPI->app.save_file(QMK_EE_RECORD);  // create eeprom file
        return 1;
    }

    uint32_t copy_length;
    copy_length = (eeprom_buffer_length > eeprom_file_length)
                      ? eeprom_file_length
                      : eeprom_buffer_length;
    memcpy(eeprom_buffer, eeprom_file, copy_length);

    return 0;
}

int save_eeprom_emulation_file() {
    uint8_t *eeprom_buffer;
    uint32_t eeprom_buffer_length;
    eeprom_get_buffer_addr(&eeprom_buffer, &eeprom_buffer_length);
    if (eeprom_buffer == NULL) {
        return 1;
    }

    uint8_t *eeprom_file;
    uint32_t eeprom_file_length;
    BMPAPI->app.get_file(QMK_EE_RECORD, &eeprom_file, &eeprom_file_length);
    if (eeprom_file == NULL) {
        BMPAPI->app.save_file(QMK_EE_RECORD);  // create eeprom file
        BMPAPI->app.get_file(QMK_EE_RECORD, &eeprom_file, &eeprom_file_length);
        if (eeprom_file == NULL) return 1;
    }

    uint32_t copy_length;
    copy_length = (eeprom_buffer_length > eeprom_file_length)
                      ? eeprom_file_length
                      : eeprom_buffer_length;
    memcpy(eeprom_file, eeprom_buffer, copy_length);

    return BMPAPI->app.save_file(QMK_EE_RECORD);
}

int load_tapping_term_file() {
    bmp_qmk_config_t *p_qmk_config;
    uint32_t          qmk_config_file_len;
    BMPAPI->app.get_file(QMK_RECORD, (uint8_t **)&p_qmk_config,
                         &qmk_config_file_len);
    if (p_qmk_config == NULL) {
        BMPAPI->app.save_file(QMK_RECORD);
        bmp_qmk_config.tapping_term[0].qkc          = KC_NO;
        bmp_qmk_config.tapping_term[0].tapping_term = TAPPING_TERM;
        return 1;
    }
    memcpy(&bmp_qmk_config, p_qmk_config, sizeof(bmp_qmk_config));

    // get default tapping term
    for (int i = 0; i < sizeof(bmp_qmk_config.tapping_term) /
                            sizeof(bmp_qmk_config.tapping_term[0]);
         i++) {
        if (bmp_qmk_config.tapping_term[i].qkc == KC_NO &&
            bmp_qmk_config.tapping_term[i].tapping_term == 0) {
            bmp_qmk_config.tapping_term[i].tapping_term = TAPPING_TERM;
        }
    }

    return 0;
}

int save_tapping_term_file() { return BMPAPI->app.save_file(QMK_RECORD); }

int load_ex_keycode_file() {
    bmp_ex_keycode_t *p_ex_keycode;
    uint32_t          ex_keycode_len;

    BMPAPI->app.get_file(BMP_EX_KEYCODE_RECORD, (uint8_t **)&p_ex_keycode,
                         &ex_keycode_len);
    if (p_ex_keycode == NULL) {
        bmp_ex_keycodes[0].byte[0] = 0;
        return 1;
    }
    memcpy(&bmp_ex_keycodes[0], p_ex_keycode, sizeof(bmp_ex_keycodes));

    for (bmp_ex_keycode_num = 0;
         bmp_ex_keycode_num <
         sizeof(bmp_ex_keycodes) / sizeof(bmp_ex_keycodes[0]);
         bmp_ex_keycode_num++) {
        if (bmp_ex_keycodes[bmp_ex_keycode_num].byte[0] == 0) {
            break;
        }
    }

    return 0;
}

int save_ex_keycode_file() {
    bmp_ex_keycode_t *p_ex_keycode;
    uint32_t          ex_keycode_len;

    BMPAPI->app.get_file(BMP_EX_KEYCODE_RECORD, (uint8_t **)&p_ex_keycode,
                         &ex_keycode_len);
    if (p_ex_keycode == NULL) {
        // create new file
        BMPAPI->app.save_file(BMP_EX_KEYCODE_RECORD);
        BMPAPI->app.get_file(BMP_EX_KEYCODE_RECORD, (uint8_t **)&p_ex_keycode,
                             &ex_keycode_len);

        if (p_ex_keycode == NULL) {
            return 1;
        }
    }

    memcpy(p_ex_keycode, &bmp_ex_keycodes[0], ex_keycode_len);
    return BMPAPI->app.save_file(BMP_EX_KEYCODE_RECORD);
}

int load_encoder_config_file() {
    bmp_encoder_config_t *p_encoder_config;
    uint32_t              encoder_config_file_len;
    BMPAPI->app.get_file(BMP_ENC_RECORD, (uint8_t **)&p_encoder_config,
                         &encoder_config_file_len);
    if (p_encoder_config == NULL) {
        BMPAPI->app.save_file(BMP_ENC_RECORD);
        bmp_encoder_config.enabled           = 0;
        bmp_encoder_config.encoder[0].pin[0] = 0;
        bmp_encoder_config.encoder[0].pin[1] = 0;
        return 1;
    }

    memcpy(&bmp_encoder_config, p_encoder_config, sizeof(bmp_encoder_config));

    return 0;
}

uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
    return BMPAPI->app.keymap_key_to_keycode(layer, (bmp_api_keypos_t *)&key);
}

uint16_t get_tapping_term(uint16_t keycode) {
    for (int i = 0; i < sizeof(bmp_qmk_config.tapping_term) /
                            sizeof(bmp_qmk_config.tapping_term[0]);
         i++) {
        if (bmp_qmk_config.tapping_term[i].qkc == keycode) {
            return bmp_qmk_config.tapping_term[i].tapping_term;
        }
    }

    // get default tapping term
    for (int i = 0; i < sizeof(bmp_qmk_config.tapping_term) /
                            sizeof(bmp_qmk_config.tapping_term[0]);
         i++) {
        if (bmp_qmk_config.tapping_term[i].qkc == KC_NO) {
            return bmp_qmk_config.tapping_term[i].tapping_term;
        }
    }
    return TAPPING_TERM;
}

void update_config_files() {
    const bmp_api_config_t *config = BMPAPI->app.get_config();
    bmp_api_keymap_info_t   keymap_info;

    BMPAPI->app.get_keymap_info(&keymap_info);

    update_keymap_string(config, keymap_string, sizeof(keymap_string),
                         &keymap_info);
    update_config_string(config, config_string, sizeof(config_string));
    update_tapping_term_string(config, qmk_config_string,
                               sizeof(qmk_config_string));
    update_ecoder_config_string(&bmp_encoder_config, encoder_config_string,
                                sizeof(encoder_config_string));
    create_info_file();
    create_index_html();
    create_user_file();
}
