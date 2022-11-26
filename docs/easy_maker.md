# Easy Maker - Build One-Off Projects In Configurator

Have you ever needed an easy way to program a controller, such as a Proton C or Teensy 2.0, for a one-off project you're building? QMK has you covered with the Easy Maker. Now you can create a firmware in minutes using QMK Configurator.

There are different styles of Easy Maker available depending on your needs:

* [Direct Pin](https://config.qmk.fm/#/?filter=ez_maker/direct) - Connect a single switch to a single pin
* Direct Pin + Backlight (Coming Soon) - Like Direct Pin but dedicates a single pin to [Backlight](feature_backlight.md) control
* Direct Pin + Numlock (Coming Soon) - Like Direct Pin but dedicates a single pin to the Numlock LED
* Direct Pin + Capslock (Coming Soon) - Like Direct Pin but dedicates a single pin to the Capslock LED
* Direct Pin + Encoder (Coming Soon) - Like Direct Pin but uses 2 pins to add a single rotary encoder

## Quickstart

The easiest way to get started is with the Direct Pin boards. This will assign a single key to each pin and you can short that pin to ground to activate it. Select your MCU from the Keyboard dropdown here:

* <https://config.qmk.fm/#/?filter=ez_maker/direct>

For more details see the [Direct Pin](#direct-pin) section.

# Direct Pin

As its name implies Direct Pin works by connecting one switch per pin. The other side of the switch should be connected to ground (VSS or GND.) You don't need any other components, your MCU has internal pull-up resistors so that the switch sensing can work.

Here is a schematic showing how we connect a single button to pin A3 on a ProMicro:

![Schematic diagram showing a ProMicro with a wire coming out of A3, connecting to the left side of a switch. Another wire comes out of the right side of the switch to connect to the Ground Plane.](https://i.imgur.com/JcDhZll.png)

Once you have wired your switches you can assign keycodes to each pin and build a firmware by selecting the MCU you are using from the Keyboard dropdown. Use this link to show only Easy Maker Direct Pin:

* <https://config.qmk.fm/#/?filter=ez_maker/direct>
