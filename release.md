# プロジェクトをリポジトリに公開する

プロジェクトをリモートリポジトリに公開するうえで気にしたいことをまとめます。

## バージョンに関する注意

リリースバージョンとスナップショットバージョンの違いに注意してください。

もし多くの人に使ってほしい安定版を公開するなら、リリースバージョンの公開を検討しましょう。後述するmaven-release-pluginを使えば、リリースバージョンが満たすべき条件を自動的に検証してくれます。
反面実装やインタフェースが安定しない開発途上のものを公開するなら、スナップショットバージョンの公開を検討しましょう。バージョン番号に含まれる`-SNAPSHOT`は、使い手とMavenに対して安定リリースではないことを伝えてくれます。


## 公開先のリポジトリを指定する

公開先のリモートリポジトリは`distributionManagement`要素によって指定できます。例として、[Sonatypeのoss-parents](https://github.com/sonatype/oss-parents/blob/master/oss-parent/pom.xml)から設定部分を引用してみましょう。

```xml
<!-- quoted from sonarype/oss-parents -->
<distributionManagement>
  <snapshotRepository>
    <id>sonatype-nexus-snapshots</id>
    <name>Sonatype Nexus Snapshots</name>
    <url>https://oss.sonatype.org/content/repositories/snapshots/</url>
  </snapshotRepository>
  <repository>
    <id>sonatype-nexus-staging</id>
    <name>Nexus Release Repository</name>
    <url>https://oss.sonatype.org/service/local/staging/deploy/maven2/</url>
  </repository>
</distributionManagement>
```

このように、スナップショットバージョンとリリースバージョンで利用するリポジトリは分かれています。チームにのみスナップショットバージョンを公開したり、リリースバージョンとスナップショットバージョンで公開に必要な権限を変えたりといったことができます。

### セントラルリポジトリにライブラリを登録する

セントラルリポジトリには誰でもライブラリを公開することができます。詳細は以下のページを参照してください。

- [【最新版】Maven Central Repository へのライブラリ登録方法 #maven](http://samuraism.jp/diary/2012/05/03/1336047480000.html)

### リポジトリへのアクセス方法の指定

Mavenは基本的にWebDAVでのアクセスを行います。FTPやSSHを使用する場合は対応するプラグインの利用が必要です。

## リポジトリへの公開

リポジトリにプロジェクトを公開する主な方法として、`deploy`ゴールと[maven-release-plugin](http://maven.apache.org/maven-release/maven-release-plugin/)の2つがあります。

### deployフェーズ

deployフェーズは作成したパッケージをリモートのプライベートリポジトリに公開します。
これはdefaultライフサイクルの最後のフェーズですので、compile, test, packageといったdefaulrライフサイクルに含まれるすべての他のフェーズが実行されてから実行されます。

```sh
$ mvn deploy
```

### maven-relase-plugin

releaseプラグインはプライベートリポジトリへの公開だけでなく、バージョン番号をインクリメントする・VCSのタグやブランチを編集する・依存するライブラリにSNAPSHOTバージョンが含まれていたらリリースを中止するなど、リリースバージョンの公開に便利な機能を提供します。リモートリポジトリにリリースバージョンを公開する場合は積極的に使いましょう。

使い方は、prepareゴールとperformゴールを順番に呼び出すだけです。リリースするバージョンなどを対話的に指定するだけで自動的に検証・編集・公開を行います。

```
$ mvn release:prepare release:perform
```

