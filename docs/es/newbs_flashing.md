# Flasheando tu teclado

Ahora que has construido tu fichero de firmware personalizado querrás flashear tu teclado. 

## Flasheando tu teclado con QMK Toolbox

La manera más simple de flashear tu teclado sería con [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases). 

De todos modos, QMK Toolbox actualmente sólo está disponible para Windows y macOS.  Si estás usando Linux (o sólo quisieras flashear el firmware desde la línea de comandos), tendrás que utilizar el [método indicado abajo](newbs_flashing.md#flash-your-keyboard-from-the-command-line).

### Cargar el fichero en QMK Toolbox

Empieza abriendo la aplicación QMK Toolbox. Tendrás que buscar el fichero de firmware usando Finder o Explorer. El firmware de teclado puede estar en uno de estos dos formatos- `.hex` o `.bin`. QMK intenta copiar el apropiado para tu teclado en el fichero raíz `qmk_firmware`.

?> Si tu estás on Windows o macOS hay comandos que puedes usar para abrir fácilmente la carpeta del firmware actual en Explorer o Finder.

?> Windows:

    start .

?> macOS:

    open .

El fichero de firmware sempre sigue el siguiente formato de nombre:

    <nombre_teclado>_<nombre_keymap>.{bin,hex}

Por ejemplo, un `plank/rev5` con un keymap `default` tendrá este nombre de fichero:

    planck_rev5_default.hex

Una vez que hayas localizado el fichero de tu firmware arrástralo a la caja "Fichero local" en QMK Toolbox, o haz click en "Abrir" y navega allí donde tengas almacenado tu fichero de firmware. 

### Pon tu teclado en modo DFU (Bootloader)

Para poder flashear tu firmware personalizado tienes que poner tu teclado en un modo especial que permite flasheado. Cuando está en este modo no podrás teclear o utilizarlo para ninguna otra cosa. Es muy importante que no desconectes tu teclado, de lo contrario interrumpirás el proceso de flasheo mientras el firmware se está escribiendo.

Diferentes teclados tienen diferentes maneras de entrar en este modo especial. Si tu PCB actualmente ejecuta QMK o TMK y no has recibido instrucciones específicas, intenta los siguientes pasos en orden:

* Manten pulsadas ambas teclas shift y pulsa `Pause`
* Manten pulsadas ambas teclas shift y pulsa `B`
* Desconecta tu teclado, mantén pulsada la barra espaciadora y `B` al mismo tiempo, conecta tu teclado y espera un segundo antes de dejar de pulsar las teclas
* Pulsa el botón físico `RESET` situado en el fondo de la PCB
* Localiza los pines en la PCB etiquetados on `BOOT0` o `RESET`, puentea estos dos juntos cuando enchufes la PCB

Si has tenido éxito verás un mensaje similar a este en QMK Toolbox:

```
*** Clueboard - Clueboard 66% HotSwap disconnected -- 0xC1ED:0x2390
*** DFU device connected
```

### Flashea tu teclado

Haz click en el botón `Flash` de QMK Toolbox. Verás una información de salida similar a esta:

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

## Flashea tu teclado desde la línea de comandos

Lo primero que tienes que saber es qué bootloader utiliza tu teclado.  Hay cuatro bootloaders pincipales que se usan habitualmente . Pro-Micro y sus clones usan CATERINA, Teensy's usa Halfkay, las placas OLKB usan QMK-DFU, y otros chips atmega32u4 usan DFU. 

Puedes encontrar más información sobre bootloaders en la página [Instrucciones de flasheado e información de Bootloader](flashing.md). 

Si sabes qué bootloader estás usando, en el momento de compilar el firmware, podrás añadir algún texto extra al comando `make` para automatizar el proceso de flasheado. 

### DFU

Para eo bootloader DFU, cuando estés listo para compilar y flashear tu firmware, abre tu ventana de terminal y ejecuta el siguiente comando de construcción: 

    make <my_keyboard>:<my_keymap>:dfu

Por ejemplo, si tu keymap se llama "xyverz" y estás construyendo un keymap para un planck rev5, utilizarás este comando:

    make planck/rev5:xyverz:dfu

Una vez que finalice de compilar, deberá aparecer lo siguiente:

```
Linking: .build/planck_rev5_xyverz.elf                                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                                               [OK]
Checking file size of planck_rev5_xyverz.hex                                                        
 * File size is fine - 18574/28672
 ```

Después de llegar a este punto, el script de construcción buscará el bootloader DFU cada 5 segundos.  Repetirá lo siguiente hasta que se encuentre el dispositivo o lo canceles:

    dfu-programmer: no device present.
    Error: Bootloader not found. Trying again in 5s.

Una vez haya hecho esto, tendrás que reiniciar el controlador.  Debería mostrar una información de salida similar a esta: 

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

?> Si tienes problemas con esto- del estilo de `dfu-programmer: no device present` - por favor consulta las [Preguntas frecuentes de construcción](faq_build.md).

#### Comandos DFU

Hay un número de comandos DFU que puedes usar para flashear firmware a un dispositivo DFU:

* `:dfu` - Esta es la opción normal y espera hasta que un dispositivo DFU esté disponible, entonces flashea el firmware. Esperará reintentando cada 5 segundos, para ver si un dispositivo DFU ha aparecido.
* `:dfu-ee` - Esta flashea un fichero `eep` en vez del hex normal.  Esto no es lo común. 
* `:dfu-split-left` - Esta flashea el firmware normal, igual que la opción por defecto (`:dfu`). Sin embargo, también flashea el fichero EEPROM "Lado Izquierdo" para teclados divididos. _Esto es ideal para los ficheros divididos basados en Elite C._
* `:dfu-split-right` - Esto flashea el firmware normal, igual que la opción por defecto (`:dfu`). Sin embargo, también flashea el fichero EEPROM "Lado Derecho" para teclados divididos. _Esto es ideal para los ficheros divididos basados en Elite C._


### Caterina 

Para placas Arduino y sus clones (como la SparkFun ProMicro), cuando estés listo para compilar y flashear tu firmware, abre tu ventana de terminal y ejecuta el siguiente comando de construcción: 

    make <my_keyboard>:<my_keymap>:avrdude

Por ejemplo, si tu keymap se llama "xyverz" y estás construyendo un keymap para un Lets Split rev2, usarás este comando:

    make lets_split/rev2:xyverz:avrdude

Una vez que finalice de compilar, deberá aparecer lo siguiente:

```
Linking: .build/lets_split_rev2_xyverz.elf                                                            [OK]
Creating load file for flashing: .build/lets_split_rev2_xyverz.hex                                    [OK]
Checking file size of lets_split_rev2_xyverz.hex                                                      [OK]
 * File size is fine - 27938/28672
Detecting USB port, reset your controller now..............
```

En este punto, reinicia la placa y entonces el script detectará el bootloader y procederá a flashear la placa.  La información de salida deber ser algo similar a esto: 

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
Si tienes problemas con esto, puede ser necesario que hagas esto: 

    sudo make <my_keyboard>:<my_keymap>:avrdude


Adicionalmente, si quisieras flashear múltiples placas, usa el siguiente comando:

    make <keyboard>:<keymap>:avrdude-loop

Cuando hayas acabado de flashear placas, necesitarás pulsar Ctrl + C o cualquier combinación que esté definida en tu sistema operativo para finalizar el bucle.


### HalfKay

Para dispositivos PJRC (Teensy's), cuando estés listo para compilar y flashear tu firmware, abre tu ventana de terminal y ejecuta el siguiente comando de construcción: 

    make <my_keyboard>:<my_keymap>:teensy

Por ejemplo, si tu keymap se llama "xyverz" y estás construyendo un keymap para un Ergodox o un Ergodox EZ, usarás este comando:

    make ergodox_ez:xyverz:teensy

Una vez que el firmware acabe de compilar, deberá mostrar una información de salida como esta: 

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

En este punto, reinicia tu placa.  Una vez que lo hayas hecho, deberás ver una información de salida como esta: 

 ```
 Found HalfKay Bootloader
Read "./.build/ergodox_ez_xyverz.hex": 28532 bytes, 88.5% usage
Programming............................................................................................................................................................................
...................................................
Booting
```

### BootloadHID

Para placas basadas en Bootmapper Client(BMC)/bootloadHID/ATmega32A, cuando estés listo para compilar y flashear tu firmware, abre tu ventana de terminal y ejecuta el comando de construcción: 

    make <my_keyboard>:<my_keymap>:bootloaderHID

Por ejemplo, si tu keymap se llama "xyverz" y estás construyendo un keymap para un jj40, usarás esté comando:

    make jj40:xyverz:bootloaderHID

Una vez que el firmware acaba de compilar, mostrará una información de salida como esta: 

```
Linking: .build/jj40_default.elf                                                                   [OK]
Creating load file for flashing: .build/jj40_default.hex                                           [OK]
Copying jj40_default.hex to qmk_firmware folder                                                    [OK]
Checking file size of jj40_default.hex                                                             [OK]
 * The firmware size is fine - 21920/28672 (6752 bytes free)
```

Después de llegar a este punto, el script de construcción buscará el bootloader DFU cada 5 segundos.  Repetirá lo siguiente hasta que se encuentre el dispositivo o hasta que lo canceles. 

```
Error opening HIDBoot device: The specified device was not found
Trying again in 5s.
```

Una vez que lo haga, querrás reinicar el controlador.  Debería entonces mostrar una información de salida similar a esta: 

```
Page size   = 128 (0x80)
Device size = 32768 (0x8000); 30720 bytes remaining
Uploading 22016 (0x5600) bytes starting at 0 (0x0)
0x05580 ... 0x05600
```

### STM32 (ARM)

Para la mayoría de placas ARM (incluyendo la Proton C, Planck Rev 6, y Preonic Rev 3), cuando estés listo para compilar y flashear tu firmware, abre tu ventana de terminal y ejecuta el siguiente comando de construcción:

    make <my_keyboard>:<my_keymap>:dfu-util

Por ejemplo, si tu keymap se llama "xyverz" y estás construyendo un keymap para un teclado Planck Revision 6, utilizarás este comando y a continuación reiniciarás el teclado con el bootloader (antes de que acabe de compilar):

    make planck/rev6:xyverz:dfu-util

Una vez que el firmware acaba de compilar, mostrará una información de salida similar a esta: 

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

Hay un número de comandos DFU que puedes usar para flashear firmware a un dispositivo DFU:

* `:dfu-util` - El comando por defecto para flashing en dispositivos STM32. 
* `:dfu-util-wait` - Esto funciona como el comando por defecto, pero te da (configurable) 10 segundos de tiempo antes de que intente flashear el firmware.  Puedes usar `TIME_DELAY=20` desde la líena de comandos para cambiar este tiempo de retardo.
   * Eg: `make <keyboard>:<keymap>:dfu-util TIME_DELAY=5`
* `:dfu-util-split-left` - Flashea el firmware normal, igual que la opción por defecto (`:dfu-util`). Sin embargo, también flashea el fichero EEPROM "Lado Izquierdo" para teclados divididos.
* `:dfu-util-split-right` - Flashea el firmware normal, igual que la opción por defecto (`:dfu-util`). Sin embargo, también flashea el fichero EEPROM "Lado Derecho" para teclados divididos.

## ¡Pruébalo!

¡Felicidades! ¡Tu firmware personalizado ha sido programado en tu teclado!

Pruébalo y asegúrate de que todo funciona de la manera que tu quieres. Hemos escrito [Testeando y depurando](newbs_testing_debugging.md) para redondear esta guía de novatos, así que pásate por allí para aprender cómo resolver problemas con tu funcionalidad personalizada.
