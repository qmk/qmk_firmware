# Flasher votre clavier

Maintenant que vous avez réussi à compiler votre firmware, il ne reste qu'à le flasher sur votre appareil.

## Flasher votre clavier avec QMK Toolbox

Le plus simple moyen de flasher votre clavier est d'utiliser [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases).

Cependant, QMK Toolbox n'est seulement disponible que sur Windows et macOS pour i vous utilisez Linux ou que vous souhaitez travailler en ligne de commande vous allez de voir suivre [cette méthode](newbs_flashing.md#flash-your-keyboard-from-the-command-line).

### Charger le firmware dans QMK Toolbox

Commencer par ouvrir l'application QMK Toolbox. Vous allez devoir localiser votre fichier de firmware dans l'explorateur de fichier ou Finder. Votre firmware de clavier peut être en deux formats différents : `hex` ou `.bin`. QMK éssaie de copier le fichier approprié à la racine du dossier `qmk_firmware`.

?> Si vous êtes sur Windows ou macOS il y a des commandes que vous pouvez facilement utiliser pour ouvrir le bon dossier.

?> Windows:

    start .

?> macOS:

    open .

Le fichier du firmware doit être nommé de la sorte :

    <keyboard_name>_<keymap_name>.{bin,hex}

Par exemple, le `plank/rev5` avec une keymap `default` vas avoir ce nom de fichier :

    planck_rev5_default.hex

Une fois que vous avez localisé votre fichier de firmware, vous pouvez le faire glisser dans la zone « Local file » (Fichier local) de QMK Toolbox ou alors cliquer sur "Open" et naviguer jusqu'à ou il se trouve.

### Mettre votre clavier en mode DFU (Bootloader)

Pour pouvoir flasher votre firmware personalisé vous allez devoir mettre votre clavier dans un mode spécial permettant le flash. Pendant que ce clavier sera dasn ce mode pour ne pourrez plus saisir de texte ou utiliser votre clavier. Il est vraiment important que vous ne débranchiez pas votre appareil ou que vous n'interrompiez le processus de flash.

Il éxiste différents moyen pour atteindre ce mode selon le clavier dont il est question. Si votre PCB fonctionne actuellement avec QMK ou TMK et que celui-ci n'a pas de particularité alors essayez le processus suivant :

* Verrouillez la touche shift et pressez `Pause`.
* Verrouillez la touche shift et pressez `B`
* Débranchez votre clavier, verrouillez la barre espace et `B` et branchez le tout en attendant une seconde avant de relacher les touches.
* Presser le bouton `RESET` qui se trouve en bas de votre PCB.
* Localisez les pins labellisés `BOOT0` et `RESET` et faite en pont entre les deux en branchant votre clavier.

Quand vous aurez réussi, vous verrez apparaitre un message de ce type dans la QMK Toolbox : 

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
```

### Flasher votre clavier

Cliquez sur le bouton `Flash` de la QMK Toolbox. Vous verrez une sortie écran similaire à la suivante :

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
*** Attempting to flash, please don't remove device
>>> dfu-programmer atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer atmega32u4 flash /Users/skully/qmk_firmware/clueboard_66_hotswap_gen1_skully.hex
    Checking memory from 0x0 to 0x55FF...  Empty.
    0%                            100%  Programming 0x5600 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x5600 bytes written into 0x7000 bytes memory (76.79%).
>>> dfu-programmer atmega32u4 reset

*** DFU device disconnected
*** Clueboard - Clueboard 66% HotSwap connected -- 0xC1ED:0x2390
```

## Flasher votre clavier en ligne de commande

La première chose que vous avez à savoir est le type de bootloader que votre clavier utilise. Il y a quattre bootloaders principaux qui sont utilisés courament. Les Pro-Micro et ses clones utiliseront CATERINA. Les Teensy's utiliseront Halfkay. Les claviers OLKB utiliseront QMK-DFU et les autres processeurs atmega32u4 utiliseront DFU.

Vous pouvez trouver plus d'informations à propos des bootloader dans la section [Instructions pour flasher et informatons sur les bootloader](flashing.md) page.

Si vous savez quel bootloader vous utilisez, alors vous pouvez aussi automatiser le processus de flash grâce à une option particulière de la commande `make`.

### DFU

Si vous êtes prêt à utiliser le bootloader DFU et à flasher votre firmware, alors ouvrez votre terminal de ligne de commande et lancez ces commandes : 

    make <my_keyboard>:<my_keymap>:dfu

Par exemple, si votre disposition (keymap) est nommée "xyverz" et que vous fabriquez une disposition pour un planck de version `rev5` alors utilisez cette commande :

    make planck/rev5:xyverz:dfu

Une fois que la compilation est terminée, vous devrez voir un texte similaire s’afficher : 

```
Linking: .build/planck_rev5_xyverz.elf                                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                                               [OK]
Checking file size of planck_rev5_xyverz.hex
 * File size is fine - 18574/28672
```

Une fois que vous avez atteint cette étape, alors le script de build vas observer toutes les 5 secondes si le bootloader DFU est disponible. Il vas répeter le scan tant qu’il n’aura pas trouver l’appareil ou que vous ne l’arretiez manuellement.

    dfu-programmer: no device present.
    Error: Bootloader not found. Trying again in 5s.

Une fois arrivé ici, vous avez besoin de réinitialiser le contrôleur. Une sortie écran similaire à celle-ci devrait apparaitre : 

```
*** Attempting to flash, please don't remove device
>>> dfu-programmer atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer atmega32u4 flash /Users/skully/qmk_firmware/clueboard_66_hotswap_gen1_skully.hex
    Checking memory from 0x0 to 0x55FF...  Empty.
    0%                            100%  Programming 0x5600 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x5600 bytes written into 0x7000 bytes memory (76.79%).
>>> dfu-programmer atmega32u4 reset
```

?> Si vous avez le moindre problème, notamment si vous voyez l’erreur `dfu-programmer: no device present` - alors dirigez vous vers la [FAQ conssacrée aux Builds](faq_build.md).

### Commandes DFU

Il y a plusieurs commandes DFU permettant de flasher un firmware sur un appareil DFU : 

* `:dfu` - C'est l'option normale qui attend qu'un appareil DFU soit disponible et qui flashe le firmware dès que c'est le cas. Le check sera fait toutes les 5 secondes.
* `:dfu-ee` - Cette option flash un fichier `.eep` à la place d'un fichier `.hex`. Ce cas est plutôt rare.
* `:dfu-split-left` - Cette option flashe le firmware normal comme avec l'option (`:dfu`). Mais cela aussi flash le coté gauche du fichier EEPROM pour les claviers splittés. _C'est l'option idéale pour un clavier splitté basé sur le Elite C_
* `:dfu-split-right` - Cette option flashe le firmware normal comme avec l'option (`:dfu`).  Mais cela aussi flash le coté droite du fichier EEPROM pour les claviers splittés. _C'est l'option idéale pour un clavier splitté basé sur le Elite C_

### Caterina

Pour les cartes Arduino et ses clones comme le ProMicro de Sparkfun alors vous devrez utiliser Caterina.

Quand vous êtes prêt pour le flash, utilisez la commande suivante pour le build :

    make <my_keyboard>:<my_keymap>:avrdude

Par exemple, si votre clavier est nommé "xyverz" et que vous fabriquez une disposition de clavier `rev2` pour un Let’s Split, alors utilisez cette commande : 

    make lets_split/rev2:xyverz:avrdude

Une fois que le firmware a terminé de compiler, vous devrez voir apparaitre quelque chose comme ça : 

```
Linking: .build/lets_split_rev2_xyverz.elf                                                            [OK]
Creating load file for flashing: .build/lets_split_rev2_xyverz.hex                                    [OK]
Checking file size of lets_split_rev2_xyverz.hex                                                      [OK]
 * File size is fine - 27938/28672
Detecting USB port, reset your controller now..............
```

À ce moment là, il est nécessaire de réinitialiser le clavier, et le script vas détecter le bootloader et flasher le clavier. La sortie écran devrait ressembler à ça : 

```
Detected controller on USB port at /dev/ttyS15

Connecting to programmer: .
Found programmer: Id = "CATERIN"; type = S
    Software Version = 1.0; No Hardware Version given.
Programmer supports auto addr increment.
Programmer supports buffered memory access with buffersize=128 bytes.

Programmer supports the following devices:
    Device code: 0x44

avrdude.exe: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude.exe: Device signature = 0x1e9587 (probably m32u4)
avrdude.exe: NOTE: "flash" memory has been specified, an erase cycle will be performed
             To disable this feature, specify the -D option.
avrdude.exe: erasing chip
avrdude.exe: reading input file "./.build/lets_split_rev2_xyverz.hex"
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex auto detected as Intel Hex
avrdude.exe: writing flash (27938 bytes):

Writing | ################################################## | 100% 2.40s

avrdude.exe: 27938 bytes of flash written
avrdude.exe: verifying flash memory against ./.build/lets_split_rev2_xyverz.hex:
avrdude.exe: load data flash data from input file ./.build/lets_split_rev2_xyverz.hex:
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex auto detected as Intel Hex
avrdude.exe: input file ./.build/lets_split_rev2_xyverz.hex contains 27938 bytes
avrdude.exe: reading on-chip flash data:

Reading | ################################################## | 100% 0.43s

avrdude.exe: verifying ...
avrdude.exe: 27938 bytes of flash verified

avrdude.exe: safemode: Fuses OK (E:CB, H:D8, L:FF)

avrdude.exe done.  Thank you.
```

Si vous avez le moindre problème avec cette commande, vous pouvez utiliser cette commande :

    sudo make <my_keyboard>:<my_keymap>:avrdude

Si vous voulez flasher plusieurs claviers, alors vous pouvez utiliser cette commande :

    make <keyboard>:<keymap>:avrdude-loop

Quand vous avez terminé de flasher des claviers, vous pouvez utiliser Ctrl + C ou la touche de votre OS permettant de stopper la boucle.

### HalfKay

Pour les appareils PJRC (Les Teensys), si vous êtes prêts à flasher votre firmware, alors utilisez la commande suivante sur votre terminal :

    make <my_keyboard>:<my_keymap>:teensy

Par exemple, si votre disposition de clavier se nomme est `xyverz` et est conssacrée à un Ergodox EZ, alors utilisez cette commande : 

    make ergodox_ez:xyverz:teensy

Une fois que le firmware a fini de compiler, il devrait afficher quelque chose comme ça : 

```
Linking: .build/ergodox_ez_xyverz.elf                                                               [OK]
Creating load file for flashing: .build/ergodox_ez_xyverz.hex                                       [OK]
Checking file size of ergodox_ez_xyverz.hex                                                         [OK]
 * File size is fine - 25584/32256
 Teensy Loader, Command Line, Version 2.1
Read "./.build/ergodox_ez_xyverz.hex": 25584 bytes, 79.3% usage
Waiting for Teensy device...
 (hint: press the reset button)
 ```

 At this point, reset your board.  Once you've done that, you'll see output like this:

 ```
 Found HalfKay Bootloader
Read "./.build/ergodox_ez_xyverz.hex": 28532 bytes, 88.5% usage
Programming............................................................................................................................................................................
...................................................
Booting
```

### BootloadHID

Pour un client Bootmapper (BMC) ou un clavier basé sur bootloadHID / ATmega32A alors si vous êtes prêt à compiler et flasher votre firmware, utilisez cette commande sur votre terminal : 

    make <my_keyboard>:<my_keymap>:bootloaderHID

Par exemple, si votre clavier est nommé "xyverz" et que vous fabriquez une disposition pour un jj40 alors vous devrez utiliser cette commande : 

    make jj40:xyverz:bootloaderHID

Une fois que le firmware sera compilé, vous devrez voir un affichage similaire : 

```
Linking: .build/jj40_default.elf                                                                   [OK]
Creating load file for flashing: .build/jj40_default.hex                                           [OK]
Copying jj40_default.hex to qmk_firmware folder                                                    [OK]
Checking file size of jj40_default.hex                                                             [OK]
 * The firmware size is fine - 21920/28672 (6752 bytes free)
```

Une fois que vous en êtes à ce point, le script de build vas boucler pour utiliser le bootloader DFU toutes les 5 secondes. Il vas répeter l’opération jusqu’à avoir accès à l’appareil ou alors que vous arrietiez la boucle.

```
Error opening HIDBoot device: The specified device was not found
Trying again in 5s.
```

Une fois qu’il a affiché ça, vous allez devoir réinitialiser le contrôleur. Il devrait afficher quelque chose comme ça :

```
Page size   = 128 (0x80)
Device size = 32768 (0x8000); 30720 bytes remaining
Uploading 22016 (0x5600) bytes starting at 0 (0x0)
0x05580 ... 0x05600
```

### STM32 (ARM)

Pour une majorité de clavier ARM incluant le Proton C, le Planck Rev 6 et le Preonic Rev 3 vous pourrez utiliser le bootloader STM32. Quand vous êtes prêt à compiler et flasher votre firmware, alors ouvrez votre terminal et saisissez :

    make <my_keyboard>:<my_keymap>:dfu-util

Par exemple, si votre keymap est nommé "xyverz" et que vous fabriquez une keymap pour un Planck de révision 6 alors vous devez utiliser cette commande et redémarrer le clavier en mode Bootloader (avant qu'il finisse de compiler) :

    make planck/rev6:xyverz:dfu-util

Une fois que le firmware sera compilé il vas afficher quelque chose de similaire :

```
Linking: .build/planck_rev6_xyverz.elf                                                             [OK]
Creating binary load file for flashing: .build/planck_rev6_xyverz.bin                               [OK]
Creating load file for flashing: .build/planck_rev6_xyverz.hex                                     [OK]

Size after:
   text    data     bss     dec     hex filename
      0   41820       0   41820    a35c .build/planck_rev6_xyverz.hex

Copying planck_rev6_xyverz.bin to qmk_firmware folder                                              [OK]
dfu-util 0.9

Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
Copyright 2010-2016 Tormod Volden and Stefan Schmidt
This program is Free Software and has ABSOLUTELY NO WARRANTY
Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

Invalid DFU suffix signature
A valid DFU suffix will be required in a future dfu-util release!!!
Opening DFU capable USB device...
ID 0483:df11
Run-time device DFU version 011a
Claiming USB DFU Interface...
Setting Alternate Setting #0 ...
Determining device status: state = dfuERROR, status = 10
dfuERROR, clearing status
Determining device status: state = dfuIDLE, status = 0
dfuIDLE, continuing
DFU mode device DFU version 011a
Device returned transfer size 2048
DfuSe interface name: "Internal Flash  "
Downloading to address = 0x08000000, size = 41824
Download        [=========================] 100%        41824 bytes
Download done.
File downloaded successfully
Transitioning to dfuMANIFEST state
```

#### STM32 Commands

Il y a de nombreuses commandes pour flasher un appareil STM32 : 

* `:dfu-util` - La commande par défaut pour flasher un appareil STM32.
* `:dfu-util-wait` - cela fonctionne de la même manière mais vous laisse un temps (configurable) de 10 secondes avant de tenter de flasher le firmware. Vous pouvez utiliser `TIME_DELAY=20` dans la ligne de commande pour changer le délai.
   * Eg: `make <keyboard>:<keymap>:dfu-util TIME_DELAY=5`
* `:dfu-util-split-left` - Permet de flasher un firmware normalement, tout comme l'option précedente mais permet de configuré le coté gauche des paramètres EEPROM sur un clavier splitté.
* `:dfu-util-split-right` - Permet de flasher un firmware normalement, tout comme l'option précedente mais permet de configuré le coté droite des paramètres EEPROM sur un clavier splitté.
* `:st-link-cli` - Cela permet de flasher le firmware avec l'utilitaire en ligne de commande ST-LINK's plutôt que d'utiliser dfu-util.

## Testez votre clavier !

Bravo ! Vous avez fabriqué votre firmware et l'avez programé sur votre clavier !

Essayez le et vérifiez bien que tout fonctionne comme vous le voulez. Vous pouvez suivre la section [Tester et déboguer](newbs_testing_debugging.md) pour en finir avec ce guide pour les noobs et réparer vos problèmes.
