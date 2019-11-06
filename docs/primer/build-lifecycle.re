
= ビルド・ライフサイクル


さて、Mavenはどのようにしてpackageの実行にcompileやtestが必要だと判断したのでしょうか。
これを理解するには、@<href>{http://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html,ビルド・ライフサイクル}について知る必要があります。



ビルド・ライフサイクルとは「コンパイル→テスト→JAR作成」などのビルドにおける作業の順番を定義したものです。
標準でdefaultサイクルとcleanサイクル、siteサイクルが用意されています。
先ほどpackageフェーズ実行時に使ったのが @<b>{defaultサイクル} 、cleanフェーズ実行時に使ったのが @<b>{cleanサイクル} です。



それぞれのビルド・ライフサイクルは1つ以上のフェーズを含んでいます。
これらのフェーズは順番に並んでいて、あるフェーズが実行されるには @<b>{それ以前のフェーズが実行済み} でなければなりません。
言い換えると、すべてのフェーズはそのひとつ前のフェーズに依存しているということです。


== defaultライフサイクル


defaultライフサイクルには次のように並んだフェーズが含まれています。

 1. validate （プロジェクトの状態確認）
 1. initialize （ビルドの初期化処理）
 1. generate-sources （ソースコードの自動生成）
 1. process-sources （ソースコードの自動処理）
 1. generate-resources （リソースの自動生成）
 1. process-resources （リソースの自動処理）
 1. compile （プロジェクトのコンパイル）
 1. process-classes （classファイルの自動処理）
 1. generate-test-sources （テストコードの自動生成）
 1. process-test-sources （テストコードの自動処理）
 1. generate-test-resources （テスト用リソースの自動生成）
 1. process-test-resources （テスト用リソースの自動処理）
 1. test-compile （テストコードのコンパイル）
 1. process-test-classes （テスト用classファイルの自動処理）
 1. test （ユニットテストの実行）
 1. prepare-package （アーティファクト作成の準備）
 1. package （アーティファクトの作成）
 1. pre-integration-test （インテグレーションテストの前処理）
 1. integration-test （インテグレーションテストの実行）
 1. post-integration-test （インテグレーションテストの後処理）
 1. verify （アーティファクトの検証）
 1. install （アーティファクトをローカルリポジトリに配置）
 1. deploy （アーティファクトをリモートリポジトリに配置）



先ほどMavenがコンパイルや自動テストを実行したのは、packageフェーズを実行するために必要なvalidateからprepare-packageまでの16のフェーズすべてを実行したためです。
こうしたフェーズの依存関係によって、Mavenユーザはやりたいことだけを伝えるだけで済むのです。


== cleanライフサイクル


前述のdefaultライフサイクルにはcleanフェーズが見当たりません。
cleanフェーズはcleanライフサイクルと呼ばれる他のライフサイクルに属しています。
このライフサイクルには3つのフェーズがあります。

 1. pre-clean （一時ファイル削除の前処理）
 1. clean （一時ファイルの削除）
 1. post-clean （一時ファイル削除の後処理）



たとえば @<tt>{mvn clean install} と実行すると、まずはcleanライフサイクルが実行され、その次にdefaultライフサイクルが実行されます。
@<tt>{mvn clean clean}ではcleanライフサイクルが2回実行されます。

