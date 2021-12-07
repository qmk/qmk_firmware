# Firmware Protocol for Talking to The App

## Overview

It's assumed the transport layer of the protocol handles delivery guarantee. In practise, the protocol is implemented in serial for now as QMK only supports arbitrary communication with the host computer via serial.

As the USB link is established, supported OSes will install the correct serial driver for the keyboard. If the chonkerkeys app is installed, the app will open the serial interface instead of the USB interface for communication.

The app would first initiate a handeshake request that confirms the firmware and protocol version. The firmware of the keyboard would then
respond with the versions hard coded in the ROM. If the version is valid, according to whatever rules the app defined, then the app would proceed to initiate the initialization sequence, otherwise it would disconnect the serial device.

(Note that since QMK requires flashing firmware to change _any_ configuration (it doesn't support storing configuration in EPPROM yet), flashing a firmware doesn't necessarily update the firmware's version even in normal operation of the app. The firmware and protocol version of a firmware is instead defined by the app before flashing according to certain rules (e.g. follow app version), or a specific version when getting out of the factory.)

The initialization sequence consists of some steps that allow the app to retrieve the current keyboard's current configuration, including layer configuration, key macros, light color etc. The sequence might involve several requests from the app, depending on the loading requirement and encoding of these configuration.

After the app had requested all configurations, _validated_ them, and deemed everything OK, the app issues a connected signal to the keyboard. Before receiving the signal, the keyboard acts as an ordinary HID keyboard. After receiving the signal, the firmware enters protocol mode. In this mode, whenver a key is pressed, instead of sending HID protocol to the host OS, the firmware sends events according to this protocol to the host app instead, such that the app can intelligently send the macros to the appropriate process. Assuming the firmware entered protocol mode, the app also sends events to the firmware when necessary. For example, the app would send event to the firmware when zoom changes it's mic's mute state.

It is conceivable that the keyboard also needs to initialize its lighting state etc according to the current meeting status when plugged in. Since these state is non-blocking to the operation of the whole application, the protocol does not mandate a specific keyboard initialization sequence. One simple implementation of keyboard initialization sequence is that the app simply dispatches all key's lighting state after it sends the connect signal.

## The Protocol

For simplicity, anything that is sent from the app from the keyboard is called a _Command_. Anything that is sent from the firmware is called an _Event_. This might introduce some weird combination of terms e.g. MuteStateChagnedEventCommand might be the command to send to the firmware whenever an app changes it's mute state. This is adviced that naming consideration takes into account this command/event convention and avoid such weird combination. For example, MuteStateChangedEventCommand can simply be renamed to ChangeMuteStateCommand.

(This naming convention is TBC, just to make it clear what is sent by what for now)

### Header Consideration and Structure

The protocol is binary based. That is, no text encoding. Number should be sent in raw byte. Text is sent in utf-8.

The basic structure of a command/event is shown as follows:

#### Version 1 command/event structure

| data                   | size in byte                           | Note |
| ---------------------- | -------------------------------------- |------|
| command/event type     | 1                                      |256 types|
| subsequent data size   | 2                                      |65536 data bytes|
| per command/event data | as spepcified in subsequence data size ||

Note that the firmware needs to allocate space to buffer the command. Thus, there is a maximum size limit for a command. The size limit is currently TBC.

TODO: Do we need a special header to indicate it's the start of a command/event? So receiver will check for its precense after parsing a comment/event, and if it's not found it knows there is a corruption/implementation error and react accrodingly (e.g. disconnect)?

### Protocol List

#### GetVersionCommand/GetVersionResponseEvent

##### Command

No data.

##### Event

|data|size in byte|Note|
|----|------------|----|
|firmware version| 4 | type is uint32_t |

#### GetConfigCommand

TODO

#### ConnectCommand

TODO

#### UpdateLightCommand

| data                                          | size in byte | Note                                                          |
| --------------------------------------------- | ------------ | ------------------------------------------------------------- |
| key                                           | 2            | first byte encode x coordinate, last byte encode y coordinate |
| state as defined by the light type of the key | 1            |

See Light type and state for more details.

#### EnterBootLoaderCommand

TODO

---

#### KeyDownEvent

TODO

#### LayerSwitchedEvent

TODO

## Light Type and Their State

It's currently unknown whehter all light type has at most 3 states. This doc is written as if some light type has more than 3 states (otherwise, we just need to define state once and go on to define the light types, one is L \* S, one is L + S).

A lighting effect consists of 2 parts: the type and the state. The type denotes a cateogry to which the light belongs, usually aligns with the category of the key. E.g. a key with a mute icon should have a `Mute` light type. The state denotes what behavior the light should currently have. Most keys have at least on/off state. Some might have more, e.g. share screen which has an intermediate state to representing user is picking a screen.

The firmware stores and only stores the light type. At start up, the app sends whatever state the keyboard should be in via the protocol. The firmware then stores the state in RAM. When unplugged, the keyboard keeps the light type via firmware, but lose the light state.

When the app needs to tell the keyboard to light up, it uses the configuration it reads from `GetConfigCommand` to get the light type, make sure it matches the operation it wants to perform (e.g. the operation might be triggered by zoom changing mute state, it then validates the light type is light type `Mute`), and then grab the appropriate value for the state. The app only sends state, as light type is already stored in the configuration in firmware.

### Binary Size Concern

This design assumes the firmware has enough space to store all the lighting routine code + configuration. That is, each key already stores its lighting type in the configuration. For example, a key can be assigned the `LightType.Mute` enumeration. When the firmware receives this command, it parses the key coordinate, get the configuration for that key, and obtain the light type and color. Knowing the key has a mute light type, it would then turn the key's LED to red when it receives off state, encoding as `0`, and green for on state, encoded as `1`. Every light state/patterns is encoded in its light type and state.

More example: share screen's light type is defined as the `LightType.ShareScreen` enumeration. It has 3 state: on, off, and intermediate. On and off are straight-forward, single-color lighting. Intermediate is a rotating singel color pattern. The state itself doesn't actually encode how the lighting pattern work. The code does. All that the state encode is all 3 of these possible states.

In this design, there will be lots of branching in the firmware's code. The branch would be based on light type + state. Each state would then "do its own thing", controlling how the LED work.

It is thus conceivable that the firmware simply does not have enough room for all the code and data (as other key configurations might consume a large amount of binary storage). It's not estimatable how many storage code consumes, but we can calculate how much data is consumed for light. Suppose that:

- each key has a light type, and
- each layer's key can have different light type, and
- there are `x` keys, and
- there are `y` layers, and
- each light type consumes 1 byte (for a total of 256 light types)

Assuming a naive, uniform 2d array for storage, the number of bytes consumed by light type is thus

```
bytes = 1 * x * y

// Assuming 6 layers
// For model "Original"
bytes = 1 * 8 * 4 * 6 = 192 = ~0.6%

// For model "Max"
bytes = 1 * 8 * 6 * 6 = 288 = ~1%
```

A bare minimum QMK firmware already consumes 57% of the available size as of the time of writing.

More work can be done to use variable size encoding so that "holes" on the board (i.e. a board slot that doesn't have a key inserted) doesn't consume any storage.

---

This section documents the light type and their state. Unless otherwise specified, the enum value is the state sent in the `UpdateLightCommand`.

### LightType.Mute

```
enum LightTypeMuteState {
    Off = 0,
    On
}
```

### LightType.ShareScreen

```
enum LightTypeShareScreenState {
    Off = 0,
    Intermediate,
    On
}
```
