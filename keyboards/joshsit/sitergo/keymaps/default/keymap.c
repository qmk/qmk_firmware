#include QMK_KEYBOARD_H

// Using COLEMAK-DH LAYOUT

// Backlight timeout feature
#define BACKLIGHT_TIMEOUT 200    // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static uint8_t old_backlight_level = -1;
static uint8_t old_hue = -1;
static uint8_t old_sat = -1;
static bool led_on = true;

// Enable below define lines for home row mods only
// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)

// Right-hand home row mods
#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)

// Tap Dance declarations
enum {
    TD_PANIC,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for TO(0)
    [TD_PANIC] = ACTION_TAP_DANCE_LAYER_MOVE(KC_ESC, 0),      
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT_ortho_3x10_6(KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_BSPC, HOME_A, HOME_R, HOME_S, HOME_T, KC_G, KC_M, HOME_N, HOME_E, HOME_I, HOME_O, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, LT(2,KC_DEL), KC_TAB, KC_ESC, TO(3), KC_SPC, LT(1,KC_ENT)),
        /* Keymap 0: Basic layer
        * .----------------------------------.             .----------------------------------.
        * |   Q  |   W  |   F  |   P  |   B  |             |   J  |   L  |   U  |   Y  | BSPC |      
        * |------+------+------+------+------|             |------+------+------+------+------|
        * | HM_A | HM_R | HM_S | HM_T |   G  |             |   M  | HM_N | HM_E | HM_I | HM_O |
        * |------+------+------+------+------|             |------+------+------+------+------|
        * |   Z  |   X  |   C  |   D  |   V  |             |   K  |   H  |   ,  |   .  |   /  |
        * '-------------+------+------+------|             |-------------+------+------+------'
        *               |  DEL |  TAB |  ESC |             | TO(3)|  SPC |  ENT |
        *               '--------------------'             '--------------------'
        *                 MO(2)                                            MO(1)               */
        
        [1] = LAYOUT_ortho_3x10_6(KC_EXLM, KC_AT, KC_HASH, KC_DLR, LGUI(KC_DOT), KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_DEL, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_BRIU, KC_VOLU, KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, KC_LPRN, KC_RPRN, KC_MINS, KC_UNDS, KC_BRID, KC_VOLD, KC_NO, KC_LT, KC_GT, QK_BOOT, KC_CAPS, KC_NO, KC_SLEP, KC_NO, KC_NO, KC_NO),
        /* Keymap 1: Symbols layer
        * .----------------------------------.             .----------------------------------.       To Add:
        * |   !  |   @  |   #  |   $  | EMOJI|             |      |      |   {  |   }  |  DEL |      
        * |------+------+------+------+------|             |------+------+------+------+------|
        * |   %  |   ^  |   &  |   *  | BR_U |             | VOL_U|   [  |   (  |   )  |   ]  |
        * |------+------+------+------+------|             |------+------+------+------+------|
        * |   (  |   )  |   -  |   _  | BR_D |             | VOL_D|      |   <  |   >  | BOOT |
        * '-------------+------+------+------|             |-------------+------+------+------'
        *               | CAPS |      | SLEEP|             |      |      |XXXXXX|
        *               '--------------------'             '--------------------'              */
        
        [2] = LAYOUT_ortho_3x10_6(RGB_TOG, KC_NO, KC_NO, KC_NO, KC_BSLS, KC_PSLS, KC_7, KC_8, KC_9, KC_BSPC, KC_NO, KC_SCLN, KC_QUOT, KC_DQUO, KC_PIPE, KC_COLN, KC_4, KC_5, KC_6, KC_PAST, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_EQL, KC_1, KC_2, KC_3, KC_PPLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_0, KC_PDOT),
        /* Keymap 2: Number Pad layer
        * .----------------------------------.             .----------------------------------.
        * |RGB_ON|      |      |      |   \  |             |   /  |   7  |   8  |   9  | BSPC |      
        * |------+------+------+------+------|             |------+------+------+------+------|
        * |      |   ;  |   '  |   "  |   |  |             |   :  |   4  |   5  |   6  |   *  |
        * |------+------+------+------+------|             |------+------+------+------+------|
        * |      |      |      |      |      |             |   =  |   1  |   2  |   3  |   +  |
        * '-------------+------+------+------|             |-------------+------+------+------'
        *               |XXXXXX|      |      |             |      |   0  |   .  
        *               '--------------------'             '--------------------'              */
        
        [3] = LAYOUT_ortho_3x10_6(LCTL(KC_W), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), SGUI(KC_S), LCTL(KC_Z), KC_LSFT, KC_LCTL, KC_LALT, KC_BSPC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, LCTL(KC_S), KC_WH_D, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_WH_U, KC_WH_D, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_DEL, KC_TAB, KC_ESC, TO(0), KC_SPC, KC_ENT )
        /* Keymap 3: Navigation layer
        * .----------------------------------.             .----------------------------------.
        * |CTL(W)|CTL(X)|CTL(C)|CTL(V)|PRTSCR|             |CTL(Z)| LSFT | LCTL | LALT | BSPC |      
        * |------+------+------+------+------|             |------+------+------+------+------|
        * | LGUI | LALT | LCTL | LSFT |CTL(S)|             | MW_D | LEFT | DOWN |   UP | RGHT |
        * |------+------+------+------+------|             |------+------+------+------+------|
        * | MW_U | MW_D | L-CLK| R-CLK| M-CLK|             | L-CLK| MS_L | MS_D | MS_U | MS_R |
        * '-------------+------+------+------|             |-------------+------+------+------'
        *               |  DEL |  TAB |  ESC |             | TO(0)|  SPC |  ENT |
        *               '--------------------'             '--------------------'              */
};


// LED STUFF

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    // {0, 1, HSV_PURPLE}
    {0, 1, HSV_WHITE}
);
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    // {0, 1, 255, 0, 255}
    {0, 1, HSV_RED} 
);
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN}
    // {0, RGBLED_NUM, 10, 0, 0} 
);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN}
    // {0, RGBLED_NUM, 0, 254, 255} 
);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLUE}
    // {0, RGBLED_NUM, 0, 254, 255} 
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_capslock_layer,
    my_layer1_layer,
    my_layer2_layer,  
    my_layer3_layer

);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(2, layer_state_cmp(state, 1));
    rgblight_set_layer_state(3, layer_state_cmp(state, 2));
    rgblight_set_layer_state(4, layer_state_cmp(state, 3));
    rgblight_set();
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
            if (led_on == false || old_backlight_level == -1) {
            if (old_backlight_level == -1) old_hue = rgblight_get_hue();
            if (old_backlight_level == -1) old_sat = rgblight_get_sat();
                if (old_backlight_level == -1) old_backlight_level = rgblight_get_val();  
                rgblight_sethsv_noeeprom(old_hue, old_sat, old_backlight_level);
                led_on = true;
            }
        #endif
        idle_timer = timer_read();
        halfmin_counter = 0;
    }
    return true;
  }

void matrix_scan_user(void) {
    // idle_timer needs to be set one time
    if (idle_timer == 0) idle_timer = timer_read();

    #ifdef RGBLIGHT_ENABLE
        if ( led_on && timer_elapsed(idle_timer) > 30000) {
            halfmin_counter++;
            idle_timer = timer_read();
        }

        if ( led_on && halfmin_counter >= BACKLIGHT_TIMEOUT * 2) {
            old_backlight_level = rgblight_get_val(); 
        old_hue = rgblight_get_hue();
        old_sat = rgblight_get_sat();
            rgblight_sethsv_noeeprom(old_hue, old_sat, 0);
            led_on = false;
            halfmin_counter = 0;
        }
    #endif
}





// qmk flash -kb sitergo -km default
qmk c2json -km default -kb sitergo -o sitergo.json keymap.c
// qmk json2c sitergo.json

// For enabling home row mods, Replace the ten keys of your home row in the LAYOUT block of your keymap.c with this.
// HOME_A, HOME_R, HOME_S, HOME_T, KC_G, KC_M, HOME_N, HOME_E, HOME_I, HOME_O,  