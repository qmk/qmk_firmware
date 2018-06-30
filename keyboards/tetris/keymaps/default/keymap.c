#include "tetris.h"
#include "action_layer.h"

#ifdef AUDIO_ENABLE
  #include "audio.h"
  float  tone_caps[][2]  = SONG( CAPS_LOCK_ON_SOUND );
  float  tone_taps[][2]     = SONG( E__NOTE( _A6 ) );
#endif

/* Fillers to make layering more clear */
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define _BASE  0
#define _CODE  1
#define _NAVI  2
#define _FUNC  3
#define _SYMB  4
#define _NUMB  5
#define _MARO  6
#define _RGB  7
#define _ADJUST  8
#define _GAME  9

/* RGB colors */
#define RGB_Layer_1_Base_Color 0, 128, 0
#define RGB_Layer_2_Base_Color 0,0,0
#define RGB_Layer_3_Base_Color 0,0,0
#define RGB_Layer_4_Base_Color 0,0,0
#define RGB_Layer_5_Base_Color 0,0,0
#define RGB_Layer_6_Base_Color 64, 0, 64
#define RGB_Layer_7_Base_Color 0, 0,0
#define RGB_Layer_8_Base_Color 0,0,0
#define RGB_Layer_9_Base_Color 0,0,0
#define RGB_Caps_Color 6,50,50
#define RGB_TAP_On_Color 0,128,0
#define RGB_TAP_Off_Color 128,0,0
#define RGB_TAP_Base_Color 0,0,0

extern rgblight_config_t	rgblight_config;
bool				NUMLAY_STATUS		= false;
int				RGB_LAYER0_mode		= 6;
bool				RGB_TAP_STATE		= false;
static uint8_t			current_layer		= 0;
static bool			has_layer_changed	= true;
static bool			save_rgbmode		= true;
static bool			caps			= false;

/* Tap Dance function */
void dance_cln_finished( qk_tap_dance_state_t* state, void* user_data )
{
  if ( state->count == 1 )
  {
    register_code( KC_LSFT );
  } else {
    layer_on( _SYMB );
    #ifdef AUDIO_ENABLE
      PLAY_SONG( tone_taps );
    #endif
  }
}


void dance_cln_reset( qk_tap_dance_state_t* state, void* user_data )
{
  if ( state->count == 1 )
  {
    unregister_code( KC_LSFT );
  }else  {
    uint8_t layer = biton32( layer_state );
    if ( layer == _SYMB )
    {
      layer_off( _SYMB );
      rgblight_mode( RGB_LAYER0_mode );
    }
  }
}

enum my_keycodes {
  RGB_TAP = SAFE_RANGE,
  KC_00
};

/* Tap Dance Declarations */
enum {
  TD_Mute_Next = 0,
  TD_SFT,
  TD_LBRC,
  TD_RBRC
};

/* Tap Dance Definitions */
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_Mute_Next]  = ACTION_TAP_DANCE_DOUBLE( KC_MUTE, KC_MNXT )
  ,[TD_SFT]  = ACTION_TAP_DANCE_FN_ADVANCED( NULL, dance_cln_finished, dance_cln_reset )
  ,[TD_LBRC]  = ACTION_TAP_DANCE_DOUBLE( KC_LBRC,   KC_LCBR )
  ,[TD_RBRC]  = ACTION_TAP_DANCE_DOUBLE( KC_RBRC,   KC_RCBR )
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* BASE - QWERTY
 *                       ,-----------------------------------------------------------------------------------.
 *                       | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  BS  |  
 *                       |------+------+------+------+------+-------------+------+------+------+------+------|
 * shift + Esc = ~ -->   | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|  <-- shift + Enter = "
 *                       |------+------+------+------+------+------|------+------+------+------+------+------|
 *                       | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Mute |  
 *                       |------+------+------+------+------+------+------+------+------+------+------+------|  <-- tap: 1.Mute 2.Next
 *                       | Ctrl | GUI  |  Alt |   [  |   -  |    Space    |   =  |   ]  |  Fx  |   \  |  Del |
 *                       `-----------------------------------------------------------------------------------'
 */

[_BASE] = LAYOUT_planck_mit(
  LT( _ADJUST,KC_TAB), KC_Q,    KC_W,     KC_E,          KC_R,                    KC_T,     KC_Y,      KC_U,                KC_I,          KC_O,             KC_P,    KC_BSPC,
  LT( _NUMB,KC_ESC),   KC_A,    KC_S,     KC_D,          KC_F,                    KC_G,     KC_H,      KC_J,                KC_K,          LT( _RGB, KC_L ), KC_SCLN, KC_ENT,
  TD( TD_SFT ),        KC_Z,    KC_X,     KC_C,          KC_V,                    KC_B,     KC_N,      KC_M,                KC_COMM,       KC_DOT,           KC_UP,   TD( TD_Mute_Next ),
  KC_LCTL,             KC_LGUI, KC_LALT,  TD( TD_LBRC ), LT( _NAVI, KC_MINS ),  LT( _CODE,  KC_SPC ),  LT( _FUNC, KC_EQL ), TD( TD_RBRC ), KC_LEFT,          KC_DOWN, KC_RGHT ),

/* Code
 *                       ,-----------------------------------------------------------------------------------.
 *                       |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 *                       |------+------+------+------+------+-------------+------+------+------+------+------|
 *                       |  `   |   <  |   [  |   {  |   (  |   &  | Left | Down |  Up  | Down |   ;  |   '  |
 *                       |------+------+------+------+------+------|------+------+------+------+------+------|
 *                       |      |   >  |   ]  |   }  |   )  |   |  |      |      |   ,  |   .  |   /  | Play |
 *                       |------+------+------+------+------+------+------+------+------+------+------+------|
 *                       |      |      |      |   [  | BkSp |   =======   |  Del |   ]  |      |   \  |      |
 *                       `-----------------------------------------------------------------------------------'
 */

[_CODE] = LAYOUT_planck_mit( /* 1 - Code */
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_GRV,  KC_LABK, KC_LBRC, KC_LCBR, KC_LPRN, KC_AMPR, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_QUOT,
  _______, KC_RABK, KC_RBRC, KC_RCBR, KC_RPRN, KC_PIPE, XXXXXXX, XXXXXXX, _______, _______, KC_SLSH, KC_MPLY,
  _______, _______, _______, KC_LBRC,     KC_BSPC,      _______, KC_DEL,  KC_RBRC, _______, KC_BSLS, _______ ),

/* Navi
 *                       ,-----------------------------------------------------------------------------------.
 *                       |      |      |      | PgUp |      |      |      |      |Insert|      |Prtsc |      |
 *                       |------+------+------+------+------+-------------+------+------+------+------+------|
 *                       |  ~   |      | Home | PgDn |  End |      |      |      |      |SrcLck|      |      |
 *                       |------+------+------+------+------+------|------+------+------+------+------+------|
 *                       |      |      |      |      |      | Break|      |      |      |      | PgUp |      |
 *                       |------+------+------+------+------+------+------+------+------+------+------+------|
 *                       |      |      |      |      |      |             |      |      | Home | PgDn |  End |
 *                       `-----------------------------------------------------------------------------------'
 */

[_NAVI] = LAYOUT_planck_mit(
  _______, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, KC_PSCR, _______,
  KC_TILD, XXXXXXX, KC_HOME, KC_PGDN, KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLCK, _______, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, _______,
  _______, _______, _______, _______, _______,     _______,      _______, _______, KC_HOME, KC_PGDN, KC_END ),

/* Func
 *                       ,-----------------------------------------------------------------------------------.
 *                       |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | F7   |  F8  |  F9  | F10  |      |
 *                       |------+------+------+------+------+-------------+------+------+------+------+------|
 *                       |      |  F11 |  F12 |      |      |      |      |      |      |      |      |      |
 *                       |------+------+------+------+------+------|------+------+------+------+------+------|
 *                       |      |      |      |      |      |      |      |      |      |      |      |      |
 *                       |------+------+------+------+------+------+------+------+------+------+------+------|
 *                       |      |      |      |      |      |             |      |      |      |      |      |
 *                       `-----------------------------------------------------------------------------------'
 */

[_FUNC] = LAYOUT_planck_mit(
  _______ , KC_F1,   KC_F2 ,   KC_F3,   KC_F4,   KC_F5,   KC_F6 ,   KC_F7,   KC_F8,   KC_F9,   KC_F10, _______,
  _______ , KC_F12,  KC_F12 ,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______ , XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______ , _______, _______ , _______, _______,      _______, _______ , _______, _______, _______, _______ ),


/* Symb - double tap shift
 *                       ,-----------------------------------------------------------------------------------.
 *                       |   |  |   !  |   @  |   #  |  $   |   %  |  ^   |  &   |  *   |  (   |  )   |      |
 *                       |------+------+------+------+------+-------------+------+------+------+------+------|
 *                       |      |      |      |      |      |      |      |      |      |      |   :  |   "  |
 *                       |------+------+------+------+------+------|------+------+------+------+------+------|
 *                       |      |      |      |      |      |      |      |      |   <  |  >   |  ?   |      |
 *                       |------+------+------+------+------+------+------+------+------+------+------+------|
 *                       |      |      |      |   {  |  _   |             |  +   |   }  |      |      |      |
 *                       `-----------------------------------------------------------------------------------'
 */

[_SYMB] = LAYOUT_planck_mit(
  KC_PIPE, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COLN, KC_DQUO,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, KC_QUES, _______,
  _______, _______, _______, KC_LCBR, KC_UNDS,     _______,      KC_PLUS, KC_RCBR, _______, KC_PIPE, _______ ),

/* Number
 *                       ,-----------------------------------------------------------------------------------.
 *                       |      |  +   |  -   |      |      |      |      |  7   |  8   |  9   |      |      |
 *                       |------+------+------+------+------+-------------+------+------+------+------+------|
 *                       |      |  *   |  /   |  =   |      |      |      |  4   |  5   |  6   |      |      |
 *                       |------+------+------+------+------+------|------+------+------+------+------+------|
 *                       |      |      |      |      |      |      |      |  1   |  2   |  3   |      |Layer0|
 *                       |------+------+------+------+------+------+------+------+------+------+------+------|
 *                       |      |      |      |      |      |             |  0   |  00  |  .   |      |      |
 *                       `-----------------------------------------------------------------------------------'
 */

[_NUMB] = LAYOUT_planck_mit( /* 5 - Numpad */
  _______, KC_PPLS, KC_PMNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7, KC_8,  KC_9,   XXXXXXX, _______, 
  _______, KC_PAST, KC_PSLS, KC_EQL,  XXXXXXX, XXXXXXX, XXXXXXX, KC_4, KC_5,  KC_6,   XXXXXXX, _______, 
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1, KC_2,  KC_3,   XXXXXXX, TO( 0 ), 
  _______, _______, _______, _______,    _______,       XXXXXXX, KC_0, KC_00, KC_DOT, XXXXXXX, _______ ),

/* MARO Empty
 *                       ,-----------------------------------------------------------------------------------.
 *                       |      |      |      |      |      |      |      |      |      |      |      |      |
 *                       |------+------+------+------+------+-------------+------+------+------+------+------|
 *                       |   |      |      |      |      |      |      |      |      |      |      |      |
 *                       |------+------+------+------+------+------|------+------+------+------+------+------|
 *                       |      |      |      |      |      |      |      |      |      |      |      |      |
 *                       |------+------+------+------+------+------+------+------+------+------+------+------|
 *                       |      |      |      |      |      |             |      |      |      |      |      |
 *                       `-----------------------------------------------------------------------------------'
 */

[_MARO] = LAYOUT_planck_mit(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,      _______,     _______, _______, _______, _______, _______ ),

/* RGB
 *                       ,-----------------------------------------------------------------------------------.
 *                       |      |      |      |      |      | _TAP |      |      |      |      |      |      |
 *                       |------+------+------+------+------+-------------+------+------+------+------+------|
 *                       | MOD  | M_R  | M_SW | M_K  | M_X  | M_G  |      |      |      |      |      |      |
 *                       |------+------+------+------+------+------|------+------+------+------+------+------|
 *                       | HUI  | SAI  | VAI  |      |      |      |      |      |      |      |      |      |
 *                       |------+------+------+------+------+------+------+------+------+------+------+------|
 *                       | HUD  | SAD  | VAD  |      |      |    RGB_TOG  |      |      |      |      |      |
 *                       `-----------------------------------------------------------------------------------'
 */

[_RGB] = LAYOUT_planck_mit(
  _______, _______, _______,  _______, _______, RGB_TAP, _______, _______, _______, _______, _______, _______,
  RGB_MOD, RGB_M_R, RGB_M_SW, RGB_M_K, RGB_M_X, RGB_M_G, _______, _______, _______, _______, _______, _______,
  RGB_HUI, RGB_SAI, RGB_VAI,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
  RGB_HUD, RGB_SAD, RGB_VAD,  _______, _______,     RGB_TOG,      _______, _______, _______, _______, _______ ),

/* Func
 *                       ,-----------------------------------------------------------------------------------.
 *                       |      |      |      |      |      |      |      |      |      |      |Layer0| Rest |
 *                       |------+------+------+------+------+-------------+------+------+------+------+------|
 *                       | Caps |      |      |      |      | Game |      |      |      |      |      |      |
 *                       |------+------+------+------+------+------|------+------+------+------+------+------|
 *                       |      |      |      |      |      |      | Numb | Music|      |      |      |      |
 *                       |------+------+------+------+------+------+------+------+------+------+------+------|
 *                       |      |      |      |      |      |             |      |      |      |      |      |
 *                       `-----------------------------------------------------------------------------------'
 */

[_ADJUST] = LAYOUT_planck_mit(
  _______, _______, _______, _______, _______, _______,   _______,   _______, _______, _______, TO( 0 ), RESET  ,
  KC_CAPS, _______, _______, _______, _______, TO(_GAME), _______,   _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,   TO(_NUMB), MU_TOG,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______,      _______,         _______, _______, _______, _______, _______ ),

[_GAME] = LAYOUT_planck_mit(
  XXXXXXX,KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
  XXXXXXX,KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,KC_LCTL, KC_A,    KC_S,    KC_D,    KC_B,    KC_N,    KC_M,    XXXXXXX, XXXXXXX, KC_UP,   TO( 0 ),
  XXXXXXX,KC_LSFT, KC_Z,    KC_X,    KC_C,       KC_SPC,        XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT ),
};

/* Encoder */
static uint8_t  encoder_state  = 0;
static int8_t  encoder_value  = 0;
static int8_t  encoder_LUT[]  = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };

/* Timer */
static uint16_t TAP_RGB_timer;
static uint16_t RGB_encoder_timer;

/* Encoder state RGB_display */
static uint8_t  RGB_encoder_count=6; 
static bool  RGB_encoder_bool  = false;

/* RGB tap HUE */
static uint16_t  Type_Hue=270; 

void matrix_init_user( void )
{
  _delay_ms( 200 );

  /* Encoder init */
  encoder_state = PIND & 0x3;

  /* Timer init */
  RGB_encoder_timer= timer_read();
  TAP_RGB_timer= timer_read();
}


void matrix_scan_user( void )
{
/* Layer  */
  uint8_t layer = biton32( layer_state );

/* Encoder  */
  encoder_state  <<= 2;
  encoder_state  |= (PIND & 0x3);
  encoder_value  += encoder_LUT[encoder_state & 0xF];

/* Encoder state RGB display */
  if (RGB_encoder_bool){
    if (timer_elapsed(RGB_encoder_timer) > 2500) {
      RGB_encoder_bool=false;
      if (RGB_TAP_STATE) {
        rgblight_mode( 1 );
        rgblight_setrgb( RGB_TAP_Base_Color );
      }else{
        rgblight_mode( RGB_LAYER0_mode );
      }
    }
  }

/* Display the Caps state */
  if (caps==true){
    rgblight_setrgb_at(RGB_Caps_Color,12);
  }

/* Start of Encoder clockwise */
  if ( encoder_value >= 4 ) {

  /* Start of Encoder state RGB_display */
    if (!RGB_encoder_bool){
      RGB_encoder_timer=timer_read();
      RGB_encoder_bool=true;
      RGB_encoder_count=5;
      rgblight_mode(1);
      rgblight_setrgb( 0,0,0 );
    }else if (RGB_encoder_bool && timer_elapsed(RGB_encoder_timer) < 800) {
      RGB_encoder_timer=timer_read();
      RGB_encoder_count-=1;
      if (RGB_encoder_count>5 || RGB_encoder_count<1){
        RGB_encoder_count=5;
        rgblight_setrgb(0, 0, 0);
      }
    }
    rgblight_setrgb_at(0,255,0,5);
    if (RGB_encoder_count<1) {RGB_encoder_count=1;}
      switch (RGB_encoder_count) {
        case 5:
          rgblight_setrgb_at(0, 255, 0,4);
          break;
        case 4:
          rgblight_setrgb_at(0, 255, 0,3);
          break;
        case 3:
          rgblight_setrgb_at(0, 255, 0,2);
          break;
        case 2:
          rgblight_setrgb_at(0, 255, 0,1);
          break;
        case 1:
          rgblight_setrgb_at(0, 255, 0,0);
          break;
      } 
  /* End of Encoder state RGB_display */

  /* Start of Set Encoder Keycode */
    switch ( layer )
    {
    case 0:
      register_code( KC_VOLD );
      unregister_code( KC_VOLD );
      break;
    case _CODE:
      register_code( KC_LEFT );
      unregister_code( KC_LEFT );
      break;
    case _RGB:
      rgblight_decrease_val();
      break;
    case _NUMB:
      register_code( KC_LEFT );
      unregister_code( KC_LEFT );
      break;
    case _MARO:
      register_code( KC_UP );
      unregister_code( KC_UP );
      break;
    default:
      register_code( KC_VOLD );
      unregister_code( KC_VOLD );
    }
  /* End of Set Encoder Keycode */

  }

/* End of Encoder clockwise */

/* Start of Encoder anti-clockwise */
  if ( encoder_value <= -4 )
  {
    /* Start of Encoder state RGB_display */
    if (!RGB_encoder_bool){
      RGB_encoder_timer=timer_read();
      RGB_encoder_bool=true;
      RGB_encoder_count=6;
      rgblight_mode(1);
      rgblight_setrgb( 0,0,0 );
    }else if (RGB_encoder_bool && timer_elapsed(RGB_encoder_timer) < 800) {
      RGB_encoder_timer=timer_read();
      RGB_encoder_count+=1;
      if (RGB_encoder_count<6 || RGB_encoder_count> 10){
        RGB_encoder_count=6;
        rgblight_setrgb(0, 0, 0);
      }
    }
    rgblight_setrgb_at(0,  0,255,6);
    if (RGB_encoder_count>11) {
      RGB_encoder_count=11;
    }
    switch (RGB_encoder_count) {
      case 6:
        rgblight_setrgb_at(0,  0,255,7);
        break;
      case 7:
        rgblight_setrgb_at(0,  0,255,8);
        break;
      case 8:
        rgblight_setrgb_at(0,  0,255,9);
        break;
      case 9:
        rgblight_setrgb_at(0,  0,255,10);
        break;
      case 10:
        rgblight_setrgb_at(0,  0,128,11);
        break;
    } 
  /* End of Encoder state RGB_display */

  /* Start of Set Encoder Keycode */
    switch ( layer )
    {
      case 0:
        register_code( KC_VOLU );
        unregister_code( KC_VOLU );
        break;
      case _CODE:
        register_code( KC_RGHT );
        unregister_code( KC_RGHT );
        break;
      case _RGB:
        rgblight_increase_val();
        break;
      case _NUMB:
        register_code( KC_RGHT );
        unregister_code( KC_RGHT );
        break;
      case _MARO:
        register_code( KC_DOWN );
        unregister_code( KC_DOWN );
        break;
      default:
        register_code( KC_VOLU );
        unregister_code( KC_VOLU );
    }
  /* End of Set Encoder Keycode */
  
}

/* End of Encoder anti-clockwise */
  
  encoder_value %= 4;

/* Start of RGB with Layer change */

  /* Save the Layer0 RGB state */
  if ( save_rgbmode == true )  {
    if (RGB_TAP_STATE==false)
    {
      RGB_LAYER0_mode = rgblight_config.mode;
    }
  }
  save_rgbmode = false;

 /* When the layer is changed */
  if ( layer != current_layer && caps == false)  {
    has_layer_changed  = true;
    current_layer    = layer; /* update layer information */
  }
  /* Check for layer change, and apply color if its changed since last check */
  if ( has_layer_changed )
  {
    /* change backlight based on layer.  These should be numbers or whatever you defined the layers as */
    switch ( layer )
    {
      case 0:

        /* if the key tap RGB effect is enable */
        if (RGB_TAP_STATE==true){
          rgblight_mode(1);
          rgblight_setrgb( RGB_TAP_Base_Color );
        }
        else{
          rgblight_mode( RGB_LAYER0_mode );
        }
        break;

      case _CODE: //1
/* Save Layer0 RGB state */
        RGB_LAYER0_mode = rgblight_config.mode;

/* set all the RGB color under the switch */
        rgblight_mode( 1 );
        rgblight_setrgb(RGB_Layer_1_Base_Color); 

        /* set each of the RGB led color under the switch */
        rgblight_setrgb_at(64, 64, 64,1);    // Q
        rgblight_setrgb_at(64, 64, 64,2);    // W
        rgblight_setrgb_at(64, 64, 64,3);    // E
        rgblight_setrgb_at(64, 64, 64,4);    // R
        rgblight_setrgb_at(64, 64, 64,5);    // T
        rgblight_setrgb_at(64, 64, 64,6);    // Y
        rgblight_setrgb_at(64, 64, 64,7);    // U
        rgblight_setrgb_at(64, 64, 64,8);    // I
        rgblight_setrgb_at(64, 64, 64,9);    // O
        rgblight_setrgb_at(64, 64, 64,10);   // P
        rgblight_setrgb_at(64, 0, 0,40);     // -
        rgblight_setrgb_at(64, 0, 0,42);     // =
      break;

    case _NAVI: //2
      RGB_LAYER0_mode = rgblight_config.mode;

      rgblight_mode( 1 );
      rgblight_setrgb(RGB_Layer_2_Base_Color);

      rgblight_setrgb_at(64, 0, 64,3);
      rgblight_setrgb_at(64, 0, 64,14);
      rgblight_setrgb_at(64, 0, 64,15);
      rgblight_setrgb_at(64, 0, 64,16);
      rgblight_setrgb_at(64, 64, 0,8);
      rgblight_setrgb_at(64, 64, 0,10);
      rgblight_setrgb_at(64, 64, 0,21);
      rgblight_setrgb_at(64, 64, 0,29);
      rgblight_setrgb_at(64, 0, 0,11);
      rgblight_setrgb_at(0, 0, 64,34);
      rgblight_setrgb_at(0, 0, 64,44);
      rgblight_setrgb_at(0, 0, 64,45);
      rgblight_setrgb_at(0, 0, 64,46);
      break;
    case _FUNC: //3
      RGB_LAYER0_mode = rgblight_config.mode;

      rgblight_mode( 1 );
      rgblight_setrgb(RGB_Layer_3_Base_Color);

      rgblight_setrgb_at(0, 0, 64,1);
      rgblight_setrgb_at(0, 0, 64,2);
      rgblight_setrgb_at(0, 0, 64,3);
      rgblight_setrgb_at(0, 0, 64,4);
      rgblight_setrgb_at(0, 0, 64,5);
      rgblight_setrgb_at(0, 0, 64,6);
      rgblight_setrgb_at(0, 0, 64,7);
      rgblight_setrgb_at(0, 0, 64,8);
      rgblight_setrgb_at(0, 0, 64,9);
      rgblight_setrgb_at(0, 0, 64,10);
      rgblight_setrgb_at(0, 0, 64,13);
      rgblight_setrgb_at(0, 0, 64,14);
      break;

    case _SYMB: //4
      RGB_LAYER0_mode = rgblight_config.mode;

      rgblight_mode( 1 );
      rgblight_setrgb(RGB_Layer_4_Base_Color);

      rgblight_setrgb_at(0, 64, 64,1);
      rgblight_setrgb_at(0, 64, 64,2);
      rgblight_setrgb_at(0, 64, 64,3);
      rgblight_setrgb_at(0, 64, 64,4);
      rgblight_setrgb_at(0, 64, 64,5);
      rgblight_setrgb_at(0, 64, 64,6);
      rgblight_setrgb_at(0, 64, 64,7);
      rgblight_setrgb_at(0, 64, 64,8);
      rgblight_setrgb_at(0, 64, 64,9);
      rgblight_setrgb_at(0, 64, 64,10);
      rgblight_setrgb_at(0, 64, 64,12);
      rgblight_setrgb_at(0, 64, 64,22);
      rgblight_setrgb_at(0, 64, 64,23);
      rgblight_setrgb_at(0, 64, 64,32);
      rgblight_setrgb_at(0, 64, 64,33);
      rgblight_setrgb_at(0, 64, 64,34);
      rgblight_setrgb_at(0, 64, 64,39);
      rgblight_setrgb_at(0, 64, 64,40);
      rgblight_setrgb_at(0, 64, 64,42);
      rgblight_setrgb_at(0, 64, 64,43);
      break;

    case _NUMB: //5
      RGB_LAYER0_mode = rgblight_config.mode;

      rgblight_mode( 1 );
      rgblight_setrgb(RGB_Layer_5_Base_Color);

      rgblight_setrgb_at(0,64,0,1);
      rgblight_setrgb_at(0,64,0,2);
      rgblight_setrgb_at(0,64,0,13);
      rgblight_setrgb_at(0,64,0,14);
      rgblight_setrgb_at(0,64,64,15);
      rgblight_setrgb_at(64,64,64,7);
      rgblight_setrgb_at(64,64,64,8);
      rgblight_setrgb_at(64,64,64,9);
      rgblight_setrgb_at(64,64,64,19);
      rgblight_setrgb_at(64,64,64,20);
      rgblight_setrgb_at(64,64,64,21);
      rgblight_setrgb_at(64,64,64,31);
      rgblight_setrgb_at(64,64,64,32);
      rgblight_setrgb_at(64,64,64,33);
      rgblight_setrgb_at(64,64,64,42);
      rgblight_setrgb_at(64,64,64,43);
      rgblight_setrgb_at(0,128,0,44);
      break;
    case _MARO: //6
      RGB_LAYER0_mode = rgblight_config.mode;

      rgblight_mode( 1 );
      rgblight_setrgb(RGB_Layer_6_Base_Color);
      break;

    case _RGB: //7
      RGB_LAYER0_mode = rgblight_config.mode;

      rgblight_mode( 1 );
      rgblight_setrgb(RGB_Layer_7_Base_Color);

      rgblight_setrgb_at(1,143,225,0);
      rgblight_setrgb_at(39,21,107,1);
      rgblight_setrgb_at(208,0,0,2);
      rgblight_setrgb_at(64,64,64,21);
      break;
    case _ADJUST: //8
      RGB_LAYER0_mode = rgblight_config.mode;

      rgblight_mode( 1 );
      rgblight_setrgb(RGB_Layer_8_Base_Color);

      rgblight_setrgb_at(0,64,0,10);
      rgblight_setrgb_at(64,0,0,11);
      rgblight_setrgb_at(0,64,0,17);
      rgblight_setrgb_at(0,64,0,30);
      rgblight_setrgb_at(6,50,50,12);
      break;

    case _GAME: //9
      RGB_LAYER0_mode = rgblight_config.mode;

      rgblight_mode( 1 );
      rgblight_setrgb(RGB_Layer_9_Base_Color);

      rgblight_setrgb_at(0,0,64,15);
      rgblight_setrgb_at(0,0,64,26);
      rgblight_setrgb_at(0,0,64,27);
      rgblight_setrgb_at(0,0,64,28);
      rgblight_setrgb_at(64,0,0,35);
      break;

    default:
      rgblight_mode( RGB_LAYER0_mode );
    }
    has_layer_changed = false;
  }
/* End of RGB with Layer change */

}  // End of matrix_scan_user 



/* shift + enter = "  from：https://github.com/qmk/qmk_firmware/blob/e899cb8940da04fa2610604f0aab417db7fac119/keyboards/mitosis/keymaps/datagrok/keymap.c */

bool  comm_shifted  = false;
bool  ques_shifted  = false;
static uint8_t  key_index  = 0;
uint8_t    shifted;
uint16_t  s_keycode;
bool    *k_shifted;

bool process_record_user( uint16_t keycode, keyrecord_t *record ){

/* Start of key tap RGB effect */
  if ( RGB_TAP_STATE ==true ) {
    key_index=(record->event.key.col)+(record->event.key.row)*12;

/* Change the Hue of the RGB color with the type speed */
    if (timer_elapsed(TAP_RGB_timer) >10000){
      TAP_RGB_timer=timer_read();
      Type_Hue=270;
    }else if (timer_elapsed(TAP_RGB_timer) >1000){
      Type_Hue+=30;
      if (Type_Hue>270) {
        Type_Hue=270;}
      }else{
        TAP_RGB_timer=timer_read();
        Type_Hue-=10;
      if (Type_Hue<10) {
        Type_Hue=10;}
      }
      if (key_index>42){        //fix the RGB index of the MIT layout position
        key_index=key_index-1;
      }
      if ( record->event.pressed  ) {
        rgblight_sethsv_at(Type_Hue,255,255,key_index);
      } else {
        rgblight_setrgb_at(RGB_TAP_Base_Color,key_index);
      }
    }
/* End of key tap RGB effect */

  switch ( keycode )
  {
  /* save the RGB state when set the new  */
    case RGB_M_R:
      save_rgbmode = true;
      break;
    case RGB_M_SW:
      save_rgbmode = true;
      break;
    case RGB_M_X:
      save_rgbmode = true;
      break;
    case RGB_M_G:
      save_rgbmode = true;
      break;
    case RGB_MODE_KNIGHT:
      save_rgbmode = true;
      break;

/* Define a New Keycode: double zero  */
    case KC_00:
      if (record->event.pressed) {
        // Do something when pressed
      } else {
        register_code( KC_0 );   // send 0
        unregister_code( KC_0 );

        register_code( KC_0 );   // send 0 twice without macro
        unregister_code( KC_0 );
      }
      return false; // Skip all further processing of this key

    /* when the REST key is pressed the 'R' key will RED,the "Bottom Left"(esc of qmk-dfu) will be GREEN  */
     case RESET:
       rgblight_mode( 1 );
       rgblight_setrgb( 0, 0, 0 );
       rgblight_setrgb_at(128, 0, 0,4);   // R
       rgblight_setrgb_at(6, 128, 24,36); // Bottom Left key
    break;

/* Define a New Keycode: key tap RGB effect toggle  */
     case RGB_TAP:
       if ( !(record->event.pressed)) {
       /* If enable,the 'On' key will be green  */
         if (RGB_TAP_STATE) {
           RGB_TAP_STATE=false;
           rgblight_mode( 1 );
           rgblight_setrgb( RGB_TAP_Base_Color );
           rgblight_setrgb_at(RGB_TAP_Off_Color,16); // O - on
         }else{
       /* If disenable,the 'oFf' key will be red  */
           RGB_TAP_STATE=true;
           rgblight_mode( 1 ); 
           rgblight_setrgb( RGB_TAP_Base_Color );
           rgblight_setrgb_at(RGB_TAP_On_Color,9);   // F - off
         }
       }
       break;

/*  special shift keys */
  case KC_ENT:
    s_keycode  = KC_QUOT;
    k_shifted  = &ques_shifted;
    break;
  case KC_UP:
    s_keycode  = KC_SLSH;
    k_shifted  = &ques_shifted;
    break;
  case KC_DOWN:
    s_keycode  = KC_BSLS;
    k_shifted  = &ques_shifted;
    break;
  default:
    return(true);
  }

  shifted = get_mods() & (MOD_BIT( KC_LSHIFT ) | MOD_BIT( KC_RSHIFT ) );

  /* Keydown. If shift is currently pressed, register its alternate keycode. */
  if ( record->event.pressed && shifted )
  {
    *k_shifted = true;
    register_code( s_keycode );
    return(false);
    /*
     * Keyup. If shift was pressed back when the key was pressed, unregister
     * its alternate keycode.
     */
  } else if ( !(record->event.pressed) && *k_shifted )  {
    *k_shifted = false;
    unregister_code( s_keycode );
    return(false);
    /* Otherwise, behave as normal. */
  } else {
    return(true);
  }

} // End ofprocess_record_user


void led_set_user( uint8_t usb_led )
{
  static uint8_t old_usb_led = 0;
  _delay_ms( 10 ); /* gets rid of tick */

  if ( (usb_led & (1 << USB_LED_CAPS_LOCK) ) && !(old_usb_led & (1 << USB_LED_CAPS_LOCK) ) )  {
/* CAPS on */
    caps= true;
    rgblight_setrgb( 0,0,0 );
    rgblight_setrgb_at(RGB_Caps_Color,12);  // caps key
    #ifdef AUDIO_ENABLE
      PLAY_SONG( tone_caps );
    #endif
  }else if ( !(usb_led & (1 << USB_LED_CAPS_LOCK) ) && (old_usb_led & (1 << USB_LED_CAPS_LOCK) ) )  {

/* CAPS off */
    caps= false;
    if (RGB_TAP_STATE==false){
      rgblight_mode( RGB_LAYER0_mode );
    }else{
      rgblight_mode(1);
      rgblight_setrgb( 0,0,0 );
    }
    #ifdef AUDIO_ENABLE
      PLAY_SONG( tone_caps );
    #endif
  }
  old_usb_led = usb_led;
}  // End of led_set_user

