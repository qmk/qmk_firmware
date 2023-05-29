# shahnetwork keyboard

My own custom board :)

* Keyboard Maintainer: [sagepeppermint](https://github.com/sagepeppermint)
* Hardware Supported: custom STM32F412 based board

Make example for this keyboard:

    make shahnetwork/b:default

Flashing this keyboard:

    make shahnetwork/b:default:dfu-util-split-left
    make shahnetwork/b:default:dfu-util-split-right

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the superior-medial most key on either side and plug in the keyboard
* **Physical reset button**: Accessible inside case with angled tweezers press RESET down (most medial key) whist plugging in
* **Keycode in layout**: Press the key mapped to `QK_BOOT`, accessed by right side medial thumb key plus 1st row 6th column key
readme.md
