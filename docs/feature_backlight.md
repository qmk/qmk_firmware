# Backlighting

<!-- FIXME: Describe how backlighting works in QMK -->

## Backlight Keycodes

These keycodes control the backlight. Most keyboards use this for single color in-switch lighting.

|Key      |Description                               |
|---------|------------------------------------------|
|`BL_TOGG`|Turn the backlight on or off              |
|`BL_STEP`|Cycle through backlight levels            |
|`BL_ON`  |Set the backlight to max brightness       |
|`BL_OFF` |Turn the backlight off                    |
|`BL_INC` |Increase the backlight level              |
|`BL_DEC` |Decrease the backlight level              |
|`BL_BRTG`|Toggle backlight breathing                |

Note that for backlight breathing, you need to have `#define BACKLIGHT_BREATHING` in your config.h.

## Configuration Options in `config.h`

* `BACKLIGHT_PIN B7` defines the pin that controlls the LEDs. Unless you design your own keyboard, you don't need to set this.
* `BACKLIGHT_LEVELS 3` defines the number of brightness levels (maximum 15 excluding off).
* `BACKLIGHT_BREATHING` if defined, enables backlight breathing. Note that this is only available if `BACKLIGHT_PIN` is B5, B6 or B7.
* `BREATHING_PERIOD 6` defines the length of one backlight "breath" in seconds.

## Notes on Implementation

To change the brightness when using pins B5, B6 or B7, the PWM (Pulse Width Modulation) functionality of the on-chip timer is used.
The timer is a counter that counts up to a certain TOP value (`0xFFFF` set in ICR1) before resetting to 0.
We also set an OCR1x register.
When the counter reaches the value stored in that register, the PWM pin drops to low.
The PWM pin is pulled high again when the counter resets to 0.
Therefore, OCR1x basically sets the duty cycle of the LEDs and as such the brightness where `0` is the darkest and `0xFFFF` the brightest setting.

To enable the breathing effect, we register an interrupt handler to be called whenever the counter resets (with `ISR(TIMER1_OVF_vect)`).
In this handler, which gets called roughly 244 times per second, we compute the desired brightness using a precomputed brightness curve.
To disable breathing, we can just disable the respective interrupt vector and reset the brightness to the desired level.
