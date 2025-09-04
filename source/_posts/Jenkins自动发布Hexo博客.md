---
title: Jenkins自动发布Hexo博客
tags:
  - jenkins
  - hexo
  - docker
  - 服务器
  - nginx
  - github
categories:
  - 工具
date: 2025-09-04 22:26:55
---

### 概述

这篇文章介绍如何在服务器上使用docker搭建jenkins，并使用jenkins自动从github仓库拉取自己 Hexo 博客的源代码，完成项目构建与部署，使用nginx对外提供博客访问服务。

### 认识 jenkins

Jenkins 是一个开源的自动化构建、部署工具，支持数百款插件扩展，支持各种自动化业务场景。Jenkins使用 java 开发，支持使用jar包部署或docker部署。

> Jenkins 官网：<https://www.jenkins.io/> 


<!-- more -->

### 核心流程与概念

1、Hexo 是静态博客，源代码编译后会生成静态页面和前端资源，可使用 nginx 部署，提供web页面访问。
2、使用服务器系统自带的软件管理工具可以一键安装 nginx 服务，修改少量配置，即可完成前端项目部署。
3、使用 docker 可以一键部署 Jenkins，部署时将博客部署的路径挂载到Jenkins容器中，就可以让Jenkins构建项目完成后直接把前端资源拷贝到部署目录，即可完成博客新内容的发布。
4、在Jenkins中创建自动构建任务，支持在GitHub提交代码时触发构建和定时每天完成构建。

### 搭建nginx

使用 CentOS 的包管理工具 yum 安装 nginx：

```bash
# （可选但建议做）更新资源
yum update

# 安装 nginx
yum install nginx -y
```

安装完成后的 nginx 的主要文件与目录：

- 可执行程序：/usr/sbin/nginx
- 配置文件目录：/etc/nginx/
- web页面默认目录：/usr/share/nginx/
- 日志目录：/var/log/nginx/

修改 nginx 配置文件 **/etc/nginx/conf.d/default.conf** ，关键内容如下。

> 配置说明：将从 `www.wqf31415.xyz` 来的请求定位到本地 `/usr/share/nginx/blog` 目录中，首页文件配置为 `index.html`

```
server {
    server_name  www.wqf31415.xyz;
    location / {
        root /usr/share/nginx/blog;
        index index.html;
    }
}
```

创建部署博客静态资源的目录 `/usr/share/nginx/blog`，将编译好的博客前端文件放到目录中。

> 后面需要把这个目录挂载到 Jenkins 容器中，方便编译完成后直接发布。

```bash 
mkdir -p /usr/share/nginx/blog
```

修改好nginx配置并将博客静态文件放到指定目录后，使用 nginx 命令验证配置是否正确，重新加载配置。浏览器打开博客域名，确认是否可以访问。

```bash
# 验证配置是否正确
nginx -t

# 重新加载配置
nginx -s reload
```

### 搭建Jenkins

编辑 docker-compose 配置文件 `docker-compose-jenkins.yml` ，内容如下：

```yaml
version: '3.0'  # 使用 Docker Compose 的 3.0 版本语法
services:
  jenkins:
    image: jenkins/jenkins:2.504.1-lts-jdk17  # 使用 Jenkins 的长期支持 (LTS) 版本镜像
    container_name: jenkins  # 将容器命名为 jenkins
    ports:
      - "8081:8080"   # 将容器的 8080 端口映射到主机的 8081 端口，用于 Web 访问
      - "50000:50000" # 映射 50000 端口，用于 Jenkins 代理（agent）连接
    volumes:
      - /root/docker/data/jenkins:/var/jenkins_home  # 挂载 Jenkins 数据卷，持久化配置和数据
      - /var/run/docker.sock:/var/run/docker.sock  # （可选）允许 Jenkins 容器内使用 Docker
      - /usr/share/nginx/blog:/mnt/blog # 用于发布blog内容
      - /etc/localtime:/etc/localtime:ro  # 让容器使用与主机相同的时区
    environment:
      - TZ=Asia/Shanghai  # 设置容器的时区为亚洲/上海（请根据你的实际位置调整）
      - JAVA_OPTS=-Duser.timezone=Asia/Shanghai  # 设置 Java 虚拟机时区参数
    user: root  # 以 root 用户身份运行容器（注意潜在安全风险，仅用于示例）
    restart: always  # 设置容器始终自动重启，除非手动停止
    privileged: true  # 授予容器特权模式（有时为挂载 Docker 所需，但有安全风险，请谨慎使用）
```

使用 docker-compose 启动 Jenkins 容器:

```bash
docker-compose -f docker-compose-jenkins.yml up -d
```
> 部署完需要从 Jenkins 日志中获取管理员密码，首次登陆Jenkins需要使用这个密码登录，登录成功后可创建其他管理员账号。

### Jenkins配置

#### 编译环境配置

用于 Hexo 博客项目需要使用 Node 环境进行编译，所以要先给Jenkins安装 `NodeJS Plugin` 。

进入 Jenkins 首页点击 **Manage Jenkins** - **插件管理** ，在可用插件中搜索 `nodejs` ，勾选 `NodeJS Plugin` ，点击安装，等待插件安装完成。

安装完成后可以在插件管理的 **Installed plugins** 中找到，确保 `NodeJS Plugin` 插件是启用状态。

![](/iamges/poost/jenkins/jenkins_installed_plugins.png) 

进入 **Manage Jenkins** - **Tools** 页面，找到 `NodeJS 安装` ，点击 **新增NodeJS**，填写别名 `NodeJs14`，版本选 14 版本中最新的一个，保存。 

![](/iamges/poost/jenkins/jenkins_add_nodejs_env.png) 

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

#### 构建触发配置

**定时触发**：在构建配置的触发器 Triggers 中选择定时构建，日程表中填写如下内容。

```bash
# 指定时区
TZ=Asia/Shanghai
# 每天1点的某分钟触发
H 1 * * *
```

**GitHub事件触发**：勾选 **GitHub hook trigger for GITScm polling** 选项。

在GitHub的博客代码项目中，进入 **Setting** - **Webhooks** ，点击 **Add webhook** 添加，关键配置如下:

- Payload URL：http://服务器ip或域名:8081/github-webhook/ ，注意这里是 http
- Content type：选 `application/json`
- SSL verification：保持默认的 `Enable SSL verification`
- Which events would you like to trigger this webhook?：选择 `Just the push event.` 只发送推代码的事件

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
git clone git@github.com:next-theme/hexo-theme-next.git themes/next

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

# 备份原来的内容，更换成新的内容
tar -zcvf blog_bak.tar.gz /mnt/blog/
rm -rf /mnt/blog/*
cp -r public/* /mnt/blog/
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

### 总结

这篇文章内容比较简单，但其中涉及到多个工具软件，包括nginx的部署与配置，docker的使用，Jenkins的使用与配置，GitHub的配置。

扩展玩法：使用 **Certbot** 自动生成和配置 https 证书。

