# 困ったときの逆引き

この章ではMaven利用時にありがちな問題について、調査方法と解決方法を説明します。

## 環境によって結果が異なる場合

実行環境によって結果が異なる場合、まずはJDKのバージョンやLocaleなどに環境差がないかどうか確認します。
以下のコマンドで環境依存の情報を一括確認できますので、利用してください。

```sh
mvn -v
```

またファイルパスによる問題なら、以下も確認してください。

* Windowsではバックスラッシュ（または円記号）、UNIX系ではスラッシュを[ファイル区切り文字][^1]に利用します。
  Mavenの設定では一括してスラッシュを利用して構いませんが、必要に応じて`${file.separator}`を利用できます。
* Windowsでは[ファイルのパスが長すぎると問題になることがあります](http://stackoverflow.com/a/265782)。
  Javaはパッケージとフォルダ階層を等しくする必要があるため、この制限に引っかかる可能性があります。
  プロジェクトはドライブ直下など、パスが浅い場所に作成するようにしてください。

これでも解決できない場合は、Mavenの設定に相違がないか確認するとよいでしょう。Mavenは実行環境に応じて
設定を切り替える機能を提供しているため、これによって結果が異なってしまっているのかもしれません。
Mavenは原因究明に便利なプラグインを提供していますので、以下に紹介します。

まずは[maven-help-pluginのactive-profilesゴール](http://maven.apache.org/plugins/maven-help-plugin/active-profiles-mojo.html)です。
これは実行時に有効化されているMavenプロファイルを一覧で表示してくれます。有効化されているMavenプロファイルに差があれば、そこに原因があるかもしれません。
このゴールを利用するには、以下のように`mvn`コマンドを実行します：

```sh
mvn org.apache.maven.plugins:maven-help-plugin:2.2:active-profiles
```

次に[maven-help-pluginのeffective-pomゴール](http://maven.apache.org/plugins/maven-help-plugin/effective-pom-mojo.html)です。
`pom.xml`は継承や`settings.xml`やMavenプロファイルなど、様々な要因によって要素が書き換えられますが、
このゴールはそうした変動要因を考慮した、最終的な設定を出力してくれます。
このゴールを利用するには、以下のように`mvn`コマンドを実行します：

```sh
mvn org.apache.maven.plugins:maven-help-plugin:2.2:effective-pom
```

最後に[maven-help-pluginのeffective-settingsゴール](http://maven.apache.org/plugins/maven-help-plugin/effective-settings-mojo.html)です。
これはMavenリポジトリのミラーサイトなど、`pom.xml`に書かれていない（プロジェクトに依存しない）設定を参照するために使用します。
このゴールを利用するには、以下のように`mvn`コマンドを実行します：

```sh
mvn org.apache.maven.plugins:maven-help-plugin:2.2:effective-settings
```

この他にも[maven-help-plugin](http://maven.apache.org/plugins/maven-help-plugin/)は
環境依存の原因究明に便利なゴールを多数提供していますので、一度見ておくとよいでしょう。


## Mavenプラグインに設定がきちんと渡っているか不安な場合

`mvn`コマンドを実行するときに、`-X`オプションを加えてみてください。
デバッグログが出力され、各プラグインがどのような設定を受け取ったか表示されるようになります。

デバッグログの出力はビルドの実行を低速化させ、ログファイルを大きくしますので、原因究明するときにのみ
使うようにするとよいでしょう。

## ClassNotFoundExceptionが出る場合

TODO

[^1]: ディレクトリ名を区切るための文字のこと。Windowsの場合は`C:\\Foo\Bar\Baz.txt`のようにバックスラッシュで区切り、UNIX系の場合は`/tmp/Foo/Bar/Baz.txt`のようにスラッシュで区切ります。
