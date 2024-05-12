# NuPhy Gem80


* Keyboard Maintainer: [ryodeushii](https://github.com/ryodeushii)
* Hardware Supported: NuPhy Gem 80 (Tri-Mode and Wired only, depends on `WORK_MODE` parameter in `config.h`)
* Hardware Availability: Private

Make example for this keyboard (after setting up your build environment):

    make nuphy/gem80/ansi:via

Flashing example for this keyboard:

    make nuphy/gem80/ansi:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## [Firmware install guide from Nuphy website](https://nuphy.com/pages/qmk-firmwares)
## [VIA guide from Nuphy website](https://nuphy.com/pages/via-usage-guide-for-nuphy-keyboards)

## Bootloader

Enter the bootloader in one way:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard

* **Hardware reset**: Remove the capslock keycap, hold the little button beneath and plug in the keyboard.


## Battery indication (level to color mapping)

```
0-20 red
20-40 orange
40-50 yellow
50-80 blue-purpleish idk how to name that, you'll see :smile:
80-100 green
```

## Notes

* Since the version 1.1.0.2 the keyboard uses asyncronous debounce algorithm. To control debounce values for press and release events you can use VIA (usevia.app) or using binds on the keyboard. Press deounbe default binds can be found in PDF or MD file with binds. Default binds for release debounce aren't set, so you have to configure them to your preference.

## Keybinds guide

Here is a [list](gem80-guide.md) of keybinds that you can use to control your keyboard.

## Default layout for functional layer (for both VIA and non-VIA versions of keyboard)

![default layout](https://i.imgur.com/pCUatpG.png)


## MCUs used

Main: STM32F072RBT6 [description](https://www.st.com/en/microcontrollers-microprocessors/stm32f072rb.html)
Wireless: NRF52832 [description](https://www.nordicsemi.com/Products/nRF52832)

Fun fact: wireless MCU is almost 2x times better (more performant) than main MCU :smile:



# Latency tests

I've tested official 1.1.4 three-mode version, mine 1.1.0.2 with stock settings and mine 1.1.0.2 with adjusted debounce 3-3

These are average latencies (per 100 measured clicks)
3-3 in last column mean 3ms press and 3ms release debounce
```
FIRMWARE    Official 1.1.4     Ryo  1.1.0.2 fresh    Ryo  1.1.0.2 (3-3)
AVERAGE         9.3465             8.7253               8.7253
MEDIAN          10.275             7.74                 7.74
PERCENT(AVG)    100.00%            -6.65%               -6.65%
PERCENT(MEDIAN) 100.00%            -24.67%              -24.67%

```

Below you can see chart with all measures over 100 samples
![https://i.imgur.com/V2tIK5P.png](https://i.imgur.com/V2tIK5P.png)


And as I placed official as 100% reference, my firmware has 6.65% less latency :slight_smile:
As expected, debounce settings haven't affected input latency. Ofc, situation would be different, if I'd use debounce above 30-40ms. But this can be felt even without any measures.


All measure were made with [latency tester](https://github.com/joelspadin/keyboard-latency-tester)


Maybe at some point [this pr](https://github.com/joelspadin/keyboard-latency-tester/pull/1) would be merged and results would be part of the original repo :D




# Links

1. Patch to use tap-dance (1 tap - caps lock, 2 taps - cmd + space - to change language in majority of OS - useful if you use caps lock in macOS to change language to keep similar behavior in Windows/Linux): [link](https://gist.github.com/ryodeushii/2587f877cbe81e9d9c666a2d8066e416)
2. Patch to apply small perf tweak (to reduce latency by 0.1-0.18ms) can be found [here](https://gist.github.com/ryodeushii/4cffcb6a6f427c023a0d0007d173ff2b)



# TODO
- [x] ~~Refactor NUM_LOCK, SCROLL_LOCK indicators to store LED position in eeprom - and update it only if it changes!!! - to avoid weird issues with board~~ remove unnecessary indicators (num, scroll)
- [x] Fix num-lock & scroll lock under key LEDs indication causing random issues with board
- [x] Store configs in keyboard data section of eeprom + proper eeprom init (instead of VIA_EEPROM and if VIA is enabled, use VIA_EEPROM)?? questionable
- [x] Add default layout without VIA
    - [x] with all custom binds assigned
    - [ ] update the manual
- [x] Refactor structure to contain VIA layout, default layout

