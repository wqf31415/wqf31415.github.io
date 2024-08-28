---
title: 部署Hexo博客到云服务器
tags:
  - hexo
  - blog
  - CentOS
  - nginx
  - 博客
  - 域名
  - 服务器
  - 网络
categories:
  - 技术
date: 2024-08-29 02:25:14
---

### 概述

这篇文章介绍了将 Hexo 静态博客部署到云服务器的方法，内容涉及到域名解析、云服务器配置、nginx安装与配置、https证书申请与配置。



### 原理其实很简单

Hexo 博客编译后会得到一些静态的前端页面和文件，将它们放到服务器上，并启动一个 nginx 作为 web 服务器，就可以访问了。

如果想让访问更加友好，那就申请一个域名，将域名解析到服务器，就可以通过域名访问了。

如果想让博客访问更安全，就申请一个免费的 https 证书，改一下 nginx 配置就行了。



<!-- more -->

### 需要准备什么

- 云服务器（CentOS 7.9 系统）

- 域名（已备案）
- Hexo 博客源码
- PC机，装了git、nodejs、shell工具（如[MobaXterm](https://mobaxterm.mobatek.net/)）、文件压缩工具（zip）



### 整体流程介绍

首先，准备好需要的物料，包括云服务器、域名、Hexo 博客源码、一台能连上云服务器的 pc 机。

然后，远程登录到云服务器，安装 nginx 。

然后，修改云服务器的访问策略，允许 80 和 443 端口访问，尝试访问服务器 80 端口，确认端口开启且 nginx 运行正常。

然后，修改域名 dns 解析配置，将域名地址解析配置为云服务器 ip，保存后尝试使用域名访问。

然后，修改 nginx 配置，将域名访问的请求解析到博客文件目录，并将本地生成的博客文件上传到博客文件目录，重启 nginx。

然后，使用域名访问，确认是否能访问博客页面，能访问说明 http 的访问已经 ok。

然后，喝口水，想想需不需要配置 https。

然后，在服务器上安装 Certbot 工具，用它申请到免费证书。

然后，修改 nginx 配置，使用申请到的整数，并配置 443 端口的访问。（这一步由 Certbot 工具自动完成）

然后，使用 https + 域名访问，验证配置是否成功。

最后，为自己鼓掌。



### 第一步，准备物料

#### 云服务器

现在云服务器厂商很多，寻找一个自己喜欢的，购买一个云服务器，买的时候操作系统选择 CentOS 7.9，其他配置根据需要选择。

> 我用过的一些云服务器商：
>
> 阿里云：https://www.aliyun.com/ 
>
> 腾讯云：https://cloud.tencent.com/
>
> 天翼云（中国电信旗下）：https://www.ctyun.cn/

购买完成后，登录官网，进入控制台，找到云主机实例，先修改登录密码，方面后续登录。

然后修改 “安全组” ，添加访问规则，允许所有ip（0.0.0.0/0）访问 TCP 协议的 80 端口和 443 端口。

最后，把云服务器的公网 ip 记录下来。



#### 域名

很多云厂商提供了域名服务，我是在阿里云购买的域名。

购买域名后，登录云厂商官网，进入控制台，找到购买的域名，点击 “解析” ，进入域名解析界面。

添加一条解析记录，记录类型选择 “A-将域名指向一个IPV4地址”，主机记录填上自己想要的域名前缀（如www），记录值填上自己云服务器的公网 ip 地址，TTL 选择 10 分钟，保存。

打开电脑 CMD，执行命令 `ping 域名` ，如果能够正确解析出服务器的 ip 地址，说明域名配置已生效。

最后，将域名记录下来，是包含前缀的完整域名。



#### Hexo博客与工具

Hexo 博客的安装与编译就不再赘述了。

打开命令行，进入博客根目录，执行命令 `hexo generate` ，等待执行完成，将 public 文件夹压缩成 zip 包，命名为 blog.zip。

安装远程终端工具 [MobaXterm](https://mobaxterm.mobatek.net/) ，运行 MobaXterm，点击菜单栏中的 “Terminal” - “Open new tab”，运行命令 `ssh root@<server_ip>` 或者 `ssh root@<your_domain>` ，输入服务器密码，完成登录。

> 注意要将本文中的 `<server_ip>` 替换成自己云服务器的公网 ip 地址，将 `<your_domain>` 替换成完整域名。



### 第二步，部署Hexo博客

#### 安装nginx

使用 MobaXterm 远程登录到服务器，按照 nginx 官方推荐方法 https://nginx.org/en/linux_packages.html 安装 nginx：

1. 安装 yum-utils：`sudo yum install yum-utils`

2. 设置 yum 仓库：创建文件 /etc/yum.repos.d/nginx.repo，内容如下

   ```ini
   [nginx-stable]
   name=nginx stable repo
   baseurl=http://nginx.org/packages/centos/$releasever/$basearch/
   gpgcheck=1
   enabled=1
   gpgkey=https://nginx.org/keys/nginx_signing.key
   module_hotfixes=true
   
   [nginx-mainline]
   name=nginx mainline repo
   baseurl=http://nginx.org/packages/mainline/centos/$releasever/$basearch/
   gpgcheck=1
   enabled=0
   gpgkey=https://nginx.org/keys/nginx_signing.key
   module_hotfixes=true
   ```

3. 安装 nginx：`sudo yum install nginx` 

4. 验证：使用浏览器访问 `http://<server_ip`> 或 `http://<your_domain>` ，如果能显示出 nginx 的欢迎页面，说明安装成功。



#### 部署 hexo博客

1. 登录服务器：使用 MobaXterm 远程登录到服务器。

2. 创建目录：创建存放博客资源的目录：`mkdir /usr/share/nginx/blog` 。

   > 资源目录可根据自己喜好创建。

3. 上传资源包：点击 MobaXterm 左侧的 “SSH browser (SFTP)” 图标，左侧会显示服务器上的目录，进入到目录 `/usr/share/nginx` ，鼠标按住打包好的 blog.zip 文件，拖入目录界面空白处，将文件上传到服务器。

4. 解压资源包：进入目录 `cd /usr/share/nginx`，使用 `unzip blog.zip` 解压资源文件，解压完成后，目录中将出现 public 目录。

   > 如果执行命令时提示 `unzip: command not found` ，说明没有安装解压 zip 的工具包 `unzip` ，运行命令安装：`yum install unzip -y` 。

5. 拷贝资源文件：执行文件拷贝命令：`cp -r public/* blog/` 。

6. 修改 nginx 配置：修改 nginx 默认配置文件 `vim /etc/nginx/conf.d/default.conf` ，在最前面添加如下配置内容：

   ```
   server {
       listen       80;
       server_name  www.wqf31415.xyz;
       location / {
           root /usr/share/nginx/blog;
           index index.html;
       }
   }
   ```

   > 注意上面配置中的 `www.wqf31415.xyz` 是域名，要改成自己的域名。

   修改完成后，运行 `nginx -t` 命令检查配置是否正确，如果打印如下信息说明配置正确：

   ```
   nginx: the configuration file /etc/nginx/nginx.conf syntax is ok
   nginx: configuration file /etc/nginx/nginx.conf test is successful
   ```

7. 加载nginx配置：运行命令 `nginx -s reload` 加载配置，运行成功后使用浏览器访问  `http://<server_ip`> 或 `http://<your_domain>` ，如果能显示博客内容，说明部署成功。



### 第三步，配置https证书

#### 安装 Certbot

按照 Certbot 官网提供的方法安装：<https://certbot.eff.org/instructions?ws=nginx&os=snap> 

1. 安装 snap：`sudo yum install snapd -y`
2. 启用 snap 的 socket 通信：`sudo systemctl enable --now snapd.socket` 
3. 启用典型的 snap 功能（创建符号链接）：`sudo ln -s /var/lib/snapd/snap /snap` 
4. 安装 Certbot：`snap install --classic certbot` 
5. 创建 Certbot 的链接，方便使用：`sudo ln -s /snap/bin/certbot /usr/bin/certbot` 



#### 申请并安装证书

使用 Certbot 申请并安装证书：运行命令`sudo certbot --nginx` ，根据提示信息填写回答。

> 第一个输入内容是：输入电子邮件地址（用于紧急续订和安全通知），按 `c` 取消；输入自己的邮箱。
>
> 第二个输入内容是：必须同意条款才能在 ACME 服务器（即 Let's Encrypt）上注册；输入Y。
>
> 第三个输入内容是：输入数字来选择要生成证书的域名；我这里只有一个选项，输入1。

输入完成后，开始注册并配置证书，打印信息如下所示：

```
Requesting a certificate for www.wqf31415.xyz

Successfully received certificate.
Certificate is saved at: /etc/letsencrypt/live/www.wqf31415.xyz/fullchain.pem
Key is saved at:         /etc/letsencrypt/live/www.wqf31415.xyz/privkey.pem
This certificate expires on 2024-11-26.
These files will be updated when the certificate renews.
Certbot has set up a scheduled task to automatically renew this certificate in the background.

Deploying certificate
Successfully deployed certificate for www.wqf31415.xyz to /etc/nginx/conf.d/default.conf
Congratulations! You have successfully enabled HTTPS on https://www.wqf31415.xyz

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
If you like Certbot, please consider supporting our work by:
 * Donating to ISRG / Let's Encrypt:   https://letsencrypt.org/donate
 * Donating to EFF:                    https://eff.org/donate-le
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
```

使用浏览器访问  `https://<your_domain>` ，如果能显示博客内容，说明部署成功。

安装完成后，查看 `/etc/nginx/conf.d/default.conf` 文件内容，发现配置中自动添加了 5 行配置。

```
server {
    server_name  www.wqf31415.xyz;
    location / {
        root /usr/share/nginx/blog;
        index index.html;
    }

    listen 443 ssl; # managed by Certbot
    ssl_certificate /etc/letsencrypt/live/www.wqf31415.xyz/fullchain.pem; # managed by Certbot
    ssl_certificate_key /etc/letsencrypt/live/www.wqf31415.xyz/privkey.pem; # managed by Certbot
    include /etc/letsencrypt/options-ssl-nginx.conf; # managed by Certbot
    ssl_dhparam /etc/letsencrypt/ssl-dhparams.pem; # managed by Certbot

}
```



### 总结

在国内，将域名解析到服务器上提供web服务，是需要备案的，备案后要将备案信息展示到页面上。

云服务器尽量买大厂的，比如阿里云、腾讯云等等，在搞活动时只需要几十块钱就可以买一年，也可以在淘宝上购买，很便宜，一定要注意新用户都有优惠的。

云服务器厂商提供了网络策略管理，在控制台就可以修改端口的访问策略。

使用 Certbot 申请的 https 证书可以免费用 3 个月，Certbot 自带了自动刷新证书功能，在证书过期前会自动更新。
