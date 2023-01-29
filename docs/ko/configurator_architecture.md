# QMK Configurator 아키텍처

이 페이지에서는 높은 수준에서 QMK Configurator 뒤의 웹 아키텍처를 설명합니다. QMK Configurator 코드 자체의 아키텍처에 대해 흥미가 있으시다면 [qmk_configurator](https://github.com/qmk/qmk_configurator) 리포지토리에서 시작해야 합니다.

# 개요

![QMK Configurator Architecture Diagram](configurator_diagram.svg)

# 구체적인 묘사

QMK Configurator는 [싱글 페이지 애플리케이션](https://ko.wikipedia.org/wiki/%EC%8B%B1%EA%B8%80_%ED%8E%98%EC%9D%B4%EC%A7%80_%EC%95%A0%ED%94%8C%EB%A6%AC%EC%BC%80%EC%9D%B4%EC%85%98)으로 QMK 적합 키보드를 위한 사용자 정의 키맵을 생성하도록 합니다. 키맵을 JSON 표현으로 내보낼 수 있으며 [QMK Toolbox](https://github.com/qmk/qmk_toolbox)와 같은 도구를 사용하여 키보드에 플래시할 수 있는, 펌웨어 바이너리를 컴파일합니다. 

Configurator는 키보드 메타데이터 저장소에서 키보드에 대한 메타데이터를 가져오며, 이를 QMK API에 컴파일 요청을 제출합니다. 컴파일 요청의 결과는 S3 호환 데이터 저장소, [Digital Ocean Spaces](https://www.digitalocean.com/products/spaces/)에서 사용이 가능할 것입니다.

## Configurator 프론트엔드

주소: <https://config.qmk.fm>

[Configurator 프론트엔드](https://config.qmk.fm)는 Github 페이지에 의해 제공되는 정적 파일의 집합으로 컴파일된 것입니다. 이 작업은 [qmk_configurator `master`](https://github.com/qmk/qmk_configurator) 브랜치의 푸시된 커밋으로 매 시간 발생합니다. 이러한 잡의 상태를 [qmk_configurator actions tab](https://github.com/qmk/qmk_configurator/actions/workflows/build.yml)에서 볼 수 있습니다.

## 키보드 메타데이터

주소: <https://keyboards.qmk.fm>

키보드 메타데이터는 [qmk_firmware](https://github.com/qmk/qmk_firmware)의 변화로 매 시간 키보드에서 생성됩니다. 결과 JSON 파일은 Spaces에 업로드되며 Configurator에서 각 키보드의 UI를 생성하는 데 사용됩니다. 이 작업의 상태를 [qmk_firmware actions tab](https://github.com/qmk/qmk_firmware/actions/workflows/api.yml)에서 볼 수 있습니다. 여러분이 QMK Collaborator라면 `workflow_dispatch` 이벤트 트리거를 사용하여 이 작업을 수동으로 실행할 수 있습니다. 

## QMK API

주소: <http://api.qmk.fm>

QMK API는 편집을 위해 `keymap.json` 파일을 받습니다. `qmk compile` 그리고 `qmk flash` 와 함께 곧바로 사용할 수 있는 같은 동일한 파일입니다. `keymap.json` 이 제출되면 브라우저는 작업이 완료될 때까지 주기적으로 (매 2초 이상, 가급적이면) 작업 상태를 폴링할 것입니다. 최종 상태의 JSON은 키맵을 위한 소스와 바이너리 다운로드의 포인터를 포함할 것입니다. 

QMK API는 GPL을 준수하기 위해 항상 소스 및 바이너리 다운로드를 나란히 제공합니다.

API에서 오는 3가지의 에러가 아닌 상태 응답이 있습니다.

1. Compile Job Queued
2. Compile Job Running
3. Compile Job Finished

### Compile Job Queued

이 상태는 작업이 [QMK Compiler](#qmk-compiler) 노드에 의해 아직 집어지지 않았다는 것을 지시합니다. Configurator는 이 상태를 "Waiting for an oven"이라고 보여줍니다.

### Compile Job Running

이 상태는 컴파일링이 시작되었다는 것을 지시합니다. Configurator는 이 상태를 "Baking"이라고 보여줍니다.

### Compile Job Finished

이 상태는 작업을 마쳤다는 것을 지시합니다. 소스 및 바이너리 다운로드를 위한 상태 JSON에 키가 있입니다.

## Redis/RQ

QMK API는 RQ를 사용하여 가능한 [QMK Compiler](#qmk-compiler) 노드에 작업을 분배합니다. `keymap.json`이 수신될 때, `qmk_compiler` 노드가 이를 선택하는 RQ queue에 넣습니다.

## QMK Compiler

[QMK Compiler](https://github.com/qmk/qmk_compiler)는 실제로 `keymap.json`의 컴파일을 수행하는 것입니다. 또한 요청된 `qmk_firmware` 브랜치를 확인하여, `qmk compile keymap.json`를 실행하고, 결과 소스와 바이너리를 Digital Ocean Spaces에 업로드 합니다.

사용자가 소스/바이너리를 다운로드 할 때, API는 곧바로 인증된 Spaces의 다운로드 URL로 리디렉션 할 것입니다. 
