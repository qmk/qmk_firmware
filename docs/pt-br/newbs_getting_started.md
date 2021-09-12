# Configurando Seu Ambiente QMK

Antes de construir mapas de teclado, você precisa instalar algum software e configurar seu ambiente de construção. Isso só precisa ser feito uma vez, não importa para quantos teclados você planeja compilar o firmware.

## 1. Pré-requisitos

Existem alguns softwares de que você precisa para começar.

* [Editor de texto](newbs_learn_more_resources.md#text-editor-resources)
  * Você precisará de um programa que edite e salve arquivos em texto pleno. O editor padrão que vem com muitos sistemas operacionais não salva arquivos em texto pleno, certifique-se que o editor de texto que você escolher faz isso.
* [QMK Toolbox (opcional)](https://github.com/qmk/qmk_toolbox)
  * Um programa gráfico para Windows e macOS que permite programar e depurar seu teclado personalizado

?> Se você nunca trabalhou com a linha de comando Linux/Unix antes, existem alguns conceitos básicos e comandos que você deve aprender. [Esses recursos](newbs_learn_more_resources.md#command-line-resources) irão ensiná-lo o suficiente para ser capaz de trabalhar com QMK.

## 2. Prepare seu ambiente de construção :id=set-up-your-environment

Tentamos tornar o QMK o mais fácil de configurar possível. Você só precisa preparar seu ambiente Linux ou Unix e deixar o QMK instalar o resto.

<!-- tabs:start -->

### ** Windows **

O QMK mantém um pacote de MSYS2, o CLI e todas as dependências necessárias. Ele também fornece um prático atalho de terminal `QMK MSYS` para inicializá-lo diretamente no ambiente correto.

#### Pré-requisitos

Você precisará instalar o [QMK MSYS](https://msys.qmk.fm/). A versão mais recente está disponível [aqui](https://github.com/qmk/qmk_distro_msys/releases/latest).

Como alternativa, se desejar instalar manualmente o MSYS2, a seção a seguir o guiará pelo processo.

<details>
  <summary>Instalação manual</summary>

?> Ignore os seguintes passos se você usar `QMK MSYS`.

#### Pré-requisitos

Você precisará instalar o MSYS2, Git e Python. Siga as instruções de instalação em https://www.msys2.org.

Depois que o MSYS2 estiver instalado, feche todos os terminais MSYS abertos e abra um novo terminal MinGW de 64 bits.

!> **NOTA:** O terminal MinGW de 64 bits *não* é igual ao terminal MSYS que abre quando a instalação é concluída. Seu prompt deve dizer "MINGW64" em texto roxo, em vez de "MSYS". Consulte [esta página](https://www.msys2.org/wiki/MSYS2-introduction/#subsystems) para obter mais informações sobre as diferenças.

Em seguida, execute o seguinte comando:

    pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip

#### Instalação

Instale o QMK CLI executando:

    python3 -m pip install qmk

</details>

### ** MacOS **

O QMK mantém um Homebrew tap que instalará automaticamente a CLI e todas as dependências necessárias.

#### Pré-requisitos

Você precisará instalar o Homebrew. Siga as instruções em https://brew.sh.

#### Instalação

Instale o QMK CLI executando:

    brew install qmk/qmk/qmk

### ** Linux / WSL **

?> **Nota para usuários WSL**: Por padrão, o processo de instalação irá clonar o repositório QMK em seu diretório inicial WSL, mas se você tiver clonado manualmente, certifique-se de que ele esteja localizado dentro da instância WSL em vez do sistema de arquivos do Windows (ou seja, não em `/mnt`), pois o acesso é atualmente [extremamente lento](https://github.com/microsoft/WSL/issues/4197).

#### Pré-requisitos

Você precisará instalar o Git e o Python. É muito provável que você já tenha ambos, mas se não tiver, um dos seguintes comandos deve instalá-los:

* Debian / Ubuntu / Devuan: `sudo apt install -y git python3-pip`
* Fedora / Red Hat / CentOS: `sudo yum -y install git python3-pip`
* Arch / Manjaro: `sudo pacman --needed --noconfirm -S git python-pip libffi`
* Void: `sudo xbps-install -y git python3-pip`
* Solus: `sudo eopkg -y install git python3`
* Sabayon: `sudo equo install dev-vcs / git dev-python / pip`
* Gentoo: `sudo emerge dev-vcs / git dev-python / pip`

#### Instalação

Instale o QMK CLI executando:

    python3 -m pip install --user qmk

#### Pacotes da comunidade

Esses pacotes são mantidos por membros da comunidade, portanto, podem não estar atualizados ou totalmente funcionais. Se você encontrar problemas, relate-os aos seus respectivos mantenedores.

Em distros baseadas em Arch, você pode instalar a CLI a partir dos repositórios oficiais (NOTA: no momento da escrita, este pacote marca algumas dependências como opcionais que não deveriam ser):

    sudo pacman -S qmk

Você também pode tentar o pacote `qmk-git` do AUR:

    yay -S qmk-git

### ** FreeBSD **

#### Instalação

Instale o pacote FreeBSD para QMK CLI executando:

    pkg install -g "py*-qmk"

NOTA: lembre-se de seguir as instruções impressas no final da instalação (use `pkg info -Dg "py*-qmk"` para mostrá-las novamente).

<!-- tabs:end -->

## 3. Execute a configuração do QMK :id=set-up-qmk

<!-- tabs:start -->

### ** Windows **

Depois de instalar o QMK, você pode configurá-lo com este comando:

    qmk setup

Na maioria das situações, você desejará responder `y` a todos os prompts.

### ** MacOS **

Depois de instalar o QMK, você pode configurá-lo com este comando:

    qmk setup

Na maioria das situações, você desejará responder `y` a todos os prompts.

### ** Linux / WSL **

Depois de instalar o QMK, você pode configurá-lo com este comando:

    qmk setup

Na maioria das situações, você desejará responder `y` a todos os prompts.

?> **Nota sobre Debian, Ubuntu e seus derivados**:
É possível que você obtenha um erro dizendo algo como: `bash: qmk: command not found`.
Isso se deve a um [bug](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=839155) que o Debian introduziu com seu lançamento Bash 4.4, que removeu `$HOME/.local/bin` do PATH. Este bug foi corrigido posteriormente no Debian e Ubuntu.
Infelizmente, o Ubuntu reproduziu esse bug e [ainda não o corrigiu](https://bugs.launchpad.net/ubuntu/+source/bash/+bug/1588562).
Felizmente, a correção é fácil. Execute-o como seu usuário: `echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc`

### ** FreeBSD **

Depois de instalar o QMK, você pode configurá-lo com este comando:

    qmk setup

Na maioria das situações, você desejará responder `y` a todos os prompts.

<!-- tabs:end -->

?> A pasta pessoal qmk pode ser especificada na configuração com `qmk setup -H <path>`, e modificada posteriormente usando a [configuração cli](cli_configuration.md?id=single-key-example) e a variável `user.qmk_home`. Para todas as opções disponíveis, execute `qmk setup --help`.

?> Se você já sabe como usar o GitHub, [recomendamos que você siga estas instruções](getting_started_github.md) e use `qmk setup <github_username>/qmk_firmware` para clonar seu fork pessoal. Se você não sabe o que isso significa, pode ignorar esta mensagem com segurança.

## 4. Teste seu ambiente de construção

Agora que seu ambiente de construção QMK está configurado, você pode construir um firmware para seu teclado. Comece tentando construir o mapa de teclado padrão do teclado. Você deve ser capaz de fazer isso com um comando neste formato:

    qmk compile -kb <keyboard> -km default

Por exemplo, para construir um firmware para um Clueboard 66%, você usaria:

    qmk compile -kb clueboard/66/rev3 -km default

Quando estiver pronto, você deve ter uma grande quantidade de saída que termina semelhante a este:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

## 5. Configure seu ambiente de compilação (opcional)

Você pode configurar seu ambiente de construção para definir os padrões e tornar o trabalho com QMK menos tedioso. Vamos fazer isso agora!

A maioria das pessoas novas no QMK tem apenas 1 teclado. Você pode definir este teclado como seu padrão com o comando `qmk config`. Por exemplo, para definir seu teclado padrão para `clueboard/66/rev4`:

     qmk config user.keyboard=clueboard/66/rev4

Você também pode definir o nome do mapa de teclado padrão. A maioria das pessoas usa seu nome de usuário do GitHub aqui, e recomendamos que você também o faça.

     qmk config user.keymap=<github_username>

Depois disso, você pode deixar esses argumentos de fora e compilar seu teclado assim:

     qmk compile

# Criando o seu Keymap

Agora você está pronto para criar seu próprio mapa de teclado pessoal! Passe para [Construindo seu primeiro firmware](newbs_building_firmware.md) para isso.