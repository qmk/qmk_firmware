# Construindo Seu Primeiro Firmware

Agora que configurou seu ambiente de construção, você está pronto para começar a construir um firmware customizado. Para esta seção do guia, iremos alternar entre 3 programas - seu gerenciador de arquivos, seu editor de texto e sua janela de terminal. Mantenha todos os 3 abertos até terminar e ficar satisfeito com o firmware do teclado.

## Criar um Novo Mapa de Tecla

Para criar seu próprio mapa de teclado, você deve criar uma cópia do mapa de teclado `default`. Se você configurou seu ambiente de construção na última etapa, pode fazer isso facilmente com o QMK CLI:

    qmk new-keymap

Se você não configurou seu ambiente ou se tem vários teclados, pode especificar um nome de teclado:

    qmk new-keymap -kb <keyboard_name>

Observe a saída desse comando, você deve ver algo assim:

    Ψ <github_username> keymap directory created in: /home/me/qmk_firmware/keyboards/clueboard/66/rev3/keymaps/<github_username>

Este é o local do seu novo arquivo `keymap.c`.

## Abra `keymap.c` em seu editor de texto favorito

Abra seu arquivo `keymap.c` em seu editor de texto. Dentro deste arquivo você encontrará a estrutura que controla o comportamento do seu teclado. No topo de `keymap.c` pode haver algumas definições e enums que tornam o mapa de teclado mais fácil de ler. Mais abaixo, você encontrará uma linha semelhante a esta:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

Esta linha indica onde a lista de camadas começa. Abaixo disso, você encontrará linhas contendo `LAYOUT`, e essas linhas indicam o início de uma camada. Abaixo dessa linha está a lista de chaves que compõem uma camada específica.

!> Ao editar seu arquivo de mapa de teclado, tome cuidado para não adicionar ou remover vírgulas. Se você fizer isso, impedirá a compilação do firmware e pode não ser fácil descobrir onde está a vírgula extra ou ausente.

## Personalize o layout de acordo com sua preferência

A forma de concluir esta etapa depende inteiramente de você. Faça a única mudança que está incomodando você ou refaça tudo completamente. Você pode remover camadas se não precisar de todas elas ou adicionar camadas até um total de 32. Há muitos recursos no QMK, explore a barra lateral à esquerda em "Using QMK" para ver a lista completa. Para começar, aqui estão alguns dos recursos mais fáceis de usar:

* [Basic Keycodes](keycodes_basic.md)
* [Quantum Keycodes](quantum_keycodes.md)
* [Grave/Escape](feature_grave_esc.md)
* [Mouse keys](feature_mouse_keys.md)

?> Enquanto você tem uma ideia de como funcionam os mapas de teclado, mantenha cada alteração pequena. Mudanças maiores tornam mais difícil depurar quaisquer problemas que surjam.

## Construa Seu Firmware :id=build-your-firmware

Quando suas alterações no mapa de teclado estiverem concluídas, você precisará construir o firmware. Para fazer isso, volte para a janela do terminal e execute o comando compile:

    qmk compile

Se você não configurou seu ambiente ou se tem vários teclados, pode especificar um teclado e / ou mapa de teclado:

    qmk compile -kb <keyboard> -km <keymap>

Enquanto isso compila, você terá muitas saídas indo para a tela, informando quais arquivos estão sendo compilados. Deve terminar com uma saída semelhante a esta:

```
Linking: .build/planck_rev5_default.elf                                                             [OK]
Creating load file for flashing: .build/planck_rev5_default.hex                                     [OK]
Copying planck_rev5_default.hex to qmk_firmware folder                                              [OK]
Checking file size of planck_rev5_default.hex                                                       [OK]
 * The firmware size is fine - 27312/28672 (95%, 1360 bytes free)
```

## Atualize seu firmware

Passe para [Flashing Firmware](newbs_flashing.md) para aprender como gravar seu novo firmware em seu teclado.