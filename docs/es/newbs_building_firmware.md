# Construyendo tu primer firmware

Ahora que has configurado tu entorno de construcción estas listo para empezar a construir firmwares personalizados. Para esta sección de la guía alternaremos entre 3 programas - tu gestor de ficheros, tu editor de texto , y tu ventana de terminal. Manten los 3 abiertos hasta que hayas acabado y estés contento con el firmware de tu teclado.

Si has cerrado y reabierto la ventana de tu terminal después de seguir el primero paso de esta guía, no olvides hacer `cd qmk_firmware` para que tu terminal esté en el directorio correcto.

## Navega a tu carpeta de keymaps 

Comienza navegando a la carpeta `keymaps` correspondiente a tu teclado.

?> Si estás en macOS o Windows hay comandos que puedes utilizar fácilmente para abrir la carpeta keymaps.

?> macOS:

    abre keyboards/<keyboard_folder>/keymaps

?> Windows:

    inicia .\\keyboards\\<keyboard_folder>\\keymaps

## Crea una copia del keymap `default`

Una vez que tengas la carpeta `keymaps` abierta querrás crear una copia de la carpeta `default`. Recomendamos encarecidamente que nombres la carpeta igual que tu nombre de usuario de GitHub, pero puedes utilizar el nombre que quieras siempre que contenga sólo letras en minúscula, números y el caracter de guión bajo.

Para automatizar el proceso, también tienes la opción de ejecutar el script `new_keymap.sh`. 

Navega a la carpeta `qmk_firmware/util` e introduce lo siguiente:

```
./new_keymap.sh <keyboard path> <username>
```

Por ejemplo, para un usuario llamado John, intentando hacer un keymap nuevo para el 1up60hse, tendría que teclear

```
./new_keymap.sh 1upkeyboards/1up60hse john
```

## Abre `keymap.c` con tu editor de texto favorito

Abre tu `keymap.c`. Dentro de este fichero encontrarás la estructura que controla cómo se comporta tu teclado. En lo alto de `keymap.c` puede haber distintos defines y enums que hacen el keymap más fácil de leer. Continuando por abajo encontrarás una línea con este aspecto:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

Esta línea indica el comienzo del listado de Capas. Debajo encontrarás líneas que contienen o bien `LAYOUT` o `KEYMAP`, y estas líneas indican el comienzo de una capa. Debajo de esa línea está la lista de teclas que pertenecen a esa capa concreta.

!> Cuando estés editando tu fichero de keymap ten cuidado con no añadir ni eliminar ninguna coma. Si lo haces el firmware dejará de compilar y puede no ser fácil averiguar dónde está la coma faltante o sobrante.

## Personaliza el Layout a tu gusto

Cómo completar esta paso depende enteramente de ti. Haz ese pequeño cambio que querías o rehaz completamente todo. Puedes eliminar capas si no las necesitas todas, o añadir nuevas hasta un total de 32. Comprueba la siguiente documentación para descubrir qué es lo que puedes definir aquí:

* [Keycodes](keycodes.md)
* [Características](features.md)
* [Preguntas frecuentes](faq.md)

?> Mientras estás descubriendo cómo funcionan los keymaps, haz pequeños cambios. Cambios mayores pueden hacer difícil la depuración de problemas que puedan aparecer.

## Construye tu firmware

Cuando los cambios a tu keymap están completos necesitarás construir el firmware. Para hacerlo vuelve a la ventana de tu terminal y ejecuta el siguiente comando:

    make <my_keyboard>:<my_keymap>

Por ejemplo, si tu keymap se llama "xyverz" y estás construyendo un keymap para un planck rev5, utilizarás el siguiente comando:

    make planck/rev5:xyverz

Mientras compila, recibirás un montón de información de salida en la pantalla informándote de qué ficheros están siendo compilados. Debería acabar con una información similar a esta:

```
Linking: .build/planck_rev5_xyverz.elf                                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                                               [OK]
Checking file size of planck_rev5_xyverz.hex                                                        [OK]
 * File size is fine - 18392/28672
```

## Flashea tu firmware

Continua con [Flasheando el firmware](newbs_flashing.md) para aprender cómo escribir tu firmware nuevo en tu teclado.
