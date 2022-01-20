typedef struct {
    bool is_press_action;
    int state;
} tap;

enum {
    SINGLE_TAP        = 1,
    SINGLE_HOLD       = 2,
    DOUBLE_TAP        = 3,
    DOUBLE_HOLD       = 4,
    DOUBLE_SINGLE_TAP = 5,  // Send two single taps.
    TRIPLE_TAP        = 6,
    TRIPLE_HOLD       = 7,
    TRIPLE_SINGLE_TAP = 8   // Send three single taps.
};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int current_dance(qk_tap_dance_state_t *state) {
    int current_state = 0;
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            current_state = SINGLE_TAP;
        } else {
            current_state = SINGLE_HOLD; //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        }
    } else if (state->count == 2) {
        /*
         * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
        */
        if (state->interrupted) {
            current_state = DOUBLE_SINGLE_TAP;
        } else if (state->pressed) {
            current_state = DOUBLE_HOLD;
        } else {
            current_state = DOUBLE_TAP;
        }
    } else if (state->count == 3) {
        if (state->interrupted) {
            current_state = TRIPLE_SINGLE_TAP;
        } else if (state->pressed) {
            current_state = TRIPLE_HOLD;
        } else {
            current_state = TRIPLE_TAP;
        }
    }
    return current_state;
}
