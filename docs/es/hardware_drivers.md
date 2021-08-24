# Controladores de hardware QMK

QMK se utiliza en un montón de hardware diferente. Mientras que el soporte para los MCUs y las configuraciones de matriz más comunes está integrado, hay una serie de controladores que se pueden añadir para soportar hardware adicional al teclado. Los ejemplos incluyen ratones y otros dispositivos de apuntamiento, extensores de i/o para teclados divididos, modúlos Bluetooth, y pantallas LCD, OLED y TFT.

<!-- FIXME: Esto debe hablar de cómo se integran los controladores en QMK y cómo puedes añadir su propio controlador.

# Descripción del sistema de controladores

-->

# Controladores disponibles

## ProMicro (Solo AVR)

Soporte para direccionar pines en el ProMicro por su nombre Arduino en lugar de su nombre AVR. Esto necesita ser mejor documentado. Si estás tratando de hacer esto y leer el código no ayuda por favor [abre una issue](https://github.com/qmk/qmk_firmware/issues/new) y podemos ayudarte por el proceso.

## Controlador OLED SSD1306

Soporte para pantallas OLED basadas en SSD1306. Para obtener más información consulta la página de [Característica de Controlador OLED](feature_oled_driver.md).

## uGFX

Puedes hacer uso de uGFX dentro de QMK para manejar LCDs de caracteres y gráficos, matrices de LED, OLED, TFT, y otras tecnologías de visualización. Esto necesita ser mejor documentado. Si estás tratando de hacer esto y leer el código no ayuda por favor [abre una issue](https://github.com/qmk/qmk_firmware/issues/new) y podemos ayudarte por el proceso.

## WS2812 (Solo AVR)

Soporte para LEDs WS2811/WS2812{a,b,c}. Para obtener más información consulta la página de [Luz RGB](feature_rgblight.md).

## IS31FL3731

Soporte para hasta 2 controladores. Cada controlador implementa 2 matrices charlieplex para direccionar LEDs individualmente usando I2C. Esto permite hasta 144 LEDs del mismo color o 32 LEDs RGB. Para obtener más información sobre cómo configurar el controlador, consulta la página de [Matriz RGB](feature_rgb_matrix.md).

## IS31FL3733

Soporte para hasta un solo controlador con espacio para expansión. Cada controlador puede controlar 192 LEDs individuales o 64 LEDs RGB. Para obtener más información sobre cómo configurar el controlador, consulta la página de [Matriz RGB](feature_rgb_matrix.md).
