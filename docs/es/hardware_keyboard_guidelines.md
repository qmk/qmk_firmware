# Pautas del teclado QMK

Desde sus inicios, QMK ha crecido a pasos agigantados gracias a personas como tú que contribuyes a la creación y mantenimiento de nuestros teclados comunitarios. A medida que hemos crecido hemos descubierto algunos patrones que funcionan bien, y pedimos que te ajustes a ellos para que sea más fácil para que otras personas se beneficien de tu duro trabajo.


## Nombrar tu Teclado/Proyecto

Todos los nombres de teclado están en minúsculas, consistiendo sólo de letras, números y guiones bajos (`_`). Los nombres no pueden comenzar con un guión bajo. La barra de desplazamiento (`/`) se utiliza como un carácter de separación de subcarpetas.

Los nombres `test`, `keyboard`, y `all` están reservados para las órdenes de make y no pueden ser usados como un nombre de teclado o subcarpeta.

Ejemplos Válidos:

* `412_64`
* `chimera_ortho`
* `clueboard/66/rev3`
* `planck`
* `v60_type_r`

## Subcarpetas

QMK utiliza subcarpetas tanto para organización como para compartir código entre las revisiones del mismo teclado. Puedes anidar carpetas hasta 4 niveles de profundidad:

    qmk_firmware/keyboards/top_folder/sub_1/sub_2/sub_3/sub_4

Si una subcarpeta tiene un archivo `rules.mk` será considerado un teclado compilable. Estará disponible en el configurador de QMK y se probará con `make all`. Si estás utilizando una carpeta para organizar varios teclados del mismo fabricante no debes tener un archivo `rules.mk`.

Ejemplo:

Clueboard utiliza subcarpetas para ambos propósitos: organización y revisiones de teclado.

* [`qmk_firmware`](https://github.com/qmk/qmk_firmware/tree/master)
  * [`keyboards`](https://github.com/qmk/qmk_firmware/tree/master/keyboards)
    * [`clueboard`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard)  &larr; This is the organization folder, there's no `rules.mk` file
      * [`60`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/60)  &larr; This is a compilable keyboard, it has a `rules.mk` file
      * [`66`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66) &larr; This is also compilable- it uses `DEFAULT_FOLDER` to specify `rev3` as the default revision
        * [`rev1`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev1) &larr; compilable: `make clueboard/66/rev1`
        * [`rev2`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev2) &larr; compilable: `make clueboard/66/rev2`
        * [`rev3`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev3) &larr; compilable: `make clueboard/66/rev3` or `make clueboard/66`

## Estructura de carpetas de teclado

Su teclado debe estar ubicado en `qmk_firm cuidada/keyboards/` y el nombre de la carpeta debe ser el nombre de su teclado como se describe en la sección anterior. Dentro de esta carpeta debe haber varios archivos:

* `readme.md`
* `info.json`
* `config.h`
* `rules.mk`
* `<keyboard_name>.c`
* `<keyboard_name>.h`

### `readme.md`

Todos los proyectos necesitan tener un archivo `readme.md` que explica lo que es el teclado, quién lo hizo y dónde está disponible. Si es aplicable, también debe contener enlaces a más información, como el sitio web del fabricante. Por favor, sigue la [plantilla publicada](documentation_templates.md#keyboard-readmemd-template).

### `info.json`

Este archivo es utilizado por la [API de QMK](https://github.com/qmk/qmk_api). Contiene la información que [configurador de QMK](https://config.qmk.fm/) necesita mostrar en una representación de su teclado. También puede establecer metadatos aquí. Para más información, consulta la [página de referencia](reference_info_json.md).

### `config.h`

Todos los proyectos necesitan tener un archivo `config.h` que establece cosas como el tamaño de la matriz, nombre del producto, USB VID/PID, descripción y otros ajustes. En general, usa este archivo para establecer la información esencial y los valores predeterminados para tu teclado que siempre funcionarán.

### `rules.mk`

La presencia de este archivo indica que la carpeta es un destino de teclado y se puede utilizar en las órdenes `make`. Aquí es donde estableces el entorno de compilación para tu teclado y configuras el conjunto predeterminado de características.

### `<keyboard_name.c>`

Aquí es donde escribirás código personalizado para tu teclado. Típicamente escribirás código para inicializar e interactuar con el hardware de tu teclado. Si tu teclado se compone de sólo una matriz de teclas sin LEDs, altavoces u otro hardware auxiliar este archivo puede estar en blanco.

Las funciones siguientes se definen típicamente en este archivo:

* `void matrix_init_kb(void)`
* `void matrix_scan_kb(void)`
* `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* `void led_set_kb(uint8_t usb_led)`

### `<keyboard_name.h>`

Este archivo se utiliza para definir la matriz para tu teclado. Debes definir al menos un macro de C que traduce una serie en una matriz que representa la matriz de interruptor físico para tu teclado. Si es posible construir tu teclado con múltiples diseños debes definir macros adicionales.

Si solo tienes un diseño debes llamar a esta macro `LAYOUT`.

Al definir diseños múltiples debes tener un diseño base, llamado `LAYOUT_all`, que soporte todas las posibles posiciones de switch en tu matriz, incluso si ese diseño es imposible de construir físicamente. Esta es la macro que deberías usar en tu keymap `predeterminado`. Debes tener keymaps adicionales llamados `default_ término layout>` que usen tus otras macros de diseño. Esto hará que sea más fácil para las personas utilizar los diseños que defines.

Los nombres de las macros de diseño son completamente minúsculas, excepto por la palabra `LAYOUT` en el frente.

Por ejemplo, si tienes un PCB de 60% que soporta ANSI e ISO podría definir los siguientes diseños y keymaps:

| Nombre de diseño | Nombre de keymap | Descripción |
|-------------|-------------|-------------|
| LAYOUT_all | default | Un diseño que soporta tanto ISO como ANSI |
| LAYOUT_ansi | default_ansi | Un diseño ANSI |
| LAYOUT_iso | default_iso | Un diseño ISO |

## Archivos de Imagen/Hardware

En un esfuerzo por mantener el tamaño de repo abajo ya no estamos aceptando archivos binarios de cualquier formato, con pocas excepciones. Alojarlos en otro lugar (por ejemplo <https://imgur.com>) y enlazarlos en el `readme.md` es preferible.

Para archivos de hardware (tales como placas, casos, pcb) puedes contribuir a [qmk.fm repo](https://github.com/qmk/qmk.fm) y estarán disponibles en [qmk.fm](http://qmk.fm). Archivos descargables se almacenan en `/<teclado>/` (nombre sigue el mismo formato que el anterior), se sirven en `http://qmk.fm/<teclado>/`, y se generan páginas de `/_pages/<teclado>/` que se sirven en la misma ubicación (Los archivos .md se generan en archivos .html mediante Jekyll). Echa un vistazo a la carpeta `lets_split` para ver un ejemplo.

## Predeterminados de teclado

Dada la cantidad de funcionalidad que expone QMK, es muy fácil confundir a los nuevos usuarios. Al armar el firmware predeterminado para tu teclado, te recomendamos limitar tus funciones y opciones habilitadas al conjunto mínimo necesario para soportar tu hardware. A continuación se formulan recomendaciones sobre características específicas.

### Bootmagic y Command

[Bootmagic](feature_bootmagic.md) and [Command](feature_command.md) son dos características relacionadas que permiten a un usuario controlar su teclado de manera no obvia. Te recomendamos que piense largo y tendido acerca de si vas a habilitar cualquiera de las características, y cómo vas a exponer esta funcionalidad. Tengas en cuenta que los usuarios que quieren esta funcionalidad puede habilitarla en sus keymaps personales sin afectar a todos los usuarios novatos que pueden estar usando tu teclado como su primera tarjeta programable.

De lejos el problema más común con el que se encuentran los nuevos usuarios es la activación accidental de Bootmagic mientras están conectando su teclado. Están sosteniendo el teclado por la parte inferior, presionando sin saberlo en alt y barra espaciadora, y luego se dan cuenta de que estas teclas han sido intercambiadas en ellos. Recomendamos dejar esta característica deshabilitada de forma predeterminada, pero si la activas consideres establecer la opción `BOOTMAGIC_KEY_SALT` a una tecla que es difícil de presionar al conectar el teclado.

Si tu teclado no tiene 2 teclas de cambio debes proporcionar un predeterminado de trabajo para `IS_COMMAND`, incluso cuando haya definido `COMMAND_ENABLE = no`. Esto dará a sus usuarios un valor predeterminado para ajustarse a si lo hacen enable Command.

## Programación de teclado personalizado

Como se documenta en [Funcionalidad de Adaptación](custom_quantum_functions.md) puedes definir funciones personalizadas para tu teclado. Por favor, tengas en cuenta que sus usuarios pueden querer personalizar ese comportamiento así, y hacer que sea posible para que puedan hacer eso. Si está proporcionando una función personalizada, por ejemplo `process_record_kb()`, asegúrese de que su función también llame a la versión` `_user()` de la llamada. También debes tener en cuenta el valor de retorno de la versión `_user()`, y ejecutar sólo tu código personalizado si el usuario devuelve `true`.

## Proyectos Sin Producción/Conectados A Mano

Estamos encantados de aceptar cualquier proyecto que utilice QMK, incluidos los prototipos y los cableados de mano, pero tenemos una carpeta `/keyboards/handwired/` separada para ellos, por lo que la carpeta `/keyboards/` principal no se llena. Si un proyecto prototipo se convierte en un proyecto de producción en algún momento en el futuro, ¡estaremos encantados de moverlo a la carpeta `/keyboards/` principal!

## Advertencias como errores

Al desarrollar su teclado, tengas en cuenta que todas las advertencias serán tratadas como errores - estas pequeñas advertencias pueden acumularse y causar errores más grandes en el camino (y pierdan es generalmente una mala práctica).

## Derechos de autor

Si estás adaptando la configuración de tu teclado de otro proyecto, pero no utilizando el mismo código, asegúrese de actualizar la cabecera de derechos de autor en la parte superior de los archivos para mostrar tu nombre, en este formato:

    Copyright 2017 Tu nombre <tu@email.com>

Si estás modificando el código de otra persona y sólo ha hecho cambios triviales debes dejar su nombre en la declaración de derechos de autor. Si has hecho un trabajo significativo en el archivo debe agregar tu nombre a la de ellos, así:

    Copyright 2017 Su nombre <original_author@ejemplo.com> Tu nombre <tu@ejemplo.com>

El año debe ser el primer año en que se crea el archivo. Si el trabajo se hizo a ese archivo en años posteriores puedes reflejar que mediante la adición del segundo año a la primera, como así:

    Copyright 2015-2017 Tu nombre <tu@ejemplo.com>

## Licencia

El núcleo de QMC está licenciado bajo la [GNU General Public License](https://www.gnu.org/licenses/licenses.en.html). Si estás enviando binarios para los procesadores AVR puedes elegir cualquiera [GPLv2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html) o [GPLv3](https://www.gnu.org/licenses/gpl.html). Si estás enviando binarios para ARM procesadores debes elegir [GPL Versión 3](https://www.gnu.org/licenses/gpl.html) para cumplir con los [ChibiOS](http://www.chibios.org) licencia GPLv3.

Si tu teclado hace uso de la [uGFX](https://gfx.io) características dentro de QMK debes cumplir con la [Licencia de uGFX](https://ugfx.io/license.html), que requiere una licencia comercial separada antes de vender un dispositivo que contiene uGFX.

## Detalles técnicos

Si estás buscando más información sobre cómo hacer que su teclado funcione con QMK, [echa un vistazo a la sección hardware](hardware.md)!
