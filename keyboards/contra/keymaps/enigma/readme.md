# A Contra Layout with an Enigma Emulator

```

,-----------------------------------------------------------------------------------.
| Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Ctrl |  Fn  | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
`-----------------------------------------------------------------------------------'
```

By default, this layout functions like a normal QWERTY layout. But it also has an in-built Enigma machine emulator.
To enable the emulator, press `Fn+.`, and to go back to QWERTY, press `FN+,`.

A demonstration video can be found [here](https://youtu.be/p8kBjP1DCzo).

When Enigma mode is enabled, all letters A-Z will be enciphered using the Enigma emulator. Other keycodes will not be modified. Shift will be sent as normal, so you can choose whether to capitalize the output. If any other modifier (Ctrl, Alt, or Gui) are being pressed, the normal letter will come through.

There are a few key combinations for configuring and diagnosing the Enigma emulator:

* `Fn+Q` resets the emulator to the last-configured settings
* `Fn+W` types out the current Enigma settings, e.g. `B. IA-IIA-IIIA (A, A, A) QW` (meaning reflector B; rotors I, II, and III all at ring setting A; all at position A, and with Q and W swapped on the plugboard)
* `Fn+P` types out 1000 enciphered As, for testing
* `Fn+Backspace` back-rotates the rotors one step, for fixing typos without having to re-type a whole message
* `Fn+Z` followed by A, B, or C is used to set the reflector
* `Fn+X` followed by three characters A-E is used to set the rotors
* `Fn+C` followed by three characters A-Z is used to set the rotor positions
* `Fn+V` followed by three characters A-Z is used to set the ring settings
* `Fn+B` followed by up to 13 pairs of characters A-Z (one at a time, not simulaneously) then the Enter key is used to set the plugboard


