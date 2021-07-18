# README

## About

This is a custom combo engine. I call it chording engine mostly to differentiate it from QMK's combos. It is useful even if you are not using chording as a main input method to replace combos.

Why does this exist? Typing on tiny keyboards can be challenging and you will end up relying on dances and / or combos. Pure QMK combos can be insufficient as they do not really support overlapping combos. For example, if you define 3 combos `(KC_Q, KC_W)`, `(KC_Z, KC_X)` and `(KC_Q, KC_W, KC_Z, KC_X)` and press Q, W, Z and X at the same time, all three combos will activate. Steno engines (and g Board Industries' custom steno inspired engine) solve this, however, they don't allow for comfortable typing in the traditional way. The steno chord activates only when *all* keys are lifted and makes it difficult to implement some advanced features. This engine treats each chord independently to allow for more comfortable typing experience.

## TOC

- [README](#readme)
  - [About](#about)
  - [TOC](#toc)
  - [Start here](#start-here)
  - [Steps](#steps)
  - [Features](#features)
    - [Chords](#chords)
    - [Tap-Dance](#tap-dance)
    - [Pseudolayers](#pseudolayers)
    - [Control chords](#control-chords)
  - [Settings up JSON definition](#settings-up-json-definition)
    - [Keyboard and engine parameters](#keyboard-and-engine-parameters)
    - [Pseudolayers](#pseudolayers-1)
    - [Supported keycodes](#supported-keycodes)
    - [Leader Key](#leader-key)
    - [Extra code](#extra-code)
  - [Further details](#further-details)
    - [Implementation](#implementation)
    - [Internal keycodes](#internal-keycodes)
    - [Chords](#chords-1)
  - [Caveats](#caveats)

## Start here

This engine therefore uses python parser that translates a JSON definition of keyboard specific information and keymap definition and produces `keymap.c`. Every function on this keymap is a chord (combo). The resulting keymap file is long and I do not encourage you to edit it. All you should have to edit is the JSON file. To produce the keymap file, run

```sh
./parser.py keymap_def.json keymap.c
```

To prepare the keymap JSON definition, you can use on of my keymaps as a starting point. I have on for butterstick and for georgi. There is also a JSON schema that has some examples and sane defaults. All details are explained in the next section. The parser tries to validate some of the things that the JSON schema can not. Finally there is a JSON in the tests folder that has at least one example of every feature.

Watch out, you can not name your JSON file `keymap.json` if you place in the keymap folder. QMK creates `keymap.json` as a part of compilation process and if you already have one, it gets confused.

## Steps

When setting up a new keyboard, follow the steps:

1. Make a new directory for your keymap as QMK's documentation describes.
2. Write your JSON. Name it anything but `keymap.json`.
3. Depending on the keyboard / keymap, create `rules.mk` (follow QMK's documentation and note that if the keyboard's `rules.mk` include custom source files, this is the place you can remove them).
4. Use my python parser to generate the `keymap.c`. Run it from the `/users/dennytom/chording_engine` directory as it is using relative paths to some extra files.
5. Follow QMK's documentation to compile and flash your firmware.

## Features

### Chords

Once again, *everything* on this keymap is a chord. Even sending `KC_Q` is done by pressing a single key chord. Chord gets activated after all it's keys get pressed. Only the longest chord gets activated. The order of the pressed keys *does not matter*, only the fact they have been pressed within the same time frame. An active chord gets deactivated if *any* of it's keys gets depressed. To activate the same single chord again, *all* it's keys have to be depressed and pressed again. With a few exceptions chords are independent of each other. No matter if some chords are currently active and some not, others can be activated or deactivated without affecting each other's state. *If you press keys to belonging to multiple different, non-overlapping chords, all get activated in the order they are defined in the keymap.*

### Tap-Dance

To make it even stranger, all chords are technically tap-dance chords. They are relatively simple state machines that execute a specific function every time they change state. For simplicity and optimization purposes, there are a few prewritten functions that implement common features like "send a single key" or "lock". Any number of chords can be "in dance" at any given moment without affecting each other's state. Custom dances can be easily added. Check out the `state_machine.png` to see all the states any chord can be in.

### Pseudolayers

Only one QMK layer is used. Following the butterstick's default keymap's example, the chording engine is using pseudolayers. The main difference to QMK's layers is that only one pseudolayer can be active at each time (meaning you can not use `KC_TRANS`, I actually don't know what will happen if you do). Chords can be activated only if they are on the currently active pseudolayer. Chords that are currently active do not get deactivated if the pseudolayer changes and will deactivate if any of their keys gets depressed even no matter the current pseudolayer. Locked chords (see below) and chords on the `ALWAYS_ON` pseudolayer can be activated anytime.

### Control chords

The engine implements a number of ways of changing how chords behave:

* **Lock**: Similarly to QMK's lock, the next chord activated after the Lock chord will not deactivate on release of any of its keys, it will deactivate when all its keys get pressed again. Any number of chords can be locked at the same time. To make sure a locked chord can be unlocked, it can activate no matter the current pseudolayer. A chord can be locked mid dance.
* **One shots**: Chords that send keycodes and chords that turn on pseudolayers can be one shots. If tapped, they will lock (stay active) until the next keycode gets sent, *not necessarily when the next chord gets activated*. If held, they will deactivate on release *even if no keycode got sent*.
* **Tap-Hold**: Also called key-layer dance and key-key dance. Either sends a defined keycode on tap and temporarily switches pseudolayer on hold *or* sends two different keycodes on tap and hold. 
* **Command mode**: After getting activated for the first time, the keyboard switches to command mode. All *keycodes* that would get registered get buffered instead. After activating the Command mode chord for the second time, all buffered keycodes get released at the same time allowing for key combination that would be hard or impossible to press. The Command mode only affects keycodes. It is therefore possible to change pseudolayers or activate / deactivate other chords while in Command mode. While multiple Command mode chords can be defined, they would not be independent. The keyboard either is or is not in command mode and there is only one buffer.
* **Leader key**: Just like pure QMK's Leader key, this allows you to add functions that get executed if the Leader key and a specific sequence of keycodes gets registered in a predefined order in a short timeframe. For example `:wq` can send `Ctrl+S` and `Ctrl+W` in a quick succession. While multiple Leader keys can be defined, they all would access the same list of sequences.
* **Dynamic macro**: A sequence of keycodes can be recorded and stored in the RAM of the keyboard and replayed.

## Settings up JSON definition

The JSON definition has 3 main sections. The elements `keys`, `parameters` and `layers` teach the engine about the  details of your keyboard and set its parameters. The elements `pseudolayers`, `leader_sequences` and `chord_sets` define your keymap. Finally, the elements `extra_code` and `extra_dependencies` allow you to include more code to extend the capabilities of the engine.

### Keyboard and engine parameters

I do not have experience with stenography, so the the steno keycodes are hard for me to remember. That is why the keymap is using new keycodes TOP1, TOP2, ... .

```c
 "keys": ["TOP1", "TOP2", "TOP3", ...]
```

You can name these however you like as long as they do not crash with QMK's keycodes.

*The chording engine in it's current implementation can handle up to 64 keys. If you need to support more, contact me (email or u/DennyTom at Reddit).*

All timings, maximum lengths for macros, command mode and leader function are defined in `keyboard_parameters` field. Almost all should be pretty self-explanatory.

My keyboards are small, so I only use the engine, but you might want to use layers that combine chord-able keys and traditional QMK keys or layers with advanced keycodes, for example for stenography. The array `layers` defines all the parser needs to know:

```json
"layers": [
    {
      "type": "auto"
    },
    {
      "type": "manual",
      "keycodes": ["KC_1", "KC_2", "KC_3", "KC_4", "KC_5", "KC_6", "KC_7", "KC_8", "KC_9", "KC_0",
                   "KC_Q", "KC_W", "KC_E", "KC_R", "KC_T", "KC_Y", "KC_U", "KC_I", "KC_O", "KC_P"
      ]
    },
    {
        "type": "manual",
        "keycodes": ["KC_1", "KC_2", "KC_3", "KC_4", "KC_5", "KC_6", "KC_7", "KC_8", "KC_9", "KC_0",
                    "BOT1", "BOT2", "BOT3", "BOT4", "BOT5", "BOT6", "BOT7", "BOT8", "BOT9", "BOT0"]
    }
  ]
```

This example defines 3 layers, one that is automatically populated with chording engine's internal keycodes, second that is populated with QMK's keycodes and third that uses both internal and QMK's keycodes. The layers do not have names, you have to access them with `TO(1)` and `TO(0)`.

Some keyboards mangle the order of keycodes when registering them in the layers. For that fill up the `layout_function_name` with the name of function / macro. If your keyboard does not do it, leave that string empty.

### Pseudolayers

Array `pseudolayers` defines the keymap per pseudolayer. Each field has to contain the name for the layer and the list of chords.

```JSON
"pseudolayers": [
  {        
    "name": "QWERTY",
	"chords": [
      {
        "type": "simple",
        "keycode": "SPACE",
        "chord": ["BOT1", "BOT0"]
      },
      {
        "type": "visual",
        "keycode": "CLEAR_KB",
        "chord": [
          "X", "", "", "", "", "", "", "", "", "X",
          "X", "", "", "", "", "", "", "", "", "X",
        ]
      },
      {
        "type": "visual_array",
        "keys": ["TOP1", "TOP2", "TOP3"],
        "dictionary": [
          ["X", "X", " ", "ESC"],
          [" ", "X", "X", "TAB"],
          ["X", "X", "X", "ENTER"]
        ]
      },
      {
        "type": "chord_set",
        "set": "rows",
        "keycodes": [
          "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", 
          "A", "S", "D", "F", "G", "H", "J", "K", "L", ";",
          "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/"
        ]
      }
    ]
  }
]
```

The array `chord` defines chords. You can either use simple chord and list all the keys that have to pressed at the same time, or use the visual chord and place `"X"` over keys that will be part of the chord. You can also use `visual_array` to define a number of chords in a visual way on a subset of keys defined in the `keys` array. Finally, you can use `chord_set` to define a number of chords following a pattern that was set in the `chord_sets` array in the root object like this:

```json
"chord_sets": [
  {
    "name": "rows",
    "chords": [
      ["TOP1"], ["TOP2"], ["TOP3"], ["TOP4"], ["TOP5"], ["TOP6"], ["TOP7"], ["TOP8"], ["TOP9"], ["TOP0"]
      ["TOP1", "BOT1"], ["TOP2", "BOT2"], ["TOP3", "BOT3"], ["TOP4", "BOT4"], ["TOP5", "BOT5"], ["TOP6", "BOT6"], ["TOP7", "BOT7"], ["TOP8", "BOT8"], ["TOP9", "BOT9"], ["TOP0", "BOT0"],
      ["BOT1"], ["BOT2"], ["BOT3"], ["BOT4"], ["BOT5"], ["BOT6"], ["BOT7"], ["BOT8"], ["BOT9"], ["BOT0"]
    ]
  },
  {
    "name": "cols",
    "chords": [
      ["TOP1", "TOP2"], ["TOP2", "TOP3"], ["TOP3", "TOP4"], ["TOP4", "TOP5"], ["TOP5", "TOP6"], ["TOP6", "TOP7"], ["TOP7", "TOP8"], ["TOP8", "TOP9"], ["TOP9", "TOP0"],
      ["TOP1", "TOP2", "BOT1", "BOT2"], ["TOP2", "TOP3", "BOT2", "BOT3"], ["TOP3", "TOP4", "BOT3", "BOT4"], ["TOP4", "TOP5", "BOT4", "BOT5"], ["TOP5", "TOP6", "BOT5", "BOT6"], ["TOP6", "TOP7", "BOT6", "BOT7"], ["TOP7", "TOP8", "BOT7", "BOT8"], ["TOP8", "TOP9", "BOT8", "BOT9"], ["TOP9", "TOP0", "BOT9", "BOT0"],
      ["BOT1", "BOT2"], ["BOT2", "BOT3"], ["BOT3", "BOT4"], ["BOT4", "BOT5"], ["BOT5", "BOT6"], ["BOT6", "BOT7"], ["BOT7", "BOT8"], ["BOT8", "BOT9"], ["BOT9", "BOT00"],
    ]
  }
]
```



You might notice that the code tries to do a few clever things when parsing keycodes:

* If the keycode would be just a character basic keycode, it tries to allow the use of shortcuts. `Q` will get replaced with `KC_Q`, `,` becomes `KC_COMMA`. This *should* work for all KC_ keycodes unless I missed some. 
* `MO()` and `DF()` macros work the same way for pseudolayers as they would for layers in pure QMK.
* `O()` is a shortcut for `OSK()` or `OSL()`.
* `STR('...')` sends a string. Careful with quoting.
* Special chords like Command mode have their own codes like `CMD`.
* The empty strings get ignored.

### Supported keycodes

* **`X`** or **`KC_X`**: Send code `KC_X` just like a normal keyboard. 

* **`STR("X")`**: Send string "x" on each activation of the chord. Once again, watch out for quoting and escaping characters. If you want special characters (especially quotes) in your string, look up Python reference for string literals and experiment. Also, because of how the string gets parsed, it is not possible to use `(` in the string. 

* **`MO(X)`**: Temporary switch to pseudolayer `X`. Because only one pseudolayer can be active at any moment, this works by switching back to the pseudolayer the chord lives on on deactivation. If you chain `MO()`s on multiple pseudolayers and deactivate them in a random order, you might end up stranded on a pseudolayer. I recommend adding `CLEAR` somewhere on `ALWAYS_ON` pseudolayer just in case.

* **`MO(X,Y)`**: Temporary switch to pseudolayer `Y`. Switches to pseudolayer `X` on deactivation. Especially useful when you want to put the `MO()` chord on `ALWAYS_ON`.

* **`DF(X)`**: Permanent switch to pseudolayer `X`.

* **`TO(X)`**: Switches the QMK layer to `X`.

* **`O(X)`**: One-shot key `X` (if `X` starts with `"KC_"`) or one-shot layer `X` (otherwise) . Both have retro tapping enabled.

* **Tap-holds**

  * **`KK(X, Y)`**: Pulses code `X` on tap and code `Y` on hold.
  * **`KL(X, Y)`**: Pulses code `X` on tap and switches to pseudolayer `Y` on hold. If during the hold no key gets registered, the code `X` will get sent instead (similar to QMK's retro tapping). 
  * **`KM(X, Y)`**: Same as `KK()` but meant for modifiers on hold. Instead of a timer to figure out tap-hold, uses retro tapping like behavior just like `KL()`. This has issues with GUI and ALT as they often have a meaning.
  * The chording engine determines if you are holding a chord based on a *global* timer. If you start holding a tap-hold chord and very quickly start tapping other chords, the hold might not activate until a short moment *after the last* chord when the timer expires. If you are running into this, adjust timeouts or wait a brief moment after pressing the chord to make sure it switches into the hold state before pressing other chords.

* **Autoshift**

  * **`AS(X)`**: Pulses code `X` on tap and Pulses left shift + `X` on hold. 
  * **`AT`** : Toggles autoshift for all autoshift chords. If off, all `AS` chords act like `KC` chords.

* **`LOCK`**: The lock key. Since tap-dances of chords are independent, it is possible to lock a chord *anywhere in it's dance if you time it right!*. If that happens, use the `CLEAR` chord or restart your keeb.

* **`CMD`**: The command mode. The number of keycodes that can be buffered is defined in  in `command_max_length`.

* **`LEAD`**: The leader key. The maximum length of the sequences needs to be defined in `keyboard_params`. You can use `leader_sequences` array to add sequences:

  ```json
  "leader_sequences": [
    {
      "name": "fn_L1",
      "function": "void fn_L1(void) { SEND(KC_LCTL); SEND(KC_LALT); SEND(KC_DEL); }",
      "sequence": ["KC_Q", "KC_Z"]
      }
  ]
  ```

  When the engine notices the sequence, it will call the function defined in the field `name`. You can either define it in the `function` field, in the field `extra_code` or in an external file that you then have to insert manually or using the `extra_dependencies` array. The parser copy-pastes the contents `extra_code` of all files specified in the `extra_dependencies` array in the `keymap.c`. 

* **`M(X, VALUE1, VALUE2)`**:  A custom macro. Adds a chord that will use function `X` and with `chord.value1 = VALUE1; chord.value2 = VALUE2;`. The function `X` can be arbitrary C function, go crazy. Just like with the leader sequences, you have to insert the code into the generated `keymap.c` manually or through `extra_code` or `extra_dependencies`. The following example defines a macro that acts exactly like `KC_MEH` (the chording engine *should* support `KC_MEH`, this is just an example):

  ```c
  void fn_M1(const struct Chord* self) {
      switch (*self->state) {
          case ACTIVATED:
              key_in(KC_LCTL);
              key_in(KC_LSFT);
              key_in(KC_LALT);
              break;
          case DEACTIVATED:
              key_out(KC_LCTL);
              key_out(KC_LSFT);
              key_out(KC_LALT);
              break;
          case FINISHED:
          case FINISHED_FROM_ACTIVE:
              break;
          case RESTART:
              key_out(KC_LCTL);
              key_out(KC_LSFT);
              key_out(KC_LALT);
              break;
          default:
              break;
      }
  }
  ```

  Since this feels like it would be the most common way to use this feature, I wrote a macro for this:

* **`MK(X1, X2, ...)`**: Acts like `KC()` except it registers / unregisters all `X1`, `X2`, ... codes at the same time.

* **`D(X1, X2, ...)`**: A basic keycode dance. If tapped (or held), registers `X1`. If tapped and then tapped again (or held), registers `X2`, ... It *cannot* be combined with tap-hold, however holding will result in repeat. You can put in as many basic keycodes as you want, but the macro will break if you go beyond 256. It will try to expand shortened keycodes. Advanced keycodes are not supported.

* **`DM_RECORD`, `DM_NEXT`, `DM_END`, `DM_PLAY`**: Start recording a dynamic macro. Once you start recording, basic keycodes will get stored. When replaying the macro, all keys you press before `DM_NEXT` or `DM_END` will get pressed at the same time. For example the sequence `DM_RECORD`, `KC_CTRL`, `KC_A`, `DM_NEXT`, `KC_BSPC`, `DM_END` will record a macro that when played will execute the sequence Ctrl+a, Backspace. `dynamic_macro_max_length` defines the maximum length of the macro to be recorded. You can increase it for the price of RAM. The example above requires 4 units of length to be saved (Ctrl, A, next, Backspace).

* **`CLEAR_KB`**: clears keyboard, sets all chords to the default state and switches the pseudolayer to the default one. Basically the emergency stop button.

* **`RESET`**: Go to the DFU flashing mode.

**Caveat** of the current implementation is that the tap-hold, `MK` and `D` keycodes can not accept any of the keycodes that have some sort a function like dynamic macro specific chords, `CLEAR_KB`, `RESET`, `LOCK`, `AT`, ...

### Leader Key

The sequences are not defined by the *keys* you press but by the *keycodes* that get intercepted. The length of the sequence must be equal or shorter than the maximum (defined in `keyboard.inc`). Currently, the timeout for the leader sequence refreshes after each key pressed. If the sequence is not in the database, nothing will happen.

### Extra code

Extra C code needed to define custom chords can be added by quoting in in the `extra_code` element or by saving it in another header file and including it using the `extra_dependencies` element:

```json
{
  "extra_code": "void double_dance(const struct Chord* self) { ... }\n",
  "extra_dependencies": ["my_header.h"]
}
```



## Further details

### Implementation

The source files are split into several files. `engine.part.1`, `engine.part.2` and `engine.part.3` contain C code that defines the Chord structure, implementations for all provided functions and the engine itself. `parser.py` generates keyboard and keymap dependent code. The file `chord.py` contains most of the logic required to properly translate chords from the JSON to the C code. I rarely write in python, if you have improvements, let me know, *please*.

### Internal keycodes

When `process_record_user()` gets one of the internal keycodes, it returns `true`, completely bypassing keyboard's and QMK's `process_record` functions. *All other* keycodes get passed down to QMK's standard processing.

### Chords

Each chord is defined by a constant structure, a function and two non-constant `int` variables keeping the track of the chord's state:

```c
struct Chord {
    uint32_t keycodes_hash;
    uint8_t pseudolayer;
    uint8_t* state;
    uint8_t* counter;
    uint16_t value1;
    uint8_t value2;
    void (*function) (const struct Chord*);
};

uint8_t state_0 = IDLE;
uint8_t counter_0 = 0;
void function_0(struct Chord* self) {
    switch (*self->state) {
        case ACTIVATED:
            register_code(self->value1);
            break;
        case DEACTIVATED:
            unregister_code(self->value1);
            break;
        case FINISHED:
        case PRESS_FROM_ACTIVE:
            break;
        case RESTART:
            unregister_code(self->value1);
            break;
        default:
            break;
    }
}
const struct Chord chord_0 PROGMEM = {H_TOP1, QWERTY, &state_0, &counter_0, KC_Q, 0, function_0};
```

All chords have to be added to `list_of_chord` array that gets regularly scanned and processed. The function doesn't actually activate on all state changes, there are a few more like `IDLE` (nothing is currently happening to the chord) or `IN_ONE_SHOT` (the chord is one shot and is currently locked). Those are all necessary for internal use only. The ones you have to worry about are

* `ACTIVATED`: Analogous to a key being pressed (this includes repeated presses for tap-dance)
* `DEACTIVATED`: Analogous to a key being depressed (also can be repeated)
* `FINISHED`: Happens if the chord got deactivated and then the dance timer expired.
* `PRESS_FROM_ACTIVE`: Happens if the chord was active when the dance timer expired. Meaning you at least once activated the chord and then kept holding it down. Useful to recognize taps and holds.
* `FINISHED_FROM_ACTIVE`:  Happens *after* `PRESS_FROM_HOLD` if the chord is still active when the dance timer expires for the second time. Can be combined with the `counter` to recognize even longer presses. Useful if you want to recognize long presses, for example for autoshift functionality. In `keyboard.inc` you can set `LONG_PRESS_MULTIPLIER` to set how many times does dance timer have to expire for the autoshift to trigger.
* `RESTART`: The dance is done. Happens immediately after `FINISHED` or on chord deactivation from `FINISHED_FROM_ACTIVE`. Anything you have to do to get the chord into `IDLE` mode happens here.

The chords change states based on external and internal events. Anytime a chord's function is activated, it may change it's own state. Also, on certain events, the chording engine will trigger the functions of all chords in a specific state and *if the chords' state hasn't changed* it will then change it appropriately. The default behavior when a chord changes state is described by the following diagram:

![state machine diagram](state_machine.png)
The colors differentiate in which function the change happens, see `state_machine.dot` for a bit more detail. Black arrows happen in more than one function. Arrows without a label happen immediately.

You can see that the diagram is not exhaustive. For example nothing leads into `IN_ONE_SHOT`. That is because the chord's function can change the chord's state. This is useful for some advanced chords that break the default behavir (one-shots) and for optimization (chords that just send `KC_X` do not need to ever go into dance).

## Caveats

Each chord stores as much as possible in `PROGMEM` and unless it needs it, doesn't allocate `counter`. However it still has to store it's `state` and sometimes the `counter` in RAM. If you keep adding more chords, at one point you will run out. If your firmware fits in the memory and your keyboard crashes, try optimizing your RAM usage.

Also, the code is not perfect. I keep testing it, but can not guarantee that it is stable. Some functions take (very short but still) time and if you happen to create keypress event when the keyboard can not see it, a chord can get stuck in a funny state. That is especially fun if the pseudolayer changes and you can not immediately press it again. Just restart the keyboard or push the key a few times.
