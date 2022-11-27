# group `programmable_button` 

HID Programmable Buttons

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`programmable_button_clear`](#group__programmable__button_1ga79c2466a8024807d919fcd149b16607d)`(void)`            | Clear the programmable button report.
`public void `[`programmable_button_add`](#group__programmable__button_1ga3626e2369fa1f6305a690462ec75198e)`(uint8_t index)`            | Set the state of a button.
`public void `[`programmable_button_remove`](#group__programmable__button_1ga36c00d75b88d8f1010fd3caefa2512ac)`(uint8_t index)`            | Reset the state of a button.
`public void `[`programmable_button_register`](#group__programmable__button_1gad23c98be75c13bcb83aa606f020394ba)`(uint8_t index)`            | Set the state of a button, and flush the report.
`public void `[`programmable_button_unregister`](#group__programmable__button_1gabcd05104c5668a4b7516547df4a26a69)`(uint8_t index)`            | Reset the state of a button, and flush the report.
`public bool `[`programmable_button_is_on`](#group__programmable__button_1ga68c867522ec5db786aa380ea6d80546b)`(uint8_t index)`            | Get the state of a button.
`public void `[`programmable_button_flush`](#group__programmable__button_1ga879ab021dea8d662621487a317b42ecc)`(void)`            | Send the programmable button report to the host.
`public uint32_t `[`programmable_button_get_report`](#group__programmable__button_1ga01116a2092003359d4c099743f3a3ee9)`(void)`            | Get the programmable button report.
`public void `[`programmable_button_set_report`](#group__programmable__button_1gaf321be669ef841e83fe7c03fdd558795)`(uint32_t report)`            | Set the programmable button report.

## Members

#### `public void `[`programmable_button_clear`](#group__programmable__button_1ga79c2466a8024807d919fcd149b16607d)`(void)` 

Clear the programmable button report.

#### `public void `[`programmable_button_add`](#group__programmable__button_1ga3626e2369fa1f6305a690462ec75198e)`(uint8_t index)` 

Set the state of a button.

#### Parameters
* `index` The index of the button to press, from 0 to 31.

#### `public void `[`programmable_button_remove`](#group__programmable__button_1ga36c00d75b88d8f1010fd3caefa2512ac)`(uint8_t index)` 

Reset the state of a button.

#### Parameters
* `index` The index of the button to release, from 0 to 31.

#### `public void `[`programmable_button_register`](#group__programmable__button_1gad23c98be75c13bcb83aa606f020394ba)`(uint8_t index)` 

Set the state of a button, and flush the report.

#### Parameters
* `index` The index of the button to press, from 0 to 31.

#### `public void `[`programmable_button_unregister`](#group__programmable__button_1gabcd05104c5668a4b7516547df4a26a69)`(uint8_t index)` 

Reset the state of a button, and flush the report.

#### Parameters
* `index` The index of the button to release, from 0 to 31.

#### `public bool `[`programmable_button_is_on`](#group__programmable__button_1ga68c867522ec5db786aa380ea6d80546b)`(uint8_t index)` 

Get the state of a button.

#### Parameters
* `index` The index of the button to check, from 0 to 31.

#### Returns
`true` if the button is pressed.

#### `public void `[`programmable_button_flush`](#group__programmable__button_1ga879ab021dea8d662621487a317b42ecc)`(void)` 

Send the programmable button report to the host.

#### `public uint32_t `[`programmable_button_get_report`](#group__programmable__button_1ga01116a2092003359d4c099743f3a3ee9)`(void)` 

Get the programmable button report.

#### Returns
The bitmask of programmable button states.

#### `public void `[`programmable_button_set_report`](#group__programmable__button_1gaf321be669ef841e83fe7c03fdd558795)`(uint32_t report)` 

Set the programmable button report.

#### Parameters
* `report` A bitmask of programmable button states.

