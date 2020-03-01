# Configurador QMK

El [Configurador QMK](https://config.qmk.fm) es un entorno gráfico online que genera ficheros hexadecimales de Firmware QMK.  

?> **Por favor sigue estos pasos en orden.**

Ve el [Video tutorial](https://youtu.be/tx54jkRC9ZY)

El Configurador QMK functiona mejor con Chrome/Firefox. 


!> **Ficheros de otras herramientas como KLE, o kbfirmware no serán compatibles con el Configurador QMK. No las cargues, no las importes. El configurador Configurador QMK es una herramienta DIFERENTE. **

## Seleccionando tu teclado

Haz click en el desplegable y selecciona el teclado para el que quieres crear el keymap. 

?> Si tu teclado tiene varias versiones, asegúrate de que seleccionas la correcta.** 

Lo diré otra vez porque es importante

!> **ASEGÚRATE DE QUE SELECCIONAS LA VERSIÓN CORRECTA!**

Si se ha anunciado que tu teclado funciona con QMK pero no está en la lista, es probable que un desarrollador no se haya encargado de él aún o que todavía no hemos tenido la oportunidad de incluirlo. Abre un issue en [qmk_firmware](https://github.com/qmk/qmk_firmware/issues) solicitando soportar ese teclado un particular, si no hay un [Pull Request](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+is%3Apr+label%3Akeyboard) activo para ello. Hay también teclados que funcionan con QMK que están en las cuentas de github de sus manufacturantes. Acuérdate de comprobar esto también. 

## Eligiendo el layout de tu teclado

Elige el layout que mejor represente el keymap que quieres crear. Algunos teclados no tienen suficientes layouts o layouts correctos definidos aún. Serán soportados en el futuro. 

## Nombre del keymap

Llama a este keymap como quieras. 

?> Si estás teniendo problemas para compilar, puede merecer la pena probar un cambio de nombre, ya que puede que ya exista en el repositorio de QMK Firmware.

## Creando Tu keymap

La adición de keycodes se puede hacer de 3 maneras.  
1. Arrastrando y soltando
2. Clickando en un hueco vacío en el layout y haciendo click en el keycode que deseas
3. Clickando en un hueco vacío en el layout, presionando la tecla física en tu teclado. 

Mueve el puntero de tu ratón sobre una tecla y un pequeño extracto te dirá que es lo que hace la tecla. Para una descripción más detallada por favor, mira

[Referencia básica de keycodes](https://docs.qmk.fm/#/keycodes_basic)    
[Referencia avanzada de keycodes](https://docs.qmk.fm/#/feature_advanced_keycodes)    

En el caso de que no puedas encontrar un layout que suporte tu keymap, por ejemplo, tres huecos para la barra espaciadora, dos huecos para el retroceso o dos huecos para shift etc etc, rellènalos TODOS. 

### Ejemplo:

3 huecos para barra espaciadora: Rellena TODOS con barra espaciadora

2 huecos para retroceso: Rellena AMBOS con retroceso

2 huecos para el shift derecho: Rellena AMBOS con shift derecho

1 hueco para el shift izquierdo y 1 hueco para soporte iso: Rellena ambos con el shift izquierdo

5 huecos , pero sólo 4 teclas: Intuye y comprueba o pregunta a alguien que lo haya hecho anteriormente. 

## Guardando tu keymap para ediciones futuras

Cuando estés satisfecho con un teclado o quieres trabajar en el después, pulsa el botón `Exportar Keymap`. Guardára tu keymap con el nombre que elijas seguido de .json. 

Entonces podrás cargar este fichero .json en el futuro pulsando el botón `Importar Keymap`. 

!> **PRECAUCIÓN:** No es el mismo tipo de fichero .json usado en kbfirmware.com ni ninguna otra herramienta. Si intentas utilizar un fichero .json de alguna de estas herramientas con el Configurador QMK, existe la posibilidad de que tu teclado **explote**. 

## Generando tu fichero de firmware

Pulsa el botón verde `Compilar`.

Cuando la compilación haya acabado, podrás presionar el botón verde `Descargar Firmware`. 

## Flasheando tu teclado

Por favor, dirígete a la sección de [Flashear firmware](newbs_flashing.md)

## Problemas comunes

#### Mi fichero .json no funciona

Si el fichero .json fue generado con el Configurador QMK, enhorabuena, has dado con un bug. Abre una issue en [qmk_configurator](https://github.com/qmk/qmk_configurator/issues)

Si no....cómo no viste el mensaje en negrita que puse arriba diciendo que no hay que utilizar otros ficheros .json? 

#### Hay espacios extra en mi layout ¿Qué hago?

Si te refieres a tener tres espacios para la barra espaciadora, la mejor decisión es rellenar los tres con la barra espaciadora. También se puede hacer lo mismo con las teclas retroceso y las de shift

#### Para qué sirve el keycode.......

Por favor, mira

[Referencia básica de keycodes](https://docs.qmk.fm/#/keycodes_basic)    
[Referencia avanzada de keycodes](https://docs.qmk.fm/#/feature_advanced_keycodes)    

#### No compila

Por favor, revisa las otras capas de tu keymap para asegurarte de que no hay teclas aleatorias presentes. 

## Problemas y bugs

Siempre aceptamos peticiones de clientes y reportes de bug. Por favor, indícalos en [qmk_configurator](https://github.com/qmk/qmk_configurator/issues)
