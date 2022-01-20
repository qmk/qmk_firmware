#include QMK_KEYBOARD_H
#include "version.h"
#include "danielo515.h"

/* STUPID JS code to split by ergodox rows. Call the format function with the unformatted array
sliceBy = groups => items => groups.reduce(({start, acc},size) => ({
    acc: (acc.push(items.slice(start,start+size)),acc ),
    start: start + size
}), {acc:[],start:0}).acc
findMaxLen = items => items.reduce((max,curr) => max < curr.length ? curr.length : max,0)
setLen = len => strings => strings.map(str => str.padEnd(len, " "));
const format = string => {
  const items = string.split(/,\s*(?![^()]*\))/)
  const group = sliceBy([7,7,6,7,5,2,1,3])
  const resize = setLen(findMaxLen(items));
  const joinstr = ',\n'
  const leftItems = group(items.slice(0,items.length/2))
  const rightItems = group(items.slice(items.length/2))
  const [left,right] = [leftItems.map(resize).join(joinstr),rightItems.map(resize).join(joinstr)]
  return `\n${left},\n\n${right}\n`
}
*/

#define OSM_SF_CMD  OSM(MOD_LGUI | MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ergodox(
    KC_EQL              ,KC_1                ,KC_2                ,KC_3                ,KC_4                ,KC_5                ,OSM(MOD_HYPR)    ,
    KC_TAB              ,KC_Q                ,KC_W                ,KC_E                ,KC_R                ,KC_T                ,TD(PASTE_DANCE) ,
    KC_DELETE           ,KC_A                ,LT(3,KC_S)          ,LT(2,KC_D)          ,LT(4,KC_F)          ,KC_G                ,
    KC_GRAVE            ,KC_Z                ,KC_X                ,KC_C                ,KC_V                ,KC_B                ,TD(COPY_CUT) ,
    KC_BSLASH           ,OSM(MOD_LCTL)       ,OSM(MOD_LALT)       ,KC_LEFT             ,KC_RIGHT            ,
    OSM_SF_CMD          ,KC_PLUS             ,
    KC_INSERT           ,
    OSM(MOD_LSFT)       ,LT(2,KC_BSPACE)     ,OSM(MOD_LGUI)              ,


    TO(1)               ,KC_6                ,KC_7                ,KC_8                ,KC_9                ,LT(3,KC_0)          ,KC_DQUO             ,
    KC_UNDS             ,KC_Y                ,KC_U                ,KC_I                ,KC_O                ,KC_P                ,RSFT_T(KC_MINUS)            ,
    HYPR_H              ,ALT_J               ,CTL_K               ,LT(6,KC_L)          ,TD_CLN              ,CMD_QUOT            ,
    ALT_TAB             ,KC_N                ,MEH_T(KC_M)         ,KC_COMMA            ,KC_DOT              ,KC_SLASH            ,LT(4,KC_KP_ASTERISK),
    LT(4,KC_ENTER)      ,KC_DOWN             ,KC_LBRACKET         ,KC_RBRACKET         ,OSL(2)              ,
    KC_AUDIO_MUTE       ,KC_ESCAPE           ,
    KC_END              ,
    KC_COLN             ,KC_LEAD             ,LT(4,KC_SPACE)
    ),

  [1] = LAYOUT_ergodox(
    KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,AC_E            ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    LT(5, KC_DELETE),AC_A            ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,FIND            ,KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,
    OSM(MOD_LSFT)   ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    TO(8)           ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    KC_ENTER        ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,
    KC_TRANSPARENT  ,KC_TRANSPARENT  ,KC_TRANSPARENT),

  [2] = LAYOUT_ergodox(
    KC_TRANSPARENT,KC_F1         ,KC_F2         ,KC_F3         ,KC_F4         ,KC_F5         ,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_EXLM       ,KC_AT         ,KC_LCBR       ,KC_RCBR       ,KC_PIPE       ,KC_CALCULATOR ,
    KC_TRANSPARENT,KC_HASH       ,KC_DLR        ,KC_TRANSPARENT,KC_RPRN       ,KC_GRAVE      ,
    KC_TRANSPARENT,KC_PERC       ,KC_CIRC       ,KC_LBRACKET   ,KC_RBRACKET   ,KC_TILD       ,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,
                                  RGB_HUI       ,
    KC_TRANSPARENT,KC_TRANSPARENT,RGB_HUD       ,
    KC_DELETE     ,KC_A          ,KC_B          ,KC_C          ,KC_D          ,KC_E          ,KC_BSPACE     ,
    KC_ENTER      ,KC_F          ,KC_7          ,KC_8          ,KC_9          ,KC_PERC       ,KC_TRANSPARENT,
                   KC_HASH       ,KC_4          ,KC_5          ,KC_6          ,KC_PLUS       ,KC_KP_ASTERISK,
    KC_KP_ENTER   ,KC_COLON      ,KC_1          ,KC_2          ,KC_3          ,KC_SLASH      ,KC_BSLASH     ,
                                  KC_0          ,KC_COMMA      ,KC_DOT        ,KC_EQUAL      ,KC_TRANSPARENT,
    RGB_TOG       ,RGB_SLD       ,
    RGB_VAI       ,
    RGB_VAD       ,KC_BSPACE     ,KC_SPACE
  ),

  [3] = LAYOUT_ergodox(
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_LABK            ,KC_RABK            ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,KC_AT              ,KC_TRANSPARENT     ,KC_EQL             ,F_ARROW            ,KC_GRAVE           ,
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_LBRACKET        ,KC_RBRACKET        ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,IARROW             ,ARROW               ,
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,
    // Right hand
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,
    LALT(LSFT(KC_UP))  ,KC_HASH            ,KC_LCBR            ,KC_RCBR            ,KC_KP_ASTERISK     ,KC_PERC            ,KC_DLR             ,
                        KC_AMPR            ,KC_LPRN            ,KC_RPRN            ,CLN_EQ             ,KC_KP_PLUS         ,KC_PIPE            ,
    LALT(LSFT(KC_DOWN)),KC_EXLM            ,KC_TILD            ,KC_CIRC            ,ARROW              ,KC_BSLASH          ,KC_BSLASH          ,
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,
    RESET              ,KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_SPACE
),

  [4] = LAYOUT_ergodox(
    KC_TRANSPARENT     ,KC_F1              ,KC_F2              ,KC_F3              ,KC_F4              ,KC_F5              ,KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,LCTL(KC_Q)         ,LCTL(KC_DOWN)      ,LGUI(KC_DOWN)      ,WIN_LEFT_HALF      ,WIN_RIGHT_HALF     ,LALT(LSFT(KC_UP))  ,
    LCTL(LSFT(KC_P))   ,LCTL(KC_A)         ,SAVE               ,LCTL(KC_D)         ,KC_TRANSPARENT     ,RGUI(KC_R)         ,
    LCTL(LSFT(KC_F))   ,UNDO               ,CUT                ,KC_PSCREEN         ,KC_TRANSPARENT     ,LGUI(KC_RIGHT)     ,LALT(LSFT(KC_DOWN)),
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,

    LALT(KC_F4)        ,KC_F6              ,KC_F7              ,KC_F8              ,KC_F9              ,KC_F10             ,KC_F11             ,
    LALT(KC_UP)        ,LSFT(KC_HOME)      ,LSFT(KC_LEFT)      ,KC_UP              ,LSFT(KC_RIGHT)     ,LSFT(KC_END)       ,KC_F13             ,
                        KC_HOME            ,KC_LEFT            ,KC_DOWN            ,KC_RIGHT           ,KC_END             ,KC_F12             ,
    LALT(KC_DOWN)      ,LSFT(KC_INSERT)    ,LCTL(LSFT(KC_J))   ,LSFT(KC_UP)        ,KC_PGUP            ,KC_TRANSPARENT     ,KC_TRANSPARENT     ,
    KC_TRANSPARENT                                             ,LSFT(KC_DOWN)      ,KC_PGDOWN          ,WIN_TO_LEFT        ,WIN_TO_RIGHT     ,
    KC_TRANSPARENT     ,KC_SYSTEM_SLEEP    ,
    KC_TRANSPARENT     ,
    KC_TRANSPARENT     ,KC_BSPACE          ,KC_TRANSPARENT
  ),

  [5] = LAYOUT_ergodox(
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,LCTL(KC_TAB)        ,LCTL(LSFT(KC_TAB))  ,LGUI(KC_D)          ,LCTL(KC_F)          ,KC_TRANSPARENT      ,
    LGUI(KC_L)          ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,

    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,LSFT(KC_F9)         ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,LCTL(LGUI(KC_LEFT)) ,LCTL(LGUI(KC_RIGHT)),KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,LCTL(KC_T)          ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT
),

  [6] = LAYOUT_ergodox(
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_MS_ACCEL2        ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_MS_WH_DOWN       ,KC_MS_UP            ,KC_MS_WH_UP         ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_MS_LEFT          ,KC_MS_DOWN          ,KC_MS_RIGHT         ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_MS_BTN3          ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,
    KC_MS_BTN1          ,KC_MS_BTN2          ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_PGUP             ,LCTL(LGUI(KC_RIGHT)),KC_MS_WH_UP         ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    LGUI(RCTL(KC_LEFT)) ,KC_MS_WH_DOWN       ,LCTL(KC_C)          ,KC_TRANSPARENT      ,KC_MEDIA_STOP       ,KC_MEDIA_PLAY_PAUSE ,
    KC_PGDOWN           ,LCTL(LSFT(KC_N))    ,LCTL(LSFT(KC_J))    ,KC_MEDIA_PREV_TRACK ,KC_MEDIA_NEXT_TRACK ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_AUDIO_VOL_UP     ,KC_AUDIO_VOL_DOWN   ,KC_AUDIO_MUTE       ,KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,
    KC_TRANSPARENT      ,KC_TRANSPARENT      ,KC_TRANSPARENT
  ),

  [7] = LAYOUT_ergodox(
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,

    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_UP         ,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_LEFT       ,KC_DOWN       ,KC_RIGHT      ,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT
  ),

  [8] = LAYOUT_ergodox(
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_Q          ,KC_W          ,KC_E          ,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_ENTER      ,KC_A          ,KC_S          ,KC_D          ,KC_F          ,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_Z          ,KC_X          ,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,
    KC_SPACE      ,KC_LSHIFT     ,KC_TRANSPARENT,

    TO(0)         ,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_PGDOWN     ,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_ENTER      ,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,
    KC_TRANSPARENT,
    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT
  ),
};
// Used for blinking leds on layers higher than 7
uint16_t blink_timer = 0;
uint16_t blink_elapsed = 0;
bool blink_led_1 = false;
bool blink_led_2 = false;
bool blink_led_3 = false;

void matrix_scan_kb(void){
    // first 7 layers do not need to blink
    if(blink_led_1 || blink_led_2 || blink_led_3){
        ergodox_board_led_off();
        ergodox_right_led_1_off();
        ergodox_right_led_2_off();
        ergodox_right_led_3_off();
        blink_elapsed = timer_elapsed(blink_timer);
        if(blink_elapsed > 2000) { blink_timer = timer_read();}
        if(blink_elapsed < 1000) {
            if(blink_led_1) ergodox_right_led_1_on();
            if(blink_led_2) ergodox_right_led_2_on();
            if(blink_led_3) ergodox_right_led_3_on();
        }
    }
    matrix_scan_user();
};

layer_state_t layer_state_set_user(layer_state_t state)
{

  uint8_t layer = get_highest_layer(state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  blink_led_1=false;
  blink_led_2=false;
  blink_led_3=false;

  switch (layer)
  {
  case 0:
    rgblight_setrgb(0, 200, 200);
    break;
  case 1:
    ergodox_right_led_1_on();
    rgblight_setrgb(0, 200, 0); // green
    break;
  case 2:
    ergodox_right_led_2_on();
    rgblight_setrgb(0, 0, 255);
    break;
  case 3:
    ergodox_right_led_3_on();
    rgblight_setrgb(255, 0, 0);
    break;
  case 4:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    rgblight_setrgb(200, 65, 0);
    break;
  case 5:
    ergodox_right_led_1_on();
    ergodox_right_led_3_on();
    rgblight_setrgb(0, 80, 33);
    break;
  case 6:
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
    rgblight_setrgb(0, 10, 200);
    break;
  case 7:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
    rgblight_setrgb(90, 150, 90);
    break;
  case 8:
    blink_led_1=true;
    rgblight_setrgb(100, 0, 100);
    break;
  case 9:
    rgblight_setrgb(200, 150, 90);
    break;
//   default:
//     rgblight_setrgb(0, 200, 200);
//     break;
  }
  return state;
};

// use leds to indicate when a one shot mod is on
void oneshot_mods_changed_user(uint8_t mods) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  // One shot checks
  if (mods & MOD_MASK_SHIFT) {
    ergodox_right_led_1_on();
  }
  if (mods & MOD_MASK_CTRL) {
    ergodox_right_led_2_on();
  }
  if (mods & MOD_MASK_ALT) {
    ergodox_right_led_3_on();
  }
  // if (mods & MOD_MASK_GUI) {
  //   println("Oneshot mods GUI");
  // }
  }

void oneshot_locked_mods_changed_user(uint8_t mods) {
    oneshot_mods_changed_user(mods);
}

//=============== alt_tab callbacks
void alt_tab_activated(void){
    layer_on(7); // activate motion layer
}
void alt_tab_deactivated(void){
    layer_off(7); // activate motion layer
}
