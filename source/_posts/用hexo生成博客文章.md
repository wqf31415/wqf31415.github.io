---
title: 用hexo生成博客文章
date: 2017-01-25 12:38:15
tags: 
- hexo
- blog
categories: 
- 技术
---

在搭建好静态博客后，最重要的一件事就是往里面填东西了，那么怎么才能生成一篇新的博文呢？该如何编辑博文呢？又该怎么编辑博客生成模板呢？请看下文！

这是一篇用Hexo生成的文章

`hexo new "Hello Hexo"`

`hexo generate`

用以上两个命令生成的！

> <https://github.com/hexojs/hexo>

<!-- more -->

自动生成的文章放在 `source/_posts` 目录下，可以用markdown编辑器修改内容。



修改好内容后运行下面的指令，部署到博客中：

`hexo clean`

`hexo g`

`hexo s`

这样就可以在浏览器里看到了

