
= 依存関係


プロジェクトをビルドするときに、JDKだけでなくライブラリを必要とすることがあります。このことを「プロジェクトはライブラリに@<href>{http://maven.apache.org/guides/introduction/introduction-to-dependency-mechanism.html,依存している}」と表現します。
Mavenではプロジェクトがライブラリに依存していることを次のように明記できます。


//emlist{
XXX: BLOCK_HTML: YOU SHOULD REWRITE IT
<pre><code class="lang-xml">&lt;dependency&gt;&lt;!-- このプロジェクトはJUnit バージョン{{book.version.junit}}に依存している --&gt;
  &lt;groupId&gt;junit&lt;/groupId&gt;
  &lt;artifactId&gt;junit&lt;/artifactId&gt;
  &lt;version&gt;{{book.version.junit}}&lt;/version&gt;
  &lt;scope&gt;test&lt;/scope&gt;
&lt;/dependency&gt;</code></pre>
//}
