Jonavin's Custom Mercutio Layout
  - Based on Fancy keymap

Features
  - Split Enter, shftEnter, Split Backspace
  - standard shorten home row keys
  - numpad and nav keys in RAISE LAYER
  - symbols in LOWER layer
  - CAPS LOCK 2 taps for RAISE layer toggle
  - RAISE layer left spacebar Backspace
  - Shift+Encoder for layer changes (from mercutio/fancy keymap)
  - MOUSEKEYS is disbled
  - shutdown oled when powered down to prevent OLED from showing Mercutio all the time
  - add WPM indicator when wpm is > 20 wpm
  - add double tap of Left Shift to toggle Caps Lock
  
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
                {"PLAY",    KC_MEDIA_PLAY_PAUSE}
        };

  - Additional encoder functionality 
        While holding Left Ctrl, navigates next or previous word
        While holding Left Alt, media next track or previous track


Default Layers
![image](https://user-images.githubusercontent.com/71780717/118902752-4aaf7880-b8e4-11eb-82f4-e5047612ffcf.png)
