# coderkun’s Neo2 layout for the ErgoDox EZ

The idea of this layout is to use it for [Neo2](http://www.neo-layout.org) but also provide layers to use QWERTZ with activated Neo driver and to use (basic) Neo when no driver is available (standard QWERTZ driver is active) (e. g. on other computers, in virtual machines) and to make heavily use of thumb keys.

The main goal of the default layer is to provide a complete symmetric layout with each modifier equally placed for both hands (mirror, of course).

It also features a layer for additional keys like F-keys (F1 – F12), some mouse keys and (hopefully in the near future) some useful Unicode symbols.


## Layers

0. Default layer for Neo2
1. Poor man’s QWERTZ
2. Poor man’s Neo
3. F-keys, mouse keys und Unicode symbols
4. Neo’s software layers 4 rebuilt in hardware


## Build

1. Enable Unicode in Makefile

    ```
    UNICODE_ENABLE   = yes
    ```
2. Build as usual

    ```
    make clean
    make KEYMAP=coderkun_neo2
    ```
