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

利用 docker 的容器化特性，在开发、测试、运维工作中都可以用来配置环境，保证环境一致，做到一处编译，到处运行。

利用 docker 容器打包应用软件及整体运行环境，简化部署运行过程，即使不了解该软件的人都可以轻松运行起来。

### 概念

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



#### docker 化应用的存在形式

在用户角度来看，用户只想要运行软件，不关心软件背后所需的操作系统、运行依赖，所以，使用 docker 可以把软件和它依赖的环境（包括操作系统和共享库等）、依赖的配置文件打包一起，以虚拟机的形式放到官方仓库，供大家使用。

但每个程序都要包含依赖的操作系统，将导致一个程序的体积变得很大。docker 的 **分层** 和 **写时拷贝策略** ，解决了包含操作系统的应用程序比较大的问题。

##### 分层的概念

在 docker 中，把一个应用分为任意多个层，比如操作系统是第一层，依赖库和第三方软件是第二层，应用的软件包和配置文件是第三层。如果两个应用有相同的底层，就可以共享这些层。

##### 写时拷贝策略

docker 中共享层存在冲突问题，比如 A 应用需要修改操作系统某个配置，B 应用不需要修改。为了解决这个问题，docker 规定层次是有优先级的，上层和下层有相同的文件和配置时，上层覆盖下层，数据以上层的数据为准。docker 给每个应用一个优先级最高的空白层，如果需要修改下层的文件，就将这个文件拷贝到这个优先级最高的空白层进行修改，保证下层的文件不做任何修改。

##### 让虚拟机轻量化

以 OpenVZ、 VServer、 LXC 为 代表 的 容器 类 虚拟 机， 是一 种 内核 虚拟 化 技术， 与 宿主 机 运行 在 相同 Linux 内核， 不需要 指令 级 模拟， 性能 消耗 非常 小， 是 非常 轻量级 的 虚拟 化 容器， 虚拟 容器 的 系统 资源 消耗 和 一个 普通 的 进程 差不多。 Docker 就是 使用 LXC（ 后来 又 推出 libcontainer） 让 虚拟 机 变得 轻量 化。



##### 镜像与容器

在 docker 仓库中的应用都是以镜像(Image)方式存在的，把镜像从 docker 仓库中拉取到本机，以这个镜像为模板启动应用，就叫容器(Container)。基于一个镜像可以创建多个名字不同但功能相同的容器。

在镜像中包含了软件运行需要的完整文件系统和程序包，没有动态生成新文件的需求。在作为容器运行时，就可能需要修改文件（输出日志、生成数据文件等），这时就需要空白层来做写时拷贝。

![](http://blog-images.qiniu.wqf31415.xyz/docker_image_container_layer.png)



##### docker 应用版本更新

在 docker 中，使用分层来完成应用版本的增量更新，当需要修改应用时，在最上面新建一个层，把所有修改内容都拷贝到这一层中，覆盖底层内容。在其他机器上需要拉取更新时，只需要拉取最新这一层的修改内容即可完成版本更新。



### 初体验

#### 安装 docker

##### Windows

从官方网站下载 Docker 桌面版安装包，安装后启动即可。

> Docker Desktop for Windows ：<https://hub.docker.com/editions/community/docker-ce-desktop-windows> 

>注意：**docker 桌面版需要 Windows 10 专业版或企业版 64 位的系统。** 老版本系统需要使用 [Docker Toolbox](https://docs.docker.com/toolbox/overview/) 运行。



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

安装完成后，使用命令行执行 `docker version` 查看 docker 版本。

也可以使用 docker 运行 hello-world 来检查是否安装成功。打开终端，运行命令：

```bash
docker run hello-world
```

运行结果：

```
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
1b930d010525: Pull complete
Digest: sha256:f9dfddf63636d84ef479d645ab5885156ae030f611a56f3a7ac7f2fdd86d7e4e
Status: Downloaded newer image for hello-world:latest

Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading. 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:  https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/
```



#### docker 命令

> 运行 `docker` 命令，可以获取 docker 命令的帮助信息。
>
> 运行 `docker COMMAND --help` ，可以获取具体指令的帮助信息。

docker 命令的基本用法是：

```bash
docker [OPTIONS] COMMAND
```

> - OPTIONS：选项、参数，可选
> - COMMAND：命令



##### 寻找镜像

###### 终端

`docker search 关键字` ，按关键字在仓库中检索镜像。如查找 nginx 镜像：`docker search nginx` 

![](http://blog-images.qiniu.wqf31415.xyz/docker_search_nginx.png)

> 检索结果分为五项，分别是：
>
> - **NAME** 镜像全名，一般包含作者和镜像名
> - **DESCRIPTION** 描述信息
> - **STARS** 镜像获得的点赞数
> - **OFFICIAL** 是否官方发布
> - **AUTOMATED** 自动构建

###### 网页

另一种查找镜像的方式是通过 docker 仓库提供的 web 页面搜索，登陆 <https://hub.docker.com> ，在搜索框中输入关键字点击搜索即可。

使用网页搜索镜像的好处是，有很多关于镜像的说明信息，包括如果拉取、运行，如何配置等。



##### 拉取镜像

`docker pull 镜像名` ，从仓库中拉取执行名称的镜像到本地，需要使用镜像全名，如 `docker pull nginx` 。

可以在镜像名后加上`:` 和标签，以此拉取拉取的版本，如果不指定，则默认拉取最新版本，最新版本标签统一为 `latest` 。

拉取最新版本 nginx 的命令如下，其中 `:latest` 可以省略：

```bash
docker pull nginx:latest
```

拉取 perl 版本 nginx 命令为：

```bash
docker pull nginx:perl
```

拉取最新版 nginx 镜像：

![](http://blog-images.qiniu.wqf31415.xyz/docker_pull_nginx.png)



##### 运行镜像

`docker run 镜像` 命令用来运行指定镜像，运行起来之后就是一个独立的容器了，可以通过 `docker ps` 来查看运行起来的容器。

一般在运行时会指定一些参数，比如设置容器名称，设置端口映射，设置后台运行等等。比如运行一个 nginx 应用：

```bash
docker run --name my-nginx -d -p 9080:80 nginx
```

> 参数说明：
>
> - *--name* 指定容器名称，后面跟的就是容器名称，这里是 `my-nginx` 。如果不指定名称，将会随机生成名称。
> - *-d* 指定容器在后台运行，如果不加这个参数，容器将在前台运行
> - *-p* 指定端口映射，这里的 `9080:80` 可以把宿主机的 9080 端口映射到容器中的 80 端口

运行结果：

![](http://blog-images.qiniu.wqf31415.xyz/docker_run_nginx.png)

命令执行后输出的这一段文字是运行成功输出的容器 ID。



##### 测试

使用 docker 启动了 nginx 后，我们可以在浏览器中访问指定的映射端口(这里是 9080)，访问地址 <http://localhost:9080/> ，出现 nginx 的欢迎页面，说明容器运行正常。

![](http://blog-images.qiniu.wqf31415.xyz/docker_run_nginx_result.png)



##### 查看运行状态

使用 `docker ps` 命令查看正在运行的容器，可以加 `-a` 参数来查看包含未启动的容器。

![](http://blog-images.qiniu.wqf31415.xyz/docker_ps.png)

> 输出内容有六项，分别是：
>
> - **CONTAINER ID** 容器ID，显示的是容器 ID 前12位
> - **IMAGE** 镜像
> - **COMMAND** 启动容器的命令 
> - **CREATED** 容器创建时间
> - **STATUS** 容器状态，正在运行的容器会显示 `Up` 和运行时长
> - **PORTS** 端口映射，这里的 `0.0.0.0:9080->80/tcp` 是将本机的 9080 端口映射到容器的 80 端口，tcp 协议
> - **NAMES** 容器名称



##### 停止运行的容器

`docker stop 容器名` ，停止指定名称的容器。如停止运行的 `my-nginx` 容器：

```bash
docker stop my-nginx
```

> 除了使用容器名称来停止运行的容器之外，还可以通过容器 ID 或容器 ID 缩写来停止容器，容器 ID 可以通过 `docker ps` 获取。



### 遇到的问题

#### Windows 系统电脑未开启虚拟化导致运行 docker 失败

docker 需要使用到电脑的虚拟化功能，如果未开启这个功能，将导致 docker 运行失败。在 windows 10 电脑任务管理器中的 `性能` 一栏中可以看到是否启用虚拟化功能，如图：

![](http://blog-images.qiniu.wqf31415.xyz/docker_windows_virtual.png) 



### 参考资料

- 李金榜. 循序渐进学Docker (容器技术系列) . 机械工业出版社
- Empowering App Development for Developers | Docker: <https://www.docker.com/> 



### 总结

在你体验过 docker 之后，你就会为它的方便折服。