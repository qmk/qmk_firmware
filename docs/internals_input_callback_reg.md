# group `input_callback_reg` {#group__input__callback__reg}

These are the functions you use to register your input callbacks.

The functions are called when the appropriate midi message is matched on the associated device's input.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`midi_register_cc_callback`](#group__input__callback__reg_1ga64ab672abbbe393c9c4a83110c8df718)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)`            | Register a control change message (cc) callback.
`public void `[`midi_register_noteon_callback`](#group__input__callback__reg_1ga3962f276c17618923f1152779552103e)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)`            | Register a note on callback.
`public void `[`midi_register_noteoff_callback`](#group__input__callback__reg_1gac847b66051bd6d53b762958be0ec4c6d)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)`            | Register a note off callback.
`public void `[`midi_register_aftertouch_callback`](#group__input__callback__reg_1gaa95bc901bd9edff956a667c9a69dd01f)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)`            | Register an after touch callback.
`public void `[`midi_register_pitchbend_callback`](#group__input__callback__reg_1ga071a28f02ba14f53de219be70ebd9a48)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)`            | Register a pitch bend callback.
`public void `[`midi_register_songposition_callback`](#group__input__callback__reg_1gaf2adfd79637f3553d8f26deb1ca22ed6)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)`            | Register a song position callback.
`public void `[`midi_register_progchange_callback`](#group__input__callback__reg_1gae6ba1a35a4cde9bd15dd42f87401d127)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)`            | Register a program change callback.
`public void `[`midi_register_chanpressure_callback`](#group__input__callback__reg_1ga39b31f1f4fb93917ce039b958f21b4f5)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)`            | Register a channel pressure callback.
`public void `[`midi_register_songselect_callback`](#group__input__callback__reg_1gaf9aafc76a2dc4b9fdbb4106cbda6ce72)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)`            | Register a song select callback.
`public void `[`midi_register_tc_quarterframe_callback`](#group__input__callback__reg_1ga0a119fada2becc628cb15d753b257e6e)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)`            | Register a tc quarter frame callback.
`public void `[`midi_register_realtime_callback`](#group__input__callback__reg_1ga764f440e857b89084b1a07f9da2ff93a)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_one_byte_func_t func)`            | Register a realtime callback.
`public void `[`midi_register_tunerequest_callback`](#group__input__callback__reg_1gae40ff3ce20bda79fef87da24b8321cb1)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_one_byte_func_t func)`            | Register a tune request callback.
`public void `[`midi_register_sysex_callback`](#group__input__callback__reg_1ga63ce9631b025785c1848d0122d4c4c48)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_sysex_func_t func)`            | Register a sysex callback.
`public void `[`midi_register_fallthrough_callback`](#group__input__callback__reg_1ga7ed189164aa9682862b3181153afbd94)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_var_byte_func_t func)`            | Register fall through callback.
`public void `[`midi_register_catchall_callback`](#group__input__callback__reg_1ga9dbfed568d047a6cd05708f11fe39e99)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_var_byte_func_t func)`            | Register a catch all callback.

## Members

#### `public void `[`midi_register_cc_callback`](#group__input__callback__reg_1ga64ab672abbbe393c9c4a83110c8df718)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1ga64ab672abbbe393c9c4a83110c8df718}

Register a control change message (cc) callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_noteon_callback`](#group__input__callback__reg_1ga3962f276c17618923f1152779552103e)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1ga3962f276c17618923f1152779552103e}

Register a note on callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_noteoff_callback`](#group__input__callback__reg_1gac847b66051bd6d53b762958be0ec4c6d)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1gac847b66051bd6d53b762958be0ec4c6d}

Register a note off callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_aftertouch_callback`](#group__input__callback__reg_1gaa95bc901bd9edff956a667c9a69dd01f)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1gaa95bc901bd9edff956a667c9a69dd01f}

Register an after touch callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_pitchbend_callback`](#group__input__callback__reg_1ga071a28f02ba14f53de219be70ebd9a48)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1ga071a28f02ba14f53de219be70ebd9a48}

Register a pitch bend callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_songposition_callback`](#group__input__callback__reg_1gaf2adfd79637f3553d8f26deb1ca22ed6)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_three_byte_func_t func)` {#group__input__callback__reg_1gaf2adfd79637f3553d8f26deb1ca22ed6}

Register a song position callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_progchange_callback`](#group__input__callback__reg_1gae6ba1a35a4cde9bd15dd42f87401d127)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` {#group__input__callback__reg_1gae6ba1a35a4cde9bd15dd42f87401d127}

Register a program change callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_chanpressure_callback`](#group__input__callback__reg_1ga39b31f1f4fb93917ce039b958f21b4f5)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` {#group__input__callback__reg_1ga39b31f1f4fb93917ce039b958f21b4f5}

Register a channel pressure callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_songselect_callback`](#group__input__callback__reg_1gaf9aafc76a2dc4b9fdbb4106cbda6ce72)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` {#group__input__callback__reg_1gaf9aafc76a2dc4b9fdbb4106cbda6ce72}

Register a song select callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_tc_quarterframe_callback`](#group__input__callback__reg_1ga0a119fada2becc628cb15d753b257e6e)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_two_byte_func_t func)` {#group__input__callback__reg_1ga0a119fada2becc628cb15d753b257e6e}

Register a tc quarter frame callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_realtime_callback`](#group__input__callback__reg_1ga764f440e857b89084b1a07f9da2ff93a)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_one_byte_func_t func)` {#group__input__callback__reg_1ga764f440e857b89084b1a07f9da2ff93a}

Register a realtime callback.

The callback will be called for all of the real time message types.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_tunerequest_callback`](#group__input__callback__reg_1gae40ff3ce20bda79fef87da24b8321cb1)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_one_byte_func_t func)` {#group__input__callback__reg_1gae40ff3ce20bda79fef87da24b8321cb1}

Register a tune request callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_sysex_callback`](#group__input__callback__reg_1ga63ce9631b025785c1848d0122d4c4c48)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_sysex_func_t func)` {#group__input__callback__reg_1ga63ce9631b025785c1848d0122d4c4c48}

Register a sysex callback.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_fallthrough_callback`](#group__input__callback__reg_1ga7ed189164aa9682862b3181153afbd94)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_var_byte_func_t func)` {#group__input__callback__reg_1ga7ed189164aa9682862b3181153afbd94}

Register fall through callback.

This is only called if a more specific callback is not matched and called. For instance, if you don't register a note on callback but you get a note on message the fall through callback will be called, if it is registered.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

#### `public void `[`midi_register_catchall_callback`](#group__input__callback__reg_1ga9dbfed568d047a6cd05708f11fe39e99)`(`[`MidiDevice`](#struct__midi__device)` * device,midi_var_byte_func_t func)` {#group__input__callback__reg_1ga9dbfed568d047a6cd05708f11fe39e99}

Register a catch all callback.

If registered, the catch all callback is called for every message that is matched, even if a more specific or the fallthrough callback is registered.

#### Parameters
* `device` the device associate with 

* `func` the callback function to register

