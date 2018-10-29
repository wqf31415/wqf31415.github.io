---
title: 小白都能学会的Git操作
date: 2017-02-23 09:24:09
tags:
- git
categories:
- 技术

---

摘要：Git是现今世界上最先进的分布式版本控制工具。这篇文章主要介绍了什么是Git，如何安装以及简单的使用Git。

![git](http://blog-images.qiniu.wqf31415.xyz/image/git/git_logo.png "git")

> 官方说明文档：https://git-scm.com/book/zh/v2

### 1 什么是git？

一句话：**git是现今世界上最先进的分布式版本控制工具** 。

缩句：**git是分布式版本控制工具** 。

再缩：**git是版本控制工具** 。

<!-- more -->

![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_workflow.png "git 工作流")

这里面就有几个概念要解释一下了，**“最先进”**  这个是毫无疑问的，全球最知名的互联网公司包括Google、Facebook、微软、twitter等等都在使用git。
**“版本控制工具”** 英文名Concurrent Version System （CVS）,提供完备的版本管理功能，用于存储、追踪目录（文件夹）和文件的修改历史，是软件开发者的必备工具，是软件公司的基础设施 。简单来说就是用来记录文件的修改历史的，让你可以回到以前的状态，犹如word里面的Ctrl + Z 撤销功能，软件记录下你前面的操作，如果不小心失误了，就可以撤销操作返回到上一个状态。
**“分布式”** 就是git仓库信息是分布在每个克隆仓库中的，就是说一旦你克隆了这个仓库到本地，那你本地的仓库里就有仓库的所有“历史记录”。分布式之前的模式是集中式，代表是SVN（Subversion），存在一个中央服务器，每次编辑后的修改被记录到中央仓库。

---------------------------------------

### 2 安装git

<div><div id="nav"><a href="javascript:void(0)" style="display: inline-block;width: 80px; text-align: center;line-height: 1.5em;">Windows</a><a href="javascript:void(0)" style="display: inline-block;width: 80px; text-align: center;line-height: 1.5em;">Linux</a><a href="javascript:void(0)" style="display: inline-block;width: 80px; text-align: center;line-height: 1.5em;">Mac OS</a></div><div id="option" style="width: 100%;border: 2px solid #ccc;padding: 5px;margin-top: 2px;border-radius: 5px;"><div id="Windows">下载exe安装程序，安装时全都选默认的，一直点下一步就OK了！</div><div id="Linux">运行指令<b>sudo apt-get install git</b></div><div id="Mac OS">从AppStore安装Xcode，Xcode集成了Git，不过默认没有安装，你需要运行Xcode，选择菜单“Xcode”->“Preferences”，在弹出窗口中找到“Downloads”，选择“Command Line Tools”，点“Install”就可以完成安装了。</div></div></div>
<script>var oUl=document.getElementById('nav');var oDiv=document.getElementById('option');var oLis=oUl.getElementsByTagName('a');var oOptDivs=oDiv.getElementsByTagName('div');for(var i=0;i<oLis.length;i++){hideDiv();document.getElementById('Windows').style.display='block';oLis[i].style.display='inlineblock';oLis[i].onclick=function(){hideDiv();showDiv(this.innerHTML);}}function showDiv(id) {var odiv=document.getElementById(id);odiv.style.display='block';}function hideDiv() {for (var i=0;i<oOptDivs.length;i++){oOptDivs[i].style.display='none';}}</script>

---------------------------------------

### 3 开始使用git

我们这里以windows操作系统为例，其它系统操作大同小异。

#### 基本配置

在windows安装git的同时会默认安装 git bash 插件，我们在桌面上右击鼠标就能看到 `git bsah here` 选项，点击后将在桌面打开 git bash 命令行工具：

![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_gitBash_0.png "git bash here")

git bash 命令行如下图所示：
![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_gitBash_cli.png "Git Bash 命令行")

我们可以输入 `git --version` 来查看git版本
![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_gitBash_gitVersion.png "查看git版本")

在第一次使用git时要设置用户名、邮箱信息，在以后的每一次提交修改时都会用到这些信息
```
git config --global user.name "wqf31415"
git config --global user.email wqf31415@hotmail.com
```
第一句指令是设置用户名，用英文的双引号括起来，第二句是设置邮箱

设置好之后我们可以在 git bash 命令行工具中输入 `git config --list` 查看设置结果
![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_config_list.png "查看git设置")

也可以输入 `git config user.name` 单独查看用户名
![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_look_username.png "查看git用户名")

#### 初始化git仓库

`git init` 指令用于初始化一个仓库
我们可以在一个空的文件夹里初始化仓库，也可以在一个用文件的文件夹里初始化，只需要我们在要初始化的文件空白区域右击打开 git bash 工具，执行 `git init` 命令即可，执行完成后将会在该目录下创建一个名叫 `.git` 的隐藏文件夹，这里面存放的是git仓库的所有必须文件。
 ![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_init.png "初始化git仓库")

#### 查看仓库状态
因为在用 git bash 向 git 仓库中添加文件时，添加成功时没有任何信息显示，为了查看我们是否添加成功，我们需要使用 `git status` 指令来查看git仓库状态：
![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_status_1.png "git 仓库状态") 
根据输出的结果，我们可以看到仓库中没有跟踪的文件，现在所有的文件和目录都没有跟踪。

 #### 添加文件

在初始化仓库后，仓库中的文件其实还没有被跟踪，就是git现在还不知道需要记录版本变化的文件，我们要把需要跟踪的文件添加进去：

 `git add 1.txt` 将 1.txt 文件添加到仓库，添加时要输入文件名和扩展名，windows 中 git bash 默认是不支持输入中文的，所以用这种方式不能添加以中文命名的文件，可以使用下面的方式将全部文件都添加进仓库，避免了输入文件名；
 ![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_add_single_file.png "添加单个文件")
 添加文件后我们再查看仓库状态，发现 1.txt 文件已经不在未跟踪文件列表里了，而是在 **changes to be committed** 下，意思是已经跟踪的文件被改变了，可以提交了。

 `git add *.html`将所有 html 文件添加到仓库，*为通配符，用这种方式可以向git仓库添加一个类型的文件；
 ![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_add_one_type_files.png "添加一个类型的文件")

 `git add .` 直接将目录下所有文件添加到git仓库；
 ![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_add_all_files.png "添加所有文件")

 #### 删除已添加的文件

 如果不小心把不需要跟踪的文件（如1.txt）添加到了仓库，可以使用 `git rm --cached 1.txt` 将文件从已添加文件中删除：
 ![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_rm_single_file.png "删除已添加文件")
 我们看到 1.txt 又回到了未跟踪文件列表。

 #### 提交文件

 在用 `git add .` 指令添加所有文件后，我们就需要提交修改过的文件到仓库：
 `git commit -m 'change description'` 引号括起来的是对修改内容的描述；
 ![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_commit_m.png "提交修改")

 此外，也可以用 `git commit` 命令来提交，提交后还会启动编辑模式让你输入修改描述：
 （我们将 1.txt 添加进来并提交）
 ![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_commit.png "输入修改内容描述")
 在输入完成后，按 **ESC** 键退出输入状态，然后 **Shift + ;**，再输入 **q!** 或 **wq!** （不保存改动，wq!是保存文件的写入修改）退出。

 ![](http://blog-images.qiniu.wqf31415.xyz/image/git/git_commit_2.png "提交1.txt")
 在所有文件添加完成后，我们查看仓库状态发现显示 **On branch master nothing to commit, working tree clean** ，就是说所有的文件修改都提交了，工作树很干净了。

 #### 连接远程git仓库

 现在我们本地git仓库已经建立好了，已经可以管理本地文件了，但这样是不够的，git最大的功能还在于多人协作，所以需要有一个远端仓库服务器，这样在不同电脑终端都可以进行工作了。

 现在最简单的就是在 git 托管平台建一个仓库，把本地仓库托管到git平台，最常用的有 **github** 、 **coding** 、 **oschina** ，这里以国内的 coding 为例。

  [https://coding.net/](https://coding.net/) 注册、登陆后新建一个项目 **git-test** ，不要勾选创建 `README.md` 选项，项目创建好后将仓库的地址复制下来，我的仓库地址是 **https://git.coding.net/wqf31415/git-test.git** 。

  然后回到本地 git-test 目录下打开 git bash ，运行 `git remote add origin https://git.coding.net/wqf31415/git-test.git` ，后面是远端仓库的地址。

  最后用 `git push -u origin master` 将本地仓库文件推送到远端仓库，第一次要加 `-u` ，以后就直接运行 `git push origin master` 。

  #### 将远端仓库克隆到本地

  运行 `git clone https://git.coding.net/wqf31415/git-test.git` 将远端仓库克隆到本地，后面 url 是git仓库地址。

  然后就可以在本地愉快的写代码了。

  在本地修改后，依次运行下列代码将修改提交到远端仓库：
  ```
    git add .
    git commit -m 'change description'
    git push origin master
  ```

-----------------

  ### 总结

  git 是一个很有用的工具，其用途不仅仅在于程序员控制代码版本，也可以用于多人协作创作小说、剧本等。只要是文本形式的文件，都可以很好的使用 git 来做版本控制，但对于其它非文本文件，就不是很好控制了。

本篇文章主要记述了 git 的安装和最基本使用，涉及到的 git 指令如下：

`git --version`  查看 git 版本

`git config --global user.name "username" `  设置全局的 git 用户，加 `--global` 将设置为全局配置

`git config --global user.email user@xxx.xx`  设置全局的 git 邮箱

`git config --list`  查看 git 配置

`git config user.name`  查看用户名

`git init`  初始化 git 仓库

`git status`  查看仓库状态

`git add 1.txt`  添加 1.txt 文件到仓库，让仓库跟踪该文件

`git add *.html`  添加所有 .html 文件到仓库

`git add .`  添加所有文件到仓库

`git rm cached 1.txt`  从已添加文件中删除 1.txt 文件

`git commit -m 'some information'`  提交文件，并添加一些描述信息

`git commit`  提交文件，打开 vim 窗口输入描述信息

`git remote add origin https://git.coding.net/wqf31415/git-test.git`  为本地仓库添加远端仓库地址

`git push -u origin master`  将本地仓库推送到远端仓库的 master 分支，第一次要加 `-u` ，以后不加

`git clone https://git.coding.net/wqf31415/git-test.git`  克隆远端仓库到本地

`git pull origin master`  拉取远端仓库的 master 分支，并自动合并到当前分支



#### git 保存密码命令

`git config --global credential.helper store` 长期存储 git 服务器的密码

`git config --global credential.helper cache` 设置 git 保存密码，有效期 15 分钟

`git config credential.helper 'cache --timeout=3600'` 设置 git 保存密码，有效期 3600 秒

