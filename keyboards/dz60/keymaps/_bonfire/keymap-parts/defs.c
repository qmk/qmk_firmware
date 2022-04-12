/**
 * Variables
 * 
 */
int held_esc_threshold = 230;
bool is_esc_held = false;
uint16_t held_esc_timer = 0;

/**
 * Define Layers
 */
enum layers {
    BASE = 0,
    NRMN,
    GAME,
    FCTN,
    KEYB
};

/**
 * Define Custom Keycodes
 */
enum custom_keycodes { 
    HLD_ESC = SAFE_RANGE,
    MOD_UP = MT(MOD_RSFT, KC_UP),
    MOD_RT = MT(MOD_HYPR, KC_RIGHT),
    MOD_DN = MT(MOD_RCTL, KC_DOWN),
    MOD_LT = MT(MOD_RGUI, KC_LEFT)
};
