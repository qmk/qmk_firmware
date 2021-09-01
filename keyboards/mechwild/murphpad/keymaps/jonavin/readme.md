Jonavin's Custom MurphPad Landscape Layout
 
This allows you to use Murphpad in a horizontal/landscape orientation with extra layers

    - OLED has been rotated for landscape mode 
    - Keymap positions have been updated so it's easier to visualize the keymap in landscape 

        [_BASE] = LAYOUT_landscape(
            TT(_FN1), TT(_FN2), KC_MUTE,

        KC_NLCK,  KC_PSLS,  KC_PAST, KC_PMNS, KC_PPLS,      KC_BSPC,
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
    - While holding R Shift, changes layers
    - While holding R Ctrl, navigates next or previous word
    - While holding R Alt, media next track or previous track
    - Otherwise change volume up/dn


rules.mk OPTIONS - Active features from userspace

    - STARTUP_NUMLOCK_ON = yes
        - turns on NUMLOCK by default

DEFAULT MAPPING

![image](https://user-images.githubusercontent.com/71780717/130542391-02bc1944-ff61-471b-9834-0caabdd86b88.png)


FN1 Layer 1

![image](https://user-images.githubusercontent.com/71780717/131718243-59c4d32a-28b6-40c0-8fcd-d885d6ff0f63.png)


RGB Layer 5 - Use Shift+Encoder to get to RGB layer 5

![image](https://user-images.githubusercontent.com/71780717/131718297-0085d125-afe9-487c-9c81-6dc1caa4c93d.png)
