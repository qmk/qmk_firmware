#ifndef KEYMAP_BR_ABNT2_H
#define KEYMAP_BR_ABNT2_H

#include "keymap_common.h"

/* Scan codes for the Brazilian ABNT2 keyboard layout */

#define BR_CCDL KC_SCLN      //  Ç   same scancode as ;: on US layout
#define BR_SCLN KC_SLSH      //  ;:  same scancode as /? on US layout
#define BR_QUOT KC_GRV       //  '"  same scancode as `~ on US layout
#define BR_TILD KC_QUOT      //  ~^  dead keys, same scancode as '" on US layout
#define BR_ACUT KC_LBRC      //  ´`  dead keys, same scancode as [{ on US layout
#define BR_LBRC KC_RBRC      //  [{  same scancode as ]} on US layout
#define BR_RBRC KC_BSLS      //  ]}  same scancode as \| on US layout
#define BR_BSLS KC_NUBS      //  \|  uses the non-US hash scancode (#~, sometimes §±)
#define BR_SLSH KC_INT1      //  /?  uses the INTL1 scancode

#define BR_COLN LSFT(BR_SCLN)   // shifted :
#define BR_DQT  LSFT(BR_QUOT)   // shifted "
#define BR_CIRC LSFT(BR_TILD)   // shifted ^ (dead key)
#define BR_GRAV LSFT(BR_ACUT)   // shifted ` (dead key)
#define BR_LCBR LSFT(BR_LBRC)   // shifted {
#define BR_RCBR LSFT(BR_RBRC)   // shifted }
#define BR_PIPE LSFT(BR_BSLS)   // shifted |
#define BR_QUES LSFT(BR_SLSH)   // shifted ?
#define BR_TRMA LSFT(KC_6)      // shifted ¨ (dead key - trema accent)

// On the ABNT2 the keypad comma and the keypad dot scancodes are switched
// (presumably because in Brazil comma is used as the decimal separator)
#define BR_KPDT KC_KP_COMMA  //  keypad .
#define BR_KPCM KC_KP_DOT    //  keypad ,

#define BR_1UP    LALT(KC_1)      // 1 superscript                    ¹   alt+1
#define BR_2UP    LALT(KC_2)      // 2 superscript                    ²   alt+2
#define BR_3UP    LALT(KC_3)      // 3 superscript                    ³   alt+3
#define BR_PND    LALT(KC_4)      // Pound sign                       £   alt+4
#define BR_CENT   LALT(KC_5)      // Cent sign                        ¢   alt+5
#define BR_NOT    LALT(KC_6)      // Not sign                         ¬   alt+6
#define BR_SECT   LALT(KC_EQL)    // Section sign                     §   alt+=
#define BR_FORD   LALT(BR_LBRC)   // Feminine Ordinal Sign            ª   alt+[
#define BR_MORD   LALT(BR_RBRC)   // Masculine Ordinal Sign           º   alt+]
#define BR_DGRE   LALT(BR_SLSH)   // Degree sign                      °   alt+/

#define BR_EURO   LALT(KC_E)      // Euro sign                        €   alt+e
#define BR_NDTD   LALT(BR_TILD)   // Non-dead key tilde               ~   alt+~
#define BR_NDAC   LALT(BR_ACUT)   // Non-dead key acute accent        ´   alt+´
#define BR_NDGV   LALT(BR_QUOT)   // Non-dead key grave accent        `   alt+'
#define BR_NDCR   LALT(BR_CIRC)   // Non-dead key circumflex accent   ^   alt+^ (alt+shift+~)
#define BR_NDTR   LALT(BR_TRMA)   // Non-dead key trema accent        ¨   alt+¨ (alt+shift+6)

// For 101-key keyboard layouts, the ABNT2 layout allows
// the slash and question mark to be typed using alt+q and alt+w.
// The shortcuts are provided here for completeness' sake,
// but it's recommended to use BR_SLSH and BR_QUES instead
#define BR_ASLS   LALT(KC_Q)
#define BR_AQST   LALT(KC_W)

#endif
