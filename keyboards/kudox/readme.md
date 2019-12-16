# The Kudox keyboard

<p align="center">
<img src="https://raw.githubusercontent.com/kumaokobo/kudox-keyboard/master/img/kudox.png" alt="Kudox logo" width="600"/>
</p>

<p align="center">
<img src="https://raw.githubusercontent.com/kumaokobo/kudox-keyboard/master/img/kudox-pcb.jpg" alt="Kudox PCB rev2.0" width="600"/>
</p>

- Keyboard Maintainer: [Kumao Kobo](https://github.com/kumaokobo)  
- Hardware Supported: Kudox PCB rev1.0 rev2.0 w/ Pro Micro  

Make example for this keyboard (after setting up your build environment):

```sh
make kudox/rev2:default
```


Example of flashing this keyboard:

```sh
make kudox/rev2:default:flash
```

*keymaps/default is for rev2.0. If you want to use rev1.0, you should remove Left-06 key and Right-06 key.*

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
