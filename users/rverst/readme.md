# Overview

This is my user space, main goal is to unify the experience between different 
keyboard models and operating systems.
My native language is German and I almost exclusively use keyboards in the
US-ANSI layout. I find this layout the most practical for programming as
far as the placement of special characters is concerned. However, when I write
in German, I miss a few special characters like umlauts, etc.
Since I also use different operating systems (MacOS, Linux and Windows)
and especially Windows and MacOS behave very differently regarding the input
of such characters (under Linux there is at least the Compose key).
So I needed a hardware solution, and that's how I came to QMK.

Here are defined some key codes to put the keyboard in different modes
(Mac, Windows, Linux) and the corresponding functions to make the input.
And some logic to store the respective mode and load it at boot time.

You'll find a proper layout here: [keyborads/id80/keymaps/rverst](../../keyboards/id80/keymaps/rverst)
