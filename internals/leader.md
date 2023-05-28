# group `leader` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`leader_start_user`](#group__leader_1gae7b6746b0c6bd83cada1e770a7d8315d)`(void)`            | User callback, invoked when the leader sequence begins.
`public void `[`leader_end_user`](#group__leader_1ga20986d88ffc5f21f00eab4b5e9a03188)`(void)`            | User callback, invoked when the leader sequence ends.
`public void `[`leader_start`](#group__leader_1ga1f5dad3a2df12d29023e48852ff638ba)`(void)`            | Begin the leader sequence, resetting the buffer and timer.
`public void `[`leader_end`](#group__leader_1ga7ecc035ad29aed6d5ee3848725234b6c)`(void)`            | End the leader sequence.
`public void `[`leader_task`](#group__leader_1gaa451b483f86840a1a3a773a074b73019)`(void)`            | 
`public bool `[`leader_sequence_active`](#group__leader_1gab52594aae07ec2f59cc6cc00dce9cc0b)`(void)`            | Whether the leader sequence is active.
`public bool `[`leader_sequence_add`](#group__leader_1ga0b9825ee3240ffac41837664d10c36ff)`(uint16_t keycode)`            | Add the given keycode to the sequence buffer.
`public bool `[`leader_sequence_timed_out`](#group__leader_1gadb5905415a54ffab4a47a8d3227b3942)`(void)`            | Whether the leader sequence has reached the timeout.
`public void `[`leader_reset_timer`](#group__leader_1ga5a9246dc3f952a5522c188f747ce0722)`(void)`            | Reset the leader sequence timer.
`public bool `[`leader_sequence_one_key`](#group__leader_1ga6bcdd330c94f7074361c21ad8ee901fd)`(uint16_t kc)`            | Check the sequence buffer for the given keycode.
`public bool `[`leader_sequence_two_keys`](#group__leader_1ga6a09c0ae645990e9d219c62244c30e42)`(uint16_t kc1,uint16_t kc2)`            | Check the sequence buffer for the given keycodes.
`public bool `[`leader_sequence_three_keys`](#group__leader_1ga0dd4e91b428947bfb5ddb6fd09b29c11)`(uint16_t kc1,uint16_t kc2,uint16_t kc3)`            | Check the sequence buffer for the given keycodes.
`public bool `[`leader_sequence_four_keys`](#group__leader_1ga5f71174f1afa31112108336e0d782ff2)`(uint16_t kc1,uint16_t kc2,uint16_t kc3,uint16_t kc4)`            | Check the sequence buffer for the given keycodes.
`public bool `[`leader_sequence_five_keys`](#group__leader_1ga2c565e3c2d21eac4b23db75a15a9fa2d)`(uint16_t kc1,uint16_t kc2,uint16_t kc3,uint16_t kc4,uint16_t kc5)`            | Check the sequence buffer for the given keycodes.

## Members

#### `public void `[`leader_start_user`](#group__leader_1gae7b6746b0c6bd83cada1e770a7d8315d)`(void)` 

User callback, invoked when the leader sequence begins.

#### `public void `[`leader_end_user`](#group__leader_1ga20986d88ffc5f21f00eab4b5e9a03188)`(void)` 

User callback, invoked when the leader sequence ends.

#### `public void `[`leader_start`](#group__leader_1ga1f5dad3a2df12d29023e48852ff638ba)`(void)` 

Begin the leader sequence, resetting the buffer and timer.

#### `public void `[`leader_end`](#group__leader_1ga7ecc035ad29aed6d5ee3848725234b6c)`(void)` 

End the leader sequence.

#### `public void `[`leader_task`](#group__leader_1gaa451b483f86840a1a3a773a074b73019)`(void)` 

#### `public bool `[`leader_sequence_active`](#group__leader_1gab52594aae07ec2f59cc6cc00dce9cc0b)`(void)` 

Whether the leader sequence is active.

#### `public bool `[`leader_sequence_add`](#group__leader_1ga0b9825ee3240ffac41837664d10c36ff)`(uint16_t keycode)` 

Add the given keycode to the sequence buffer.

If `LEADER_NO_TIMEOUT` is defined, the timer is reset if the buffer is empty.

#### Parameters
* `keycode` The keycode to add.

#### Returns
`true` if the keycode was added, `false` if the buffer is full.

#### `public bool `[`leader_sequence_timed_out`](#group__leader_1gadb5905415a54ffab4a47a8d3227b3942)`(void)` 

Whether the leader sequence has reached the timeout.

If `LEADER_NO_TIMEOUT` is defined, the buffer must also contain at least one key.

#### `public void `[`leader_reset_timer`](#group__leader_1ga5a9246dc3f952a5522c188f747ce0722)`(void)` 

Reset the leader sequence timer.

#### `public bool `[`leader_sequence_one_key`](#group__leader_1ga6bcdd330c94f7074361c21ad8ee901fd)`(uint16_t kc)` 

Check the sequence buffer for the given keycode.

#### Parameters
* `kc` The keycode to check.

#### Returns
`true` if the sequence buffer matches.

#### `public bool `[`leader_sequence_two_keys`](#group__leader_1ga6a09c0ae645990e9d219c62244c30e42)`(uint16_t kc1,uint16_t kc2)` 

Check the sequence buffer for the given keycodes.

#### Parameters
* `kc1` The first keycode to check. 

* `kc2` The second keycode to check.

#### Returns
`true` if the sequence buffer matches.

#### `public bool `[`leader_sequence_three_keys`](#group__leader_1ga0dd4e91b428947bfb5ddb6fd09b29c11)`(uint16_t kc1,uint16_t kc2,uint16_t kc3)` 

Check the sequence buffer for the given keycodes.

#### Parameters
* `kc1` The first keycode to check. 

* `kc2` The second keycode to check. 

* `kc3` The third keycode to check.

#### Returns
`true` if the sequence buffer matches.

#### `public bool `[`leader_sequence_four_keys`](#group__leader_1ga5f71174f1afa31112108336e0d782ff2)`(uint16_t kc1,uint16_t kc2,uint16_t kc3,uint16_t kc4)` 

Check the sequence buffer for the given keycodes.

#### Parameters
* `kc1` The first keycode to check. 

* `kc2` The second keycode to check. 

* `kc3` The third keycode to check. 

* `kc4` The fourth keycode to check.

#### Returns
`true` if the sequence buffer matches.

#### `public bool `[`leader_sequence_five_keys`](#group__leader_1ga2c565e3c2d21eac4b23db75a15a9fa2d)`(uint16_t kc1,uint16_t kc2,uint16_t kc3,uint16_t kc4,uint16_t kc5)` 

Check the sequence buffer for the given keycodes.

#### Parameters
* `kc1` The first keycode to check. 

* `kc2` The second keycode to check. 

* `kc3` The third keycode to check. 

* `kc4` The fourth keycode to check. 

* `kc5` The fifth keycode to check.

#### Returns
`true` if the sequence buffer matches.

