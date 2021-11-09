# Mavenのインストール

まず先に[JDKをインストール](http://www.oracle.com/technetwork/java/javase/downloads/)しておいてください。

次に[Maven公式サイトから圧縮ファイルをダウンロード](http://maven.apache.org/download.cgi)し、展開してください。
binディレクトリに実行可能ファイルが含まれていますので、これをPATHに追加すればインストールは完了です。

最後に`mvn --version`を実行して、Mavenが正しく実行されること・意図どおりのJDKが認識されていることを確認してください。
参考までに、執筆している環境では次のような出力が得られました。

<pre><code class="lang-zsh">$ mvn --version
Apache Maven 3.8.3 (ff8e977a158738155dc465c6a97ffaf31982d739)
Maven home: /Users/kengo/.m2/wrapper/dists/apache-maven-3.8.3-bin/5a6n1u8or3307vo2u2jgmkhm0t/apache-maven-3.8.3
Java version: 11.0.13, vendor: GraalVM Community, runtime: /Users/kengo/Downloads/graalvm-ce-java11-21.3.0/Contents/Home
Default locale: en_JP, platform encoding: UTF-8
OS name: "mac os x", version: "12.0.1", arch: "x86_64", family: "mac"
</core></pre>

このように、Mavenは`mvn`コマンドによって呼び出します。`--version`はMavenやJDKのバージョンを出力するための
オプションです。オプションについては適宜解説していきます。

利用されるJDKが意図したものではなかった場合、`JAVA_HOME`環境変数にJDKのホーム（jreディレクトリの親ディレクトリ）を
設定してから再度`mvn --version`を実行して確認してください。
