# Techtomas Configuration

## Base Layer

The base layer is a merge of what I liked with the default layout and the ordinary layout. The thumb cluster is more like the Kinesis advantage and the top row of the cluster is convient for use on the mac.

* The Caps Lock postion handles [Hyper/Esc](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)
* The Tab key toggles MEH.
* The top vertical mods on the left and right are [ and ].
* The bottom vertical mods on the left and right are tab and shift+tab
* The HYPER and MEH key are made in the same location on the right side of the board as well. Using Keyboard Maestro for OS X makes one-handed shortcuts very easy.
* Layer switching is focused around the thumb clusters plus some additional locations for convience.

## Symbol Layer
The symbol layer can be tap/toggled with the bottom right key and also toggled on the thumb clusters.

The bottom two vertical mods are set to F14 and F15 which is the default for changing screen brightness on the mac

## App Layer
The app layer is used to control media playback and also some application shortcuts (OS X Focused).
It can be toggled on the left board in the top left corner (tilde/grave) or using your pinky on the right side of the board using either ; or /.
There is one additional toggle on the right thumb cluster for quick access to play and mute key combos.

### Current App shortcuts defined
* Q = CMD+Q
* W = CMD+W
* Z = CMD+Z
* X = CMD+X
* C = CMD+C
* V = CMD+V
* B = CTRL+C
* P = Print Screen

## Control Layer
The control layer is meant to help easily navigate and select text. It can also be stacked ontop of the Symbol layer when needed.

The right arrow key and End key toggle the control layer on the left board. There is also a tap toggle for the layer in the same position on the right side of the board.

On the left board you have mouse control with left & right click in the location of the G and B keys.
On the right board you have vim-style arrow keys using hjkl

The left thumb cluster moves shift and alt within easy reach while holding the toggle (end). So far I've found this convient to navigate and  skip around text when using the hjkl arrow keys. I found that it was easy to get the alt key stuck on depending on what key you released first so I added the PREVENT_STUCK_MODIFIERS to the config.h to help with that.

## Changelog

* May 4th, 2016 (v1.2):
  * Moved layer toggles around to match my habbits of typing
  * Enabled Prevent Stuck Modifers in my config.h (L3 + Alt on cluster would get stuck)
  * Changed media layer to be more like an app layer with some quick shortcuts (mac centric)
  * Moved around the base layer arrow keys so mod keys were more accesible

* Apr 29, 2016 (V1.1):
  * Added F14 and F15 to symbol layer
  * Added control layer toggle to A key.

* Apr 28, 2016 (V1.0):
  * Modified config based on the default layout plus inspiration from the ordinary layout
