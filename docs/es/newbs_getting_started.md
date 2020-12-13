# Introducción

El teclado de tu computador tiene un procesador dentro de él, no muy distinto del que está dentro de tu ordenador. Este procesador ejecuta software que es responsable de detectar la pulsación de las teclas y enviar informes sobre el estado del teclado cuando las teclas son pulsadas y liberadas. QMK ocupa el rol de ese software. Cuando construyes un keymap personalizado , estas creando el equivalente de un programa ejecutable en tu teclado.

QMK intenta poner un montón de poder en tus manos haciendo que las cosas fáciles sean fáciles, y las cosas difíciles posibles. No tienes que saber cómo programar para crear keymaps potentes — sólo tienes que seguir un conjunto simple de reglas sintácticas.

# Comenzando

Antes de que puedas construir keymaps, necesitarás instalar algun software y configurar tu entorno de construcción. Esto sólo hay que hacerlo una vez sin importar en cuántos teclados planeas configurar el software. 

Si prefieres hacerlo mediante un interfaz gráfico , por favor, considera utilizar el [Configurador QMK](https://config.qmk.fm). En ese caso dirígete a [Construyendo tu primer firmware usando la GUI](newbs_building_firmware_configurator.md). 


## Descarga el software

### Editor de texto

Necesitarás un programa con el que puedas editar y guardar archivos de **texto plano**, en windows puedes utilizar Notepad y en tu Linux puedes utilizar gedit. Estos dos programas son editores simples y funcionales. En macOS ten cuidado con la aplicación de edición de texto por defecto TextEdit: no guardará texto plano a menos de que se le seleccione explícitamente _Make Plain Text_ desde el menú _Format_.

También puedes descargar e instalar un editor de texto dedicado como [Sublime Text](https://www.sublimetext.com/) o [VS Code](https://code.visualstudio.com/). Esta es probablemente la mejor manera independientemente de la plataforma, ya que estos programas fueron creados específicamente para editar código.

?> ¿No estás seguro de qué editor de texto utilizar? Laurence Bradford escribió una [estupenda introducción](https://learntocodewith.me/programming/basics/text-editors/) al tema.

### QMK Toolbox

QMK Toolbox is an optional graphical program for Windows and macOS that allows you to both program and debug your custom keyboard. You will likely find it invaluable for easily flashing your keyboard and viewing debug messages that it prints.

[Download the latest release here.](https://github.com/qmk/qmk_toolbox/releases/latest)

* For Windows: `qmk_toolbox.exe` (portable) or `qmk_toolbox_install.exe` (installer)
* For macOS: `QMK.Toolbox.app.zip` (portable) or `QMK.Toolbox.pkg` (installer)

## Configura tu entorno

Hemos intentado hacer QMK lo más fácil de configurar posible. Sólo tienes que preparar tu entorno Linux o Unix, y luego dejar que QMK
instale el resto.

?> Si no has trabajado con la línea de comandos de Linux/Unix con anterioridad, hay algunos conceptos y comandos básicos que deberías aprender. Estos recursos te enseñarán lo suficiente para poder trabajar con QMK:<br>
[Comandos de Linux que debería saber](https://www.guru99.com/must-know-linux-commands.html)<br>
[Algunos comandos básicos de Unix](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

Necesitarás instalar MSYS2 y Git.

* Sigue las instrucciones de instalación en la [página de MSYS2](http://www.msys2.org).
* Cierra las terminales abiertas de MSYS2 y abre una nueva termial de MSYS2 MinGW 64-bit.
* Instala Git ejecutando este comando: `pacman -S git`.

### macOS

Necesitarás instalar Homebrew. Sigue las instrucciones que encontrarás en la [página de Homebrew](https://brew.sh).

Despueś de que se haya inastalado Homebrew, continúa con _Set Up QMK_. En ese paso ejecutará un script que instalará el resto de paquetes.

### Linux

Necesitarás instalar Git. Es bastante probable que ya lo tengas, pero si no, uno de los siguientes comandos debería instalarlo:

* Debian / Ubuntu / Devuan: `apt-get install git`
* Fedora / Red Hat / CentOS: `yum install git`
* Arch: `pacman -S git`

?> Docker es también una opción en todas las plataformas. [Haz click aquí si quieres detalles.](getting_started_build_tools.md#docker)

## Configura QMK

Una vez que hayas configurado tu entorno Linux/Unix, estarás listo para descargar QMK. Haremos esto utilizando Git para "clonar" el respositorio de QMK. Abre una ventana de Terminal o MSYS2 MinGW y mantenla abierta mientras sigues esta guía. Dentro de esa ventana ejecuta estos dos comandos:

```shell
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

?> Si ya sabes [cómo usar GitHub](getting_started_github.md), te recomendamos en vez de eso, crees y clones tu propio fork. Si no sabes lo que significa, puedes ignorar este mensaje sin problemas.

QMK viene con un script para ayudarte a configurar el resto de cosas que necesitarás. Deberías ejecutarlo introduciendo este comando:

    util/qmk_install.sh

## Prueba tu entorno de construcción

Ahora que tu entorno de construcción de QMK está configurado, puedes construcir un firmware para tu teclado. Comienza intentado construir el keymap por defecto del teclado. Deberías ser capaz de hacerlo con un comando con este formato:

    make <keyboard>:default

Por ejemplo, para construir el firmware para un Clueboard 66% deberías usar:

    make clueboard/66/rev3:default

Cuando esté hecho, deberías tener un montón de información de salida similar a esta:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

# Creando tu keymap

Ya estás listo para crear tu propio keymap personal! Para hacerlo continua con [Construyendo tu primer firmware](newbs_building_firmware.md).
