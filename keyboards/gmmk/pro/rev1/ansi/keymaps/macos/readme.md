# GMMK Pro Standard Layout for macOS by zvuc

As you may know, Glorious does not (yet) provide their Glorious Core software for macOS; so with stock firmware, there aren't any ways to customize layouts on the hardware level unless you turn to software-based override solutions such as [Karabiner Elements](https://karabiner-elements.pqrs.org/). This is my attempt to try to create the most macOS-like experience on the GMMK Pro, taking close notes from Apple's Magic Keyboard, also referencing code from other community keymaps.

## Keymap
Layer 0
<img width="1092" alt="Layer0" src="https://user-images.githubusercontent.com/2870726/132235505-64ac1c89-ecf9-49b5-a030-1d94389fc66d.png">

Layer 1 (Hold <kbd>Fn</kbd>)
<img width="1088" alt="Layer1" src="https://user-images.githubusercontent.com/2870726/133090831-5e84fb69-a8bf-463e-a8f6-f1f38a5901d6.png">

Layer 2 (Togglable alternative function row layout by pressing <kbd>Fn</kbd>+<kbd>F</kbd>)
<img width="1094" alt="Layer2" src="https://user-images.githubusercontent.com/2870726/133090841-0c6a8b16-bf46-4e6c-b8fa-79f213f95765.png">


## Notable differences from stock key layout for Windows:
- <kbd>Delete</kbd> key placed right next to backspace (under rotary encoder)
- <kbd>F13</kbd> key for the bottommost row (Assign it to a shortcut you like in macOS preferences! [For example: "Emoji & Symbols" to bring up the emoji input popup instantly](https://user-images.githubusercontent.com/2870726/132237211-7e13c156-96a8-4a91-b215-28d310228feb.png))
- <kbd>Eject</kbd> key for the last key in function row: Needed for macOS native global "Sleep" hotkey (<kbd>⌘</kbd><kbd>⌥</kbd><kbd>Eject</kbd>)

## Notable Features
- VIA support
- Rotary Encoder support (Defaults to stock behavior Volume Up/Down)
- Standard order for macOS modifier keys: 
    * Left: <kbd>⌃ Control</kbd><kbd>⌥ Option</kbd><kbd>⌘ Command</kbd> 
    * Right: <kbd>⌘ Command</kbd><kbd>⌥ Option</kbd><kbd>Fn</kbd>
- Apple Magic Keyboard-like Function Row Mode (Toggle with <kbd>Fn</kbd>+<kbd>F</kbd>)
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

> #### NOTE
> - Media key mappings follow Apple Magic Keyboard except <kbd>F8</kbd> thru <kbd>F12</kbd>, where keys have been shifted by one to the right. It's because I wanted to get over the awkward gap between <kbd>F8</kbd> and <kbd>F9</kbd> that the GMMK Pro has—and also because we don't need dedicated keys for volume control when we have the more convenient rotary knob.
> - To access standard <kbd>F1</kbd> - <kbd>F12</kbd> keys, press the Function keys while holding <kbd>Fn</kbd>.
> - If you're planning to use Karabiner Elements, use the standard Function row mode (<kbd>F1</kbd> - <kbd>F12</kbd>) because Karabiner Elements always overrides function keys even if you want to just use simple or complex modifications, and it doesn't catch custom keys like Mission Control, Launchpad or <kbd>Eject</kbd>. (<kbd>Eject</kbd> is mapped as <kbd>F24</kbd> so you can replace it with 'Eject' within Karabiner.)

## RGB Lighting
- Retains Glorious stock firmware key mappings for control
    * <kbd>Fn</kbd><kbd>Up</kbd> / <kbd>Fn</kbd><kbd>Down</kbd>: Cycle presets
    * <kbd>Fn</kbd><kbd>Left</kbd> / <kbd>Fn</kbd><kbd>Right</kbd>: Adjust speed
    * <kbd>Fn</kbd><kbd>W</kbd> / <kbd>Fn</kbd><kbd>S</kbd>: Adjust brightness
- Quickly switch to popular presets:
    * <kbd>Fn</kbd><kbd>`</kbd> : Solid color (no animation)
    * <kbd>Fn</kbd><kbd>1</kbd> : Solid duotone (no animation) - <kbd>Shift</kbd><kbd>Knob</kbd> to change secondary color.
    * <kbd>Fn</kbd><kbd>2</kbd> : Vertical gradient - <kbd>Shift</kbd><kbd>Knob</kbd> to change secondary color.
    * <kbd>Fn</kbd><kbd>3</kbd> : "Jellybean Raindrops"
    * <kbd>Fn</kbd><kbd>4</kbd> : Horizontal wipe with white backlight
    * <kbd>Fn</kbd><kbd>5</kbd> : Horizontal wipe
    * <kbd>Fn</kbd><kbd>6</kbd> : Single color pinwheel
    * <kbd>Fn</kbd><kbd>7</kbd> : Horizontal rainbow
    * <kbd>Fn</kbd><kbd>8</kbd> : Rainbow pinwheel
    * <kbd>Fn</kbd><kbd>9</kbd> : Breathing
    * <kbd>Fn</kbd><kbd>0</kbd> : Reactive (light up on keypress)
    * <kbd>Fn</kbd><kbd>-</kbd> : "Digital Rain"
    * <kbd>Fn</kbd><kbd>=</kbd> : "Heatmap"
- RGB turns off after 20 minutes of inactivity
- RGB turns off when USB is suspended / enters sleep
- <kbd>Caps Lock</kbd> toggle indicator (<kbd>Caps Lock</kbd> key and side lights will turn red)
- Easy RGB control using Rotary Encoder
    - <kbd>Control</kbd>+<kbd>Rotate Knob</kbd>: Adjust hue
    - <kbd>Option</kbd>+<kbd>Rotate Knob</kbd>: Adjust saturation
    - <kbd>Command</kbd>+<kbd>Rotate Knob</kbd>: Adjust brightness

> All latest QMK effects [(41 as of now)](https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgb_matrix#rgb-matrix-effects-id-rgb-matrix-effects) are enabled by default and will apply in order when cycling through using <kbd>Fn</kbd><kbd>Up</kbd> / <kbd>Fn</kbd><kbd>Down</kbd>. You can disable specific effects by uncommenting (remove the `//` at the beginning of line) respective lines (ex: `#define DISABLE_RGB_MATRIX_BREATHING`) in `qmk_firmware/keyboards/gmmk/pro/ansi/keymaps/zvuc/config.h` then recompiling the firmware.

## Other Features
- 1000hz polling rate
- Short DEBOUNCE time (5 ms)
- Per-key debounce algorithm (`sym_defer_pk`)
- NKRO toggle (<kbd>Fn</kbd>+<kbd>N</kbd>)

## Warning regarding VIA support
When observing this keyboard firmware in VIA, some custom-implemented keys such as Mission Control/Launchpad and RGB preset shortcuts appear as keycodes such as `0x5d62`. **These must not be modified!** There is no way to get their default functionality back unless you re-flash the firmware through QMK Toolbox.

## Download pre-compiled firmware binary file
[Download BIN file from here](https://github.com/zvuc/qmk_firmware/releases/tag/zvuc-1.0.1)
