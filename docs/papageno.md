
# Papageno-QMK: Turn your keyboard into a magical instrument

## Abstract

Define multi-key tap-dances, highly customizable leader key-sequences, chords, key-clusters or mixtures of it all. [Papageno](https://github.com/noseglasses/papageno/) an advanced pattern matching library seamlessly integrates with QMK to provide ultimate flexibility in the generation of multi-key-commands. An automatized compression mechanism converts easy-to-define search-tree data structures into statically allocated, compile-time static compressed data-sets. This allows for Flash and RAM memory-saving definitions of large amounts of key-patterns in a clearly arranged fashion.

## Introduction

A description of Papageno, its basic features and a motivation of its development and application is followed by a brief example how to use the Papageno-QMK API in `key-map.c` definitions. Links to further documents that describe Papageno and its QMK-API are provided at the end of the document.

## Motivation

### Utilization of thumb keys on ergonomic keyboards

Most modern ergonomic keyboards come with dedicated thumb key clusters. These are mainly motivated by the obvious under-utilization of the thumbs on traditional computer keyboards. 
As our thumbs are the most powerful fingers, it is desirable to shift as much work as possible from the other fingers towards the thumbs. The actual number of (reachable) thumb keys varies between different keyboard designs. Typically there are between four and eight (reachable) and freely programmable thumb keys available.
This restriction in number means that when assigning key-codes or actions to these special keys it is important to do it in a way that optimizes both, utilization and usability. In the recent past there occurred a significant number of innovative ideas that aim to assign more than two key-codes or actions to a physical key.

### Existing QMK-features

[Tap-dances](tap_dance.md), modifier keys, with and without one-touch, as well as multiple key-map-layers provide different ways to creatively assign work to thumb keys using QMK. These methods all have specific advantages and drawbacks. A thorough analysis of the many possible ways to utilize and combine those could fill a research article of its own. Therefore, we will concentrate on tap-dances to explain the enhancements introduced by Papageno. 

[Tap-dances](tap_dance.md) theoretically allow to assign an infinite number of meanings to a single physical key. A specific number of key-presses, usually entered in rapid succession, triggers a specific action.
This is probably the only, but also the greatest disadvantage of *traditional* tap-dances. Hitting a key a given number of times in a row can be fairly difficult to accomplish, especially for non pianists and when there are definitions for say, three, four and five strokes of the same key.

### Towards multi-key tap-dances

As a keyboard comes with a multitude of keys, why not extend the concept of tap-dances to combinations of several keys? It is much easier to hit two, three or more keys in a defined order than to hit the same key a given number of times. Entering key sequences, i.e. words, is precisely what typists are trained to do.
 
Of course, we want the action that is triggered when the key sequence has been completed to replace the actual series of key-codes that is assigned with the keys when hit independently, same as with tap-dances.

### Some numbers

Let's go back to where we came from, shifting work, e.g. to thumb keys. It would be useful to assign actions to two key combinations (two key words) of thumb keys that are assigned to the left and the right hand.
For a keyboard with two thumb keys for each hand, this would mean that we would end up with eight possible two-key combinations of thumb keys assigned to different hands. Hereby, we assume that hitting two keys A and B in two different orders is supposed to trigger two different actions. 

If we add to these eight combinations the four possible actions assigned to keys when hit independently, this sums up to twelve different actions for four thumb keys.

It is up to the reader to solve the task of computing the drastic increase in number if we would also consider three-key combinations and so forth.

### A real-life use case

Let's look at a brief example how multi-key tap-dances (in Papageno jargon called single-note lines, clusters and chords) could be applied to enhance QMK's capability. 

Imagine editing some sort of program source code. A hereby common task is to indent lines, either to improve readability or because the language requires indentation as part of its semantic. Often it is also necessary to un-indent lines of code. Most editors assign shortcuts to both operations that are more or less simple to enter.
As indentation/un-indentation are a fairly common operations when programming, it seems to be a good idea to trigger them through thumb-keys of our possibly ergonomic, programmable keyboard. 

In the following we use the letter `A` for one of the left hand thumb-keys and `B` for one of the right hand thumb keys. 
One possible solution for the given task would be to indent
 when keys `A` and `B` are hit in order `A-B` and un-indent when hit in order `B-A`. Both operations would, of course, be programmed to emit the required shortcut.
 
From a neuromuscular point of view this key-assignment strategy is doubtlessly a good choice as it is fairly easy to learn. Moreover, it is rather intuitive as we assign a forward-backward relation to indentation and un-indentation with respect to the order of the two thumb keys being hit. This certainly aids memorizing our new key assignment.

### Papageno - a pattern matching library

To bring the above example to life, we need a mechanism that is capable to recognize more or less complex keystroke patterns. The requirements described, among others,
led to the development of [Papageno](https://github.com/noseglasses/papageno/), an advanced pattern matching library. Originally implemented as part of QMK, Papageno emerged to a stand-alone multi-platform library that still seamlessly integrates with QMK. It provides a variety of different ways to define patterns that go far beyond advanced tap-dances only.

## A QMK example

The impatient may directly jump to a [QMK example key-map](https://github.com/noseglasses/noseglasses_qmk_layout/) that demonstrates how Papageno can be employed to effectively shift load from fingers to thumbs.

## Papageno-QMK

Papageno allows for the definition of general multi-key patterns, chords, key clusters, arbitrary leader sequences with multiple leader keys and more. All features utilize the same efficient and optimized pattern matching algorithm. To be used with QMK, Papageno provides a wrapper API. It allows to define patterns in a simple and readable way and encapsules common tasks through C-pre-processor macros.

The heart of Papageno is a search tree that is established based on the definitions that are part of user-implemented QMK key-map files.
As typical for dynamically assembled tree data structures, this tree-based approach relies on dynamic memory allocation. Many believe that dynamically allocated data structures are a no-go on embedded architectures, such as those used in programmable keyboards. Actually, it is not that much of a hindrance as Papageno mainly allocates memory but does not free it during program execution. This inherently avoids RAM fragmentation which would otherwise lead to an early exhaustion of RAM. 

To optimize the utilization of both, Flash memory and SRAM, Papageno comes with an integrated compression mechanism.

## Compression of data-structures

Where the dynamic creation of tree data structures works well for a moderate amount of key patterns, it can be problematic when a large amount of patterns is defined or if many other features of QMK are used along with Papageno. In such a case the limited resources of the keyboard hardware might be a problem.

Before we talk about compression of data structures, let us look at the two modes of operation, that Papageno provides. The first and general one requires the generation of dynamic data structures during firmware execution on the keyboard. The second, a more advanced and optimized mode of operation allows for a two stage compile process that compresses most of Papageno's data structures and aims to be as memory efficient as possible, both with respect to flash memory and RAM.

This integrated compression mechanism turns the dynamically allocated pattern matching search tree into a compile-time static data structure. We, thus, avoid dynamic memory allocations and significantly shrink binary size. Apart from the sheer compactification of data structures, compression also helps to safe program memory as no code is required to establish dynamic data structures during firmware execution. The respective C-functions are, therefore, automatically stripped from the binary as part of the firmware build process. 

When applied to [noseglasses'](https://github.com/noseglasses/noseglasses_qmk_layout/) QMK-key-map compiled for an ErgoDox EZ, Papageno's compression mechanism reduces the size of the emerging hex-file by 2420 byte. Program storage and RAM saved can e.g. be used for other valuable QMK features.

## Compatibility with existing QMK features

The efficiency of Papageno's tree based pattern matching approach is one of the reasons why some features that were already part of QMK, such as tap-dances and leader sequences, have been incorporated into Papageno. (Another reason is that they were just fun to implement based on Papageno).

Let's concentrate on our primary motivation, efficiency.
If features provided by Papageno are used in common with equivalent pre-existing QMK-features, such as e.g. leader sequences, that are now also supported by Papageno, resource usage can be expected to be significantly higher than if Papageno would deal with the given tasks alone. The reason is obvious, more program memory and probably more RAM is required to store binary code and variables for two or more modules instead of only one. 

Although optimized resource utilization is never a bad idea, Papageno plays along well with other QMK features.

## Papageno as a wrapper to QMK

Papageno-QMK is designed as a wrapper for the rest of QMK. Any keystrokes are intercepted and passed through Papageno's pattern matching engine. Only if a series of keystrokes is identified as non-matching any defined pattern, it is passed over to the main QMK engine. To QMK these keystrokes appear as if they had just emerged during the most recent keyboard matrix scan.

This allows for a strong decoupling of Papageno and QMK that is robust and can be expected to work quite well with most other features provided by QMK.

For compatibility reasons, Papageno provides a layer mechanism that is fairly similay to that of QMK's key-maps. At their point of definition, patterns are associated with layers. They are only active while their associated layer is activated, which is controlled by the rest of QMK.
Layer fall through, works similar to the assignment of transparent key-codes in QMK key-maps.

It is most common to emit QMK key-codes when a defined pattern matches a series of keystrokes.
To allow for more advanced functionality Papageno provides an interface to define arbitrary user callback functions that can be supplied with user defined data.

## An introduction to Papageno' QMK API

### Key definitions

Papageno as integrated with QMK operates on key-positions or key-codes as building blocks for patterns. Using key-positions means that a physical key, i.d. the key-switch at a given position on the keyboard is assigned with an identifier. QMK/TMK key-codes can also be assigned an identifier that is used by Papageno for pattern matching. This means that several keys that have been assigned the same key-code have the same meaning during pattern matching.

To enable key-code lookup, keystrokes are passed through QMK's lookup engine to determine the key-code that is defined in the key-map of the current layer. The key-code found is then passed over to Papageno's pattern matching engine.

As it is the more common approach, we will restrict the provided example below to the use of key-positions as building blocks of pattern definitions.

### Using key-positions to define patterns

To use key-positions as tokens to define patterns, add the following code to your key-map. The example assumes that we want to assign names to the matrix key-position `(5,2)` and `(5,B)` which represent the left and right inner thumb keys on an ErgoDox EZ. 

Please note the auxiliary macro parameter `S`. It is necessary for implementation purposes. The parameter name `S` can be replaced arbitrarily.

```C
#define LEFT_INNER_THUMB_KEY(S)     PPG_QMK_KEYPOS_HEX(5, 2, S)
#define RIGHT_INNER_THUMB_KEY(S)    PPG_QMK_KEYPOS_HEX(5, B, S)
```

All keys that are supposed to be used in Papageno patterns must be macro-defined in the provided way.

All key-positions must be registered with Papageno by defining a macro `PPG_QMK_MATRIX_POSITION_INPUTS` that registers all key-position macros that we have defined.

```C
// Define a set of Papageno inputs that are associated with
// keyboard matrix positions.
//
// Important: - The macro must be named PPG_QMK_MATRIX_POSITION_INPUTS!
//            - If no inputs are supposed to be associated with
//              matrix positions, define an empty PPG_QMK_MATRIX_POSITION_INPUTS
//
#define PPG_QMK_MATRIX_POSITION_INPUTS(OP) \
\
__NL__      OP(LEFT_INNER_THUMB_KEY) \
__NL__      OP(RIGHT_INNER_THUMB_KEY)
```

In the current example we concentrate on key-positions as input tokens. Nevertheless, we must inform Papageno of the key-codes (here none) that we want to use as input tokens.

```C
// Define a set of Papageno inputs that are associated with
// qmk keycodes.
//
// Important: - The macro must be named PPG_QMK_KEYCOKC_INPUTS!
//            - If no inputs are supposed to be associated with
//              keycodes, define an empty PPG_QMK_KEYCOKC_INPUTS
//
#define PPG_QMK_KEYCODE_INPUTS(OP)
```

Finally, we initialize any global data structures used by Papageno-QMK.

```C
// Initialize Papageno data structures for qmk
// This is based on the definitions of
//
//    PPG_QMK_MATRIX_POSITION_INPUTS
//
// and
//
//    PPG_QMK_KEYCODE_INPUTS
//
// and assumes these to be already defined.
//
PPG_QMK_INIT_DATA_STRUCTURES
```

### Initialization of the pattern matching engine

To set up Papageno patterns it is recommended to define a dedicated initialization function. The name `init_papageno` can be arbitrarily replaced. However, please note that some auxiliary macros might rely on the name being `init_papageno` when used.

```C
void init_papageno(void)
{
   // Initialize the Papageno-QMK system
   //
   PPG_QMK_INIT
   
   // Define an individual timeout for Papageno-QMK. 
   // Keystrokes whose time interval
   // exceeds the timeout are considered individually, i.e. as not
   // part of a Papageno pattern and are thus passed directly over to QMK.
   //
   ppg_qmk_set_timeout_ms(200);
   
   // Left inner and right inner thumb key are supposed to 
   // trigger emission of the enter key-code (KC_ENTER) if clustered,
   // i.e. when hit one after the other in arbitrary order.
   //
   PPG_QMK_KEYPOS_CLUSTER_ACTION_KEYCODE(
      0, // Layer 0, equivalent to the respective QMK layer
      KC_ENTER, // Keycode action
      
      // An unlimited number of matrix key-positions may follow.
      // Here we use the key-position macros defined above.
      //
      LEFT_INNER_THUMB_KEY,
      RIGHT_INNER_THUMB_KEY
      // ...
   );
   
   // ... more Papageno-QMK pattern definitions
  
   // Compile and establish Papageno's search tree
   //
   PPG_QMK_COMPILE
}
```

### Connection with QMK

Our initialization function must be linked to the QMK system by overriding
the QMK-interface function `matrix_init_user`.

```C
void matrix_init_user(void) 
{ 
   init_papageno();
   
   // ... other initialization tasks
}
```

Two more interface function must be overridden to connect Papageno with QMK.

The overridden function `matrix_scan_user` ensures, amongst others, that pattern matching timeouts are correctly handled.
```C
void matrix_scan_user(void) 
{
   ppg_qmk_matrix_scan();
   
   // ... other matrix scan tasks
};
```

The actually key-press handling is performed by an overriden version of `action_exec_user`.
```C
void action_exec_user(keyevent_t event)
{
   ppg_qmk_process_event(event);
   
   // ... other matrix scan tasks
}
```

If no other tasks are to be performed by the overridden QMK-interface functions, all above overrides can be defined automatically by calling the macro `PPG_QMK_CONNECT` at global scope. Please ensure to name the initialization function `init_papageno` in this case.

### A small working example

The following is a short version of the keymap file `keyboards/ergodox_ex/keymaps/papageno/keymap.c' file that is part of the QMK source distribution.
The example can be build for an ErgoDox EZ and with slight modifications (adapt the keymap definition to your keyboard) for any other keyboard that QMK supports. It demonstrates how the two inner thumb keys of the keyboard trigger emission of the key-code KC_ENTER when hit in arbitrary order.

```C
#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include "process_papageno.h"

// ... define your QMK-key-codes here

// Define key positions that are supposed to be used by Papageno
//
#define LEFT_INNER_THUMB_KEY(S)  PPG_QMK_KEYPOS_HEX(5, 2, S)
#define RIGHT_INNER_THUMB_KEY(S) PPG_QMK_KEYPOS_HEX(5, B, S)

// Define a set of Papageno inputs that are associated with
// keyboard matrix positions.
//
// Important: - The macro must be named PPG_QMK_MATRIX_POSITION_INPUTS!
//            - If no inputs are supposed to be associated with
//              matrix positions, define an empty PPG_QMK_MATRIX_POSITION_INPUTS
//
#define PPG_QMK_MATRIX_POSITION_INPUTS(OP) \
\
__NL__      OP(LEFT_INNER_THUMB_KEY) \
__NL__      OP(RIGHT_INNER_THUMB_KEY)

// Define a set of Papageno inputs that are associated with
// qmk keycodes.
//
// Important: - The macro must be named PPG_QMK_KEYCOKC_INPUTS!
//            - If no inputs are supposed to be associated with
//              keycodes, define an empty PPG_QMK_KEYCOKC_INPUTS
//
#define PPG_QMK_KEYCODE_INPUTS(OP)

// Initialize Papageno data structures for qmk
// This is based on the definitions of 
//
//    PPG_QMK_MATRIX_POSITION_INPUTS
//
// and
//
//    PPG_QMK_KEYCODE_INPUTS
//
PPG_QMK_INIT_DATA_STRUCTURES

void init_papageno(void)
{
   PPG_QMK_INIT

   ppg_qmk_set_timeout_ms(200);

   PPG_QMK_KEYPOS_CLUSTER_ACTION_KEYCODE(
      0,
      KC_ENTER,
      LEFT_INNER_THUMB_KEY,
      RIGHT_INNER_THUMB_KEY
   );
   
   // ... more pattern definitions

   PPG_QMK_COMPILE
}

PPG_QMK_CONNECT
```

## Advanced usage - further reading

For matters of simplicity, the introductory example above only demonstrates one of the many features provided by Papageno. A complete documentation of Papageno's QMK-API goes far beyond the scope of this document. 

The application of a large portion of Papageno's features is exemplified with the help of noseglasses' [QMK-key-map](https://github.com/noseglasses/noseglasses_qmk_layout/).

Please see also the file `process_key-code/process_papageno.h` in the root directory of QMK's source tree. It contains the definition of the overall Papageno-QMK API in terms of C-functions and utility pre-processor macros.

All of the functions and macros defined in `process_key-code/process_papageno.h` are some sort of wrappers to the actual Papageno API [Papageno API](https://github.com/noseglasses/papageno/).