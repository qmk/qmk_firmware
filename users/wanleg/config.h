#pragma once

//TAPPING_TERM
//tapping term short (<100): on multi-purpose keys, slow taps may not register, but "holds" register easier. multi-tap keys may be difficult to activate.
//tapping term long (>200): holds don't register as easily - noticeable when typing quickly (e.g. shift doesn't want to engage.)


//MIGHT HAVE TO SPLIT THIS INTO TWO CONDITIONS
#if defined(TAP_DANCE_ENABLE) && defined(KEYBOARD_lets_split_rev2) || defined(KEYBOARD_iris_rev2)
//Kailh Coppers activate quickly and don't need a long tapping term
#define TAPPING_TERM 100

#elif defined(TAP_DANCE_ENABLE) && defined(KEYBOARD_bigswitch)
#define TAPPING_TERM 700

#else
#define TAPPING_TERM 145
#endif

//Mousekey Settings
#ifdef MOUSEKEY_ENABLE
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0
#endif

// Disable action_get_macro and fn_actions, since we don't use these
// and it saves on space in the firmware.
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT

// Disable mod tap interrrupt
#ifndef IGNORE_MOD_TAP_INTERRUPT
#define IGNORE_MOD_TAP_INTERRUPT
#endif // !mod tap interrrupt