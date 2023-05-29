# CTRL - Dvorak Programmer layout.

Provides Dvorak Programmer (dvp) on the first layer.
The second layer is for controlling of LEDs, volume, etc.
The third layer is the original qwerty setup.

To switch between the layers the key PAUSE is overriden:
- On dvp (layer 0) -> Pause switches to led control layer (layer 1).
- On led control layer (layer 1) -> Pause switches to original qwerty factory setup (layer 2).
- On original qwerty (layer 2) -> Pause switches to dvp layer (layer 0).

## Requirements

https://github.com/Massdrop/mdloader/releases
Must be downloaded, unzipped and placed somewhere in the $PATH
