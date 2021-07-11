# Massdrop Ctrl Endgame

This keymap is here to show some love to the MD Ctrl.

## Layers

### Typing Layer

![Typing Layer](https://imgur.com/QUIU2SL.png)

### Function Layer

![Function Layer](https://imgur.com/4q4ld4X.png)

### Mouse Layer

![Mouse Layer](https://imgur.com/xXVFyEE.png)

### Git Layer

![Git Layer](https://imgur.com/WMMM0zz.png)

## Features

These are the features currently supported by this keymap:

### RGB Time Out

This allows setting a dynamic timeout for RGB to turn off. The following is supported:

1. Restores on the first click of any key.
2. Restores to its previous state before timeout. i.e. if it was edge only before timeout it will restore to edge only, same for all modes.
3. Doesn't interfere with RGB modes. You can set keyboard to All, Edge Only or Off and timeout will not interfere with these modes.
4. The time before RGB is turned off is dynamically adjustable using keycodes ROUT_VI to increase, ROUT_VD to decrease. They have a 10 second steps by default. Minimum value 10 seconds by default and maximum is 10 minutes.
5. Can be toggled on or off dyncamically with the ROUT_TG keycode.
6. Can be put in fast mode using ROUT_FM, for movie watching purposes. Default value is 3 seconds. Note that fast mode disabled ROUT_VD and ROUT_VI so to use them again you have to toggle fast mode off with ROUT_FM. It doesn't impact ROUT_TG and ROUT_TG will remember if fast mode was enabled when toggled back on, so it doesn't disable fast mode on its own, only ROUT_FM can disable or enable fast mode.

### Tapdance Keys

Not really a feature. I just want to document what tapdance keys this keymap has because there will be many of them.

1. LGUI is used for both LGUI and toggle mouse layer for double tap.
2. LCTRL sends LCTRL for single tap and LCTRL+LALT+T for double tap, which opens terminal in most environments.

## Future Work

By the time this is project has accomplished its original primary objectives, the following features will be available for the ctrl:

1. Automatic RGB timeout with all the options you would need. **DONE**
2. Macro and Shortcut layers for at least the following: Git **DONE**, IntelliJ, VIM **WIP**, Yakuake, KDE, Firefox, Slack, Discord. All using default program configuration. [This list may and probably will get longer]
3. Custom LED configs that offer all the RGB layouts I deem useful or having a unique feature, look or feel. **DONE**
4. Increased Dynamic Macro slots, because two simply isn't enough. This particular one falls outside Ctrl config and into QMK core modification. However, it is on the list of features I would like this keyboard to have and is a **TOP PRIORITY** for me. It won't be easy, but I will figure it out.
5. Porting from the Drop, Inc. way of doing things to the QMK way of doing things, wherever possible. Full QMK support of this keyboard is the goal, not that it's possible, but I'd like to get as close as it gets. **WIP**
6. An easier way to configure LED than both the QMK way and the Drop way. I'm thinking of a graphical LED config like Drop configurator that offers the advanced LED config features QMK offers. This may or may not get done depending on whether or not I get sick of QMK LED config at any point. If it does get done, it may or may not be added to QMK Configurator.
7. Better documentation of the MD Ctrl specifications, features, etc. This will be included here in the form of C and doxygen comments. The bigger portion will be included in QMK docs if and where possible. **WIP**

Additions:

8. Implement Raw HID. **WIP**

This list will most probably either expand or have some items removed if they're deemed not worthy, probably both. Nothing will be removed because it can't be done though, I am a firm believer in You Can Do It. Anything modified in this list will be clearly marked, for posterity.

## Motivation

I bought this keyboard because I believed and still believe that it offers the greatest possible value for money for any TKL fan. It was very disappointing to me after receiving it to see that this keyboard didn't get the love it should have in QMK, from either Drop, Inc. or users.
Granted, this is a TKL RGB board which means it is hated by every single enthusiast in the community. That doesn't mean it shouldn't be getting love form its users, or most importantly its maker.

Drop, Inc. have for some reason decided that they want to work on their own QMK stack. A stupid decision to say the least. Although having made this decision, they did very little actual work on this keyboard and have offered very little support and almost no time working on the firmware. To my knowledge, no one is currently working on it in a truly active fashion. A small handful of people work on the software and even then, they seem to think that their own way of doing things is better than the way chosen by the thousands in the community who have worked on QMK. Their QMK fork for the keyboard is abandoned for months. Updates are few and far between and it seems this keyboard has been forgotten in the annals of 2018 by both its maker and its users.

To their credit, at least they decided to abandon their idiotic RGB setup and have opted after taking their sweet time to use QMK RGB and they did make some much needed changes to mdloader. That being said, Drop, Inc. still don't show love to this keyboard and whether or not they are actually able is questionable.

So the aim of this work, starting with this Keymap, is to make the Massdrop Ctrl a true QMK keyboard instead of the marketing spiel "QMK Supported". As much as it can be made so of course within the bounds of what can be done with information openly available about the keyboard.

I am not of the opinion that a mechanical keyboard is inherently superior. I am of the opinion that a mechanical keyboard is a tool that boosts productivity, enjoyment and efficiency, if it fails at that then it is no longer superior. Programmability is a huge part of that and I can no longer use any keyboard that doesn't have a level of programmability less than  QMK offers.

I will personally do my best for this keyboard for no reason other than it will likely be my main keyboard for years to come.

## Credits

RGB timeout functionality was originally inspired by the code in this [gist](https://gist.github.com/algernon/9182469e21894192017f2bb5d478c7df).
LED config code was mostly transferred from [matthewrobo keymap](https://github.com/qmk/qmk_firmware/tree/master/keyboards/massdrop/ctrl/keymaps/matthewrobo).

Rest of the information about RGB matrix, scan matrix, and whatever information I have used was made publicly available by many other awesome members of the community.
