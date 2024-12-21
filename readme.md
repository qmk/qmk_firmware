# Fork of QMK !

This fork contains my keymaps and special configs for the following keyboards :
- Kyria
- Planck rev7
- Iris

In order to compile the firmwares :

- Kyria : 
```bash
git switch sheep-planck
sudo qmk flash -kb splitkb/kyria/rev2 -km sheep -bl dfu
#sudo qmk flash -kb splitkb/kyria/rev2:sheep -km sheep -bl dfu
```

- Planck :
```bash
git switch sheep-planck
sudo qmk compile -kb planck/rev7 -km sheep
sudo qmk flash -kb planck/rev7 -km sheep
```

- Iris :
```bash
git switch sheep-iris
sudo qmk flash -kb keebio/iris/rev3 -km sheep
```

- HHKB :
```bash
git switch sheep-hhkb
sudo qmk flash -kb hhkb/ansi -km sheep
```

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [Docsify](https://docsify.js.org/) and hosted on [GitHub](/docs/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls), or by clicking the "Edit this page" link at the bottom of any page.

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
