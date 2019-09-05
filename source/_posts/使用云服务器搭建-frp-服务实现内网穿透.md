---
title: 使用云服务器搭建 frp 服务实现内网穿透
date: 2019-03-16 11:18:02
tags:
- frp
- 服务器
- 域名
- 内网穿透
categories:
- 技术
---

### 概述
本文介绍了在云服务器(Windows Server 2012)上搭建 frp 服务，以及域名 DNS 解析配置，实现内网穿透功能，使用自定义域名访问部署于内网的 web 服务。

### 背景
开发过微信公众号程序的同学都知道，微信公众号的服务器配置中，需要指定服务器地址，微信平台会往这个地址推送消息。这个地址必须是公网能够访问的，我们在本地开发测试时，就需要一个地址，能够在公网中访问本地运行的程序，内网穿透就是干这个的。以前我使用的是别人的 ngrok ，但有一些问题，比如不能指定 url 前缀，使用自定义的需要交费，再比如别人服务器关了，我就要满世界去找其它的工具了。
frp 是一款开源的用于内网穿透的反向代理工具，支持 tcp、udp 协议，为 http、https 协议提供了额外的能力。
![](http://blog-images.qiniu.wqf31415.xyz/network_server.jpg)

<!-- more -->

在买了云服务器后，我自己搭建了一个内网穿透服务，不再在网上找免费的了。

### 环境与原材料
#### 云服务器
不限于云服务器，只要是能使用的服务器都可以。我使用的是腾讯云的服务器 `windows server 2012` `1核` `2G内存` `50G硬盘` `1M带宽` ，最适合尝鲜的配置。

#### 域名
域名申请于阿里云，因为当时打折，域名一年才 1 块钱。

#### frp
frp 是一个开源项目，可以从其 github 上获取最新发布版本，下载地址：[https://github.com/fatedier/frp/releases](https://github.com/fatedier/frp/releases "frp release") 。

### 搭建 frp 服务
> frp 官方中文文档: [https://github.com/fatedier/frp/blob/master/README_zh.md](https://github.com/fatedier/frp/blob/master/README_zh.md "frp 官方中文文档")

#### 下载并解压
> 官网最新版本下载地址：[https://github.com/fatedier/frp/releases](https://github.com/fatedier/frp/releases "frp release")

因为我的服务器和客户端都是 windows 系统，所以下载的是 frp_0.21.0_windows_amd64.zip ，解压出来之后有下面这些文件：
![](http://blog-images.qiniu.wqf31415.xyz/frp_zip_files.png "frp 压缩包中文件")

从文件名可以知道这些文件的功能：
- frpc.exe 客户端程序
- frpc.ini 客户端配置文件
- frpc_full.ini 客户端完全配置示例
- frps.exe 服务端程序
- frps.ini 服务端配置文件
- frps_full.ini 服务端完全配置示例
- LICENSE 协议说明

#### frp 服务端
将解压出来文件中的 frps 相关的所有文件拷贝到服务器上，修改 frps.ini 配置后，使用命令 `frps.exe -c frps.ini` 即可启动 frp 服务。
我的 frps.ini 配置如下：
``````ini
[common]
# 绑定端口
bind_port = 7000

# http 访问端口，默认值为 80
vhost_http_port = 8084

# https 端口
vhost_https_port = 443

# 子域名
subdomain_host = frp.wqf31415.xyz

# 验证令牌
token = 123456
``````

更多配置可以参考 frps_full.ini 文件。

#### nginx 配置
由于我服务器上还有其它 web 服务，不希望 80 端口被占用，所以我在上面将 http 访问端口 `vhost_http_port` 配置成了 8084 ，现在就需要使用 nginx 将来自域名 `frp.wqf31415.xyz` 的所有 80 端口的请求映射到 frp 的 8084 端口，修改 nginx 配置如下:
``````

#user  nobody;
worker_processes  1;

#error_log  logs/error.log;
#error_log  logs/error.log  notice;
#error_log  logs/error.log  info;

#pid        logs/nginx.pid;


events {
    worker_connections  1024;
}


http {
    include       mime.types;
    default_type  application/octet-stream;

    #log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
    #                  '$status $body_bytes_sent "$http_referer" '
    #                  '"$http_user_agent" "$http_x_forwarded_for"';

    #access_log  logs/access.log  main;

    sendfile        on;
    #tcp_nopush     on;

    #keepalive_timeout  0;
    keepalive_timeout  65;

    #gzip  on;

	# frp config	
	server {
       listen       80;
       server_name  frp.wqf31415.xyz;
       location / {
                     proxy_pass http://frp.wqf31415.xyz:8084/;
              }
    }
}
``````

> 其中只需要关注 http 配置项中 frp config 的 server 配置。

#### 客户端
从解压的文件中取出 frpc 相关的文件，修改 frpc.ini 配置，使用命令 `frpc.exe -c frpc.ini` 即可运行客户端。
我的 frpc.ini 配置：
``````ini
[common]
# 服务器配置，与服务器中 frps.ini 中的内容保持一致
# 服务器地址
server_addr = 118.24.50.165

# 服务器端口
server_port = 7000

# 验证令牌
token = 123456

[web]
# 协议类型
type = http

# 本地端口，我本地开发微信服务器时使用的端口是 8181
local_port = 8181

# 子域名
subdomain = wx

# 域名
custom_domains = frp.wqf31415.xyz
``````

完成以上配置并成功启动 frp 服务后，访问 http://wx.frp.wqf31415.xyz  ->  http://localhost:8181 
更多的配置信息可以参考 frpc_full.ini 文件，或官方文档。

### 域名设置
> 域名可能需要备案，可以到域名申请商或服务器供应商处进行域名本案。

添加两条域名解析，一条 A 类型，主机记录 `frp` ，记录值为服务器 ip 地址；第二条 CNAME 类型，主机记录为 `*.frp` ，记录值为 `frp.wqf31415.xyz` 。配置结果如下图所示，其中 wqf31415.xyz 是我的域名：
![](http://blog-images.qiniu.wqf31415.xyz/frp_domain_dns.png "域名解析配置")

> 添加 `*.frp` 的解析规则是为了实现自定义域名前缀，添加这条解析规则后，可以将 `xxx.frp.wqf31415.xyz` 的请求解析到云服务器上来。

### 测试使用
完成域名配置后，到服务器启动 frp 服务，可以将启动命令写入一个 bat 文件，使用 nssm 或 WinSW 工具将其设置成服务，开机自动启动，方便使用。
启动本地 web 服务，启动本地 frp 客户端，在公网访问配置的域名 wx.frp.wqf31415.xyz 即可访问本地 web 服务。
![](http://blog-images.qiniu.wqf31415.xyz/frp_client_run.png "启动 frp 客户端")

### 参考资料
- frp github：[https://github.com/fatedier/frp](https://github.com/fatedier/frp "frp github 仓库") 
- frp 官方中文文档: [https://github.com/fatedier/frp/blob/master/README_zh.md](https://github.com/fatedier/frp/blob/master/README_zh.md "frp 官方中文文档") 

