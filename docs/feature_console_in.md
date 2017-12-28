# Console In

The "Console" in QMK refers to PJRC's vendor page of `0xFF31` and usage page of `0x74` - this is mainly used for sending debug statements to the computer that can be read via the QMK Toolbox (recommended), or HID listen.

When `#define CONSOLE_IN_ENABLE` is placed in the `config.h` file, the keyboard will also listen to messages sent to the keyboard, will be able to respond in a custom way, defined at the `quantum`, `kb`, or `user` level. A keymap's example might look like this:

```c
void process_console_data_user(uint8_t * data, uint8_t length) {
  switch (data[0]) {
    case 0x05:
      print("Sending back a message to the computer\n");
      break;
  }
}
```

Which will execute when a report is sent to the keyboard when the first byte is `0x05`.

## Default actions (defined at the `quantum` level)

When the first byte is:

* `0x01`: Print "Saying hello\n" via the console, and play the audio on song
* `0xFE`: Enter the bootloader - only works when `CONSOLE_IN_BOOTLOADER` is defined in the `config.h`

This needs to be fleshed out a bit more with some sort of versioning.