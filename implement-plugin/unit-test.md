# ユニットテストを作成する

Mavenプラグインのユニットテストを作成するために、`maven-plugin-testing-harness`というライブラリが
提供されています。ここではこのライブラリをJUnitと組み合わせて、ユニットテストを作成する方法を紹介します。


## pom.xmlに依存ライブラリを追記する

まずJUnitと`maven-plugin-testing-harness`を使用するために、以下2つの`<dependency>`を
`pom.xml`に追加します。

<pre><code class="lang-xml">&lt;dependencies&gt;
  ...
  &lt;dependency&gt;
    &lt;groupId&gt;junit&lt;/groupId&gt;
    &lt;artifactId&gt;junit&lt;/artifactId&gt;
    &lt;version&gt;{{book.version.junit}}&lt;/version&gt;
    &lt;scope&gt;test&lt;/scope&gt;
  &lt;/dependency&gt;
  &lt;dependency&gt;
    &lt;groupId&gt;org.apache.maven.plugin-testing&lt;/groupId&gt;
    &lt;artifactId&gt;maven-plugin-testing-harness&lt;/artifactId&gt;
    &lt;version&gt;3.3.0&lt;/version&gt;
    &lt;scope&gt;test&lt;/scope&gt;
  &lt;/dependency&gt;
&lt;/dependencies&gt;</code></pre>

## ユニットテストを作成する

追加したらユニットテストの作成を開始できます。
`maven-plugin-testing-harness`ではJUnit4の`@Rule`アノテーションを利用しての開発が可能です。
もっとも単純なテストは次のようになります。

```java
public class SampleMojoTest {
  @Rule
  public MojoRule mojoRule = new MojoRule();

  @Rule
  public TestResources resources = new TestResources();

  @Test
  public void testMojoHasHelpGoal() throws Exception {
    // src/test/projects/project/pom.xml に書かれた設定を元にMojoインスタンスを作成
    File baseDir = resources.getBasedir("project");
    File pom = new File(baseDir, "pom.xml");

    // 'help' ゴールを実行
    Mojo mojo = mojoRule.lookupMojo("help", pom);
    mojo.execute();
  }
}
```

`MojoRule`はMojoインスタンスを生成するためのJUnit Ruleです。

`TestResources`は各テストメソッドで固有のリソースを使うためのJUnit Ruleです。
`src/test/projects`次にダミーのMavenプロジェクトが入ったディレクトリを配置しておき、
そのディレクトリ名を`getBasedir()`メソッドに渡すことで、ダミープロジェクトの設定を元に
Mojoインスタンスを作成することができます。

つまりこのテストは、ダミープロジェクトの設定を元に作成したMojoインスタンスのメソッドを呼ぶことで
プラグインが正常に動作することを確認するためのものです。


## 期待とおりに正常終了することをテストする

前述のとおり、`MojoRule`のインスタンスメソッドを通じて取得した`Mojo`インスタンスの`execute()`メソッドを呼ぶことで、
実際にMavenプラグインを実行できます。`execute()`メソッドが例外を投げずに終了した場合、Mavenプラグインが
正常終了したとみなせます。

```java
  @Test
  public void testGoalSucceeds() {
    File baseDir = resources.getBasedir("project");
    File pom = new File(baseDir, "pom.xml");

    Mojo samplePlugin = mojoRule.lookupMojo("help", pom);
    assertNotNull(samplePlugin);
    samplePlugin.execute();
  }
```

テスト内容によっては、実行時にMojoの状態を確認するコードなどを記述する必要があるかもしれません。

## 期待とおりに異常終了することをテストする

設定が異常なときや必要なファイルがないときは、Mavenプラグインが異常終了する必要があります。

JUnitのテストとしては、`execute()`メソッドが`MojoFailureException`あるいは`MojoExecutionException`を投げることを確認するコードを書きます。
次のように`@Test`アノテーションに期待される例外を指定してください。

```java
  @Test(expected = MojoFailureException.class)
  public void testGoalFailsAsExpected() {
    File baseDir = resources.getBasedir("project");
    File pom = new File(baseDir, "pom.xml");

    Mojo samplePlugin = mojoRule.lookupMojo("help", pom);
    assertNotNull(samplePlugin);
    samplePlugin.execute();
  }
```

Wikiによると`MojoExecutionException`は[設定に問題がありMojoの実行ができなかったとき](https://cwiki.apache.org/confluence/display/MAVEN/MojoExecutionException)に、`MojoFailureException`は[依存関係やプロジェクトが持つソースコードに問題がありMojoの実行が失敗したとき](https://cwiki.apache.org/confluence/display/MAVEN/MojoFailureException)に投げる必要があります。

[Javadocに記載されている表現](http://maven.apache.org/ref/{{book.version.maven}}/maven-plugin-api/apidocs/org/apache/maven/plugin/Mojo.html#execute%28%29)で言い換えると、`MojoExecutionException`はプラグイン提供者が発生を期待しない問題が生じたときにビルドをエラー終了させるために、`MojoFailureException`はプラグイン提供者が期待する問題が生じたときにビルドを失敗させるために使います。
適宜使い分けてください。


## ログが正しく呼ばれていることを確認する

Mavenプラグインを使用するユーザは、ログを通じてプラグインからの結果報告や異常通知などを受けます。
このためログが特定の条件下で期待とおりに出ることは、ぜひテストで確認・保証しておきたいポイントです。

`Mojo`インタフェースはロガーをセットするメソッドを提供していますので、モックオブジェクトを利用することができます。
次のコードは[Mockito](https://github.com/mockito/mockito)を利用してデバッグログの出力内容を確認するものです。

```java
  @Test
  public void testSampleGoalPrintsOutputDirectory() throws Exception {
    File baseDir = resources.getBasedir("simple");
    File pom = new File(baseDir, "pom.xml");
    Log log = Mockito.mock(Log.class);

    Mojo samplePlugin = mojoRule.lookupMojo("sample", pom);
    samplePlugin.setLog(log);
    samplePlugin.execute();
    Mockito.verify(log).debug("outputDirectory is /tmp/target");
  }
```

以上で紹介したように、Mavenプラグインは簡単にユニットテストによってテストできます。
複数の動作環境で動作することを保証する意味でも、ソースコードの変更によるバグ混入を未然に防ぐ意味でも、自動テストはプラグイン開発に有用です。
[Jenkinsのマルチ構成プロジェクト](https://wiki.jenkins-ci.org/display/JA/Building+a+matrix+project)や[JUnitのTheory](https://github.com/junit-team/junit/wiki/Theories)と組み合わせるなどして、機能の安定提供に役立ててください。
