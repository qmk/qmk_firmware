#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define DISABLE_LEADER
#define FORCE_NKRO

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT