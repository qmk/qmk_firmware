My main layout (Layer 0) is based on qwerty. I tried to fit the layout of the kinesis keyboard onto the ergodox. Furthermore I did some tweaks. 
The other layers are seldom used. Except the F Keys and the teensy key. As I own a ergodox I cant press the reset button, so i need a key to send the teensy into reprogram mode.
There is a layer with symbols a numpad. These layers are seldom used. Except the F Keys and the teensy key. As I own a ergodox I need a key to reprogram, because I can't access the reset button.

I am a linux user and need the esc key and str keys often therefore it is easyly accessed. Switching console str+alt+tab+f2 (layer 2 and 2) is tricky but you get it after a while.
As I live in germany and need to type umlaut frquently, i mapped the CAPS to the meta key, and swapped ' and ". So I can type ö with CAPS o + ¨. no need to press o+SHIFT+'
As a note for linux users i use str+p to get last command, instead of using the cursor keys.  

HOWTO to convert CAPS to Meta-Key and swap ' with "

* create file with following content 
.Xmodmap
 clear Lock
 keycode 48 = quotedbl apostrophe quotedbl apostrophe
 keycode 66 = Multi_key

* apply with
xmodmap .Xmodmap

* convert to xkbmap
xkbcomp $DISPLAY $HOME/.xkbmap

* automatic startup each time you startup x
echo 'xkbcomp $HOME/.xkbmap $DISPLAY' >> ~/.xinitrc

    KEYMAP(  // layer 0 : default
        // left hand
        KC_EQL  ,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_LBRC,
	KC_FN25 ,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_HOME,
        KC_FN27 ,  KC_A,    KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT ,  KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_PGUP,
        KC_LGUI , KC_GRV,KC_LEFT,KC_RGHT,KC_LALT,
                                          KC_NO , KC_NO  ,
                                               KC_NO  ,
                                     KC_BSPC,KC_DEL ,KC_FN23,
        // right hand
             KC_RBRC , KC_6,   KC_7 ,  KC_8,   KC_9,   KC_0,   KC_MINS,
             KC_END  , KC_Y,   KC_U ,  KC_I,   KC_O,   KC_P,   KC_FN28,
             KC_H    , KC_J,   KC_K ,  KC_L,   KC_SCLN,KC_FN30,
             KC_PGDN , KC_N,   KC_M ,  KC_COMM,KC_DOT, KC_SLSH,KC_FN29,
             KC_RALT , KC_DOWN,KC_UP,  KC_NO  ,KC_RGUI,
        KC_NO  , KC_NO,
        KC_NO  ,
        KC_FN29,KC_ENT ,KC_SPC 
    ),

    KEYMAP(  // layer 1 : function and symbol keys
        // left hand
        KC_TRNS,KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F11,
        KC_TRNS,KC_AT,KC_UNDS ,KC_LBRC,KC_RBRC,KC_CIRC ,KC_TRNS,
        KC_TRNS,KC_BSLS,KC_SLSH,KC_LCBR ,KC_RCBR ,KC_ASTR,
        KC_TRNS,KC_HASH ,KC_DLR ,KC_PIPE ,KC_TILD ,KC_GRV ,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                           KC_TRNS,
                                 KC_TRNS,KC_TRNS,KC_FN1,
        // right hand
             KC_F12, KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_TRNS,
             KC_TRNS,KC_EXLM,LSFT(KC_COMM),LSFT(KC_DOT),KC_EQL,KC_AMPR, KC_TRNS,
             LSFT(KC_SLSH),KC_LPRN,KC_RPRN,KC_MINS,LSFT(KC_SCLN),KC_TRNS,
             KC_TRNS,KC_PLUS,LSFT(KC_5),LSFT(KC_QUOT),KC_QUOT,KC_SCLN,KC_TRNS,
                       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,
        KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS
    ),

    KEYMAP(  // layer 2: navigation 
        // left hand
        KC_NO,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_PGUP,KC_HOME,KC_UP ,KC_END,KC_NO ,KC_TRNS,
        KC_TRNS,KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,KC_NO,
        KC_TRNS,KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_NO,KC_NO,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                      KC_TRNS,KC_TRNS,
                                           KC_TRNS,
                                 KC_TRNS,KC_TRNS,KC_FN1 ,
        // right hand
             KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
             KC_TRNS ,KC_TRNS,  KC_HOME,  KC_TRNS,  KC_TRNS, KC_END ,KC_TRNS,
                  KC_NO,  KC_LEFT,  KC_UP,   KC_DOWN, KC_RGHT,KC_TRNS,
             KC_TRNS,KC_TRNS,  KC_HOME,  KC_UP,  KC_END, KC_PGUP,KC_TRNS,
                       KC_LEFT,  KC_DOWN,KC_RGHT,KC_PGDN,KC_TRNS,
        KC_TRNS,KC_TRNS,
        KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS
    ),
    KEYMAP(  // layer 3 : teensy bootloader functions
        // left hand
        KC_FN0, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                      KC_TRNS,KC_TRNS,
                                           KC_TRNS,
                                 KC_TRNS,KC_TRNS,KC_FN1 ,
        // right hand
             KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
             KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
             KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,
        KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS
    ),


    KEYMAP(  // layer 4: numpad
        // left hand
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                      KC_TRNS,KC_TRNS,
                                           KC_TRNS,
                                 KC_TRNS,KC_TRNS,KC_TRNS,
        // right hand
             KC_TRNS,KC_NLCK,KC_PSLS,KC_PAST,KC_PAST,KC_PMNS,KC_BSPC,
             KC_TRNS,KC_NO,  KC_P7,  KC_P8,  KC_P9,  KC_PMNS,KC_BSPC,
                  KC_NO,  KC_P4,  KC_P5,  KC_P6,  KC_PPLS,KC_PENT,
             KC_TRNS,KC_NO,  KC_P1,  KC_P2,  KC_P3,  KC_PPLS,KC_PENT,
                       KC_P0,  KC_PDOT,KC_SLSH,KC_PENT,KC_PENT,
        KC_TRNS,KC_TRNS,
        KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS
    ),

};


