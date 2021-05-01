# Foire aux questions sur la compilation

Cette page couvre les questions concernant la compilation de QMK. Si vous ne l'avez pas encore fait, vous devriez lire les guides [Configuration de l'environnement de build](getting_started_build_tools.md) et [Instructions pour Make](getting_started_make_guide.md).

## Je ne peux pas programmer sous Linux

Vous aurez besoin des permissions appropriées pour utiliser un périphérique. Pour les utilisateurs de Linux, référez-vous aux instructions concernant les règles `udev` ci-dessous. Si `udev` vous pose des problèmes, une alternative est d'utiliser la commande `sudo`. Si vous ne connaissez pas cette commande, référez-vous à son manuel d'utilisation en utilisant `man sudo` ou [regardez cette page](https://linux.die.net/man/8/sudo).

Un exemple utilisant `sudo`, lorsque votre contrôleur est un ATMega32u4 :

    $ sudo dfu-programmer atmega32u4 erase --force
    $ sudo dfu-programmer atmega32u4 flash your.hex
    $ sudo dfu-programmer atmega32u4 reset

ou simplement :

    $ sudo make <keyboard>:<keymap>:dfu

Veuillez noter que lancer `make` avec `sudo` est généralement une **mauvaise** idée, et vous devriez préférer une des méthodes précédente, si possible.

### Règles `udev` pour Linux

Sous Linux, vous aurez besoin des permissions appropriées pour accéder au MCU (le micro-contrôleur). Vous avez le choix d'utiliser `sudo` en flashant le firmware, ou placer ces fichiers dans `/etc/udev/rules.d`. Une fois ajouté, lancez les commandes suivantes :

```console
sudo udevadm control --reload-rules
sudo udevadm trigger
```

**/etc/udev/rules.d/50-atmel-dfu.rules:**
```
# Atmel ATMega32U4
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff4", MODE:="0666"
# Atmel USBKEY AT90USB1287
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ffb", MODE:="0666"
# Atmel ATMega32U2
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff0", MODE:="0666"
```

**/etc/udev/rules.d/52-tmk-keyboard.rules:**
```
# tmk keyboard products     https://github.com/tmk/tmk_keyboard
SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", MODE:="0666"
```

**/etc/udev/rules.d/54-input-club-keyboard.rules:**

```
# Input Club keyboard bootloader
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1c11", MODE:="0666"
```

**/etc/udev/rules.d/55-catalina.rules:**
```
# ModemManager should ignore the following devices
ATTRS{idVendor}=="2a03", ENV{ID_MM_DEVICE_IGNORE}="1"
ATTRS{idVendor}=="2341", ENV{ID_MM_DEVICE_IGNORE}="1"
```

**Note:** Le filtrage utilisant ModemManager fonctionnera uniquement si vous n'êtes pas en mode strict. Les commandes suivantes peuvent changer cette option :

```console
sudo sed -i 's/--filter-policy=strict/--filter-policy=default/' /lib/systemd/system/ModemManager.service
sudo systemctl daemon-reload
sudo systemctl restart ModemManager
```

**/etc/udev/rules.d/56-dfu-util.rules:**

```
# stm32duino
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1eaf", ATTRS{idProduct}=="0003", MODE:="0666"
# Generic stm32
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="df11", MODE:="0666"
```

### Le périphérique sériel n'est pas détecté en mode bootloader sous Linux

Assurez-vous que votre kernel ait un support approprié pour votre périphérique. Si votre périphérique utilise USB ACM, par exemple pour les Pro Micro (AtMega32u4), assurez-vous d'inclure `CONFIG_USB_ACM=y`. D'autres périphériques peuvent avoir besoin de `USB_SERIAL` et de ses sous-options.

## Périphérique inconnu pour le bootloader DFU

Les problèmes rencontrés lorsque l'on flash des claviers sous Windows sont, la plupart du temps, dus à une installation du mauvais pilote, ou un pilote manquant.

Relancer le script d'installation de QMK (`./util/qmk_install.sh` situé dans répertoire `qmk_firmware`sous MSYS2 ou WSL) ou réinstaller la QMK Toolbox peut résoudre le problème. Une alternative est de télécharger et lancer manuellement le package [`qmk_driver_installer`](https://github.com/qmk/qmk_driver_installer).

Si vous rencontrez toujours des problèmes, essayez de télécharger et lancer Zadig. Voir [Installation du driver du bootloader avec Zadig](driver_installation_zadig.md) pour plus d'informations.

## USB VID et PID

Vous pouvez utiliser l'ID de votre choix en modifier `config.h`. Il y a peu de chance de conflit avec d'autres produits.

La plupart des boards QMK utilisent `0xFEED` comme vendor ID. Vérifiez les autres claviers pour être sûr de choisir un Product ID unique.

Étudiez aussi ce ticket
https://github.com/tmk/tmk_keyboard/issues/150

Vous pouvez acheter un VID:PID unique ici. Je ne pense pas que ce soit nécessaire pour un usage personnel.
- http://www.obdev.at/products/vusb/license.html
- http://www.mcselec.com/index.php?page=shop.product_details&flypage=shop.flypage&product_id=92&option=com_phpshop&Itemid=1

## BOOTLOADER_SIZE pour AVR

Notez que la taille du bootloader pour les Teensy2.0++ est de 2048bytes. Quelques Makefiles peuvent contenir une erreur et avoir le mauvais commentaire.

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 2048
#   Atmel DFU loader 4096       (TMK Alt Controller)
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=2048
```

## `avr-gcc: internal compiler error: Abort trap: 6 (program cc1)` sous MacOS

C'est un problème de mise à jour avec brew, causée par des liens symboliques (symlinks) dont dépend avr-gcc qui sont détruits.

La solution est de supprimer et réinstaller tous les modules affectés.

```
brew rm avr-gcc
brew rm dfu-programmer
brew rm dfu-util
brew rm gcc-arm-none-eabi
brew rm avrdude
brew install avr-gcc
brew install dfu-programmer
brew install dfu-util
brew install gcc-arm-none-eabi
brew install avrdude
```

### avr-gcc 8.1 et LUFA

Si vous avez mis à jour votre avr-gcc au-dessus de la version 7, vous risquez de voir des erreurs impliquant LUA. Par exemple :

`lib/lufa/LUFA/Drivers/USB/Class/Device/AudioClassDevice.h:380:5: error: 'const' attribute on function returning 'void'`

Pour le moment, vous devrez revenir à la version 7 de avr-gcc dans brew.

```
brew uninstall --force avr-gcc
brew install avr-gcc@8
brew link --force avr-gcc@8
```

### Je viens de flasher mon clavier et il ne fait rien/l'appui des touches n'est pas enregistré - c'est aussi un ARM(rev6 plank, clueboard 60, hs60v2, etc.) (Février 2019)

A cause de la manière dont les EEPROM fonctionnent sur les puces ARM, les options sauvegardées peuvent ne plus être valides. Ceci affecte les calques par défaut et *peut*, sous certaines conditions que nous essayons encore de déterminer, rendre le clavier inutilisable. Réinitialiser l'EEPROM corrigera le problème.

[Réinitialiser EEPROM sur Planck rev6](https://cdn.discordapp.com/attachments/473506116718952450/539284620861243409/planck_rev6_default.bin) peut être utilisé pour forcer une réinitialisation d'EEPROM. Une fois cette image flashée, flashez à nouveau votre firmware standard. Cela devrait rétablir le fonctionnement de votre clavier.
Si bootmagic est activé dans n'importe quel forme, vous devriez être capable de faire aussi ceci (regardez  [Documentation Bootmagic](feature_bootmagic.md) et les informations spécifiques à votre clavier).
