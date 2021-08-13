# Flasher votre clavier

Maintenant que vous avez compilé un firmware custom, vous allez vouloir le flasher dans votre clavier.

## Flasher votre clavier avec QMK Toolbox

La manière la plus simple de flasher votre clavier est avec [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases).

Toutefois, la QMK Toolbox n'est actuellement disponible que pour Windows et macOS. Si vous utilisez Linux (ou préférez flasher le firmware depuis la ligne de commande), vous devrez utiliser [la métode décrite ci-dessous](newbs_flashing.md#flash-your-keyboard-from-the-command-line).

### Charger le fichier dans QMK Toolbox

Démarrez en ouvrant l'application QMK Toolbox. Cherchez le fichier de firmware dans Finder ou Explorer. Vore firmware de clavier peut être dans un de deux formats `.hex` ou `.bin`. QMK essaye de copier le bon format pour votre clavier du répertoire racine `qmk_firmware`.

?> Si vous êtes sous Windows ou macOS il y a des commandes que vous pouvez utiliser pour facilement ouvrir le répertoire firmware dans Explorer ou Finder.

?> Windows:

    start .

?> macOS:

    open .

Le fichier firmware suit toujours ce format de nommage:

    <keyboard_name>_<keymap_name>.{bin,hex}

Par exemple, le `plank/rev5` avec une keymap `default` aura ce nom de fichier:

    planck_rev5_default.hex

Une fois que vous aurez trouvé votre fichier de firmware, glissez le dans la boîte "Local file" sur QMK Toolbox, ou cliquez sur "Open" et naviguez où votre firmware est enregistré.

### Mettez votre clavier en mode DFU (Bootloader)

Afin de flasher votre firmware custom, vous devez mettre votre clavier dans un mode spécial. Lorsqu'il sera dans ce mode, vous ne pourrez pas taper ou utiliser votre clavier. Il est très important que vous ne débranchiez pas votre clavier ou n'arrêtiez pas le processus d'écriture du firmware.

Chaque clavier a une manière différente d'entrer dans ce mode spécial. Si votre clavier tourne actuellement QMK ou TMK et vous n'avez pas reçu d'instruction spécifiques, essayez, dans cet ordre:

* Enfoncez les deux touches shift et appuyez sur `Pause`
* Enfoncez les deux touches shift et appuyez sur `B`
* Débranchez votre clavier, gardez shift la barre d'espace et `B` en même temps, branchez votre clavier et attendez une seconde avant de relâcher les touches.
* Appuyez la touche physique `RESET` en bas du PCB
* Trouvez les pins sur le PCB marquées `BOOT0` ou `RESET`, court circuitez ces pins en branchant votre PCB

Lorsque vous aurez réussi, vous verrez le message suivant dans QMK Toolbox:

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
```

### Flasher votre clavier

Appuyez sur le boutton `Flash` dans QMK Toolbox. Vous verrez un résultat similaire à ce qui suit:

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

## Flashez votre clavier à l'aide de la ligne de commande

C'est désormais relativement simple. Lorsque vous êtes prêt à compiler et à flasher votre firmware, ouvrez la fenêtre de votre terminal et exécutez la commande de build :

    make <my_keyboard>:<my_keymap>:flash

Par exemple, si votre keymap s'appelle "xyverz" et que vous fabriquez une keymap pour un clavier `planck` de version `rev5` vous devrez utiliser cette commande:

    make planck/rev5:xyverz:flash

La commande va vérifier la configuration du clavier, puis tentera de le flasher en fonction du bootloader (chargeur d’amorçage) spécifié. Cela signifie que vous n'avez pas besoin de savoir quel bootloader votre clavier utilise. Exécutez simplement la commande et laissez-le faire le gros du travail.

Cependant, tout dépend du bootloader qui est installé sur le clavier. Si cette information n’est pas configurée ou si vous tentez de flasher un clavier qui ne permet pas d’être flashé alors vous obtiendrez cette erreur:

    WARNING: This board's bootloader is not specified or is not supported by the ":flash" target at this time.

Dans ce cas, vous devrez choisir le bootloader.

Il y a cinq bootloaders principaux. Les Pro-Micro et les clones utilisent Caterina, les Teensy utilisent Halfkay, les claviers AVR d’OLKB utilisent QMK-DFU, certains controleurs atmega32u4 utilisent DFU et la plupart des controlleurs ARM utilisent ARM DFU.

Vous pouvez trouver plus d'information à propos des bootloaders sur la page [Instructions de flash et information sur le Bootloader](flashing.md).

Si vous savez quel bootloader vous utilisez, lorsque vous compilez le firmware, vous pouvez ajouter quelques options à la commande `make` pour automatiser le processus de flash.

### DFU

Pour le bootloader DFU, lorsque vous êtes prêts à compiler et flasher votre firmware, ouvrez votre fenêtre de terminal et lancez la commande de compilation:

    make <my_keyboard>:<my_keymap>:dfu

Par exemple, si vous keymap s'appelle "xyverz" et vous compilez une keymap pour une plank rev5, vous utiliserez cette commande:

    make planck/rev5:xyverz:dfu

Une fois la compilation terminée, le résultat devrait être le suivant:

```
Linking: .build/planck_rev5_xyverz.elf                                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                                               [OK]
Checking file size of planck_rev5_xyverz.hex
 * File size is fine - 18574/28672
 ```

Une fois arrivé à ce stade, le script de compilation va chercher le bootloader DFU toutes les 5 secondes. Il va répéter les messages suivants jusqu'à ce que l'appareil soit trouvé ou que vous l'annuliez.

    dfu-programmer: no device present.
    Error: Bootloader not found. Trying again in 5s.

Une fois terminé, vous devrez mettre à zéro le contrôleur. Vous allez voir un résultat similaire à ceci:

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

?> Si vous avez des soucis concernant ceci - par exemple `dfu-programmer: no device present` - merci de regarder [Foires Aux Questions de Compilation](faq_build.md).

#### Commandes DFU

Il y  aun certain nombre de commandes du DFU que vous pouvez utiliser pour flasher un firmware sur un device DFU:

* `:dfu` - C'est l'option standard qui attends jusqu'à e qu'un appareil DFU soit disponible, puis flash le firmware. Il va vérifier toutes les 5 secondes, afin de voir si un appareil DFU est apparu.
* `:dfu-ee` - Ceci flash un fichier `eep` à la place du standard hex, peu commun.
* `:dfu-split-left` - Ceci flash le firmware standard, comme la commande standard (`:dfu`). Toutefois, elle flash aussi les fichiers EEPROM du "côté gauche" pour les claviers scindés. _C'est l'option idéale pour les claviers scindés basés sur Elite C._
* `:dfu-split-right` - Ceci flash le firmware standard, comme la commande standard (`:dfu`). Toutefois, elle flash aussi les fichiers EEPROM du "côté droit" pour les claviers scindés. _C'est l'option idéale pour les claviers scindés basés sur Elite C._

### Caterina

Pour les boards Arduino et leurs clones (tel que le SparkFun ProMicro), lorsque vous êtes prêt à compiler et flasher votre firmware, ouvrez votre terminal et lancer la commande de compilation:

    make <my_keyboard>:<my_keymap>:avrdude

Par exemple, si votre keymap se nomme "xyverz" et que vous compilez une keymap pour un Lets Split rev2, vous utiliserez la commande suivante:

    make lets_split/rev2:xyverz:avrdude

Une fois le firmware compilé, vous aurez le résultat suivant:

```
Linking: .build/lets_split_rev2_xyverz.elf                                                            [OK]
Creating load file for flashing: .build/lets_split_rev2_xyverz.hex                                    [OK]
Checking file size of lets_split_rev2_xyverz.hex                                                      [OK]
 * File size is fine - 27938/28672
Detecting USB port, reset your controller now..............
```

Une fois ceci fait, réinitialisez votre board et le script va détecter et flasher le firmware. La sortie devrait ressembler à quelque chose comme ça:

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

Si vous avez un souci, essayez de faire ceci:

    sudo make <my_keyboard>:<my_keymap>:avrdude

#### Commandes Caterina 

Il existe un certain nombre de commandes DFU que vous pouvez utiliser pour mettre à jour le firmware sur un périphérique DFU:

* `: avrdude` - Il s’agit de l’option normale. Elle attend qu’un appareil Caterina soit disponible, puis tente de flasher le firmware. Il attendra de détecter un autre port COM, puis il flashera à nouveau.
* `: avrdude-loop` - Cela fonctionne de la même manière que `: avrdude`, mais une fois que chaque périphérique est flashé, il tentera de flasher à nouveau. Cela peut être utile pour flasher plusieurs claviers à la suite. _Cela implique de sortir manuellement de la boucle en appuyant sur Ctrl + C, Cmd + C ou un raccourci équivalent selon votre OS_
* `: avrdude-split-left` - Cela fonctionne de la même manière que la fonction (`: avrdude`). Toutefois, cela permet aussi de flasher le coté gauche de l'EEPROM des claviers splittés / divisés. C'est donc la méthode recommandée pour les claviers splittés avec Pro Micro.
* `: avrdude-split-right` - Cela fonctionne de la même manière que la fonction (`: avrdude`). Toutefois, cela permet aussi de flasher le coté droite de l'EEPROM des claviers splittés / divisés. C'est donc la méthode recommandée pour les claviers splittés avec Pro Micro.

### HalfKay

Pour les composants PJRC (les Teensy), lorsque vous êtes prêts à compiler et flasher votre firmware, ouvrez votre fenêtre de terminal et lancez la commande de compilation suivante:

    make <my_keyboard>:<my_keymap>:teensy

Par exemple, si vous keymap s'appelle "xyverz" et vous compilez une keymap pour un Ergodox ou un Ergodox EZ, vous utiliserez cette commande:

    make ergodox_ez:xyverz:teensy

Une fois la compilation du firmware terminée, votre sortie devrait ressembler à ça:

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

Une fois terminé, réinitialisez votre board. Une fois fait, vous verrez une sortie comme ça:

 ```
 Found HalfKay Bootloader
Read "./.build/ergodox_ez_xyverz.hex": 28532 bytes, 88.5% usage
Programming............................................................................................................................................................................
...................................................
Booting
```

### STM32 (ARM)

Pour la majorité des boards ARM (incluant les Proton C, Planck Rev 6, et Preonic Rev 3), lorsque vous êtes prêt à compiler et flasher votre firmware, ouvrez la fenêtre de terminal et lancez la commande de compilation:

    make <my_keyboard>:<my_keymap>:dfu-util

Par exemple, si votre keymap s'appelle "xyverz" et vous compilez une keymap pour le clavier Plank Revision 6, vous utiliserez cette commande et redémarrerez le clavier vers le bootloader (avant que la compilation soit terminée):

    make planck/rev6:xyverz:dfu-util

Une fois le firmware compilé, il va afficher quelque chose comme ça:

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

#### Commandes STM32

Il y  aun certain nombre de commandes du DFU que vous pouvez utiliser pour flasher un firmware sur un device STM32:

* `:dfu-util` - C'est l'option standard pour flasher un appareil STM32. Elle attendra qu'un bootloader STM32 soit présent et tentera de l’utiliser.
* `:dfu-util-left` - Ceci flasher le firmware standard, comme la commande standard (`:dfu-util`). Toutefois, elle flasher aussi les fichiers EEPROM du "côté gauche" pour les claviers scindés.
* `:dfu-util-right` - Ceci flash le firmware standard, comme la commande standard (`:dfu-util`). Toutefois, elle flash aussi les fichiers EEPROM du "côté droit" pour les claviers scindés.
* `:st-link-cli` - Cela permet de flasher le firmware avec l'utilitaire en ligne de commande ST-LINK's plutôt que d'utiliser dfu-util.

### BootloadHID

Pour les claviers basés sur Bootmapper Client(BMC)/bootloadHID/ATmega32A, si vous êtes prêts à compiler et flasher le firmware, ouvrez votre fenêtre de terminal et lancez la commande suivante:

    make <my_keyboard>:<my_keymap>:bootloaderHID

Par exemple, si votre keymap s'appelle "xyverz" et que vous compilez une keymap pour un jj40, utilisez cette commande:

    make jj40:xyverz:bootloaderHID

Une fois le firmware compilé, vous aurez cette sortie:

```
Linking: .build/jj40_default.elf                                                                   [OK]
Creating load file for flashing: .build/jj40_default.hex                                           [OK]
Copying jj40_default.hex to qmk_firmware folder                                                    [OK]
Checking file size of jj40_default.hex                                                             [OK]
 * The firmware size is fine - 21920/28672 (6752 bytes free)
```

A ce stade, le script de build va chercher le bootloader DFU toutes les 5 secondes. Il répétera l ’affichage de ce message jusqu'à ce que l’appareil soit trouvé ou que vous annuliez l'opération```

```
Error opening HIDBoot device: The specified device was not found
Trying again in 5s.
```

Une fois ce résultat obtenu, réinitialisez le contrôleur. Le résultat suivant devrait s’afficher:

```
Page size   = 128 (0x80)
Device size = 32768 (0x8000); 30720 bytes remaining
Uploading 22016 (0x5600) bytes starting at 0 (0x0)
0x05580 ... 0x05600
```

## Faites l'essai!

Bravo! Votre firmware customisé a été programmé sur votre clavier!

Essayez-le et vérifiez qu'il fonctionne comme vous le souhaitez. Nous avons écrit [Tester et débugger](newbs_testing_debugging.md) pour compléter le guide du débutant, alors allez voir là-bas pour apprendre comment dépanner vos fonctionnalités custom.
