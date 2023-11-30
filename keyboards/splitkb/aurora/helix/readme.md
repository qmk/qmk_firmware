![Aurora Helix](https://i.imgur.com/zzzW8Tu.jpg)

# Aurora Helix
The Aurora Helix is a redesign by splitkb.com of the popular Helix by Yushakobo.

Keyboard Maintainer: [splitkb.com](https://github.com/splitkb)  
Hardware Supported: Pro Micro 5V/16MHz and compatible.  
Hardware Availability: [splitkb.com](https://splitkb.com).

Make example for this keyboard (after setting up your build environment):

    make splitkb/aurora/helix/rev1:default

Example of flashing this keyboard:

    make splitkb/aurora/helix/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
You can enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button on the side of the PCB, next to the TRRS socket.
* **Bootmagic reset**: Hold down the bootmagic key and plug in the keyboard. For the left half, this is the top-left button. For the right half, this is the top-right button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.

# Assembly
A build guide for the entire Aurora series is available at [https://splitkb.com/aurora-build](https://splitkb.com/aurora-build).

# Features
The Aurora Helix supports the following features:

- Support for MX or Kailh Choc switches;
- Top mounted controllers for a lower profile;
- Up to two 128×32 pixel OLED displays;
- Up to one EC11 rotary encoder per half in one of three possible positions;
- Per-key RGB backlight by individual RGB LEDs;
- Underglow by individual RGB LEDs;
- Support for a power switch for wireless controllers;
- Support for the splitkb.com tenting puck.

# What is the Aurora Series?

The Aurora series were designed as a homage to open source keyboard kits that have carved their space into the community. Kits that provided something new and unique, kits that resonated with the community and that have both received and have given a lot of love in return.

With the Aurora series, we aim to make these kits available to the community in a way that both honors the original, while also offering the best possible feature set and a consistent, well-documented build experience.

For each kit sold, we give back to the community by donating €1 across [the firmware projects we support](https://opencollective.com/splitkb). This way we support open source projects and benefit everyone using keyboards, whether they use our kits or their own.