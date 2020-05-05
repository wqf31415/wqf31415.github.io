---
title: 使用 TravisCI 自动部署 hexo 博客
tags:
  - ci
  - travis-ci
  - 持续集成
  - hexo
  - blog
  - 博客
categories:
  - 工具
date: 2020-02-07 13:58:38
---

### 概述

这篇文章介绍了使用 Travis-CI 读取 github 中的项目代码，然后完成自动编译任务，最后将编译后的文件自动推送到指定 git 仓库，实现 hexo 博客的自动部署功能。

### Travis-CI 是什么

![](http://blog-images.qiniu.wqf31415.xyz/travis_ci.jpeg)

> 官网：<https://www.travis-ci.org/> 

Travis-CI 是一个在线的开源项目的持续集成构建工具，可以自动完成项目构建、测试、部署。支持多种主流的编程语言，如 C、C++、Java、Android、Python、PHP等，支持多种平台编译环境，如 Ubuntu、macOS、Windows，支持 docker ，使用 `yml` 配置任务，非常简洁。



<!-- more -->



### Hexo 是什么

> 官网：<https://hexo.io/zh-cn/> 

Hexo 是一个开源的，高效、简洁的静态博客工具，基于 `nodejs` 开发，使用 markdown 编辑博客内容，拥有大量精美的主题和实用插件，用起来非常高效而又省心。

### 博客项目

首先需要搭建一个 hexo 项目，然后把项目的源码上传到 github，并开启 github 的 page 服务，从而实现 hexo 静态博客的访问。

详情请参考：<a href="/2017/02/22/教你从0开始搭建个人博客/" target="_blank">教你从0开始搭建个人博客</a> 。

> 建议使用同一个 git 仓库存放 hexo 博客的源代码和部署文件，只需要在 git 仓库中创建两个分支，`master` 分支用于存放部署的文件，`source` 分支存放博客源文件。
>
> 可参考：<a href="/2017/02/11/如何维护hexo静态博客/" target="_blank">如何维护hexo静态博客</a> 
>
> <span style="background:#fffa55">注意，travis CI 对开源的仓库是免费的，这里需要将存放 hexo 博客源码的仓库设置为公开的。

### Travis 自动部署配置

#### github 添加 Travis CI 及 Travis CI 

- **搜索 Travis 扩展** 登录 github ，进入 `Marketplace` ，搜索 `travis` ，或直接进入 <https://github.com/marketplace/travis-ci> 。

  ![](http://blog-images.qiniu.wqf31415.xyz/github_extend_travis.png)

- **选择开源版本** 将 travis-ci 扩展添加到 github，这里需要选择 `Open Source` 免费版本，点击 `Install it for free` 按钮。

  ![](http://blog-images.qiniu.wqf31415.xyz/github_install_travis_ci.png)

- **确认订单并安装** Travis CI 扩展。

  ![](http://blog-images.qiniu.wqf31415.xyz/github_install_travis_ci_complete.png)

- **仓库访问权限** 选择 Travis-CI 可用的仓库，默认是所有仓库，可以根据需要选择指定的仓库，选好之后点击 `Install` ，会出现密码确认界面，输入 github 密码确认安装。

  > 如果后续需要修改仓库访问权限：登录你的 github 账户，在 `Applications settings` 中配置 Travis CI 权限，使其能够访问你的仓库。

  ![](http://blog-images.qiniu.wqf31415.xyz/github_install_travis_ci_select_repo.png)

- **登录 Travis CI** 确认安装后，会自动跳转到 Travis CI 的页面，我们可以直接使用 github 账户授权登录。如果没有自动跳转，可以手动打开 <https://travis-ci.com/> 。

  ![travis-ci sign in](http://blog-images.qiniu.wqf31415.xyz/travis_ci_sign_in.png)

- 使用 github 账户登录 Travis CI 后，可以看到自己 github 的仓库。

  

#### 创建 github 个人访问令牌

我们需要创建一个访问令牌，供 Travis CI 访问我们的 github 仓库，需要能够仓库的读与写权限，这个令牌等会配置 Travis CI 时需要用到。

- 另开一个页面登录 github ，进入配置页面（快捷链接：<https://github.com/settings/profile>），进入开发者选项配置。

  ![](http://blog-images.qiniu.wqf31415.xyz/github_developer_settings.png)

- 个人访问令牌配置（快捷链接：<https://github.com/settings/tokens>），点击新建令牌。

  ![](http://blog-images.qiniu.wqf31415.xyz/github_personal_access_tokens.png)

- 填写令牌名称，勾选权限，这里主要需要读和写的权限，然后点击最下方的创建按钮即可。

  ![](http://blog-images.qiniu.wqf31415.xyz/github_travis_ci_token.png)

- 创建好令牌后，一定要把令牌复制并保存下来，因为离开这个页面后，将无法再查看这个令牌的内容。

  ![](http://blog-images.qiniu.wqf31415.xyz/github_travis_ci_token_content.png)

  

#### Travis CI 配置

给 Travis CI 添加 github 访问令牌。

- 回到 Travis CI 页面，选择需要存放博客源码的仓库，进入仓库配置页面。

  ![](http://blog-images.qiniu.wqf31415.xyz/travis_ci_settings.png)

- 将 github 访问令牌添加到环境变量，在 Travis 配置页面下拉，找到 `Environment Variables` 配置，添加一个名为 `GH_TOKEN` 的记录(名称可以自己定义)，值(value) 为上一步获得的 访问令牌，分支选择所有，**一定要确认 `DISPLAY VALUE INBUILD LOG` 选项<span style="color:red">未勾选</span>，防止访问令牌泄露**，点击 `Add` 添加记录。

  ![](http://blog-images.qiniu.wqf31415.xyz/travis_ci_add_github_token.png)

  

#### Travis CI 自动部署配置 `.travis.yml`

在博客源码根目录下创建一个文件 `.travis.yml` ，内容如下：

```yml
sudo: false # 是否需要管理员权限，我们不需要
language: node_js # 语言环境
node_js:
  - 10 # 使用 nodejs v10 LTS
cache: npm
branches: # github 分支配置
  only:
    - source # 只有 source 分支有推送时才触发构建
script: # 要执行的命令
  - git clone https://github.com/theme-next/hexo-theme-next themes/next ## 下载博客主题
  - hexo generate # hexo 生成静态文件
deploy:
  provider: pages
  skip-cleanup: true
  target_branch: master # 部署的目标分支，默认为 gh_pages 分支
  github-token: $GH_TOKEN # 在 Travis CI 环境变量中添加的 github 访问令牌名
  keep-history: true
  on:
    branch: source # 源码分支
  local-dir: public # 要部署内容的目录
notifications: # 通知
  email: true # 使用 email 通知自动部署结果
```

> 上面配置将会在 github 仓库的 `source` 分支有新内容推送上去时，触发 Travis CI 的自动部署任务，将自动生成 hexo 博客内容，然后将生成的内容推送到 github 仓库的 `master` 分支上。部署任务做完后将发送邮件通知。

注意：我的博客使用了 next 主题，所以在执行的命令中，需要添加下载 next 主题内容的命令



#### 测试效果

将 `.travis.yml` 文件推送到 github 仓库中，将自动触发部署任务，这时候进入 Travis CI 网站 <https://travis-ci.com/>，可以看到自动构建部署的输出日志。

![](http://blog-images.qiniu.wqf31415.xyz/travis_ci_build_log.png)

等待 Travis CI 自动构建部署完成后，可以登录你的 github pages 地址看看是不是部署成功了。



### 总结

使用 Travis CI 自动部署 hexo 真的非常方便，以后写完博客之后只需要推送到 github 就行了，不用手动构建、部署了。需要注意的是，如果你的博客里用了一些自定义的东西的时候，在 Travis CI 的配置文件 `.travis.yml` 中要修改或添加相应的配置项，详情可以参考 Travis CI 的官方文档。Travis CI 有一个问题是，在国内的访问速度可能会有点慢，有时根本打不开，但是只需要你第一次配置好了，后续就算 Travis CI 网站打不开也不影响！



