Overview
========

This is my personal Numpad (Woodpad) configuration, and my daily driver.

Most of the code resides in my userspace, rather than here, as I have multiple keyboards.

How to build 
------------
make handwired/woodpad:drashna:avrdude

Layers
------
* NUMLOCK: Num pad, locked to NUM LOCK enabled. 
* NAV: Navigation codes without needing to enable numlock. 
* DIABLO: This contains a Diablo 3 layout, that requires much less reaching or shifting. If Tap Dance is enabled, then it has a "spam" feature. See Userspace for details.
* MACROS: This layer contains a bunch of macros for spamming chat, with a toggle on what key to open up chat with. 
* MEDIA: Media and RGB commands

All layers have RGB specific indicators, so you can see what layer you're on by the underglow.

Woodpad Specific Code
---------------------

Aside from my userspace code, this includes LED indications for numlock and macro mode.  It also forces NUMLOCK to be enabled.
