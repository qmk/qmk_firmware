# Momentum

Momentum is a feature that lets you control the speed of lighting effects (like the Rainbow Swirl effect) with the speed of your typing. The faster you type, the faster the lights will go!

## Usage
For Momentum to take effect, you need to enable it with the MOM_TOG keycode, which toggles it on and off.

The following light effects will all be controlled by Momentum when it is enabled:
 - RGB Breathing
 - RGB Rainbow Mood
 - RGB Rainbow Swirl
 - RGB Snake
 - RGB Knight

 As long as Momentum is enabled, it will control the speed regardless of any other speed setting that your RGB lights are currently on.

 ## Configuration
 Momentum doesn't currently support any configuration via keyboard settings. If you want to adjust something like the speed increase or decay rate, you would need to edit `momentum.c` and adjust the values there to achieve the kinds of speeds that you like.