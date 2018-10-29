---
title: 用hexo生成博客文章
date: 2017-01-25 12:38:15
tags: 
- hexo
- blog
categories: 
- 技术
---

在搭建好静态博客站点后，最重要的一件事就是往里面填东西了，那么怎么才能生成一篇新的博文呢？该如何编辑博文呢？又该怎么编辑博客生成模板呢？请看下文！

### 话不多说，直接来创建一篇文章

  - 按照规矩，第一篇文章一定得叫 **Hello Hexo** ，在blog目录下打开命令行，执行下面的命令

  `hexo new "Hello Hexo"` 
  
  ![](http://blog-images.qiniu.wqf31415.xyz/image/hexo_new_article.png "用Hexo生成一篇叫 Hello Hexo 的文章") 
  
  - 执行完这条命令后，我们到 `source/_posts` 目录下看看，就会发现一个名叫 **Hello-Hexo.md** 的文件，.md文件是markdown格式文件的扩展名，实质上也是文本文件，我们可以用熟悉的文本编辑器来编写，最简单的就是直接用记事本打开，只要熟悉markdown语法就可以愉快的进行写作了。
  
  ![](http://blog-images.qiniu.wqf31415.xyz/image/hexo_new_article_file.png "Hexo生成的文章为 .md 格式") 

### 编辑文章
  
  - 既然要用markdown来写文章，那基本的语法还是得要掌握的不是，[http://www.markdown.cn/](http://www.markdown.cn/) 
  
  - 为了协作效率和避免出错，还是在这里推荐几个markdown编辑器，[Markdown——入门指南](http://www.jianshu.com/p/1e402922ee32/) ，我比较喜欢用 **IntelliJ IDEA** 来编辑，idea不仅可以实现编辑实时预览，还可以用来编辑博客中的其它配置文件，非常方便
  
<!-- more -->
  
### 生成网页静态文件

  - 要知道用Hexo生成博客文件后，还要执行下面的命令来生成静态html文件，才能在博客中看到
  
  `hexo generate` 或简写为 `hexo g`
  
  ![](http://blog-images.qiniu.wqf31415.xyz/image/hexo_generate_article.png "已经生成了文章的静态html页面") 


### 在本地预览文章（别自信回头）

  - 建议在写完文章后先在本地预览一下，看看内容、图片以及格式是否是预期效果，如果对自己技术很自信的话也可以跳过这步
  
  - 开启本地Hexo服务
  
  `hexo server` 或简写为 `hexo s`
  
  - 打开 [http://localhost:4000](http://localhost:4000) 进行预览


### 部署文章到git平台

  - 执行下面命令将本地的文章部署到git平台
  
  `hexo deploy` 或简写为 `hexo d`


### 修改文章

  - 找到要修改文章的md文件，用编辑器修改完成后，需要依次执行下列命令来重新发布文章

    - 清除本地缓存： `hexo clean`
    
    - 生成静态文件： `hexo g`
    
    - 本地预览(可选)： `hexo s`
    
    - 发布文章： `hexo d`


### 修改文章模板

  - 我们打开新生成的文章可以发现，默认的模板里只有文章的属性信息，如下图
  
  ![](http://blog-images.qiniu.wqf31415.xyz/image/hexo_new_article_head.png "用Hexo默认文章模板生成的文章") 
  
  - 生成文章用的模板在 **blog/scaffolds** 文件夹里，打开后看到里面有三个文件
  
    - draft.md     为文章草稿的模板
    - page.md      为生成页面的模板
    - post.md      为发布文章的模板
  
  - 根据需要修改对应的模板，我们在这里修改一下 **post.md** ，打开这个文件，由三条横杠包含的是文章的属性信息，默认只有标题、创建时间和标签，我们可以增加自己想要的属性，比如增加文章更新时间和分类
  
  ![](http://blog-images.qiniu.wqf31415.xyz/image/hexo_scaffolds_post.png "在post模板中增加了更新时间和分类属性") 
  
  - 文章的属性有下面几个：
<table><thead><td>属性</td><td>描述</td><td>值</td></thead><tr><td>layout</td><td>Layout</td><td>post或page</td></tr><tr><td>title</td><td>文章标题</td><td>&nbsp;</td></tr><tr><td>date</td><td>创建日期</td><td>文件的创建日期</td></tr><tr><td>updated</td><td>修改日期</td><td>文件的修改日期</td></tr><tr><td>comments</td><td>是否开启评论</td><td>默认true</td></tr><tr><td>tags</td><td>标签</td><td>&nbsp;</td></tr><tr><td>categories</td><td>分类</td><td>&nbsp;</td></tr><tr><td>permalink</td><td>url中的名字</td><td>文件名</td></tr></table>
  
   

### 下台鞠躬！


  ![](http://blog-images.qiniu.wqf31415.xyz/meme/meme_bow_01.jpg) 