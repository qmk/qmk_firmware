# SPV1 keyboard QMK firmware

![spv1](https://i.imgur.com/C2tNDzY.jpg)

SPV1 is a southpaw 75% with numpad designed by Bisoromi and sold through CannonKeys.

* Keyboard Maintainer: [Gondolindrim](https://github.com/Gondolindrim);
* Hardware Supported: proprietary PCB using STM32F401 microcontroller;
* Hardware Availability: the groupbuy of the SPV1 ran in february 2023.

## Flashing instructions 

### Step 1: enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: press the physical button on the back of the PCB for at least five seconds
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (ESC key at layer 1 in the default layout)

### Step 2: compile firmware

After accessing the DFU state in your PCB, build the default layout using:

    make spv1:default

### Step 3: flashing

You can use a flashing tool like `dfu-util` or QMK Toolbox to download the resulting `*.bin` file into your PCB.

### (Alternative) Compile and flash

After accessing the DFU state in your PCB, you can compile-and-flash automatically using `dfu-util` through

    make spv1:default:flash

### VIA firmware

When compiling, just substitute `default` for `via`.

## Additional info

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
