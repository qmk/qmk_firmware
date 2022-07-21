# ai

![ai](https://i.imgur.com/4l6BzRh.png)

This is a small open source 5x4-1 macropad powered by QMK

* Keyboard Maintainer: [Louis Dalibard](https://github.com/make42)
* Hardware Supported: The PCB for ai is located here: [ai](https://github.com/make42/ai)
* Hardware Availability: Here is a complete BOM with links to where you can find parts:
  * PCB (I personally used JLCPCB)
  * Arduino Pro Micro ([Aliexpress](https://fr.aliexpress.com/item/32768308647.html?spm=a2g0o.order_list.0.0.3ccc5e5bU64POK&gatewayAdapt=glo2fra))
  * Female pin rows ([Aliexpress]https://fr.aliexpress.com/item/4001122376295.html?spm=a2g0o.order_list.0.0.23845e5bTBt8sp&gatewayAdapt=glo2fra))
  * Gateron hotswap sockets ([Aliexpress](https://fr.aliexpress.com/item/1005003129613578.html?spm=a2g0o.order_list.0.0.23845e5bTBt8sp&gatewayAdapt=glo2fra))
  * Zener diodes ([Aliexpress](https://fr.aliexpress.com/item/1005003276184193.html?spm=a2g0o.order_list.0.0.23845e5bTBt8sp&gatewayAdapt=glo2fra))
  * Keyswitches (use a compatible MX switch)
  * Keycaps (Duh)

Make example for this keyboard (after setting up your build environment):

    make ai:default

Flashing example for this keyboard:

    make ai:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
-   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
-   **Keycode in layout**: Press the key mapped to `RESET` if it is available
