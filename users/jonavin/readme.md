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
    Enabled deafult encoder funtions
  
TD_LSFT_CAPSLOCK_ENABLE = yes
    This will enable double tap on Left Shift to toggle CAPSLOCK

IDLE_TIMEOUT_ENABLE = yes
    Enables Timer functionality; for RGB idle timeouts that can be changed dynamically
    
    Functions:
        void timeout_update_threshold(bool increase)    // change threshold: true = increase, false = decrease     
        void timeout_reset_timer(void)                  // resets timer (put in process_record_user if you override it)
        void timeout_tick_timer(void)                   // registers time ticks (put in maxtrix_scan_user if you override it)

Other Functions:
    - activate_numlock(bool turn_on)                    // true = turn on NUM LOCK, false = off 


LIST OF COMPATIBLE KEYMAPS
    - gmmk/pro
    - gmmk/pro/ansi
    - keebio/quefrency/rev3
    - mechwild/mercutio
    - mechwild/murphpad (*)
    - mechwild/OBE (*)
    - nopunin10did/kastenwagen (*)

    (*) coming soon
