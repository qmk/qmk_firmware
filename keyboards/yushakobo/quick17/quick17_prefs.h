enum layer_names {
    _CONTROL,
    _EDIT1,
    _EDIT2,
    _FN
};

#define _HSV(H, S, V) (HSV){ .h = H, .s = S, .v = V }
#define _RGB(rgb) rgb.r, rgb.g, rgb.b

bool input_mode(void);
void set_input_mode(bool _mode_jaen);
