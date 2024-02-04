# 依存関係

プロジェクトをビルドするときに、JDKだけでなくライブラリを必要とすることがあります。このことを「プロジェクトはライブラリに[依存している](http://maven.apache.org/guides/introduction/introduction-to-dependency-mechanism.html)」と表現します。
Mavenではプロジェクトがライブラリに依存していることを次のように明記できます。

```xml
<dependency><!-- このプロジェクトはJUnit バージョン{{book.version.junit}}に依存している -->
  <groupId>junit</groupId>
  <artifactId>junit</artifactId>
  <version>{{book.version.junit}}</version>
  <scope>test</scope>
</dependency>
```
