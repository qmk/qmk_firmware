// [CRKBD layers Init] -------------------------------------------------------//
typedef enum {
    _NEO,
    _NUM,
    _SYM,
    _GAME,
    _WEAPON,
    _ADJ
}CRKBD_LAYERS;

enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
    HIBER = 0
};
extern enum CRKBD_LAYERS crkbd_layers;
