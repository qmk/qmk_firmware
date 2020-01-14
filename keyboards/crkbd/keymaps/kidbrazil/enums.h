// [CRKBD Layer Colors]-------------------------------------------------------//
typedef enum{
    _GREEN = 0,
    _GOLD = 1,
    _GOLDENROD = 2,
    _RED = 3,
    _PURPLE = 4
}CRKBD_COLORS;
// [CRKBD layers Init] -------------------------------------------------------//
typedef enum {
    _QWERTY,
    _NUM,
    _SYM,
    _GAME,
    _WEAPON
}CRKBD_LAYERS;

extern enum CRKBD_COLORS crkbd_colors;
extern enum CRKBD_LAYERS crkbd_layers;
