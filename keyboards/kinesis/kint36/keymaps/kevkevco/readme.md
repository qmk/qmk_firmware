# Kevin's Kinesis Advantage keymap

Tested with a Kinesis Advantage2, kinT (stapelberg) keyboard controller built
with a Teensy 3.6 microcontroller and a USA system layout.

## CAPSWORD and NUMWORD from replicaJunction
The concept here is simple: more often than you'd think, you need to type a single word in ALL CAPS. An easy example for me, as a programmer, is a constant value; in most programming languages, constants are typed in all caps by convention.

You typically have a few choices, but each one comes with a drawback. Here are the options I'm aware of:

* Use proper typing technique and alternate which hand holds Shift for each keypress
    * This can often end up requiring you to switch / re-press Shift again and again, making this a tedious process
* Hold a single Shift key down
    * This can lead to uncomfortable finger gymnastics
* Hit the Caps Lock key, then hit it again when you're done
    * Requires you to remember to hit it again, meaning a higher cognitive load
    * In some layouts for smaller keyboards, Caps Lock is not easily accessible (sometimes not mapped at all)
    
The solution to this problem is CAPSWORD. When enabled, it activates Caps Lock and begins running an additional callback on each keypress. If the keypress is an alphanumeric key or one of a specific few symbols (such as the underscore), nothing happens. Otherwise, before processing the keypress, Caps Lock is disabled again.

NUMWORD is a similar concept, but has a slightly more elaborate implementation. There's a bit of extra logic in the NUMWORD code that allows the keycode to act as a tap/hold key as well. Tapping enables NUMWORD while number keys are in use, while holding the key enables a number layer for the duration of the key hold and disables it again afterwards.

**Note:** The implementation of NUMWORD requires that the keyboard's layer definitions be accessible in a header file. In my case, since I use a fairly standard set of layers, I've declared it in my userspace.


# Credits

numword from replicaJunction

[bpruitt-goddard](https://github.com/qmk/qmk_firmware/blob/master/keyboards/ergodox_ez/keymaps/bpruitt-goddard/readme.md)
* Dynamic macro tap-dance



// Inactive Aliases
// #define NUMPAD  TG(_NUMPAD)
// #define ADJUST  MO(_ADJUST2)
// #define SPCFN   LT(_FUNCTION, KC_SPC)
// #define BSPCFN  LT(_FUNCTION2, KC_BSPC)
// #define ENTNS   LT(_NUMBERS, KC_ENT)
// #define DELNS   LT(_NUMBERS2, KC_DEL)
// #define CTLESC  CTL_T(KC_ESC)
// #define ALTAPP  ALT_T(KC_APP)
// #define CTL_A   LCTL(KC_A)
// #define CTL_C   LCTL(KC_C)
// #define CTL_V   LCTL(KC_V)
// #define CTL_X   LCTL(KC_X)
// #define CTL_Z   LCTL(KC_Z)
// #define CTL_Y   LCTL(KC_Y)
// #define CA_TAB  LCA(KC_TAB)
// #define HYPER   ALL_T(KC_NO)
// #define TD_ADJ  TD(ADJ)
// #define TD_LBCB TD(LBCB)
// #define TD_RBCB TD(RBCB)
// #define TD_EQPL TD(EQPL)
// #define TD_PLEQ TD(PLEQ)
// #define TD_MNUN TD(MNUN)
// #define TD_SLAS TD(SLAS)
// #define TD_GVTL TD(GVTL)
// #define TD_PPEQ TD(PPEQ)
// #define TD_PMUN TD(PMUN)
// #define TD_PSPA TD(PSPA)
// #define NKROTG  MAGIC_TOGGLE_NKRO




    case PRG_EQ: {
            if (record->event.pressed) {
                SEND_STRING("==");
            }
            return false;
        }
        case PRG_NE: {
            if (record->event.pressed) {
                SEND_STRING("!=");
            }
            return false;
        }

        case QK_MAKE: {
            if (record->event.pressed)
                SEND_STRING("qmk compile --keyboard " QMK_KEYBOARD " --keymap " QMK_KEYMAP);
            return false;
        }


<!-- 

ACTIVE

/*
,--------------------------------------------------------------.                                     ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                                     |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                                     `--------------------------------------------------------------'
,------------------------------------------------------.                                                     ,------------------------------------------------------.
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                                     |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                                     |        |        |        |        |        |         |
`---------+--------+--------+--------+--------+--------'                                                     `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                                       |        |        |        |        |
          `-----------------------------------'                                                                       `-----------------------------------'
	                                                   ,-----------------.                 ,-----------------.
	                                                   |        |        |                 |        |        |
	                                          ,--------+--------+--------|                 |--------+--------+--------.
	                                          |        |        |        |                 |        |        |        |
	                                          |        |        |--------|                 |--------|        |        |
	                                          |        |        |        |                 |        |        |        |
	                                          `--------------------------'                 `--------------------------'
*/

[_BLANK] = LAYOUT_pretty(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______,                                                                         _______, _______, _______, _______,
                                                        _______, _______,                   _______, _______,
                                                                 _______,                   _______,
                                               _______, _______, _______,                   _______, _______, _______
),





// Swapping Hands Matrix starting on line numbers that end in 0 for quick counting

/*  ---------------- LEFT HAND -----------------   ---------------- RIGHT HAND ---------------- */
#define LAYOUT_pretty(                                                                           \
    kC0, kD0, kE0, kC1, kD1, kE1, kC2, kD2, kE2,   kC3, kD3, kE3, kC4, kD4, kE4, kC5, kE5, kD5,  \
    k00, k10, k20, k30, k40, k50,                            k60, k70, k80, k90, kA0, kB0,       \
    k01, k11, k21, k31, k41, k51,                            k61, k71, k81, k91, kA1, kB1,       \
    k02, k12, k22, k32, k42, k52,                            k62, k72, k82, k92, kA2, kB2,       \
    k03, k13, k23, k33, k43, k53,                            k63, k73, k83, k93, kA3, kB3,       \
         k14, k24, k34, k54,                                      k64, k84, k94, kA4,            \
                             k56, k55,                  k96, k85,                                \
                                  k35,                  k86,                                     \
                        k36, k46, k25,                  k66, k75, k65                            \
) {                                              \
    { k00,  k01,  k02,  k03,  ___,  ___,  ___ }, \
    { k10,  k11,  k12,  k13,  k14,  ___,  ___ }, \
    { k20,  k21,  k22,  k23,  k24,  k25,  ___ }, \
    { k30,  k31,  k32,  k33,  k34,  k35,  k36 }, \
    { k40,  k41,  k42,  k43,  ___,  ___,  k46 }, \
    { k50,  k51,  k52,  k53,  k54,  k55,  k56 }, \
    { k60,  k61,  k62,  k63,  k64,  k65,  k66 }, \
    { k70,  k71,  k72,  k73,  ___,  k75,  ___ }, \
    { k80,  k81,  k82,  k83,  k84,  k85,  k86 }, \
    { k90,  k91,  k92,  k93,  k94,  ___,  k96 }, \
    { kA0,  kA1,  kA2,  kA3,  kA4,  ___,  ___ }, \
    { kB0,  kB1,  kB2,  kB3,  ___,  ___,  ___ }, \
    { kC0,  kC1,  kC2,  kC3,  kC4,  kC5,  ___ }, \
    { kD0,  kD1,  kD2,  kD3,  kD4,  kD5,  ___ }, \
    { kE0,  kE1,  kE2,  kE3,  kE4,  kE5,  ___ }  \
}
INACTIVE




/*
        Blank layer:
        ,-------------------------------------------------------------------------------.
        |          |      |      |        |        |          |        |        |       |
        `-------------------------------------------------------------------------------'
        ,-------------------------------------------------------------------------------.
        |          |      |      |        |        |          |        |        |       |
        `-------------------------------------------------------------------------------'
        ,-------------------------------------------.,-------------------------------------------.
        |        |      |      |      |      |      ||      |      |      |      |      |        |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        |        |      |      |      |      |      ||      |      |      |      |      |        |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        |        |      |      |      |      |      ||      |      |      |      |      |        |
        |--------+------+------+------+------+------||------+------+------+------+------+--------|
        |        |      |      |      |      |      ||      |      |      |      |      |        |
        `--------+------+------+------+------+------'`------+------+------+------+------+--------'
                 |      |      |      |      |              |      |      |      |      |
                 `---------------------------'              `---------------------------'
                                      ,-------------.,-------------.
                                      |      |      ||      |      |
                               ,------|------|------||------+------+------.
                               |      |      |      ||      |      |      |
                               |      |      |------||------|      |      |
                               |      |      |      ||      |      |      |
                               `--------------------'`--------------------'
*/
/*
[_BLANK] = LAYOUT_pretty (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, _______
    ),
*/



/*
Compressed pretty layout

,--------------------------------------------------------------.                      ,--------------------------------------------------------------.
|      |      |      |      |      |      |      |      |      |                      |      |      |      |      |      |      |      |      |      |
`--------------------------------------------------------------'                      `--------------------------------------------------------------'
,------------------------------------------------------.                                      ,------------------------------------------------------.
|         |        |        |        |        |        |                                      |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                      |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                      |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                      |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                      |        |        |        |        |        |         |
|---------+--------+--------+--------+--------+--------|                                      |--------+--------+--------+--------+--------+---------|
|         |        |        |        |        |        |                                      |        |        |        |        |        |         |
`---------+--------+--------+--------+--------+--------'                                      `--------+--------+--------+--------+--------+---------'
          |        |        |        |        |                                                        |        |        |        |        |
          `-----------------------------------'                                                        `-----------------------------------'
	                                                   ,-----------------.  ,-----------------.
	                                                   |        |        |  |        |        |
	                                          ,--------+--------+--------|  |--------+--------+--------.
	                                          |        |        |        |  |        |        |        |
	                                          |        |        |--------|  |--------|        |        |
	                                          |        |        |        |  |        |        |        |
	                                          `--------------------------'  `--------------------------'
*/ 

/* Archived Not Pretty Layout
[_QWERTY] = LAYOUT (
           // Left Hand
           ESC_STATUS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, TG(_FUNCTION),  TG(_VIM),
           QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
           OSM(MOD_LGUI),      LCTL_T(KC_A),    LOPT_T(KC_S),    LGUI_T(KC_D),    LSFT_T(KC_F),    KC_G,
           OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                    TD(PLEQ),  TD(MNUN), KC_LEFT, KC_RGHT,

                                              LCTL_T(KC_ESC), KC_LAPO,
                                                                G(KC_SPC),
                                              KC_BSPC, LGUI_T(KC_DEL), APP_NAV,

           // Right Hand
                    QWERTY,   KC_F10,  KC_F11,  TG(_SYMBOLS),  KC_MUTE, KC_VOLD, KC_VOLU, TG(_KEYPAD),  TG(_PROGRAM),
                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TG(_NAV),
                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
                    KC_H,    RSFT_T(KC_J),    RGUI_T(KC_K),    ROPT_T(KC_L),    RCTL_T(KC_SCLN), TD(APQU),
                    KC_N,    KC_M,    TD(CMAG), TD(PDAG),  KC_SLSH, OSM(MOD_RSFT),
                             KC_UP,   KC_DOWN, TD(LBCB), TD(RBCB),

           KC_RCPC, KC_LEAD,
           HYPR_T(KC_BSPC),
           OSM(MOD_MEH), LT(_KEYPAD, KC_ENT), RGUI_T(KC_SPC)
    ),
*/


// Triple Tap Tap Dance Function Definition


// void triple_tap_dance_pair_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {

//     qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

//     if (state->count == 3) {
//         // immediately finish on third press
//         register_code16(pair->kc2);
//         state->finished = true;
//     }
// }

// void triple_tap_dance_pair_finished(qk_tap_dance_state_t *state, void *user_data) {
//     qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

//     if (state->count == 1) {
//         register_code16(pair->kc1);
//     } else if (state->count == 2) {
//         // tap plus hold
//         tap_code16(pair->kc1);
//         register_code16(pair->kc1);
//     } else if (state->count == 3) {
//         register_code16(pair->kc2);
//     }
// }

// void triple_tap_dance_pair_reset(qk_tap_dance_state_t *state, void *user_data) {
//     qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

//     if (state->count == 1 || state->count == 2) {
//         // 1-tap and 2-tap both result in `kc1` pressed so release it
//         unregister_code16(pair->kc1);
//     } else if (state->count == 3) {
//         unregister_code16(pair->kc2);
//     }
// // }


//  #define TRIPLE_TAP_DANCE_DOUBLE(kc1, kc2) \
//          { .fn = {
//              triple_tap_dance_pair_on_each_tap, triple_tap_dance_pair_finished, triple_tap_dance_pair_reset
//              }, 
//              .user_data = (void *) & ( (qk_tap_dance_pair_t) {kc1, kc2} ), 
//          } 

// END Triple Tap Tap Dance Function Definition
