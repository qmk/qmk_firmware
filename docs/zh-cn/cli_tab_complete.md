# QMK Tab补全

<!---
  original document: 0.15.12:docs/cli_tab_complete.md
  git diff 0.15.12 HEAD -- docs/cli_tab_complete.md | cat
-->

在使用Bash 4.2及更高版本、Zsh或FiSH时，可以启用QMK CLI的Tab补全功能，可以实现对 `qmk` 参数中的开关、键盘、文件等参数的自动补全。

## 设置

有以下几种启用Tab补全的方法。

### 仅当前用户生效

将以下内容添加到文件 `.profile` 或 `.bashrc` 的末尾:

    source ~/qmk_firmware/util/qmk_tab_complete.sh

若你的 `qmk_firmware` 存放在其它路径，以上路径也需要调整。

### 系统级的符号关联

若想让所有本地用户都可以实现Tab补全，可以按如下方法添加符号连接到 `qmk_tab_complete.sh` 脚本：

    `ln -s ~/qmk_firmware/util/qmk_tab_complete.sh /etc/profile.d/qmk_tab_complete.sh`

### 系统级的脚本拷贝

有时符号连接的方案无效，可以改用拷贝文件到指定位置的方案。但须留意该Tab补全脚本可能会不定时更新，你需要定期重新拷贝一次该脚本。

    cp util/qmk_tab_complete.sh /etc/profile.d
