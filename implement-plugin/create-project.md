# Mavenプラグインを実装する

この節ではMavenプラグインをMavenプロジェクトとして実装する方法を紹介します。

## pom.xmlを設定する

はじめに、`pom.xml`に以下を設定しましょう。

* `<packaging>` 要素を `<project>` 要素の直下に追加し、値を *maven-plugin* に設定
* *maven-plugin-api* と *maven-plugin-annotations* に *provided* スコープで依存
* `<artifactId>` 要素を *(任意の名前)-maven-plugin* に設定
* 慣習でありで必須ではありませんが、このように命名することでMavenプラグイン実行時に `-maven-plugin` を省略できます。
例えば *jp.skypencil* グループに属する *sample-maven-plugin* なら、`mvn jp.skypencil:sample` で実行できます。
* 古い資料では *maven-(任意の名前)-plugin* を使うよう推奨していますが、現在は非推奨ですので使用しないでください。
* *maven-plugin-plugin* に `<execution><id>default-descriptor</id></execution><phase>process-classes</phase>` を[追記][^1]します。

`pom.xml`の概要は以下のようになります。

```xml
<project>
  <artifactId>sample-maven-plugin</artifactId>
  <packaging>maven-plugin</packaging>

  <dependencies>
    <dependency>
      <groupId>org.apache.maven</groupId>
      <artifactId>maven-plugin-api</artifactId>
      <version>3.2.5</version><!-- version of Maven -->
      <scope>provided</scope>
    </dependency>
    <dependency>
      <groupId>org.apache.maven.plugin-tools</groupId>
      <artifactId>maven-plugin-annotations</artifactId>
      <version>3.4</version><!-- version of Maven Plugin Tools -->
      <scope>provided</scope>
    </dependency>
    <dependency>
      <groupId>junit</groupId>
      <artifactId>junit</artifactId>
      <version>4.12</version>
      <scope>test</scope>
    </dependency>
  </dependencies>

  <build>
    <plugins>
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-plugin-plugin</artifactId>
        <version>3.4</version>
        <executions>
          <execution>
            <id>default-descriptor</id>
            <phase>process-classes</phase>
          </execution>
        </executions>
      </plugin>
    </plugins>
  </build>
```

なお、[archetypeプラグインを利用するとpom.xmlを自動的に生成してくれます][^2]ので、1から実装を行う場合はぜひ利用してください。
以下のコマンドでプロジェクトの作成を行えます。

```sh
mvn archetype:generate -DarchetypeGroupId=org.apache.maven.archetypes -DarchetypeArtifactId=maven-archetype-plugin -DarchetypeVersion=1.2
```

[^1]: http://maven.apache.org/plugin-tools/maven-plugin-plugin/examples/using-annotations.html
[^2]: TODO かなり古いので、新しいアーキタイプを作成すること
