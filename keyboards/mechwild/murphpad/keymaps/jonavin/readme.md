Jonavin's Custom MurphPad Layout
 

Features
  - FN layer has encoder selectable key codes and displayed on OLED
        
        Change these in keymap.c to assign your desired key selection

        static const keycodedescType PROGMEM keyselection[] = {
            // list of key codes that will be scrollled through by encoder and description
                {"TASK",    KC_TASK},
                {"INS",     KC_INS},
                {"DEL",     KC_DEL},
                {"PrtSc",   KC_PSCR},
                {"ScrLk",   KC_SCLN},
                {"Break",   KC_PAUS},
                {"C-A-D",   KC_CAD},  // Ctrl-Alt-Del
                {"AltF4",   KC_AF4},
                {"PLAY",    KC_MEDIA_PLAY_PAUSE},
                {"RESET",   RESET},  // firmware flash mode
       };

  - Additional encoder functionality 
        While holding Left Ctrl, navigates next or previous word
        While holding Left Alt, media next track or previous track


rules.mk OPTIONS - Active features from userspace
STARTUP_NUMLOCK_ON = yes
    - turns on NUMLOCK by default

TD_LSFT_CAPSLOCK_ENABLE = yes
    - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS

