# Signynt's Keymap: 'Sigma-Squared'

Sigma Squared is an adaptation & modification of the Layout [Miryoku](https://github.com/manna-harbour/qmk_firmware/blob/miryoku/users/manna-harbour_miryoku/miryoku.org#miryoku-) by *manna-harbour*

*manna-harbour* lays out the general principles of the layout as follows:

- Use layers instead of reaching.
- Use both hands instead of contortions.
- Use the home positions as much as possible.
- Make full use of the thumbs.
- Avoid unnecessary complication.



Sigma Squared modifies on **Miryoku** in the following ways:

- Added the Mods to the outer most columns to be easily accessed while typing with the pinkies
- Extended the **NUMBER** layer to include symbols on the right side to allow calcualtion to be typed more easily without haveing to move between layers
- Added a **GAME** layer to be used for gaming that emulates a more standard keyboard that most games expect
  - moves *left shift* and *left ctrl* down
  - *esc* moved to top left
  - gives access to a **SECOND GAME** layer that contains an Fn row as well as number and arrow keys right under your left fingers
- Added Shortcuts to the bottom row to reduce the amount of keycombos needed to use commonly needed features
  - Mission Control, Screenshot, Cycling Apps & Windows
- Added LED indicators to display what layer is currently active (only active while RGB is turned on)



### Flashing

- to directly flash to board:

  `qmk flash -kb kprepublic/bm40hsrgb -km signynt`

- to only compile:

  `qmk compile -kb kprepublic/bm40hsrgb -km signynt`



# Layout

## BASE

Tap the layer keys to use the black legends, hold them to activate the corresponding layer.

The Shortcut keys can be modified to suit your needs, or change them in your OS to match the keys.

If you are using MacOS I recommend swapping your *Ctrl* and *Cmd* keys in system preferences

The Music Control key can be pressed once to pause and be pressed twice in rapid succession to skip to the next song. 

The Screenshot Key takes a screenshot to the clipboard if pressed once, if double tapped it will take a screenshot to be saved to the desktop.

![img](https://i.imgur.com/vhb1L2f.png)

## NAVIGATION

Provides access to all essential navigation keys, comfortably under your home row. Modifiers remain identical to **BASE** layer to be used for navigating lines and words.

*Game Layer* key takes you to the **GAME** layer. *(duh)*

Bottom right keys are used to swap between Virtual Desktops. You might need to modify these to fit your OS.

![img](https://i.imgur.com/daKxxFz.png)



## MEDIA

Provides access to all basic media keys, emulating the arrow keys on the home row.

Also gives access to RGB controls.

![img](https://i.imgur.com/1jWOvvH.png)

## NUMBER

Numbers are arranged in a numpad layout beneath home row, with 0 being positioned under the thumb resting position. Layer includes all most commonly needed symbols to reduce amount of layer switching needed to type longer calculations.

Top right key changed to *Back Space* so corrections can be made without leaving layer.

![img](https://i.imgur.com/LGJT3so.png)

## SYMBOL

Symbols are positioned over respective numbers from the **NUMBER** layer.

Mouse keys are positioned similarly under the home row corresponding to the arrow keys.

Also includes *Back Space* key for corrections.

![img](https://i.imgur.com/ihOcdPj.png)

## Fn

Fn keys are arranged in the same layout as the numbers, with *F10* to *F12* added to the left

![img](https://i.imgur.com/bPpI8KN.png)

## GAME

Somewhat emulates a regular layout needed for gaming. Top right key LED will indicate that you are on the **GAME** layer, and can be pressed to exit it. Holding one of the *Second Game* keys will give you access to **SECOND GAME**

![img](https://i.imgur.com/r9KIWLX.png)

## SECOND GAME

Top right key will turn red to indicate you are in the layer

![img](https://i.imgur.com/BLKHfVB.png)



# Contact

If you have any issues or questions you can reach me through Reddit at u/Signynt or on the QMK Discord
