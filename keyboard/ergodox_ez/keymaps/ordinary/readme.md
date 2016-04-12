# The Ordinary Layout, a familiar and powerful layout #

The Ordinary Layout is intended to be unremarkably mundane and remarkably useful. This layout maintains most key positions from common QWERTY keyboards, and it features enhanced Symbol and Media layers compared to the default Ergodox EZ layout.

The Ordinary Layout is supposed to look mostly like a normal keyboard, except in the ways that the Ergodox key arrangement is unique. The thumbs are responsible for space, enter, plus both forward and backward delete; with only a couple exceptions, all other keys are in the same place they are found on traditional keyboards.

Nicholas Keene
ordinarylayout@nicholaskeene.com
no rights reserved, use for any purposes, credit me if you are a nice person

## The Base Layout ##

* The light blue keys are modifiers: traditional Control, Option, and Command keys, plus Hyper and Meh
* The dark blue keys are Shift keys: Capitals Shift (traditional shift), Symbol Shift, and Media Shift; plus a Shift Lock key
* Several dark blue keys double for entry of characters which would typically be in those locations
* The turquoise keys are text navigation and manipulation
* The red keys is Escape and it is always found in that location no matter what

![Ordinary base layout](ordinary-base.png)

This layout puts the modifier keys along the bottom of the keyboard where they are on most keyboards. They are in the regular order, with the addition of Hyper and Meh keys. On the outside edges are the Shift keys. The traditional shift key is called Capitals Shift and it is in the normal location. Above that are Symbols Shift and Media Shift. Each Shift key momentarily switches the layout to that layer, and if you use the Shift Lock button you can lock the layout to that layer.

Touch typists will also find tilde, tab, equals/plus, slash/pipe, and quote/double-quote sharing space on those Shift keys where they would probably be on a common keyboard. Other than the turquoise keys the only buttons which move to new locations are the Brackets and Dash and Escape. Most touch typists dont touch-type brackets or dash anyway so only Escape really requires retraining of muscle memory, and see below for the Special Escape Sequence.

The four big turquoise keys are arranged differently than in the default Ergodox EZ layout. The Ordinary Layout here copies the design of the old Fingerworks TouchStream keyboard, but also reflects the natural presumptions of the author -- me! I type the space character with my right hand, and to me it makes sense for the two delete keys to be next to one another.

The Forward Tab and Backward Tab keys are in their locations mostly because I ended up with two extra buttons and needed something to do with them. My muscle memory from using the Truly Ergonomic Keyboard makes me look for the Tab key with my right index finger, so it is handy to have this redundant Tab, and the idea with the Backward Tab key is that it becomes easy to navigate text fields in forms, or to indent/unindent code.

## The Symbols Layer ##

* The light green keys are the eponymous symbols
* The bright green keys are F-Keys
* The dark green keys constitute a number pad
* The turquoise keys are the *reverse* of the turquoise keys on the base layer

![Ordinary symbol layout](ordinary-symbol.png)

The Ergodox EZ ships with the "Coder Layer" which I like to call the Symbols layer. There are some significant improvements in The Ordinary Layout over the default layout.

The symbol keys are mostly the same as on the default layout, which did a good job in this regard, but with a few enhancements:

* Angle brackets on this layer mean that curly, square, and angle brackets are all available on different layers of the same two buttons. Also, they mean that all kinds of brackets, including parentheses, are available on both the Base and Symbols layers.
* The slash, backslash, and pipe characters are grouped together as a memory aid.
* The & and | symbols are juxtaposed as a memory aid

The number pad area here, in green, includes all four arithmetic operations in the same order found on most number pads and features an Enter key. The keycodes emitted here are normal numeric keycodes, not the number-pad specific keycodes emitted by most number pads, because this layout does not use a Num Lock key to switch the buttons between numeric keycodes and navigational keycodes. See the explanation in The Media Layout section about navigation using these same buttons.

Finally, consider the turquoise text-nav keys. Here in the Symbols layer, these are *reversed* from the base layer, with most keys mirrored, but the Delete keys shifted to maintain the directional significance of their arrangement. This is powerful! Often I find myself using the mouse with my right hand, and the left hand needs to press Enter. Instead of reaching the left hand over to the right side of the keyboard, now I simply tap Symbols to reverse the yellow keys, and Enter is right where it should be.

## The Media Layer ##

* The dark orange keys on the left move the mouse cursor
* The dark orange keys on the right move the text cursor
* The light orange keys are for scrolling and paging
* The bright green keys are more F-keys
* The dark yellow keys signal Web and Audio applications
* The light yellow keys signal the operating system

![Ordinary media layout](ordinary-media.png)

This layer was inspired by the Media layer on the Ergodox EZ but takes it farther. The Fingerworks TouchStream keyboard had a very useful feature for controlling the text cursor easily and this layer does something similar. The left hand can move the mouse, the right hand moves the text cursor, in all four directions, in small or large increments. This greatly enhances navigation in text documents.

Moreover, the orange keys on the right overlay the numberpad from the Symbols Layer, such that in the Media Layer the same keys can be used as if they were a number pad in navigational mode (Num Lock off). For instance, in traditional number pads the '3' key became 'Page Down', and so it is here. This means a user can do text navigation without moving either hand.

## Switching Between Layers ##

The three Shift keys correspond to three logical layers on top of the ever-present base layer, and are represented in the three LEDs on the keyboard: Capitals (red), Symbols (green), Media (blue). The color of a layer illuminates when the layer is active. Shift keys work in the expected way: press them and the keys shift to that layer; release them and the keys shift back to the base layer. The Ordinary Layout also features a Shift Lock key to keep a layer active indefinitely. Hold down the Shift Lock key then press any Shift key to lock to that layer. Or, hold down the Shift key and press the Shift Lock key; either way works. To revert to the base layer, use the Shift Lock key again in combination with the Shift key.

This layout attempts to treat the Capitals Shift layer the same as the other two Shift layers, but internally they are different which causes some inconsistencies. For instance, it is possible to switch from any layer to any other layer, and to lock to any layer, *except* it is not possible to go from Media to Symbols. You must exit the Media layer before engaging the Symbols layer. Also, the Caps Lock feature must be triggered by first pressing the Shift Lock key then a Capitals Shift key; it doesn't work if you press the Shift key first (instead you get the secondary symbol associated with the Shift Lock button).

## Special Escape Sequence ##

In the Ordinary Layout, the most unsatisfying key location is the Escape key which rightly belongs segregated on its own way up on the top left of the keyboard. The Ergodox does not have a physical button in such a location and the nearest one, in the top left corner, was assigned to the tilde button which is traditionally found in that location. The Escape key is important so it features prominently on the other top corner on the left side of the keyboard, and is always there in all layers. Nevertheless, alas, it isn't Ordinary to put the escape in that different corner!

That tilde key has a second function as the Shift Lock key and that makes possible a special feature. To make this layout as Ordinary as possible, the Escape key can *also* be accessed by pressing Shift Lock then the 1 button right next to it. This easy gesture is a way to partially maintain the ease of flicking your wrist to the left and tapping Escape. This gesture works in all layers.
