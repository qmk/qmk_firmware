/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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
#include "host.h"
#include "report.h"
#include "debug.h"
#include "action_util.h"
#include "action_layer.h"
#include "timer.h"
#include "keycode_config.h"
#include <quantum/quantum.h>

extern keymap_config_t keymap_config;

static uint8_t real_mods  = 0;
static uint8_t weak_mods  = 0;
static uint8_t macro_mods = 0;

#ifdef USB_6KRO_ENABLE
#    define RO_ADD(a, b) ((a + b) % KEYBOARD_REPORT_KEYS)
#    define RO_SUB(a, b) ((a - b + KEYBOARD_REPORT_KEYS) % KEYBOARD_REPORT_KEYS)
#    define RO_INC(a) RO_ADD(a, 1)
#    define RO_DEC(a) RO_SUB(a, 1)
static int8_t cb_head  = 0;
static int8_t cb_tail  = 0;
static int8_t cb_count = 0;
#endif

// TODO: pointer variable is not needed
// report_keyboard_t keyboard_report = {};
report_keyboard_t *keyboard_report = &(report_keyboard_t){};

extern inline void add_key(uint8_t key);
extern inline void del_key(uint8_t key);
extern inline void clear_keys(void);

#ifndef NO_ACTION_ONESHOT
static uint8_t oneshot_mods        = 0;
static uint8_t oneshot_locked_mods = 0;
uint8_t        get_oneshot_locked_mods(void) { return oneshot_locked_mods; }
void           set_oneshot_locked_mods(uint8_t mods) {
    if (mods != oneshot_locked_mods) {
        oneshot_locked_mods = mods;
        oneshot_locked_mods_changed_kb(oneshot_locked_mods);
    }
}
void clear_oneshot_locked_mods(void) {
    if (oneshot_locked_mods) {
        oneshot_locked_mods = 0;
        oneshot_locked_mods_changed_kb(oneshot_locked_mods);
    }
}
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
static uint16_t oneshot_time = 0;
bool            has_oneshot_mods_timed_out(void) { return TIMER_DIFF_16(timer_read(), oneshot_time) >= ONESHOT_TIMEOUT; }
#    else
bool has_oneshot_mods_timed_out(void) { return false; }
#    endif
#endif

/* oneshot layer */
#ifndef NO_ACTION_ONESHOT
/** \brief oneshot_layer_data bits
 * LLLL LSSS
 * where:
 *   L => are layer bits
 *   S => oneshot state bits
 */
static int8_t oneshot_layer_data = 0;

inline uint8_t get_oneshot_layer(void) { return oneshot_layer_data >> 3; }
inline uint8_t get_oneshot_layer_state(void) { return oneshot_layer_data & 0b111; }

#    ifdef SWAP_HANDS_ENABLE
enum {
    SHO_OFF,
    SHO_ACTIVE,   // Swap hands button was pressed, and we didn't send any swapped keys yet
    SHO_PRESSED,  // Swap hands button is currently pressed
    SHO_USED,     // Swap hands button is still pressed, and we already sent swapped keys
} swap_hands_oneshot = SHO_OFF;
#    endif

#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
static uint16_t oneshot_layer_time = 0;
inline bool     has_oneshot_layer_timed_out() { return TIMER_DIFF_16(timer_read(), oneshot_layer_time) >= ONESHOT_TIMEOUT && !(get_oneshot_layer_state() & ONESHOT_TOGGLED); }
#        ifdef SWAP_HANDS_ENABLE
static uint16_t oneshot_swaphands_time = 0;
inline bool     has_oneshot_swaphands_timed_out() { return TIMER_DIFF_16(timer_read(), oneshot_swaphands_time) >= ONESHOT_TIMEOUT && (swap_hands_oneshot == SHO_ACTIVE); }
#        endif
#    endif

#    ifdef SWAP_HANDS_ENABLE

void set_oneshot_swaphands(void) {
    swap_hands_oneshot = SHO_PRESSED;
    swap_hands         = true;
#        if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_swaphands_time = timer_read();
    if (oneshot_layer_time != 0) {
        oneshot_layer_time = oneshot_swaphands_time;
    }
#        endif
}

void release_oneshot_swaphands(void) {
    if (swap_hands_oneshot == SHO_PRESSED) {
        swap_hands_oneshot = SHO_ACTIVE;
    }
    if (swap_hands_oneshot == SHO_USED) {
        clear_oneshot_swaphands();
    }
}

void use_oneshot_swaphands(void) {
    if (swap_hands_oneshot == SHO_PRESSED) {
        swap_hands_oneshot = SHO_USED;
    }
    if (swap_hands_oneshot == SHO_ACTIVE) {
        clear_oneshot_swaphands();
    }
}

void clear_oneshot_swaphands(void) {
    swap_hands_oneshot = SHO_OFF;
    swap_hands         = false;
#        if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_swaphands_time = 0;
#        endif
}

#    endif

/** \brief Set oneshot layer
 *
 * FIXME: needs doc
 */
void set_oneshot_layer(uint8_t layer, uint8_t state) {
    oneshot_layer_data = layer << 3 | state;
    layer_on(layer);
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_layer_time = timer_read();
#    endif
    oneshot_layer_changed_kb(get_oneshot_layer());
}
/** \brief Reset oneshot layer
 *
 * FIXME: needs doc
 */
void reset_oneshot_layer(void) {
    oneshot_layer_data = 0;
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_layer_time = 0;
#    endif
    oneshot_layer_changed_kb(get_oneshot_layer());
}
/** \brief Clear oneshot layer
 *
 * FIXME: needs doc
 */
void clear_oneshot_layer_state(oneshot_fullfillment_t state) {
    uint8_t start_state = oneshot_layer_data;
    oneshot_layer_data &= ~state;
    if (!get_oneshot_layer_state() && start_state != oneshot_layer_data) {
        layer_off(get_oneshot_layer());
        reset_oneshot_layer();
    }
}
/** \brief Is oneshot layer active
 *
 * FIXME: needs doc
 */
bool is_oneshot_layer_active(void) { return get_oneshot_layer_state(); }
#endif

/** \brief Send keyboard report
 *
 * FIXME: needs doc
 */
void send_keyboard_report(void) {
    keyboard_report->mods = real_mods;
    keyboard_report->mods |= weak_mods;
    keyboard_report->mods |= macro_mods;
#ifndef NO_ACTION_ONESHOT
    if (oneshot_mods) {
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        if (has_oneshot_mods_timed_out()) {
            dprintf("Oneshot: timeout\n");
            clear_oneshot_mods();
        }
#    endif
        keyboard_report->mods |= oneshot_mods;
        if (has_anykey(keyboard_report)) {
            clear_oneshot_mods();
        }
    }

#endif
    host_keyboard_send(keyboard_report);
}

/** \brief Get mods
 *
 * FIXME: needs doc
 */
uint8_t get_mods(void) { return real_mods; }
/** \brief add mods
 *
 * FIXME: needs doc
 */
void add_mods(uint8_t mods) { real_mods |= mods; }
/** \brief del mods
 *
 * FIXME: needs doc
 */
void del_mods(uint8_t mods) { real_mods &= ~mods; }
/** \brief set mods
 *
 * FIXME: needs doc
 */
void set_mods(uint8_t mods) { real_mods = mods; }
/** \brief clear mods
 *
 * FIXME: needs doc
 */
void clear_mods(void) { real_mods = 0; }

/** \brief get weak mods
 *
 * FIXME: needs doc
 */
uint8_t get_weak_mods(void) { return weak_mods; }
/** \brief add weak mods
 *
 * FIXME: needs doc
 */
void add_weak_mods(uint8_t mods) { weak_mods |= mods; }
/** \brief del weak mods
 *
 * FIXME: needs doc
 */
void del_weak_mods(uint8_t mods) { weak_mods &= ~mods; }
/** \brief set weak mods
 *
 * FIXME: needs doc
 */
void set_weak_mods(uint8_t mods) { weak_mods = mods; }
/** \brief clear weak mods
 *
 * FIXME: needs doc
 */
void clear_weak_mods(void) { weak_mods = 0; }

/* macro modifier */
/** \brief get macro mods
 *
 * FIXME: needs doc
 */
uint8_t get_macro_mods(void) { return macro_mods; }
/** \brief add macro mods
 *
 * FIXME: needs doc
 */
void add_macro_mods(uint8_t mods) { macro_mods |= mods; }
/** \brief del macro mods
 *
 * FIXME: needs doc
 */
void del_macro_mods(uint8_t mods) { macro_mods &= ~mods; }
/** \brief set macro mods
 *
 * FIXME: needs doc
 */
void set_macro_mods(uint8_t mods) { macro_mods = mods; }
/** \brief clear macro mods
 *
 * FIXME: needs doc
 */
void clear_macro_mods(void) { macro_mods = 0; }

#ifndef NO_ACTION_ONESHOT
/** \brief set oneshot mods
 *
 * FIXME: needs doc
 */
void set_oneshot_mods(uint8_t mods) {
    if (oneshot_mods != mods) {
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        oneshot_time = timer_read();
#    endif
        oneshot_mods = mods;
        oneshot_mods_changed_kb(mods);
    }
}
/** \brief clear oneshot mods
 *
 * FIXME: needs doc
 */
void clear_oneshot_mods(void) {
    if (oneshot_mods) {
        oneshot_mods = 0;
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        oneshot_time = 0;
#    endif
        oneshot_mods_changed_kb(oneshot_mods);
    }
}
/** \brief get oneshot mods
 *
 * FIXME: needs doc
 */
uint8_t get_oneshot_mods(void) { return oneshot_mods; }
#endif

/** \brief Called when the one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_locked_mods_changed_user(uint8_t mods) {}

/** \brief Called when the locked one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_locked_mods_changed_kb(uint8_t mods) { oneshot_locked_mods_changed_user(mods); }

/** \brief Called when the one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_mods_changed_user(uint8_t mods) {}

/** \brief Called when the one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_mods_changed_kb(uint8_t mods) { oneshot_mods_changed_user(mods); }

/** \brief Called when the one shot layers have been changed.
 *
 * \param layer Contains the layer that is toggled on, or zero when toggled off.
 */
__attribute__((weak)) void oneshot_layer_changed_user(uint8_t layer) {}

/** \brief Called when the one shot layers have been changed.
 *
 * \param layer Contains the layer that is toggled on, or zero when toggled off.
 */
__attribute__((weak)) void oneshot_layer_changed_kb(uint8_t layer) { oneshot_layer_changed_user(layer); }

/** \brief inspect keyboard state
 *
 * FIXME: needs doc
 */
uint8_t has_anymod(void) { return bitpop(real_mods); }

/** \brief custom modifier handling
 *
 * This function checks if the given modifier mask is set and the given layer is
 * the current spec. If not it returns true. If the mask is set and the key
 * pressed, it deregisters the currently held modifiers, executes the given
 * function and returns the value returned by the function. If the key is
 * released, it simply runs the function and returns its value.
 *
 * This function is meant to be used in process_record_user to be able to
 * trigger specific action on key code with modifier, for example when shift-esc
 * is pressed.
 *
 * \param modifier_mask modifier mask to check against current modifiers held.
 * \param layer layer to check against current layer.
 * \param keycode the processed keycode, will be forwarded to handler.
 * \param record the processed record, will be forwarded to handler.
 * \param data anonymous data to be passed to the handler.
 * \param handler to be called when modifiers and layer are matched.
 * \return true if modifiers or layer did not match, return value of handler otherwise.
 */
bool run_on_modifiers(uint8_t modifier_mask, int16_t layer, uint16_t keycode,  keyrecord_t *record,
                      void *data,  bool (*handler)(uint16_t keycode,  keyrecord_t *record, void *data)) {
  static bool in_alternate_modifier;

  /* nothing to do if we are not in the right layer */
  if (layer >= 0 && !layer_state_is(layer))
    return true;

  /* when it's a key press and modifier state is pressed */
  if (record->event.pressed && (get_mods() & modifier_mask) == modifier_mask) {
    in_alternate_modifier = true;

    /* will send modifier up so that the os won't shift the keycode we will send */
    del_mods(modifier_mask);

    /* send mods modifications */
    send_keyboard_report();

    /* execute handler */
    bool rc = handler(keycode, record, data);

    add_mods(modifier_mask);

    return rc;
  }

  /* when releasing the key and we activated alternate modifier */
  if (!record->event.pressed && in_alternate_modifier) {
    in_alternate_modifier = false;

    /* execute handler */
    bool rc = handler(keycode, record, data);

    /* make sure all mods we sat up earlier are released */
    clear_weak_mods();

    /* send mods modification */
    send_keyboard_report();

    return rc;
  }

  return true;
}

/** \brief add a weak mod if keycode has the mod enabled */
#define maybe_add_weak_mods(keycode, mod)                               \
  if (keycode < QK_MODS_MAX &&                                          \
      (keycode & 0xff00) == QK_ ## mod)                                 \
    add_weak_mods(MOD_BIT(KC_ ## mod))

/** \brief copy keycode mods as weak mod */
static void copy_mods_as_weak(uint16_t keycode) {
    /* send mods if keycode needs it */
    maybe_add_weak_mods(keycode, LCTL);
    maybe_add_weak_mods(keycode, LSFT);
    maybe_add_weak_mods(keycode, LALT);
    maybe_add_weak_mods(keycode, LGUI);
    maybe_add_weak_mods(keycode, RCTL);
    maybe_add_weak_mods(keycode, RSFT);
    maybe_add_weak_mods(keycode, RALT);
    maybe_add_weak_mods(keycode, RGUI);
}

/** \brief run_on_modifiers handler to send custom keycode
 */
static bool custom_keycode_on_modifiers_handler(uint16_t keycode, keyrecord_t *record, void *data) {
  uint16_t custom_keycode =  *((uint16_t *) data);

  if (record->event.pressed) {
    /* register custom keycode mods */
    copy_mods_as_weak(custom_keycode);
    send_keyboard_report();

    /* send alternate key code */
    register_code16(custom_keycode);
  } else {
    /* release the alternate key */
    unregister_code16(custom_keycode);

    /* make sure all mods we sat up earlier are released */
    clear_weak_mods();

    /* send mods modification */
    send_keyboard_report();
  }

  return false;
}

/** \brief Send custom keycode when modifier mask is set on layer.
 *
 */
bool custom_keycode_on_modifiers(uint8_t modifier_mask, int16_t layer, keyrecord_t *record, uint16_t custom_keycode) {
  return run_on_modifiers(modifier_mask, layer, 0, record, &custom_keycode, custom_keycode_on_modifiers_handler);
}
