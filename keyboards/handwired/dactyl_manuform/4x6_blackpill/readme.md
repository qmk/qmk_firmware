ARM Split Dactyl Manuform mechanical keyboard that uses MCP 23017 io port expander on the right side.

* Keyboard Maintainer: [pathnirvana](https://github.com/pathnirvana)
* Hardware Supported: f401/f411 blackpill

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/dactyl_manuform/4x6_blackpill/f401 -km default
    qmk compile -kb handwired/dactyl_manuform/4x6_blackpill/f411 -km default

    make handwired/dactyl_manuform/4x6_blackpill/f401:default
    make handwired/dactyl_manuform/4x6_blackpill/f411:default