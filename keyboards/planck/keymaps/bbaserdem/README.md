# Planck Layout

Built this planck layout to use DVORAK with an unorthodox Turkish layout.
If you used a previous layout with a persistent base layer change,
change it to 0 before proceeding.
The layout has the following functionality

* **QWERTY** can be toggled on/off from **Function** layer.
* **Mouse** layer allows manipulation of the mouse.
* **Function** layer has F and special keys.
* **Symbol** layer has numericals and symbols.
* **Game** layout can be toggled on/off from **Function** layer.
* **Music** layer allows playing sounds like a keyboard.

Double tapping **Mouse**, **Function** and **Symbol** layers activate them until deacivation.
Topleftmost key turns off **Function**, **Symbol**, **Game** and **Music** layers,
and puts the board into *reset* mode from the **Mouse** layer.

# Using Turkish letters

Instead of a turkish F keyboard layout (very inconvenient to code in),
I opted to modulate characters like an *AltGr* impleentation.
Tap and holding *Alt* on **DVORAK** and **QWERTY** layer will change some letters
to Turkish equivelants.
Shifting these letters will work.
The keycodes should transmit the correct unicode characters combined with shift.
The turkish letters are sent via the unicode implementation.
No software layout change is neccessary (hence making coding easier).
By default, the unicode is set to Linux mode. Switch to windows (non-persistent)
can be done from the associated key in **Function** layer.
**Symbol** layer also has the symbol for Turkish Lira.

# To improve

I want to write a couple pieces of my own music for layer switching.
