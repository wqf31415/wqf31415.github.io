---
title: 如何维护hexo静态博客
date: 2017-02-11 12:25:47
tags: 
- hexo
- git
categories: 
- 技术

---



### 如何在多个pc终端更新自己的hexo博客？

​        在最开始的时候，我的博客是在公司电脑生成的，在回家后也想更新博客，于是就遇到了一些麻烦，该怎么把资源文件同步到其他电脑上呢？参考了简书上@长仙人 的文章[多台电脑使用Hexo](http://www.jianshu.com/p/4bcf2848b3fc '多台电脑使用Hexo') 在github的仓库里建了两个分枝，一个用了放发布的博客文件，一个用了放源文件，完美解决！

---

### 在不同电脑上更新博客

1. 首先要安装好[nodejs](https://nodejs.org/en/ 'nodejs')和[git](https://git-scm.com/ 'git') 

2. 克隆项目到本地

   ``````
   git clone https://github.com/wqf31415/wqf31415.github.io.git
   ``````

3. 进入文件目录并切换分支

   `cd wqf31415.github.io`

   `git checkout source`

4. 运行npm安装hexo

   `npm install hexo-deployer-git --save`

5. 用hexo在本地试运行

   `hexo g`  生成hexo静态文件

   `hexo s`  在本地运行hexo服务

   用浏览器访问 [http://localhost:4000](http://localhost:4000 '本地hexo') 预览

   > 在本地预览时，可能会报错 WARN No layout: index.html 错误。
   >
   > 原因是博客用的是[next主题](http://theme-next.iissnan.com/getting-started.html 'next官网') ，在克隆source分支到本地后，发现next文件夹是空的，需要重新安装NexT：
   >
   >  `git clone https://github.com/iissnan/hexo-theme-next themes/next` 
   >
   > 然后重新部署：
   >
   > `hexo clean` 
   >
   > `hexo g`
   >
   > `hexo d` 部署到github   

6. 在本地正确运行后就可以对博客进行更新、维护和写作了

---

### 写新的文章

1. 运行hexo新建命令：

   `hexo new '文章标题'`

   在命令运行成功后，将在`source/_posts` 目录下生成 `文章标题.md` ，用markdown编辑器编写即可；

2. 文章撰写、修改完成后，需要运行hexo生成博客静态文件：

   `hexo clean` 清除缓存

   `hexo g` 生成博客静态文件

   `hexo s` 开启hexo服务，用于本地预览

   `hexo d` 部署博客到git平台（PS：一定要在本地预览没问题再部署）

3. 将本地博客源文件同步到git仓库，用于多电脑博客管理：

   `git add .` 把本地修改提交到缓存

   `git commit -m '修改描述'` 提交修改

   `git push origin source` 把本地仓库推送到远端仓库


---

### 从github仓库拉取更新过的源文件

​        在一台电脑上更新过博客内容后，用上述的方法将源文件推送到github仓库，在其他电脑上再更新时就要先从仓库拉取最新的源文件，然后再进行操作，具体操作步骤如下：

1. 进入到博客源文件所在目录，`H:\GitHub\wqf31415.github.io` ，在空白区域右击选择`Git Bash Here` 启动git bash命令行；

2. 查看本地分支：

   `git branch` 

   如果不是source分支就需要切换到source分支：

   `git checkout source`

3. 拉取最新文件内容：

   `git pull origin source`

​        这样就完成了从远端仓库拉取源文件，可以在本地进行博客更新了！---这样就完成了从远端仓库拉取源文件，可以在本地进行博客更新了！

---




