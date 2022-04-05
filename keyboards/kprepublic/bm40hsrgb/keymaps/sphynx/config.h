
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#undef DEBOUNCE
#define DEBOUNCE 10
#define DEBOUNCE_Type = sym_eager_pk

// #define COMBO_TERM 25
// #define COMBO_COUNT 76 // 86