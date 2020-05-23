# The RSTHD Layout for minidox - Empowered with Combos
An attempt at porting Xuming Zeng’s [RSTHD](https://xsznix.wordpress.com/2016/05/16/introducing-the-rsthd-layout/) from the Ergodox to the Minidox.
[KLE Link](http://www.keyboard-layout-editor.com/#/gists/3161700bf3573325804716b2bdafa50f)
![RSTHD empowered with chords](https://live.staticflickr.com/65535/49926249372_77ab8eba95_z.jpg)

**Output shown with keyboard identified by MacOS as "International/ISO" hardware (not ANSI) and "Input Source" within Preferences set to "British Mac".**
The overall design intention is to telescope seven columns into five using combos. The top row and the bottom row form the basis of the number and nav layers respectively. Combos are shown in the above drawing using paired blue legends.
## Writing specific
As a hobby writer I have purposely chosen to make a layout that favours prose rather than code. I am sure that it will do coding very well too as I copied the general scheme from various technical looking donors in the QMK repository.
My aim has been to minimise the risk of ‘negligent discharge’ of functions whilst typing - which can be fatal to creative flow. Almost all the clever Minidox layouts I have played with suffer this to some extent. To counter this, the mod/tap keys are kept well away from the home row. The shift keys are duplicated and use ‘one shot’ functionality.
## Combos!
The philosophy behind this layout is to simulate the missing inner and outer columns that the minidox lacks relative to the Ergodox. All combos operate on keys within the inner pair of columns of each side because during normal typing the index finger has to cover both these columns, making press events of adjacent keys unlikely to overlap. They are assigned names within the keymap that relate to their position on the keyboard (not to my assigned functions) so their functions can be changed at will to suit user preference without confusing the keymap.
- Six of the chords approximate the outer keys of the Ergodox and require pairs of adjacent keys in the neighbouring columns to be pressed.
- A further four chords span the central divide, using pairs of letters that infrequently occur consecutively.
	- The three combos spanning adjacent keys over the central divide represent the inboard keys of the Ergodox, and are set to chamber one shot of their respective modifiers.
	- The quotation mark is a combo of both resting keys of the index fingers. This is inspired by those ‘air quotes’ people use in conversation.
I am confident these combos will rarely be accidentally triggered. If this occurs, try reducing the tapping term.
## Other features
- Number pad on left. This confers many benefits for the RSTHD layout, such as leaving key symbols on the primary layer uncovered that are useful for numbers (,.:-). On this layer ‘E’ becomes ‘0’.
-  The nav cluster is now on the right hand and, upon activation ’space’ becomes ‘del’, which allows rapid navigation and editing of text.
- Pair of one shot shift keys. Some users might choose to move the shift onto the bottom left and right combos which corresponds to where shift lives in the outer columns of the ergodox layout.
