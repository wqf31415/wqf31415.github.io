---
title: 认识 docker
tags:
  - docker
  - 工具
categories:
  - 工具
date: 2020-03-14 21:01:20
---

### 概述

在未来，软件项目会越来越复杂，其中的依赖关系更是错综复杂，使用 docker 能够解决环境依赖问题，减少环境配置带来的工作量。本文介绍了 docker 的一些基本概念，什么是 docker，阐述 docker 是怎么工作的。还讲解了 docker 的一些应用场景，说明了 docker 能够解决什么问题，在什么情况下适合使用 docker，以及不同人员怎么使用 docker。



### 定义

![](http://blog-images.qiniu.wqf31415.xyz/docker.jpg)

> 官网：<https://www.docker.com/> 

docker 是一个开源的应用容器引擎，可以将应用以及应用运行所需的环境一起打包，在不同机器上直接运行，达到一次部署，到处运行的效果。

docker 是 dotCloud 公司的产品，使用 go 语言开发，遵循 Apache 2.0 开源协议。

<!-- more -->



### 背景及应用场景

#### 背景

当代互联网技术蓬勃发展，优秀的系统和软件如雨后春笋般层出不穷，这么丰富的技术栈一方面为我们应用的开发提供了方便，可以选择不同的软件来实现功能，但另一方面也带来了一些问题，技术选型多，需要配置的依赖环境也多，在开发、测试和运维之间协调统一运行环境，就是一件非常麻烦的事情。因而在实际开发时，往往为了避免运维的麻烦，一般只能选择一两种来支持。

Docker 的出现就解决了不同技术运行环境的协调问题，让我们可以从环境搭建的重复工作中解脱出来，docker 作为一个应用容器引擎，可以让用户把应用和开发环境打包到一个容器中，开发、测试、运维都能保持环境一致。同时，创建的镜像可以发布到任何运行 docker 引擎的机器上，方便应用扩展和创建集群。



#### 应用场景

##### 使用人员

###### 开发

- 复制开发环境：小组开发同一个项目，用 docker 搭建开发环境后，环境变更可以一键复制到其它开发人员电脑上，也可以一键复制到新成员电脑上，大大节约了搭建开发环境的时间。

- 快速运行：在使用新软件新技术时，如果该软件有 docker 镜像，就可以使用 docker 一键运行。

- 多环境切换：同时开发多个项目时，使用 docker 轻松完成多个开发环境的切换。

###### 测试

保证测试环境与开发环境一致：使用 docker 后，开发人员提交应用时，同时提供运行相关的环境，就可以避免因环境不同导致的 bug。在开发更新环境配置后，直接将修改内容提交到仓库中，测试使用 docker 拉取更新内容，即可完成测试环境更新。

###### 运维

- 简化部署流程：可以把应用和复杂的部署环境整合成一个镜像，一键部署项目，这样即使是不熟悉项目的人，也可以轻松完成应用部署工作；在机器发生故障时，使用 docker 能够快速在其他机器上运行项目。
- 版本切换：可以创建应用多个版本的镜像，如果新版本出问题可以快速切换回原来版本。
- 保证应用一致：只要使用同一个镜像部署应用，那么每个应用实例都是完全一致的。
- 跨平台：docker 可以在不同操作平台中运行，那么使用 docker 部署的项目也就能够达到跨平台部署的效果。
- docker 化的应用时虚拟化，多个应用可以混合部署在同一台机器上，互不干扰，提高机器使用率。



##### 场景

利用 docker 的容器化特性，在开发、测试、运维工作中都可以用来配置环境，保证环境一致。



### 概念

#### 容器(Container)



#### 镜像(Image)



#### docker 程序

使用 docker 时，需要在机器上是运行的一个 docker 程序，提供了一些接口和内核进行交互。

在本机上 docker 是 C/S 架构，docker daemon 作为服务端，以后台守护进程形式运行。客户端比较灵活，可以使用本机 bin 命令形式发送命令，也可以通过远程 restful 接口形式发送命令，docker 服务端接收指令并分解成一系列任务执行。



#### 仓库(Repository)

仓库是用来存放已经打包好的 docker 应用——Docker镜像。

> 官方仓库：<https://hub.docker.com> 

官方仓库中应用非常丰富，有各大公司打包的应用镜像，也有个人开发者提供的应用，用户可以从这个官方仓库拉取镜像。



#### docker 工作流程

首先需要运行 docker 软件包，并启动 docker deamon 守护进程，然后就可以使用 docker client 端发送各种指令，服务端执行完指令将结果返回给客户端。

比如我们启动一个 nginx 程序：

- 打开终端，运行启动 nginx 的指令 `docker run nginx` 
- docker deamon 收到命令，先查找本地有没有这个程序的镜像，如果已经存在，则使用这个镜像创建容器并开始运行；如果本地不存在这个镜像，docker deamon 请求官方仓库，从官方仓库中搜索这个镜像 nginx。
- 从仓库中将镜像下载到本地
- docker deamon 启动应用
- 把启动应用是否成功的结果返回给客户端



### 初体验

#### 安装 docker

##### Windows



##### Linux

> 几乎所有系统和平台都支持 docker，但因为 docker 是 2013年3月才诞生的，用到了 linux 内核 3.8 以上的系统才具有的一些特性，所以只有相对较新的系统版本才支持 docker。

docker 是在 Ubuntu 下诞生和发展的，docker 的最新特性都是在 Ubuntu 下开发和测试的，所以<span style="background:#ffa"> Ubuntu 是支持 docker 最好的操作系统</span>。

###### Ubuntu 安装 docker

- 更新 apt 软件源

  ```bash
  sudo apt-get update
  ```

  

- 安装docker

  - 方法一 从 apt 源安装 docker.io ，但版本比较旧
  
    ```bash
    sudo apt-get install docker.io
    ```
  
    
  
  - 方法二<sup>(推荐)</sup> 使用官方脚本安装，能够安装最新版 docker
  
    ```bash
    sudo apt-get install curl
    curl -sSL https://get.docker.com/ | sh
    ```
  
    

- 启动 docker 守护进程

  ```bash
  sudo service docker start
  ```

  

- 验证是否安装成功

  ```bash
  sudo docker run hello-world
  ```




###### 不想每次运行 docker 都使用 sudo 权限

如果不想每次运行 docker 都使用 sudo 权限，可以把用户加到 docker 组中。如我的用户名为 `wqf` ，则添加命令如下：

```bash
sudo usemod -aG docker wqf
```

重启生效后，执行 docker 命令就不用再加 `sudo` 了。



##### 测试

安装完成后，我们使用 docker 运行 hello-world 来检查是否安装成功。打开终端，运行命令：

```bash
docker run hello-world
```



#### 寻找镜像



#### 拉取镜像



#### 运行镜像



#### 测试



#### 查看运行状态



#### 停止运行



### 遇到的问题

#### Windows 系统电脑未开启虚拟化导致运行 docker 失败

docker 需要使用到电脑的虚拟化功能，如果未开启这个功能，将导致 docker 运行失败。在 windows 10 电脑任务管理器中的 `性能` 一栏中可以看到是否启用虚拟化功能，如图：

![](http://blog-images.qiniu.wqf31415.xyz/docker_windows_virtual.png) 



### 总结

在你体验过 docker 之后，你就会为它的方便折服。