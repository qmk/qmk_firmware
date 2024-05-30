# Digitizer {#digitizer}

Digitizers allow the mouse cursor to be placed at absolute coordinates, unlike the [Pointing Device](feature_pointing_device) feature which applies relative displacements.

This feature implements a stylus device with a tip switch and barrel switch (generally equivalent to the primary and secondary mouse buttons respectively). Tip pressure is not currently implemented.

## Usage {#usage}

Add the following to your `rules.mk`:

```make
DIGITIZER_ENABLE = yes
```

## Positioning {#positioning}

The X and Y coordinates are normalized, meaning their value must be set between 0 and 1. For the X component, the value `0` is the leftmost position, whereas the value `1` is the rightmost position. Similarly for the Y component, `0` is at the top and `1` at the bottom.

::: tip
Since there is no display attached, the OS will likely map these coordinates to the virtual desktop. This may be important to know if you have multiple monitors.
:::

## Examples {#examples}

This example simply places the cursor in the middle of the screen:

```c
digitizer_in_range_on();
digitizer_set_position(0.5, 0.5);
```

The "in range" indicator is required to be on for the change in coordinates to be taken. It can then be turned off again to signal the end of the digitizer interaction, but it is not strictly required.

You can also modify the digitizer state directly, if you need to change multiple fields in a single report:

```c
digitizer_state.in_range = true;
digitizer_state.dirty = true;
digitizer_flush();
```

`digitizer_state` is a struct of type `digitizer_t`.


## API {#api}

### `struct digitizer_t` {#api-digitizer-t}

Contains the state of the digitizer.

#### Members {#api-digitizer-t-members}

 - `bool in_range`  
   Indicates to the host that the contact is within range (ie. close to or in contact with the digitizer surface).
 - `bool tip`  
   The state of the tip switch.
 - `bool barrel`  
   The state of the barrel switch.
 - `float x`  
   The X coordinate of the digitizer contact.
 - `float y`  
   The Y coordinate of the digitizer contact.
 - `bool dirty`  
   Whether the current state needs to be sent to the host.

---

### `void digitizer_flush(void)` {#api-digitizer-flush}

Send the digitizer report to the host if it is marked as dirty.

---

### `void digitizer_in_range_on(void)` {#api-digitizer-in-range-on}

Assert the "in range" indicator, and flush the report.

---

### `void digitizer_in_range_off(void)` {#api-digitizer-in-range-off}

Deassert the "in range" indicator, and flush the report.

---

### `void digitizer_tip_switch_on(void)` {#api-digitizer-tip-switch-on}

Assert the tip switch, and flush the report.

---

### `void digitizer_tip_switch_off(void)` {#api-digitizer-tip-switch-off}

Deassert the tip switch, and flush the report.

---

### `void digitizer_barrel_switch_on(void)` {#api-digitizer-barrel-switch-on}

Assert the barrel switch, and flush the report.

---

### `void digitizer_barrel_switch_off(void)` {#api-digitizer-barrel-switch-off}

Deassert the barrel switch, and flush the report.

---

### `void digitizer_set_position(float x, float y)` {#api-digitizer-set-position}

Set the absolute X and Y position of the digitizer contact, and flush the report.

#### Arguments {#api-digitizer-set-position-arguments}

 - `float x`  
   The X value of the contact position, from 0 to 1.
 - `float y`  
   The Y value of the contact position, from 0 to 1.
