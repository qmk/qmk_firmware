# OWS

Open-source steno keyboard with a pseudo-split layout, designed to be compact, portable, and cost-effective.

![OWS](https://i.imgur.com/OKkenaR.jpeg "OWS v1 prototype")

* Keyboard maintainer: [ivndbt](https://github.com/ivndbt)
* Hardware supported: Pro Micro RP2040
* Hardware Availability: OWS is open-source, check the [project repository](https://github.com/ivndbt/obiwanstenobit)

Make example for this keyboard (after setting up your build environment):

    make ivndbt/ows:default

Flashing example for this keyboard:

    make ivndbt/ows:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

1. There are 4 ways to enter the bootloader:

    * **Physical reset button**: Double tap the `RST` button located on the back of the Controller PCB.
    * **Physical boot button**: Hold the `BOOT` button as you plug the RP2040
    * **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top-left key on the right-hand Main PCB) while plugging in the keyboard.
    * **Keycode in layout**: Press the key assigned to `QK_BOOT` if it is available

2. Wait for the OS to detect the device
3. Copy the `.uf2` file to the new USB disk or flash via QMK CLI
4. Wait for the keyboard to become available