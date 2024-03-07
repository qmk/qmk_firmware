# Abats Keyboard Club New Jeans

![NewJeans](https://i.imgur.com/c5vHuF4l.jpg)

The New Jeans TKL is a keyboard inspired by the K-pop group NewJeans, which made its debut in 2022. NewJeans is a South Korean group formed by ADOR and consists of five members: Minji, Hanni, Danielle, Haerin, and Hyein. Known for their modern pop and R&B songs that draw inspiration from the styles of the 1990s and 2000s, NewJeans has quickly become a symbol of youthful and vibrant culture.

This keyboard mirrors the blend of modern and classic influences seen in NewJeans' music. It incorporates the use of Tadpole and Poron gasket mounts, elements commonly found in various high-end keyboards, which are celebrated for enhancing typing comfort and sound quality. Furthermore, the New Jeans TKL marks the third development from the Abats Keyboard Club, showcasing their continued innovation and craftsmanship in the keyboard industry.

By integrating elements reminiscent of the NewJeans group's style and music, the New Jeans TKL keyboard not only serves as a functional tool for typing and gaming but also as a tribute to the cultural impact of the group. It stands as a unique fusion of technology and pop culture, appealing to fans of the group and keyboard enthusiasts alike.

* Keyboard Maintainer: [Ramon Imbao](https://github.com/ramonimbao)
* Hardware Supported: STM32F072

Make example for this keyboard (after setting up your build environment):

    make abatskeyboardclub/newjeans:default

Flashing example for this keyboard:

    make abatskeyboardclub/newjeans:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press and hold the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
