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

---

#### GetVersionCommand/GetVersionResponseEvent

##### Command

No data.

##### Event

|data|size in byte|Note|
|----|------------|----|
|firmware version| 4 | type is uint32_t |

---

#### GetConfigCommand/GetConfigResponseEvent

##### Command

No data.

##### Event

|data|size in byte|Note|
|----|------------|----|
|layer count|1|max 256 layer|
|*layer*|
|layer type|1|maps to `LayerType`, e.g. `ZoomWindows`|
|*key*|
|key(x,y) size and ordinal|1|`enum class Ordinal : uint8_t { left = 0, top, right, bottom, empty }` & `enum class Size : uint8_t { Key1, Key1.5, Key3 }` << 6 |
|key(x,y) action type|1|maps to `KeyActionType`, e.g. `ZoomMute`|
|key(x,y) icon|4|1 unicode code point in UTF32 (TBA). Just return whatever is stored in the firmware (which is in turn configured via the app/factory image). Leave meeting currently is hard coded as 3u's label always.|
|repeat *key* for all keys in a layer|48 or 72|4x2x6 = 48 for original, 4x3x6 = 72 for max|
|repeat *layer* for all layers|48 + 1 x n or 72 + 1 x n|where n is the number of layers|

TODO: Custom label? Is it a thing?
TODO: Custom executable path?

---

#### ConnectCommand

No data.

---

#### ResetCommand

No data.

---

#### SetLEDCommand

|data|size in byte|Note|
|----|------------|----|
|animation type|1|256 type|
|key x|1||
|key y|1||
|R|1||
|G|1||
|B|1||
|animation data|animation-specific||

##### Animation Data

###### Steady

No data.

###### Blink

|data|size in byte|Note|
|----|------------|----|
|frequency|1|Unit is TBC|

###### Like animation

No data.

###### Leave meeting animation

No data.

###### Momentary

|data|size in byte|Note|
|----|------------|----|
|duration|1|Unit is 1/100 of a second, range is 10ms to 2560ms|

---

#### KeyDownEvent

|data|size in byte|Note|
|--|--|--|
|layer |1||
|key x|1||
|key y|1||

#### LayerSwitchedEvent

TODO
