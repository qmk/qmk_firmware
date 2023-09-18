# Configuración de teclado CRKBD jNicioN
Hola, dado que no hay mucha documentación de configuración en español, trate de realizar esta sección para explicar ciertas cosas que he aprendido a lo largo de esta configuración.

## Pantalla Oled
La pantalla oled se puede configurar de diferentes maneras, desde poner texto fijo, mostrar leyendas bajo ciertas condiciones, hasta el tener animaciones en ellas.

Para las funciones más básicas es necesario que siempre contemos con un archivo font, en este caso estamos utilizando el archivo [glcdfont.c](glcdfont.c) el cuál tiene un diseño como el de la imagen a continuación.

![glcdfont](https://i.imgur.com/i3CyAW8.png)

Para esta parte se esta basando del proyecto [thunderbird2086/glcdfont.c](../thunderbird2086/glcdfont.c) haciendo ligeras modificaciones para identificar los iconos y la parte de las capas.

## Archivo de reglas
El archivo [rules.mk](rules.mk) contine las reglas bajo las que trabajara el teclado, se activan o desactivan según lo que queramos que se utilice en el teclado, actualmente estan como comentarío que hace cada una de las reglas dentro del archivo. Se debe de considerar que en diversas actualizaciones estos pueden cambiar.

## Archivo de configuración 
Dentro del archivo [config.h](config.h) se encuentra ciertas configuraciones que ayudaran a la compilación del archivo. Parte de estas tienen que ver con las animaciones de colores del teclado y ciertas banderas para configurar acciones.

## Key Map
La sección de [keymap.c](keymap.c) es donde se configura la distribución del teclado, la capa 0 es la inicial y es la que estara por default al usar el teclado, tambien aquí se identifican las capas siguientes que según el gusto se configuraran a las necesidades.
