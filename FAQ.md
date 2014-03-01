# Degug Console
## 'hid_listen' can't find device
When debug console of your device is not ready you will see like this:

    Waiting for device:.........

once the device is pluged in then 'hid_listen' finds it you will get this message:

    Waiting for new device:.........................
    Listening:

Check these if you can't get this 'Listening:' message:
- build with 'CONSOLE_ENABLE=yes' in Makefile


# NKRO

# PS/2 mouse support