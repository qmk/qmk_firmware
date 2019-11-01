# Introducción

Esta página trata de brindarte la información básica que necesitas conocer para trabajar con el proyecto QMK. Asume que estas familiarizado navegando en el shell de Unix, pero no asume que estas familiarizado con C o compilar utilizando `make`.

## Estructura Básica de QMK

QMK es un fork del proyecto [tmk_keyboard](https://github.com/tmk/tmk_keyboard) de [Jun Wako](https://github.com/tmk). El código original TMK, con modificaciones, se encuentra en el directorio `tmk`. Lo que QMK ha agregado al proyecto se encuentra en el directorio `quantum`. Proyectos de teclados pueden encontrarse en los directorios `handwired` y `keyboard`.


### Estructura Userspace

La carpeta `users` es un directorio para cada usuario. Este es el lugar donde los usuarios pueden agregar código que pueden utilizar en diferentes teclados. Véase la documentación para [Característica Userspace](es/feature_userspace.md) para más información.

### Estructura de proyecto de teclado

Dentro del directorio `keyboards`, su subdirectorio `handwired` y sus subdirectorios de fabricante y vendedor, por ejemplo `clueboard` podras encontrar un directorio para cada projecto de teclado, por ejemplo `qmk_firmware/keyboards/clueboard/2x1800`. Dentro de él, podrás encontrar la siguiente estructura:

* `keymaps/`: Diferentes mapas de caracteres (keymaps) que pueden construirse.
* `rules.mk`: El archivo que define las opciones por defecto de "make". No edites este archivo directamente, en su lugar utiliza un archivo `rules.mk` específico para el keymap.
* `config.h`: El archivo que define las opciones por defecto en tiempo de compilación. No edites este archivo directamente, en su lugar utiliza un archivo `config.h` específico para el keymap.
* `info.json`: El archivo utilizado para definir la plantilla para QMK Configurator. Véase [Sporte Configurator](es/reference_configurator_support.md)  para más información.
* `readme.md`: Una breve descripción del teclado.
* `<keyboardName>.h`: Este archivo es donde la plantilla del teclado se define contra la matriz de interruptores del teclado.
* `<keyboardName>.c`: Este archivo es donde puedes encontrar código personalizado para el teclado.

Para más información sobre la estructura del proyecto, véase [QMK Guías de Teclado](es/hardware_keyboard_guidelines.md).

### Estructura Keymap

En cada directorio de mapa de caracteres (keymap), se pueden encontrar los siguientes archivos. Solamente `keymap.c` es requerido, y si el resto de los archivos no se encuentran las opciones por defecto serán elegidas.

* `config.h`: Las opciones para configurar tu keymap.
* `keymap.c`: Todo el código de tu keymap, requerido.
* `rules.mk`: Las características de QMK que están habilitadas.
* `readme.md`: Una descripción de tu keymap, cómo otros pueden utilizarlo, y explicaciones de sus características. Por favor, subir las imágenes necesarias a servicios como imgur.

# El Archivo `config.h`

Existen 3 posibles ubicaciones del archivo `config.h`:

* keyboard (`/keyboards/<keyboard>/config.h`)
* userspace (`/users/<user>/config.h`)
* keymap (`/keyboards/<keyboard>/keymaps/<keymap>/config.h`)

El build system automáticamente toma los archivos de configuración en el orden anterior. Si deseas sobreescribir cualquiera de las configuraciones de algún `config.h` anterior necesitarás primero incluir código repetitivo para las opciones que desees cambiar.

```
#pragma once
```

Después para sobreescribir una configuración de un archivo `config.h` anterior debes `#udef` y después `#define` la configuración nuevamente.

El código y la configuración lucen así juntos:

```
#pragma once

// overrides go here!
#undef MY_SETTING
#define MY_SETTING 4
```
