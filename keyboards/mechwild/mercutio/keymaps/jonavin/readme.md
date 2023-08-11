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
  - add WinLock feature with FN + Win; display WL on OLED when enabled
  
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
                {"RESET",   QK_BOOT},  // firmware flash mode
       };

  - Additional encoder functionality 
        While holding Left Ctrl, navigates next or previous word
        While holding Left Alt, media next track or previous track


rules.mk OPTIONS - Active features from userspace
STARTUP_NUMLOCK_ON = yes
    - turns on NUMLOCK by default

TD_LSFT_CAPSLOCK_ENABLE = yes
    - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS

Default Layers
![image](https://user-images.githubusercontent.com/71780717/127014682-3aa05136-6dc7-4a40-9be1-89a5b584848a.png)

MO(1) / FN Layer
![image](https://user-images.githubusercontent.com/71780717/127014620-a3a36dc6-6e22-4a9b-ad9a-6c6a5d18cbc5.png)

MO(2) / Lower layer
![image](https://user-images.githubusercontent.com/71780717/127014816-09598d62-2d23-42e5-a625-504a79a54ca9.png)

MO(3) / Raise layer
![image](https://user-images.githubusercontent.com/71780717/127014881-a181c198-a7e8-4f48-9789-a7a85eabcbd1.png)




