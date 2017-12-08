##Design goals:
1. Arrow keys always available.
2. As close to a to my US layout 107-key QWERTY keyboard as I could manage, (i.e. as few arbitrary decisions as possible).
3. Togglable DVORAK keyboard.
4. most frequently used things in the easiest to reach places.
5. Ability to game on it, just for fun.

My layout differs from most in the placement the ARROW keys, `ESC`, VOL keys, use of double-tap `CAPS`, and the GAME LOCK function.

I put the layer buttons in the usual spots. I originally wanted only function/symbols layer, but that proved detrimental. I use some timed press actions to save some space, but this has been accounted for, (see GAME LOCK below). I'm not fully satisfied with the current product (see NOTES below), so it may change in the future.

##Effective layers:
* Default later is obviously your letters and modifiers.
* Lower layer [NUMBER] is your numbers and punctuation.
* Upper layer [ACTION] is your symbols and actions.
* Function layer is the infrequently used function keys, layout toggle, game lock, and reset.

There is also a toggle for the DVORAK/QWERTY layers, but in normal typing this is not of concern.

###Special keys:
* `RSHFT` and `ENTER` are combined. Tap once for `ENTER` and hold for `RSHFT`. `ENTER` will be registered on release if released within 200 ms, else `RSHFT` is registered starting at 201 ms until release.
* If for some reason, this interferes with the normal usage of the `ENTER` key in any way, (some problem that may never happen), I have added a regular non-modified `ENTER` key on the same key in the [ACTION] layer.
* `LSHFT` and `CAPS` are also combined. The key works like a normal `LSHFT` unless double-tapped, in which case it counts as `CAPS`. This functionality unfortunately delays all key presses by at most 200 ms, but I have added ways to disable this both temporarily or permanently, described below.
* A failsafe `CAPS` key is on the same key in the [ACTION] layer.
* There are `UNDO`, `CUT`, `COPY`, and `PASTE` keys. This was intended to be a universal way to use these commands since in macOS cut is `⌘ + C` but in Windows it is `⌃ + C`. Unfortunately these special keys only work in Windows. ¯\\\_(ツ)\_/¯

##Game lock:
**TL;DR** the game lock toggle disables the double-tap `CAPS`, and disables `GUI` keys (WINDOWS key).

I wished for this keyboard to be fully usable in the most demanding of games. The most demanding game I know of is ARMA 3 which has a binding to practically every individual key of a 107-key keyboard. This means I need to have pretty much every key possible somewhere. I also wanted the keyboard to be responsive in games for every critical keypress. This means having a way to disable features that introduce an inherent delay to registering keys, such as double-tap.

I do not expect to see this used by the pros, but I enjoyed making it. As for use in ARMA 3, I got a little ways into the APEX campaign, but I found a few flaws. For Example, I cannot enable my HUD GPS since that requires `RCTRL`+`M` but `RCTRL` is not bound. The obvious fix is to rebind the action to a new key, but I still take this as a shortcoming of my layout.

###If you wish to disable double-tap
####Disable it temporarily
Turn on the game lock. While on, it registers as normal `LSHFT` and has no delay. Whether in game mode or not, `CAPS` is on the same key in the [ACTION] layer.

####Disable it permanently
Open the `Makefile` and set `TAP_DANCE_ENABLE = no`. I wrote the layout to compensate for this change, and no further changes to the code should be necessary. Whether or not it's disabled, `CAPS` is on the same key in the [ACTION] layer.

##Notes:
* `ALT` and `GUI` are reversed compared to the normal US layout. I will also be using my Planck on my mac, and that's the standard in the Apple ecosystem. I may add a special compiler flag in the future to swap the two.
* The DVORAK `Z` key is to the right of the `S` key instead of under it as part of a compromise I made to keep the ARROW keys available on the default layer. I prioritize the ARROW keys, so the DVORAK layout is the one to suffer.
* I also support the little tones that the default Planck layout features, identical to them too, (minus those for layouts I don't support). To enable it, open the `Makefile` and set `AUDIO_ENABLE = yes`.

![keyboard-layout](https://i.imgur.com/HHSZSQq.png)
