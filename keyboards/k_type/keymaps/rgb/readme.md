# K-Type RGB Matrix Keymap

This is an experimental keymap adding support for RGB Matrix on the K-Type.

The keyboard should now support full RGB lightings. The lighting animations are running at 10 fps for performance reasons.
You can configure this by changing the `RGB_MATRIX_LED_FLUSH_LIMIT` inside the `config.h` file to a lower value.
For example `RGB_MATRIX_LED_FLUSH_LIMIT 16` would mean that the animations run every 16 ms or at 60 fps.
