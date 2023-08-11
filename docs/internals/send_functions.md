# group `send_functions` {#group__send__functions}

These are the functions you use to send midi data through a device.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`midi_send_cc`](#group__send__functions_1gaaf884811c92df405ca8fe1a00082f960)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t val)`            | Send a control change message (cc) via the given device.
`public void `[`midi_send_noteon`](#group__send__functions_1ga467bcf46dbf03ec269ce565b46bc2775)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t vel)`            | Send a note on message via the given device.
`public void `[`midi_send_noteoff`](#group__send__functions_1gaedb7d8805425eef5d47d57ddcb4c7a49)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t vel)`            | Send a note off message via the given device.
`public void `[`midi_send_aftertouch`](#group__send__functions_1ga0014847571317a0e34b2ef46a6bc584f)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t note_num,uint8_t amt)`            | Send an after touch message via the given device.
`public void `[`midi_send_pitchbend`](#group__send__functions_1gae5a4a1e71611e7534be80af9ce3d3491)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,int16_t amt)`            | Send a pitch bend message via the given device.
`public void `[`midi_send_programchange`](#group__send__functions_1ga7b15588ef25e5e1ff09c2afc3151ce86)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num)`            | Send a program change message via the given device.
`public void `[`midi_send_channelpressure`](#group__send__functions_1gaf23e69fdf812e89c0036f51f88ab2e1b)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t amt)`            | Send a channel pressure message via the given device.
`public void `[`midi_send_clock`](#group__send__functions_1ga4e1b11a7cdb0875f6e03ce7c79c581aa)`(`[`MidiDevice`](#struct__midi__device)` * device)`            | Send a clock message via the given device.
`public void `[`midi_send_tick`](#group__send__functions_1ga2b43c7d433d940c5b907595aac947972)`(`[`MidiDevice`](#struct__midi__device)` * device)`            | Send a tick message via the given device.
`public void `[`midi_send_start`](#group__send__functions_1ga1569749a8d58ccc56789289d7c7245cc)`(`[`MidiDevice`](#struct__midi__device)` * device)`            | Send a start message via the given device.
`public void `[`midi_send_continue`](#group__send__functions_1gaed5dc29d754a27372e89ab8bc20ee120)`(`[`MidiDevice`](#struct__midi__device)` * device)`            | Send a continue message via the given device.
`public void `[`midi_send_stop`](#group__send__functions_1ga026e1a620276cb653ac501aa0d12a988)`(`[`MidiDevice`](#struct__midi__device)` * device)`            | Send a stop message via the given device.
`public void `[`midi_send_activesense`](#group__send__functions_1ga9b6e4c6ce4719d2604187b325620db37)`(`[`MidiDevice`](#struct__midi__device)` * device)`            | Send an active sense message via the given device.
`public void `[`midi_send_reset`](#group__send__functions_1ga3671e39a6d93ca9568fc493001af1b1b)`(`[`MidiDevice`](#struct__midi__device)` * device)`            | Send a reset message via the given device.
`public void `[`midi_send_tcquarterframe`](#group__send__functions_1ga5b85639910eec280bb744c934d0fd45a)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t time)`            | Send a tc quarter frame message via the given device.
`public void `[`midi_send_songposition`](#group__send__functions_1gab1c9eeef3b57a8cd2e6128d18e85eb7f)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t pos)`            | Send a song position message via the given device.
`public void `[`midi_send_songselect`](#group__send__functions_1ga42de7838ba70d949af9a50f9facc3c50)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t song)`            | Send a song select message via the given device.
`public void `[`midi_send_tunerequest`](#group__send__functions_1ga8db6c7e04d48e4d2266dd59118ca0656)`(`[`MidiDevice`](#struct__midi__device)` * device)`            | Send a tune request message via the given device.
`public void `[`midi_send_byte`](#group__send__functions_1ga857e85eb90b288385642d4d991e09881)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t b)`            | Send a byte via the given device.
`public void `[`midi_send_data`](#group__send__functions_1ga36e2f2e45369d911b76969361679054b)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t count,uint8_t byte0,uint8_t byte1,uint8_t byte2)`            | Send up to 3 bytes of data.
`public void `[`midi_send_array`](#group__send__functions_1ga245243cb1da18d2cea18d4b18d846ead)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t count,uint8_t * array)`            | Send an array of formatted midi data.

## Members

#### `public void `[`midi_send_cc`](#group__send__functions_1gaaf884811c92df405ca8fe1a00082f960)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t val)` {#group__send__functions_1gaaf884811c92df405ca8fe1a00082f960}

Send a control change message (cc) via the given device.

#### Parameters
* `device` the device to use for sending 

* `chan` the channel to send on, 0-15 

* `num` the cc num 

* `val` the value of that cc num

#### `public void `[`midi_send_noteon`](#group__send__functions_1ga467bcf46dbf03ec269ce565b46bc2775)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t vel)` {#group__send__functions_1ga467bcf46dbf03ec269ce565b46bc2775}

Send a note on message via the given device.

#### Parameters
* `device` the device to use for sending 

* `chan` the channel to send on, 0-15 

* `num` the note number 

* `vel` the note velocity

#### `public void `[`midi_send_noteoff`](#group__send__functions_1gaedb7d8805425eef5d47d57ddcb4c7a49)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num,uint8_t vel)` {#group__send__functions_1gaedb7d8805425eef5d47d57ddcb4c7a49}

Send a note off message via the given device.

#### Parameters
* `device` the device to use for sending 

* `chan` the channel to send on, 0-15 

* `num` the note number 

* `vel` the note velocity

#### `public void `[`midi_send_aftertouch`](#group__send__functions_1ga0014847571317a0e34b2ef46a6bc584f)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t note_num,uint8_t amt)` {#group__send__functions_1ga0014847571317a0e34b2ef46a6bc584f}

Send an after touch message via the given device.

#### Parameters
* `device` the device to use for sending 

* `chan` the channel to send on, 0-15 

* `note_num` the note number 

* `amt` the after touch amount

#### `public void `[`midi_send_pitchbend`](#group__send__functions_1gae5a4a1e71611e7534be80af9ce3d3491)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,int16_t amt)` {#group__send__functions_1gae5a4a1e71611e7534be80af9ce3d3491}

Send a pitch bend message via the given device.

#### Parameters
* `device` the device to use for sending 

* `chan` the channel to send on, 0-15 

* `amt` the bend amount range: -8192..8191, 0 means no bend

#### `public void `[`midi_send_programchange`](#group__send__functions_1ga7b15588ef25e5e1ff09c2afc3151ce86)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t num)` {#group__send__functions_1ga7b15588ef25e5e1ff09c2afc3151ce86}

Send a program change message via the given device.

#### Parameters
* `device` the device to use for sending 

* `chan` the channel to send on, 0-15 

* `num` the program to change to

#### `public void `[`midi_send_channelpressure`](#group__send__functions_1gaf23e69fdf812e89c0036f51f88ab2e1b)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t chan,uint8_t amt)` {#group__send__functions_1gaf23e69fdf812e89c0036f51f88ab2e1b}

Send a channel pressure message via the given device.

#### Parameters
* `device` the device to use for sending 

* `chan` the channel to send on, 0-15 

* `amt` the amount of channel pressure

#### `public void `[`midi_send_clock`](#group__send__functions_1ga4e1b11a7cdb0875f6e03ce7c79c581aa)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga4e1b11a7cdb0875f6e03ce7c79c581aa}

Send a clock message via the given device.

#### Parameters
* `device` the device to use for sending

#### `public void `[`midi_send_tick`](#group__send__functions_1ga2b43c7d433d940c5b907595aac947972)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga2b43c7d433d940c5b907595aac947972}

Send a tick message via the given device.

#### Parameters
* `device` the device to use for sending

#### `public void `[`midi_send_start`](#group__send__functions_1ga1569749a8d58ccc56789289d7c7245cc)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga1569749a8d58ccc56789289d7c7245cc}

Send a start message via the given device.

#### Parameters
* `device` the device to use for sending

#### `public void `[`midi_send_continue`](#group__send__functions_1gaed5dc29d754a27372e89ab8bc20ee120)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1gaed5dc29d754a27372e89ab8bc20ee120}

Send a continue message via the given device.

#### Parameters
* `device` the device to use for sending

#### `public void `[`midi_send_stop`](#group__send__functions_1ga026e1a620276cb653ac501aa0d12a988)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga026e1a620276cb653ac501aa0d12a988}

Send a stop message via the given device.

#### Parameters
* `device` the device to use for sending

#### `public void `[`midi_send_activesense`](#group__send__functions_1ga9b6e4c6ce4719d2604187b325620db37)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga9b6e4c6ce4719d2604187b325620db37}

Send an active sense message via the given device.

#### Parameters
* `device` the device to use for sending

#### `public void `[`midi_send_reset`](#group__send__functions_1ga3671e39a6d93ca9568fc493001af1b1b)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga3671e39a6d93ca9568fc493001af1b1b}

Send a reset message via the given device.

#### Parameters
* `device` the device to use for sending

#### `public void `[`midi_send_tcquarterframe`](#group__send__functions_1ga5b85639910eec280bb744c934d0fd45a)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t time)` {#group__send__functions_1ga5b85639910eec280bb744c934d0fd45a}

Send a tc quarter frame message via the given device.

#### Parameters
* `device` the device to use for sending 

* `time` the time of this quarter frame, range 0..16383

#### `public void `[`midi_send_songposition`](#group__send__functions_1gab1c9eeef3b57a8cd2e6128d18e85eb7f)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t pos)` {#group__send__functions_1gab1c9eeef3b57a8cd2e6128d18e85eb7f}

Send a song position message via the given device.

#### Parameters
* `device` the device to use for sending 

* `pos` the song position

#### `public void `[`midi_send_songselect`](#group__send__functions_1ga42de7838ba70d949af9a50f9facc3c50)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t song)` {#group__send__functions_1ga42de7838ba70d949af9a50f9facc3c50}

Send a song select message via the given device.

#### Parameters
* `device` the device to use for sending 

* `song` the song to select

#### `public void `[`midi_send_tunerequest`](#group__send__functions_1ga8db6c7e04d48e4d2266dd59118ca0656)`(`[`MidiDevice`](#struct__midi__device)` * device)` {#group__send__functions_1ga8db6c7e04d48e4d2266dd59118ca0656}

Send a tune request message via the given device.

#### Parameters
* `device` the device to use for sending

#### `public void `[`midi_send_byte`](#group__send__functions_1ga857e85eb90b288385642d4d991e09881)`(`[`MidiDevice`](#struct__midi__device)` * device,uint8_t b)` {#group__send__functions_1ga857e85eb90b288385642d4d991e09881}

Send a byte via the given device.

This is a generic method for sending data via the given midi device. This would be useful for sending sysex data or messages that are not implemented in this API, if there are any. Please contact the author if you find some so we can add them.

#### Parameters
* `device` the device to use for sending 

* `b` the byte to send

#### `public void `[`midi_send_data`](#group__send__functions_1ga36e2f2e45369d911b76969361679054b)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t count,uint8_t byte0,uint8_t byte1,uint8_t byte2)` {#group__send__functions_1ga36e2f2e45369d911b76969361679054b}

Send up to 3 bytes of data.

% 4 is applied to count so that you can use this to pass sysex through

#### Parameters
* `device` the device to use for sending 

* `count` the count of bytes to send, %4 is applied 

* `byte0` the first byte 

* `byte1` the second byte, ignored if cnt % 4 != 2 

* `byte2` the third byte, ignored if cnt % 4 != 3

#### `public void `[`midi_send_array`](#group__send__functions_1ga245243cb1da18d2cea18d4b18d846ead)`(`[`MidiDevice`](#struct__midi__device)` * device,uint16_t count,uint8_t * array)` {#group__send__functions_1ga245243cb1da18d2cea18d4b18d846ead}

Send an array of formatted midi data.

Can be used for sysex.

#### Parameters
* `device` the device to use for sending 

* `count` the count of bytes to send 

* `array` the array of bytes

