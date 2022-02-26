# GMMK Pro Keymap (mly32)

<!-- imgur album: https://imgur.com/a/Alj4Ncr -->

## Layers

### Default Layer

![layer 0](https://i.imgur.com/3JhzMr0.png)

### Alt Layer, MO(1)

![layer 1](https://i.imgur.com/q4jGy1j.png)

### Function Layer, MO(2)

![layer 2](https://i.imgur.com/eS2cju5.png)

## Keybindings

The default rotary knob (labeled "Enc" in the figures above) acts as `MUTE` when
pressed. When turned counter-clockwise, it acts as `VOLUME DOWN`; when turned
clockwise, it acts as `VOLUME UP`.

When pressing `CONTROL` or `ALT` at the same time as turning the rotary knob,
the knob behaves like `TAB` or `SHIFT + TAB` (depending on the turning
direction). For example, pressing `CONTROL` and turning the knob
counter-clockwise will produce `CONTROL + SHIFT + TAB`.

The default layer is similar to the vanilla GMMK Pro layout, except:

- `ESCAPE` replaces the `CAPS LOCK` key;
- the key to the left of the rotary knob is `DELETE`;
- the right-most column keys are `HOME`, `PAGE UP`, `PAGE DOWN`, and `END`;
- to the right of the spacebar, there are two momentary layer keys for switching
  to layers 1 and 2.

Layer 1 acts like the default layer, except:

- the `H`, `J`, `K`, `L` keys are `LEFT`, `DOWN`, `UP`, `RIGHT` respectively
  (Vim like behavior);
- the `N`, `M`, `,`, `.` keys are `HOME`, `PAGE DOWN`, `PAGE UP`, `END`
  respectively;
- the `+`, `BACKSPACE` keys are `INSERT` `DELETE` respectively.

Layer 2 acts like the default layer, except:

- the top row (Fn keys) holds common function keys as well as the `RESET` and
  `EEPROM RESET` buttons;
- the right-most column holds RGB control keys and `CAPS LOCK`;
- the arrow key cluster holds additional RGB control keys.

## Options

This keymap turns off mouse-key support and enables via support.

## RGB

This keymap includes a custom RGB matrix effect:
`RGB_MATRIX_CUSTOM_rgb_gradient_td`. This matrix effect provides behavior like
`GRADIENT_UP_DOWN` but uses 6 (the number of rows on the GMMK Pro) discrete
colors instead of 4.

When a non-default layer (layers 1 and 2) is active, the non-default keys will
be colored differently. Usually, this color is white. If n-key rollover is off,
the keys will be colored green. If caps lock is on, the keys will be colored
blue. If both are true, the keys will be colored cyan (a mix between green and
blue color hues).
