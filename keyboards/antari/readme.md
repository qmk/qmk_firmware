# Antari

![Antari](https://user-images.githubusercontent.com/82454371/150683198-763633a3-3cf9-430c-b591-c8792491a326.jpg)
![PCBlegend](https://user-images.githubusercontent.com/82454371/150684317-690598c6-5f0f-4b85-8dc5-5e3b115f4f24.jpg)

ANTARI is 4x4 macropad supports analog potentiometer, rotary encoders, Oled screen, passive buzzer, 3.5mm TRS socket for sending out serial data like midi output and more. The rotary encoder also outputs midi signal when the keyboard is switched to 'Lightroom' dedicated layer, once you pressed an letter key the knob will output a midi cc signal with different parameter, which allows you use a knob to adjust up to 45 sliders in lightroom with Lightroom keymap, most importantly, the value will not jump or jitter, oppositely it moves relatively and smoothly. The oled screen will show you the last letter key you pressed and every information you need. 

* Keyboard Maintainer: [sandipratama](https://github.com/nendezkombet)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: https://github.com/nendezkombet/antari

Make example for this keyboard (after setting up your build environment):

    make antari:default

Flashing example for this keyboard:

    make antari:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available