# 公開先のMavenリポジトリを指定する

公開先のリモートリポジトリはpom.xmlの`distributionManagement`要素によって指定できます。
例として、[Sonatypeのoss-parents](https://github.com/sonatype/oss-parents/blob/master/oss-parent/pom.xml)から設定部分を引用してみましょう。

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

このように、スナップショットバージョンとリリースバージョンで利用するリポジトリは分かれています。
チームにのみスナップショットバージョンを公開したり、リリースバージョンとスナップショットバージョンで公開に必要な権限を変えたりといったことができます。

## セントラルリポジトリにライブラリを登録する

セントラルリポジトリには誰でもライブラリを公開することができます。詳細は次のページを参照してください。

- [【最新版】Maven Central Repository へのライブラリ登録方法 #maven](http://samuraism.jp/diary/2012/05/03/1336047480000.html)

## リポジトリへのアクセス方法の指定

Mavenは基本的にWebDAVでのアクセスを行います。FTPやSSHを使用する場合は対応するプラグインの利用が必要です。
