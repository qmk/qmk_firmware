# Kemove DK61 Snowfox / Shadow

![Kemove DK61 Snowfox v1.5 PCB](https://raw.githubusercontent.com/milouk/kemove-dk61-qmk/2ba0fdc7fb71eb5bf5812d947b367af0bfd8affd/docs/images/board.jpg)

A 61 key hotswap keyboard with USB and Bluetooth. This is the first generation, sold as "Turing Gaming Keyboard" with USB ID `1EA7:9005` (Snowfox) or `1EA7:9006` (Shadow). Later DK61 boards use a Sonix MCU and are not supported here.

* Keyboard Maintainer: [Michael Loukeris](https://github.com/milouk)
* Hardware Supported: Kemove DK61 Snowfox and Shadow, PCB v1.5 (NXP LPC11U35, CYW20730 Bluetooth module, 2x SLED1734x)
* Hardware Availability: [Kemove](https://www.kemove.com/)

Make example for this keyboard (after setting up your build environment):

    make kemove/snowfox/v1_5:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The firmware is linked at `0x2000` and needs the [OpenKemove DFU bootloader](https://github.com/OpenKemove/kemove_lpc_dfu) in place of the stock one. Installing it and flashing are described at <https://github.com/milouk/kemove-dk61-qmk>.

Enter the bootloader in 3 ways:

* **Physical key**: hold Esc while plugging in the keyboard
* **Keycode in layout**: press the key mapped to `QK_BOOT`, Fn+B in the default keymap
* **VIA**: Enter update mode on the Kemove page

## Keys

The default keymap follows the stock layout and Fn shortcuts.

| Keys | Function |
| --- | --- |
| Fn+1 to Fn+=, Fn+Esc | F1 to F12, \` |
| Fn+U, I, O | Print Screen, Scroll Lock, Pause |
| Fn+J, K, L, M, comma, period | Insert, Home, Page Up, Delete, End, Page Down |
| Fn+/, Right Alt, Menu, Right Ctrl | Arrows |
| Fn+A, S, D, F, G, H | Play, previous, next, mute, volume down, volume up |
| Fn+Backspace | Lighting on or off |
| Fn+\, Fn+] | Next, previous lighting effect |
| Fn+P, Fn+[ | Brightness down, up |
| Fn+;, Fn+' | Effect speed down, up |
| Fn+Caps Lock | Change colour |
| Fn+Q, W, E, R, T | Profile 1 to 4, profile 0 |
| Fn+Z, X, C | Bluetooth host 1 to 3. Hold 3 seconds to pair |
| Fn+Right Shift (hold) | Battery level |
| Fn+Space | Lock the F keys on the number row |
| Fn+Win | Lock the Win key |
| Fn+Tab (hold 3 seconds) | Reset all settings |
| Fn+B | Bootloader |

Battery, reset, profile, Fn lock and Bluetooth host keys are also custom keycodes in VIA.

## Profiles

Profiles 1 to 4 are layers over the base layer, empty in the default keymap. Fill in only the keys that should differ, in VIA or in a keymap. Profile 0 is the base layer alone. Each profile remembers its own lighting, and switching flashes the keyboard in the profile's colour: white, red, green, blue, yellow for 0 to 4.

## Switch on the back

By default it selects the Windows or Mac base layer. It can instead be set to pick the layout from the computer seen over USB, with the switch in its Mac position then locking the Win key or the F keys.

## Lighting

QMK's RGB Matrix effects, plus a typing speed effect that goes from dim blue to bright red as you type faster.

| Indicator | Meaning |
| --- | --- |
| Caps Lock red | Caps Lock on |
| Win/Cmd keys blinking red | Win lock on: those keys are disabled |
| Fn key blinking red | Fn lock on: F1 to F12 on the number row |
| Z, X or C blinking cyan | Pairing that host |
| Z, X or C blinking purple | Reconnecting to that host |
| Z, X or C blue for 3 seconds | Connected |
| Only Fn keys lit | Fn held |
| Number row | Battery level while Fn+Right Shift is held: one key per 10%, red to 20%, yellow to 50%, then green |

## Bluetooth

Three hosts. The keyboard reconnects to the last one at power up, and again after a dropped link, retrying for about 7 minutes. Over USB it uses NKRO, over Bluetooth 6KRO.

## Battery

On battery the lights turn off after 3 minutes without typing and come back with the next key press. Between key presses the firmware pauses, so the chip idles while you are not typing.

## VIA

The VIA keymap adds a Kemove page:

| Setting | Options |
| --- | --- |
| Battery | Level, read from the keyboard |
| Lights off on battery after | Off, 1, 3, 5 or 10 minutes |
| Bluetooth | Status, connect or pair host 1 to 3, disconnect |
| Profile | 0 to 4 |
| Reset current profile | Default lighting, and no key changes on profiles 1 to 4 |
| Back switch | Windows or Mac layout, or automatic with the switch locking the Win key or the F keys |
| Enter update mode | Bootloader |
| Reset all settings | Factory reset |
