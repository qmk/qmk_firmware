# Migrating Lily58 to use split_common

[#6260](https://github.com/qmk/qmk_firmware/pull/6260) Modifies the default firmware for Lily58 to use the `split_common` library, instead of including and depending on its own set of libraries for the following functionality:
- SSD1306 display
- i2c for OLED
- Serial Communication

This allows current lily58 firmware to advance with updates to the `split_common` library, which is shared with many other split keyboards.

## To migrate existing Lily58 firmware:

[Changes to `config.h`](https://github.com/qmk/qmk_firmware/pull/6260/files#diff-445ac369c8717dcd6fc6fc3630836fc1):
- Remove `#define SSD1306OLED` from config.h


[Changes to `keymap.c`](https://github.com/qmk/qmk_firmware/pull/6260/files#diff-20943ea59856e9bdf3d99ecb2eee40b7):
- Find/Replace each instance of `#ifdef SSD1306OLED` with `#ifdef OLED_DRIVER_ENABLE`
- The following changes are for compatibility with the OLED driver. If you don't use the OLED driver you may safely delete [this section](https://github.com/qmk/qmk_firmware/blob/e6b9980bd45c186f7360df68c24b6e05a80c10dc/keyboards/lily58/keymaps/default/keymap.c#L144-L190)
- Alternatively, if you did not change the OLED code from that in `default`, you may find it easier to simply copy the [relevant section](https://github.com/qmk/qmk_firmware/blob/4ac310668501ae6786c711ecc8f01f62ddaa1c0b/keyboards/lily58/keymaps/default/keymap.c#L138-L172). Otherwise, the changes you need to make are as follows (sample change [here](https://github.com/qmk/qmk_firmware/pull/6260/files#diff-20943ea59856e9bdf3d99ecb2eee40b7R138-R173))
- [Remove](https://github.com/qmk/qmk_firmware/pull/6260/files#diff-20943ea59856e9bdf3d99ecb2eee40b7L138-L141) the block
```c
#ifdef SSD1306OLED	
  iota_gfx_init(!has_usb());   // turns on the display	
#endif
```
- Within the block bounded by `#ifdef OLED_DRIVER_ENABLE` and `#endif // OLED_DRIVER_ENABLE`, add the following block to ensure that your two OLEDs are rotated correctly across the left and right sides:
```c
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}
```
- Remove the functions `matrix_scan_user`, `matrix_update` and `iota_gfx_task_user`
- Find/Replace `matrix_render_user(struct CharacterMatrix *matrix)` with `iota_gfx_task_user(void)`
- Find/Replace `is_master` with `is_keyboard_master()`
- For each instance of `matrix_write_ln(matrix, display_fn())`, rewrite it as `oled_write_ln(read_layer_state(), false);`
- For each instance of `matrix_write(matrix, read_logo());`, replace with `oled_write(read_logo(), false);`
# Refactor zinc to use split_common

[#7114](https://github.com/qmk/qmk_firmware/pull/7114)

* Refactor to use split_common and remove split codes under the zinc/revx/
* Add - backlight RGB LED and/or underglow RGB LED option
* Add - continuous RGB animations feature (between L and R halves) 
* Fix - keymap files to adapt to changes
    * all authors of keymaps confirmed this PR
* Update - documents and rules.mk

# Refactor of TKC1800 to use common OLED code

[#8472](https://github.com/qmk/qmk_firmware/pull/8472) Modifies the default firmware for TKC1800 to use the in-built I2C and OLED drivers, instead of including and depending on its own set of libraries for the following functionality:
- SSD1306 display
- i2c for OLED

This allows current TKC1800 firmware to advance with updates to those drivers, which are shared with other keyboards.

## To migrate existing TKC1800 firmware:

[Changes to `config.h`](https://github.com/qmk/qmk_firmware/pull/8472/files#diff-d10b26e676b4a55cbb00d71955116526):
- Remove `#define SSD1306OLED` from config.h

[Changes to `tkc1800.c`](https://github.com/qmk/qmk_firmware/pull/8472/files#diff-3b35bd30abe89c8110717c6972cd2cc5):
- Add the following to avoid debug errors on HID_listen if the screen is not present
```c
void keyboard_pre_init_kb(void) {
  setPinInputHigh(D0);
  setPinInputHigh(D1);

  keyboard_pre_init_user();
}
```

[Changes to `keymap.c`](https://github.com/qmk/qmk_firmware/pull/8472/files#diff-05a2a344ce27e4d045fe68520ccd4771):
- Find/Replace each instance of `#ifdef SSD1306OLED` with `#ifdef OLED_DRIVER_ENABLE`
- The following changes are for compatibility with the OLED driver. If you don't use the OLED driver you may safely delete [this section](https://github.com/qmk/qmk_firmware/blob/e6b9980bd45c186f7360df68c24b6e05a80c10dc/keyboards/lily58/keymaps/default/keymap.c#L144-L190)
- [Remove](https://github.com/qmk/qmk_firmware/pull/6260/files#diff-20943ea59856e9bdf3d99ecb2eee40b7L91-L158) the block
```c
#ifdef SSD1306OLED	
  iota_gfx_init(!has_usb());   // turns on the display	
#endif
```
- Within the block bounded by `#ifdef OLED_DRIVER_ENABLE` and `#endif // OLED_DRIVER_ENABLE`, add the following block to ensure that your two OLEDs are rotated correctly across the left and right sides:
```c
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}
```
- Remove the function `iota_gfx_task_user`