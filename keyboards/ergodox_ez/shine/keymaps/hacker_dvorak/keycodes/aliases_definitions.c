// Compound keycode aliases
#define SCTL(kc)   LSFT(LCTL(kc))  // Modifier keys: SHIFT+CTRL+kc combination.

// Tap
#define LASG_T(kc) MT(MOD_LGUI | MOD_LALT | MOD_LSFT, kc)  // Mod tap: kc when tapped, GUI+ALT+SHIFT when held.
#define LCSG_T(kc) MT(MOD_LGUI | MOD_LSFT | MOD_LCTL, kc)  // Mod tap: kc when tapped, GUI+CTL+SHIFT when held.

#define LCG_T(kc)  MT(MOD_LCTL | MOD_LGUI, kc)  // Mod tap: kc when tapped, CTL+GUI when held.
#define LAS_T(kc)  MT(MOD_LALT | MOD_LSFT, kc)  // Mod tap: kc when tapped, ALT+SHIFT when held.
#define LAG_T(kc)  MT(MOD_LALT | MOD_LGUI, kc)  // Mod tap: kc when tapped, ALT+GUI when held.

// Others
#define COMPOSE    KC_RALT  // Compose key (used to input characters like á, ñ, ü).
