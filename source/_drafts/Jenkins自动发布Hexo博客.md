---
title: Jenkins自动发布Hexo博客
tags:
  - jenkins
  - hexo
  - docker
  - 服务器
  - nginx
categories:
  - 工具
date: 2025-09-03 22:30:55
---

### 概述
这篇文章介绍如何在服务器上使用docker搭建jenkins，并使用jenkins自动从github仓库拉取代码，部署到本地，使用nginx提供服务。



### 认识 jenkins



<!-- more -->

### 核心流程与概念

### 搭建nginx

### 搭建Jenkins


### Jenkins配置

#### 编译环境配置

用于 Hexo 博客项目需要使用 Node 环境进行编译，所以要先给Jenkins安装 `NodeJS Plugin` 。

进入 Jenkins 首页点击 **Manage Jenkins** - **插件管理** ，在可用插件中搜索 `nodejs` ，勾选 `NodeJS Plugin` ，点击安装，等待插件安装完成。

安装完成后可以在插件管理的 **Installed plugins** 中找到，确保 `NodeJS Plugin` 插件是启用状态。

进入 **Manage Jenkins** - **Tools** 页面，找到 `NodeJS 安装` ，点击 **新增NodeJS**，填写别名 `NodeJs14`，版本选 14 版本中最新的一个，保存。 


#### 配置ssh凭证

使用 ssh 从 github 拉取代码，但由于是在 docker 中安装的 Jenkins，所以需要在 Jenkins 容器内生成ssh 证书，把公钥配置到 github ，把私钥配置到 Jenkins 中。

进入 Jenkins 容器：

```bash
docker exec -it jenkins /bin/bash
```

生成公钥和私钥，邮箱建议填写自己GitHub的邮箱，一路回车，使用默认位置和空密码生成：

```bash
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
```

查看公钥内容，拷贝输出的内容，登录GitHub，进入 **Settings** -> **SSH and GPG keys** -> **New SSH key**，添加标题并粘贴公钥。

```bash
# 容器内，查看公钥内容
cat ~/.ssh/id_rsa.pub
```

查看私钥内容，拷贝输出内容，登录Jenkins，在 **Manage Jenkins** - **凭据** - **系统** - **全局凭据** 中点击 `Add Credentials` ：
- 类型选择 `SSH Username with private key` 
- 范围选全局
- id可以写 `github-ssh-key`
- Username写自己用户名，我填的是 `wqf31415` 
- Private Key 选 Enter directly，粘贴私钥内容。

```bash
# 查看私钥内容
cat ~/.ssh/id_rsa
```

#### 创建任务与git仓库配置

登录Jenkins页面，点击 **新建Item** ，输入任务名称，如 blog-deploy，选择类型为 **Freestyle project**，保存后进入项目，点击 **配置**。

在 **源码管理** 中选择 `Git` 类型，仓库地址 `Repository URL` 一栏填写项目的 ssh 地址，证书 `Credentials` 选择创建的github ssh 证书，分支填写仓库的源码分支，我这里是 `source`。

#### 定时触发配置

在构建配置的触发器 Triggers 中选择定时构建，日程表中填写如下内容。

```bash
# 指定时区
TZ=Asia/Shanghai
# 每天1点的某分钟触发
H 1 * * *
```

#### 构建配置

在环境Environment配置中勾选 **Delete workspace before build starts**，每次构建开始前删除工作空间，根据需要勾选。

勾选 **Provide Node & npm bin/ folder to PATH**，提供node编译环境，NodeJS Installation 中选择之前创建的 `NodeJs14` 。

在编辑步骤 Build Steps 中添加 `执行 shell`，命令一栏填入以下内容。

```bash
# 打印当前环境和版本信息
node -v
npm -v

# 安装项目依赖（若存在node-sass等需编译的依赖，建议在服务器上提前配置好环境）
npm config set registry https://registry.npmmirror.com
npm install

#下载主题
#当前使用的是 NexT 主题，下载方式，进入项目根目录，执行：
git clone https://github.com/next-theme/hexo-theme-next themes/next

#修改主题配置
#在 themes_config 目录中存了主题相关的配置文件备份，将其中配置文件 _config.yml 复制到 themes/next/ 目录下覆盖文件：
cp themes_config/next/_config.yml themes/next/

#修改翻译错误
#在博客中可能存在一些自定义的菜单项，显示为英文，如需要修改成显示中文，则可以修改 themes/next/languages/zh-CN.yml 中的配置，在 menu 一项中添加需要的字段配置即可。也可以将写好的配置文件复制在 next 主题的目录中，执行命令：
cp themes_config/next/languages/zh-CN.yml themes/next/languages/

#渲染博客内容并开启预览
#先使用命令清除已生成的页面：
node_modules/hexo/bin/hexo clean
#hexo clean

#然后渲染生成页面文件：
node_modules/hexo/bin/hexo generate
#hexo generate

# （可选）将构建产物打包，便于后续传输
tar -zcvf blog_public.tar.gz public/
```

#### 构建后配置

支持在构建完成或失败时发送邮件通知，在构建后操作中添加 **E-mail Notification** ，填写收件人邮箱。

注意需要提前在凭据管理中添加 **Username with password** 类型的凭据，填入邮箱用户名、密码。

在系统配置中填写邮箱服务器信息，**系统管理员邮件地址** 中填写自己的邮箱，在 **Extended E-mail Notification** 中：
- **SMTP server**填写 邮箱服务器地址，我的是阿里云的 `smtp.mxhichina.com`
- **SMTP Port** 填写 465
- 在 **高级** 中，**Credentials** 选上一步添加的邮箱凭据，勾选 **Use SSL**。 

系统配置页面中的 **邮件通知** 按上面的填写。

> 填写配置后，在最下面有个选项可以发送测试邮件验证配置是否正确。

### 参考资料

### 总结



