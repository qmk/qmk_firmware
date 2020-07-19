# EndlessReform's Prime_O Keymap

I love small form-factor ortho boards. Their compact size makes them perfect for travel, their grid layout adds vital space to the bottom row, and their reliance on layers allows me to never leave the home row. But occasionally function layers just don't cut the mustard. Sometimes you just need to hit F5 to refresh or F11 to full-screen with one finger, add a number to a key combo without finger gymnastics, or give your wrists a break. That's where the Prime_O comes in. It combines the efficiency of an ortho board, the small form factor of a 65%, the spaciousness of a TKL, and the pronation reduction of a split board. Over my last year with this board, I've tried to exploit these advantages to the fullest. It's the perfect keyboard for programming; here's how I use it:

## Core principles

* Put the most commonly used keys on the strongest fingers
* Encapsulate common actions in as few key strokes as practical
* [KISS](https://en.wikipedia.org/wiki/KISS_principle)
  * Create no macros for text that could just as easily be typed or autocompleted
  * Limit cognitive overhead by keeping mnemonics and metaphors clear and simple

## Base layer

![Base layer](https://i.imgur.com/VIKdqFQ.png)

In my base layer, I've taken full advantage of both the Prime_O's four extra rows and the Planck's five extra bottom row keys:

* I've added an F-row and nav keys in the middle of the board. This has many advantages:
  * My left and right hands are four more units apart, which helps wrist pronation quite a bit. It's most of the ergonomic advantages of a split keyboard with none of the disadvantages.
  * I can hit arrow keys with my thumb. While I still usually use arrows in a function layer (more on that later), this makes keyboard shortcuts with an arrow a cinch (think Win+Left to snap windows).
  * I have physical F-keys. Yes, I know, I can just use a function layer. But often I'm in a mouse-first workflow and just need to occasionally hit an F-key: full-screening a Zoom call, running a SQL script in SSMS etc. At times like this, I really appreciate dedicated F-keys.
* I've doubled up modifier keys. Shifting both my left pinkie and ring finger to hit two modifiers at once throws my entire hand out of place, causing painful stretches and time-consuming breaks in my typing. Using just one finger is far easier and less painful. This makes an enormous difference day-to-day:
  * I put OS+Shift in the left corner key. This is insanely useful both in Windows and Linux:
    * In Windows, so many commands use OS+Shift: Throwing windows to another monitor, opening Windows Explorer...
    * In Linux, I use the [i3 window manager](https://i3wm.org/), which uses the mod key (LGUI) to both arrange open windows with just the keyboard and execute other user-defined shortcuts. Mod+Shift allows me to exit and refresh i3, throw windows to other workspaces, etc. with much less effort, and doubles the amount of available 2-key shortcuts.
  * I put Ctrl+Shift in the right corner key. Now I can open Chrome Inspector, go back a tab, and so on with ease.
* I use the left thumb key as backspace. I only ever type space with my right thumb (bad habit, I know), so   why can't one of my strongest fingers make itself useful? This does, unfortunately, mean that this keyboard is useless for gaming, since there's no spacebar for my left hand to reach. However, that's what I have other keyboards for!
* I love, love, love QMK's tap/hold functionality. It means keys in the most valuable spaces can effectively serve double duty:
  * Control is where it *should* be, right next to A - but now escape can also be where it *should* be, right next to A. Vimmers will understand.
  * My left thumb can make even more use of itself by holding down the navigation layer toggle, meaning that I can use arrows on the home row as long as I want with no fatigue.

## Lower layer

![img](https://i.imgur.com/2upgkH5.png)

This layout is for numbers, function keys, *lower* case tilde and grave, and reset.

Now I know what you're thinking: Why add the F-keys and numbers to the lower layer when they're already on the base layer? Why bury keys like + and -, ~ and \ in a function layer when you have so many keys to spare? Honestly, if my Prime_O were my only ortho board, I wouldn't duplicate the F-keys and would move `:*/+` above the numpad. But this isn't my only board: I have two 40% ortho boards, which use this same keymap to avoid the lack of a R5. It's already a constant struggle to remember what keyboard does what, so I use the same lower for all ortho boards: consistency is worth a little inefficiency

That said, there is some stuff I'm proud of here:

* A built-in numberpad, accessible right on the home row. For typing only numbers, this is infinitely better than either a dedicated number row or a dedicated numpad in the middle or right of the keyboard. (However, this is much worse when you have to combine numbers and modifiers (Mod+1, Ctrl+0 etc), which is why I still use the dedicated base layer number row).
* A-F and X added to the numpad. That way, when I'm typing hex codes, I don't have to waste mental effort constantly toggling between lower and base layers (e.g. 0xF5F5FA).
* A dedicated ``` key for Markdown code fences

## Raise layer

![](https://i.imgur.com/5aT5oX1.png)

This layout is for extended punctuation, media keys, and *upper* (shifted) special characters:

* I write nearly everything in Markdown (Github-flavored, R, and Obsidian) these days, so I've made commonly used characters and key combos easier to hit:
  * Parentheses go under opposite index fingers. This is ergonomically better, but also mnemonically better: Opening paren with my left and closing with my right helps me remember to close parentheses better than just using my right hand.
  * Brackets and braces are easier to hit in a layer
  * There are dedicated double brackets, for [Obsidian](https://obsidian.md/) inter-note linking. I put them above parentheses so I could have the mnemonic "parentheses, but higher"
  * For R Markdown, there's a macro which throws down a code fence and then pulls you one character behind the end brace, allowing you to name the chunk with no extra strokes. This saves so much time because you can't just autocomplete these in.
  * There's also a dedicated Markdown todo macro.
* For straight R, there's two [magrittr](https://cran.r-project.org/web/packages/magrittr/vignettes/magrittr.html) pipe macros: pipe and pipe-assign. Again, these are ordinarily both annoying to type and impossible to autocomplete (there is a keyboard shortcut in RStudio for regular pipe, but `Ctrl+Alt+M` is mnemonically rather weak).
* Again, there's special characters, where they would be as shifted versions of the numbers on the lower layer. Why not just use shift + base layer numbers? Again, ortho muscle memory.

## Nav layer

![img](https://i.imgur.com/FF556Rw.png)

* Vim key 1:1 analogues: HJKL arrows, W and B for word forward and back. This comes in so handy when apps don't have a Vim mode (the horror!)
* D and F: select a whole line to its beginning or end. Very useful when I want to overwrite everything before or after a point but can't just type `c0` or `c$`.
* Select previous or next word: I use this key all the freaking time, usually when I want to delete the last word I wrote or when I want to cut a word for use elsewhere. Together with Ctrl+Backspace (delete last word), this has sped up my typing immensely. 
* A duplicate nav cluster: again, for ortho compatibility reasons.