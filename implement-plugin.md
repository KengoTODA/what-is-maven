# プラグインを実装する

ここではMavenプラグインをMavenプロジェクトとして実装する方法を紹介します。

## pom.xmlを設定する

はじめに、pom.xmlに以下を明示しましょう。

* `<packaging>`要素を`<project>`要素の直下に追加し、値を *maven-plugin* に設定
* *maven-plugin-api* と *maven-plugin-annotations* に *provided* スコープで依存
* `<artifactId>`要素を *(任意の名前)-maven-plugin* に設定
    * 慣習でありで必須ではありませんが、このように命名することでMavenプラグイン実行時に *-maven-plugin* を省略できます。
    * 例えば jp.skypencilグループIDに属するsample-maven-pluginなら、`mvn jp.skypencil:sample`で実行できます。

pom.xmlの概要は以下のようになります。

```xml
<packaging>maven-plugin</packaging>
<build>
    <plugins>
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-plugin-plugin</artifactId>
        <version>3.2</version>
        <configuration>
          <skipErrorNoDescriptorsFound>true</skipErrorNoDescriptorsFound>
        </configuration>
        <executions>
          <execution>
            <id>generate-helpmojo</id>
            <goals>
              <goal>helpmojo</goal>
            </goals>
          </execution>
          <execution>
            <id>mojo-descriptor</id>
            <goals>
              <goal>descriptor</goal>
            </goals>
          </execution>
        </executions>
      </plugin>
    </plugins></build>
<dependencies>
  <dependency>
    <groupId>org.apache.maven</groupId>
    <artifactId>maven-plugin-api</artifactId>
    <version>3.1.0</version>
    <scope>provided</scope>
  </dependency>
  <dependency>
    <groupId>org.apache.maven.plugin-tools</groupId>
    <artifactId>maven-plugin-annotations</artifactId>
    <version>3.2</version>
    <scope>provided</scope>
  </dependency>
  <dependency>
    <groupId>junit</groupId>
    <artifactId>junit</artifactId>
    <version>4.11</version>
    <scope>test</scope>
  </dependency>
</dependencies>```

なお、archetypeプラグインを利用するとpom.xmlを自動的に生成してくれますので、1から実装を行う場合はぜひ利用してください。以下のコマンドでプロジェクトの作成を行えます。

```sh
$ mvn archetype:generate -DarchetypeGroupId=org.apache.maven.archetypes -DarchetypeArtifactId=maven-archetype-plugin -DarchetypeVersion=1.2
```

## プラグインを実装する

Mavenプラグインの実体は、Mojoと呼ばれるクラスです。Mavenプラグインは含まれるゴールの数だけMojoを保有します。
このクラスに必要なメソッドとMojoアノテーションを追加することでプラグインの実装を行います。

    ※旧来はMojoアノテーションはJavadocタグに似た形式を採っていましたが、
    現在はアノテーションによって記述することができます。

MojoはAbstractMojoを継承し、@Mojoアノテーションを持つ必要があります。また@Executeアノテーションや@Parameterアノテーション、@Componentアノテーションなど[org.apache.maven.plugins.annotationsパッケージ](http://maven.apache.org/plugin-tools/apidocs/org/apache/maven/plugins/annotations/package-summary.html)に用意されたアノテーションを使用することもできます。
以下にシンプルなMojoの実装を記載します。

```java
import java.io.File;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugins.annotations.Execute;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;

@Mojo(
        name = "sample",
        threadSafe = true
)
@Execute(
        goal = "sample",
        phase = LifecyclePhase.COMPILE
)
public class SampleMojo extends AbstractMojo {
    @Parameter(
            property = "project.build.directory",
            required = true
    )
    private File outputDirectory;

    @Override
    public void execute() throws MojoExecutionException {
        getLog().info("sample plugin start!");
        getLog().debug("project.build.directory is " + outputDirectory.getAbsolutePath());
    }
}
```

順を追って見ていきましょう。

### 呼び出されるメソッドを実装する

Mavenプラグインが実行されると、Mojoの`execute`メソッドが実行されます。プラグインの実際の処理はここに記載することになります。

### 実行するフェーズを指定する

@Executeアノテーションによって、実行するフェーズを指定することができます。

### 設定を作成する

プラグインは様々なプロジェクトに対応するため、しばしば設定を提供します。設定はpom.xmlに記載することができるため、同じ設定を複数の環境で容易に共有することができます。
一般的な設定としては以下があります。

* `<skip>` ... trueならプラグインの実行を行いません。テストを支援するプラグインでは、`maven.test.skip`プロパティをデフォルト値として使用できます。
* `<outputDirectory>` ... 成果物の出力先ディレクトリです。`project.build.directory`プロパティをデフォルト値として使用するべきです。"target"などとハードコードすると、ユーザが`project.build.directory`プロパティを変更した際に動作しなくなります。
* `<encoding>` ... ファイルの読み書きに利用するエンコードです。`project.build.sourceEncoding`プロパティをデフォルト値として使用できます。

### ログを出力する

Mavenプラグインを実装する場合、ログの出力は標準出力や標準エラー出力ではなく親クラスが提供するロガーを利用します。
これによって、Mavenの`-q`オプション（エラーのみ出力）や`-X`オプション（デバッグログ出力）やログのプレフィクスに準拠でき、ログの可読性が向上します。

```java
getLog().info( "This is info  level, Maven will print this if user does not use -q option.");
getLog().debug("This is debug level, Maven will print this if user uses -X option.");
getLog().error("This is error level, Maven will print this even if user uses -q option.");
```

### ヘルプを実装する

Mojoに記載したJavadocを元に、helpゴールを自動生成することができます。ユーザはこのゴールを実行することでゴールの一覧や使い方を知ることができます。
ヘルプの自動生成はmaven-plugin-pluginのhelpmojoゴールによって行われます。

```xml
<plugin>
  <groupId>org.apache.maven.plugins</groupId>
  <artifactId>maven-plugin-plugin</artifactId>
  <version>3.2</version>
  <configuration>
    <skipErrorNoDescriptorsFound>true</skipErrorNoDescriptorsFound>
  </configuration>
  <executions>
    <execution>
      <!-- helpゴールを自動生成する -->
      <id>generate-helpmojo</id>
      <goals>
        <goal>helpmojo</goal>
      </goals>
    </execution>
    ...
  </executions>
</plugin>
```

なお生成されたクラスに対してjavadocの生成を実行すると、以下のようなエラーが表示されます。maven-plugin-pluginバージョン3.2の時点では回避策は無いようです。

```
[WARNING] Javadoc Warnings
[WARNING] /path/to/sample-maven-plugin/target/generated-sources/plugin/jp/skypencil/HelpMojo.java:30: warning - @author tag has no arguments.
[WARNING] /path/to/sample-maven-plugin/target/generated-sources/plugin/jp/skypencil/HelpMojo.java:30: warning - @version tag has no arguments.
```

### マルチスレッド対応であることを明示する

もし作成したプラグインがスレッドセーフである場合、つまり他のプラグインと同時実行しても問題ない場合はそれを明示することが望ましいと言えます。
Maven3.1.0時点でのマルチスレッドサポートは限定的ですが、これが改善されたときのために用意しておきましょう。

@MojoアノテーションのthreadSafeプロパティによってスレッドセーフか否かを表現できます。

```java
@Mojo(
        name = "sample",
        threadSafe = true
)
```

並列実行可能なプラグインとしては、作成したり変更したりするモノが他のプラグインやMavenそのものと衝突しないものが挙げられます。
例えばレポートを生成するプラグインは、他のプラグインによってレポートの更新が行われないならば並列実行可能です。classファイルを生成したり変更したりするプラグインは同種のプラグインと同時実行するとclassファイルが壊れる可能性があるため、並列実行できません。

* [Parallel builds in Maven 3](https://cwiki.apache.org/confluence/display/MAVEN/Parallel+builds+in+Maven+3)

## プラグインを配布する

プラグインは通常の成果物と同様、deployフェーズやmaven-release-pluginでリモートリポジトリにデプロイできます。
ユーザに使ってもらうバージョンはsnapshotバージョンではなくreleaseバージョンにするよう心がけましょう。

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

* [sample-maven-plugin](./sample-maven-plugin)
