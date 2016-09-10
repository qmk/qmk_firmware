Stanley Lai's Split Right Shift with Dedicated Arrow Keys
======================

![Image of KC60 with RGB Underglow](../ws2812/ws2812_example.jpg)

## Quantum MK Firmware
For the full Quantum feature list, see [the parent readme.md](/readme.md).

## Keymap Notes
- Keymap setup with split Right Shift in mind.
- Right-side modifiers are setup as dedicated arrow keys

### Base Layer Reference
- Fn Layer indicated on keycap front legends.
- Tapping Caps Lock key toggles Caps. Holding it down momentarily switches us to the Fn Layer.
- Holding down "Fn" and "Page Down" momentarily switches us to the RGB Layer. Tapping "Page Down" behaves as expected.
![Base Layer](base_layer.jpg)

### RGB Layer Reference
![RGB Layer](rgb_layer.jpg)

## WS2812 Support
By default, it is now setup for 16 LEDs on the PF5 breakout pin. See [included image](../ws2812/ws2812_wiring.jpg) for wiring reference.

### Build
To build this keymap, simply run `make KEYMAP=stanleylai`.
