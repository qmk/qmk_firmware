# QMK コンパイラ開発ガイド	 

<!---
  original document: 0.9.50:docs/api_development_overview.md
  git diff 0.9.50 HEAD -- docs/api_development_overview.md | cat
-->

このページでは、開発者に QMK コンパイラを紹介しようと思います。コードを読まなければならないような核心となる詳細に立ち入って調べることはしません。ここで得られるものは、コードを読んで理解を深めるためのフレームワークです。

# 概要

QMK Compile API は、いくつかの可動部分からできています:

![構造図](https://raw.githubusercontent.com/qmk/qmk_api/master/docs/architecture.svg)

API クライアントは API サービスと排他的にやりとりをします。ここでジョブをサブミットし、状態を調べ、結果をダウンロードします。API サービスはコンパイルジョブを [Redis Queue](https://python-rq.org) に挿入し、それらのジョブの結果について RQ と S3 の両方を調べます。

ワーカーは RQ から新しいコンパイルジョブを取り出し、ソースとバイナリを S3 互換のストレージエンジンにアップロードします。

# ワーカー

QMK コンパイラワーカーは実際のビルド作業に責任を持ちます。ワーカーは RQ からジョブを取り出し、ジョブを完了するためにいくつかの事を行います:

* 新しい qmk_firmware のチェックアウトを作成する
* 指定されたレイヤーとキーボードメタデータを使って `keymap.c` をビルドする
* ファームウェアをビルドする
* ソースのコピーを zip 形式で圧縮する
* ファームウェア、ソースの zip ファイル、メタデータファイルを S3 にアップロードする
* ジョブの状態を RQ に送信する

# API サービス

API サービスは比較的単純な Flask アプリケーションです。理解しておくべきことが幾つかあります。

## @app.route('/v1/compile', methods=['POST'])

これは API の主なエントリーポイントです。クライアントとのやりとりはここから開始されます。クライアントはキーボードを表す JSON ドキュメントを POST し、API はコンパイルジョブをサブミットする前にいくらかの(とても)基本的な検証を行います。

## @app.route('/v1/compile/&lt;string:job_id&gt;', methods=['GET'])

これは最もよく呼ばれるエンドポイントです。ジョブの詳細が redis から利用可能であればそれを取り出し、そうでなければ S3 からキャッシュされたジョブの詳細を取り出します。

## @app.route('/v1/compile/&lt;string:job_id&gt;/download', methods=['GET'])

このメソッドによりユーザはコンパイルされたファームウェアファイルをダウンロードすることができます。

## @app.route('/v1/compile/&lt;string:job_id&gt;/source', methods=['GET'])

このメソッドによりユーザはファームウェアのソースをダウンロードすることができます。
