cbbrowne custom keyboard
==============================

Due to cbbrowne@acm.org
Christopher Browne

This was originally based on the default keyboard map, but I have been
doing sundry experimentation:

 * To figure things out about the toolset
 * I'm an Emacs guy, so will be needing a fair bit of tuning
 * It made sense to mess around some with keyboard maps.
   - I tried added Workman alongside Dvorak and Colemak
     - Boy, oh boy, these don't help!!!
     - I have done 30 years of learning of Emacs key mappings, and
       these alternative keyboards massively mess me up
   - I added a keypad, originally based on keymaps/numpad.c, but
     mighty substantially revised, as that one seems to be rotated 90
     degrees from usual conventions for number pads
 * The keypad layer also includes some sample "hacks" of cool things,
   all using actions attached in using the function action_get_macro()
   - Key [1][2] aka "q" types out my name, cbbrowne, as a fun example
     of a key generating a bunch of keystrokes.  The keystroke is
     sufficiently inconvenient that it isn't terribly practical for me
     to use it, but hey, it shows how others might use this facility
     in a more useful context.
   - Key [2][2] aka "a" uses a random number generator to select a digit 0-9 at random
   - Key [3][2] aka "z" uses a random number generator to select a letter a-z at random	 
