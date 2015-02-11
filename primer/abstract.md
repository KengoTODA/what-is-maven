## Mavenの使い方

基本的には`mvn package`のように行いたいことを引数に渡して実行するだけです。
この「行いたいこと」をMavenではフェーズ（phase）と呼んでいます。主なphaseをいくつか紹介します。

* validate （プロジェクトの状態確認）
* clean （一時ファイルの削除）
* compile （プロジェクトのコンパイル）
* test-compile （テストコードのコンパイル）
* test （単体テストの実行）
* package （アーティファクトの作成）
* integration-test （インテグレーションテストの実行）
* verify （アーティファクトの検証）
* install （アーティファクトをローカルリポジトリに配置）
* deploy （アーティファクトをリモートリポジトリに配置）

アーティファクト（artifact）とはjarやwarのような[成果物のこと][1]を指します。またリポジトリとは他の
開発者とアーティファクトを共有するための保管庫を指します。詳しくはのちほど説明します。

ここでは例として、筆者が開発している[findbugs plugin](https://github.com/KengoTODA/findbugs-plugin)プロジェクトを
ビルドしてみましょう。以下のコマンドを実行してください。`target`ディレクトリが作成され、中にjarファイルが入っていることが
確認できますか？

```zsh
$ git clone https://github.com/KengoTODA/findbugs-plugin.git
$ cd findbugs-plugin
$ mvn package
$ ls ./target
```

targetディレクトリにはアーティファクトだけでなくプロジェクトのclassファイルやテストケースのclassファイル、
単体テストの実行結果も配置されていることがわかると思います。コマンドの引数にはpackage（アーティファクトの作成）
しか指定していないのに、Mavenがpackageに必要なcompileやtest-compile、testフェーズも実行してくれていた
ということです。

さて、もうひとつ便利なフェーズを試してみましょう。`mvn clean`を実行すると、`target`ディレクトリに作成された
一時ファイルをディレクトリごと削除します。実行後にディレクトリが削除されていることを確認してください。

```zsh
$ ls -l
$ mvn clean
$ ls -l
```

Mavenはビルドを高速化するため、既に作成されたclassファイルなどを再利用することがあります。
ビルドを完全にまっさらな状態から実行する場合は、事前にcleanを実行しておきましょう。

なお`target`ディレクトリの削除によってcleanの実行を代替できるように見えますが、一時ファイルが
targetディレクトリ以外の場所に作られることもありえますので、ディレクトリの削除ではなくcleanを
利用するように心がけましょう。

[1]: http://stackoverflow.com/questions/2487485/what-is-maven-artifact "What is Maven artifact?"

### Antに慣れている方のための補足

Antでは各targetの間に依存関係を明示することができました。例えば以下のXMLは、packageを実行する前に
compileを実行しなければならないことを意味しています。

```xml
<target name="compile">
...
</target>

<target name="package" depends="compile">
...
</target>
```

Mavenではこうしたtargetと依存関係、各targetで実行すべきtaskがデフォルトで用意されていると考えてください。
開発者が行うべきことがJavaプロジェクトのビルドである以上、行うべき作業には他のJavaプロジェクトとの共通点が
多いはずです。Mavenはそれをデフォルトで提供することにより、開発者がファイルに書くべき設定を削減しています。

MavenではAntのtargetがフェーズ、Antのtaskがプラグインに相当します。各フェーズで実行されるプラグインは
デフォルトで割り当てられたものに加え、好みのものを追加することも可能です。

### makeやnpmに慣れている方のための補足

Mavenのインストールは`make install`や`npm install -g`とは違い、プロジェクトから実行可能ファイルを作って
PATHに追加することを意味しません。アーティファクトを作ってプライベートリポジトリに配置することです。

またデフォルトではビルドされたアーティファクトは`java -jar`で実行できません。マニフェストファイルを適切に作成する必要があります。
