# Overview

My personal QMK userspace. First, I must say that the credit for a majority of the code found here belongs to Drashna and/or the people he derived his code from. My Ergodox layout is briefly described in its respective folder. As for explaining this userspace, you could honestly go to Drashna's userspace and read his well put together readme. Regardless, I am mostly writing this as an excercise for myself to better understand what is going on, and where applicable, describe things that I innovated on my own.

## Bocaj.c

### Unicode

I've always had difficulty implementing unicode in QMK, all of this code is literally copy/pasted from Drashna's userspace and lies dormant here until I can take the time to figure it out.

Update: Got it to work in Mac OS which is more important to me than Windows (probably pretty easy to figure out at this point). So I'm a happy table flipping person now!

(ノಠ痊ಠ)ノ彡┻━┻

┬─┬ノ( º _ ºノ)

### Tap Macro

Not sure why this doesn't exist in QMK already (maybe it does?)

```c
void tap(uint16_t keycode){ register_code(keycode); unregister_code(keycode); };
```

### *_keymap functions

We're running *_user functions in the userspace, that way we can add to or reconfigure at the keyboard level. Any *_user functions should call the equivalent *_keymap function at the end. If the *_keymap function isn't defined in the keymap, the `__attribute__ ((weak))` will prevent build problems.

### Startup/Suspend/Shutdown Functions

I have no idea what these do. Non-Ergodox keyboard functions?

### Matrix Scan User

Leader key defines, Diablo macro ancillary function, run matrix_scan_keymap.

#### Leader Key

I've always been interested in this feature, but I've had 0 experience with applications that have similar behavior. My implementation seeks to implement features that I feel VS2017 lacks

## Secrets

Hacked Drashna's secret macro implementation to work with the leader key instead.
TODO: Finish documentation

## Bocaj.h

Layer defines, some macro ancillary defines, setup Diablo macros and failsafe

## Process_Records.c/.h

Again, taking ideas from Drashna to make maintenance simpler. A couple of things that I'm proud of here, but nothing really ground breaking.

* Features
  * Change default layer
    * KC_MWRK, KC_WWRK, KC_MQWR
  * MacOS Lock Screen Macro
  * Make macro (Credit: Drashna)
    * Need to reconfigure so it runs the docker command if one of the Mac OS layers are default because the AVR install fails on the corporate laptop
  * Arrow macro (->) because I find myself telling people how to get to something quite frequently and typing this manually requires moving the right hand to the top-left of the ergodox and then to the bottom right, which feels unnatural.
  * LM_GRAVE
    * While combining _NUMS and _LOWER, I also needed a place to put F1-12 keys. This required me to relocate the grave key. The most comfortable place to put it was over a key that I frequently use to toggle the numpad. I do have other ways to get to/from this layer but my mind has been wired to use them for different workflows, so I would sit here frozen for a moment trying to tell my fingers where to go
    * How it works
      * A timer starts when pressed down
      * If the timer at release was less than the TAPPING_TERM define
        * Get mods
        * If Shift was held or one-shot shift was active
          * Send `~`
        * Else
          * Send `
      * Else (timer at released was greater than the TAPPING_TERM define)
        * Move to the default layer
  * KC_CCCV
    * Another neat idea I found in Drashna's userspace... highly underutilized in my layout but the inspiration for LM_GRAVE was obviously derived from this code
  * Unicode stuff
    * All I've ever wanted was a table-flip macro... I managed to get about half of it to work before I gave up and disabled it

## Send_Unicode.c/.h

I have some basic understanding of this, Drashna may already have it documented in his userspace. I'll put it in my own words when I get around to making it work and understanding it better.

## Tap_Dances.c/h

Again, building on Drashna's userspace organization to simplify maintenance of a heavily configured layout. This is all the stuff for the Diablo 3 macros that spam a given skill (1-4) every ~1 second

## Wrappers.h

Traditionally, you would put all of this into the \<username>.h file. But I liked the idea of separating it to simplify modification in the future.

### GUI_CTR(os, kc)

A notable mention in this file is the GUI_CTR(os, kc) custom keycode defined in process_records.h as:

```c
#define GUI_CTR(os, kc) MT( (os == 0) ? (MOD_LGUI) : (MOD_LCTL), kc )
```

I tried several things before coming to this one-liner conclusion. I believe it is quite elegant and it definitely solves the problem I had (separate wrappers for Windows/MacOS layers). But I would love to make this into something more intuitive, like a macro that detects which layer you're on and sends the applicable hotkey when held, or keycode when tapped. Ultimately, I was too tired of thinking about it to come up with a solution like that at this time.

Anyhow, if you set `os == 1`, it sends the Windows CTRL hotkey when held. If you set `os == 0`, it sends the Mac OS GUI hotkey when held. If tapped, it sends the keycode.

This is effectively a slightly more advanced `MOD_T(kc)` keycode.
