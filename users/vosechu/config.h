#pragma once

#undef PERMISSIVE_HOLD
//#define QUICK_TAP_TERM 0
//#define RETRO_TAPPING

#ifndef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2
#endif

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 150

// Disable action_get_macro and fn_actions, since we don't use these
// and it saves on space in the firmware.
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
