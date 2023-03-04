# The Zweihander Layout

NB: the backtick (\`) is special in Markdown. If I write ⌘\` in this readme, I mean “Command-backtick”, not “Command-backslash-backtick”.

This README refers to two secondary layers: the Media Layer and the Symbol Layer. The Media Layer is accessed by holding ; (the semicolon) and has cursor-movement, window-management, and volume-adjustment keys on it. The Symbol Layer is accessed by holding either of the two tall keys between T and Y, or by tapping one of the small keys between 5 and 6. It has a 10-key keypad, parentheses and similar grouping punctuation, and F1–F12.

This layout is tuned for people who…

## use macOS

While this layout works fine in Windows, it’s not tuned for it. No sane person who primarily uses Windows would put this many Windows keys on a keyboard layout. That said, Print Screen, Scroll Lock, and Pause are available in their usual order on the Media Layer if you need them.

## mouse left-handed while doing other things with the right hand

I tend to have my mouse in my left hand, but I like to use my other hand to make things go faster. I’ve added a bunch of buttons to the Media Layer (hold ;) to speed up browsing in applications like Safari and Finder:

- ⌘[ — Back
- ⌘] — Forward
- ⌥⌘↓ — Open Selection and Close Parent Folder
- ⌥⌘↑ — Go Up and Close Just-Left Folder

I also have a few keys dedicated to window management:

- ⌘W — Close Window
- ⌘\` — Move Focus to Next Window
- ⌘⇧\` — Move Focus to Previous Window

Cut, Copy, and Paste (⌘X, ⌘C, and ⌘V) are also available on the three bottommost right-thumb buttons if you hold ;.

## use lots of modifier keys in macOS menu-item shortcuts

I wanted to preserve the feel of a number of shortcuts that involve pressing lots of modifier keys at once. This is why the bottom left of the keyboard has Shift, Control, Option, and Command in the usual spots. Further I’ve added affordances so some key combinations are easier to press with just the right hand.

I also put a second Backspace (⌫) key on the right half of the keyboard to make some particularly commonly-used keyboard shortcuts faster and more convenient for right-handed use:

- ⌘⌫ — Move to Trash / Delete
- ⇧⌥⌘⌫ — Empty Trash Without Asking for Confirmation

⇧⌥⌘⌫ is much more satisfying to press when you do it like on a normal keyboard: one left-hand finger on each of ⇧, ⌥, and ⌘, and the right index finger on ⌫.

Pressing and holding / will give you Option. This makes a number of keyboard shortcuts easy to press with just the right hand:

- ⌥↑ — Move Line Up   (in Visual Studio Code)
- ⌥↓ — Move Line Down (in Visual Studio Code)
- ⌥⇧↑ — Copy Line Up / Go To Previous Channel With Unread Messages
- ⌥⇧↓ — Copy Line Down / Go To Next Channel With Unread Messages

## use Emacs-style shortcuts

I press C-a, C-e, and C-k all the time. It’s difficult to press these key combinations with the Control key on the far left, so the innermost thumb buttons are Control keys. Above/inside them are Option keys.

## use Visual Studio Code

;-W and ;-R are bound to ⌥↑ and ⌥↓, respectively, for moving lines up and down in Visual Studio Code. In normal macOS applications, they’re used for moving the cursor to the beginning and end of a line, and then on to the previous/next line.

## use spreadsheets

All the common spreadsheet operations (+-*/=) are on the right side of the Symbol Layer. Make-numbers-bigger (+, \*) operations on the right; make-numbers-smaller (-, /) on the left. There’s also a colon there for entering times and maybe IPv6 addresses.

## know the ↑↓←→ fn-key shortcuts for MacBooks

Have you looked at the Page Up, Page Down, Home, and End keys on the EDSF keys and wondered why they’re arranged that way? They’re arranged the same way as the fn-key shortcuts on an Apple laptop’s arrow keys. On Apple keyboards with an\* fn key, if you press fn-↑, you’ll get Page Up; if you press fn-← you’ll get Home. Similarly, on Zweihander, ;-E is Page Up and ;-S is Home.

## write a fair bit of Markdown

If you’re on the second layer (hold/tap one of the four inside middle top keys), the `'` button on the far right is a `\`` key.

If you’re on the second layer, pressing `v` will send the string `"\n- "`, not including the quotation marks. This is intended to be a faster way to make a new list item when writing meeting notes in Markdown.

## use Siri

F16, accessed by holding ; and pressing the ' key next to it, is intended for Siri.

## use the fn/🌐︎︎︎ key

A thumb key is bound to Caps Lock. You are not expected to use this for Caps Lock. You would probably be happier going into System Settings, opening the “Customize modifier keys” part of it, and having Caps Lock work as the fn key. macOS is convinced that Ergodoxen EZ have fn keys, so you might as well have one in a place that lends itself tolerably well to keyboard shortcuts.

## use it with an iPad

This layout overrides `USB_MAX_POWER_CONSUMPTION` to turn it down to 100 mA instead of the default of 500 mA. This is not what you want if your Ergodox EZ has the Shine or Glow lights, but good if you want to be able to plug it into your iPad’s lightning port with a USB adapter. The indicator lights that tell you what layer you’re on are _not_ Shine or Glow lights.

\* I pronounce “fn” as “effin’”. Your mileage may vary.
