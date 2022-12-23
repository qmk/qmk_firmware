# The default keymap for NK87

![Layer 0](https://i.imgur.com/RQvNaqq.png)
Fn Layer:
![Layer 1](https://i.imgur.com/5mKCvRb.png)

Default layer is normal ANSI TKL

This keymap uses  [RGB Matrix Lighting](https://github.com/samhocevar-forks/qmk-firmware/blob/master/docs/feature_rgb_matrix.md)
by default. VIA is not supporting configuration of RGB Matrix Lighting effects but there are still options to do the effects configurations:
- Use `Layer 1` keycodes
- Create new keymap and set defaults using following options set at `config.h`:
    - RGB_MATRIX_DEFAULT_MODE
    - RGB_MATRIX_DEFAULT_HUE
    - RGB_MATRIX_DEFAULT_SAT
    - RGB_MATRIX_DEFAULT_SPD
    - RGB_MATRIX_DEFAULT_VAL
- Use `via` keymap where RGB Matrix Lighting replaced with RGB Backlight (RGB Backlight has less effects implemented than RGB Matrix Lighting)