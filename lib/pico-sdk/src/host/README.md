This is a basic set of replacement library implementations sufficient to get simple applications
running on your computer (Raspberry Pi OS, Linux, macOS or Windows using Cygwin or Windows Subsystem for Linux).
It is selected by `PICO_PLATFORM=host` in your CMake build

This can be extremely useful for testing and debugging higher level application code, or porting code which is not yet small enough 
to run on the RP2040 device itself.

This base level host library provides a minimal environment to compile programs, but is likely sufficient for programs
that don't access hardware directly.

It is possible however to inject additional SDK library implementations/simulations to provide 
more complete functionality. For an example of this see the [pico-host-sdl](https://github.com/raspberrypi/pico-host-sdl) 
which uses the SDL2 library to add additional library support for pico_multicore, timers/alarms in pico-time and 
pico-audio/pico-scanvideo from [pico-extras](https://github.com/raspberrypi/pico-extras)
