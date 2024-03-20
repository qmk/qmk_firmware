// Keymap helpers
// define reference layers per layer.
#define REF_LAYER_FOR_LAYER(LAYER, REF_LAYER)   \
  case LAYER: return REF_LAYER;

#define DEF_REF_LAYER(LAYER)                    \
  default: return LAYER;

#define K_ENUM(name, key, ...) name,
#define K_DATA(name, key, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#define K_COMB(name, key, ...) [name] = COMBO(cmb_##name, key),

#define A_ENUM(name, string, ...) name,
#define A_DATA(name, string, ...) const uint16_t PROGMEM cmb_##name[] = {__VA_ARGS__, COMBO_END};
#define A_COMB(name, string, ...) [name] = COMBO_ACTION(cmb_##name),
#define A_ACTI(name, string, ...)               \
    case name:                                  \
        if (pressed) SEND_STRING(string);           \
        break;

#define A_TOGG(name, layer, ...)                \
    case name:                                    \
        if (pressed) layer_invert(layer);             \
        break;

#define BLANK(...)
#undef COMBO_REF_LAYER
#undef DEFAULT_REF_LAYER
#define COMBO_REF_LAYER BLANK
#define DEFAULT_REF_LAYER BLANK

// Generate data needed for combos/actions
// Create Enum
#undef COMB
#undef SUBS
#undef TOGG
#define COMB K_ENUM
#define SUBS A_ENUM
#define TOGG A_ENUM
enum combos {
#include "combos.def"
    COMBO_LENGTH
};
// Export length to combo module
uint16_t COMBO_LEN = COMBO_LENGTH;

// Bake combos into mem
#undef COMB
#undef SUBS
#undef TOGG
#define COMB K_DATA
#define SUBS A_DATA
#define TOGG A_DATA
#include "combos.def"
#undef COMB
#undef SUBS
#undef TOGG

// Fill combo array
#define COMB K_COMB
#define SUBS A_COMB
#define TOGG A_COMB
combo_t key_combos[] = {
#include "combos.def"
};
#undef COMB
#undef SUBS
#undef TOGG

// Fill QMK hook
#define COMB BLANK
#define SUBS A_ACTI
#define TOGG A_TOGG
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
#include "combos.def"
    }

    // Allow user overrides per keymap
#if __has_include("inject.h")
# include "inject.h"
#endif
}
#undef COMB
#undef SUBS
#undef TOGG

// Allow reference layers per layer.
#define COMB BLANK
#define SUBS BLANK
#define TOGG BLANK

#undef DEFAULT_REF_LAYER
#undef COMBO_REF_LAYER
#define COMBO_REF_LAYER REF_LAYER_FOR_LAYER
#define DEFAULT_REF_LAYER DEF_REF_LAYER

uint8_t combo_ref_from_layer(uint8_t current_layer){
  switch (current_layer){
#include "combos.def"
  }
  return current_layer;
}

#undef COMB
#undef SUBS
#undef TOGG
#undef COMBO_REF_LAYER
#undef DEFAULT_REF_LAYER
