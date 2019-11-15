#include QMK_KEYBOARD_H
#include <string.h>

void dynamic_macro_init(void) {
  /* zero out macro blocks  */
  memset(&dynamic_macros, 0, DYNAMIC_MACRO_COUNT * sizeof(dynamic_macro_t));
}

/* Blink the LEDs to notify the user about some event. */
void dynamic_macro_led_blink(void) {
#ifdef BACKLIGHT_ENABLE
  backlight_toggle();
  wait_ms(100);
  backlight_toggle();
#else
  led_set(host_keyboard_leds() ^ 0xFF);
  wait_ms(100);
  led_set(host_keyboard_leds());
#endif
}

/**
 * Start recording of the dynamic macro.
 *
 * @param macro_id[in]     The id of macro to be recorded
 */
void dynamic_macro_record_start(uint8_t macro_id) {
  dprintf("dynamic macro recording: started for slot %d\n", macro_id);

  dynamic_macro_led_blink();

  clear_keyboard();
  layer_clear();

  dynamic_macros[macro_id].length = 0;
}

/**
 * Play the dynamic macro.
 *
 * @param macro_id[in]     The id of macro to be played
 */
void dynamic_macro_play(uint8_t macro_id) {
  dprintf("dynamic macro: slot %d playback, length %d\n", macro_id, dynamic_macros[macro_id].length);

  uint32_t saved_layer_state = layer_state;

  clear_keyboard();
  layer_clear();

  for (uint8_t i = 0; i < dynamic_macros[macro_id].length; ++i) {
    process_record(&dynamic_macros[macro_id].events[i]);
  }

  clear_keyboard();

  layer_state = saved_layer_state;
}

/**
 * Record a single key in a dynamic macro.
 *
 * @param macro_id[in] The start of the used macro buffer.
 * @param record[in]     The current keypress.
 */
void dynamic_macro_record_key(uint8_t macro_id, keyrecord_t* record) {
  dynamic_macro_t* macro  = &dynamic_macros[macro_id];
  uint8_t          length = macro->length;

  /* If we've just started recording, ignore all the key releases. */
  if (!record->event.pressed && length == 0) {
    dprintln("dynamic macro: ignoring a leading key-up event");
    return;
  }

  if (length < DYNAMIC_MACRO_SIZE) {
    macro->events[length] = *record;
    macro->length         = ++length;
  } else {
    dynamic_macro_led_blink();
  }

  dprintf("dynamic macro: slot %d length: %d/%d\n", macro_id, length, DYNAMIC_MACRO_SIZE);
}

/**
 * End recording of the dynamic macro. Essentially just update the
 * pointer to the end of the macro.
 */
void dynamic_macro_record_end(uint8_t macro_id) {
  dynamic_macro_led_blink();

  dynamic_macro_t* macro  = &dynamic_macros[macro_id];
  uint8_t          length = macro->length;

  keyrecord_t* events_begin   = &(macro->events[0]);
  keyrecord_t* events_pointer = &(macro->events[length - 1]);

  dprintf("dynamic_macro: macro length before trimming: %d\n", macro->length);
  while (events_pointer != events_begin && (events_pointer)->event.pressed) {
    dprintln("dynamic macro: trimming a trailing key-down event");
    --(macro->length);
    --events_pointer;
  }

#ifdef DYNAMIC_MACRO_EEPROM_STORAGE
  macro->checksum = dynamic_macro_calc_crc(macro);
  dynamic_macro_save_eeprom(macro_id);
#endif

  dprintf("dynamic macro: slot %d saved, length: %d\n", macro_id, length);
}

/* Handle the key events related to the dynamic macros. Should be
 * called from process_record_user() like this:
 *
 *   bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 *       if (!process_record_dynamic_macro(keycode, record)) {
 *           return false;
 *       }
 *       <...THE REST OF THE FUNCTION...>
 *   }
 */
bool process_record_dynamic_macro(uint16_t keycode, keyrecord_t* record) {
  /* 0 to DYNAMIC_MACRO_COUNT -1 - macro macro_id is being recorded */
  static uint8_t macro_id        = 255;
  static uint8_t recording_state = STATE_NOT_RECORDING;

  if (STATE_NOT_RECORDING == recording_state) {
    /* Program key pressed to request programming mode */
    if (keycode == DYN_MACRO_PROG && record->event.pressed) {
      dynamic_macro_led_blink();

      recording_state = STATE_RECORD_KEY_PRESSED;
      dprintf("dynamic macro: programming key pressed, waiting for macro slot selection. %d\n", recording_state);

      return false;
    }
    /* Macro key pressed to request macro playback */
    if (keycode >= DYN_MACRO_KEY1 && keycode <= DYN_MACRO_KEY12 && record->event.pressed) {
      dynamic_macro_play(keycode - DYN_MACRO_KEY1);

      return false;
    }

    /* Non-dynamic macro key, process it elsewhere. */
    return true;
  } else if (STATE_RECORD_KEY_PRESSED == recording_state) {
    /* Program key pressed again before a macro selector key, cancel macro recording.
       Blink leds to indicate cancelation. */
    if (keycode == DYN_MACRO_PROG && record->event.pressed) {
      dynamic_macro_led_blink();

      recording_state = STATE_NOT_RECORDING;
      dprintf("dynamic macro: programming key pressed, programming mode canceled. %d\n", recording_state);

      return false;
    } else if (keycode >= DYN_MACRO_KEY1 && keycode <= DYN_MACRO_KEY12 && record->event.pressed) {
      macro_id = keycode - DYN_MACRO_KEY1;

      /* Macro slot selected, enter recording state. */
      recording_state = STATE_CURRENTLY_RECORDING;
      dynamic_macro_record_start(macro_id);

      return false;
    }
    /* Ignore any non-macro key press while in RECORD_KEY_PRESSED state. */
    return false;
  } else if (STATE_CURRENTLY_RECORDING == recording_state) {
    /* Program key pressed to request end of macro recording. */
    if (keycode == DYN_MACRO_PROG && record->event.pressed) {
      dynamic_macro_record_end(macro_id);
      recording_state = STATE_NOT_RECORDING;

      return false;
    }
    /* Don't record other macro key presses. */
    else if (keycode >= DYN_MACRO_KEY1 && keycode <= DYN_MACRO_KEY12 && record->event.pressed) {
      dprintln("dynamic macro: playback key ignored in programming mode.");
      return false;
    }
    /* Non-macro keypress that should be recorded  */
    else {
      dynamic_macro_record_key(macro_id, record);

      /* Don't output recorded keypress. */
      return false;
    }
  }

  return true;
}

#ifdef __AVR__
#  include <util/crc16.h>
uint16_t dynamic_macro_calc_crc(dynamic_macro_t* macro) {
  uint16_t crc  = 0;
  uint8_t* data = (uint8_t*)macro;

  for (uint16_t i = 0; i < DYNAMIC_MACRO_CRC_LENGTH; ++i) {
    crc = _crc16_update(crc, *(data++));
  }
  return crc;
}
#endif /* __AVR__ */

inline void* dynamic_macro_eeprom_macro_addr(uint8_t macro_id) { 
    return DYNAMIC_MACRO_EEPROM_BLOCK0_ADDR + sizeof(dynamic_macro_t) * macro_id;
}

bool dynamic_macro_header_correct(void) { 
    return eeprom_read_word(DYNAMIC_MACRO_EEPROM_MAGIC_ADDR) == DYNAMIC_MACRO_EEPROM_MAGIC;
}

void dynamic_macro_load_eeprom_all(void) {
  if (!dynamic_macro_header_correct()) {
    dprintf("dynamic_macro: eeprom header not valid, not restoring macros.\n");
    return;
  }

  for (uint8_t i = 0; i < DYNAMIC_MACRO_COUNT; ++i) {
    dynamic_macro_load_eeprom(i);
  }
}

void dynamic_macro_load_eeprom(uint8_t macro_id) {
  dynamic_macro_t* dst = &dynamic_macros[macro_id];

  eeprom_read_block(dst, dynamic_macro_eeprom_macro_addr(macro_id), sizeof(dynamic_macro_t));

  /* Validate checksum, ifchecksum is NOT valid for macro, set its length to 0 to prevent its use. */
  if (dynamic_macro_calc_crc(dst) != dst->checksum) {
    dprintf("dynamic macro: slot %d not loaded, checksum mismatch\n", macro_id);
    dst->length = 0;

    return;
  }

  dprintf("dynamic macro: slot %d loaded from eeprom, checksum okay\n", macro_id);
}

void dynamic_macro_save_eeprom(uint8_t macro_id) {
  if (!dynamic_macro_header_correct()) {
    eeprom_write_word(DYNAMIC_MACRO_EEPROM_MAGIC_ADDR, DYNAMIC_MACRO_EEPROM_MAGIC);
    dprintf("dynamic macro: writing magic eeprom header\n");
  }

  dynamic_macro_t* src = &dynamic_macros[macro_id];

  eeprom_update_block(src, dynamic_macro_eeprom_macro_addr(macro_id), sizeof(dynamic_macro_t));
  dprintf("dynamic macro: slot %d saved to eeprom\n", macro_id);
}
