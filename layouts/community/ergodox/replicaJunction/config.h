#pragma once

// Do not allow one macro to contain the other macro
#define DYNAMIC_MACRO_NO_NESTING

// "THE most important tap hold configuration setting"
// https://precondition.github.io/home-row-mods#ignore-mod-tap-interrupt
// https://docs.qmk.fm/#/tap_hold?id=ignore-mod-tap-interrupt
#define IGNORE_MOD_TAP_INTERRUPT

// This one is a style choice. Play with it both on and off to see which
// one suits you better.
// https://precondition.github.io/home-row-mods#permissive-hold
// https://docs.qmk.fm/#/tap_hold?id=permissive-hold
#define PERMISSIVE_HOLD

// If you press a dual-role key for longer than TAPPING_TERM, then
// release it without pressing another key, without this setting nothing
// would happen. With this setting, it sends the key's tap function.
// https://precondition.github.io/home-row-mods#retro-tapping
#define ENABLE_RETRO_TAPPING

// Disable some unused features to save space
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

/////
// Flags for stuff in my userspace

#define USER_INCLUDE_GAMING_LAYER
#define USER_INCLUDE_MACRO_LAYER

// "Super Alt-Tab"
// https://docs.qmk.fm/#/feature_macros?id=super-alt%E2%86%AFtab
#define USER_SUPER_ALT_TAB_TIMEOUT 500
