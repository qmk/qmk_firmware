# NyxKeys Hermes

![NyxKeys Hermes](https://imagedelivery.net/5Lj-4KVs36OWCtiVSZ4L1Q/bd9b4a5e-22b9-4ca1-54c0-a578e045a000/public)

The Hermes is a 24-key numpad featuring a dedicated function row (F1–F4), a standard numpad layout with tall Plus and Enter keys, and a utility column on the right side. Designed and produced by NyxKeys.

- Keyboard Maintainer: [Shiva1796](https://github.com/Shiva1796)
- Hardware Supported: STM32F072-based PCB
- Hardware Availability: [nyxkeys.com](https://nyxkeys.com)

Make example for this keyboard (after setting up your build environment):

    make nyxkeys/hermes:default

Flashing example for this keyboard:

    make nyxkeys/hermes:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold the F1 key (top-left, matrix position 0,0) while plugging in the keyboard
- **Physical reset button**: Briefly press the button on the back of the PCB
- **Keycode in layout**: Hold the Fn key (NumLock position) and press Backspace
