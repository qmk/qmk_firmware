Jonavin's Custom MurphPad Landscape Layout
 
This allows you to use Murphpad in a horizontal/landscape orientation with extra layers

    - OLED has been rotated for landscape mode 
    - Keymap positions have been updated so it's easier to visualize the keymap in landscape 

        [_BASE] = LAYOUT_landscape(
            TT(_FN1), TT(_FN2), KC_MUTE,

            KC_NUM,   KC_PSLS,  KC_PAST, KC_PMNS, KC_PPLS,      KC_BSPC,
            KC_TAB,   KC_P7,    KC_P8,   KC_P9,   KC_PDOT,      KC_RGUI,
            KC_RSFT,  KC_P4,    KC_P5,   KC_P6,   KC_COMMA,     KC_RCTL,
            KC_P0,    KC_P1,    KC_P2,   KC_P3,   KC_PENT,      KC_RALT,

                        _______, _______, _______
        ),

NOTE:  VIA is enabled, but it will show it in the normal orientation until I build a landscape layout version

Special Features
  - FN1 layer has encoder selectable key codes and displayed on OLED
        
        Change these in keymap.c to assign your desired key selection

        static const keycodedescType PROGMEM keyselection[] = {
            // list of key codes that will be scrollled through by encoder and description
            {"TASK ",   KC_TASK},
            {"PREV ",   KC_MEDIA_PREV_TRACK},
            {"NEXT ",   KC_MEDIA_NEXT_TRACK},
            {"PLAY ",   KC_MEDIA_PLAY_PAUSE},
            {"PrtScm",  KC_PSCR},
            {"ScrLk",   KC_SCLN},
            {"Break",   KC_PAUS},
            {"C-A-D",   KC_CAD},  // Ctrl-Alt-Del
            {"AltF4",   KC_AF4},
            {"RESET",   QK_BOOT},   // firmware flash mode
          };

  - Additional encoder functionality
    - While holding R Shift, changes layers
    - While holding R Ctrl, navigates next or previous word
    - While holding R Alt, media next track or previous track
    - Otherwise change volume up/dn


rules.mk OPTIONS - Active features from userspace

    - STARTUP_NUMLOCK_ON = yes
        - turns on NUMLOCK by default

DEFAULT LANDSCAPE MAPPING 

![image](https://user-images.githubusercontent.com/71780717/131718965-b20afef6-3bc5-49e4-952f-5755a9d6d539.png)


FN1 Layer 1

![image](https://user-images.githubusercontent.com/71780717/131719025-d41cbcd9-80b1-4a0a-abb5-55d878752dc6.png)


FN2 Layer 2

![image](https://user-images.githubusercontent.com/71780717/132967003-63268514-2ac3-4069-bca1-6d92992ca403.png)


RGB Layer 5 - Use Shift+Encoder to get to RGB layer 5

![image](https://user-images.githubusercontent.com/71780717/131719492-e2d05a75-3a7a-48ca-94a3-faa3ff891914.png)

--------------

NORMAL / TRADITIONAL NON-LANDSCAPE NUMPAD LAYOUT

![image](https://user-images.githubusercontent.com/71780717/132966975-3b463fb4-059f-42c5-b8b3-a3d35f4a0d6b.png)

