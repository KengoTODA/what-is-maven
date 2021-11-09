# リポジトリへの公開

リポジトリにプロジェクトを公開する主な方法として、`deploy`フェーズと[maven-release-plugin](http://maven.apache.org/maven-release/maven-release-plugin/)の2つがあります。

## deployフェーズ

deployフェーズは作成したパッケージをリモートのプライベートリポジトリに公開します。
これはdefaultライフサイクルの最後のフェーズですので、compile, test, packageといったdefaultライフサイクルに含まれるすべての他のフェーズが実行されてから実行されます。

```sh
$ mvn deploy
```

この方法は主にSNAPSHOTバージョンをリポジトリへと公開するときに利用します。
安定バージョンを公開するときは、次に説明する`maven-release-plugin`を利用してください。


## `maven-relase-plugin`

`maven-release-plugin`はプライベートリポジトリへの公開だけでなく、バージョン番号をインクリメントする・
VCSのタグやブランチを編集する・依存するライブラリにSNAPSHOTバージョンが含まれていたらリリースを
中止するなど、安定バージョンの公開に便利な機能を提供します。
リモートリポジトリに安定バージョンを公開する場合は積極的に使いましょう。

使い方は、prepareゴールとperformゴールを順番に呼び出すだけです。
リリースするバージョンなどを対話的に指定するだけで自動的に検証・編集・公開します。

```
$ mvn release:prepare release:perform
```

## 権限不足で公開に失敗したら

リポジトリへの公開に権限が必要な場合、リポジトリの管理者に問い合せて権限を取得する必要があります。
多くの場合は`~/.m2/settings.xml`を編集し、ユーザ名やパスワードなどの認証情報を設定します。
