# CHANGELOG

### 1.0.0 - initial attempt to fix double keystrokes

1. Override originally used sym_eager_pk with asym_eager_defer_pk for better double keystroke prevention + bump default QMK debounce from 5 to 7 ms. And there will be another prebuilt variant with 10ms debounce
2. Remove strange wait_ms timeout call (which was actually used as a hack to fix double keystrokes)
3. Fix definition file for VIA app (both web and desktop) so keys now will be displayed properly (file can be used with both this firmware variant and with official variant as well (at least up to version 1.0.3.6


### 1.0.1 - move to non-nuphy RF driver and sleep logic

1. Debounce set to 10ms and asym_eager_defer_pk is used. This mitigates double keypresses input, while keeping input latency and polling as they should be originally.
One more time, description of this algorithm is the following:

```
Debouncing per key. On a key-down state change, response is immediate, followed by DEBOUNCE milliseconds of no further input for that key.
On a key-up state change, a per-key timer is set. When DEBOUNCE milliseconds of no changes have occurred on that key, the key-up status change is pushed.

```

So it means, that once key pressed - signal is sent to PC, then for DEBOUNCE there will be no repeated input, if key was not release in DEBOUNCE period - key-up event would be sent to PC.

2. RF driver and sleep handler from @jincao1 (many thanks for his job)

3. NKRO toggle fixed, so no auto-nkro from Nuphy, only base implementation from QMK

4. Now repo is based on mainstream QMK, so keyboard files are fully compatible with current QMK releases.


### 1.0.1.1 Fix logo LED not resuming stored values, battery indication

Battery indication now back to official - top left LED color-based.
Logo LED now correctly restores values after power-cycle.


### 1.0.1.2 Fix RF sleep

RF sleep was fixed (unnecessary `keyboard_post_init_user` was the problem).

Sleep timer set to 5 minutes instead of default 6 minutes (weird value)

Again, just in case VIA definition file :)


### 1.0.1.3 - Finally keyboard sleeps (light mode only)

All link modes are using light sleep, battery drain is less than without sleep, but more than in deep sleep.

To make it work it would require much more investigation and digging into implementation. If someone
willing to help - you're welcome to join this journey :D


### 1.0.1.4 Possible fix of RGB matrix misconfiguration (heatmap on space issue)

Possible fix for the RGB leds placement. Requires thorough testing, tbh.

[How it was before](https://discord.com/channels/864389832829567067/1189869383321923646/1220357545995272223) (original firmware and all previous releases of mine varian).

[How it became now](https://discord.com/channels/864389832829567067/1189869383321923646/1220368601157206166)


### 1.0.1.5 RGB matrix layout calculated from scratch

If in terms of RGB effects previous release suits you well - no reasons to do update to this one. In this case it worth to wait for next release.

Note, for some effects (based on center of keyboard for ex. spiral, in/out and some others) you would see, that center is located in the area of "H" key. This is done intentionally, 'because if I would set center to be as it should be geometrical center - then effects would play around "K" key, which is not really visually beautiful.

### 1.0.2 Some improvements & features

There are few features enabled in this release.

#### First things first. Debounce.
Algorithm is returned to `sym_eager_pk` 'cause it allows faster polling rates, while adding latency only if key "bounces".
Debounce time is set to 12ms. If you're not really comfortable with this debounce time - feel free to compile firmware from my repo with adjusted debounce.
From my testing fastest key press-release events I've achieved with 1.1.0/1.1.1 official firmware were like 24-27ms, in current state of mine firmware lowest events are 4-5ms.
Also this debounce algorithm uses less resources, so more space to use additional QMK features.

#### Win lock & scroll lock
While in official firmware, there are no scroll lock indication at all and win lock indicator is strictly bound to top-right key LED I've made some improvements.

Added scroll-lock indication
Both scroll- and win-lock indicators are shown under the key they are assigned to (even if you assign them into non-default layer they will preserve their position).

#### Caps-lock indication

While in mine previous release there was a way to choose how to show caps lock indicator (under key, top-left LED or both) during compile time, I decide to change it.

So from now on there is custom key defined (default placement is FN + Caps Lock) which allows to switch between caps lock indication modes (top-left LED, under key, both, none). This setting is preserved during power-cycles. Default state is equal to original - use top left LED for indication.

#### USB sleep toggle
From intermediate changes I also decide to add a possibility to control USB sleep mode on the fly. By default this button assigned to FN + Backspace. Default state of USB sleep is off.


#### Side thingies
Additionally RF driver was updated by recommendation of @jincao1 I really appreciate your work in this direction!

----

If you're not aware, there is a way to use autocorrection right inside of the keyboard. And as I'm tired of my fingers being slower than my mind, I've added some corrections (developer focused) so I won't be doing that manually anymore. Below you can find what will be corrected to what :) If you want to actually write this typo - you'll have to use ALT or CTRL key right when typo starts for these words.
For example, if you want to actually write fasle you would need either to write fas<CTRL>le or fas<ALT>le I hope you got the idea :D
```
fasle             -> false

fales             -> false
cosnt             -> const
costn             -> const
devlop            -> develop
typoe             -> typo
tihs              -> this
calss             -> class
fitler            -> filter
lenght            -> length

ouput             -> output
widht             -> width
```

** Please keep in mind, you have to use new definition file for VIA's design tab if you want to see proper custom keys names and to be able to assign them**
If you still meet the issue with double keypresses when using this version - please consider using 15ms version. This should be pretty enough. Best part of this algorithm is that even when we go upper with debounce - actual latency changes non linearly and even with 20ms debounce fastest click would be <=10ms which is at least 2.5 times lower than on official firmware.

### 1.0.3 Introduce realtime debounce change

I've copied QMK implementation of sym_eager_pk algo and adjusted it to use debounce (ms) value from eeprom instead of depending on compile-time variable.

Default debounce (after flashing) is 3ms (personal preference). Please adjust it after flashing.

Keybinds are set as the following:
`FN+HOME` - display debounce value (ESC-F9 are 0 to 9 decimal part, if debounce is 12 then F1 would be highlighted, and 1 to 0 are ones, so in case of 12 - 2 would be highlighted)
`FN+PG_UP` - increase debounce by one
`FN+PG_DOWN` - decrease debounce by one

Disabled AUTOCORRECT & CAPS WORD features. I found them interesting, but not useful enough to keep.
Updated VIA definition file with support for new custom keys for control debounce.


### 1.0.3.1 Various sleep adjustments

1. [Fixed] When you put PC/laptop to Sleep/Suspended state and keyboard was in RF mode, on wakeup there would be no RGB at all, until keyboard would be powered off - on.
2. [Fixed] "Stuck" key when keyboard goes off USB sleep mode until you press any key

3. [Added] On-the-fly sleep time adjustments. Value range is between 1 and 60 minutes. Default value is 5 minutes.
`FN+END` shows sleep value (ESC-F9 0-9 decimals, 1-0 - ones, so for 10 minutes sleep F1 and 0 would be highlighted). Highlight color is set to cyan to make it differentiable (at least for a bit) from debounce highlighted values.
`FN+INS` - increase time before sleep by 1 minute
`FN+DEL` - decrease time before sleep by 1 minute
Due to point [2] USB sleep now enabled by default.
To see new keys and to be able to assign them you need to use new VIA definition file in design tab.

### 1.0.3.2 Fix battery indication

As it was found by @weborican during testing of mine firmware there was a bug, that indicator was always showing full battery, while in BT mode host reports proper battery level.
Fixes were implemented and also I've adjusted battery levels to be a bit more informative (by default whole range between 40 and 80 percents was covered by same color).
Here are new mappings:
```
0-20 red
20-40 orange
40-50 yellow

50-80 blue-purpleish idk how to name that, you'll see :smile:
80-100 green
```

### 1.0.3.3 Various fixes for sleep & RF

1. fix: if sleep time was > 10.9 minuts keyboard was sleeping for 10.9m (value overflow)
2. fix: caps lock indicator in RF mode
3. fix: RF mode first key on wake lost (early wake handling)
4. added readme for bindings in keyboard folder (keyboards/nuphy/gem80/ansi/gem80-guide.md and also pdf version, thanks to LitEye for putting effort into it)


### 1.0.4 Maybe major update, maybe not :D

#### What's Changed

1. add MacOS globe key by @SheezChill in https://github.com/ryodeushii/gem80-qmk-firmware/pull/4
2. changes in battery reporting level: now they are consistent 0-20-40-60-80-100 (before of 0-20-40-50-80-100)
3. updated readme in keyboard directory with some useful links
4. setup wired only variant of the keyboard
5. add script `compile.sh` in root directory to compile both wired and wireless versions simultaneously

#### Note

This time there is new custom key (macOS globe key) added, so I'd recommend to upload new definition file in VIA so you'd be able to use this new key.

#### New Contributors
@SheezChill made their first contribution in https://github.com/ryodeushii/gem80-qmk-firmware/pull/4

### 1.1.0 - The Major update

Well, this release is the most interesting one at the moment (at least in my opinion).


First things first, firmware now uses latest QMK changes (state of 2024.04.06).


#### Debounce changes

##### Before

My firmware was using `sym_eager_pk` debounce which basically affects only key press event.


On *key down* - event to host is being sent immediately, then algorithm waits for DEBOUNCE ms to filter bounces and then keyboards sends key up event to host.

##### And now

I've implemented fully asymmetric `asym_eager_defer_pk`.

On key down - event to host is being sent immediately, then algorithm waits for DEBOUNCE_PRESS ms to filter bounces (if no bounces, then it goes to next step straight away). Then on key up - if bounces happen - algorithm waits for DEBOUNCES_RELEASE ms to filter bounces and then sends key up event to host.

> Note: Originally in QMK this asymmetric algorithm is not really asymmetric, because it always uses SAME DEBOUNCE value for both up and down events.

> Note2: Also there were new keys added to control DEBOUNCE_RELEASE value, but not assigned by default. Feel free to assign them yourself :)

#### Keyboard customization (for all custom features) in VIA UI

This is probably the most major change in the firmware at the moment.
I was kinda tired to reconfigure all lights and debounces every time using keyboard, so I decided to implement custom UI for VIA (web & standalone). VIA allows this to be done natively, only some changes in firmware are needed + updates for keyboard definition file.

Now it's possible to configure side & logo lights, debounces (press and release), sleep time, sleep overall and usb sleep in particular and caps lock indication using custom tab in VIA.

##### !!WARNING!! this release requires you to use new definition file in VIA if you want to properly configure your keyboard through it.

After the firmware update & when you upload new definition file in design tab in VIA you can find new tab appeared in bottom-left part.
image

You can find 3 sub-menus there:

* Debounce
* Sleep
* Indicators

Also in Lightning menu there are few more sub-menus added. Originally there was only Backlight one.

And current list is the following:


* Backlight
* Side Light
* Logo Light


Well, in case you will find some issues with this release, feel free to mention me in NuPhy's official Discord channel for gem80 or you can create issue in this repository (if you familiar with GitHub).


### 1.1.0.1 Some fixes

FIX: non-saving keyboard options (technically not loading :D)

### 1.1.0.2 Fixed version with new VIA UI

Fix issue with macOS (layer0) keys receiving random assignments


