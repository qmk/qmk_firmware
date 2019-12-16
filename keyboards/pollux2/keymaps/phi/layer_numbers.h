enum layer_number {
    BASE = 0,
    RAISE,
    FUNCTION,
    MOUSE,
    WHEEL,
    CURSOR,
    CURSOR_ACCL,
    MICROWRITER
};

#define LAYER_ON(n) (layer_state & (2 << ((n) - 1)))
