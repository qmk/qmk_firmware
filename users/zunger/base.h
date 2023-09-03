#ifndef USERS_ZUNGER_BASE_H__
#define USERS_ZUNGER_BASE_H__

// Return values for process_* functions, because I get this wrong without macros
#define FALLTHROUGH true
#define STOP false

#define IS_SHIFTED (get_mods() & MOD_MASK_SHIFT)

#endif  // USERS_ZUNGER_BASE_H__
