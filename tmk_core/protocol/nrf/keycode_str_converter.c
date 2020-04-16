/*
 * keycode2str.c
 *
 *  Created on: 2018/08/24
 *      Author: sekigon
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "keycode_str_converter.h"
#include "action_code.h"
#include "keycode.h"
#include "quantum_keycodes.h"
#include "keymap_jp.h"
#include "bmp_custom_keycode.h"

const key_string_map_t regular_keys = {
  .start_kc = KC_NO,
  .end_kc = KC_EXSEL,
  .key_strings =
    "NO\0"
    "TRNS\0"
    "POST_FAIL\0"
    "UNDEFINED\0"
    "A\0"
    "B\0"
    "C\0"
    "D\0"
    "E\0"
    "F\0"
    "G\0"
    "H\0"
    "I\0"
    "J\0"
    "K\0"
    "L\0"
    "M\0"
    "N\0"
    "O\0"
    "P\0"
    "Q\0"
    "R\0"
    "S\0"
    "T\0"
    "U\0"
    "V\0"
    "W\0"
    "X\0"
    "Y\0"
    "Z\0"
    "1\0"
    "2\0"
    "3\0"
    "4\0"
    "5\0"
    "6\0"
    "7\0"
    "8\0"
    "9\0"
    "0\0"
    "ENT\0"
    "ESC\0"
    "BSPC\0"
    "TAB\0"
    "SPC\0"
    "MINS\0"
    "EQL\0"
    "LBRC\0"
    "RBRC\0"
    "BSLS\0"
    "NUHS\0"
    "SCLN\0"
    "QUOT\0"
    "GRV\0"
    "COMM\0"
    "DOT\0"
    "SLSH\0"
    "CAPS\0"
    "F1\0"
    "F2\0"
    "F3\0"
    "F4\0"
    "F5\0"
    "F6\0"
    "F7\0"
    "F8\0"
    "F9\0"
    "F10\0"
    "F11\0"
    "F12\0"
    "PSCR\0"
    "SLCK\0"
    "PAUS\0"
    "INS\0"
    "HOME\0"
    "PGUP\0"
    "DEL\0"
    "END\0"
    "PGDN\0"
    "RGHT\0"
    "LEFT\0"
    "DOWN\0"
    "UP\0"
    "NLCK\0"
    "PSLS\0"
    "PAST\0"
    "PMNS\0"
    "PPLS\0"
    "PENT\0"
    "P1\0"
    "P2\0"
    "P3\0"
    "P4\0"
    "P5\0"
    "P6\0"
    "P7\0"
    "P8\0"
    "P9\0"
    "P0\0"
    "PDOT\0"
    "NUBS\0"
    "APP\0"
    "POWER\0"
    "PEQL\0"
    "F13\0"
    "F14\0"
    "F15\0"
    "F16\0"
    "F17\0"
    "F18\0"
    "F19\0"
    "F20\0"
    "F21\0"
    "F22\0"
    "F23\0"
    "F24\0"
    "EXECUTE\0"
    "HELP\0"
    "MENU\0"
    "SELECT\0"
    "STOP\0"
    "AGAIN\0"
    "UNDO\0"
    "CUT\0"
    "COPY\0"
    "PASTE\0"
    "FIND\0"
    "_MUTE\0"
    "_VOLUP\0"
    "_VOLDOWN\0"
    "LOCKING_CAPS\0"
    "LOCKING_NUM\0"
    "LOCKING_SCROLL\0"
    "KP_COMMA\0"
    "KP_EQUAL_AS400\0"
    "RO\0"   //"INT1\0"
    "KANA\0" //"INT2\0"
    "JYEN\0" //"INT3\0"
    "HENK\0" //"INT4\0"
    "MHEN\0" //"INT5\0"
    "INT6\0"
    "INT7\0"
    "INT8\0"
    "INT9\0"
    "LANG1\0"
    "LANG2\0"
    "LANG3\0"
    "LANG4\0"
    "LANG5\0"
    "LANG6\0"
    "LANG7\0"
    "LANG8\0"
    "LANG9\0"
    "ALT_ERASE\0"
    "SYSREQ\0"
    "CANCEL\0"
    "CLEAR\0"
    "PRIOR\0"
    "RETURN\0"
    "SEPARATOR\0"
    "OUT\0"
    "OPER\0"
    "CLEAR_AGAIN\0"
    "CRSEL\0"
    "EXSEL\0"
};

const key_string_map_t modifiers = {
  .start_kc = KC_LCTRL,
  .end_kc = KC_RGUI,
  .key_strings =
    "LCTL\0"
    "LSFT\0"
    "LALT\0"
    "LGUI\0"
    "RCTL\0"
    "RSFT\0"
    "RALT\0"
    "RGUI\0"
};

const key_string_map_t system_and_consumers = {
  .start_kc = KC_SYSTEM_POWER,
  .end_kc = KC_MEDIA_REWIND,
  .key_strings =
    "PWR\0"
    "SLEP\0"
    "WAKE\0"
    "MUTE\0"
    "VOLU\0"
    "VOLD\0"
    "MNXT\0"
    "MPRV\0"
    "MSTP\0"
    "MPLY\0"
    "SLCT\0"
    "EJCT\0"         //0xB0
    "MAIL\0"
    "CALC\0"
    "MYCM\0"
    "WSCH\0"
    "WHOM\0"
    "WBAK\0"
    "WFWD\0"
    "WSTP\0"
    "WREF\0"
    "WFAV\0"
    "MFFD\0"
    "MRWD\0"
};

const key_string_map_t mouse_keys = {
  .start_kc = KC_MS_UP,
  .end_kc = KC_MS_ACCEL2,
  .key_strings =
    "MS_U\0"
    "MS_D\0"
    "MS_L\0"
    "MS_R\0"
    "BTN1\0"
    "BTN2\0"
    "BTN3\0"
    "BTN4\0"
    "BTN5\0"
    "WH_U\0"
    "WH_D\0"
    "WH_L\0"
    "WH_R\0"
    "ACL0\0"
    "ACL1\0"
    "ACL2\0"
};

const key_string_map_t rgb_keys = {
  .start_kc = RGB_TOG,
  .end_kc = RGB_MODE_RGBTEST,
  .key_strings =
    "TOG\0"
    "MOD\0"
    "RMOD\0"
    "HUI\0"
    "HUD\0"
    "SAI\0"
    "SAD\0"
    "VAI\0"
    "VAD\0"
    "SPI\0"
    "SPD\0"
    "M_P\0"
    "M_B\0"
    "M_R\0"
    "M_SW\0"
    "M_SN\0"
    "M_K\0"
    "M_X\0"
    "M_G\0"
};

const key_string_map_t magic_keys = {
  .start_kc = RESET,
  .end_kc = MAGIC_TOGGLE_NKRO,
  .key_strings =
    "RESET\0"
    "DEBUG\0"
    "SWAP_CONTROL_CAPSLOCK\0"
    "CAPSLOCK_TO_CONTROL\0"
    "SWAP_LALT_LGUI\0"
    "SWAP_RALT_RGUI\0"
    "NO_GUI\0"
    "SWAP_GRAVE_ESC\0"
    "SWAP_BACKSLASH_BACKSPACE\0"
    "HOST_NKRO\0"
    "SWAP_ALT_GUI\0"
    "UNSWAP_CONTROL_CAPSLOCK\0"
    "UNCAPSLOCK_TO_CONTROL\0"
    "UNSWAP_LALT_LGUI\0"
    "UNSWAP_RALT_RGUI\0"
    "UNNO_GUI\0"
    "UNSWAP_GRAVE_ESC\0"
    "UNSWAP_BACKSLASH_BACKSPACE\0"
    "UNHOST_NKRO\0"
    "UNSWAP_ALT_GUI\0"
    "TOGGLE_NKRO\0"
};

const key_string_map_t shifted_keys1 = {
  .start_kc = KC_EXLM,
  .end_kc = KC_RPRN,
  .key_strings =
      "EXLM\0" "AT\0" "HASH\0" "DLR\0" "PERC\0"
      "CIRC\0" "AMPR\0" "ASTR\0" "LPRN\0" "RPRN\0"
};

const key_string_map_t shifted_keys2 = {
  .start_kc = KC_UNDS,
  .end_kc = KC_QUES,
  .key_strings =
      "UNDS\0" "PLUS\0" "LCBR\0" "RCBR\0" "PIPE\0"
      "\0" "COLN\0" "DQUO\0" "TILD\0" "LT\0" "RT\0" "QUES\0"
};

const key_string_map_t jp_keys1 = {
  .start_kc = JP_MINS,
  .end_kc = JP_SLSH,
  .key_strings =
    "MINS\0"
    "CIRC\0"
    "AT\0"
    "LBRC\0"
    "\0"
    "RBRC\0"
    "SCLN\0"
    "COLN\0"
    "ZHTG\0"
    "COMM\0"
    "DOT\0"
    "SLSH\0"
};

const key_string_map_t jp_ascii1 = {
  .start_kc = JP_MINS,
  .end_kc = JP_SLSH,
  .key_strings =
    "-\0"
    "^\0"
    "@\0"
    "[\0"
    "\0"
    "]\0"
    ";\0"
    ":\0"
    "\0" // "ZHTG\0"
    "\\,\0"
    ".\0"
    "/\0"
};

const key_string_map_t jp_keys2 = {
  .start_kc = JP_BSLS,
  .end_kc = JP_MEISU,
  .key_strings =
    "BSLS\0"
    "KANA\0"
    "YEN\0"
    "HENK\0"
    "MHEN\0"
    "\0\0\0\0"
    "MKANA\0"
    "MEISU\0"
};

const key_string_map_t jp_ascii2 = {
  .start_kc = JP_BSLS,
  .end_kc = JP_MEISU,
  .key_strings =
    "\0" // "BSLS\0"
    "\0" // "KANA\0"
    "\\\\\0"
    "\0" // "HENK\0"
    "\0" // "MHEN\0"
    "\0\0\0\0"
    "\0" //"MKANA\0"
    "\0" //"MEISU\0"
};

const key_string_map_t jp_keys3 = {
  .start_kc = JP_EXLM,
  .end_kc = JP_QUES,
  .key_strings =
    "EXLM\0"
    "DQUO\0"
    "HASH\0"
    "DLR\0"
    "PERC\0"
    "AMPR\0"
    "QUOT\0"
    "LPRN\0"
    "RPRN\0"
    "\0\0\0\0\0\0"
    "EQL\0"
    "TILD\0"
    "GRV\0"
    "LCBR\0"
    "\0"
    "RCBR\0"
    "PLUS\0"
    "ASTR\0"
    "\0"
    "LT\0"
    "GT\0"
    "QUES\0"
};

const key_string_map_t jp_ascii3 = {
  .start_kc = JP_EXLM,
  .end_kc = JP_QUES,
  .key_strings =
    "!\0"
    "\\\"\0"
    "#\0"
    "$\0"
    "%\0"
    "&\0"
    "'\0"
    "(\0"
    ")\0"
    "\0\0\0\0\0\0"
    "=\0"
    "~\0"
    "`\0"
    "{\0"
    "\0"
    "}\0"
    "+\0"
    "*\0"
    "\0"
    "<\0"
    ">\0"
    "?\0"
};

const key_string_map_t jp_keys4 = {
  .start_kc = JP_UNDS,
  .end_kc = JP_PIPE,
  .key_strings =
    "UNDS\0"
    "\0"
    "PIPE\0"
};

const key_string_map_t jp_ascii4 = {
  .start_kc = JP_UNDS,
  .end_kc = JP_PIPE,
  .key_strings =
    "_\0"
    "\0"
    "|\0"
};

const key_string_map_t ascii_keys1 = {
  .start_kc = KC_A,
  .end_kc = KC_0,
  .key_strings =
    "a\0b\0c\0d\0e\0f\0g\0h\0i\0j\0k\0l\0m\0n\0o\0p\0q\0"
    "r\0s\0t\0u\0v\0w\0x\0y\0z\0"
    "1\0""2\0"
    "3\0""4\0""5\0""6\0""7\0""8\0""9\0""0\0"
};

const key_string_map_t ascii_keys2 = {
  .start_kc = KC_MINS,
  .end_kc = KC_SLSH,
  .key_strings =
    "-\0=\0[\0]\0"
    "\\\\\0\0;\0'\0`\0\\,\0.\0/\0"
};

const key_string_map_t ascii_keys3 = {
  .start_kc = KC_EXLM,
  .end_kc = KC_RPRN,
  .key_strings =
    "!\0@\0#\0$\0%\0^\0&\0*\0(\0)\0"
};

const key_string_map_t ascii_keys4 = {
  .start_kc = KC_UNDS,
  .end_kc = KC_QUES,
  .key_strings =
    "_\0+\0{\0}\0|\0|\0:\0"
    "\\\"\0~\0<\0>\0?\0"
};

const key_string_map_t custom_keys_bmp = {
  .start_kc = SAFE_RANGE,
  .end_kc = xKANA,
  .key_strings=
    "BLE_DIS\0"
    "BLE_EN\0"
    "USB_DIS\0"
    "USB_EN\0"
    "SEL_BLE\0"
    "SEL_USB\0"
    "ADV_ID0\0"
    "ADV_ID1\0"
    "ADV_ID2\0"
    "ADV_ID3\0"
    "ADV_ID4\0"
    "ADV_ID5\0"
    "ADV_ID6\0"
    "ADV_ID7\0"
    "AD_WO_L\0"
    "DEL_ID0\0"
    "DEL_ID1\0"
    "DEL_ID2\0"
    "DEL_ID3\0"
    "DEL_ID4\0"
    "DEL_ID5\0"
    "DEL_ID6\0"
    "DEL_ID7\0"
    "DELBNDS\0"
    "ENT_DFU\0"
    "ENT_WEB\0"
    "ENT_SLP\0"
    "BATT_LV\0"
    "SAVE_EE\0"
    "DEL_EE\0"
    "xEISU\0"
    "xKANA\0"
};

typedef enum
{
  MAP_REGULAR,
  MAP_SHIFTED_1,
  MAP_SHIFTED_2,
  MAP_MOD,
  MAP_SYS_CONSUMER,
  MAP_MOUSE,
  MAP_RGB,
  MAP_MAGIC,
} KEY_STRING_MAP_IDX;

const key_string_map_t* key_string_maps[] = {
  [MAP_REGULAR] = &regular_keys,
  [MAP_SHIFTED_1] = &shifted_keys1,
  [MAP_SHIFTED_2] = &shifted_keys2,
  [MAP_MOD] = &modifiers,
  [MAP_SYS_CONSUMER] = &system_and_consumers,
  [MAP_MOUSE] = &mouse_keys,
  [MAP_RGB] = &rgb_keys,
  [MAP_MAGIC] = &magic_keys,
};

const key_string_map_t* key_ascii_maps[] = {
  &ascii_keys1,
  &ascii_keys2,
  &ascii_keys3,
  &ascii_keys4,
};

const key_string_map_t* key_ascii_maps_jp[] = {
};

const key_string_map_t* key_jp_maps[] = {
  &jp_keys1,
  &jp_keys2,
  &jp_keys3,
  &jp_keys4,
};

const key_string_map_t* key_jp_maps_ascii[] = {
  &jp_ascii1,
  &jp_ascii2,
  &jp_ascii3,
  &jp_ascii4,
};

extern const key_string_map_t custom_keys_user;
const key_string_map_t* key_custom_maps[] =
{
    &custom_keys_bmp,
    &custom_keys_user,
};

#define ARRAY_LEN(x) sizeof(x)/sizeof(x[0])

uint8_t copy_key_string(char* dst, const char* src, uint8_t len) {
  int i;
  for (i=0; i<len-1; i++) {
    if (src[i] != '\0') {
      dst[i] = src[i];
    } else {
      break;
    }
  }
  dst[i] = '\0';
  return i;
}

const char* get_keycode_string(const key_string_map_t *const * map,
    uint32_t map_len, uint16_t kc) {
  int i, j;
  const char* pstr;
  for (i = 0; i < map_len; i++) {
    if (kc >= map[i]->start_kc
        && kc <= map[i]->end_kc) {
      pstr = map[i]->key_strings;
      for(j = 0; j < kc - map[i]->start_kc; j++) {
        while (*pstr++ != '\0') continue;
      }
      return pstr;
    }
  }
  return NULL;
}

uint8_t keycode2str(uint8_t kc, char* str, uint8_t len) {
  return copy_key_string(str,
     get_keycode_string(key_string_maps, ARRAY_LEN(key_string_maps), kc), len);
}

const char * get_keycode_string_locale(uint16_t kc, KEYMAP_LOCALE locale,
  bool use_ascii_char) {

  const char* pstr = NULL;
  switch(locale){
    case LOCALE_JP:
    {
      if (use_ascii_char)
      {
        pstr = get_keycode_string(key_jp_maps_ascii,
          ARRAY_LEN(key_jp_maps_ascii), kc);
      }
      if (pstr == NULL || *pstr == '\0')
      {
        pstr = get_keycode_string(key_jp_maps, ARRAY_LEN(key_jp_maps), kc);
      }
    }
    break;

    case LOCALE_US:
    default:
    {
      if (use_ascii_char)
      {
        pstr = get_keycode_string(key_ascii_maps,
          ARRAY_LEN(key_ascii_maps), kc);
      }
    }
    break;
  }

  if (pstr == NULL || *pstr == '\0')
  {
    pstr = get_keycode_string(key_string_maps,
      ARRAY_LEN(key_string_maps), kc);
  }
  if (pstr == NULL || *pstr == '\0')
  {
    pstr = get_keycode_string(key_custom_maps,
      ARRAY_LEN(key_custom_maps), kc);
  }
  return pstr;
}

const char* modbit[] = {"CTL", "SFT", "ALT", "GUI"};
uint8_t modbit2str(uint8_t mod, char* str, uint8_t len) {
  int i;
  char *pstr = str;
  uint8_t capa = len-1;
  for(i=0; i<4; i++) {
    if(mod & (1<<i)) {
      if(pstr != str && capa) {
        *pstr++ = '|';
        capa--;
      }
      if(capa > 4) {
        *pstr++ = (mod & 0x80) ? 'R' : 'L';
        capa--;
        memcpy(pstr, modbit[i], 3);
        pstr += 3;
        capa -= 3;
      } else {
        break;
      }
    }
  }
  *pstr = '\0';
  return len - capa + 1;
}

#define case_mod2prefix(mod) \
case MOD_ ## mod: \
  strncpy(str, #mod, len); \
  break;

uint8_t modbit2prefix(uint8_t mod, char* str, uint8_t len) {
  uint8_t found = 1;
  switch (mod)
  {
  case_mod2prefix(LCTL);
  case_mod2prefix(LSFT);
  case_mod2prefix(LALT);
  case_mod2prefix(LGUI);
  case_mod2prefix(RSFT);
  case_mod2prefix(RCTL);
  case_mod2prefix(RALT);
  case_mod2prefix(RGUI);
  case MOD_LCTL | MOD_LSFT:
  strncpy(str, "C_S", len);
  break;
  case MOD_LCTL | MOD_LSFT | MOD_LALT:
  strncpy(str, "MEH", len);
  break;
  case MOD_LCTL | MOD_LALT | MOD_LGUI:
  strncpy(str, "LCAG", len);
  break;
  case MOD_RCTL | MOD_RALT | MOD_RGUI:
  strncpy(str, "RCAG", len);
  break;
  case MOD_LCTL | MOD_LALT | MOD_LGUI | MOD_LSFT:
  strncpy(str, "ALL", len);
  break;
  case MOD_LGUI | MOD_LSFT:
  strncpy(str, "SGUI", len);
  break;
  case MOD_LCTL | MOD_LALT:
  strncpy(str, "LCA", len);
  break;
  default:
    found = 0;
  break;
  }
  return found;
}

#define case_proc_qkc(code, locale, use_ascii, ...) \
{                                                                   \
    keycode_str = get_keycode_string_locale(code, locale, use_ascii);\
    if(keycode_str!= NULL) {                                        \
      copied_len = snprintf(str, len, __VA_ARGS__);        \
    } else {                                                        \
      copied_len = snprintf(str, len, "ANY(%d)", qk);               \
    }                                                               \
}

const char *keycode_prefix[] =
{
  [LOCALE_US] = "KC_",
  [LOCALE_JP] = "JP_",
};

uint8_t quantum_keycode2str_locale(uint16_t qk, char* str, uint32_t len,
  KEYMAP_LOCALE locale, bool use_ascii)
{
  uint8_t kc = qk & 0xFF;
  uint8_t copied_len = 0;
  const char* keycode_str=NULL;
  char mod_str[20];
  const char* kc_prefix = keycode_prefix[LOCALE_US];

  switch(locale) {
    case LOCALE_JP:
    for (int i=0; i<ARRAY_LEN(key_jp_maps); i++)
    {
      if ( (kc >= key_jp_maps[i]->start_kc && kc <= key_jp_maps[i]->end_kc)
            || (qk >= key_jp_maps[i]->start_kc && qk <= key_jp_maps[i]->end_kc)
         )
      {
        kc_prefix = keycode_prefix[LOCALE_JP];
      }
    }
    break;
    default:
    break;
  }

  switch(qk) {
  case QK_BASIC...QK_BASIC_MAX:
  case_proc_qkc(qk, locale, use_ascii, "%s%s", kc_prefix, keycode_str);
  break;

  case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
  case_proc_qkc(kc, locale, use_ascii, "LT(%d,%s%s)", (qk >> 8) & 0xF, kc_prefix,
    keycode_str);
  break;

  case QK_TO...QK_TO_MAX:
  copied_len = snprintf(str, len, "TO(%d)", qk & 0x0F);        \
  break;

  case QK_MOMENTARY...QK_MOMENTARY_MAX:
  copied_len = snprintf(str, len, "MO(%d)", qk & 0xFF);        \
  break;

  case QK_DEF_LAYER...QK_DEF_LAYER_MAX:
  copied_len = snprintf(str, len, "DF(%d)", qk & 0xFF);        \
  break;

  case QK_MODS...QK_MODS_MAX:
  switch (qk)
  {
    case KC_EXLM...KC_RPRN:
    case_proc_qkc(qk, locale, use_ascii,  "%s%s", kc_prefix, keycode_str);
    break;

    case KC_UNDS...KC_QUES:
    case_proc_qkc(qk, locale, use_ascii, "%s%s", kc_prefix, keycode_str);
    break;

    default:
    if ((qk >> 8) == 0x0F)
    {
      strncpy(mod_str, "HYPR", sizeof("HYPR")); // Use hyper for MODS and Use all for tap
    }
    else
    {
      uint8_t found = modbit2prefix((qk >> 8) & 0x1F, mod_str, sizeof(mod_str));
      if (!found) {
        copied_len = snprintf(str, len, "ANY(%d)", qk);
        break;
      }
    }
    case_proc_qkc(kc, locale, use_ascii, "%s(%s%s)", mod_str, kc_prefix, keycode_str);
    break;
  }
  break;

  case QK_TOGGLE_LAYER...QK_TOGGLE_LAYER_MAX:
  copied_len = snprintf(str, len, "TG(%d)", qk & 0xFF);        \
  break;

  case QK_ONE_SHOT_LAYER...QK_ONE_SHOT_LAYER_MAX:
  copied_len = snprintf(str, len, "OSL(%d)", qk & 0xFF);        \
  break;

  case QK_MOD_TAP...QK_MOD_TAP_MAX:
  if (modbit2prefix((qk >> 8) & 0x1F, mod_str, sizeof(mod_str))) {
    case_proc_qkc(kc, locale, use_ascii, "%s_T(%s%s)", mod_str, kc_prefix, keycode_str);
  } else {
    copied_len = snprintf(str, len, "ANY(%d)", qk);
  }
  break;

  case RGB_TOG...RGB_MODE_RGBTEST:
  case_proc_qkc(qk, locale, use_ascii, "RGB_%s", keycode_str);
  break;

  case RESET:
  copied_len = snprintf(str, len,"RESET");
  break;

  case MAGIC_SWAP_CONTROL_CAPSLOCK...MAGIC_TOGGLE_NKRO:
  case_proc_qkc(qk, locale, use_ascii, "MAGIC_%s", keycode_str);
  break;

  default:
  case_proc_qkc(qk, locale, use_ascii, "%s", keycode_str);
  break;
  }

  return copied_len;
}

// default setting
uint8_t quantum_keycode2str(uint16_t qk, char* str, uint32_t len) {
  return quantum_keycode2str_locale(qk, str, len, LOCALE_US, false);
}

typedef enum
{
 KC, JP, MO, TG, TO, TT, DF, OSL, LT, MT,
 RGB, MAGIC, ANY,
 LCTL, LSFT, LALT, LGUI, RCTL, RSFT, RALT, RGUI,
 LCA, MEH, ALL, C_S,
 HYPR, LCAG, RCAG, SGUI, EX,
} QK_PREFIX_STRING;
#define PREFIX_PAIR(prefix) [prefix]= #prefix

bool check_prefix(const char* str, const char* prefix)
{
  for (int i=0; i<16; i++)
  {
    if (prefix[i] == '\0')
    {
      return true;
    }
    else if (str[i] == '\0' || str[i] != prefix[i])
    {
      return false;
    }
  }
  return false;
}

uint16_t convert_kc_helper(const char* str, uint8_t len,
  const key_string_map_t * const * pkey_string_maps, uint32_t map_len,
  uint32_t map_idx_start)
{
  const char * kc_string;
  bool match = false;

  if (map_idx_start >= map_len)
  {
    // start map index overs defined map
    return KC_NO;
  }

  // convert based on keycode-string maps
  for (int i = map_idx_start; i < map_len; i++)
  {
    kc_string = pkey_string_maps[i]->key_strings;
    for (int str_idx = 0;
        str_idx < (pkey_string_maps[i]->end_kc - pkey_string_maps[i]->start_kc + 1);
        str_idx++)
    {
      match = true;
      for (int char_idx = 0; char_idx < len; char_idx++)
      {
        if (str[char_idx] != *kc_string || *kc_string == '\0')
        {
          match = false;
          break;
        }
        kc_string++;
      }
      if (match && *kc_string == '\0')
      {
        return pkey_string_maps[i]->start_kc + str_idx;
      }

      // search next kc string
      while (*(kc_string++) != '\0') { continue; }
    }
  }
  return KC_NO;
}

typedef uint16_t (*kc_convert_func_t)(const char*, uint8_t, uint8_t);
// convert string to keycode
uint16_t convert_kc(const char* str, uint8_t len, uint8_t key_string_map)
{
  uint16_t kc = KC_NO;

  kc = convert_kc_helper(str, len, key_string_maps, ARRAY_LEN(key_string_maps),
    key_string_map);
  if (kc != KC_NO) return kc;

  kc = convert_kc_helper(str, len, key_custom_maps, ARRAY_LEN(key_custom_maps),
    0);
  if (kc != KC_NO) return kc;

  kc = convert_kc_helper(str, len, key_ascii_maps, ARRAY_LEN(key_ascii_maps),
    0);
  if (kc != KC_NO) return kc;

  return KC_NO;
}

// convert string to keycode
uint16_t convert_jp(const char* str, uint8_t len, uint8_t key_string_map)
{
  uint16_t kc;
  kc = convert_kc_helper(str, len, key_jp_maps, ARRAY_LEN(key_jp_maps), key_string_map);
  if (kc != KC_NO) return kc;

  kc = convert_kc_helper(str, len, key_custom_maps, ARRAY_LEN(key_custom_maps),
    0);
  if (kc != KC_NO) return kc;

  kc = convert_kc_helper(str, len, key_jp_maps_ascii, ARRAY_LEN(key_jp_maps_ascii),
    0);
  if (kc != KC_NO) return kc;

  kc = convert_kc(str, len, 0);
  if (kc != KC_NO) return kc;

  return KC_NO;
}

kc_convert_func_t convert_func_array[] = {
    [LOCALE_US] = convert_kc,
    [LOCALE_JP] = convert_jp,
};

uint16_t convert_lt(const char* str, uint8_t len, KEYMAP_LOCALE locale)
{
  unsigned int layer;
  char kc_str[16];
  int i;

  layer = atoi(str);
  while (*(str++) != ',') { continue; }
  while (*(str) == ' ') { str++; continue; }
  for (i=0; i<sizeof(kc_str) && *str != ')' && *str != ' '; i++)
  {
    kc_str[i] = *(str++);
  }
  kc_str[i] = 0;
  uint16_t kc = str2quantum_keycode_locale(kc_str, i, locale);

  return LT(layer, kc);
}

uint16_t convert_layer_key(const char* str, uint8_t len, QK_PREFIX_STRING prefix_idx)
{
  uint8_t layer;
  layer = (uint8_t)atoi(str);
  switch (prefix_idx)
  {
  case MO:
    return MO(layer);
  case TO:
    return TO(layer);
  case DF:
    return DF(layer);
  case TG:
    return TG(layer);
  case OSL:
    return OSL(layer);
  default:
    return KC_NO;
  }
}

uint16_t convert_kc_with_single_mod(const char *str, uint8_t len, uint8_t mod_idx,
    KEYMAP_LOCALE locale)
{
  uint16_t kc;
  uint16_t mod_bit = (mod_idx < 4) ? (1<<mod_idx) : (0x10 | (1<<(mod_idx-4)));

  if (str[0] == 'T' && str[1] == '(')
  {
    kc = str2quantum_keycode_locale(str+2, len-3, locale); // skip T( and )
    return MT(mod_bit, kc);
  }
  else
  {
    kc = str2quantum_keycode_locale(str, len-1, locale); // skip )
    return (mod_bit << 8) |kc;
  }
  return KC_NO;
}

uint16_t convert_kc_with_mods(const char *str, uint8_t len, QK_PREFIX_STRING prefix_idx, KEYMAP_LOCALE locale)
{
  uint16_t kc;
  uint16_t mod_bit;

  switch (prefix_idx)
  {
  case LCA:
    mod_bit = MOD_LCTL | MOD_LALT;
    break;
  case MEH:
    mod_bit = MOD_LCTL | MOD_LSFT | MOD_LALT;
    break;
  case ALL:
  case HYPR:
    mod_bit = MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI;
    break;
  case C_S:
    mod_bit = MOD_LCTL | MOD_LSFT;
    break;
  case LCAG:
    mod_bit = MOD_LCTL | MOD_LALT | MOD_LGUI;
    break;
  case RCAG:
    mod_bit = MOD_RCTL | MOD_RALT | MOD_RGUI;
    break;
  case SGUI:
    mod_bit = MOD_LSFT | MOD_LGUI;
    break;
  default:
    mod_bit = 0;
    break;
  }

  if (str[0] == 'T' && str[1] == '(')
  {
    kc = str2quantum_keycode_locale(str+2, len-3, locale); // skip T( and )
    return MT(mod_bit, kc);
  }
  else
  {
    kc = str2quantum_keycode_locale(str, len - 1, locale); // skip )
    return (mod_bit << 8) |kc;
  }
  return KC_NO;
}

uint16_t get_kc_strlen(const char* str, uint16_t len)
{
    int idx;
    int pcnt = 0;
    for (idx=0; idx<len; idx++)
    {
        if (str[idx] == '\\')
        {
            idx++;
            continue;
        }
        else if (str[idx] == '(')
        {
            pcnt++;
        }
        else if (str[idx] == ')')
        {
            pcnt--;
            if (pcnt == 0)
            {
                return idx + 1;
            }
            else if (pcnt == -1)
            {
                return idx;
            }
        }
        else if (str[idx] == ',' && pcnt == 0)
        {
            return idx;
        }
    }

    return len;
}

uint16_t get_inner_element(const char** pp_str, uint16_t len)
{
    const char *str = *pp_str;
    int idx;
    int paren_open;

    // find first (
    for (idx=0; idx<len; idx++)
    {
        if (str[idx] == '(')
        {
            break;
        }
    }

    if (idx == len) return len;
    paren_open = idx + 1;

    // find last )
    for (idx=len-1; idx > paren_open; idx--)
    {
        if (str[idx] == ')')
        {
            break;
        }
    }
    if (idx == paren_open) return len;

    *pp_str = &str[paren_open];
    return idx - paren_open;
}

uint16_t get_element_array(const char* str, uint16_t len,
    const char **pp_element, uint16_t* element_len, uint16_t buf_len)
{
    int idx;
    int paren_open;
    const char *element_start = str;
    uint16_t element_num = 0;

    // find first (
    for (idx=0; idx<len; idx++)
    {
        if (str[idx] == '\\')
        {
            // skip next charactar
            idx++;
            continue;
        }
        else if (str[idx] == ',')
        {
            pp_element[element_num] = element_start;
            element_len[element_num] = &str[idx] - element_start;
            element_start = str + idx + 1;

            element_num++;
            if (element_num >= buf_len)
            {
                break;
            }
        }
        else if (str[idx] == '(')
        {
            paren_open = idx;
            for (idx=paren_open; idx < len; idx++)
            {
                if (str[idx] == ')')
                {
                    break;
                }
            }
            if (idx == len)
            {
                idx = paren_open;
            }
        }
        else if (str[idx] == ' ' && element_start == &str[idx])
        {
            // skip white space on start
            element_start++;
        }
    }

    if (element_num < buf_len)
    {
        pp_element[element_num] = element_start;
        element_len[element_num] = &str[idx] - element_start;
        element_start = str + idx + 1;

        element_num++;
    }

    return element_num;
}

uint16_t str2quantum_keycode_locale(const char* str, uint32_t len,
    KEYMAP_LOCALE locale)
{
  const char * prefix_str[] = {
      PREFIX_PAIR(KC),
      PREFIX_PAIR(JP),
      PREFIX_PAIR(MO),
      PREFIX_PAIR(TG),
      PREFIX_PAIR(TO),
      PREFIX_PAIR(TT),
      PREFIX_PAIR(DF),
      PREFIX_PAIR(OSL),
      PREFIX_PAIR(LT),
      PREFIX_PAIR(MT),
      PREFIX_PAIR(RGB),
      PREFIX_PAIR(MAGIC),
      PREFIX_PAIR(ANY),
      PREFIX_PAIR(LCTL),
      PREFIX_PAIR(LSFT),
      PREFIX_PAIR(LALT),
      PREFIX_PAIR(LGUI),
      PREFIX_PAIR(RCTL),
      PREFIX_PAIR(RSFT),
      PREFIX_PAIR(RALT),
      PREFIX_PAIR(RGUI),
      PREFIX_PAIR(LCA),
      PREFIX_PAIR(MEH),
      PREFIX_PAIR(ALL),
      PREFIX_PAIR(C_S),
      PREFIX_PAIR(HYPR),
      PREFIX_PAIR(LCAG),
      PREFIX_PAIR(RCAG),
      PREFIX_PAIR(SGUI),
      PREFIX_PAIR(EX),
  };

  int prefix_idx=0;
  for (prefix_idx=0; prefix_idx<ARRAY_LEN(prefix_str); prefix_idx++)
  {
    if (check_prefix(str, prefix_str[prefix_idx]))
    {
      break;
    }
  }

  kc_convert_func_t conv = convert_func_array[locale];

  uint32_t prefix_len = 0;

  if (prefix_idx < ARRAY_LEN(prefix_str))
  {
     prefix_len = strlen(prefix_str[prefix_idx]) + 1; // prefix + (
  }

  uint16_t kc;
  switch ((QK_PREFIX_STRING)prefix_idx)
  {
  case KC:
	  return conv(str + prefix_len, len-prefix_len, MAP_REGULAR);
    break;
  case JP:
	  return convert_jp(str + prefix_len, len-prefix_len, 0);
    break;
  case LT:
	  return convert_lt(str + prefix_len, len-prefix_len, locale);
    break;
  case MO...DF:
	  return convert_layer_key(str + prefix_len, len-prefix_len, prefix_idx);
    break;
  case OSL:
	  return convert_layer_key(str + prefix_len, len-prefix_len, prefix_idx);
    break;
  case RGB:
	  return conv(str + prefix_len, len-prefix_len, MAP_RGB);
    break;
  case MAGIC:
	  return conv(str + prefix_len, len-prefix_len, MAP_MAGIC);
  case ANY:
    kc = atoi(str + prefix_len);
    if (kc == KC_NO)
    {
      kc = str2quantum_keycode_locale(str + prefix_len, len-prefix_len-1, locale);
    }
	return kc;
    break;
  case LCTL...RGUI:
	  return convert_kc_with_single_mod(str + prefix_len, len-prefix_len, prefix_idx - (int)LCTL, locale);
  case LCA...C_S:
	  return convert_kc_with_mods(str + prefix_len, len-prefix_len, prefix_idx, locale);
  case HYPR...SGUI:
	  return convert_kc_with_mods(str + prefix_len, len-prefix_len, prefix_idx, locale);
  case EX:
      return EXKC_START;
  default:
	  return conv(str, len, 0);
    break;
  }
  return 0;
}
uint16_t str2quantum_keycode(const char* str, uint32_t len)
{
  return str2quantum_keycode_locale(str, len, LOCALE_US);
}

#define STR_MATCH(str, key) (strncmp(str, key, sizeof(key)-1) == 0)
uint8_t str2locale(const char *str)
{
  if (STR_MATCH(str, "US"))
  {
    return LOCALE_US;
  }
  else if (STR_MATCH(str, "JP"))
  {
    return LOCALE_JP;
  }

  return LOCALE_US;
}

void locale2str(KEYMAP_LOCALE locale, char *str, uint32_t len)
{
  switch (locale)
  {
    case LOCALE_JP:
    strncpy(str, "JP", len);
    break;
    default:
    strncpy(str, "US", len);
    break;
  }
}
