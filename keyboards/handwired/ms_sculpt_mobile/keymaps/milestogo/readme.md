# keymap taking advantage of the STM32 storage & CPU. 
RGB LED is used to show layers. 
The default bluepill LED is capslock.

###RGB over serial
There's a simple serial protocol for the keyboard to listen for color change commands from the PC. 
Useful for "do stuff && cat "green">/dev/ttyACM0"
Lower case letters set pre-programmed colors
Upper case letters change RGB mode
Command C takes 3-5 octets of RGB settings. Numbers can be terminated with a comma or period. 
3 octets = set all LED, 4th argument specfies specfic LED, 4+5 specify start and stop LEDs.
