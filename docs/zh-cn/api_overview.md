# QMK API

<!---
  original document: 0.15.12:docs/api_overview.md
  git diff 0.15.12 HEAD -- docs/api_overview.md | cat
-->

QMK API提供了一套可用于Web及GUI工具可用的异步API，用于实现将任何[QMK](https://qmk.fm/)支持的键盘的键映射方案进行编译。已有的键映射模板支持所有的QMK键码并且不需要额外的C代码需求。键盘的维护团队可以提供新的模板来启用更多功能的支持。

## App开发者

若您是一位意愿将这套API引入您的程序中的移动端App开发者，请参阅[API使用指引](zh-cn/api_docs.md)。

## 键盘维护团队

若您希望强化您维护的键盘方案在QMK编译API中的支持，请参阅[键盘支持](zh-cn/reference_configurator_support.md)。

## 后端开发者

若您对这套API系统本身感兴趣，请参阅[开发环境](zh-cn/api_development_environment.md)搭建环境并继续深入探索[架构总览](zh-cn/api_development_overview.md)。
