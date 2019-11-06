
= Mavenの使い方


基本的には@<tt>{mvn package}のように行いたいことを引数に渡して実行するだけです。
この「行いたいこと」をMavenではフェーズ（phase）と呼んでいます。主なphaseをいくつか紹介します。

 * clean （一時ファイルの削除）
 * validate （プロジェクトの状態確認）
 * compile （プロジェクトのコンパイル）
 * test-compile （テストコードのコンパイル）
 * test （ユニットテストの実行）
 * package （アーティファクトの作成）
 * integration-test （インテグレーションテストの実行）
 * verify （アーティファクトの検証）
 * install （アーティファクトをローカルリポジトリに配置）
 * deploy （アーティファクトをリモートリポジトリに配置）



アーティファクト（artifact）とはjarやwarのような@<href>{http://stackoverflow.com/questions/2487485/what-is-maven-artifact,成果物のことを指します}。
またリポジトリとは他の開発者とアーティファクトを共有するための保管庫を指します。詳しくは@<href>{./maven-repository.md,のちほど説明します}。



ここでは例として、筆者が開発している@<href>{https://github.com/KengoTODA/findbugs-plugin,findbugs plugin}プロジェクトをビルドしてみましょう。
次のコマンドを実行してください。@<tt>{target}ディレクトリが作成され、中にjarファイルが入っていることが確認できます。


//emlist[][zsh]{
$ git clone https://github.com/KengoTODA/findbugs-plugin.git
$ cd findbugs-plugin
$ mvn package
$ ls ./target
//}


targetディレクトリにはアーティファクトだけでなくプロジェクトのclassファイルやテストケースのclassファイル、ユニットテストの実行結果も配置されていることが分かります。
コマンドの引数にはpackage（アーティファクトの作成）しか指定していないのに、Mavenがpackageに必要なcompileやtest-compile、testフェーズも実行してくれていたということです。
この理由は@<href>{./build-lifecycle.md,ビルド・ライフサイクル}の節で解説します。



さて、もうひとつ便利なフェーズを試してみましょう。
@<tt>{mvn clean}を実行すると、@<tt>{target}ディレクトリに作成された一時ファイルをディレクトリごと削除します。
実行後にディレクトリが削除されていることを確認してください。


//emlist[][zsh]{
$ ls -l
$ mvn clean
$ ls -l
//}


Mavenはビルドを高速化するため、すでに作成されたclassファイルなどを再利用することがあります。
ビルドを完全にまっさらな状態から実行する場合は、事前にcleanを実行しておきましょう。



なお@<tt>{target}ディレクトリの削除によってcleanの実行を代替できるように見えますが、一時ファイルがtargetディレクトリ以外の場所に作られることもありえますので、ディレクトリの削除ではなくcleanを利用するように心がけましょう。


== Antに慣れている方のための補足


Antでは各targetの間に依存関係を明示できました。
たとえば次のXMLは、packageを実行する前にcompileを実行しなければならないことを意味しています。


//emlist[][xml]{
<target name="compile">
...
</target>

<target name="package" depends="compile">
...
</target>
//}


Mavenではこうしたtargetと依存関係、各targetで実行すべきtaskがデフォルトで用意されていると考えてください。
開発者の行うべきことがJavaプロジェクトのビルドである以上、行うべき作業には他のJavaプロジェクトとの共通点が多いはずです。
Mavenはそれをデフォルトで提供することにより、開発者がファイルに書くべき設定を削減しています。



MavenではAntのtargetがフェーズ、Antのtaskがプラグインに相当します。
各フェーズで実行されるプラグインはデフォルトで割り当てられたものに加え、好みのものを追加することも可能です。


== makeやnpmに慣れている方のための補足


Mavenのインストールは@<tt>{make install}や@<tt>{npm install -g}とは違い、プロジェクトから実行可能ファイルを作ってPATHに追加することを意味しません。
Mavenのインストールはアーティファクトを作ってローカルリポジトリに配置することです。



またデフォルトではビルドされたアーティファクトは@<tt>{java -jar}で実行できません。
マニフェストファイルを適切に作成しアーティファクトに同梱する必要があります。

