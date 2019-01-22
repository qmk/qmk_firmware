// Keycode aliases
#define SCTL(kc)   LSFT(LCTL(kc))  // Modifier keys: SHIFT+CTRL+kc combination.
#define LGAS_T(kc) MT(MOD_LGUI | MOD_LALT | MOD_LSFT, kc)  // Mod tap: kc when tapped, GUI+ALT+SHIFT when held.
#define LAS_T(kc)  MT(MOD_LALT | MOD_LSFT, kc)  // Mod tap: kc when tapped, ALT+SHIFT whin held.
#define COMPOSE    KC_RALT  // Compose key (used to input characters like á, ñ, ü).
