
#include "bmp.h"
#include "bmp_encoder.h"

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


static int sleep_enter_counter = -1;

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
                        action_exec((keyevent_t){
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
    action_exec(TICK);

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

char config_string[2048];
char keymap_string[10*1024];
bmp_qmk_config_t bmp_qmk_config;
char qmk_config_string[1024];

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

void parse_and_save_config(void)
{
    bmp_api_config_t config;
    json_config_convert_inst_t inst;
    json_to_config_conv_inst_init(&inst, &config);
    int32_t res = json_to_config_conv(&inst, config_string);
    if (res)
    {
        BMPAPI->logger.info("Failed to parse config");
    }
    else
    {
        if (BMPAPI->app.set_config(&config) == BMP_OK)
        {
            matrix_init();
            BMPAPI->logger.info("Update config");
            BMPAPI->app.save_file(0);
        }
        else
        {
            BMPAPI->logger.info("Invalid config");
        }
    }
}

void parse_and_save_keymap(void)
{
    uint16_t keymap[512];
    json_keymap_convert_inst_t inst;
    json_to_keymap_init(&inst, keymap, sizeof(keymap)/sizeof(keymap[0]));
    inst.locale = BMPAPI->app.get_config()->keymap.locale;
    if (json_to_keymap_conv(&inst, keymap_string) == 0)
    {
        xprintf("Update keymap. length:%d\r\n", inst.keymap_idx);
        BMPAPI->app.set_keymap(keymap, inst.keymap_idx);
        BMPAPI->app.save_file(1);
    }
    else
    {
        BMPAPI->logger.info("Invalid keymap");
    }
}

void parse_and_save_qmk_config(void)
{
    json_to_tapping_term_config_conv(qmk_config_string,
        &bmp_qmk_config,
        BMPAPI->app.get_config()->keymap.locale);
    int res = save_tapping_term_file();
    if (res == 0)
    {
        xprintf("Update tapping term\r\n");
    }
    else
    {
        xprintf("Failed to update tapping term\r\n");
    }
}

typedef struct
{
  const char* key;
  char* string_dst;
  uint32_t dst_len;
  void (*parse_and_save)(void);
} file_string_parser_t;

file_string_parser_t file_string_parser[]
  = {{.key = "\"config\"", .string_dst = config_string,
    .dst_len = sizeof(config_string), parse_and_save_config},
    {.key = "\"layers\"", .string_dst = keymap_string,
    .dst_len = sizeof(keymap_string), parse_and_save_keymap},
    {.key = "\"tapping_term\"", .string_dst = qmk_config_string,
    .dst_len = sizeof(qmk_config_string), parse_and_save_qmk_config }
    };

bmp_error_t msc_write_callback(const uint8_t* dat, uint32_t len)
{
  static uint8_t write_mode = 0;
  static uint16_t write_idx = 0;
  static char* dst = NULL;
  static uint32_t dst_len = 0;
  int32_t json_close;
  static file_string_parser_t *parser = NULL;

  if (write_mode == 0)
  {
    for (int i=0; i<sizeof(file_string_parser)/sizeof(file_string_parser[0]); i++)
    {
      if (strnstr((const char*)dat, file_string_parser[i].key, len) != NULL)
      {
        write_mode = i + 1;
        parser = &file_string_parser[i];
        dst = parser->string_dst;
        dst_len = parser->dst_len;
        memcpy(dst, dat, len);
        write_idx = len;
        xprintf("Match key: %s\r\n", parser->key);
      }
    }
  }
  else
  {
    if (write_idx + len > dst_len)
    {
      write_idx = 0;
      write_mode = 0;
      return BMP_INVALID_PARAM;
    }
    memcpy(dst + write_idx, dat, len);
    write_idx += len;
  }

  if (write_mode > 0)
  {
    json_close = is_json_closed((const char*)dst, write_idx);
    if (json_close == 0)
    {
      parser->parse_and_save();
      parser = NULL;
      write_idx = 0;
      write_mode = 0;
      BMPAPI->logger.info("Received json");
    }
    else if (json_close == -1)
    {
      write_idx = 0;
      write_mode = 0;
      BMPAPI->logger.info("Invalid json");
    }
  }
  return BMP_OK;
}

bmp_error_t webnus_write_callback(const uint8_t* dat, uint32_t len)
{
  if (strnstr((const char*)dat, "show keymap", len) != NULL)
  {
    BMPAPI->web_config.set_send_buffer((uint8_t*)keymap_string,
      strlen(keymap_string) + 1); // send keymap string whit null character
  }
  else if (strnstr((const char*)dat, "show config", len) != NULL)
  {
    BMPAPI->web_config.set_send_buffer((uint8_t*)config_string,
      strlen(config_string) + 1); // send keymap string whit null character
  }
  else if (strnstr((const char*)dat, "show tapping term", len) != NULL)
  {
    // TODO implement
    // BMPAPI->web_config.set_send_buffer((uint8_t*)config_string,
    //   strlen(config_string) + 1); // send keymap string whit null character
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
  strcpy(str, "{\"layers\":\r\n");
  keymap_to_json_conv_layout(&keymap_conv_inst, str + 12,
      len-12, config->matrix.layout);
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

static inline void create_info_file()
{
  static const char info[] =
                        "API version: " STR(API_VERSION) "\n"
                        "Config version: " STR(CONFIG_VERSION) "\n"
                        "Build from " STR(GIT_HASH) STR(GIT_HAS_DIFF)"\n"
                        "Build Target: " STR(TARGET);
  BMPAPI->usb.create_file("VERSION TXT", (uint8_t*)info, strlen(info));
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
          .rows = MATRIX_ROWS,
          .cols = MATRIX_COLS,
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

  BMPAPI->app.init(&default_config);
  const bmp_api_config_t * config = BMPAPI->app.get_config();
  BMPAPI->usb.set_msc_write_cb(msc_write_callback);
  BMPAPI->app.set_state_change_cb(bmp_state_change_cb);

  BMPAPI->usb.init(config, DISABLE_MSC);
  BMPAPI->ble.init(config);

  BMPAPI->logger.info("usb init");
  cli_init();

  bmp_api_keymap_info_t keymap_info;
  BMPAPI->app.get_keymap_info(&keymap_info);
  if (keymap_info.len == 0)
  {
    BMPAPI->app.set_keymap((uint16_t*)keymaps, keymaps_len()); // load default keymap
    BMPAPI->app.get_keymap_info(&keymap_info);
  }

  if (config->mode == SPLIT_SLAVE)
  {
    BMPAPI->ble.set_nus_rcv_cb(nus_rcv_callback);
  }

  load_tapping_term_file();
  load_eeprom_emulation_file();

  if (config->mode == WEBNUS_CONFIG)
  {
    update_keymap_string(config, keymap_string, sizeof(keymap_string), &keymap_info);
    update_config_string(config, config_string, sizeof(config_string));
    update_tapping_term_string(config, qmk_config_string, sizeof(qmk_config_string));
    BMPAPI->web_config.set_rcv_callback(webnus_write_callback);
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
    bmp_qmk_config.tapping_term[0].qkc = KC_NO;
    bmp_qmk_config.tapping_term[0].tapping_term = TAPPING_TERM;
    return 1;
  }
  memcpy(&bmp_qmk_config, p_qmk_config, sizeof(bmp_qmk_config));

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

bool get_ble_enabled() { return ble_enabled; }
void set_ble_enabled(bool enabled) { ble_enabled = enabled; }
bool get_usb_enabled() { return usb_enabled; }
void set_usb_enabled(bool enabled) { usb_enabled = enabled; }


bool process_record_user_bmp(uint16_t keycode, keyrecord_t *record)
{
  char str[16];
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
