# 単体テストを作成する

Mavenプラグインの単体テストを作成するために、`maven-plugin-testing-harness`というライブラリが
提供されています。ここではこのライブラリをJUnitと組み合わせて、単体テストを作成する方法を紹介します。


## pom.xmlに依存ライブラリを追記する

まずJUnitと`maven-plugin-testing-harness`を使用するために、以下2つの`<dependency>`を
`pom.xml`に追加します。

```xml
<dependencies>
  ...
  <dependency>
    <groupId>junit</groupId>
    <artifactId>junit</artifactId>
    <version>4.12</version>
    <scope>test</scope>
  </dependency>
  <dependency>
    <groupId>org.apache.maven.plugin-testing</groupId>
    <artifactId>maven-plugin-testing-harness</artifactId>
    <version>3.3.0</version>
    <scope>test</scope>
  </dependency>
</dependencies>
```

## 単体テストを作成する

追加したら単体テストの作成を開始できます。
`maven-plugin-testing-harness`ではJUnit4の`@Rule`アノテーションを利用しての開発が可能です。
最も単純なテストは以下のようになります。

```java
public class SampleMojoTest {
  @Rule
  public MojoRule mojo = new MojoRule();

  @Rule
  public TestResources resources = new TestResources();

  @Test
  public void testMojoHasHelpGoal() throws Exception {
    // src/test/projects/project/pom.xml に書かれた設定を元にMojoインスタンスを作成
    File baseDir = resources.getBasedir("project");
    File pom = new File(baseDir, "pom.xml");

    // 'help' ゴールを実行
    Mojo mojo = mojo.lookupMojo("help", pom);
    mojo.execute();
  }
}
```

`MojoRule`はMojoインスタンスを生成するためのJUnit Ruleです。

`TestResources`は各テストメソッドで固有のリソースを使うためのJUnit Ruleです。
`src/test/projects`以下にダミー用のMavenプロジェクトを配置


## 期待通りに正常終了することをテストする

`MojoRule`のインスタンスメソッドを通じて取得した`Mojo`インスタンスの`execute()`メソッドを呼ぶことで、
実際にMavenプラグインを実行できます。`execute()`メソッドが例外を投げずに終了した場合、Mavenプラグインが
正常終了したとみなせます。

```java
  @Test
  public void testGoalSucceeds() {
    // TODO how to use lookupMojo?
    Mojo samplePlugin = mojo.lookupMojo("help", "pom.xml");
    assertNotNull(samplePlugin);
    samplePlugin.execute();
  }
```

テスト内容によっては、実行時にMojoの状態を確認するコードなどを記述する必要があるかもしれません。

## 期待通りに異常終了することをテストする

設定が異常なときや必要なファイルがないときは、Mavenプラグインが異常終了する必要があります。

JUnitのテストとしては、`execute()`メソッドが`MojoFailureException`を投げることを確認するコードを書きます。
次のように`@Test`アノテーションに期待される例外を指定してください。

```java
  @Test(expected = MojoFailureException.class)
  public void testGoalFailsAsExpected() {
    // TODO how to use lookupMojo?
    Mojo samplePlugin = mojo.lookupMojo("help", "pom.xml");
    assertNotNull(samplePlugin);
    samplePlugin.execute();
  }
```

// TODO MojoExecutionException との違いは？

## ログが正しく呼ばれていることを確認する

Mavenプラグインを使用するユーザは、ログを通じてプラグインからの結果報告や異常通知などを受けます。
このためログが特定の条件下で期待通りに出ること、


```java
```



* http://maven.apache.org/plugin-testing/maven-plugin-testing-harness/getting-started/index.html
