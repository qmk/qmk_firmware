enum layer_names {
    _CONTROL,
    _EDIT1,
    _EDIT2,
    _FN
};

//static bool layer_shift = false;
#define _HSV(H, S, V) (HSV){ .h = H, .s = S, .v = V }
#define _RGB(rgb) rgb.r, rgb.g, rgb.b