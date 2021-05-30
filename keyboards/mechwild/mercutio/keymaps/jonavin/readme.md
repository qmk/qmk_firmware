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
  
  - FN layer has encoder selectable key codes and displayed on OLED
        
        Change these in keymap.c to assign your desired key selection

        const uint16_t fkeycodes[] = { // list of key codes that will be scrollled through by encoder
            KC_TASK, KC_INS, KC_DEL, KC_PSCR, KC_SCLN, KC_PAUS, KC_CAD, KC_AF4, KC_MEDIA_PLAY_PAUSE
        };
        const char* fkeydesc[] =    { // list of desc to be shown on LCD max 5 chars will be shown
            "TASK","INS",  "DEL",  "PRTSC", "SCRLK", "BREAK", "C-A-D", "AltF4", "PLAY"
        };

  - Additional encoder functionality 
        While holding Left Ctrl, navigates next or previous word
        While holding Left Alt, media next track or previous track


Default Layers
![image](https://user-images.githubusercontent.com/71780717/118902752-4aaf7880-b8e4-11eb-82f4-e5047612ffcf.png)
