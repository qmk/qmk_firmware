# tobiasvl's ISO layout for HS60

![Layout image](https://imgur.com/6go4vQV.png)

Default layer is normal ISO and Fn layer is used for RGB functions, Volume control and arrow cluster

### Specifics

* ISO
* SpaceFN
* Caps Lock is replaced by a Fn key
* Fn keys activate layers momentarily while held, and toggle layers when tapped twice
* Fn+q is PgUp, Fn+e is PgDn

## Building

* Unplug keyboard
* Hold Esc
* Plug in keyboard

```
sudo make hs60/v2:tobiasvl:dfu-util
```

