## ビルド・ライフサイクル

さて、Mavenはどのようにしてpackageにcompileやtestが必要だと判断したのでしょうか。これを知るには
[ビルド・ライフサイクル][1]について知る必要があります。

ビルド・ライフサイクルとは「コンパイル→テスト→JAR作成」などのビルドにおける作業の順番を定義したものです。
標準でdefaultサイクルとcleanサイクル、siteサイクルが用意されています。先ほどpackageフェーズ実行時に
使ったのがdefaultサイクル、cleanフェーズ実行時に使ったのがcleanサイクルです。

それぞれのビルド・ライフサイクルは1つ以上のフェーズを含んでいます。例えばdefaultライフサイクルには
compile, test, verify, installといったフェーズが含まれています。

これらのフェーズは順番に並んでいて、あるフェーズが実行されるには *それ以前のフェーズが実行済み* でなければ
なりません。つまり、すべてのフェーズはそのひとつ前のフェーズに依存しています。

例えばdefaultライフサイクルには以下のように並んだフェーズが含まれています。

1. validate
2. initialize
3. generate-sources
4. process-sources
5. generate-resources
6. process-resources
7. compile
8. process-classes
9. generate-test-sources
10. process-test-sources
11. generate-test-resources
12. process-test-resources
13. test-compile
14. process-test-classes
15. test
16. prepare-package
17. package
18. pre-integration-test
19. integration-test
20. post-integration-test
21. verify
22. install
23. deploy

先ほどMavenがコンパイルや自動テストを実行したのは、packageフェーズを実行するために必要な
validateからprepare-packageまでの16のフェーズすべてを実行したためです。
こうしたフェーズの依存関係によって、Mavenユーザはやりたいことだけを伝えるだけで済むのです。

さて、このdefaultライフサイクルにはcleanが見当たりません。cleanフェーズはcleanライフサイクルと呼ばれる他の
ライフサイクルに属しています。このライフサイクルには3つのフェーズがあります。

1. pre-clean
2. clean
3. post-clean

例えば `mvn clean install` と実行すると、まずはcleanライフサイクルが実行され、その次にdefaultライフサイクルが
実行されます。`mvn clean clean`ではcleanライフサイクルが2回実行されます。
「コンパイルしてからテストしたい！」という場合でも`mvn compile test`ではなく`mvn test`で充分だという
ことに注意してください。

[1]: http://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html "Introduction to the Build Lifecycle"
