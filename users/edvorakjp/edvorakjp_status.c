#include "eeprom.h"
#include "edvorakjp.h"

typedef union {
  uint8_t raw;
  struct {
    bool enable_jp_extra_layer : 1;
    bool enable_kc_lang        : 1;  // for macOS
  };
} edvorakjp_config_t;
static edvorakjp_config_t edvorakjp_config;

typedef struct {
  bool japanese_mode;
} edvorakjp_state_t;
static edvorakjp_state_t edvorakjp_state;

/*
 * private methods
 */
uint8_t eeconfig_read_edvorakjp(void) {
  return eeprom_read_byte(EECONFIG_EDVORAK);
}

void eeconfig_update_edvorakjp(uint8_t val) {
  eeprom_update_byte(EECONFIG_EDVORAK, val);
}

/*
 * public methods
 */
void edvorakjp_status_init(void) {
  edvorakjp_state.japanese_mode = false;
  edvorakjp_config.raw = eeconfig_read_edvorakjp();
}

bool get_enable_jp_extra_layer(void) {
  return edvorakjp_config.enable_jp_extra_layer;
}

void set_enable_jp_extra_layer(bool new_state) {
  edvorakjp_config.enable_jp_extra_layer = new_state;
  eeconfig_update_edvorakjp(edvorakjp_config.raw);
}

bool get_enable_kc_lang(void) {
  return edvorakjp_config.enable_kc_lang;
}

void set_enable_kc_lang(bool new_state) {
  edvorakjp_config.enable_kc_lang = new_state;
  eeconfig_update_edvorakjp(edvorakjp_config.raw);
}

bool get_japanese_mode(void) {
  return edvorakjp_state.japanese_mode;
}

void set_japanese_mode(bool new_state) {
  edvorakjp_state.japanese_mode = new_state;
  if (edvorakjp_state.japanese_mode) {
    if (edvorakjp_config.enable_kc_lang) {
      SEND_STRING(SS_TAP(X_LANG1));
    } else {
      SEND_STRING(SS_LALT("`"));
    }
  } else {
    dvorakj_layer_off();
    if (edvorakjp_config.enable_kc_lang) {
      SEND_STRING(SS_TAP(X_LANG2));
    } else {
      SEND_STRING(SS_LALT("`"));
    }
  }
}
