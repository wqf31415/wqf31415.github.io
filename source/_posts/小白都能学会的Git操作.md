---
title: 小白都能学会的Git操作
date: 2017-02-23 09:24:09
tags:
- git
categories:
- 技术

---

摘要：Git是现今世界上最先进的分布式版本控制工具。这篇文章介绍了什么是Git，如何安装以及使用Git。

![git](http://okbn8yrzu.bkt.clouddn.com/image/git/git_logo.png "git") 

> 官方说明文档：https://git-scm.com/book/zh/v2

### 1 什么是git？

一句话：**git是现今世界上最先进的分布式版本控制工具** 。

缩句：**git是分布式版本控制工具** 。

再缩：**git是版本控制工具** 。

<!-- more -->

![](http://okbn8yrzu.bkt.clouddn.com/image/git/git_workflow.png "git 工作流")

这里面就有几个概念要理解一下了，**“最先进”**  这个是毫无疑问的，全球最知名的互联网公司包括Google、Facebook、微软、twitter等等都在用git。**“版本控制工具”** 英文名Concurrent Version System （CVS）,提供完备的版本管理功能，用于存储、追踪目录（文件夹）和文件的修改历史，是软件开发者的必备工具，是软件公司的基础设施 。简单来说就是用来记录文件的修改历史的，让你可以回到以前的状态，犹如word里面的Ctrl + Z 撤销功能，软件记录下你前面的操作，如果不小心失误了，就可以撤销操作返回到上一个状态。**“分布式”** 就是git仓库信息是分布在每个克隆仓库中的，就是说一旦你克隆了这个仓库到本地，那你本地的仓库里就有仓库的所有“历史记录”。分布式之前的模式是集中式，代表是SVN（Subversion），存在一个中央服务器，每次编辑后的修改被记录到中央仓库。



### 2 安装git

<table><thead><td>windows</td><td>linux</td><td>mac os</td></thead><tr><td>下载exe安装程序运行即可</td><td>运行指令<b>sudo apt-get install git</b></td><td>从AppStore安装Xcode，Xcode集成了Git，不过默认没有安装，你需要运行Xcode，选择菜单“Xcode”->“Preferences”，在弹出窗口中找到“Downloads”，选择“Command Line Tools”，点“Install”就可以完成安装了。</td></tr></table>

### 3 开始使用git

