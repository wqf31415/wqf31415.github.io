---
title: CentOS中搭建hexo博客
tags:
  - hexo
  - blog
  - linux
  - CentOS
categories:
  - 技术
date: 2021-06-28 10:19:28
---

### 概述

这篇文章介绍了在 CentOS 7 中搭建 hexo 博客的方法，内容包括在 linux 系统中安装与配置 nodejs，安装与启动 hexo 博客服务，开启防火墙的端口访问。



<!-- more --> 

### 安装步骤

#### 登陆系统

使用 ssh 远程连接 CentOS 主机，然后查看系统信息，确认开发环境。

```
ssh root@192.168.191.6
```



如果远程主机未安装 ssh ，可执行下述命令安装 `openssh-server` ：

```bash
yum install -y openssh-server
```



远程连接上后，查看系统信息：

```bash
cat /etc/redhat-release
```

结果显示：`CentOS Linux release 7.6.1810 (Core)` 



#### 安装 nodejs

> 有多种方式安装 nodejs ，如源码安装、`yum` 安装、`nvm` 安装、自行编译安装，这里的示例使用源码安装。

在 Linux 系统中使用 `wget` 工具下载 nodejs 的包，解压出来，创建软链接。

##### 下载

登陆 nodejs 官网 <https://nodejs.org/en/download/>，复制下载链接后，使用 `wget` 下载：

```bash
wget https://nodejs.org/dist/v14.17.1/node-v14.17.1-linux-x64.tar.xz
```

> nodejs 版本不同，下载地址也不同，这里以 node v14.17.1 为例。

##### 解压

要执行两个命令。

解压 xz 包，解压后得到文件 `node-v14.17.1-linux-x64.tar` 

```bash
xz -d node-v14.17.1-linux-x64.tar.xz
```

解压 tar 包，解压后得到一个目录 `node-v14.17.1-linux-x64` 

```bash
tar -xvf node-v14.17.1-linux-x64.tar
```

将目录移动到 `/usr/local/src/` 目录下：

```bash
mv node-v14.17.1-linux-x64 /usr/local/src/
```

##### 创建软链接

分别为 node 中的 `node` 、`npm` 、`npx` 创建软连接，方便在任何目录中使用。

```bash
ln -s /usr/local/src/node-v14.17.1-linux-x64/bin/node /usr/bin/node
ln -s /usr/local/src/node-v14.17.1-linux-x64/bin/npm /usr/bin/npm
ln -s /usr/local/src/node-v14.17.1-linux-x64/bin/npx /usr/bin/npx
```

> **修改环境变量** 
>
> 创建软链接的目的是方便全局使用，也可以将 nodejs 的 bin 目录加入到环境变量中，达到相同效果，这种方式比创建软链接更方便，配置到环境变量后，以后使用 `npm` 全局安装的工具都可以直接使用了，不需要再配置或创建软链接。
>
> 操作方法：
>
> 编辑 `/etc/profile` 将 nodejs 的 bin 目录加入到配置中。
>
> ```bash
> vi /etc/profile
> ```
>
> 在文件最后面添加：
>
> ```
> PATH=$PATH:/usr/local/src/node-v14.17.1-linux-x64/bin 
> export PATH
> ```
>
> 立即生效：
>
> ```bash
> source /etc/profile
> ```



##### 测试

使用命令查看 `node` 和 `npm` 版本，以此确定是否安装成功，打印出版本信息说明安装成功。

```bash
node -v
npm -v
```



#### 安装 cnpm

安装 `cnpm` 使用国内镜像，提升包下载速度：

```bash
npm install cnpm -g --registry=https://registry.npm.taobao.org
```

执行完成后，在 `/usr/local/src/node-v14.17.1-linux-x64/bin/` 目录下会增加一个文件 `cnpm` ，为这个文件添加软链接：

```bash
ln -s /usr/local/src/node-v14.17.1-linux-x64/bin/cnpm /usr/bin/cnpm
```



#### 安装 hexo

使用 `cnpm` 或 `npm` 全局安装 `hexo` ，创建软链接。

```bash
cnpm install -g hexo
```

 安装完成后，在 nodejs 的 bin 目录中，即 `/usr/local/src/node-v14.17.1-linux-x64/bin/` ，有安装的 `hexo` ，为其创建软链接：

```bash
ln -s /usr/local/src/node-v14.17.1-linux-x64/bin/hexo /usr/bin/hexo
```



#### 创建博客测试

创建一个新的目录，在其中初始化 `hexo` 博客，使用 `cnpm` 安装依赖，启动起来访问一下。

##### 创建目录

必须在空目录中初始化 `hexo` 博客，否则会报错，所以创建了一个新目录 `myblog` 。

```bash
mkdir myblog
```

##### 初始化

进入创建的空目录，初始化 `hexo` 项目。

```bash
cd myblog
hexo init
```

##### 安装依赖

使用 `cnpm` 或 `npm` 安装博客所需依赖。

```bash
cnpm install
```

##### 编译

编译博客项目，也可以使用简化命令 `hexo g` 。

```bash
hexo generate
```

##### 启动服务

开启 `hexo` 服务，可以使用简化命令 `hexo s` 。服务默认在 `4000` 端口启动服务，启动后提示访问 <http://localhost:4000> 。

```bash
hexo server
```



#### 开启端口访问

由于 CentOS 没有 UI 界面，不能在本地访问，需要访问 `http://{ip}:4000` ，如我的 CentOS 主机 ip 为 `192.168.193.6` ，所以可以访问 <http://192.168.193.6:4000> 。

如果访问不了，可能是防火墙限制了访问，需要开启端口访问策略：

```bash
firewall-cmd --zone=public --add-port=4000/tcp --permanent
```

开启防火墙访问策略后，需要重新加载一次，再次访问，即可正确展示页面。

```bash
firewall-cmd --reload
```



> CentOS 防火墙相关命令：
>
> - 关闭4000端口：`firewall-cmd --zone=public --remove-port=4000/tcp --permanent` 
> - 查看防火墙状态：`firewall-cmd --state` 
> - 查看开启的端口：`firewall-cmd --zone=public --list-ports` 
> - 关闭防火墙：`systemctl stop firewalld.service` 
> - 开启防火墙：`systemctl start firewalld.service` 



### 参考资料

- CentOS7安装最新版NodeJS: <https://www.jianshu.com/p/d4a78b27fe83> 
- Centos7开放及查看端口: <https://www.cnblogs.com/heqiuyong/p/10460150.html> 
- centos下安装nodejs的三种种方式: <https://blog.csdn.net/bbwangj/article/details/82253785> 
- CentOS 添加环境变量的三种方法: <https://blog.csdn.net/f110300641/article/details/82663132> 
