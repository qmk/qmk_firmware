# melka's keymap for XIUDI's 60% XD60 rev3 PCB

## Additional Notes
Custom Keymap for XD60 rev3. French Mac layout.

## Security Note
This keymap includes macros for entering passwords.

While it is possible to use macros to send passwords, credit card numbers,
and other sensitive information it is a supremely bad idea to do so. Anyone who gets a hold
of your keyboard will be able to access that information by opening a text editor.

Use this functionnality at your own risk.

To define your password, rename passwd_template.h file to passwd.h and edit the defines inside.

## Build

To build this keymap, simply run:

    make xd60/rev3:melka  # XD60 rev3
