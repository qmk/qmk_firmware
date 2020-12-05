# Teclados con Procesadores AVR

Esta página describe el soporte para procesadores AVR en QMK. Los procesadores AVR incluyen el atmega32u4, atmega32u2, at90usb1286, y otros procesadores de la Corporación Atmel. Los procesadores AVR son MCUs de 8-bit que son diseñados para ser fáciles de trabajar. Los procesadores AVR más comunes en los teclados tienen USB y un montón de GPIO para permitir grandes matrices de teclado. Son los MCUs más populares para el uso en los teclados hoy en día.

Si aún no lo has hecho, debes leer las [Pautas de teclados](hardware_keyboard_guidelines.md) para tener una idea de cómo los teclados encajan en QMK.

## Añadir tu Teclado AVR a QMK

QMK tiene varias características para simplificar el trabajo con teclados AVR. Para la mayoría de los teclados no tienes que escribir ni una sola línea de código. Para empezar, ejecuta el archivo `util/new_keyboard.sh`:

```
$ ./util/new_keyboard.sh
Generating a new QMK keyboard directory

Keyboard Name: mycoolkb
Keyboard Type [avr]: 
Your Name [John Smith]: 

Copying base template files... done
Copying avr template files... done
Renaming keyboard files... done
Replacing %KEYBOARD% with mycoolkb... done
Replacing %YOUR_NAME% with John Smith... done

Created a new keyboard called mycoolkb.

To start working on things, cd into keyboards/mycoolkb,
or open the directory in your favourite text editor.
```

Esto creará todos los archivos necesarios para tu nuevo teclado, y rellenará la configuración con valores predeterminados. Ahora sólo tienes que personalizarlo para tu teclado. 

## `readme.md`

Aquí es donde describirás tu teclado. Por favor sigue la [Plantilla del readme de teclados](documentation_templates.md#keyboard-readmemd-template) al escribir tu `readme.md`. Te animamos a colocar una imagen en la parte superior de tu `readme.md`. Por favor, utiliza un servicio externo como [Imgur](http://imgur.com) para alojar las imágenes.

## `<keyboard>.c`

Aquí es donde pondrás toda la lógica personalizada para tu teclado. Muchos teclados no necesitan nada aquí. Puedes aprender más sobre cómo escribir lógica personalizada en [Funciones Quantum Personalizadas](custom_quantum_functions.md).

## `<keyboard>.h`

Este es el archivo en el que defines tu(s) [Macro(s) de Layout](feature_layouts.md). Por lo menos deberías tener un `#define LAYOUT` para tu teclado que se ve algo así:

```c
#define LAYOUT(          \
      k00, k01, k02,     \
      k10,   k11         \
) {                      \
    { k00, k01,   k02 }, \
    { k10, KC_NO, k11 }, \
}
```

La primera mitad de la macro pre-procesador `LAYOUT` define la disposición física de las llaves. La segunda mitad de la macro define la matriz a la que están conectados los interruptores. Esto te permite tener una disposición física de las llaves que difiere de la matriz de cableado.

Cada una de las variables `k__` tiene que ser única, y normalmente sigue el formato `k<row><col>`.

La matriz física (la segunda mitad) debe tener un número de filas igualando `MATRIX_ROWS`, y cada fila debe tener exactamente `MATRIX_COLS` elementos. Si no tienes tantas teclas físicas puedes usar `KC_NO` para rellenar los espacios en blanco.

## `config.h`

El archivo `config.h` es donde configuras el hardware y el conjunto de características para tu teclado. Hay un montón de opciones que se pueden colocar en ese archivo, demasiadas para listar allí. Para obtener una visión de conjunto completa de las opciones disponibles consulta la página de [Opciones de Configuración](config_options.md).

### Configuración de hardware


En la parte superior de `config.h` encontrarás ajustes relacionados con USB. Estos controlan la apariencia de tu teclado en el Sistema Operativo. Si no tienes una buena razón para cambiar debes dejar el `VENDOR_ID` como `0xFEED`. Para el `PRODUCT_ID` debes seleccionar un número que todavía no esté en uso.

Cambia las líneas de `MANUFACTURER` y `PRODUCT` para reflejar con precisión tu teclado.

```c
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Tú
#define PRODUCT         mi_teclado_fantastico
```

?> Windows y macOS mostrarán el `MANUFACTURER` y `PRODUCT` en la lista de dispositivos USB. `lsusb` en Linux toma estos de la lista mantenida por el [Repositorio de ID USB](http://www.linux-usb.org/usb-ids.html) por defecto. `lsusb -v` mostrará los valores reportados por el dispositivo, y también están presentes en los registros del núcleo después de conectarlo.

### Configuración de la matriz del teclado

La siguiente sección del archivo `config.h` trata de la matriz de tu teclado. Lo primero que debes establecer es el tamaño de la matriz. Esto es generalmente, pero no siempre, el mismo número de filas y columnas como la disposición física de las teclas.

```c
#define MATRIX_ROWS 2
#define MATRIX_COLS 3
```

Una vez que hayas definido el tamaño de tu matriz, necesitas definir qué pines en tu MCU están conectados a filas y columnas. Para hacerlo simplemente especifica los nombres de esos pines:

```c
#define MATRIX_ROW_PINS { D0, D5 }
#define MATRIX_COL_PINS { F1, F0, B0 }
#define UNUSED_PINS
```

El número de entradas debe ser el mismo que el número que asignaste a `MATRIX_ROWS`, y del mismo modo para `MATRIX_COL_PINS` y `MATRIX_COLS`. No tienes que especificar `UNUSED_PINS`, pero puedes si deseas documentar qué pines están abiertos.

Finalmente, puedes especificar la dirección en la que apuntan tus diodos. Esto puede ser `COL2ROW` o `ROW2COL`.

```c
#define DIODE_DIRECTION COL2ROW
```

#### Matriz de patas directas
Para configurar un teclado en el que cada interruptor está conectado a un pin y tierra separados en lugar de compartir los pines de fila y columna, usa `DIRECT_PINS`. La asignación define los pines de cada interruptor en filas y columnas, de izquierda a derecha. Debe ajustarse a los tamaños dentro de `MATRIX_ROWS` y `MATRIX_COLS`. Usa `NO_PIN` para rellenar espacios en blanco. Sobreescribe el comportamiento de `DIODE_DIRECTION`, `MATRIX_ROW_PINS` y `MATRIX_COL_PINS`.

```c
// #define MATRIX_ROW_PINS { D0, D5 }
// #define MATRIX_COL_PINS { F1, F0, B0 }
#define DIRECT_PINS { \
    { F1, E6, B0, B2, B3 }, \
    { F5, F0, B1, B7, D2 }, \
    { F6, F7, C7, D5, D3 }, \
    { B5, C6, B6, NO_PIN, NO_PIN } \
}
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
//#define DIODE_DIRECTION
```

### Configuración de retroiluminación

QMK soporta retroiluminación en la mayoría de los pines GPIO. Algunos de ellos pueden ser manejados por el MCU en hardware. Para más detalles, consulta la [Documentación de Retroiluminación](feature_backlight.md).

```c
#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6
```

### Otras opciones de configuración

Hay un montón de características que se pueden configurar o ajustar en `config.h`. Debes consultar la página de [Opciones de Configuración](config_options.md) para más detalles.

## `rules.mk`

Usa el archivo `rules.mk` para decirle a QMK qué archivos construir y qué características habilitar. Si estás construyendo sobre un atmega32u4 deberías poder dejar mayormente los valores predeterminados. Si estás usando otro MCU es posible que tengas que ajustar algunos parámetros.

### Opciones MCU

Estas opciones le indican al sistema de compilación para qué CPU construir. Ten mucho cuidado si cambias cualquiera de estos ajustes. Puedes inutilizar tu teclado.

```make
MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT
```

### Gestores de arranque

El gestor de arranque es una sección especial de tu MCU que te permite actualizar el código almacenado en el MCU. Piensa en ello como una partición de rescate para tu teclado.

#### Ejemplo de gestor de arranque

```make
BOOTLOADER = halfkay
```

#### Ejemplo de cargador DFU Atmel

```make
BOOTLOADER = atmel-dfu
```

#### Ejemplo de gestor de arranque Pro Micro

```make
BOOTLOADER = caterina
```

### Opciones de construcción

Hay un serie de características que se pueden activar o desactivar en `rules.mk`. Consulta la página de [Opciones de Configuración](config_options.md#feature-options) para obtener una lista detallada y una descripción.
