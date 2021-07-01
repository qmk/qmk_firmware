enum layer_names {
    _CONTROL,
    _EDIT1,
    _EDIT2,
    _FN
};

#define _HSV(H, S, V) (HSV){ .h = H, .s = S, .v = V }
#define _RGB(rgb) rgb.r, rgb.g, rgb.b

enum _mode_ja {
    _INPUT_JP = 0,
    _INPUT_EN
};

static uint8_t INPUT_MODE;
