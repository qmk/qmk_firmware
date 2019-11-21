#define ACTION_ENHANCED_SHIFT ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_finished,  shift_reset)

extern bool shift_holded;

void shift_reset (qk_tap_dance_state_t*, void*);
void shift_finished (qk_tap_dance_state_t*, void*);
