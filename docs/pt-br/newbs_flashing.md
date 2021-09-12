# Atualizando seu teclado

Agora que você construiu um arquivo de firmware personalizado, você vai querer atualizar seu teclado.

## Coloque seu teclado no modo DFU (Bootloader)

Para atualizar seu firmware personalizado, você deve primeiro colocar o teclado em um modo de flash especial. Enquanto estiver neste modo, você não poderá digitar ou usar o teclado de qualquer outra forma. É muito importante que você não desconecte o teclado ou interrompa o processo de flash durante a gravação do firmware.

Teclados diferentes têm maneiras diferentes de entrar neste modo especial. Se o seu PCB atualmente executa QMK, TMK ou PS2AVRGB (Bootmapper Client) e você não recebeu instruções específicas, tente o seguinte, em ordem:

* Mantenha ambas as teclas Shift pressionadas e pressione `Pause`
* Mantenha ambas as teclas Shift pressionadas e pressione `B`
* Desconecte o teclado, mantenha pressionada a barra de espaço e `B` ao mesmo tempo, conecte o teclado e espere um segundo antes de liberar as teclas
* Desconecte o teclado, mantenha pressionada a tecla superior ou inferior esquerda (geralmente Escape ou Controle esquerdo) e conecte o teclado
* Pressione o botão físico `RESET`, geralmente localizado na parte inferior do PCB
* Localize os pinos de cabeçalho no PCB rotulados como `RESET` e` GND`, e coloque-os juntos enquanto conecta seu PCB

Se você tentou tudo acima sem sucesso, e o chip principal na placa diz `STM32` nele, isso pode ser um pouco mais complicado. Geralmente, sua melhor aposta é pedir ajuda em [Discord](https://discord.gg/Uq7gcHh). É provável que algumas fotos da placa sejam solicitadas – se você puder prepará-las com antecedência, isso ajudará a mover as coisas!

Caso contrário, você verá uma mensagem em amarelo, semelhante a esta na Caixa de ferramentas QMK:

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
```

e este dispositivo bootloader também estará presente no Device Manager, System Information.app ou `lsusb`.

## Atualizando seu teclado com QMK Toolbox

A maneira mais simples de atualizar seu teclado será com o [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases).

No entanto, a Toolbox está disponível apenas para Windows e macOS. Se você estiver usando Linux (ou apenas desejar atualizar o firmware da linha de comando), vá para a seção [Atualize seu teclado na linha de comando](#flash-your-keyboard-from-the-command-line).

### Carregar o arquivo na caixa de ferramentas QMK

Comece abrindo o aplicativo QMK Toolbox. Você necessita localizar o arquivo de firmware no Finder ou Explorer. O firmware do seu teclado pode estar em um dos dois formatos - `.hex` ou` .bin`. O QMK tenta copiar o apropriado para o seu teclado no diretório raiz `qmk_firmware`.

Se você estiver no Windows ou macOS, existem comandos que você pode usar para abrir facilmente a pasta atual no Explorer ou Finder.

<!-- tabs:start -->

#### ** Windows **

```
start .
```

#### ** MacOS **

```
open .
```

<!-- tabs:end -->

O arquivo de firmware sempre segue este formato de nomenclatura:

```
<keyboard_name>_<keymap_name>.{bin,hex}
```

Por exemplo, o `planck/rev5` com um mapa de teclado `default` terá este nome de arquivo:

```
planck_rev5_default.hex
```

Depois de localizar seu arquivo de firmware, arraste-o para a caixa "Local file" no QMK Toolbox ou clique em "Open" e navegue até onde o arquivo de firmware está armazenado.

### Flash seu teclado

Clique no botão `Flash` na caixa de ferramentas QMK. Você verá uma saída semelhante a esta:

```
*** DFU device connected: Atmel Corp. ATmega32U4 (03EB:2FF4:0000)
*** Attempting to flash, please don't remove device
>>> dfu-programmer.exe atmega32u4 erase --force
    Erasing flash...  Success
    Checking memory from 0x0 to 0x6FFF...  Empty.
>>> dfu-programmer.exe atmega32u4 flash "D:\Git\qmk_firmware\gh60_satan_default.hex"
    Checking memory from 0x0 to 0x3F7F...  Empty.
    0%                            100%  Programming 0x3F80 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    0%                            100%  Reading 0x7000 bytes...
    [>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
    Validating...  Success
    0x3F80 bytes written into 0x7000 bytes memory (56.70%).
>>> dfu-programmer.exe atmega32u4 reset
    
*** DFU device disconnected: Atmel Corp: ATmega32U4 (03EB:2FF4:0000)
```

## Atualize seu teclado a partir da linha de comando

Isso foi bem simples em comparação com o que costumava ser. Quando você estiver pronto para compilar e atualizar seu firmware, abra a janela do terminal e execute o comando flash:

    flash qmk

Se você não configurou o nome do teclado/mapa de teclado na CLI ou se tem vários teclados, pode especificar o teclado e o mapa de teclado:

    qmk flash -kb <my_keyboard> -km <my_keymap>

Isso verificará a configuração do teclado e, em seguida, tentará atualizá-lo com base no bootloader especificado. Isso significa que você não precisa saber qual gerenciador de inicialização o seu teclado usa. Apenas execute o comando e deixe o comando fazer o trabalho pesado.

No entanto, isso depende do bootloader ser definido pelo teclado. Se esta informação não estiver configurada ou se você estiver usando uma placa que não tem um alvo compatível para fazer flash, você verá este erro:

    WARNING: This board's bootloader is not specified or is not supported by the ":flash" target at this time.

Neste caso, você terá que voltar a especificar o bootloader. Consulte o guia [Flashing Firmware](flashing.md) para obter mais detalhes.

## Teste!

Parabéns! Seu firmware personalizado foi programado para o teclado e você está pronto para testá-lo!

Com um pouco de sorte, tudo funcionará perfeitamente, mas se não houver etapas que o ajudarão a descobrir o que está errado.
Testar seu teclado geralmente é bastante simples. Pressione cada tecla e certifique-se de enviar as teclas que você espera. Você pode usar o modo de teste do [QMK Configurator](https://config.qmk.fm/#/test/) para verificar o teclado, mesmo se ele não executar o QMK.

Ainda sem funcionar? Navegue pelos tópicos do FAQ para obter mais informações ou [converse conosco no Discord](https://discord.gg/Uq7gcHh).