# GMMK Pro Standard Layout for macOS by zvuc

As you may know, Glorious does not (yet) provide their Glorious Core software for macOS; so with stock firmware, there aren't any ways to customize layouts on the hardware level unless you turn to software-based override solutions such as [Karabiner Elements](https://karabiner-elements.pqrs.org/). This is my attempt to try to create the most macOS-like experience on the GMMK Pro, taking close notes from Apple's Magic Keyboard, also referencing code from other community keymaps.

## Keymap
<img width="1092" alt="image" src="https://user-images.githubusercontent.com/2870726/132235505-64ac1c89-ecf9-49b5-a030-1d94389fc66d.png">
<img width="1091" alt="image" src="https://user-images.githubusercontent.com/2870726/132235558-e7a2e6c7-9ed8-4917-9345-43181b3e7c7c.png">

## Notable differences from stock key layout for Windows:
- <kbd>Delete</kbd> key placed right next to backspace (under rotary encoder)
- <kbd>F13</kbd> key for the bottommost row (Assign it to a shortcut you like in macOS preferences! [For example: "Emoji & Symbols" to bring up the emoji input popup instantly](https://user-images.githubusercontent.com/2870726/132237211-7e13c156-96a8-4a91-b215-28d310228feb.png))
- <kbd>Eject</kbd> key for the last key in function row: Needed for macOS native global "Sleep" hotkey (Cmd+Option+Eject)

## Notable Features
- VIA support
- Rotary Encoder support (Defaults to stock behavior Volume Up/Down)
- Standard order for macOS modifier keys: 
    * Left: <kbd>⌃ Control</kbd><kbd>⌥ Option</kbd><kbd>⌘ Command</kbd> 
    * Right: <kbd>⌘ Command</kbd><kbd>⌥ Option</kbd><kbd>Fn</kbd>
- Apple Magic Keyboard-like Function key row
    * <kbd>F1</kbd>: Decrease display brightness
    * <kbd>F2</kbd>: Increase display brightness
    * <kbd>F3</kbd>: Mission Control
    * <kbd>F4</kbd>: Launchpad
    * <kbd>F5</kbd>: Decrease keyboard backlight brightness
    * <kbd>F6</kbd>: Increase keyboard backlight brightness
    * <kbd>F7</kbd>: (none)
    * <kbd>F8</kbd>: (none)
    * <kbd>F9</kbd>: Media Rewind 
    * <kbd>F10</kbd>: Media Play/Pause
    * <kbd>F11</kbd>: Media Fast Forward
    * <kbd>F12</kbd>: (none)
> Note: 
> - Media key positions have been rearranged slightly due to GMMK Pro having a gap inbetween <kbd>F8</kbd> and <kbd>F9</kbd> keys, and because we don't need dedicated keys for volume control when we have the rotary knob.
> - To access standard <kbd>F1</kbd>-<kbd>F12</kbd> keys, press the Function keys while holding <kbd>Fn</kbd>.

## RGB Lighting 
- Retains Glorious stock firmware key mappings for control
    * <kbd>Fn</kbd>+<kbd>Up</kbd>/<kbd>Down</kbd>: Cycle presets
    * <kbd>Fn</kbd>+<kbd>Left</kbd>/<kbd>Right</kbd>: Adjust speed
    * <kbd>Fn</kbd>+<kbd>W</kbd>/<kbd>S</kbd>: Adjust brightness
- Quickly switch to popular presets using <kbd>Fn</kbd>+ number row keys (From <kbd>`</kbd> thru <kbd>=</kbd>)
- RGB turns off after 20 minutes of inactivity
- RGB turns off when USB is suspended / enters sleep
- <kbd>Caps Lock</kbd> toggle indicator (<kbd>Caps Lock</kbd> key and side lights will turn red)
- Easy RGB control using Rotary Encoder
    - <kbd>Control</kbd>+<kbd>Rotate Knob</kbd>: Adjust hue
    - <kbd>Option</kbd>+<kbd>Rotate Knob</kbd>: Adjust saturation
    - <kbd>Command</kbd>+<kbd>Rotate Knob</kbd>: Adjust brightness

> All 41 effects enabled by default. You can disable specific effects by uncommenting (remove the `//` at the beginning of line) respective lines (ex: `#define DISABLE_RGB_MATRIX_BREATHING`) in `qmk_firmware/keyboards/gmmk/pro/ansi/keymaps/zvuc/config.h` then recompiling the firmware.

## Other Features
- 1000hz polling rate
- Short DEBOUNCE time (5 ms)
- Per-key debounce algorithm (`sym_defer_pk`)
- NKRO toggle (Fn+N)

## Warning regarding VIA support
When observing this keyboard firmware in VIA, some custom-implemented keys such as Mission Control/Launchpad and RGB preset shortcuts appear as keycodes such as `0x5d62`. **These must not be modified!** There is no way to get their default functionality back unless you re-flash the firmware through QMK Toolbox.

## Download pre-compiled firmware binary file
[Download BIN file from here](https://github.com/zvuc/qmk_firmware/releases/tag/zvuc-1.0.0)
