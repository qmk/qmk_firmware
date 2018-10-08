Legonut's RGBKB workspace

Need some help with rotary encoders right now, I can't seem to get the split code and rotary encoder stuff working. Here's the details:
The rotary encoder is on pins D6 and D4. The serial connection is on pin D3 (INT3)
The rest of the pin assignments/stuff can be found in the Sol keyboard folder.

Right now, I've got a modified version of the knob_macro_pad working with the rotary encoder. It's simplified and doesn't have all the code Sol needs, but it proves that the hardware does work with the encoder. I've tried adding the serail code to this, with no luck (i also don't really know what i'm doing lol)

I've been trying to work with lets_spilt/keymaps/anderson, which seems to be a working let's split mod with rotary encoders. I modified this to use Sol's pin assignments, and somehow, when I turn the rotary encoder, the keyboard crashes. Any idea there?

Any help is greatly appreciated!