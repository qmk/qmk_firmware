# Keymap for Spin by DMQ Design - work in progress

* Keypad layout rotated to a vertical position (encoders at top, OLED at bottom)
* Layer selection is via the third encoder and is looped
* OLED displays layer name and RGB mode  
<br />

* First layer is a numberpad.
* Encoders (CW, !CW, Press):
* 1 - VolUp, VolDn, Mute
* 2 - ScrollUp, ScrollDn, Reset
* 3 - Next layer, Previous layer, Photoshop layer
<br />

* Second layer is RGB control layer. Encoders as numberpad.
<br />

* Third layer is F keys
<br />

* Forth layer is user specific (ie customised) Photoshop keys (customised keybinds included below) 
* Encoders (CW, !CW, Press):
* 1 - ], [, Mute
* 2 - Opacity/Fill/Flow (with Shift modifier) +3%, -3%, Next Document (CTRL+TAB)
* 3 - Next layer, Previous layer, Numberpad layer
* Note that the opacity/fill/flow functionality cannot read the current value from Photoshop, instead a value of 60% is chosen as the start point (when the keypad is connected)and for each detent turn cw that value is increased by 3, rememberred, and sent as a keypress. Turning anti-cw  reduces the value by 3 and sends as a keypress. ie on first use it will **always** set the opacity/fill/flow to 60% and increase/decrease form there.  
<br />

* Fifth layer is arrow keys (aiming to merge these into another layer).  Encoders as numberpad.  
<br />

* Sixth layer is Destiny 2 macros for lazy Guardians (not implimented yet becasue timed macros).  Encoders as numberpad.  
<br />
<br />

#Photoshop keybinds

KEY	|	TOOLS				|	CTRL			|	CTRL SHFT			|	CTRL ALT				|	CTRL ALT SHIFT	|	ALT SHIFT/MODE
---	|	------------------	|	--------------	|	------------------	|	---------------------	|	--------------	|	--------------
A 	|	Quick mask			|	Select all		|	Show/Hide 			|							|	High pass		|	
I 	|	Eye dropper			| 	Invert			|	Inverse selection	|	Edit image				|	File info		|
N 	|	Brush				|	New document	|	New layer			|							|					|	Normal
G 	|	Gradient			|	Group			|	Ungroup				|	Link/release clip mask	|					|
X 	|	Switch swatches 	|	Cut				|	Liquify				|	Transform				|	Puppet warp		|
C 	|	Crop				|	Copy			|	Copy visible		|	Dupe to new layer		|	Colour range	|	Colour
V 	|	Move 				|	Paste			|						|							|					|
D 	|	Reset swatches		|	Deselect		|						|							|					|
S	|	Clone, Heal, Spot 	|	Save			|	Save as				|	Smart object			|					|	Screen
E 	|	Dodge, Burn 		|	Merge Down		|	Merge visible		|	Stamp selected 			|	Stamp visible	|	Difference
P 	|	Path 				|	Curves			|	Place linked		|	Place embedded			|					|	Passthrough
K 	|	Smudge, Blur 		|	Selective col	|	Hue/Sat				|							|					|	Darken
L 	|	Lasso, Marquee 		|	Levels 			|						|							|					|	Luminosity
Z 	|	Zoom 				|	Step backward	|	Step forward 		|	Undo/Redo				|					|
TBA	|						|					|						|							|					|	Overlay
TBA	|						|					|						|							|					|	Soft light