# Mavenプロジェクトを作成する

この節ではMavenプラグインを実装するためのMavenプロジェクトを作成する方法を紹介します。

## pom.xmlを設定する

はじめに、`pom.xml`に以下を設定しましょう。

* `<packaging>` 要素を `<project>` 要素の直下に追加し、値を *maven-plugin* に設定
* *maven-plugin-api* と *maven-plugin-annotations* に *provided* スコープで依存
* `<artifactId>` 要素を *(任意の名前)-maven-plugin* に設定
    * 慣習でありで必須ではありませんが、このように命名することでMavenプラグイン実行時に `-maven-plugin` を省略できます。
例えば *jp.skypencil* グループに属する *sample-maven-plugin* なら、`mvn jp.skypencil:sample` で実行できます。
    * 古い資料では *maven-(任意の名前)-plugin* を使うよう推奨していますが、現在は非推奨ですので使用しないでください。
* *maven-plugin-plugin* に `<execution><id>default-descriptor</id></execution><phase>process-classes</phase></execution>` を追記[^1]
* *maven-plugin-plugin* に `<execution><id>generate-helpmojo</id><goals><goal>helpmojo</goal></goals></execution>` を追記[^2]

`pom.xml`の概要は以下のようになります。

<pre><code class="lang-xml">&lt;project&gt;
  &lt;artifactId&gt;sample-maven-plugin&lt;/artifactId&gt;
  &lt;packaging&gt;maven-plugin&lt;/packaging&gt;

  &lt;dependencies&gt;
    &lt;dependency&gt;
      &lt;groupId&gt;org.apache.maven&lt;/groupId&gt;
      &lt;artifactId&gt;maven-plugin-api&lt;/artifactId&gt;
      &lt;version&gt;{{book.version.maven}}&lt;/version&gt;&lt;!-- version of Maven --&gt;
      &lt;scope&gt;provided&lt;/scope&gt;
    &lt;/dependency&gt;
    &lt;dependency&gt;
      &lt;groupId&gt;org.apache.maven.plugin-tools&lt;/groupId&gt;
      &lt;artifactId&gt;maven-plugin-annotations&lt;/artifactId&gt;
      &lt;version&gt;3.4&lt;/version&gt;&lt;!-- version of Maven Plugin Tools --&gt;
      &lt;scope&gt;provided&lt;/scope&gt;
    &lt;/dependency&gt;
    &lt;dependency&gt;
      &lt;groupId&gt;junit&lt;/groupId&gt;
      &lt;artifactId&gt;junit&lt;/artifactId&gt;
      &lt;version&gt;{{book.version.junit}}&lt;/version&gt;
      &lt;scope&gt;test&lt;/scope&gt;
    &lt;/dependency&gt;
  &lt;/dependencies&gt;

  &lt;build&gt;
    &lt;plugins&gt;
      &lt;plugin&gt;
        &lt;groupId&gt;org.apache.maven.plugins&lt;/groupId&gt;
        &lt;artifactId&gt;maven-plugin-plugin&lt;/artifactId&gt;
        &lt;version&gt;3.4&lt;/version&gt;
        &lt;executions&gt;
          &lt;execution&gt;
            &lt;id&gt;default-descriptor&lt;/id&gt;
            &lt;phase&gt;process-classes&lt;/phase&gt;
          &lt;/execution&gt;
          &lt;execution&gt;
            &lt;id&gt;generate-helpmojo&lt;/id&gt;
            &lt;goals&gt;
              &lt;goal&gt;helpmojo&lt;/goal&gt;
            &lt;/goals&gt;
          &lt;/execution&gt;
        &lt;/executions&gt;
      &lt;/plugin&gt;
    &lt;/plugins&gt;
  &lt;/build&gt;</code></pre>

なお、archetypeプラグインを利用するとpom.xmlを自動的に生成してくれます[^3]ので、
スクラッチで実装を行う場合はぜひ利用してください。以下のコマンドでMavenプロジェクトの作成を行えます。

```sh
mvn archetype:generate -DarchetypeGroupId=org.apache.maven.archetypes -DarchetypeArtifactId=maven-archetype-plugin -DarchetypeVersion=1.2
```

## Eclipseプロジェクトを作成する

Eclipseで開発を行う場合、以下のコマンドでEclipseプロジェクトの作成を行ってください。
作成後、メニューバーの「ファイル→インポート」から既存のEclipseプロジェクトとして取り込むことができます。

```sh
mvn eclipse:eclipse
```

あるいはEclipseの`m2e`プラグインを使用することで、MavenプロジェクトをEclipseプロジェクトとして
直接開くことも可能です。詳しくは`m2e`の公式サイトをご確認ください。

TODO 上記サイトのURLを調べる。

[^1]: http://maven.apache.org/plugin-tools/maven-plugin-plugin/examples/using-annotations.html
[^2]: ヘルプ表示用Mojoを自動生成するため
[^3]: TODO 1.2は2015年2月時点での最新版だが、長く更新されていないので、新しいアーキタイプを作成すること
