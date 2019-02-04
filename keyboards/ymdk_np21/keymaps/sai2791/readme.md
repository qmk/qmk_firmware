#additional readme to program on a mac using mac os 10.13

I had lots of problems getting this keyboard to be programmable on a mac, I gave up on
make ymdk_np21:<layout>:program because it was complaining about a missing Python
module pyusb

This is how I got it working after a fashion.

This was taken from the ymd75 directory.

$ brew cask install crosspack-avr
$ brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb
```

You can just build it and flash the firmware directly with
`bootloadHID` if you boot the board while holding down `Left Control` to keep it
in the bootloader:

```
$ make ymdk_np21:<layout>
$ sudo bootloadHID -r <generated file>.hex
