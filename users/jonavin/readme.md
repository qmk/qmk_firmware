Copyright 2021 Jonavin Eng @Jonavin

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

LAYERS:
    0 = _BASE
    1 = _FN1
    2 = _LOWER
    3 = _RAISE

KEYCODES:
    KC_CAD          Ctrl-Alt-Del	  
    KC_AF4	        Alt-F4
    KC_TASK	        Windows Task Manager (Ctrl-Shift-Esc) 
    LSFT_CAPSLOCK   When LSFT_CAPSLOCK_ENABLE is defined, hold for Shift double tap for CAPSLOCK; otherwise, just Shift
    KC_00           double zero "00"
    KC_WINLCK       toggles LGui/Win key lock
    RGB_TOI         Increase Timeout idle time threshold
    RGB_TOD         Decrease Timeout idle time threshold

ENABLE FEATURES your keymap rules.mk

STARTUP_NUMLOCK_ON = yes
    turns on NUMLOCK by default

ENCODER_DEFAULTACTIONS_ENABLE = yes
    Enabled default encoder funtions
    When enabled, use this in the keymap for an additional encoder processing 
        bool encoder_update_keymap(uint8_t index, bool clockwise)
  
    OPTION: set ENCODER_DEFAULTACTIONS_INDEX to the encoder number if the encoder is not index 0
  
TD_LSFT_CAPSLOCK_ENABLE = yes
    This will enable double tap on Left Shift to toggle CAPSLOCK
        KC_LSFTCAPS to bind to left Shift to enable feature
        KC_LSFTCAPSWIN does the same thing but will not turn on CAPS when Win Lkey is disabled

IDLE_TIMEOUT_ENABLE = yes
    Enables Timer functionality; for RGB idle timeouts that can be changed dynamically
    When enabled, use this in the keymap for an additional matrix processing     
        void matrix_scan_keymap(void)
    
    Functions:
        u16int_t get_timeout_threshold(void)            // returns the current timeout threshold
        void timeout_update_threshold(bool increase)    // change threshold: true = increase, false = decrease     
        void timeout_reset_timer(void)                  // resets timer (put in process_record_user if you override it)
        void timeout_tick_timer(void)                   // registers time ticks (put in maxtrix_scan_user if you override it)

Other Functions:
    - activate_numlock(bool turn_on)                    // true = turn on NUM LOCK, false = off 

KEYMAP LEVEL ADDITIONAL PROCESSING FUNCTIONS
    bool process_record_keymap(uint16_t keycode, keyrecord_t *record)
    void keyboard_post_init_keymap(void)

LIST OF COMPATIBLE KEYMAPS
    - gmmk/pro/ansi
    - keebio/quefrency/rev3
    - mechwild/mercutio
    - mechwild/murphpad
    - mechwild/OBE (*)
    - nopunin10did/kastenwagen (*)

    (*) coming soon
