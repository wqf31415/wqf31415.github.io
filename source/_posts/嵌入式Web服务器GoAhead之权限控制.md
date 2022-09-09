---
title: 嵌入式Web服务器GoAhead之权限控制
tags:
  - c
  - 嵌入式
  - web
  - 服务器
categories:
  - c
date: 2022-06-27 20:57:38
---

### 概述

在嵌入式 web 服务中引入访问权限控制对于保证设备安全非常重要，这篇文章介绍了嵌入式服务器 GoAhead 中权限相关的功能，包括用户信息配置、uri 路由权限配置，介绍了项目中的权限配置流程。

> 本文中示例基于 GoAhead 5.2.0

![](http://blog-images.qiniu.wqf31415.xyz/padlock-428549_1280.jpg)



### GoAhead 权限

> 官方文档: <https://www.embedthis.com/goahead/doc/users/authentication.html> 

GoAhead 提供了三种权限架构：

- 基于Web表单（Web Form）的身份验证：使用 HTML web 表单让用户输入用户名、密码，以 POST 方法请求身份验证。
- 基本（Basic）认证：基于浏览器弹出框捕获用户名和密码，然后简单编码后传输，这种方式与明文方式并无太大差异。
- 摘要式（Digest）身份验证：对基本认证方案进行 MD5 处理后传输凭据。

<!-- more -->



### 三种认证方式的特点

Basic 和 Digest 身份验证方案是 HTML/1.1 RFC2616 规范定义的 HTTP 协议机制，属于协议级别，提供了更低级别的功能和灵活性。这种方式的缺点是每次访问受保护内容时都要弹出对话框让用户输入凭据，每次请求都需要传输凭据，而仅对凭据进行弱加密处理，有安全隐患，建议使用 SSL 提高安全性。而且这种方式没有登出机制。

Web表单的身份验证方案（推荐使用）使用标准网页表单让用户输入用户名、密码，数据使用 POST 方式提交，GoAhead 验证身份成功后将创建会话并将 cookie 返回用户的浏览器。用户后续请求将自动携带 cookie 完成身份认证。这种方式是以明文方式传输用户信息，因此建议使用 SSL 连接保证数据安全。Web表单身份认证方案的优势是登录一次后，后续身份认证自动完成，而且具有登出功能。缺点是登录时用户信息是明文传输的。



### Web表单方式实现权限控制

#### 用户信息

GoAhead 实现了基于用户角色的访问权限控制，用户、角色与能力信息在 `auth.txt` 文件中配置。

在 `auth.txt` 文件中填写用户信息时，需要填写加密后的密码，可以用编译结果目录（我的是 `build/linux-x64-default/bin/`）中的 `gopass` 程序来生成，生成命令如下：

```bash
./gopass --cipher md5 --password adminpwd example.com admin manager
```

> 说明：
>
> `./gopass` : 调用 gopass 工具
>
> `--cipher md5` : 密码加密算法，make 项目时默认使用 MD5 加密，可选项还有 `blowfish` 。使用摘要式身份认证时必须使用 MD5，使用 web表单的身份验证方案时，建议使用 Blowfish
>
> `--password adminpwd` : 要加密的密码内容，这里的密码内容为 `adminpwd` ，如果没有指定这个参数，执行命令后将提示输入密码
>
> `example.com` : 域名（realm），使用 Basic 或 Digest 身份认证时将显示在弹出的对话框顶部，使用 Web 表单身份认证时，将作为盐对密码进行加密。默认值为 `example.com` ，在使用 make 编译 GoAhead 项目时，可使用 `ME_GOAHEAD_REALM` 参数设置域名值。
>
> `admin` : 用户名
>
> `manager` : 用户拥有的角色

以上命令执行后将会在控制台输出生成的加密密码，如 `0068b2cb850231c2706858bde45d3d01` ，将这个内容复制下来，需要写入到 `auth.txt` 文件中。

修改 `auth.txt` 文件，添加内容：

```
# Role
role name=manager abilities=view,edit,delete

# User
user name=admin password=0068b2cb850231c2706858bde45d3d01 roles=manager
```

以上内容定义了一个名为 `manager` 的角色，这个角色拥有的权限有：`view`、`edit`、`delete` ，然后定义了一个名为 `admin` 的用户，密码为上一步上次的密文 `0068b2cb850231c2706858bde45d3d01`，密码明文为 `adminpwd` ，此用户拥有的角色是 `manager` 。

> 定义角色时，多个权限以逗号 `,` 分隔，可以写其他角色名以包含其拥有的权限，如：
>
> ```
> # Role
> role name=user abilities=view
> role name=manager abilities=user,edit,delete
> ```
>
> 定义用户时，多个角色以逗号 `,` 分隔。



#### 路由配置

在路由配置文件 `route.txt` 文件中给需要权限控制的路由加上权限要求，要求如下：

- 通过 SSL 重定向所有 HTTP 流量的路由
- 未经身份验证时必须可访问的登录页面的路由
- 登录服务的路由
- 注销服务的路由
- 要求对所有 URI 进行身份验证的路由

路由配置如下：

```
# Web Auth
# 1. 将所有 http 协议请求都重定向到 https 协议
route uri=/ protocol=http redirect=*@https handler=redirect
# 2. 开放 /pub/ 目录下的资源访问权限，这里面存的是不需要权限控制的资源，如登录页面 login.html、js、css等
route uri=/pub/
# 3. 添加用户登录请求的路由配置，登录成功时跳转到 /index.html ，登录失败时跳转到登录页面
route uri=/action/login methods=POST handler=action redirect=200@/index.html redirect=401@/pub/login.html
# 4. 登出请求的路由配置，登出后跳转到登录页面
route uri=/action/logout methods=GET|POST handler=action redirect=200@/pub/login.html
# 5. 设置所有请求都需要 from 身份认证，如果认证失败，跳转到登录页面
route uri=/ auth=form handler=continue redirect=401@/pub/login.html

# 以下是其他路由配置
route uri=/action handler=action
route uri=/jst extensions=jst handler=jst

#
#   Catch-all route without authentication for all other URIs
#
route uri=/
```



#### 登录页面

登录页面需要一个表单 `form` ，请求方法是 `post` ，请求地址是 `/action/login` 。表单中需要两个参数：username（用户名）和 password（密码），这两个参数名称不可以修改。

在 web 文档目录下创建目录 `pub` 用来存放公开访问的资源文件。在 pub 目录中创建 `login.html` 文件，内容如下：

```html
<html><head><title>登录</title></head>
<body>
    <p>请登录</p>
    <form name="details" method="post" action="/auth/login" >
        用户名 <input type="text" name="username" value=''><br/>
        密码 <input type="password" name="password" value=''><br/>
        <button type="submit">登录</button>
    </form>
</body>
</html>
```



#### 首页（含登出功能）

首页文件 `index.html` 存放在 web 文件目录根目录中，是受保护的资源，需要登录后才能访问，直接访问将跳转到登录页面。

在首页中添加了登出按钮，index.html 内容如下:

```html
<!DOCTYPE html>
<html lang="en">
<head>
<title>Home Page</title>
</head>

<body>
    <p>Congratulations! The server is up and running.<p/>
    <a href="/action/logout">Logout</a>
</body>
</html>

```



#### 测试

登录 http 协议的网站主页，如 http://ip:80 ，页面将自动跳转到 https 协议的登录页面 https://ip:443/pub/login.html ，在登录页面输入正确的用户名、密码后点击登录按钮，登录成功后跳转到主页，点击主页下方的登出按钮，页面跳转到登录页面。 



### 注意事项

#### 用户登录需要使用 SSL

在 GoAhead 中使用 Web 表单方式进行身份认证时，登录请求必须使用 SSL 连接，否则从服务端返回的 cookie 将无法写入浏览器 Cookie，后续的操作将无法进行。



#### 路由跳转时跳转到 127.0.0.1 导致无法访问

当启动 GoAhead 时不指定绑定的 ip，路由跳转时将自动跳转到 127.0.0.1，可能导致页面无法访问，解决办法时在启动时指定要绑定的 ip 地址，如：

```bash
goahead -v --home /etc/goahead/ /var/www/goahead/ http://192.168.1.170:80 https://192.168.1.170:443
```



### 总结

RBAC（Role-Based Access Control），基于角色的访问控制，是普遍使用的权限控制模型，分为 3 个基础组成部分：用户、角色、权限，这种方式简化了用户和权限的关系，易扩展和维护。GoAhead 项目中实现了这一权限控制模型，因此使用起来非常简单和方便。
