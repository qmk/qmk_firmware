# Converting a board to use the Proton C

If a board currently supported in QMK uses a Pro Micro (or compatible board) and you want to use the Proton C, you can generate the firmware by appending `CONVERT_TO_PROTON_C=yes` (or `CTPC=yes`) to your make argument, like this:

    make 40percentclub/mf68:default CTPC=yes

You can add the same argument to your keymap's `rules.mk`, which will accomplish the same thing.

This exposes the `CONVERT_TO_PROTON_C` flag that you can use in your code with `#ifdef`s, like this:

    #ifdef CONVERT_TO_PROTON_C
        // Proton C code
    #else
        // Pro Micro code
    #endif

Before being able to compile, you may get some errors about `PORTB/DDRB`, etc not being defined, so you'll need to convert the keyboard's code to use the [GPIO Controls](internals_gpio_control.md) that will work for both ARM and AVR. This shouldn't affect the AVR builds at all.

The Proton C only has one on-board LED (C13), and by default, the TXLED (D5) is mapped to it. If you want the RXLED (B0) mapped to it instead, add this like to your `config.h`:

    #define CONVERT_TO_PROTON_C_RXLED

## Feature Conversion

These are defaults based on what has been implemented for ARM boards.

| Feature                             | Notes                                                                                                            |
|-------------------------------------|------------------------------------------------------------------------------------------------------------------|
| [Audio](feature_audio.md)           | Enabled                                                                                                          |  
| [RGB Lighting](feature_rgblight.md) | Disabled                                                                                                         |
| [Backlight](feature_backlight.md)   | Forces [task driven PWM](feature_backlight.md#software-pwm-driver) until ARM can provide automatic configuration |
