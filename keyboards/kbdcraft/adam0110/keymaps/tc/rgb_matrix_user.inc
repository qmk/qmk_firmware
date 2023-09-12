// Copyright 2023 TC Teo (@tcteo)
// SPDX-License-Identifier: GPL-2.0-or-later

RGB_MATRIX_EFFECT(empty_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// There is a bug that causes rgb matrix values to be overwritten by the active effect. https://github.com/qmk/qmk_firmware/issues/14686
// As a workaround, define a custom effect that does nothing, preventing rgb_matrix_set_color() values from being overwritten.
// This effect is set as the init default in keymap.c.

bool empty_effect(effect_params_t* params) {
    return false;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
