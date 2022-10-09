# 配置器问题排查

<!---
  original document: 0.15.12:docs/configurator_troubleshooting.md
  git diff 0.15.12 HEAD -- docs/configurator_troubleshooting.md | cat
-->

## 我的 .json 文件不可用

如果该 .json 文件确实是QMK配置器中导出的，恭喜你遇到bug了，请在[QMK配置器](https://github.com/qmk/qmk_configurator/issues)库中提交一个issue。

如果不是……那么页面顶部加大加粗的提示让你不要使用其它 .json 文件，你是怎么错过的？

## 我的配列中有好多空格键，我应该怎么处理？

如果你是说有三个空格键栏，最好的做法是都放上空格键。这个处理方案也适用于退格键和Shift键。

## 用于...的键码是什么？

参见：

* [基础键码资料](zh-cn/keycodes_basic.md)
* [进阶键码资料](zh-cn/feature_advanced_keycodes.md)

## 无法编译

请检查键映射中所有的层，确保没有随机（random）键。

## Bug及其它问题

我们很乐意倾听你的需求及bug报告，请到[QMK配置器](https://github.com/qmk/qmk_configurator/issues)代码库中提交吧。
