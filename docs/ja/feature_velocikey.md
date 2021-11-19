# Velocikey

<!---
  original document: 0.8.147:docs/feature_velocikey.md
  git diff 0.8.147 HEAD -- docs/feature_velocikey.md | cat
-->

Velocikey は入力の速度を使って(レインボー渦巻効果のような)ライト効果の速度を制御できる機能です。速く入力すればするほどライトが速くなります！

## 使用法
Velocikey を使うためには、2つのステップがあります。最初に、キーボードをコンパイルする時に、`rules.mk` に `VELOCIKEY_ENABLE=yes` を設定する必要があります。例えば:

```
MOUSEKEY_ENABLE = no
STENO_ENABLE = no
EXTRAKEY_ENABLE = yes
VELOCIKEY_ENABLE = yes
```

次に、キーボードの使用中に、VLK_TOG キーコードを使って Velocikey を有効にする必要もあります。これは機能をオンおよびオフにします。

以下の全てのライト効果が、Velocikey を有効にすることで制御されます:
- RGB 明滅動作
- RGB レインボームード
- RGB レインボー渦巻
- RGB スネーク
- RGB ナイト

LED 明滅動作の効果のサポートは計画されていますがまだ利用できません。

Velocikey が有効になっている限り、現在オンになっている RGB ライトの他の全ての速度設定に関係なく、速度が制御されます。

## 設定
Velocikey は現在のところキーボード設定を介したどのような設定もサポートしません。速度の増加あるいは減少率などを調整したい場合は、`velocikey.c` を編集し、そこで値を調整して、好みの速度を実現する必要があります。
