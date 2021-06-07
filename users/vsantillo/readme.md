# Vince's QMK Userspace

## Introduction
Hi, my name is Vince. This directory contains my QMK userspace. You can pull this userspace into your fork and mess with things. However, if you find anything needs updating, let me know! I'm always interested in learning more.

This repository currently contains **Tap Dances**, **Lighting Animations**, and an implementation for the **DZ60RGB ANSI v2**. I will continue to make further revisions and additions to this code.
**Tap Dances**:

 - Space Cadet Pro
 - Quick Mute
 - Quick Undo/Redo

**Animations**:
- Berry LERP 

## Tap Dances

### Space Cadet Pro
This is an extension of the Space Cadet Shift pattern. My touch typing accuracy with ring and pinky fingers isn't so hot, so in addition to not having to navigate to the `9` and  `0`, I also don't have to navigate to `[` and `]` keys respectfully.  This version extends so that two presses prints square brackets (`[]`) and three presses sends curly braces (`{}`). 

### Quick Mute
This tap dance will send `KC_VOLD` on Tap, and `KC_MUTE` on Hold. This has a set time separate from the set `TAPPING_TERM`. This function requires a shorter tap dance term because subsequent taps will further delay their processing making it seem less responsive. At the set interval, it is capable of performing the Mute without holding up any of the Volume Down messages.

### Quick Undo/Redo

This tap dance will a `ALT+Z` and `ALT+Shift+Z`which are my editors' Undo and Redo functions respectfully. Double Tap and Hold left Alt key to Undo. Double Tap and Hold right Alt key to Redo.

## Animations

### Berry LERP

This animation is an HSV LERP (Linear Interpolation) between Purple, Cyan, Magenta, and Teal. The implementation of HSV LERP is based on [The Secrets of Colour Interpolation](https://www.alanzucconi.com/2016/01/06/colour-interpolation/) by [Alan Zucconi](https://www.alanzucconi.com) and is located in `lighting/animations/common.h`. 

## My Keyboards

### Chu Cake

**Case**: Zig Zag 60%
**PCB**: DZ60RGB ANSI v2
**Keycaps**: DSA Vilebloom 
**Keyswitches**:
 - **Spacebar**: Tealios
 - **Else**: Box Royal

**Stabilizers**: Screw-in Stabilizers
