# group `digitizer` 

HID Digitizer

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`digitizer_flush`](#group__digitizer_1ga2f0ca7925ebf293c0e2c623ec41a386d)`(void)`            | Send the digitizer report to the host if it is marked as dirty.
`public void `[`digitizer_in_range_on`](#group__digitizer_1ga00f949f2d7e4e09d8a5bbc090fc78eb8)`(void)`            | Assert the "in range" indicator, and flush the report.
`public void `[`digitizer_in_range_off`](#group__digitizer_1gabe4bf2d9168ffc3b68ffceeebd542c2d)`(void)`            | Deassert the "in range" indicator, and flush the report.
`public void `[`digitizer_tip_switch_on`](#group__digitizer_1ga45a4bff373ac3cb13525135e47430a4d)`(void)`            | Assert the tip switch, and flush the report.
`public void `[`digitizer_tip_switch_off`](#group__digitizer_1gad0d1db66781ff2c9ea126b843dd0accb)`(void)`            | Deassert the tip switch, and flush the report.
`public void `[`digitizer_barrel_switch_on`](#group__digitizer_1gaf27cd1194daed947a09ecf621a958bb1)`(void)`            | Assert the barrel switch, and flush the report.
`public void `[`digitizer_barrel_switch_off`](#group__digitizer_1ga8a5ca5c394f6ee28da4929d9c324d9df)`(void)`            | Deassert the barrel switch, and flush the report.
`public void `[`digitizer_set_position`](#group__digitizer_1ga478e95afcb52a17c038cc705c889fc51)`(float x,float y)`            | Set the absolute X and Y position of the digitizer contact, and flush the report.
`public void `[`host_digitizer_send`](#group__digitizer_1ga82bd010c3ad9a37cd34cfe80003e0111)`(`[`digitizer_t`](.build/docs/internals/digitizer.md#structdigitizer__t)` * digitizer)`            | 
`struct `[`digitizer_t`](#structdigitizer__t) | 

## Members

#### `public void `[`digitizer_flush`](#group__digitizer_1ga2f0ca7925ebf293c0e2c623ec41a386d)`(void)` 

Send the digitizer report to the host if it is marked as dirty.

#### `public void `[`digitizer_in_range_on`](#group__digitizer_1ga00f949f2d7e4e09d8a5bbc090fc78eb8)`(void)` 

Assert the "in range" indicator, and flush the report.

#### `public void `[`digitizer_in_range_off`](#group__digitizer_1gabe4bf2d9168ffc3b68ffceeebd542c2d)`(void)` 

Deassert the "in range" indicator, and flush the report.

#### `public void `[`digitizer_tip_switch_on`](#group__digitizer_1ga45a4bff373ac3cb13525135e47430a4d)`(void)` 

Assert the tip switch, and flush the report.

#### `public void `[`digitizer_tip_switch_off`](#group__digitizer_1gad0d1db66781ff2c9ea126b843dd0accb)`(void)` 

Deassert the tip switch, and flush the report.

#### `public void `[`digitizer_barrel_switch_on`](#group__digitizer_1gaf27cd1194daed947a09ecf621a958bb1)`(void)` 

Assert the barrel switch, and flush the report.

#### `public void `[`digitizer_barrel_switch_off`](#group__digitizer_1ga8a5ca5c394f6ee28da4929d9c324d9df)`(void)` 

Deassert the barrel switch, and flush the report.

#### `public void `[`digitizer_set_position`](#group__digitizer_1ga478e95afcb52a17c038cc705c889fc51)`(float x,float y)` 

Set the absolute X and Y position of the digitizer contact, and flush the report.

#### Parameters
* `x` The X value of the contact position, from 0 to 1. 

* `y` The Y value of the contact position, from 0 to 1.

#### `public void `[`host_digitizer_send`](#group__digitizer_1ga82bd010c3ad9a37cd34cfe80003e0111)`(`[`digitizer_t`](.build/docs/internals/digitizer.md#structdigitizer__t)` * digitizer)` 

# struct `digitizer_t` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public bool `[`in_range`](#structdigitizer__t_1a892bdb0283b79d3a2f522e235827a466) | 
`public bool `[`tip`](#structdigitizer__t_1af805d442a9b04f396e165fe1d22edb12) | 
`public bool `[`barrel`](#structdigitizer__t_1a1b9fd2b48c6e2325de54ef5050e0999d) | 
`public float `[`x`](#structdigitizer__t_1ad0da36b2558901e21e7a30f6c227a45e) | 
`public float `[`y`](#structdigitizer__t_1aa4f0d3eebc3c443f9be81bf48561a217) | 
`public bool `[`dirty`](#structdigitizer__t_1ad25edacba00e4d0666a9959053b7cc10) | 

## Members

#### `public bool `[`in_range`](#structdigitizer__t_1a892bdb0283b79d3a2f522e235827a466) 

#### `public bool `[`tip`](#structdigitizer__t_1af805d442a9b04f396e165fe1d22edb12) 

#### `public bool `[`barrel`](#structdigitizer__t_1a1b9fd2b48c6e2325de54ef5050e0999d) 

#### `public float `[`x`](#structdigitizer__t_1ad0da36b2558901e21e7a30f6c227a45e) 

#### `public float `[`y`](#structdigitizer__t_1aa4f0d3eebc3c443f9be81bf48561a217) 

#### `public bool `[`dirty`](#structdigitizer__t_1ad25edacba00e4d0666a9959053b7cc10) 

