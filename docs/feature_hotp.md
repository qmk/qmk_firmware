# HOTP: Two-Factor Authentication

The HOTP features allows you to generate OATH-HOTP two-factor authentication codes. Unlike the more common time-based TOTP, HOTP is based on a counter that increments on every use, so QMK can store the counter in EEPROM without needing a source of time. For more information, please read [RFC 4226](https://tools.ietf.org/html/rfc4226).

## Usage

Add your HOTP configuration to `config.h`:

* `HOTP_OUTPUT_DIGITS` — Number of output digits. Typically between 6 and 8.
* `HOTP_SECRET` — Your secret. This _must_ be formatted in the form of a hex array: 
```c
{0x00, 0x01, ..., 0xFF}
```

!> Make sure you don't commit your secret to git, or everyone will be able to see it! One way to manage this might be to define `HOTP_SECRET` in a separate header file that's included in your `config.h`.


Include the `hotp/hotp.h` header:
```c
#include "hotp/hotp.h"
```

Call `hotp_send()` to send a single code and increment the counter internally.

### Resetting the Counter

The counter value is stored in EEPROM, and when EEPROM is reset, it will set the counter value to 0. To programmatically reset EEPROM, you can call `eeconfig_init()`.

## Debug

In `quantum/hotp/hotp.c`, you can set `HOTP_DEBUG` and `HOTP_DEBUG_VERBOSE` to `1` to output additional debug information.
