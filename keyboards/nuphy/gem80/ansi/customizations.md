# Non-Stock Customizations & Fixes

The following customizations/changes/fixes were applied on top of NuPhy's stock firmware. It includes various personal enhancements and bug fixes.

## Customizations

- `Fn + B` when held temporarily displays the current battery percentage on the F and number row.
The F row represents the 10s percentage and number row the ones. Example, 35% will light `F3` and `5`.
- `Fn + \` turns on percent battery display as well as the stock side LED indicator. Side LED battery gauge steps are enhanced, turning off 1 LED every 20%.
- Battery indicator colours: green for 100% to 81%, yellow for 80% to 41%, orange/amber for 40% to 21%, and red for 20% and below.
- `Fn + M + Z` to toggle the RF disconnect sleep timer between `5s` and `120s` (NuPhy default). Default is set to `5s`. This persist through restarts.
This sets how long the board tries to connect (left light blinking) before giving up.
- `Fn + M + S` toggles idle sleep timer between `30s` and default `360s`. This is temporary.
- `Fn + M + D` toggles QMK debugging. Don't turn this on when not connected to QMK toolbox.
The letter `D` will light up red when enabled.
- Side indicators will flash red for 0.5s when board enters sleep mode, as an indicator.
This is a deep sleep state. It only happens if the board is not charging, otherwise the board enters a light sleep state with no indicators.
- Bluetooth connection indicators will be lit blue when establishing connection. This lights the corresponding
BT mode key. No indicator for RF as the sidelight is a different colour.
- Default startup LED brightness set to zero and side led set to lowest brightness. This is because I don't use LEDs so I don't need to toggle them off when resetting the board or flashing new firmware.
- 3ms debounce instead of 2ms (potential stability)

## Fixes

- Fix keyboard randomly crashing/freezing.
- Fix keyboard not sleeping properly and draining battery. This version sleeps the processor and uses almost no battery on sleep.
- Fix LED lights not powering down when not used. This increases battery life around 50-70% when LEDs aren't used.
- Fix keystrokes being lost on wake. Wake keystrokes will appear after a very short delay while board re-establishes connection. BT wake keys may not be as reliable as the 2.4ghz dongle.  
  This is achieved through a buffer of 64 key actions (key down and key up are 2 actions). The buffer is cleared if connection is not established within 1s after the last action.
  Key events after the buffer is full will also be dropped.
- Enhance keyboard reports transmission logic to greatly reduce stuck/lost key strokes. It may still occasionally drop/repeat keys but it's rare.
- Slightly enhanced sidelight refresh intervals for smoother animations.
- Reduced unused side LED tables to save a chunk of memory. This may be essential to the RF queue as the board only has 16kb memory available - the queue alone uses over 1.2kb.

## Author

[@jincao1](https://github.com/jincao1)