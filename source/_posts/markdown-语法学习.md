---
title: markdown 语法学习
date: 2019-03-18 16:29:08
tags:
- markdown
categories:
- 技术
---

[官网]: <https://daringfireball.net/projects/markdown/> "官方网站"

### 概述
这篇文章主要讲解了 markdown 的语法规则、编辑器以及一些使用技巧。

### 在线测试一下
下面这个是用来尝试 markdown 语法的：

<iframe src="http://wqf31415.coding.me/app/markdown-viewer.html" name="iframe_a" style="border: 1px solid #ccc;width: 100%; height: 500px;"></iframe>


<!-- more -->

### 概念
> [官网][] Markdown is a text-to-HTML conversion tool for web writers. Markdown allows you to write using an easy-to-read, easy-to-write plain text format, then convert it to structurally valid XHTML (or HTML).

Markdown 是一种易读、易写的纯文本格式语法工具，帮网络作者将文本文档转成 HTML 或 XHTML。
Markdown 不是 HTML 的替代品或类似产品，只是它的一个子集，包含了部分 HTML 元素，让你不学习 HTML 就可以写出漂亮的文章。Markdown 的特点是轻量化、易读易写、支持插入图片、图表、代码或数学式，很多论坛上使用 markdown 来发表文章或撰写说明文档，如 Github、reddit、CSDN、印象笔记、简书等。

### 基本语法
#### 标题
在 markdown 中，标题以 `#` 字符指定，与标题文字间以空格分隔，`#` 字符数量限定标题级数，一般支持 6 级标题，对应 HTML 中的 `H1` ~ `H6` 标签。如：
```markdown
markdown:
## 二级标题
#### 四级标题

html：
<h2>二级标题</h2>
<h4>四级标题</h4>
```

#### 段落
在 markdown 中，每一行普通文字就是一个 段落，不同段落需要使用空行分隔，没有空行的两行文字将会呈现在一个段落中，中间会添加一个 `<br>` 标签，段落对应 HTML 中 `p` 标签。如：
```markdown
markdown:
这是一个段落。
段落第二行。

第二段。

html:
<p>这是一个段落。<br>段落第二行。</p>
<p>第二段。</p>
```

#### 文字样式
- **加粗**: 使用双 `*` 或双 `_` 包裹得到加粗的文字，对应 HTML 的 `strong` 标签，如  `**加粗文字**`，将得到 `<strong>加粗文字</strong>`，效果：**加粗文字**。
- _倾斜_ : 使用 单 `*` 或单 `_` 包裹得到倾斜的文字，对应 HTML 的 `em` 标签，如 `*倾斜文字*`，将得到 `<em>倾斜文字</em>`，效果：*倾斜文字*。


#### 分割线
使用三个及以上连续或以空格分隔的 `-` 或 `_` 或 `*`  添加分割线，用于分隔文章，对应 HTML 中的 `<hr/>` 标签。注意分割线上方必须要有空行，否则不生效。
```markdown
---
----
- - -
-------------------
___
____
_ _ _
____________________
***
****
* * *
********************
* * * * * * * * * * *
```

- - - - - - - - - - - - - - - - - - - -

#### 引用块
使用 `> ` 定义引用块，对应 HTML 中的 `blockquote` 标签，添加二级引用块时使用两个 `>` 符号，中间用空格分隔；引用块分段时，使用 `>` 指定一个空行。如：
```markdown
markdown:
> 引用块 
> > 二级引用块。
>
> 引用块第二段

html:
<blockquote>
  <p>引用块 </p>
<blockquote>
  <p>二级引用块。</p>
</blockquote>
<p>引用块第二段</p>
</blockquote>
```

效果：
> 引用块 
> > 二级引用块。
>
> 引用块第二段


#### 列表
##### 无序列表
使用 `-` 或 `+` 或 `*` 定义无序列表，对应 HTML 中 `ul`，这三个符号可以混用，使用缩进指定列表层级，如在列表项下方空两格，可以指定子列表项。示例：
```markdown
markdown:
- 列表项1
列表项1的内容
  - 子项1
  - 子项2
    列表子项2的内容。
- 列表项2
  列表项2的内容。

+ 列表项3
列表项3 的内容。
+ 列表项4

* 列表项5
* 列表项6

html:
<ul>
<li>列表项1
列表项1的内容
<ul><li>子项1</li>
<li>子项2
列表子项2的内容。</li></ul></li>
<li><p>列表项2
列表项2的内容。</p></li>
<li><p>列表项3
列表项3 的内容。</p></li>
<li><p>列表项4</p></li>
<li><p>列表项5</p></li>
<li>列表项6</li>
</ul>
```

效果：
- 列表项1
  列表项1的内容
  - 子项1
  - 子项2
    列表子项2的内容。
- 列表项2
  列表项2的内容。

+ 列表项3
  列表项3 的内容。
+ 列表项4

* 列表项5
* 列表项6

##### 有序列表
使用数字加 `.`来添加有序列表，对应 HTML 中 `ol` 标签，使用缩进确定列表层级，数字值与顺序不影响最终结果。示例：
```markdown
markdown
1. 列表项1
列表项1内容
2. 列表项2
  9. 子项1
  7. 子项2
  15. 子项3
3. 列表项3
  1. 子项1
  1. 子项2
    子项内容。
  1. 子项3
    0. 子子项1
    0. 子子项2
    
html：
<ol>
<li>列表项1
列表项1内容</li>
<li>列表项2
<ol><li>子项1</li>
<li>子项2</li>
<li>子项3</li></ol></li>
<li>列表项3
<ol><li>子项1</li>
<li>子项2
子项内容。</li>
<li>子项3</li>
<li>子子项1</li>
<li>子子项2</li></ol></li>
</ol>
```

效果(不同编辑器渲染效果可能略有不同)：
1. 列表项1
  列表项1内容
2. 列表项2
  9. 子项1
  10. 子项2
  11. 子项3
3. 列表项3
  1. 子项1
  2. 子项2
    子项内容。
  3. 子项3
    0. 子子项1
    1. 子子项2

#### 表格
使用 `|` 符号创建表格，第一行为表头，第二行使用 `:` 与 `----` 指定每一列的对其方式，`：` 在左边为左对齐，在右边为右对齐，在两边为居中对齐，没有 `:` 时不指定对齐方式。示例：
```markdown
markdown:
|列1|列2|列3|列4|
|:----|:----:|----:|----|
|左对齐|居中对齐|右对齐|默认对齐|
|1|2|3|4|

html:
<table> 
  <thead> 
    <tr> 
      <th align="left">列1</th> 
      <th align="center">列2</th> 
      <th align="right">列3</th> 
      <th>列4</th> 
    </tr> 
  </thead> 
  <tbody>
    <tr> 
      <td align="left">左对齐</td> 
      <td align="center">居中对齐</td> 
      <td align="right">右对齐</td> 
      <td>默认对齐</td> 
    </tr> 
    <tr> 
      <td align="left">1</td> 
      <td align="center">2</td> 
      <td align="right">3</td> 
      <td>4</td> 
    </tr> 
  </tbody>
</table>
```

效果：

| 列1   |  列2  |   列3 | 列4   |
| :---- | :----: | ----: | ---- |
| 左对齐  | 居中对齐 |  右对齐 | 默认对齐 |
| 1    |  2   |    3 | 4    |


#### 代码与代码块
**代码**：使用反引号 `` `代码` `` 包裹内容来指定代码，使用两个反引号 ` `` ` 来显示单反引号，对应 HTML 中 `<code>代码</code>` 标签；
**代码块**：使用多个(3个或更多)反引号来指定代码块，生成的 HTML 内容会被 `<pre><code>代码内容</code></pre>` 标签包裹以此保留代码的缩进信息。在代码块起始标记后可添加语言类型，以指定代码的语言类型，结束代码块需要与起始定义保持相同数量的代引号。示例：

> 注：需要在代码中显示反单引号 `` ` `` 时，用其他数量的反单引号组合包裹要显示的反单引号即可。如需要显示 1 个反单引号时，就用两个 单引号包裹这一个单引号，中间用空格分隔，<code>\`\` \` \`\`</code> ，效果：`` ` ``。如果要显示两个反引号时，就用一个单引号包裹，<code>\` \`\` \`</code>，效果：` `` `。


``````markdown
markdown：
`` 单反引号 ` ``

`var a = 12;`

``const b = 1.2``

​```java
String c = "hello";
​```

html:
<p><code>单反引号 `</code></p>
<p><code>var a = 12;</code></p> 
<p><code>const b = 1.2</code></p> 
<pre>
  <code class="language-java">String c = &quot;hello&quot;;</code>
</pre>
``````

效果：
`` 单反引号 ` ``

`var a = 12;`

``const b = 1.2 ``

​```java
String c = "hello";
​```

#### 链接
给文字添加超链接，需要使用 `[文本内容](url "说明")`，对应 HTML 中 `<a href="url" title="说明">文本内容</a>` 标签。

引用模式，适合需要多次引用的链接：

- 方式1 通过 `[id]: url "说明"` 来定义链接信息，使用 `[文本内容][id]` 来引用链接；
- 方式2 通过 `<url>` 标记URL为链接，将生成 HTML 标签 `<a href="url">url</a>`，用这种方式可以生成邮箱链接，如 `<wqf31415@hotmail.com>` 将产生超链接到指定邮箱地址，生成的 HTML 为 `<a href="mailto:wqf31415@hotmail.com">wqf31415@hotmail.com</a>`，效果：<wqf31415@hotmail.com>；
- 方式3 通过 `[链接名]: url "说明"` 来定义链接信息，使用 `[链接名][]` 来引用链接；

> 注：url 可以使用 `<` 与 `>` 括起来，说明信息需要使用双引号 `"` 或单引号 `'` 或小括号 `()` 包裹起来，否则会当成 url 的一部分，说明信息可以为空。 
> 使用引用模式时，使用的 id 和链接名是不区分大小写的，如 `mYbLOG` 与 `MyBlog` 是可以引用的。
> 在编译成 html 时，引用定义将不存在。

```markdown
markdown：
[我的博客](http://blog.wqf31415.xyz "打开我的博客")
[引用模式][1]
[MyBlog][]
[mYbLOG][]

[1]: http://blog.wqf31415.xyz "引用模式"
[MyBlog]: <http://blog.wqf31415.xyz> '引用模式2'

HTML：
<p>
  <a href="http://blog.wqf31415.xyz" title="打开我的博客">我的博客</a><br/>
  <a href="http://blog.wqf31415.xyz" title="引用模式">引用模式</a><br/>
  <a href="http://blog.wqf31415.xyz" title="引用模式2">MyBlog</a><br/>
  <a href="http://blog.wqf31415.xyz" title="引用模式2">mYbLOG</a>
</p>
```

效果：
[我的博客](http://blog.wqf31415.xyz "打开我的博客")
[引用模式][1]
[MyBlog][]
[mYbLOG][]

[1]: http://blog.wqf31415.xyz "引用模式"
[MyBlog]: <http://blog.wqf31415.xyz> "引用模式2"

#### 图片
使用 `![图片名](url "标题")` 来插入图片，对应 HTML 中 `<img src="url" alt="图片名" title="标题"/>` 标签。
使用引用模式：
- 使用 `[id]: url "图片标题"` 来定义链接信息，使用 `![说明信息][id]` 来引用图片。

```markdown
markdown:
![这是个灯泡](http://blog-images.qiniu.wqf31415.xyz/icon-dianyu.png "灯泡")
![这是引用模式的][dengpao]

[dengpao]: http://blog-images.qiniu.wqf31415.xyz/icon-dianyu.png "引用模式-灯泡"

html:
<p>
  <img src="http://blog-images.qiniu.wqf31415.xyz/icon-dianyu.png" alt="这是个灯泡" title="灯泡"/><br/>
  <img src="http://blog-images.qiniu.wqf31415.xyz/icon-dianyu.png" alt="这是引用模式的" title="引用模式-灯泡"/>
</p>
```

，效果：
![这是个灯泡](http://blog-images.qiniu.wqf31415.xyz/icon-dianyu.png "灯泡")
![这是引用模式的][dengpao]

[dengpao]: http://blog-images.qiniu.wqf31415.xyz/icon-dianyu.png "引用模式-灯泡"

#### 转义字符
在文章中需要显示 markdown 语法关键字符时，为了避免被编译成 HTML 标签，可以使用反斜杠 `\` 来添加转义字符，在输入成 HTML 时显示原字符。
可使用的转义字符:

|字符|名称|转义写法|
|:----:|:----:|:----:|
|\\|反斜杠|\\\\|
|\`|反引号|\\\`|
|\*|星号|\\\*|
|\#|井号|\\\#|
|\_|下划线|\\\_|
|\{\}|大括号|\\\{\\\}|
|\[\]|中括号|\\\[\\\]|
|\(\)|小括号|\\\(\\\)|
|\+|加号|\\\+|
|\-|减号|\\\-|
|\.|点|\\\.|
|\!|叹号|\\\!|

### 编辑器
markdown 是纯文本的，所以原则上只要是文本编辑器都可以写，用系统自带的文本编辑器就可以，但使用一些工具，或在文本编辑器中添加相应插件，可以让 markdown 书写更加顺畅，更能体现 markdown 易读易写的哲学。

#### Typora
> 官网: <https://typora.io/>

![](http://blog-images.qiniu.wqf31415.xyz/typora.png "Typora")

windows 平台中五星推荐的编辑器。
- 支持 markdown基础语法、markdown math、流程图、html 行内样式。
- 支持代码高亮。
- 所见即所得: 在 Typora 中，取消了预览窗口，读和写在一个窗口中，写出来马上就能看到效果。写作时也可以手动切换到代码编辑模式，对文章进行调整。
- 快捷操作: 右键点击快速插入图片、表格、段落，快速添加文字样式，如加粗、倾斜、超链接等。
- 提供多种显示主题，如 Github、Night等。
- 生成文章目录大纲，快速跳转。
- 多平台，支持 mac OS、Windows、Linux。
- 更新活跃，Typora 更新频率很高，差不多每半个月就会有新版本。

#### Mou
> 官网：<http://25.io/mou/>

![](http://blog-images.qiniu.wqf31415.xyz/mou.png "Mou")

仅支持 Mac OS
- 界面美观
- 支持实时预览(左边编辑、右边预览)，同步滚动
- 自动保存
- 支持多种显示主题，可以自定义主题和 css 样式，或在 github 上下载主题
- 自动补全英文单词
- 字数统计

### 一些技巧

#### 使用 HTML 标签
在 markdown 文档中，可以直接添加行内 html 标签，如 `<del>删除线</del>` 、`<abbr title="Not Only SQL">NoSQL</abbr>` 等，效果：<del>删除线</del> 、 <abbr title="Not Only SQL">NoSQL</abbr> 。

利用这一特性，我们可以还可以在 markdown 文档中嵌入音频、视频等，甚至可以使用 `iframe` 标签嵌入一个 html 页面。

#### Markdown Math 数学公式

#### 流程图

#### 图床
由于在 markdown 中插入的图片时需要指定图片链接，在文章发布在网上时就需要先找地方存起来，将其链接添加到文章中，这个存放图片并提供链接访问的地方就成为图床。

- 七牛云
  [七牛云](https://www.qiniu.com/ ) 免费提供 10G 的存储空间，超出部分最高 0.165元/GB。非常实用，不仅可以存储图片，还可以存储其它文件，如视频、文档等。

- 新浪微博相册
  [新浪微博相册](http://photo.weibo.com/ ) 支持外链，在国内访问速度快，可以用来存储 markdown 需要的图片，支持jpg/gif/png/jpeg格式，单张照片不超过20M。

### 应用场景

- 个人博客
  如 Hexo 博客，就是使用 markdown 来写文章，最终渲染成 html 页面。

- 论坛文章
  如 [CSDN 博客](https://www.csdn.net/ )、[简书](https://www.jianshu.com/ )、[GitBook](https://www.gitbook.com/ ) 等论坛也使用 markdown 来发布文章。

- 笔记文章
  在[印象笔记](https://www.yinxiang.com/ ) 中，现在已经支持创建 markdown 笔记了。

- git 仓库项目描述
  在 [github](https://github.com/ )、[Coding](https://coding.net/ )、[码云](https://gitee.com/ ) 等代码托管平台都支持 markdown 的项目描述文件 `README.md` 。

### 参考资料
- [官网][]
- [维基百科](https://zh.wikipedia.org/wiki/Markdown )
- [使用Markdown输出LaTex数学公式](https://segmentfault.com/a/1190000018527239 )
- [选择适合自己的Markdown编辑器](http://www.cnblogs.com/gibbonnet/p/5373703.html )
- [Markdown——入门指南](https://www.jianshu.com/p/1e402922ee32/ )
- [免费图床：新浪微博相册](https://www.jianshu.com/p/55c42017848f )

