// [CRKBD layers Init] -------------------------------------------------------//
typedef enum {
    _NEO = 0,
    _NUM = 1,
    _SYM = 2,
    _GAME = 3,
    _WEAPON,
    _ADJ
}CRKBD_LAYERS;

enum custom_keycodes {
    HIBER = 0
};
extern enum CRKBD_LAYERS crkbd_layers;
