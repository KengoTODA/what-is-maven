# Mavenのインストール

まず先に[JDKをインストール](http://www.oracle.com/technetwork/java/javase/downloads/)しておいてください。

次に[Maven公式サイトから圧縮ファイルをダウンロード](http://maven.apache.org/download.cgi)し、展開してください。
binディレクトリに実行可能ファイルが含まれていますので、これをPATHに追加すればインストールは完了です。

最後に`mvn --version`を実行して、Mavenが正しく実行されること・意図どおりのJDKが認識されていることを確認してください。
参考までに、執筆している環境では次のような出力が得られました。

<pre><code class="lang-zsh">$ mvn --version
Apache Maven 3.8.1 (05c21c65bdfed0f71a2f2ada8b84da59348c4c5d)
Maven home: /Users/kengo/.m2/wrapper/dists/apache-maven-3.8.1-bin/2l5mhf2pq2clrde7f7qp1rdt5m/apache-maven-3.8.1
Java version: 1.8.0_191, vendor: Oracle Corporation, runtime: /home/kengo/jvm/oracle-jdk-1.8.0_191/jre
Default locale: en_US, platform encoding: UTF-8
OS name: "linux", version: "4.15.0-38-generic", arch: "amd64", family: "unix"
</core></pre>

このように、Mavenは`mvn`コマンドによって呼び出します。`--version`はMavenやJDKのバージョンを出力するための
オプションです。オプションについては適宜解説していきます。

利用されるJDKが意図したものではなかった場合、`JAVA_HOME`環境変数にJDKのホーム（jreディレクトリの親ディレクトリ）を
設定してから再度`mvn --version`を実行して確認してください。
