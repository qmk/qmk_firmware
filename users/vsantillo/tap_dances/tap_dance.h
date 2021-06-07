// Tap - manage a key's state
typedef struct {
    uint8_t state;
    uint8_t count;
} tap;

// Tap States
enum {
    SINGLE_TAP = 1, // 1 Tap
    SINGLE_HOLD,    // 1 Hold
    SINGLE_TAP_INT, // 1 interrupted Tap (e.g. Shift + key)
    DOUBLE_TAP,     // 2 Taps
    DOUBLE_HOLD,    // 1 Tap + 1 Hold
    DOUBLE_TAP_INT, // 2 interrupted Tap (e.g. pe'pp'er)
    TRIPLE_TAP,     // 3 Taps
    TRIPLE_HOLD,    // 2 Taps + 1 Hold
    QUAD_TAP,       // 4 Taps
    QUAD_HOLD,      // 3 Taps + 1 Hold;
};
