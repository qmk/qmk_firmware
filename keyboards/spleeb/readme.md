# spleeb

![spleeb](https://i.imgur.com/2rmZa6Mh.jpg)

A 5x7 split keyboard that has support for rotary encoders, an oled and a Ciruqe touchpad

* Keyboard Maintainer: [Chris Hoage](https://github.com/chrishoage)
* Hardware Supported: Spleeb PCB with a rp2040 MCU (Blok, Elite Pi, etc)
* Hardware Availability: [https://github.com/chrishoage/spleeb](https://github.com/chrishoage/spleeb)

Make example for this keyboard (after setting up your build environment):

    make spleeb:default

Flashing example for this keyboard:

    make spleeb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Encoder Mode Map

Spleeb firmware has support for an encoder mode map similar to the native encoder map in QMK. The difference is the encoder mode map allows one to change behavior or the encoders independently of the layers. In your keymap.c file you can include something the following:

```c
enum spleeb_enc_mode {
    DEF_DPI,
    SNP_DPI,
    VOL,
    SEL,
};

void spleeb_encoder_mode_trigger(uint8_t mode, bool clockwise) {
    dprintf("spleeb_encoder_mode_trigger m: %u, c: %u\n", mode, clockwise);
    switch (mode) {
        case DEF_DPI:
            spleeb_cycle_pointer_default_dpi(clockwise);
            break;
        case SNP_DPI:
            spleeb_cycle_pointer_sniping_dpi(clockwise);
            break;
        case VOL:
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
            break;
        case SEL:
            bool     is_shift = get_mods() & MOD_MASK_SHIFT;
            uint16_t dir      = clockwise ? KC_RIGHT : KC_LEFT;
            if (is_shift) {
                tap_code(dir);
            } else {
                tap_code16(LSFT(LCTL(dir)));
            }

        default:
            break;
    }
}

const char *spleeb_encoder_mode_string(uint8_t mode) {
    switch (mode) {
        case DEF_DPI:
            return "df dpi";
        case SNP_DPI:
            return "sn dpi";
        case VOL:
            return "volume";
        case SEL:
            return "select";
    }

    return get_u8_str(mode, ' ');
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
}

const spleeb_enc_mode_t spleeb_encoder_mode_map[NUM_ENCODERS][SPLEEB_ENCODER_MODE_COUNT] = {
    [0] = {SPLEEB_ENC_MODE(VOL), SPLEEB_ENC_MODE(SEL)},
    [1] = {SPLEEB_ENC_MODE(DEF_DPI), SPLEEB_ENC_MODE(SNP_DPI), SPLEEB_ENC_MODE(SEL)},
};
```

This will enable 4 encoder modes. On the left side there will be modes for volume control and text selection. On the right side there will be three modes to allow controlling the DPI of the Cirque trackpad and also text selection. 

## Custom Keycodes 

This firmware defines the following custom keycodes for use in keymap.c. Depending on your defines the pointing or encoder specific keymaps will not be included.

```c
#define DF_MOD POINTER_DEFAULT_DPI_FORWARD
#define DF_RMOD POINTER_DEFAULT_DPI_REVERSE
#define SP_MOD POINTER_SNIPING_DPI_FORWARD
#define SP_RMOD POINTER_SNIPING_DPI_REVERSE
#define SNIPING SNIPING_MODE
#define SNP_TOG SNIPING_MODE_TOGGLE
#define DRGSCRL DRAGSCROLL_MODE
#define DRG_TOG DRAGSCROLL_MODE_TOGGLE
#define ENC_STL ENC_MODE_STEP_LEFT
#define ENC_STR ENC_MODE_STEP_RIGHT
```

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
