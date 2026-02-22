# handwired/tnx_corne_f401

*A handwired Corne keyboard using STM32F401, with support for encoders and 3D-printed parts.*

- **Hardware Supported:** STM32 (I used the Blackpill F401, but any STM32F401, F411, or F103 development board should work, provided the USB supports HID).
- **Hardware Availability:** The Blackpill F401 and Bluepill F103 are readily available in my area. I used an EC11 encoder, Outemu Blue switches, and a TRRS male-to-male cable, along with female headers to connect the two halves and enable I2C communication.
- **Flashing:** To flash the controllers with [tinyuf2](https://github.com/adafruit/tinyuf2), you will need an FTDI module or an ST-Link. These tools are essential for both the initial tinyuf2 flashing and any subsequent firmware updates.

> **NOTE:** This is more of a DIY project than a polished keyboard. I had to modify the 3D-printed case with a soldering iron to fit the controller and encoders. Proceed with caution if you follow this project.
> If you need help, I highly recommend checking out [Joe Scotto’s YouTube channel](https://www.youtube.com/@joe_scotto) and the [QMK Discord](https://discord.com/invite/qmk)—both were incredibly helpful! Special thanks to [zvecr](https://github.com/zvecr) for assisting me multiple times.

---

## Questions

### Why the STM32?
It was the cheapest option available that supported QMK. The Pro Micro was more expensive and less powerful.

### Why did I choose the Blackpill F401, and why shouldn’t you?
I chose it because it had USB-C. The Bluepill was much cheaper (about a third of the price) and would work just as well for a keyboard. However, I do not recommend the Blackpill because I bought three, and the USB-C port failed on all of them. Fortunately, the STM32 has USB pins, so I used USB-C female test boards to complete the build.

![](https://raw.githubusercontent.com/ToYoNiX/img-hosting/main/corne36_stm32f401_with_encoders/8.jpg)

---

## How to Build and Flash

**Build command:**
```sh
make handwired/tnx_corne_f401:default
```

**Flash command:**
```sh
make handwired/tnx_corne_f401:default:flash
```

---

## Bootloader

You need to flash the controllers with [tinyuf2](https://github.com/adafruit/tinyuf2).

**To enter the bootloader:**
- **Physical reset button:** Double-press the reset button on the dev board to enter DFU mode.
- **Keycode in layout:** Press the key mapped to `QK_BOOT`.

---

## 3D-printed Parts Files

- Case: https://www.printables.com/model/347524-corne-keyboard-case-5-and-6-columns.
- Keycaps and encoder knobs: Choose any prefered design you want available online.

---

## Images

![](https://raw.githubusercontent.com/ToYoNiX/img-hosting/main/corne36_stm32f401_with_encoders/0.jpg)
![](https://raw.githubusercontent.com/ToYoNiX/img-hosting/main/corne36_stm32f401_with_encoders/1.jpg)
![](https://raw.githubusercontent.com/ToYoNiX/img-hosting/main/corne36_stm32f401_with_encoders/2.jpg)
![](https://raw.githubusercontent.com/ToYoNiX/img-hosting/main/corne36_stm32f401_with_encoders/3.jpg)
![](https://raw.githubusercontent.com/ToYoNiX/img-hosting/main/corne36_stm32f401_with_encoders/4.jpg)
![](https://raw.githubusercontent.com/ToYoNiX/img-hosting/main/corne36_stm32f401_with_encoders/5.jpg)
![](https://raw.githubusercontent.com/ToYoNiX/img-hosting/main/corne36_stm32f401_with_encoders/6.jpg)
![](https://raw.githubusercontent.com/ToYoNiX/img-hosting/main/corne36_stm32f401_with_encoders/7.jpg)

---
