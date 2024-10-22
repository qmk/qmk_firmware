# The QMK Tutorial

Your computer keyboard has a processor inside of it, similar to the one inside your computer. This processor runs software that is responsible for detecting button presses and informing the computer when keys are pressed. QMK Firmware fills the role of that software, detecting button presses and passing that information on to the host computer. When you build your custom keymap, you are creating an executable program for your keyboard.

QMK tries to put a lot of power into your hands by making easy things easy, and hard things possible. You don't have to know how to program to create powerful keymaps — you only have to follow a few simple syntax rules.

Not sure if your keyboard can run QMK? If it's a mechanical keyboard you built yourself chances are good it can. We support a [large number of hobbyist boards](https://qmk.fm/keyboards/). If your current keyboard can't run QMK there are a lot of choices out there for boards that do.

::: tip Is This Guide For Me?
If the thought of programming intimidates you, please [take a look at our online GUI](newbs_building_firmware_configurator) instead.
:::

## Overview

This guide is suitable for everyone who wants to build a keyboard firmware using the source code. If you are already a programmer you will find the process very familiar and easier to follow. There are 3 main sections to this guide:

1. [Setup Your Environment](newbs_getting_started)
2. [Building Your First Firmware](newbs_building_firmware)
3. [Flashing Firmware](newbs_flashing)

This guide is focused on helping someone who has never compiled software before. It makes choices and recommendations based on that viewpoint. There are alternative methods for many of these procedures, and we support most of those alternatives. If you have any doubt about how to accomplish a task you can [ask us for guidance](support).

## Additional Resources

Beyond this guide there are several resources you may find helpful while you learn QMK. We've collected them on the [Syllabus](syllabus) and [Learning Resources](newbs_learn_more_resources) pages.
