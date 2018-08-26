# Velocikey

Velocikey is a feature that lets you control the speed of lighting effects (like the Rainbow Swirl effect) with the speed of your typing. The faster you type, the faster the lights will go!

## Usage
For Velocikey to take effect, you need to enable it with the VLK_TOG keycode, which toggles it on and off.

The following light effects will all be controlled by Velocikey when it is enabled:
 - RGB Breathing
 - RGB Rainbow Mood
 - RGB Rainbow Swirl
 - RGB Snake
 - RGB Knight

Support for LED breathing effects is planned but not available yet.

 As long as Velocikey is enabled, it will control the speed regardless of any other speed setting that your RGB lights are currently on.

 ## Configuration
 Velocikey doesn't currently support any configuration via keyboard settings. If you want to adjust something like the speed increase or decay rate, you would need to edit `velocikey.c` and adjust the values there to achieve the kinds of speeds that you like.