# Pointing Device :id=pointing-device

Pointing Device is a generic name for a feature intended to be generic: moving the system pointer around.  There are certainly other options for it - like mousekeys - but this aims to be easily modifiable and lightweight.  You can implement custom keys to control functionality, or you can gather information from other peripherals and insert it directly here - let QMK handle the processing for you.

To enable Pointing Device, uncomment the following line in your rules.mk:

```makefile
POINTING_DEVICE_ENABLE = yes
```

To manipulate the mouse report, you can use the following functions:

* `pointing_device_get_report()` - Returns the current report_mouse_t that represents the information sent to the host computer
* `pointing_device_set_report(report_mouse_t newMouseReport)` - Overrides and saves the report_mouse_t to be sent to the host computer

Keep in mind that a report_mouse_t (here "mouseReport") has the following properties:

* `mouseReport.x` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing movement (+ to the right, - to the left) on the x axis.
* `mouseReport.y` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing movement (+ upward, - downward) on the y axis.
* `mouseReport.v` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing vertical scrolling (+ upward, - downward).
* `mouseReport.h` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing horizontal scrolling (+ right, - left).
* `mouseReport.buttons` - this is a uint8_t in which the last 5 bits are used.  These bits represent the mouse button state - bit 3 is mouse button 5, and bit 7 is mouse button 1.

Once you have made the necessary changes to the mouse report, you need to send it:

* `pointing_device_send()` - Sends the mouse report to the host and zeroes out the report. 

When the mouse report is sent, the x, y, v, and h values are set to 0 (this is done in `pointing_device_send()`, which can be overridden to avoid this behavior).  This way, button states persist, but movement will only occur once.  For further customization, both `pointing_device_init` and `pointing_device_task` can be overridden.

Additionally, by default, `pointing_device_send()` will only send a report when the report has actually changed.  This prevents it from continuously sending mouse reports, which will keep the host system awake.  This behavior can be changed by creating your own `pointing_device_send()` function.

Also, you use the `has_mouse_report_changed(new, old)` function to check to see if the report has changed.

In the following example, a custom key is used to click the mouse and scroll 127 units vertically and horizontally, then undo all of that when released - because that's a totally useful function.  Listen, this is an example:

```c
case MS_SPECIAL:
    report_mouse_t currentReport = pointing_device_get_report();
    if (record->event.pressed) {
        currentReport.v = 127;
        currentReport.h = 127;
        currentReport.buttons |= MOUSE_BTN1;  // this is defined in report.h
    } else {
        currentReport.v = -127;
        currentReport.h = -127;
        currentReport.buttons &= ~MOUSE_BTN1;
    }
    pointing_device_set_report(currentReport);
    pointing_device_send();
    break;
```

Recall that the mouse report is set to zero (except the buttons) whenever it is sent, so the scrolling would only occur once in each case.
