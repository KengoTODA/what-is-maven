
= Mavenのインストール


まず先に@<href>{http://www.oracle.com/technetwork/java/javase/downloads/,JDKをインストール}しておいてください。



次に@<href>{http://maven.apache.org/download.cgi,Maven公式サイトから圧縮ファイルをダウンロード}し、展開してください。
binディレクトリに実行可能ファイルが含まれていますので、これをPATHに追加すればインストールは完了です。



最後に@<tt>{mvn --version}を実行して、Mavenが正しく実行されること・意図どおりのJDKが認識されていることを確認してください。
参考までに、執筆している環境では次のような出力が得られました。


//emlist{
XXX: BLOCK_HTML: YOU SHOULD REWRITE IT
<pre><code class="lang-zsh">$ mvn --version
Apache Maven 3.6.0 (97c98ec64a1fdfee7767ce5ffb20918da4f719f3; 2018-10-25T02:41:47+08:00)
Maven home: /home/kengo/.m2/wrapper/dists/apache-maven-3.6.0-bin/3rgjh30jneo7541hun7uggltkb/apache-maven-3.6.0
Java version: 1.8.0_191, vendor: Oracle Corporation, runtime: /home/kengo/jvm/oracle-jdk-1.8.0_191/jre
Default locale: en_US, platform encoding: UTF-8
OS name: "linux", version: "4.15.0-38-generic", arch: "amd64", family: "unix"
</core></pre>

//}


このように、Mavenは@<tt>{mvn}コマンドによって呼び出します。@<tt>{--version}はMavenやJDKのバージョンを出力するための
オプションです。オプションについては適宜解説していきます。



利用されるJDKが意図したものではなかった場合、@<tt>{JAVA_HOME}環境変数にJDKのホーム（jreディレクトリの親ディレクトリ）を
設定してから再度@<tt>{mvn --version}を実行して確認してください。

