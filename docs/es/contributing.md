# Cómo contribuir

👍🎉 Antes que nada, gracias por darte el tiempo de leer esto y contribuir! 🎉👍

Las contribuciones externas nos ayudan a crecer y mejorar QMK. Queremos hacer del proceso de crear pull request y contribuir algo útil y fácil para contribuyentes y quienes mantienen el proyecto. Para este fin hemos creado los siguientes lineamientos para contribuyentes para ayudar a que tu pull request sea aceptada sin necesidad de cambios mayores.

* [Resumen del Proyecto](#project-overview)
* [Coding Conventions](#coding-conventions)
* [Lineamientos Generales](#general-guidelines)
* [¿Qué significa el Código de Conducta para mí?](#what-does-the-code-of-conduct-mean-for-me)

## No Quiero Leer Todo Esto! Solamente Tengo una Pregunta!

SI deseas hacer preguntas acerca de QMK puedes hacerlo en el [Subreddit OLKB](https://reddit.com/r/olkb) o en [Discord](https://discord.gg/Uq7gcHh).

Por favor ten esto en mente:

* Pueden pasar varias horas para que alguien responda a tu pregunta. Por favor se paciente!
* Todos los involucrados con QMK están donando su tiempo y energía. No nos pagan por trabajar o contestar preguntas acerca de QMK.
* Trata de hacer tu pregunta de forma que sea lo más fácil de responder como sea posible. Si no estas seguro de como hacer eso estas son buenas guías:
  * https://opensource.com/life/16/10/how-ask-technical-questions
  * http://www.catb.org/esr/faqs/smart-questions.html

# Resumen del Proyecto

QMK está escrito ampliamente en C, con características especificas y otras partes escritas en C++. Esto está dirigido a procesadores embebidos en teclados, particularmente AVR ([LUFA](http://www.fourwalledcubicle.com/LUFA.php)) y ARM ([ChibiOS](http://www.chibios.com)). Si ya estás muy familiarizado con programación en Arduino encontraras muchos conceptos y limitaciones familiares. Sin embargo la experiencia previa con Arduino no es algo requerido para contribuir satisfactoriamente con QMK.

<!-- FIXME: We should include a list of resources for learning C here. -->

# ¿Dónde Puedo Buscar Ayuda?

Si necesitas ayuda puedes [abrir un issue](https://github.com/qmk/qmk_firmware/issues) o [preguntar en Discord](https://discord.gg/Uq7gcHh).

# Cómo Hago una Contribución?

¿Nunca has hecho una contribución a código abierto antes? ¿Te preguntas como funcionan las contribuciones en QMK? ¡Aquí tienes una guía rápida!

0. Crea una cuenta en [GitHub](https://github.com).
1. Arma un keymap para contribuir, [encuentra un issue](https://github.com/qmk/qmk_firmware/issues) que estés interesado en solucionar, o [a característica](https://github.com/qmk/qmk_firmware/issues?q=is%3Aopen+is%3Aissue+label%3Afeature) que desees agregar.
2. Haz un Fork del repositorio asociado con el issue a tu cuenta de Github. Esto significa que tendrás una copia del repositorio en `your-GitHub-username/qmk_firmware`.
3. Clona el repositorio a tu equipo local utilizando `git clone https://github.com/github-username/repository-name.git`.
4. Si estás trabajando en una característica nueva considera abrir un issue para hablar con nosotros acerca del trabajo del que te encargarás.
5. Crea una nueva branch para tu solución utilizando `git checkout -b branch-name-here`.
6. Haz los cambios necesarios para el issue que estás tratando de resolver o la característica que quieres agregar.
7. Utiliza `git add insert-paths-of-changed-files-here` para agregar el contenido de los archivos modificados al "snapshot" que git utiliza para manejar el estado del proyecto, también conocido como el índice o index.
8. Utiliza `git commit -m "Insert a short message of the changes made here"` para guardar el contenido del índice con un mensaje descriptivo.
9. Empuja los cambios a tu repositorio en Github utilizando `git push origin branch-name-here`.
10. Crea un pull request a [QMK Firmware](https://github.com/qmk/qmk_firmware/pull/new/master).
11. Crea el título de tu pull request con una breve descripción de los cambios realizados y el issue o número de bug asociado con tu cambio en inglés. Por ejemplo, puedes nombrar un pull request como "Added more log outputting to resolve #4352".
12. En la descripción del pull request explica los cambios que realizaste, cualquier error que crees pueda existir en el pull request que hiciste, y cualquier pregunta que tengas para quien mantiene el proyecto. Está bien si tu pull rquest no es perfecta (ninguna lo es), quien lo revise estará en disposición de ayudarte a solucionar cualquier problema y mejorarlo!
13. Espera a que el pull request sea revisado por alguien de mantenimiento.
14. Haz cambios a tu pull request si el mantenedor que hizo la revisión te recomienda alguno.
15. ¡Celebra tu éxito después de que tu pull request haya sido mergeada!

# Coding Conventions

La mayor parte de nuestro estilo es muy fácil de implementar. Si estas familiarizado con C o Python no deberías tener mayores problemas con nuestros estilos locales.

* [Coding Conventions - C](es/coding_conventions_c.md)
* [Coding Conventions - Python](es/coding_conventions_python.md)

# Lineamientos Generales

Tenemos unos cuantos tipos diferentes de cambios en QMK, cada uno requiere de un nivel o rigor diferentes. Queremos que tengas los siguientes lineamientos en mente sin importar el tipo de cambio que estés realizando.

* Separa PRs en unidades lógicas. Por ejemplo, no crees un PR que cubra dos características independientes, en lugar de eso crea un PR diferente por cada característica.
* Verifica si hay espacios en blanco innecesarios con `git diff --check` antes de hacer commit.
* Asegurate de que el código modificado compile.
  * Keymaps: Asegurate de que `make keyboard:your_new_keymap` no regrese ningún error.
  * Keyboards: Asegurate de que `make keyboard:all` no regrese ningún error.
  * Core: Asegurate de que `make all` no regrese ningún error.
* Asegurate de que los mensajes de tus commits sean entendibles por si solos. Debes poner una breve descripción (no más de 70 caracteres) en la primer línea, la segunda línea debe estar vacía, y de la tercer línea en delante debes describir tu commit detalladamente, si es necesario. Todo esto en inglés. Ejemplo:

```
Adjust the fronzlebop for the kerpleplork

The kerpleplork was intermittently failing with error code 23. The root cause was the fronzlebop setting, which causes the kerpleplork to activate every N iterations.

Limited experimentation on the devices I have available shows that 7 is high enough to avoid confusing the kerpleplork, but I'd like to get some feedback from people with ARM devices to be sure.
```

!> **IMPORTANTE:** Si deseas contribuir con alguna solución a un error o alguna mejora al código de usaurio, como los keymaps que no son default, userspace y plantillas, asegurate de taggear al creador original del código en tu PR. Muchos usuarios, sin importar el nivel de experiencia con Git y GitHub, pueden sentirse confundidos o frustrados cuando modifican su código sin que se les informe.

## Documentación

Documentación es una de las maneras más fáciles de iniciar contribuyendo con QMK. Encontrar lugares donde la documentación está mal o incumpleta y solucionarlo ¡es fácil! Además necesitamos urgente mente alguien que edite nuestra documentación, así que si tienes habilidades de editor pero no estás seguro de dónde o como iniciar, por favor ¡[búsca ayuda](#where-can-i-go-for-help)!

Puedes encontrar toda nuestra documentación en el directorio `qmk_firmware/docs`, o, si prefieres un flujo de trabajo basado en web, puedes hacer click en "Suggest an Edit" en la parte superior de cada página en http://docs.qmk.fm/.

Cuando agregues ejemplos de código en tu documentación, trata de observar las nomenclaturas observadas en el resto de la documentación. Por ejemplo, estandarizando enums como `my_layers` o `my_keycodes` para ser consistentes:

```c
enum my_layers {
  _FIRST_LAYER,
  _SECOND_LAYER
};

enum my_keycodes {
  FIRST_LAYER = SAFE_RANGE,
  SECOND_LAYER
};
```

## Keymaps

La mayoría de los que contribuyen a QMK por primera vez inician con sus keymaps personales. Tratamos de mantener los estándares de keymaps bastante relajados (los keymaps, después de todo, reflejan la personalidad de sus creadores) pero te pedimos que sigas los siguientes lineamientos para hacer más fácil a otros descubrir y aprender de tu keymap.

* Escribe un `readme.md` usando [la plantilla](es/documentation_templates.md).
* Todas las PR's de keymaps son comprimidas, así que si te importa como se comprimen tus commits deberías hacerlo tú mismo.
* No agregues características con un PR de keymap. Crea primero la característica y después crea un segundo PR para el keymap.
* No incluyas `Makefile`s en tu carpeta keymap (ya no se utilizan)
* Actualiza el copyright en la cabecera de tu archivo (busca `%YOUR_NAME%`)

## Teclados (Keboards)

Los Teclados son la razón principal detrás de QMK. Algunos teclados son mantenidos por la comunidad, mientras que otros son mantenidos por las personas responsables de hacer un teclado en particular. El `readme.md` debería decirte quien mantiene un teclado en particular. Si tienes preguntas relacionadas con un teclado en particular puedes [Abrir un Issue](https://github.com/qmk/qmk_firmware/issues) y taggear al encargado de mantenerlo en tu pregunta.

También te pedimos que sigas estos lineamientos:

* Escribir un `readme.md` utilizando [la plantilla](es/documentation_templates.md).
* Mantener el número de commits razonable o tendremos que comprimir tu PR.
* No agregues características del núcleo con nuevos teclados. Crea primero la característica y después crea un segundo PR para el teclado.
* Nombra los archivos `.c`/`.h` como su fólder padre inmediato, ejemplo: `/keyboards/<kb1>/<kb2>/<kb2>.[ch]`
* No incluyas `Makefile`s en tu carpeta de teclado (ya no se utilizan)
* Actualiza el copyright en la cabecera de tu archivo (busca `%YOUR_NAME%`)

## Núcleo Quantum/TMK

Antes de que pongas mucho trabajo en crear tu nueva característica deberías asegurarte de que la estas implementando de la mejor manera. Puedes obtener un conocimiento básico de QMK leyendo [Entendiendo QMK](es/understanding_qmk.md), el cual te guiará por un tour del flujo de programa de QMK. Desde aquí deberías de hablar con nosotros para obtener una guía de la mejor manera de implementar tu idea. Existen dos principales maneras de hacer esto:

* [Chat en Discord](https://discord.gg/Uq7gcHh)
* [Abrir un Issue](https://github.com/qmk/qmk_firmware/issues/new)

PR de características y resolución de errores afectan a todos los teclados. Además estamos en el proceso de reconstruir QML. Por esta razón es especialmente importante que los cambios significativos sean discutidos antes de que inicie la implementación. Si creas un PR sin hablar con nosotros primero por favor preparate para re-hacer tu trabajo significativamente si tus decisiones no se mezclan bien con la dirección que hemos planeado.

Aquí hay algunas cosas para tener en cuenta cuando trabajes en una característica o resolución de errores.

* **Deshabilitado por defecto** - la memoria es muy limitada en la mayoría de los chips que soporta QMK, y es importante que los keymaps actuales no se rompan, así que por favor permite que tu característica pueda ser encendida (**on**), en lugar de tener que apagarla. Si tú crees que debería estar encendida por defecto, o reduce el tamaño del código, por favor, habla con nosotros sobre ello.
* **Compilar localmente antes de enviarlo** - esperamos que esto sea obvio, pero las cosas deben compilar! Nuestor sistema Travis atrapará cualquier problema, pero generalmente es más rápido que tú compiles algunos teclados localmente en lugar de esperar a que los resultados regresen.
* **Considera revisiones y diferentes chip-bases** - existen muchos teclados que tienen revisiones que permiten configuraciones ligeramente diferentes, e incluso diferentes chip-bases. Trata de hacer una característica soportada por ARM y AVR, o deshabilitala automáticamente en plataformas donde no funcione.
* **Explica tu característica** - Documéntalo en `docs/`, puede ser en un archivo nuevo o en alguno existente. Si no lo documentas otras personas no podrán beneficiarse de tu duro trabajo.

También te pedimos que sigas estos lineamientos:

* Mantén el número de commits razonable o tendremos que comprimir tu PR.
* No agregues teclados o keymaps en características del núcleo. Envía primero tu característica.
* Escribe [Tests Unitarios](es/unit_testing.md) para tu característica.
* Sigue el estilo del archivo que estás editando. Si el estílo no está claro o está mezclado con otros debes de hacerlo conforme a las [coding conventions](#coding-conventions) más arriba.

## Refactorizar

Para mantener una visión clara de como se presentan las cosas en QMK nosotros tratamos de planear las refactorizaciones profundamente y tener a un colaborador para que realice los cambios. Si tienes una idea para refactorizar, o sugerencias, [abre un issue](https://github.com/qmk/qmk_firmware/issues), nos encanta hablar acerca de cómo podemos mejorar QMK.


# ¿Qué significa el Código de Conducta para mí?

Nuestro [Código de Conducta]
(https://github.com/qmk/qmk_firmware/blob/master/CODE_OF_CONDUCT.md) significa que tú eres responsable de tratar a cada individuo en el proyecto con respeto y cortesía sin importar su identidad. Si eres victima de algún comportamiento inapropiado o comentarios como los descritos en nuestro Código de Conducta, estamos aquí para tí y haremos nuestro mejor esfuerzo para asegurarnos de que el abusador sea reprimido apropiadamente, por nuestro código.
