# A visualization library for the TMK keyboard firmware

This library is designed to work together with the [TMK keyboard firmware](https://github.com/tmk/tmk_keyboard). Currently it only works for [Chibios](http://www.chibios.org/)
 flavors, but it would be possible to add support for other configurations as well. The LCD display functionality is provided by the [uGFX library](http://www.ugfx.org/). 

## To use this library as a user
You can and should modify the visualizer\_user.c file. Check the comments in the file for more information.

## To add this library to custom keyboard projects

1. Add tmk_visualizer as a submodule to your project
1. Set VISUALIZER_DIR in the main keyboard project makefile to point to the submodule
1. Define LCD\_ENABLE and/or LCD\_BACKLIGHT\_ENABLE, to enable support
1. Include the visualizer.mk make file
1. Copy the files in the example\_integration folder to your keyboard project
1. All other files than the callback.c file are included automatically, so you will need to add callback.c to your makefile manually. If you already have a similar file in your project, you can just copy the functions instead of the whole file.
1. Edit the files to match your hardware. You might might want to read the Chibios and UGfx documentation, for more information.
1. If you enable LCD support you might also have to write a custom uGFX display driver, check the uGFX documentation for that. You probably also want to enable SPI support in your Chibios configuration.
