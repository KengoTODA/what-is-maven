# Mavenリポジトリを通じて配布する

プラグインは通常の成果物と同様、`deploy`フェーズや`maven-release-plugin`でリモートリポジトリにデプロイできます。
ユーザに使ってもらうバージョンは`SNAPSHOT`バージョンではなく安定バージョンにするよう心がけましょう。

## 配布したプラグインを利用する

pom.xmlに利用するプラグインを記載することで、Mavenが自動的にプラグインをダウンロードして利用するようになります。
プラグインがプライベートリポジトリにある場合、`<pluginRepositories>`要素をpom.xmlの`<build>`直下に追加して利用するリポジトリを明示する必要があります。

```xml
<pluginRepositories>
  <pluginRepository>
    <id>private-repository</id>
    <name>Private Repository</name>
    <url>http://repository.skypencil.jp/</url>
  </pluginRepository>
</pluginRepositories>
```

## 参考になるプラグイン

以下のプラグインは規模も大きくなく簡単に読むことができます。実装の際に参考にしてください。

* [sample-maven-plugin](../sample-maven-plugin)
