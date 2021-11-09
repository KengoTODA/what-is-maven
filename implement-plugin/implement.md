# Mojoを作成する

Mavenプラグインの実体は、Mojo（Maven plain Old Java Object）と呼ばれるクラスです。Mavenプラグインは含まれるゴールの数だけMojoを保有します。
このクラスに必要なメソッドとMojoアノテーションを追加することでプラグインを実装します。

Mojoは`AbstractMojo`を継承し、`@Mojo`アノテーションで修飾される必要があります。
また`@Execute`アノテーションや`@Parameter`アノテーション、`@Component`アノテーションなど[org.apache.maven.plugins.annotationsパッケージ](http://maven.apache.org/plugin-tools/apidocs/org/apache/maven/plugins/annotations/package-summary.html)に用意されたアノテーションを使用できます。

次にシンプルなMojoの実装を記載します。

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
        threadSafe = true,
        defaultPhase = LifecyclePhase.COMPILE
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

## 呼び出されるメソッドを実装する

Mavenプラグインが実行されると、Mojoの`execute`メソッドが実行されます。
プラグインの実際の処理はここに記載します。

## 実行するフェーズを指定する

`@Mojo`アノテーションの`defaultPhase`オプションによって、実行するフェーズを指定できます。
この設定はユーザの設定によって上書くことが可能ですが、デフォルト設定で多くの環境で問題なく動作することが望ましいでしょう。

## 設定を作成する

プラグインはさまざまなプロジェクトに対応するため、しばしば設定を提供します。
設定は`pom.xml`に記載できるため、同じ設定を複数の環境で容易に共有できます。
一般的な設定としては以下があります。

* `<skip>` ... trueならプラグインの実行を行いません。プロジェクト固有のプロパティで指定できることもあります。
* `<outputDirectory>` ... 成果物の出力先ディレクトリです。`project.build.directory`プロパティが示すディレクトリ、あるいはそのサブディレクトリをデフォルト値として使用するべき[^1]です。
* `<encoding>` ... ファイルの読み書きに利用するエンコードです。`project.build.sourceEncoding`プロパティをデフォルト値として使用できます。

## ログを出力する

Mavenプラグインを実装する場合、ログの出力は標準出力や標準エラー出力ではなく、親クラスが提供するロガーを利用します。
これによって、Mavenの`-q`オプション（エラーのみ出力）や`-X`オプション（デバッグログ出力）準拠でき、ログに適切な接頭辞が付くためログの可読性が向上します。

```java
getLog().info( "This is info  level, Maven will print this if user does not use -q option.");
getLog().debug("This is debug level, Maven will print this if user uses -X option.");
getLog().error("This is error level, Maven will print this even if user uses -q option.");
```

処理を高速化するため、デバッグ時にのみ情報を取得・計算できます。

```java
if (getLog().isDebugEnabled()) {
  getLog().debug(computeDetailedLogMessage());
}
```

なお引数に渡す文字列には、改行コードを含めないことをお勧めします。接頭辞のつかない行ができてしまい、
機械的に処理することが難しくなるためです。複数行を出力したい場合は、メソッドを複数回に分けて
呼び出してください。


## マルチスレッド対応の明示

もし作成したプラグインがスレッドセーフである場合は、それを明示することが望ましいといえます。
Maven{{book.version.maven}}時点でのマルチスレッドサポートは限定的ですが、これが改善されたときのために用意しておきましょう。

`@Mojo`アノテーションの`threadSafe`プロパティによってスレッドセーフか否かを表現できます。
[公式のチェックリスト](https://cwiki.apache.org/confluence/display/MAVEN/Parallel+builds+in+Maven+3#ParallelbuildsinMaven3-Mojothreadsafetyassertionchecklist)を確認し、スレッドセーフであるといえる場合は、`true`を指定しましょう。

```java
@Mojo(
        name = "sample",
        threadSafe = true
)
```

2015年4月時点での公式チェックリストの訳を次に記載します。

* staticなフィールドや変数を使っている場合、その値がスレッドセーフであることを確認すること。
    * 特に "java.text.Format" のサブクラス （NumberFormat, DateFormat など） はスレッドセーフでないので、staticなフィールドを介して複数のスレッドから利用されるようなことがないように注意する。
* `components.xml`にシングルトンとして定義されているPlexusコンポーネントを使っている場合、そのコンポーネントはスレッドセーフでなければならない。
* 依存ライブラリに既知の問題が存在しないか確認すること。
* サードパーティ製ライブラリがスレッドセーフであることを確認すること。

つまり、単一JVM内で複数のMojoインスタンスが並列に作成・実行される可能性があるので、それに備える必要があるということです。


## 動作確認

ここまで来たら、作ったプラグインが正常に動作することを確認してみましょう。
ローカルリポジトリにプラグインをインストールしてから、作成したMojoを実行してみてください。

```sh
mvn clean install
mvn jp.skypencil:sample-maven-plugin:sample
mvn jp.skypencil:sample-maven-plugin:help
```

[^1]: "target"などとハードコードすると、ユーザが`project.build.directory`プロパティを変更した際に動作しなくなります。
