# The default keymap for zima

This includes support for the OLED and Encoder.  However, the actual code is found in the `zima.c` file. This can be replaced by adding your own `oled_task_user(void)` and `encoder_update_user` functinons. These will replace what is in the keyboard, and allow you to customize these features. 

The reason that this is done this way, is so that this functionality will work on the [QMK Configurator](https://config.qmk.fm/#/splitkb/zima/LAYOUT_ortho_4x3)

For reference, the code used for the oled and encoder defaults is in [zima.c](https://github.com/qmk/qmk_firmware/tree/master/keyboards/splitkb/zima/zima.c).
