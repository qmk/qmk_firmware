# QMK 문서 번역

루트 폴더 (`docs/`)안에 있는 모든 파일들은 영어이여야 합니다. 그 외 모든 다른 언어는 뒤에 '-'와 해당하는 국가 코드가 따르는, ISO 639-1 언어 코드에 맟춘 하위 폴더이여야 합니다. [일반적인 목록은 여기에서 찾을 수 있습니다.](https://www.andiamo.co.uk/resources/iso-language-codes/) 이러한 폴더가 존재하지 않는다면, 만들면 됩니다. 각 번역된 파일들은 반드시 영어 버전과 이름이 동일해야 하고, 성공적으로 대체되야 합니다.

`_summary.md` 파일은 각 파일에 대한 링크 목록과 번역된 이름, 언어 폴더가 앞에 오는 링크로 이 폴더에 존재해야 합니다.

```markdown
 * [QMK简介](zh-cn/getting_started_introduction.md)
```

다른 문서 페이지의 모든 링크에도 반드시 언어 폴더가 접두어로 붙어야 합니다. 링크가 페이지의 특정 부분에 있는 경우 (이를테면 특정 제목 등), 다음과 같이 반드시 영문 ID를 제목에 사용합니다:

```markdown
[建立你的环境](zh-cn/newbs-getting-started.md#set-up-your-environment)

## 建立你的环境 :id=set-up-your-environment
```

새로운 언어 번역을 마치면, 다음의 따르는 파일을 수정할 필요가 있을 것입니다:

* [`docs/_langs.md`](https://github.com/qmk/qmk_firmware/blob/master/docs/_langs.md)  
  각 줄은 여러분의 언어로 제시되는 국가명과 이를 따르는 [GitHub emoji shortcode](https://github.com/ikatyang/emoji-cheat-sheet/blob/master/README.md#country-flag) 특정 국가의 국기를 포함해야 합니다:

  ```markdown
   - [:cn: 中文](/zh-cn/)
  ```

* [`docs/index.html`](https://github.com/qmk/qmk_firmware/blob/master/docs/index.html)  
  `placeholder` 와 `noData`객체에는 문자열의 언어 폴더에 대한 사전 항목이 있어야 합니다:

  ```js
  '/zh-cn/': '没有结果!',
  ```

  `nameLink` 객체는, 사이드바에서 "QMK 펌웨어" 제목 링크를 설정하는 것으로, 반드시 다음을 추가해야 합니다:

  ```js
  '/zh-cn/': '/#/zh-cn/',
  ```

  그리고 `fallbackLanguages` 항목에 언어 폴더를 추가했는지 확인하세요, 그래야 404ing 대신 영어로 올바르게 대체됩니다. 

  ```js
  fallbackLanguages: [
    // ...
    'zh-cn',
    // ...
  ],
  ```

## 번역 미리보기

[문서 미리보기](ko/contributing.md#previewing-the-documentation)에서 문서의 로컬 인스턴스를 설정하는 방법을 볼 수 있습니다 - 상단 우측의 "Translations" 메뉴에서 새로운 언어를 선택해야 할 수 있습니다.

일단 작업이 만족스럽다면, 언제든지 풀 리퀘스트를 여세요!
