# bottilabo layout
 [twitter: @bottilabo](https://twitter.com/bottilabo)
 https://github.com/bottilabo/qmk-harmonize
 
## features
- QWERTY,colemak,dvorak,arensito... many layout
- language specific input mode(for now, Japanese Nicola,Tron,New JIS,Naginata-shiki,Katana-shiki,M-shiki)
- simultaneous keying, pre shift, post shift

please refer [qmk_firmware/users/bottilabo/readme.md](../../../../users/bottilabo/readme.md)

## crkbd

### build example
```
make crkbd:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBIM1=IM_TRON -DPLUG1=PLUG_OLED'
```

