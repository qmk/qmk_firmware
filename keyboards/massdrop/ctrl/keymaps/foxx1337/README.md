# Massdrop CTRL default layout with raw HID protocol

This represents my current layout, with filtered out effects, personal defaults,
added inactivity timeout (for rgbmatrix) and a HID protocol example.

To test that this is working, there's a user application I'm using to help with
development on [my GitHub](https://github.com/foxx1337/rawhid_io).

Currently all the HID operations defined in the protocol are callable from the
user application:

- hello: gets the string "CTRLHID 1.0.0"
- lights: toggles the rgbmatrix on/off
- led n #RRGGBB: colors the specified led. Valid n from 0 to 117 (87-117 are on
    the edge)
- leds start #RRGGBB #RRGGBB #RRGGBB ...: colors the range of leds from start
- mode n: switches to the specific rgbmatrix mode. Use the last one, 11, to test
    the led operations listed above
