---
title: nginx常用配置
tags:
  - nginx
  - 服务器
  - 工具
categories:
  - 工具
date: 2021-09-02 19:41:45
---

### 概述

这篇文章介绍了 nginx 的配置语法与常见配置示例。



### 关于 nginx

Nginx (读音同 `engine X`)，是开源的异步框架的网页服务器，可以用作反向代理、负载均衡器和 HTTP 缓存。

> 官网：<http://nginx.org/> 

<!-- more -->



### 配置语法

#### 配置结构

```
main		# 全局配置，对全局生效
	events	# 影响 nginx 服务器或与用户的网络连接
	http	# 配置代理、缓存、日志定义等绝大多数功能和第三方模块的配置
		upstream	# 配置后端服务器具体地址，负载均衡配置不可或缺的部分
		server		# 配置虚拟主机的相关参数，一个 http 块中可以有多个 server 块
			location	# 配置 uri 匹配路由，server 块可以包含多个 location 块
```

#### 语法

- 配置文件由指令和指令块构成
- 每条指令以 `;` 分号结尾，指令与参数间以空格符号分隔
- 指令块以大括号 `{}` 包裹，可包含多个配置文件
- `include` 语句允许组合多个配置文件以提升可维护性
- `#` 用于添加注释
- `$` 用于引用变量
- 部分指令的参数支持正则表达式，如 `location` 指令

#### 内置变量

| 变量               | 含义                                                         |
| ------------------ | ------------------------------------------------------------ |
| `$host`            | 请求信息中的 Host，如果请求中没有 Host 行，则等于设置的服务器名 |
| `$request_method`  | 客户端请求方法，如 GET、POST                                 |
| `$remote_addr`     | 客户端 IP 地址                                               |
| `$args`            | 请求中的参数                                                 |
| `$content_length`  | 请求头中的 `Content-length` 字段                             |
| `$http_user_agent` | 客户端 agent 信息                                            |
| `$http_cookie`     | 客户端 cookie 信息                                           |
| `$remote_port`     | 客户端端口                                                   |
| `$server_protocol` | 请求使用的协议，如 HTTP/1.1                                  |
| `$server_addr`     | 服务器地址                                                   |
| `$server_name`     | 服务器名称                                                   |
| `$server_port`     | 服务器端口号                                                 |



### 常用配置

#### 反向代理

将用户请求代理的真实的服务器上。

```
server {
	listen 80;
	
	# 将所有请求代理到 nginx 根目录下的 html/dest/web 目录
    location / {
        root   html/dest/web;
        index  index.html index.htm;
        try_files $uri $uri/ /index.html;
    }
	
	# 将所有 80 端口的 /api 开头的请求代理到本地 8080 端口
	location /api {
		proxy_pass http://localhost:8080;
	}
	
    # 反代所有以/static/开头的的请求到本地文件目录
    location ^~ /static/ {
        alias   "D:/data/";
        autoindex off;
        access_log off;
        expires max;
    }
    
    # 发生 500、502、503、504 错误时返回 json 格式的错误信息
    error_page 500 502 503 504 /respon_500.json;
    location = /respon_500.json {
        default_type application/json;
        return 403 '{"state":"fail","result":"Server Error"}';
    }
    
    # 多个 server 配置
    server {
    	listen 443 ssl; # https 请求
    	        server_name  _;

        #字符集
        charset utf-8;

        # ssl 证书配置
        ssl_certificate      G:\\program\\server\\nginx-1.16.1\\ssl\\server.crt;
        ssl_certificate_key  G:\\program\\server\\nginx-1.16.1\\ssl\\server.key;
        ssl_session_cache    shared:SSL:1m;
        ssl_session_timeout  5m;
        ssl_ciphers  HIGH:!aNULL:!MD5;
        ssl_prefer_server_ciphers  on;

        location / {
            root   html/dest/web;
            index  index.html index.htm;
        }
    }
    
    server {
    	listen 80; # 可以配置有相同的端口
    	server_name www.xxx.com www.yyy.com; # 指定访问域名，从这些域名进来的请求会进到这个配置块
    	
        location / {
            root   html/dest/web;
            index  index.html index.htm;
        }
    }
}
```



#### 访问权限

禁止指定 ip 访问，被禁止访问的 ip 访问时会报 `403` 错误。

```
server {
	listen 80;
	
	location / {
		allow 172.16.16.1; # 允许访问的ip
		allow 192.168.0.0/16; # 允许访问的ip段
		deny all; # 拒绝其他所有 ip
		
		root html/dest/web;
		index index.html index.htm;
	}
}
```



### 参考资料

- Nginx 最全操作总结: <https://mp.weixin.qq.com/s/LmtHTOVOvdcnMBuxv7a9_A> 
