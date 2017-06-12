# smt's TV44 keymap

This keymap is based on a combination of my Planck keymap and [jeebak's TV44 layout](https://github.com/qmk/qmk_firmware/tree/master/keyboards/tv44/keymaps/jeebak). I removed the macros and TouchCursor/MouseCursor layers, because I'm just not ready for that level of mind-mapping.

I had been using something close to the default Minivan layout, but after spending a bit of time with the Planck and Preonic, I decided it would be better for me to try to standardize to some degree, where possible.

Also, it's worth noting that my Minivan is one with the "arrows" layout, which has a 45th key, so I had to define a new KEYMAP_TV45 macro in config.h. In spite of this, the 45-key Minivan is still technically considered a "TV44" as far as I know.

![smt's TV44 keymap](https://i.imgur.com/Y4n6eHj.png)

## Notable features (most of which can be found in my or jeebak's respective keymap file):

1. **Shift/Enter**

    I use both the left and right shift keys when I type. When I want to modify a key with shift, I hold shift with the hand opposite the one typing the key. In the default keymap, Enter is where shift would be on a standard keyboard layout. Oh, muscle memory.

    Thankfully, QMK supports [mod-tap](https://github.com/jackhumbert/qmk_firmware/wiki#fun-with-modifier-keys) keys, and this allows me to set the Enter key to send a modifier (MOD_LSFT) when held, and KC_ENT when tapped. Awesome!

2. **Hyper/Tab**

    This key modifies with "Hyper" (see [Brett Terpstra's post](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/) on this) when held, and outputs the code for Tab when tapped. On the Mac, I use KeyboardMaestro to remap my hyper-keys to do a lot of crazy things.

3. **Ctrl/Escape**
    
    I set up another mod-tap, this time for the Escape key that would act as a Control modifier when held.
    
4. **Alt/Backtick**

    I don't currently have LEDs on most of my keyboards, and I certainly don't want LED controls on the base layer of a 40%.

    So, why use backtick in the lower left corner? I use it as my tmux prefix key, so I need to type it more frequently than most people. Putting it on the base layer works well for my use case, and it's consistent with where I place it in my Planck and Preonic keymaps.

    I also like Alt in that position, so it works well as yet another mod-tap key.


## Layers

### Qwerty

```
,---------+------+------+------+------+------+------+------+------+------+------+---------.
|Hyper/Tab|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  Bksp   |
|---------`------`------`------`------`------`------`------`------`------`------`---------|
| Ctrl/Esc |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '    |
|----------`------`------`------`------`------`------`------`------`------`------`--------|
|   Shift   |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Sft/Ent|
|-----------`------`------`------`------`-----'-------`------`------`------`------`-------|
|  Alt/` |   GUI   |  Lower |    Space     |    Space     |  Raise  | GUI  | Alt  | Ctrl  |
 `-------+---------+--------+-----^^^------+-----^^^------+---------+------+------+-------'
```

### Colemak

```
,---------+------+------+------+------+------+------+------+------+------+------+---------.
|Hyper/Tab|   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  Bksp   |
|---------`------`------`------`------`------`------`------`------`------`------`---------|
| Ctrl/Esc |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |   '    |
|----------`------`------`------`------`------`------`------`------`------`------`--------|
|   Shift   |   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Sft/Ent|
|-----------`------`------`------`------`-----'-------`------`------`------`------`-------|
|  Alt/` |   GUI   |  Lower |    Space     |    Space     |  Raise  | GUI  | Alt  | Ctrl  |
 `-------+---------+--------+-----^^^------+-----^^^------+---------+------+------+-------'
```

### Dvorak

```
,---------+------+------+------+------+------+------+------+------+------+------+---------.
|Hyper/Tab|   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  Bksp   |
|---------`------`------`------`------`------`------`------`------`------`------`---------|
| Ctrl/Esc |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |   -    |
|----------`------`------`------`------`------`------`------`------`------`------`--------|
| Shift     |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Sft/Ent|
|-----------`------`------`------`------`-----'-------`------`------`------`------`-------|
|  Alt/` |   GUI   |  Lower |    Space     |    Space     |  Raise  | GUI  | Alt  | Ctrl  |
 `-------+---------+--------+-----^^^------+-----^^^------+---------+------+------+-------'
```

### Lower

This is where I put the number row, two numpad clusters, common arithmetic operators, and cursorkeys: Arrow cluster, Home/End, Page Up/Page Down. `0` and `$` are also placed on the left side for convenient access to beginning-of-line and end-of-line Vim commands. BRITE has been moved here from the base layer.

```
,---------+------+------+------+------+------+------+------+------+------+------+---------.
|   0     |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   Del   |
|---------`------`------`------`------`------`------`------`------`------`------`---------|
|   $      |   4  |   5  |   6  |   .  |   +  |   *  |   4  |   5  |   6  |   .  | PageUp |
|----------`------`------`------`------`------`------`------`------`------`------`--------|
|   =       |   7  |   8  |   9  |   0  |   -  |   /  |   1  |   2  |   3  |  Up  |PageDn |
|-----------`------`------`------`------`-----'-------`------`------`------`------`-------|
|  Brite |         |        |    Home      |     End      |         | Left | Down | Right |
 `-------+---------+--------+-----^^^------+-----^^^------+---------+------+------+-------'
```

### Raise

As a developer, it makes the most sense for me to group all the commonly-used symbols that don't fit on the main layer. In particular, having the dual-column of parens-braces-brackets helps me keep them straight. I've dropped basic media controls onto this layer as well.

```
,---------+------+------+------+------+------+------+------+------+------+------+---------.
|   ~     |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   Del   |
|---------`------`------`------`------`------`------`------`------`------`------`---------|
|   F1     |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   ?  |   +  |   {  |   }  |   |    |
|----------`------`------`------`------`------`------`------`------`------`------`--------|
|   F7      |  F8  |  F9  |  F10 |  F11 |  F12 |   -  |   /  |   =  |   [  |   ]  |   \   |
|-----------`------`------`------`------`-----'-------`------`------`------`------`-------|
|  Brite |         |        |     Play     |     Next     |         | Mute | Vol- | Vol+  |
 `-------+---------+--------+-----^^^------+-----^^^------+---------+------+------+-------'
```

### Adjust (Lower + Raise)

Utility layer. There isn't much here; it's mainly for swapping the default keymap between Qwerty and Dvorak, or putting the keyboard into flash mode via the Reset key.

```
,---------+------+------+------+------+------+------+------+------+------+------+---------.
|         | Reset|      |      |      |      |      |      |      |      |      |   Del   |
|---------`------`------`------`------`------`------`------`------`------`------`---------|
|          |      |      |      |      |AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |        |
|----------`------`------`------`------`------`------`------`------`------`------`--------|
|           |      |      |      |      |     |       |      |      |      |      |       |
|-----------`------`------`------`------`-----'-------`------`------`------`------`-------|
|        |         |        |              |              |         |      |      |       |
 `-------+---------+--------+-----^^^------+-----^^^------+---------+------+------+-------'
```
