enum layers {        // Hacker Dvorak keyboard layers:
    DVORAK   = 0,    //   * Dvorak base layer.
    PLOVER   = 1,    //   * Steno layer for use with Plover.
    GAMING   = 2,    //   * Gaming layer intended for general purpose playing.
    ARROWS   = 3,    //   * Arrows movement keys and edition shortcuts.
    MOUSE    = 4,    //   * Mouse movement keys and edition shortcuts.
    NUMPAD   = 5,    //   * ATM style numpad with symbols and letters that should suffice to input any numeric literal.
    LAYERS   = 6,    //   * Layer switcher used to change between DVORAK, PLOVER and GAMING layers.
    MEDIA_FN = 7,    //   * Media, RGB and function keys from F1 to F24 in symmetric fashion.
    HYPER    = 8,    //   * Hot keys layer (uses hyper + F1 .. F24) suitable for global shortcut tasks.
    FIRMWARE = 9     //   * Layer with firmware related functionality, like the reset and EEPROM keys.
};
