enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _GAME,
  _SPACEING,
  _LOWER,
  _RAISE,
  _MOV,
  _NUM,
  _ACCENT,
  _ACCENT2,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  GAME,
  SPACEING,
  LOWER,
  RAISE,
  UNIWIN,
  UNILIN,
  ACCENT,
  ACCENT2,
  AACCD,
  EACCD,
  IACCD,
  OACCD,
  UACCD,
  UDIER,
  NTILT,
  CTRAN,
  BACKLIT
};

// Def keys & Layers
#define LOWER LT(_LOWER, KC_BSPC)
#define RAISE LT(_RAISE, KC_ENT)
#define SPCMOV LT(_MOV, KC_SPC)
#define TABNUM LT(_NUM, KC_TAB)
#define NUM MO(_NUM)
#define ACCENT MO(_ACCENT)

// Def Unicode & characters
#ifdef UNICODEMAP_ENABLE
  enum unicode_names{
    AMAD,
    AMID,
    AMAI,
    AMII,
    EMAD,
    EMID,
    EMAI,
    EMII,
    IMAD,
    IMID,
    IMAI,
    IMII,
    OMAD,
    OMID,
    OMAI,
    OMII,
    UMAD,
    UMID,
    UMAI,
    UMII,
    UMAC,
    UMIC,
    NMAC,
    NMIC,
    CMAC,
    CMIC
  };

  const uint32_t PROGMEM unicode_map[] = {
    [AMAD] = 0x00C1,
    [AMID] = 0x00E1,
    [AMAI] = 0x00C0,
    [AMII] = 0x00E0,
    [EMAD] = 0x00C9,
    [EMID] = 0x00E9,
    [EMAI] = 0x00C8,
    [EMII] = 0x00E8,
    [IMAD] = 0x00CD,
    [IMID] = 0x00ED,
    [IMAI] = 0x00CC,
    [IMII] = 0x00EC,
    [OMAD] = 0x00D3,
    [OMID] = 0x00F3,
    [OMAI] = 0x00D2,
    [OMII] = 0x00F2,
    [UMAD] = 0x00DA,
    [UMID] = 0x00FA,
    [UMAI] = 0x00D9,
    [UMII] = 0x00F9,
    [UMAC] = 0x00DC,
    [UMIC] = 0x00FC,
    [NMAC] = 0x00D1,
    [NMIC] = 0x00F1,
    [CMAC] = 0x00C7,
    [CMIC] = 0x00E7
  };

  #define AACCD XP(AMID, AMAD)
  #define AACCI XP(AMII, AMAI)
  #define EACCD XP(EMID, EMAD)
  #define EACCI XP(EMII, EMAI)
  #define IACCD XP(IMID, IMAD)
  #define IACCI XP(IMII, IMAI)
  #define OACCD XP(OMID, OMAD)
  #define OACCI XP(OMII, OMAI)
  #define UACCD XP(UMID, UMAD)
  #define UACCI XP(UMII, UMAI)
  #define UDIER XP(UMIC, UMAC)
  #define NTILT XP(NMIC, NMAC)
  #define CTRAN XP(CMIC, CMAC)
#endif

// Sounds
#ifdef AUDIO_ENABLE
  #include "audio.h"
  float tone_startup[][2] = SONG(PREONIC_SOUND);
  float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
  float tone_qwerty[][2] = SONG(QWERTY_SOUND);
  float tone_colemak[][2] = SONG(COLEMAK_SOUND);
  float tone_dvorak[][2] = SONG(DVORAK_SOUND);
  float tone_game[][2] = SONG(GAME_SOUND);
  float tone_spaceing[][2] = SONG(SPACEING_SOUND);
  float tone_uniwin[][2] = SONG(UNICODE_WINDOWS);
  float tone_unilin[][2] = SONG(UNICODE_LINUX);
  float tone_capson[][2] = SONG(CAPS_LOCK_ON_SOUND);
  float tone_capspoff[][2] = SONG(CAPS_LOCK_OFF_SOUND);
#endif

// RGBLight Layers
// 6 5 4 3
//    0
// 7 8 1 2
#ifdef RGBLIGHT_ENABLE
  const rgblight_segment_t PROGMEM rgb_segment_capslock[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 1, HSV_WHITE}
  );

  const rgblight_segment_t PROGMEM rgb_segment_lower[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_RED}
  );

  const rgblight_segment_t PROGMEM rgb_segment_raise[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_RED}
  );

  const rgblight_segment_t PROGMEM rgb_segment_adjust[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_RED},
    {1, 1, HSV_RED}
  );

  const rgblight_segment_t PROGMEM rgb_segment_accent[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_RED}
  );

  const rgblight_segment_t PROGMEM rgb_segment_accent2[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 1, HSV_RED}
  );

  const rgblight_segment_t PROGMEM rgb_segment_mov[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_RED}
  );

  const rgblight_segment_t PROGMEM rgb_segment_num[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 4, HSV_RED}
  );

  const rgblight_segment_t* const PROGMEM rgb_segment_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_segment_capslock,
    rgb_segment_lower,
    rgb_segment_raise,
    rgb_segment_adjust,
    rgb_segment_accent,
    rgb_segment_accent2,
    rgb_segment_mov,
    rgb_segment_num
  );

  void keyboard_post_init_user(void) {
    rgblight_layers = rgb_segment_layers;
  }

  bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
  }

  layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(4, layer_state_cmp(state, _ACCENT));
    rgblight_set_layer_state(5, layer_state_cmp(state, _ACCENT2));
    rgblight_set_layer_state(6, layer_state_cmp(state, _MOV));
    rgblight_set_layer_state(7, layer_state_cmp(state, _NUM));
    return state;
  }
#endif

// Layers ext

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_qwerty);
            #endif
            #ifdef RGBLIGHT_ENABLE
              rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            #endif
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_colemak);
            #endif
            #ifdef RGBLIGHT_ENABLE
              rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            #endif
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dvorak);
            #endif
            #ifdef RGBLIGHT_ENABLE
              rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            #endif
          }
          return false;
          break;
        case GAME:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_GAME);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_game);
            #endif
            #ifdef RGBLIGHT_ENABLE
              rgblight_mode(RGBLIGHT_MODE_BREATHING);
            #endif
          }
          return false;
          break;
        case SPACEING:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_SPACEING);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_spaceing);
            #endif
            #ifdef RGBLIGHT_ENABLE
              rgblight_mode(RGBLIGHT_MODE_BREATHING);
            #endif
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case UNIWIN:
          if(record->event.pressed){
            set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_uniwin);
            #endif
          }
          return false;
          break;
        case UNILIN:
          if(record->event.pressed){
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_unilin);
            #endif
          }
          return false;
          break;
        case ACCENT:
          if (record->event.pressed) {
            layer_on(_ACCENT);
          } else {
            layer_off(_ACCENT);
          }
          return false;
          break;
        case ACCENT2:
          if (record->event.pressed) {
            layer_on(_ACCENT2);
          } else {
            layer_off(_ACCENT2);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef RGBLIGHT_ENABLE
              rgblight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
          }
          return false;
          break;
  }
    return true;
};

void matrix_init_user(void){
    #ifdef AUDIO_ENABLE
        wait_ms(50);
        PLAY_SONG(tone_startup);
    #endif
}

#ifdef AUDIO_ENABLE
void play_goodbye_tone(void){
  PLAY_SONG(tone_goodbye);
  wait_ms(150);
}

void shutdown_user(){
    PLAY_SONG(tone_goodbye);
    wait_ms(150);
    stop_all_notes();
}
#endif
