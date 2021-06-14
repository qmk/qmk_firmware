#include "quantum.h"
#include "command.h"
#include "action_pseudo_lut.h"

static uint8_t send_key_shift_bit[SHIFT_BIT_SIZE];

/*
 * Pseudo layout action.
 * This action converts a keycode in order to output the character according to the keymap you specified
 * still your keyboard layout recognized wrongly on your OS.
 * Memo: Using other layer keymap to get keycode
 */
void action_pseudo_lut(keyrecord_t *record, uint8_t base_keymap_id, const uint16_t (*keymap)[2]) {
  uint8_t prev_shift;
  uint16_t keycode;
  uint16_t pseudo_keycode;

  /* get keycode from keymap you specified */
  keycode = keymap_key_to_keycode(base_keymap_id, record->event.key);

  prev_shift = keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));

  if (record->event.pressed) {
    /* when magic commands entered, keycode does not converted */
    if (IS_COMMAND()) {
      if (prev_shift) {
        add_shift_bit(keycode);
      }
      register_code(keycode);
      return;
    }

    if (prev_shift) {
      pseudo_keycode = convert_keycode(keymap, keycode, true);
      dprintf("pressed: %02X, converted: %04X\n", keycode, pseudo_keycode);
      add_shift_bit(keycode);

      if (IS_LSFT(pseudo_keycode)) {
        register_code(QK_LSFT ^ pseudo_keycode);
      } else {
        /* delete shift mod temporarily */
        del_mods(prev_shift);
        send_keyboard_report();
        register_code(pseudo_keycode);
        add_mods(prev_shift);
        send_keyboard_report();
      }
    } else {
      pseudo_keycode = convert_keycode(keymap, keycode, false);
      dprintf("pressed: %02X, converted: %04X\n", keycode, pseudo_keycode);

      if (IS_LSFT(pseudo_keycode)) {
        add_weak_mods(MOD_BIT(KC_LSFT));
        send_keyboard_report();
        register_code(QK_LSFT ^ pseudo_keycode);
        /* on Windows, prevent key repeat to avoid unintended output */
        unregister_code(QK_LSFT ^ pseudo_keycode);
        del_weak_mods(MOD_BIT(KC_LSFT));
        send_keyboard_report();
      } else {
        register_code(pseudo_keycode);
      }
    }
  } else {
    if (get_shift_bit(keycode)) {
      del_shift_bit(keycode);
      pseudo_keycode = convert_keycode(keymap, keycode, true);
    } else {
      pseudo_keycode = convert_keycode(keymap, keycode, false);
    }
    dprintf("released: %02X, converted: %04X\n", keycode, pseudo_keycode);

    if (IS_LSFT(pseudo_keycode)) {
      unregister_code(QK_LSFT ^ pseudo_keycode);
    } else {
      unregister_code(pseudo_keycode);
    }
  }
}

uint16_t convert_keycode(const uint16_t (*keymap)[2], uint16_t keycode, bool shift_modded)
{
  uint16_t pseudo_keycode;

  switch (keycode) {
    case KC_A ... KC_CAPSLOCK:
      #if defined(__AVR__) 
        if (shift_modded) {
          pseudo_keycode = pgm_read_word(&keymap[keycode][1]);
        } else {
          pseudo_keycode = pgm_read_word(&keymap[keycode][0]);
        }
      #else
        if (shift_modded) {
          pseudo_keycode = keymap[keycode][1];
        } else {
          pseudo_keycode = keymap[keycode][0];
        }
      #endif
      /* if undefined, use got keycode as it is */
      if (pseudo_keycode == 0x00) {
        if (shift_modded) {
          pseudo_keycode = S(keycode);
        } else {
          pseudo_keycode = keycode;
        }
      }
      break;
    default:
      if (shift_modded) {
        pseudo_keycode = S(keycode);
      } else {
        pseudo_keycode = keycode;
      }
      break;
  }
  return pseudo_keycode;
}

uint8_t get_shift_bit(uint16_t keycode) {
  if ((keycode >> 3) < SHIFT_BIT_SIZE) {
    return send_key_shift_bit[keycode >> 3] & (1 << (keycode & 7));
  } else {
    dprintf("get_shift_bit: Can't get shift bit. keycode: %02X\n", keycode);
    return 0;
  }
}

void add_shift_bit(uint16_t keycode) {
  if ((keycode >> 3) < SHIFT_BIT_SIZE) {
    send_key_shift_bit[keycode >> 3] |= (1 << (keycode & 7));
  } else {
    dprintf("add_shift_bit: Can't add shift bit. keycode: %02X\n", keycode);
  }
}

void del_shift_bit(uint16_t keycode) {
  if ((keycode >> 3) < SHIFT_BIT_SIZE) {
    send_key_shift_bit[keycode >> 3] &= ~(1 << (keycode & 7));
  } else {
    dprintf("del_shift_bit: Can't delete shift bit. keycode: %02X\n", keycode);
  }
}
