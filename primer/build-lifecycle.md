# ビルド・ライフサイクル

さて、Mavenはどのようにしてpackageの実行にcompileやtestが必要だと判断したのでしょうか。
これを理解するには、[ビルド・ライフサイクル][1]について知る必要があります。

ビルド・ライフサイクルとは「コンパイル→テスト→JAR作成」などのビルドにおける作業の順番を定義したものです。
標準でdefaultサイクルとcleanサイクル、siteサイクルが用意されています。
先ほどpackageフェーズ実行時に使ったのが *defaultサイクル* 、cleanフェーズ実行時に使ったのが *cleanサイクル* です。

それぞれのビルド・ライフサイクルは1つ以上のフェーズを含んでいます。
これらのフェーズは順番に並んでいて、あるフェーズが実行されるには *それ以前のフェーズが実行済み* でなければなりません。
言い換えると、すべてのフェーズはそのひとつ前のフェーズに依存しているということです。

## defaultライフサイクル

defaultライフサイクルには以下のように並んだフェーズが含まれています。

1. validate （プロジェクトの状態確認）
2. initialize （ビルドの初期化処理）
3. generate-sources （ソースコードの自動生成）
4. process-sources （ソースコードの自動処理）
5. generate-resources （リソースの自動生成）
6. process-resources （リソースの自動処理）
7. compile （プロジェクトのコンパイル）
8. process-classes （classファイルの自動処理）
9. generate-test-sources （テストコードの自動生成）
10. process-test-sources （テストコードの自動処理）
11. generate-test-resources （テスト用リソースの自動生成）
12. process-test-resources （テスト用リソースの自動処理）
13. test-compile （テストコードのコンパイル）
14. process-test-classes （テスト用classファイルの自動処理）
15. test （ユニットテストの実行）
16. prepare-package （アーティファクト作成の準備）
17. package （アーティファクトの作成）
18. pre-integration-test （インテグレーションテストの前処理）
19. integration-test （インテグレーションテストの実行）
20. post-integration-test （インテグレーションテストの後処理）
21. verify （アーティファクトの検証）
22. install （アーティファクトをローカルリポジトリに配置）
23. deploy （アーティファクトをリモートリポジトリに配置）

先ほどMavenがコンパイルや自動テストを実行したのは、packageフェーズを実行するために必要なvalidateからprepare-packageまでの16のフェーズすべてを実行したためです。
こうしたフェーズの依存関係によって、Mavenユーザはやりたいことだけを伝えるだけで済むのです。

## cleanライフサイクル

前述のdefaultライフサイクルにはcleanフェーズが見当たりません。
cleanフェーズはcleanライフサイクルと呼ばれる他のライフサイクルに属しています。
このライフサイクルには3つのフェーズがあります。

1. pre-clean （一時ファイル削除の前処理）
2. clean （一時ファイルの削除）
3. post-clean （一時ファイル削除の後処理）

例えば `mvn clean install` と実行すると、まずはcleanライフサイクルが実行され、その次にdefaultライフサイクルが実行されます。
`mvn clean clean`ではcleanライフサイクルが2回実行されます。

[1]: http://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html "Introduction to the Build Lifecycle"
