# 翻译QMK文档

<!---
  original document: 0.15.12:docs/translating.md
  git diff 0.15.12 HEAD -- docs/translating.md | cat
-->

根目录下（`docs/`）的所有文件应当是英语的 - 其它语言应使用 ISO 639-1 中定义的语言编码建立子目录，后跟随一个 `-` 以及必要的国家编码。[常见的语言编码可见这里](https://www.andiamo.co.uk/resources/iso-language-codes/)。如果此目录不存在，可以新建。每个翻译过的文件的文件名，都应保持与英语版本的一致，以确保超链接的退化兼容性。

文件夹下的 `_summary.md` 文件中，有链接向其它文件的地址，在翻译过的名称后，跟随的链接前应添加该语言的目录名：

```markdown
 * [QMK简介](zh-cn/getting_started_introduction.md)
```

所有导向其它文档页面的链接也必须有语言目录名前缀，若还指向了页面指定位置（即特定的标题），必须使用标题的英文ID，如：

```markdown
[建立你的环境](zh-cn/newbs-getting-started.md#set-up-your-environment)

## 建立你的环境 :id=set-up-your-environment
```

在翻译后，以下文件也需要进行修改：

* [`docs/_langs.md`](https://github.com/qmk/qmk_firmware/blob/master/docs/_langs.md)  
  中的每一行应包含该语言国家国旗的[GitHub emoji编码](https://github.com/ikatyang/emoji-cheat-sheet/blob/master/README.md#country-flag)标志：

  ```markdown
   - [:cn: 中文](/zh-cn/)
  ```

* [`docs/index.html`](https://github.com/qmk/qmk_firmware/blob/master/docs/index.html)  
  `placeholder` 及 `noData` 对象应有一个指向对应语言的入口项：

  ```js
  '/zh-cn/': '没有结果!',
  ```

  用于 "QMK固件" 边栏标题链接的 `nameLink` 同样需要添加对应配置：

  ```js
  '/zh-cn/': '/#/zh-cn/',
  ```

  最后确保在 `fallbackLanguages` 列表中添加该语言项，这样未翻译的文档链接将回退到英文版，而不是出现404页面：

  ```js
  fallbackLanguages: [
    // ...
    'zh-cn',
    // ...
  ],
  ```

## 预览你的翻译成果

请阅读[文档预览](zh-cn/contributing.md#previewing-the-documentation)来设置文档的本地预览 - 在页面右上角的 "Translations" 菜单中应当可以看到你翻译的语言的入口。

当你觉得一切就绪了，请发起pull request给我们吧！
