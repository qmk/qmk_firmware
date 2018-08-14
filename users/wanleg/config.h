#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H

#define PREVENT_STUCK_MODIFIERS

//TAPPING_TERM
#ifdef TAP_DANCE_ENABLE
#define TAPPING_TERM 200
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

#endif // !USERSPACE_CONFIG_H
