# The Redox keyboard

<p align="center">
<img src="https://github.com/mattdibi/redox-keyboard/raw/master/img/redox-logo.png" alt="Redox logo" width="600"/>
</p>

<p align="center">
<img src="https://github.com/mattdibi/redox-keyboard/raw/master/img/redox-pcb2.jpg" alt="Redox PCB rev1.0" width="600"/>
</p>

**Redox**: the **R**educed **E**rgo**dox** project. More information and building instruction [here](https://github.com/mattdibi/redox-keyboard).

- Keyboard Maintainer: [Mattia Dal Ben](https://github.com/mattdibi)  
- Hardware Supported: Redox PCB rev1.0 w/ Pro Micro  
- Hardware Availability: [Falbatech](https://falba.tech/product-category/keyboard-parts/redox-parts/)

Make example for this keyboard (after setting up your build environment):

```sh
make redox/rev1:default
```

Example of flashing this keyboard:

```sh
make redox/rev1:default:avrdude
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
