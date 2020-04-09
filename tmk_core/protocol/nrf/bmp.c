
#include "bmp.h"
#include "bmp_encoder.h"
#include "bmp_custom_keycode.h"
#include "bmp_process_extended_keycode.h"
#include "keycode_str_converter.h"

#include <stdint.h>
#include "quantum.h"
#include "keyboard.h"
#include "matrix.h"
#include "host.h"
#include "led.h"
#include "keycode.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "command.h"
#include "util.h"
#include "sendchar.h"
#include "eeconfig.h"
#include "backlight.h"
#include "action_layer.h"
#ifdef BOOTMAGIC_ENABLE
#   include "bootmagic.h"
#else
#   include "magic.h"
#endif
#ifdef MOUSEKEY_ENABLE
#   include "mousekey.h"
#endif
#ifdef PS2_MOUSE_ENABLE
#   include "ps2_mouse.h"
#endif
#ifdef SERIAL_MOUSE_ENABLE
#   include "serial_mouse.h"
#endif
#ifdef ADB_MOUSE_ENABLE
#   include "adb.h"
#endif
#ifdef RGBLIGHT_ENABLE
#   include "rgblight.h"
#endif
#ifdef STENO_ENABLE
#   include "process_steno.h"
#endif
#ifdef FAUXCLICKY_ENABLE
#   include "fauxclicky.h"
#endif
#ifdef SERIAL_LINK_ENABLE
#   include "serial_link/system/serial_link.h"
#endif
#ifdef VISUALIZER_ENABLE
#   include "visualizer/visualizer.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
#   include "pointing_device.h"
#endif
#ifdef MIDI_ENABLE
#   include "process_midi.h"
#endif
#ifdef HD44780_ENABLE
#   include "hd44780.h"
#endif
#ifdef QWIIC_ENABLE
#   include "qwiic.h"
#endif
#ifdef OLED_DRIVER_ENABLE
    #include "oled_driver.h"
#endif
#ifdef VELOCIKEY_ENABLE
  #include "velocikey.h"
#endif

#ifndef DISABLE_MSC
#define DISABLE_MSC 0
#endif

#ifndef TAPPING_TERM
#define TAPPING_TERM 200
#endif


void bmp_action_exec(keyevent_t event)
{
    bmp_action_exec_impl(event);
    action_exec(event);
}

static int sleep_enter_counter = -1;
int reset_counter = -1;

/** \brief Keyboard task: Do keyboard routine jobs
 *
 * Do routine keyboard jobs:
 *
 * * scan matrix
 * * handle mouse movements
 * * run visualizer code
 * * handle midi commands
 * * light LEDs
 *
 * This is repeatedly called as fast as possible.
 */
void bmp_keyboard_task(void)
{
    static matrix_row_t matrix_prev[32];
    static uint8_t led_status = 0;
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;
#ifdef QMK_KEYS_PER_SCAN
    uint8_t keys_processed = 0;
#endif

#if defined(OLED_DRIVER_ENABLE) && !defined(OLED_DISABLE_TIMEOUT)
    uint8_t ret = matrix_scan();
#else
    matrix_scan();
#endif

    // bmp_check_timeout_extended_keycode();

#ifdef BMP_ENCODER_ENABLE
    bmp_encoder_read();
#endif

    const bmp_api_config_t *config = BMPAPI->app.get_config();


    if (is_keyboard_master()) {
        for (uint8_t r = 0; r < config->matrix.rows; r++) {
            matrix_row = matrix_get_row(r);
            matrix_change = matrix_row ^ matrix_prev[r];
            if (matrix_change) {
#ifdef MATRIX_HAS_GHOST
                if (has_ghost_in_row(r, matrix_row)) { continue; }
#endif
                if (debug_matrix) matrix_print();
                for (uint8_t c = 0; c < config->matrix.cols; c++) {
                    if (matrix_change & ((matrix_row_t)1<<c)) {
                        bmp_action_exec((keyevent_t){
                            .key = (keypos_t){ .row = r, .col = c },
                            .pressed = (matrix_row & ((matrix_row_t)1<<c)),
                            .time = (timer_read() | 1) /* time should not be 0 */
                        });
                        // record a processed key
                        matrix_prev[r] ^= ((matrix_row_t)1<<c);
#ifdef QMK_KEYS_PER_SCAN
                        // only jump out if we have processed "enough" keys.
                        if (++keys_processed >= QMK_KEYS_PER_SCAN)
#endif
                        // process a key per task call
                        goto MATRIX_LOOP_END;
                    }
                }
            }
        }
    }
    // call with pseudo tick event when no real key event.
#ifdef QMK_KEYS_PER_SCAN
    // we can get here with some keys processed now.
    if (!keys_processed)
#endif
    bmp_action_exec(TICK);

MATRIX_LOOP_END:

#ifdef QWIIC_ENABLE
    qwiic_task();
#endif

#ifdef OLED_DRIVER_ENABLE
    oled_task();
#ifndef OLED_DISABLE_TIMEOUT
    // Wake up oled if user is using those fabulous keys!
    if (ret)
        oled_on();
#endif
#endif

#ifdef MOUSEKEY_ENABLE
    // mousekey repeat & acceleration
    mousekey_task();
#endif

#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_task();
#endif

#ifdef SERIAL_MOUSE_ENABLE
    serial_mouse_task();
#endif

#ifdef ADB_MOUSE_ENABLE
    adb_mouse_task();
#endif

#ifdef SERIAL_LINK_ENABLE
	serial_link_update();
#endif

#ifdef VISUALIZER_ENABLE
    visualizer_update(default_layer_state, layer_state, visualizer_get_mods(), host_keyboard_leds());
#endif

#ifdef POINTING_DEVICE_ENABLE
    pointing_device_task();
#endif

#ifdef MIDI_ENABLE
    midi_task();
#endif

#ifdef VELOCIKEY_ENABLE
    if (velocikey_enabled()) { velocikey_decelerate();  }
#endif

    // update LED
    if (led_status != host_keyboard_leds()) {
        led_status = host_keyboard_leds();
        keyboard_set_leds(led_status);
    }

    // sleep flag check
    if (sleep_enter_counter > 0)
    {
        sleep_enter_counter--;
        if (sleep_enter_counter == 0)
        {
            BMPAPI->app.enter_sleep_mode();
        }
    }

    // reset flag check
    if (reset_counter > 0)
    {
        reset_counter--;
        if (reset_counter == 0)
        {
            // reset without safemode flag
            BMPAPI->app.reset(0);
        }
    }
}

bmp_error_t nus_rcv_callback(const uint8_t* dat, uint32_t len)
{
    if (len == sizeof(rgblight_syncinfo_t))
    {
        rgblight_update_sync((rgblight_syncinfo_t*)dat, false);
    }
    return BMP_OK;
}

#include "keycode_str_converter.h"
#include "config_file_util.h"
#include "apidef.h"
#include "cli.h"
#include "bmp_matrix.h"

#ifndef BMP_FORCE_SAFE_MODE
#define BMP_FORCE_SAFE_MODE false
#endif

char config_string[2048];
char keymap_string[10*1024];
bmp_qmk_config_t bmp_qmk_config;
char qmk_config_string[1024];

bmp_ex_keycode_t bmp_ex_keycodes[BMP_EX_KC_LEN];
uint32_t bmp_ex_keycode_num;

char *strnstr(const char *haystack, const char *needle, size_t len) {
  int i;
  size_t needle_len;

  needle_len = strnlen(needle, len);

  if (needle_len == 0)
  {
    return (char*)haystack;
  }

  for (i = 0; i <= (int)(len - needle_len); i++)
  {
    if ((haystack[0] == needle[0])
        && (strncmp(haystack, needle, needle_len) == 0))
    {
      return (char *) haystack;
    }

    haystack++;
  }
  return NULL;
}

const char *strnchr(const char *haystack, char needle, size_t len) {
  int i;
  for (i=0; i < len; i++)
  {
      if (haystack[i] == needle) {
          return &haystack[i];
      }
      else if (haystack[i] == '\0') {
          return NULL;
      }
  }
  return NULL;
}

int parse_config(void)
{
    bmp_api_config_t config;
    json_config_convert_inst_t inst;
    json_to_config_conv_inst_init(&inst, &config);
    int32_t res = json_to_config_conv(&inst, config_string);
    if (res)
    {
        BMPAPI->logger.info("Failed to parse config");
        return 1;
    }
    else
    {
        if (BMPAPI->app.set_config(&config) == BMP_OK)
        {
            matrix_init();
            BMPAPI->logger.info("Update config");
        }
        else
        {
            BMPAPI->logger.info("Invalid config");
            return 2;
        }
    }

    return 0;
}

void save_config(void)
{
    BMPAPI->app.save_file(0);
}

int parse_keymap(void)
{
    uint16_t keymap[512];
    json_keymap_convert_inst_t inst;
    json_to_keymap_init(&inst, keymap, sizeof(keymap)/sizeof(keymap[0]));
    inst.locale = BMPAPI->app.get_config()->keymap.locale;
    inst.bmp_ek = bmp_ex_keycodes;
    memset(bmp_ex_keycodes, 0, sizeof(bmp_ex_keycodes));

    if (json_to_keymap_conv(&inst, keymap_string) == 0)
    {
        xprintf("Update keymap. length:%d\n", inst.keymap_idx);
        xprintf("%d extended keycodes are found\n", inst.ek_num);
        xprintf("keyboard:%s\n", inst.layout_name);
        BMPAPI->app.set_keymap(keymap, inst.keymap_idx, inst.layout_name);
        bmp_ex_keycode_num = inst.ek_num;
    }
    else
    {
        BMPAPI->logger.info("Invalid keymap");
        return 1;
    }

    return 0;
}

void save_keymap(void)
{
    BMPAPI->app.save_file(1);
    save_ex_keycode_file();
}

int parse_qmk_config(void)
{
    uint32_t res = json_to_tapping_term_config_conv(qmk_config_string,
        &bmp_qmk_config,
        BMPAPI->app.get_config()->keymap.locale);

    if (res == 0)
    {
        BMPAPI->logger.info("Failed to update tapping term");

        return 1;
    }

    BMPAPI->logger.info("Update tapping term");
    return 0;
}

void save_qmk_config(void)
{
    int res = save_tapping_term_file();
    if (res == 0)
    {
        BMPAPI->logger.info("Tapping term saved");
    }
    else
    {
        BMPAPI->logger.info("Failed to save tapping term");
    }
}


const file_string_parser_setting_t file_string_parser_setting[]
  = {{.key = "\"config\"", .string_dst = config_string,
    .dst_len = sizeof(config_string), parse_config, save_config},
    {.key = "\"layers\"", .string_dst = keymap_string,
    .dst_len = sizeof(keymap_string), parse_keymap, save_keymap},
    {.key = "\"tapping_term\"", .string_dst = qmk_config_string,
    .dst_len = sizeof(qmk_config_string), parse_qmk_config, save_qmk_config }
    };

static file_string_parser_t parser = { NULL, 0 };

void set_parser(parser_type_t parser_type) {
    if (parser_type >= PARSER_NONE) {
        parser.setting = NULL;
        parser.write_idx = 0;
    } else {
        parser.setting = &file_string_parser_setting[parser_type];
        parser.write_idx = 0;
    }
}

file_string_parser_t * get_parser() {
    return &parser;
}

int stream_write_callback(const uint8_t* dat, uint32_t len)
{
  char* dst = NULL;
  uint32_t dst_len = 0;
  int32_t json_close = -1;

  if (parser.setting == NULL)
  {
    for (int i=0;
        i<sizeof(file_string_parser_setting)/sizeof(file_string_parser_setting[0]);
        i++)
    {
      if (strnstr((const char*)dat, file_string_parser_setting[i].key, len) != NULL)
      {
        set_parser(i);
        dst = parser.setting->string_dst;
        memcpy(dst, dat, len);
        parser.write_idx = len;
        dprintf("Match key: %s\r\n", parser.setting->key);
      }
    }
  }
  else
  {
    dst = parser.setting->string_dst;
    dst_len = parser.setting->dst_len;

    if (parser.write_idx + len + 1 > dst_len)
    {
      // buffer overflow
      parser.write_idx = 0;
      set_parser(PARSER_NONE);

      return 2;
    }
    memcpy(dst + parser.write_idx, dat, len);
    parser.write_idx += len;
  }

  if (parser.setting != NULL)
  {
    json_close = is_json_closed((const char*)dst, parser.write_idx);
    if (json_close == 0)
    {
      dst[parser.write_idx] = '\0';
      int res = parser.setting->parse();
      parser.write_idx = 0;
      BMPAPI->logger.info("Received json");

      return res == 0 ? 0 : 1;
    }
    else if (json_close == -1)
    {
      parser.write_idx = 0;
      set_parser(PARSER_NONE);
      BMPAPI->logger.info("Invalid json");

      return 1;
    }
  }

  // continue
  return -1;
}

bmp_error_t msc_write_callback(const uint8_t* dat, uint32_t len)
{
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

bmp_error_t webnus_write_callback(const uint8_t* dat, uint32_t len)
{
  if (strnstr((const char*)dat, "show keymap", len) != NULL)
  {
    BMPAPI->web_config.set_send_buffer((uint8_t*)keymap_string,
      strlen(keymap_string) + 1); // send keymap string with null character
  }
  else if (strnstr((const char*)dat, "show config", len) != NULL)
  {
    BMPAPI->web_config.set_send_buffer((uint8_t*)config_string,
      strlen(config_string) + 1); // send keymap string with null character
  }
  else if (strnstr((const char*)dat, "show tapping term", len) != NULL)
  {
    // TODO implement
    // BMPAPI->web_config.set_send_buffer((uint8_t*)config_string,
    //   strlen(config_string) + 1); // send keymap string with null character
  }
  else
  {
    msc_write_callback(dat, len);
  }
  return BMP_OK;
}

static inline void update_config_string(bmp_api_config_t const * config,
    char * str, uint32_t len)
{
  config_to_json_conv(config, str, len);
  BMPAPI->usb.create_file("CONFIG  JSN", (uint8_t*)str, strlen(str));
}

static inline void update_keymap_string(bmp_api_config_t const * config,
    char * str, uint32_t len,
    bmp_api_keymap_info_t const * const keymap_info)
{
  keymap_json_convert_inst_t keymap_conv_inst;
  keymap_to_json_init(&keymap_conv_inst, keymap_info->array, keymap_info->len);
  keymap_conv_inst.locale = config->keymap.locale;
  keymap_conv_inst.use_ascii = config->keymap.use_ascii;
  keymap_conv_inst.bmp_ek = bmp_ex_keycodes;

  char keyboard_name[32] = {0};
  char layout_name[32] = {0};
  const char* delimiter = strnchr(keymap_info->layout_name, ':', 32);

  if (delimiter != NULL)
  {
    memcpy(keyboard_name, keymap_info->layout_name,
        delimiter - keymap_info->layout_name);

    strncpy(layout_name, delimiter + 1, sizeof(layout_name));
  }
  else
  {
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
  BMPAPI->usb.create_file("KEYMAP  JSN", (uint8_t*)str, strlen(str));
}

static inline void update_tapping_term_string(bmp_api_config_t const * config,
    char * str, uint32_t len)
{
  tapping_term_config_to_json_conv(&bmp_qmk_config, str, len,
     config->keymap.locale,
     config->keymap.use_ascii
     );
  BMPAPI->usb.create_file("TAPTERM JSN", (uint8_t*)str, strlen(str));
}

__attribute__ ((weak))
void create_user_file() { }

static const char bmp_version_info[] =
                    "API version: " STR(API_VERSION) "\n"
                    "Config version: " STR(CONFIG_VERSION) "\n"
                    "Build from: " STR(GIT_DESCRIBE) "\n"
                    "Build Target: " STR(TARGET);
static inline void create_info_file()
{
  BMPAPI->usb.create_file("VERSION TXT", (uint8_t*)bmp_version_info,
    strlen(bmp_version_info));
}

const char* bmp_get_version_info() {
    return bmp_version_info;
}

static inline void create_index_html()
{
  static const char index_html[] = "<meta http-equiv=\"refresh\" content=\"0;URL=\'https://github.com/sekigon-gonnoc/BLE-Micro-Pro/tree/master/AboutDefaultFirmware\'\"/>";
  BMPAPI->usb.create_file("INDEX   HTM", (uint8_t*)index_html, strlen(index_html));
}

bmp_error_t bmp_state_change_cb(bmp_api_event_t event)
{
  const bmp_api_config_t * config = BMPAPI->app.get_config();
  bmp_api_keymap_info_t keymap_info;
  switch (event)
  {
    case USB_CONNECTED:
      BMPAPI->app.get_keymap_info(&keymap_info);
      update_keymap_string(config, keymap_string, sizeof(keymap_string), &keymap_info);
      update_config_string(config, config_string, sizeof(config_string));
      update_tapping_term_string(config, qmk_config_string, sizeof(qmk_config_string));
      create_info_file();
      create_index_html();
      create_user_file();
      break;
    default:
      break;
  }
  return BMP_OK;
}

static bool checkKeyIsPressedOnStartup(bmp_api_config_t const * const config, uint8_t row, uint8_t col)
{
  int8_t low_side_pin, high_side_pin;
  if (config->matrix.diode_direction == MATRIX_COL2ROW
    || config->matrix.diode_direction == MATRIX_COL2ROW2COL
    || config->matrix.diode_direction == MATRIX_COL2ROW_LPME) {
    high_side_pin = col;
    low_side_pin = row;
  }
  else if (config->matrix.diode_direction == MATRIX_ROW2COL
    || config->matrix.diode_direction == MATRIX_ROW2COL2ROW
    || config->matrix.diode_direction == MATRIX_ROW2COL_LPME) {
    high_side_pin = row;
    low_side_pin = col;
  }
  else {
    // return default value
    return false;
  }

  setPinInput(high_side_pin);
  setPinOd(low_side_pin);
  writePinLow(low_side_pin);

  uint8_t pin_state = readPin(high_side_pin);

  writePinLow(low_side_pin);

  return pin_state == 0;
}

static inline bool checkSafemodeFlag(bmp_api_config_t const * const config)
{
    return checkKeyIsPressedOnStartup(config, config->matrix.row_pins[0],
            config->matrix.col_pins[0]);
}

#if defined(ALLOW_MSC_ROW_PIN) && defined(ALLOW_MSC_COL_PIN)
static inline bool checkMscDisableFlag(bmp_api_config_t const * const config)
{
  if (checkKeyIsPressedOnStartup(config,
    ALLOW_MSC_ROW_PIN, ALLOW_MSC_COL_PIN) == 0) {
    // enable MSC
    return false;
  } else {
    // disable MSC
    return true;
  }
}
#endif

static bool has_ble = true;
static bool has_usb = true;
static bool is_safe_mode_ = false;

bool is_safe_mode() { return is_safe_mode_; }

void bmp_init()
{

  if (BMPAPI->api_version != API_VERSION)
  {
    BMPAPI->bootloader_jump();
  }

  BMPAPI->logger.init();
  BMPAPI->logger.info("logger init");
  static const bmp_api_config_t default_config = {
      .version = CONFIG_VERSION,
      .mode = BMP_DEFAULT_MODE == 0 ? SINGLE:
                BMP_DEFAULT_MODE == 1 ? SPLIT_MASTER:
                BMP_DEFAULT_MODE == 2 ? SPLIT_SLAVE : SINGLE,
      .device_info = {PRODUCT_ID, VENDOR_ID,
        STR(PRODUCT), STR(MANUFACTURER), STR(DESCRIPTION)},
      .matrix = {
          .rows = MATRIX_ROWS_DEFAULT,
          .cols = MATRIX_COLS_DEFAULT,
          .device_rows = THIS_DEVICE_ROWS,
          .device_cols = THIS_DEVICE_COLS,
          .debounce = 1,
          .is_left_hand = IS_LEFT_HAND ? 1:0,
          .diode_direction = DIODE_DIRECTION == ROW2COL ? 1:0,
          .row_pins = MATRIX_ROW_PINS,
          .col_pins = MATRIX_COL_PINS,
          .layout = MATRIX_LAYOUT,
      },
      .param_peripheral = {60, 30, 7},
      .param_central = {60, 30, 7},
      .led = {.pin = RGB_DI_PIN, .num = RGBLED_NUM_DEFAULT},
      .keymap = {.locale = KEYMAP_PRIOR_LOCALE, .use_ascii = KEYMAP_ASCII}
  };

  is_safe_mode_ = (BMPAPI->app.init(&default_config) > 0);

  const bmp_api_config_t * config = BMPAPI->app.get_config();


  if (checkSafemodeFlag(config) || BMP_FORCE_SAFE_MODE)
  {
    // start in safe mode
    BMPAPI->app.set_config(&default_config);
    config = &default_config;
    is_safe_mode_ = true;
  }

  BMPAPI->usb.set_msc_write_cb(msc_write_callback);
  BMPAPI->app.set_state_change_cb(bmp_state_change_cb);

  if (!is_safe_mode_) {
#if defined(ALLOW_MSC_ROW_PIN) && defined(ALLOW_MSC_COL_PIN)
    BMPAPI->usb.init(config, checkMscDisableFlag(config));
#else
    BMPAPI->usb.init(config, DISABLE_MSC);
#endif
  } else {
      BMPAPI->usb.init(config, DISABLE_MSC);
  }

  BMPAPI->ble.init(config);

  BMPAPI->logger.info("usb init");
  cli_init();

  bmp_api_keymap_info_t keymap_info;
  BMPAPI->app.get_keymap_info(&keymap_info);
  if (keymap_info.len == 0)
  {
    BMPAPI->app.set_keymap((uint16_t*)keymaps, keymaps_len(), keymap_info.layout_name); // load default keymap
    BMPAPI->app.get_keymap_info(&keymap_info);
  }

  if (config->mode == SPLIT_SLAVE)
  {
    BMPAPI->ble.set_nus_rcv_cb(nus_rcv_callback);
  }

  load_ex_keycode_file(); // load exkc before tapping_term
  load_tapping_term_file();
  load_eeprom_emulation_file();

  if (config->mode == WEBNUS_CONFIG)
  {
    update_keymap_string(config, keymap_string, sizeof(keymap_string), &keymap_info);
    update_config_string(config, config_string, sizeof(config_string));
    update_tapping_term_string(config, qmk_config_string, sizeof(qmk_config_string));
    BMPAPI->web_config.set_rcv_callback(webnus_write_callback);
    has_ble = false;
  }
  else if ((config->mode == SINGLE || config->mode == SPLIT_MASTER) &&
    config->startup == 1)
  {
    BMPAPI->ble.advertise(255);
  }


  BMPAPI->usb.enable();
  BMPAPI->logger.info("usb enable");
}

int load_eeprom_emulation_file()
{
  uint8_t *eeprom_buffer;
  uint32_t eeprom_buffer_length;
  eeprom_get_buffer_addr(&eeprom_buffer, &eeprom_buffer_length);
  if (eeprom_buffer == NULL)
  {
    return 1;
  }

  uint8_t *eeprom_file;
  uint32_t eeprom_file_length;
  BMPAPI->app.get_file(QMK_EE_RECORD, &eeprom_file, &eeprom_file_length);
  if (eeprom_file == NULL)
  {
    BMPAPI->app.save_file(QMK_EE_RECORD); // create eeprom file
    return 1;
  }

  uint32_t copy_length;
  copy_length = (eeprom_buffer_length > eeprom_file_length) ?
                eeprom_file_length : eeprom_buffer_length;
  memcpy(eeprom_buffer, eeprom_file, copy_length);

  return 0;
}

int save_eeprom_emulation_file()
{
  uint8_t *eeprom_buffer;
  uint32_t eeprom_buffer_length;
  eeprom_get_buffer_addr(&eeprom_buffer, &eeprom_buffer_length);
  if (eeprom_buffer == NULL)
  {
    return 1;
  }

  uint8_t *eeprom_file;
  uint32_t eeprom_file_length;
  BMPAPI->app.get_file(QMK_EE_RECORD, &eeprom_file, &eeprom_file_length);
  if (eeprom_file == NULL)
  {
    BMPAPI->app.save_file(QMK_EE_RECORD); // create eeprom file
    BMPAPI->app.get_file(QMK_EE_RECORD, &eeprom_file, &eeprom_file_length);
    if (eeprom_file == NULL) return 1;
  }

  uint32_t copy_length;
  copy_length = (eeprom_buffer_length > eeprom_file_length) ?
                eeprom_file_length : eeprom_buffer_length;
  memcpy(eeprom_file, eeprom_buffer, copy_length);

  return BMPAPI->app.save_file(QMK_EE_RECORD);
}

int load_tapping_term_file()
{
  bmp_qmk_config_t *p_qmk_config;
  uint32_t qmk_config_file_len;
  BMPAPI->app.get_file(QMK_RECORD, (uint8_t**)&p_qmk_config, &qmk_config_file_len);
  if (p_qmk_config == NULL)
  {
    BMPAPI->app.save_file(QMK_RECORD);
    bmp_qmk_config.tapping_term[0].qkc = KC_NO;
    bmp_qmk_config.tapping_term[0].tapping_term = TAPPING_TERM;
    return 1;
  }
  memcpy(&bmp_qmk_config, p_qmk_config, sizeof(bmp_qmk_config));

  // get default tapping term
  for (int i=0;
     i<sizeof(bmp_qmk_config.tapping_term)/sizeof(bmp_qmk_config.tapping_term[0]);
     i++)
  {
    if (bmp_qmk_config.tapping_term[i].qkc == KC_NO
        && bmp_qmk_config.tapping_term[i].tapping_term == 0)
    {
        bmp_qmk_config.tapping_term[i].tapping_term = TAPPING_TERM;
    }
  }

  return 0;
}

int save_tapping_term_file()
{
  bmp_qmk_config_t *p_qmk_config;
  uint32_t qmk_config_file_len;
  BMPAPI->app.get_file(QMK_RECORD, (uint8_t**)&p_qmk_config, &qmk_config_file_len);
  if (p_qmk_config == NULL)
  {
    BMPAPI->app.save_file(QMK_RECORD);
    BMPAPI->app.get_file(QMK_RECORD, (uint8_t**)&p_qmk_config, &qmk_config_file_len);
    if (p_qmk_config == NULL) return 1;
  }

  memcpy(p_qmk_config, &bmp_qmk_config, sizeof(bmp_qmk_config));

  return BMPAPI->app.save_file(QMK_RECORD);
}

int load_ex_keycode_file()
{
  bmp_ex_keycode_t *p_ex_keycode;
  uint32_t ex_keycode_len;

  BMPAPI->app.get_file(BMP_EX_KEYCODE_RECORD,
     (uint8_t**)&p_ex_keycode, &ex_keycode_len);
  if (p_ex_keycode == NULL)
  {
    bmp_ex_keycodes[0].byte[0] = 0;
    return 1;
  }
  memcpy(&bmp_ex_keycodes[0], p_ex_keycode, sizeof(bmp_ex_keycodes));

  for (bmp_ex_keycode_num=0;
         bmp_ex_keycode_num<sizeof(bmp_ex_keycodes)/sizeof(bmp_ex_keycodes[0]);
         bmp_ex_keycode_num++)
  {
    if (bmp_ex_keycodes[bmp_ex_keycode_num].byte[0] ==  0)
    {
      break;
    }
  }

  return 0;
}

int save_ex_keycode_file()
{
  bmp_ex_keycode_t *p_ex_keycode;
  uint32_t ex_keycode_len;

  BMPAPI->app.get_file(BMP_EX_KEYCODE_RECORD,
     (uint8_t**)&p_ex_keycode, &ex_keycode_len);
  if (p_ex_keycode == NULL)
  {
    // create new file
    BMPAPI->app.save_file(BMP_EX_KEYCODE_RECORD);
    BMPAPI->app.get_file(BMP_EX_KEYCODE_RECORD,
        (uint8_t**)&p_ex_keycode, &ex_keycode_len);

    if (p_ex_keycode == NULL) { return 1; }
  }

  memcpy(p_ex_keycode, &bmp_ex_keycodes[0], ex_keycode_len);
  return BMPAPI->app.save_file(BMP_EX_KEYCODE_RECORD);
}


uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
  return BMPAPI->app.keymap_key_to_keycode(layer, (bmp_api_keypos_t*)&key);
}

uint16_t get_tapping_term(uint16_t keycode) {
  for (int i=0;
     i<sizeof(bmp_qmk_config.tapping_term)/sizeof(bmp_qmk_config.tapping_term[0]);
     i++)
  {
    if (bmp_qmk_config.tapping_term[i].qkc == keycode)
    {
      return bmp_qmk_config.tapping_term[i].tapping_term;
    }
  }

  // get default tapping term
  for (int i=0;
     i<sizeof(bmp_qmk_config.tapping_term)/sizeof(bmp_qmk_config.tapping_term[0]);
     i++)
  {
    if (bmp_qmk_config.tapping_term[i].qkc == KC_NO)
    {
      return bmp_qmk_config.tapping_term[i].tapping_term;
    }
  }
  return TAPPING_TERM;
}

static bool usb_enabled = true;
static bool ble_enabled = true;

bool get_ble_enabled() { return ble_enabled & has_ble; }
void set_ble_enabled(bool enabled) { ble_enabled = enabled; }
bool get_usb_enabled() { return usb_enabled & has_usb; }
void set_usb_enabled(bool enabled) { usb_enabled = enabled; }

bool process_record_user_bmp(uint16_t keycode, keyrecord_t *record)
{
  char str[16];

  switch (keycode) {
    case xEISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;

    case xKANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;

    default:
      break;
  }

  if (record->event.pressed) {
    switch (keycode) {
      case BLE_DIS:
        set_ble_enabled(false);
        return false;
      case BLE_EN:
        set_ble_enabled(true);
        return false;
      case USB_DIS:
        set_usb_enabled(false);
        return false;
      case USB_EN:
        set_usb_enabled(true);
        return false;
      case SEL_BLE:
        set_usb_enabled(false);
        set_ble_enabled(true);
        return false;
      case SEL_USB:
        set_ble_enabled(false);
        set_usb_enabled(true);
        return false;
      case ADV_ID0...ADV_ID7:
        BMPAPI->ble.advertise(keycode - ADV_ID0);
        return false;
      case AD_WO_L:
        BMPAPI->ble.advertise(255);
        return false;
      case DEL_ID0...DEL_ID7:
        BMPAPI->ble.delete_bond(keycode - DEL_ID0);
        return false;
      case DELBNDS:
        BMPAPI->ble.delete_bond(255);
        return false;
      case ENT_DFU:
        BMPAPI->bootloader_jump();
        return false;
      case ENT_WEB:
        BMPAPI->web_config.enter();
        return false;
      case BATT_LV:
        snprintf(str, sizeof(str), "%4dmV", BMPAPI->app.get_vcc_mv());
        send_string(str);
        return false;
      case SAVE_EE:
        save_eeprom_emulation_file();
        return false;
      case DEL_EE:
        BMPAPI->app.delete_file(QMK_EE_RECORD);
        return false;
    }
  }
  else if (!record->event.pressed) {
    switch  (keycode) {
    case ENT_SLP:
    sleep_enter_counter = 10;
    return false;
    }
  }

  return true;
}

__attribute__((weak))uint32_t keymaps_len()
{
  return 0;
}

