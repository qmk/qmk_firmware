# group `secure` 

Exposes a set of functionality to act as a virtual padlock for your device ...as long as that padlock is made of paper and it's currently raining.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`secure_is_locked`](#group__secure_1ga123b42cd996c68f2efc9b3494c84f8d6)            | Helper to check if unlocking is currently locked.
`define `[`secure_is_unlocking`](#group__secure_1ga94c74c61bb8fa298e67d00786022671e)            | Helper to check if unlocking is currently in progress.
`define `[`secure_is_unlocked`](#group__secure_1ga993276e79b1dc06560d50b0fd4391ab1)            | Helper to check if unlocking is currently unlocked.
`enum `[`secure_status_t`](#group__secure_1gaf36d8f063112cfb4941819b5c0d5813b)            | Available secure states.
`public `[`secure_status_t`](.build/docs/internals/undefined.md#group__secure_1gaf36d8f063112cfb4941819b5c0d5813b)` `[`secure_get_status`](#group__secure_1ga968df3331fc7fee7d9b9fc3a81eb61f7)`(void)`            | Query current secure state.
`public void `[`secure_lock`](#group__secure_1gacd93c9c823473f7276ed86d42f480485)`(void)`            | Lock down the device.
`public void `[`secure_unlock`](#group__secure_1ga6145d5b4803d6a398337b1035f9365e9)`(void)`            | Force unlock the device.
`public void `[`secure_request_unlock`](#group__secure_1ga1fdae68489874ef6e6d11d932fd47e62)`(void)`            | Begin listening for an unlock sequence.
`public void `[`secure_activity_event`](#group__secure_1ga9b4f79591d59dae7f9b605f8c1e77589)`(void)`            | Flag to the secure subsystem that user activity has happened.
`public void `[`secure_keypress_event`](#group__secure_1gaf1ad593119530b4c132956ea33fee50a)`(uint8_t row,uint8_t col)`            | Flag to the secure subsystem that user has triggered a keypress.
`public void `[`secure_task`](#group__secure_1ga131293f79c4216912291caae9bacb768)`(void)`            | Handle various secure subsystem background tasks.
`public void `[`secure_hook_quantum`](#group__secure_1ga342bca0feb51fa9e481dc70d14cb7770)`(`[`secure_status_t`](.build/docs/internals/undefined.md#group__secure_1gaf36d8f063112cfb4941819b5c0d5813b)` secure_status)`            | quantum hook called when changing secure status device
`public bool `[`secure_hook_user`](#group__secure_1ga80ebfd7bd2d61b015cf1d2c16cdffb4f)`(`[`secure_status_t`](.build/docs/internals/undefined.md#group__secure_1gaf36d8f063112cfb4941819b5c0d5813b)` secure_status)`            | user hook called when changing secure status device
`public bool `[`secure_hook_kb`](#group__secure_1gad5049a2017598a23402b9fef4c230cc5)`(`[`secure_status_t`](.build/docs/internals/undefined.md#group__secure_1gaf36d8f063112cfb4941819b5c0d5813b)` secure_status)`            | keyboard hook called when changing secure status device

## Members

#### `define `[`secure_is_locked`](#group__secure_1ga123b42cd996c68f2efc9b3494c84f8d6) 

Helper to check if unlocking is currently locked.

#### `define `[`secure_is_unlocking`](#group__secure_1ga94c74c61bb8fa298e67d00786022671e) 

Helper to check if unlocking is currently in progress.

#### `define `[`secure_is_unlocked`](#group__secure_1ga993276e79b1dc06560d50b0fd4391ab1) 

Helper to check if unlocking is currently unlocked.

#### `enum `[`secure_status_t`](#group__secure_1gaf36d8f063112cfb4941819b5c0d5813b) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
SECURE_LOCKED            | 
SECURE_PENDING            | 
SECURE_UNLOCKED            | 

Available secure states.

#### `public `[`secure_status_t`](.build/docs/internals/undefined.md#group__secure_1gaf36d8f063112cfb4941819b5c0d5813b)` `[`secure_get_status`](#group__secure_1ga968df3331fc7fee7d9b9fc3a81eb61f7)`(void)` 

Query current secure state.

#### `public void `[`secure_lock`](#group__secure_1gacd93c9c823473f7276ed86d42f480485)`(void)` 

Lock down the device.

#### `public void `[`secure_unlock`](#group__secure_1ga6145d5b4803d6a398337b1035f9365e9)`(void)` 

Force unlock the device.

bypasses user unlock sequence

#### `public void `[`secure_request_unlock`](#group__secure_1ga1fdae68489874ef6e6d11d932fd47e62)`(void)` 

Begin listening for an unlock sequence.

#### `public void `[`secure_activity_event`](#group__secure_1ga9b4f79591d59dae7f9b605f8c1e77589)`(void)` 

Flag to the secure subsystem that user activity has happened.

Call when some user activity has happened and the device should remain unlocked

#### `public void `[`secure_keypress_event`](#group__secure_1gaf1ad593119530b4c132956ea33fee50a)`(uint8_t row,uint8_t col)` 

Flag to the secure subsystem that user has triggered a keypress.

Call to trigger processing of the unlock sequence

#### `public void `[`secure_task`](#group__secure_1ga131293f79c4216912291caae9bacb768)`(void)` 

Handle various secure subsystem background tasks.

#### `public void `[`secure_hook_quantum`](#group__secure_1ga342bca0feb51fa9e481dc70d14cb7770)`(`[`secure_status_t`](.build/docs/internals/undefined.md#group__secure_1gaf36d8f063112cfb4941819b5c0d5813b)` secure_status)` 

quantum hook called when changing secure status device

#### `public bool `[`secure_hook_user`](#group__secure_1ga80ebfd7bd2d61b015cf1d2c16cdffb4f)`(`[`secure_status_t`](.build/docs/internals/undefined.md#group__secure_1gaf36d8f063112cfb4941819b5c0d5813b)` secure_status)` 

user hook called when changing secure status device

#### `public bool `[`secure_hook_kb`](#group__secure_1gad5049a2017598a23402b9fef4c230cc5)`(`[`secure_status_t`](.build/docs/internals/undefined.md#group__secure_1gaf36d8f063112cfb4941819b5c0d5813b)` secure_status)` 

keyboard hook called when changing secure status device

