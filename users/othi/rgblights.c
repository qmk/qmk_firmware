uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case NM_MODE:
        rgblight_setrgb (0x00,  0x66, 0x00);
        break;
    case VI_MODE:
        rgblight_setrgb (0x66,  0x66, 0x00);
        break;
    case ACCENT:
        rgblight_setrgb (0x7A,  0x00, 0xFF);
        break;
    case ACCENT_CAP:
        rgblight_setrgb (0x7A,  0xFF, 0xFF);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0x00,  0x00, 0xFF);
        break;
    }
  return state;
}
