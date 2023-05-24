# A keymap for Durgod Taurus K310/K320 that supports toggling between Mac and Windows

Supports both ANSI and ISO layouts.

Layer 0 : Standard layout (Windows)

Layer 1 : Media control and Windows lock key (Windows)
- Reusing Durgod's Original Media Control for Fn + F1 ~ Fn + F7
- Fn + Windows to toggle Windows lock key functionality

Layer 2 : System layer (Windows)
- Fn + Menu + Esc : Bootloader mode
- Fn + Menu + F1  : System Sleep
- Fn + Menu + F4  : Turning Off System
- Fn + Menu + F12 : Switch to Mac layout

Layer 3 : Mac layout

Layer 4 : Media control and Media lock key (Mac)
 - Standard Mac Media keys for Fn + F1 ~ Fn + F12.
 - Fn + F13 to toggle Media lock key functionality

Layer 5 : System layer (Mac)
- Fn + R-ALT + Esc : Bootloader mode
- Fn + R-ALT + F4  : Shutdown/Sleep (Hold down on Mac)
- Fn + R-ALT + F12 : Switch to Windows layout

## Toggle between Mac and Windows layout

You can switch between Mac and Windows layout by doing the following:
- Hold down Fn + Menu (Windows Layout) or Fn + Right-Alt (Mac layout)  (These are the same physical keys)
- Press F12

The 'M' led will be lit when you are using the alternate layout.  By default Mac is the alternate layout.

You can change the default & alternate layout by setting the following flags to either '_WBL'(Windows) or '_MBL' (Mac)
- DEFAULT_LAYOUT (initial layout to use on boot)
- ALT_LAYOUT (layout that will light the 'M' LED when active)

For example, to configure Mac as the default layer, and Windows to be the alternate layout, compile with these flags:

    make EXTRAFLAGS="-DDEFAULT_LAYOUT=_MBL -DALT_LAYOUT=_WBL" durgod/k3x0/k310:chimera

## Windows key lock

In windows layout, you can hold down Fn + Windows key to disable the Windows key while in locked mode.  The 'Lock' LED
indicates if the Windows key is locked.

This is similar to the stock K310/K320 Windows key lock functionality.

## Mac Media Lock

To switch between Function row and Media row in Mac layout, press Fn + PrtSc.  The 'Lock' LED indicator will be lit when in Media row mode.

### Subsequent Flashing

For repeating Flashing you have two options with this keymap:
1. Use BootMagic
- BootMagic Lite has been enabled with Assigned "Esc" key 
- Unplug USB Cable
- Holding Esc Button 
- Plug in USB Cable, Keyboard should be in ST-Bootloader state
2. Use key combination if using default keymap
- Hold down Fn + Menu (Windows Layout) or Fn + Right-Alt (Mac layout)  (These are the same physical keys)
- Press Esc.  Keyboard should go into booloader state.
