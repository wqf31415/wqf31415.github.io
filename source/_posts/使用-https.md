---
title: 使用 https
tags:
  - 网络
  - 开发
  - 服务器
categories:
  - 技术
date: 2020-09-18 14:04:38
---

### 概述

这篇文章介绍了 https 的用途、原理以及在实际项目中的部署使用。

![](https://blog-images.qiniu.wqf31415.xyz/https.jpg)

### 什么是 HTTPS

超文本传输安全协议（**H**yper**T**ext **T**ransfer **P**rotocol **S**ecure ，缩写：HTTPS）是一种通过计算机网络进行安全通信的传输协议，HTTPS 使用 HTTP 进行通信，但增加了 SSL/TLS 来加密数据包。HTTPS 开发的目的是提供网站服务器的身份认证，保护交换资料的隐私与完整性。

简单来说 HTTPS 是一种网络传输协议，HTTPS = HTTP + SSL/TLS 。

<!-- more -->

### 为什么要用 HTTPS

HTTPS 的主要作用是在不安全的网络上传建一个安全信道，在使用适当的加密包和服务器证书可被验证且可被信任，对窃听和中间人攻击提供合理的防护。

使用 HTTPS 的好处包括：

- 保证数据传输安全，通过传输加密和身份认证防止流量劫持，保证数据完整
- 增加用户信任度，在浏览器中访问 https 的网站会提示网站安全
- 提升网站排名，相对于 HTTP 网站，使用 HTTPS 加密的网站在搜索引擎结果排名会更高



### 与 HTTP 对比

HTTPS 与 HTTP 的主要不同点：

| 不同项   | HTTP               | HTTPS                           |
| -------- | ------------------ | ------------------------------- |
| 安全性   | 明文传输，安全性低 | 加密传输，数据安全              |
| 复杂性   | 低                 | 需要使用 SSL 证书，部署相对复杂 |
| 标准端口 | 80                 | 443                             |
| 协议层   | 基于应用层         | 基于传输层                      |
| 浏览器   | 提示不安全         | 有绿色的安全锁，提示安全        |



### HTTPS 原理

#### 工作流程

HTTPS 工作流程如下图所示：

![](https://blog-images.qiniu.wqf31415.xyz/https_work_flow.jpg)

#### 证书验证

使用 HTTPS 需要到第三方证书颁发机构（Certificate Authority）申请证书，证书颁发机构通过验证相关信息，如公钥、组织信息、域名等信息，通过验证后才会签发认证文件——证书。

证书中包含的信息有：

- 证书颁发机构CA
- 证书的有效期
- 公钥
- 证书所有者
- 签名
- ......

客户端发送请求给服务端获取到证书后，会对证书信息进行校验，判断证书是否来源于内置的受信任的证书颁发机构，如果找不到将会提示证书不被信任。

如果来自于受信任机构，浏览器从操作系统中取出颁发证书机构的公钥，对证书里的签名进行解密，浏览器使用相同的 hash 算法计算出服务器发来的证书的hash值，将这个计算的hash值与证书中签名做对比，如果一致说明服务器发来的证书合法，未被冒充。

通过验证后，浏览器从证书中取出公钥，用于后续的加密。



#### 数据加密传输

通过证书验证后，浏览器从证书中取得服务器公钥；

浏览器使用公钥加密随机密码，并将加密后的随机密码传输到服务器；

服务器使用私钥解密获得随机密码；

双方把这个随机密码作为对称加密的密钥，对后续的数据进行加密传输。



### SSL 证书供应商

国内 SSL 供应商：

- 腾讯云：<https://cloud.tencent.com/product/ssl> 
- 阿里云：<https://www.aliyun.com/product/security/markets/aliyun/product/cas> 
- 七牛云：<https://portal.qiniu.com/certificate/ssl> 
- 新浪云：<https://ssl.sinacloud.com/> 

免费 SSL 供应商：

- Let's Encrypt：<https://letsencrypt.org/zh-cn/> 

- 数安时代: <https://certmall.trustauth.cn/Free> 

  > 这个实际也是使用 Let's Encrypt 提供的免费证书，不过他们提供了可视化页面和操作指导，使用起来非常方便。



### 使用 Certbot 获取免费证书

> 在 Let's Encrypt 官方文档中，推荐**拥有命令行访问权限**的用户使用 Certbot ACME 客户端，它可以在不下线你的服务器的前提下自动执行证书颁发和安装。对于不需要自动配置的用户，Certbot 还提供专家模式，它易于使用，适用于许多操作系统，并有出色的文档。
>
> Certbot: <https://certbot.eff.org/> 

示例：为我的域名 `www.wqf31415.xyz` 申请证书。

首先域名解析到了我的服务器，能够通过浏览器访问到。

然后下载并安装 Certbot，我的服务器是 Windows 系统，所以我下载的是 `certbot-beta-installer-win32.exe` ，双击安装后即可使用。

以**管理员身份**打开命令行，或切换到管理员模式，然后执行命令: 

```bash
certbot.exe certonly
```

然后根据提示输入需要的信息：

首先是选择权限验证方式，输入 1 或 2 进行选择。我选择的是第二种，放置验证文件到web服务的根目录。

然后输入要注册证书的域名，在输入web 服务根目录的路径，等待程序执行。

执行完成后，将会输出证书文件快捷访问文件的存放位置。我生成的文件放在了 `C:\Certbot\live\www.wqf31415.xyz\` 目录下。

生成的文件包括 4 个 .pem 结尾的快捷方式文件(可以右键 `打开文件位置` 查找的原始文件)，和一个 README 说明文件：

- `cert.pem` 
- `chain.pem`
- `fullchain.pem` 
- `privkey.pem` 
- `README` 

执行结果：

```
PS C:\Users\Administrator\Desktop> certbot.exe certonly
Saving debug log to C:\Certbot\log\letsencrypt.log

How would you like to authenticate with the ACME CA?
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
1: Spin up a temporary webserver (standalone)
2: Place files in webroot directory (webroot)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Select the appropriate number [1-2] then [enter] (press 'c' to cancel): 2
Plugins selected: Authenticator webroot, Installer None
Please enter in your domain name(s) (comma and/or space separated)  (Enter 'c'
to cancel): www.wqf31415.xyz
Obtaining a new certificate
Performing the following challenges:
http-01 challenge for www.wqf31415.xyz
Input the webroot for www.wqf31415.xyz: (Enter 'c' to cancel): D:\xxx\tomcat\webapps\xxx
Waiting for verification...
Cleaning up challenges
Subscribe to the EFF mailing list (email: wqf31415@hotmail.com).
[1m
IMPORTANT NOTES:
[0m - Congratulations! Your certificate and chain have been saved at:
   C:\Certbot\live\www.wqf31415.xyz\fullchain.pem
   Your key file has been saved at:
   C:\Certbot\live\www.wqf31415.xyz\privkey.pem
   Your cert will expire on 2022-06-27. To obtain a new or tweaked
   version of this certificate in the future, simply run certbot
   again. To non-interactively renew *all* of your certificates, run
   "certbot renew"
 - If you like Certbot, please consider supporting our work by:

   Donating to ISRG / Let's Encrypt:   https://letsencrypt.org/donate
   Donating to EFF:                    https://eff.org/donate-le
```



### 使用 HTTPS

#### 本地开发

本地开发调试中需要使用 HTTPS 时，建议使用 openssl 自己颁发证书，然后将其添加到浏览器的受信任证书列表中。

> OpenSSL: <https://www.openssl.org> 
>
> OpenSSL 是一个开源的软件库包，其中包含了密码算法、常用密钥、证书封装管理功能及实现 ssl 协议，主要有三个主要功能部分：SSL 协议库 libssl、应用程序命令工具以及密码算法库 libcrypto。



#### 实际项目

在实际项目中，我们需要到证书颁发机构申请证书，需要付费，有些平台首年可以免费使用，如阿里云的 `DigiCert` 品牌的 `单域名型` 证书，腾讯云、七牛云、新浪云的 `TrustAsia` 品牌的 `单域名型` 证书。

下面介绍使用 Let's Encrypt 生成证书的方法。

- 下载并安装 certbot：<https://certbot.eff.org/> ，Let's Encrypt 使用 certbot 客户端来获取、安装和更新证书，所以首先需要根据使用的服务器操作系统下载安装 certbot 客户端，如我的 Windows 服务器需要下载安装包进行安装，安装完成后可以运行 `certbot --help` 命令查看帮助信息。
- 执行生成证书的命令：如果能够关闭网站服务，可以先关闭网站服务(因为需要使用 80 端口)，执行命令 `certbot certonly --standalone` ；如果需要保持网站服务在 80 端口上运行，执行命令 `certbot certonly --webroot` 。

#### 部署 HTTPS

##### Tomcat

以下示例配置本地 Tomcat 使用 https：

- 使用 jdk 中自带的 keytool 工具生成 `tomcat.keystore` 

  ```bash
  keytool -genkey -alias tomcat -keyalg RSA -keystore tomcat.keystore
  ```

- 修改 Tomcat 配置中的 `server.xml` 

  ```xml
  <Connector port="8443" protocol="HTTP/1.1" SSLEnabled="true"
             maxThreads="150" scheme="https" secure="true"
             clientAuth="false" keystoreFile="conf/ssl/tomcat.keystore"
             keystorePass='wqf123456' sslProtocol="TLS" />
  ```

- 访问：<https://localhost:8443> 



##### Nginx

获得证书后，修改 nginx 配置，配置内容如下：

```
# 为了节约篇幅省略了其他不相关配置
http{
    server {
        listen       443 ssl;
        server_name  www.wqf31415.xyz; # 网站域名

        ssl_certificate      C:\\server\\nginx-1.13.12\\ssl\\certificate.crt; # 证书配置
        ssl_certificate_key  C:\\server\\nginx-1.13.12\\ssl\\www.wqf31415.xyz.key; # 私钥

        ssl_session_cache    shared:SSL:1m;
        ssl_session_timeout  5m;

        ssl_ciphers  HIGH:!aNULL:!MD5;
        ssl_prefer_server_ciphers  on;

        location / {
                     proxy_pass http://127.0.0.1:8080/blog/;
              }
    }
}
```

nginx 配置 http 自动跳转 https：

```
http{
	server {
       listen       80;
       server_name  www.wqf31415.xyz;
	   return 301 https://$host$request_uri;
    }
}
```



### 参考资料

- HTTPS原理看了很多，这个是最清晰的：<http://www.easemob.com/news/3706> 
- 深入理解HTTPS工作原理：<https://segmentfault.com/a/1190000018992153> 
- 使用 Let's Encrypt（Certbot） 配置 HTTPS：<https://www.cnblogs.com/ly-radiata/articles/6119374.html> 
- OpenSSL简介: <https://blog.csdn.net/naioonai/article/details/80984032> 
- 两步配置Tomcat+Openssl的https单向认证: <https://www.jianshu.com/p/dd3f02e784e1> 



### 总结

虽然项目使用 https 部署会有点麻烦，购买商业证书还需要考虑费用支出，但使用了 https 能够让网站信息传输更加安全，让用户使用的更加放心，所以建议有能力的网站考虑使用 https。