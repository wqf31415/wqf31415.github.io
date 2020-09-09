---
title: docker 镜像管理
tags:
  - docker
  - 工具
categories:
  - 工具
date: 2020-09-09 19:35:40
---

### 概述

镜像是 docker 的精髓，只有了解 docker 镜像，才能真正理解 docker 的内涵。这篇文章介绍了镜像相关的操作和对镜像的操作。

![](http://blog-images.qiniu.wqf31415.xyz/docker_whale_2.jpg)



### 什么是镜像

镜像是一个应用程序的依赖包以及其运行环境的完整拷贝，用于为创建容器提供模板。

每个 docker 镜像都有一个唯一的标识 ImageID，与容器 ID 类似，默认为 128 位，可以使用前 16 位的缩略形式，也可以**使用镜像的名字(NAME)和版本号(TAG)组合成唯一标识**，如果省略版本号则使用最新版本（latest）。如：`redis:latest` 、`redis:6.0.7` 



<!-- more -->



### 镜像的分层概念

docker 镜像采用分层机制，相同部分独立成层，只需要存储一份就可以了，多个镜像可以使用相同的底层镜像，大大节省了镜像空间。

对于分层的 docker 镜像有两个特性：

- **已有的分层只能读不能修改**，如果要修改已有层上的文件，只能将文件拷贝到新层上，然后修改新层中的文件。
- **上层镜像的优先级高于底层镜像**，如果不同层有相同的文件，则上层的文件将覆盖下层的文件，以上层文件为准。

容器是在镜像的基础上创建的，从文件系统的角度看，它是在镜像的基础上增加一个新的空白层，这个新分层是可读写的。容器的所有写操作都会存储在最上面的可读写层。

![](http://blog-images.qiniu.wqf31415.xyz/docker_image_container_layer.png)

使用 `docker commit` 命令提交对镜像的修改，会将修改的层叠加到已有镜像层之上，形成新的镜像，最终用户看到的是所有层叠加的结果，所看到的文件也是所有层文件的集合。如：

第一层文件：

```
a.txt
b.txt
c.txt
```

第二层文件：

```
d.txt
e.txt
```

第三层文件：

```
f.txt
```

最终：

```
a.txt
b.txt
c.txt
d.txt
e.txt
f.txt
```



### 体验

在 docker 客户端启动一个容器时，docker 会自动获取镜像。首先会在本地镜像中查找所需镜像，如果有则直接启动；如果本地没有该镜像，docker 客户端会从远程仓库中查找，找到后会下载到本地并启动，如果都没有找到则会报错。所以我们只需要运行容器就可以自动获取镜像，如运行 redis 容器：

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
```

从上述运行结果可以看出，由于本地没有 `hello-world:latest` 镜像，所以从远端仓库下载了该镜像。



### 查看镜像

使用 `docker images -a` 或 `docker image ls` 命令查看本地所有镜像。

使用 `docker inspect` 命令查看镜像详情。

使用 `docker history` 查看镜像提交历史。



### 获取镜像

我们可以从 docker 仓库中查找并下载镜像。

> Docker 官方的镜像仓库地址：<https://hub.docker.com/> 

#### 检索镜像

- 登录 docker 镜像仓库的 web 页面，可以搜索自己想要的镜像，并可以查看镜像相关信息，如版本特性、使用说明等。

- 在客户端使用 `docker search` 命令搜索镜像，用法如下：

  ```bash
  docker search [OPTIONS] TERM
  ```

  参数：

  - `-f` ，`--filter` 按指定条件过滤输出结果
  - `--format` 使用 Go 模板格式化输出结果
  - `--limit` 限制最大搜索结果数量，默认 25
  - `--no-trunc` 不删减输出

  例如：检索 redis 镜像，执行命令 `docker search redis`：

  ```bash
  NAME                             DESCRIPTION                                     STARS               OFFICIAL            AUTOMATED
  redis                            Redis is an open source key-value store that…   8542                [OK]
  bitnami/redis                    Bitnami Redis Docker Image                      160                                     [OK]
  sameersbn/redis                                                                  80                                      [OK]
  grokzen/redis-cluster            Redis cluster 3.0, 3.2, 4.0, 5.0, 6.0           70
  rediscommander/redis-commander   Alpine image for redis-commander - Redis man…   46                                      [OK]
  kubeguide/redis-master           redis-master with "Hello World!"                32
  ```

  > 结果中有五个数据项：
  >
  > - `NAME` 镜像名
  > - `DESCRIPTION` 镜像描述，只显示一部分，如果需要看完整描述，可以加上参数 `--no-trunc` 
  > - `STARS` 获得的 star 数
  > - `OFFICIAL` 是否官方版本
  > - `AUTOMATED` 是否自动构建

#### 拉取镜像

在客户端可以使用 `docker pull` 或 `docker image pull` 从仓库中拉取镜像，使用方法说明：

```bash
docker pull [OPTIONS] NAME[:TAG|@DIGEST]
docker image pull [OPTIONS] NAME[:TAG|@DIGEST]
```

拉取镜像时需要指定镜像名，如拉取 redis 镜像： `docker pull redis`。可以指定版本，如果不指定版本，默认使用最新版本(latest)，如拉取 6.0.7 版本的 redis：`docker pull redis:6.0.7` 。

参数：

- `-a` , `--all-tags` 下载所有版本的镜像
- `--disable-content-trust` 跳过镜像校验，默认为 true
- `--platform` 指定平台
- `-q` , `--quiet` 禁止冗余输出



### 创建镜像

#### 通过提交容器创建镜像

使用 `docker commit` 命令可以将 docker 容器提交成为镜像。

使用 `docker image history` 命令查看镜像的提交历史。



#### 通过 Dockerfile 创建

Dockerfile 文件中描述了整个 docker 镜像的编译顺序、编译规则。

##### Dockerfile 语法

每一行都以一个关键字为行首，如果一行内容过长，它使用 `\` 把多行连接到一起。

###### `FROM` 指定最底层镜像

###### `MAINTAINER` 指定镜像创建者

###### `ENV` 设置环境变量

###### `RUN` 运行 shell 命令

如果有多条命令，可以使用 `&&` 连接。

###### `COPY` 拷贝文件

将编译机本地文件拷贝到镜像文件系统中。

###### `EXPOSE` 指定监听端口

###### `ENTRYPOINT` 容器启动后执行的命令

这个关键字与上述关键字不同，上述关键字都是在镜像编译时执行，这个关键字在创建镜像时不执行，要等到使用该镜像创建容器，容器启动后才会执行的命令。

##### 编译镜像

进入 Dockerfile 文件目录，使用 `docker build` 命令编译 Dockerfile ，通过 `-t` 选项给镜像指定名字（带版本号）。如：

```bash
docker build -t image_redis:v1.0
```

编译过程有九步，每一步对应 Dockerfile 的一个关键字，每执行完一步，都会生成一个临时镜像。



##### 注意事项

- 制作自己的应用镜像时，应尽量考虑使用相同的底层镜像，这样可以极大地降低后续维护的成本。

- 在选择基础镜像时，尽可能选择适合自己的基础镜像，也可以在已有的基础镜像上进行改造，提交新镜像作为自己项目的基础镜像。

- 基础镜像可以从 docker-hub 上寻找，如果没有合适的，就需要自己构建基础镜像。

  > 自定义基础镜像时，可以使用 **debootstrap** 工具来定制最小化的 Linux 基础镜像。



### 提交镜像

当镜像更新后，可以使用 `docker commit` 命令将修改内容提交，提交时更新镜像版本。这样就获得了新版本的镜像。

本地镜像提交后，可以使用 `docker push` 命令将镜像推送到远端仓库，供其他人拉取使用。



### 参考资料

- 李金榜. 循序渐进学Docker



### 总结

镜像是 docker 的基础，虽然官方仓库中有各种第三方的开源镜像供我们使用，可以满足基本的需求，但如果要深入使用 docker 来辅助开发、测试与实施，就需要了解镜像的概念与特性，学习维护镜像。