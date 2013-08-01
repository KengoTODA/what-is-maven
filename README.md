# Mavenとは

プロジェクトをビルドするためのツールです。
ソースコードのコンパイルに加えて、依存関係を整理して必要なJARファイルを探したりテストを実行したりビルドしたJARファイルを公開したりといった作業を簡単に行うことができます。

# リポジトリとは

JARファイルをライブラリやバージョンごとに整理してまとめておく場所のことです。セントラルリポジトリ、ローカルリポジトリ、プライベートリポジトリの3種類があります。JARだけでなくソースコードやJavadocを保管することもできます。

## セントラルリポジトリとは

インターネットに公開されているリポジトリで、たくさんのライブラリ（JARファイル）が公開されています。

- [Maven central repository](http://search.maven.org/)

### セントラルリポジトリにライブラリを登録する

以下のページを参照してください。

- [【最新版】Maven Central Repository へのライブラリ登録方法 #maven](http://samuraism.jp/diary/2012/05/03/1336047480000.html)

## ローカルリポジトリとは

mvnコマンドを実行したマシンにある単純なディレクトリのことです。デフォルトでは`~/.m2/repository`が利用されます。
他のリポジトリからダウンロードしたライブラリを保管するため、`install`ゴールでJARをインストールするために使われます。

## プライベートリポジトリとは



# ゴール

## clean

## compile

## test

## package

## verify

## install


# この文書について

<a rel="license" href="http://creativecommons.org/licenses/by/3.0/deed.en_US"><img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by/3.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/3.0/deed.en_US">Creative Commons Attribution 3.0 Unported License</a>.

