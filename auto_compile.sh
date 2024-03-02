#!/bin/sh

# コマンドライン引数から作者の名前を取得
AUTHOR="$1"

# 引数が空でないことを確認
if [ -z "$AUTHOR" ]; then
  echo "Usage: $0 <author_name>"
  exit 1
fi

# 指定された作者のキーボードを検索
for KEYBOARD_DIR in keyboards/$AUTHOR/*; do
  # キーボード名を取得
  KEYBOARD=$(basename $KEYBOARD_DIR)

  # キーマップディレクトリが存在するか確認
  if [ -d "keyboards/$AUTHOR/$KEYBOARD/keymaps" ]; then
    # キーマップを列挙
    for KEYMAP_DIR in keyboards/$AUTHOR/$KEYBOARD/keymaps/*; do
      # キーマップ名を取得
      KEYMAP=$(basename $KEYMAP_DIR)

      # ビルドコマンドの実行
      qmk compile -kb $AUTHOR/$KEYBOARD -km $KEYMAP
    done
  fi
done