# A multi-OS keyboard layout with support for both Linux (KDE) and MacOS-specific QWERTY layouts for many 60-ish% keyboards (

## Author: [BlueTufa](https://github.com/BlueTufa)

> Supported Keyboards: 1up RGB and HTE, Clueboard 66, dztech 60 RGB, and partial support for Preonic and Planck ortholinear keyboards.

## Layouts

### QWERTY
Default layer:  Standard QWERTY layer with CAPS lock mapped to ESC.  ESC is a Layer toggle, when held down it maps to KDE-specific MOVE layer.  Dedicated Function key for ADJUST layer.  I also take advantage of the AG_SWAP when using this keyboard on Linux, which swaps between ALT and GUI on both sides.  

Mac layer:  Mostly the same as the default layer, except that the ESC key maps to a MacOS specific set of MOVE layer shortcuts.  These leverage a piece of software called Rectangle, which makes up for some of the tiling shortcomings of MacOS.

### MOVE layer
OS-specific convenience shortcuts.  Macros are defined to make it easier to adapt these to other operating systems.  The macros also help maintain the spacing that helps with the readability of the layers in source control.  

The main goal of the MOVE layer is to manage window move and resize, and jump to a specific virtual desktop.  The other function is to expose VIM-style move keys as arrow keys to other applications.  Some keys from ADJUST layer are also redefined here.

Care was taken to keep the tiling and virtual desktop shortcuts as similar as possible between Linux and MacOS in this MOVE layer.  The most notable difference is that I haven't found a good way to do corner tiling in Linux the way that it's supported in MacOS Rectangle.

REMINDER: The 9-key left-hand pattern requires the installation of the MacOS rectangle app:

```bash
brew cask install rectangle
```

### ADJUST layer
Access to function keys as well as media controls and keyboard settings.  Some useful OS action keys are defined here as well.  

### Config layer
Access to Quantum keyboard controls as well as RGB configuration.  If audio is supported it would belong in this layer as well.
