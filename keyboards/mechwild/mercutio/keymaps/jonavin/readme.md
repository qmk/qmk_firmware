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
  - FN layer has encoder selectable key codes
  
Change these in keymap.c to assign your desired key selection

const uint8_t fkeycodes[] = { // list of key codes that will be scrollled through by encoder
    KC_INS, KC_DEL, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24
};
const char* fkeydesc[] =    { // list of desc to be shown on LCD max 5 chars will be shown
    "INS",  "DEL",  "F13",  "F14",   "F15", "F16",  "F17",  "F18",  "F19",  "F20",  "F21",  "F22",  "F23",  "F24"
};


![image](https://user-images.githubusercontent.com/71780717/118902752-4aaf7880-b8e4-11eb-82f4-e5047612ffcf.png)
