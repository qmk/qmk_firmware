# OLED tester

Available commands using a single key:
- Single tap: Switch to the next test pattern.
- Single hold: Switch to the next orientation (note that 90° and 270° orientations may not work correctly with some displays).
- Double tap: Toggle horizontal scrolling of the top row.  Note that this scrolling is implemented by the controller and has major limitations: it works only with SSD1306-based displays, blocks all display updates, may not work correctly if the display width is less than 128 pixels, and does not handle 90°/270° rotation properly.
- Tap and hold: Change scrolling speed (because of controller limitations, scrolling needs to be started again manually using a double tap).
- Triple tap: Start or stop the update speed test.  This test repeatedly fills the display with all-on and all-off pixels, measures the time required for updating the display, and prints the measured values to the HID console every 256th refresh.
- Double tap and hold: Switch between the “draw once” (default) and “draw always” modes.  The “draw always” mode means that `oled_task_user()` redraws the whole picture completely every time it is called; the example code in the OLED feature documentation is written in this style.  Testing the “draw always” mode can uncover bugs in the implementation of drawing functions (they must not set the dirty mark if the buffer content is not actually changed).

Available test patterns:
- QMK logo (clipped to fit on the display).
- Fill the whole screen with as much unique characters as possible (all 94 printable ASCII characters are used, and if the display has more character positions available, the same characters are printed again, but inverted).
- “Slow update” test — instead of updating the whole screen at once, draw things piece by piece to uncover display update bugs.  The drawing sequence used by this test:
  - Fill the whole screen with printable ASCII characters (similar to the previous test, but characters are drawn one by one with 250 ms intervals between them, and inverted characters are not used to avoid obscuring the next phases).
  - Draw a frame along the screen edges, starting from the top left corner and going down along the left edge, then along the bottom, right and top edges, with 50 ms delay after every pixel.
  - Repeat the same sequence again, but with the character sequence shifted by 1 character (so that the updates would be visible).
- All pixels on.
- Pixels at the edges of the screen on.
- All pixels off.
- Horizontal on/off 1px lines (two variants - starting from on or off state).
- Vertical on/off 1px lines (two variants - starting from on or off state).
- Checkerboard pattern (three variants - 1×1, 2×2, 4×4 pixels).
