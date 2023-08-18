# Brauner's Preonic Keymap

This is a keymap layout heavily optimized for vim.
It mostly follows `QWERTY` but moves various symbols on to different layers.

* Number keys function only as number keys.
  Additional symbols they would produce when `Shift` is held are turned off as they are intercepted.
* `Y`, `P`, and `X` function as `Ctrl+C`, `Ctrl+V`, and `Ctrl+X` when held.
  This avoids having to hold down `Ctrl` and also aligns regular copy and paste with vim functionality.
* Various keys perform different functions when tapped than when held.
* `!` and `?` are on top of `.` on different layers.
* `\` and `|` are on top of `/` on different layers.
* `:` and `;` are on top of `,` on different layers.
* All navigation is done via `H`, `J`, `K`, and `L`.
* `O`, `U`, `S`, and `A` produce the Umlauts `Ö`, `Ü`, `ß`, and `Ä` when held.
  This relies on the operating system keyboard layout to be set to US Intl.
* Different layers will activate different types of navigation.
  For example, left, right, up, and down or backspace, page up, page down, and tab.
* There's a dedicated mouse layer which can be activated allowing to navigate solely with the keyboard where otherwise a mouse or trackpad would be needed.
* There's a dedicated management layer where the boot loader can be entered or music mode can be turned on or off.
* Lastly, there's a compositor layer which is optimized for managing a tiling window manager.
  The layer is used specifically via layer-mod keys in the base layer.
  In other words, specific modifiers are held when this layer is accessed.
* Opening and closing brackets are always located on adjacent keys on the same layer.
  Pressing a matching opening and closing bracket key at the same time will insert both brackets and move the cursor into the middle of the bracket pair.
  As should be obvious, this is useful when programming: `(|)`, `[|]`, `{|}`, `<|>`.
