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

![](https://blog-images.qiniu.wqf31415.xyz/docker_whale_2.jpg)



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

![](https://blog-images.qiniu.wqf31415.xyz/docker_image_container_layer.png)

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

Dockerfile 是一个描述了 docker 镜像编译顺序、编译规则的脚本文件，是一个文本文件，跟 Makefile 的概念类似。

##### 示例：

这是一个最简单的 Dockerfile 示例，用来将一个打包好的 springboot 项目 jar 包构建成一个 docker 镜像。

```cmake
# 使用 openjdk8 镜像，添加 java 环境
FROM openjdk:8-jre-alpine
# 将打包后的项目文件添加到镜像中，并改名为 app.jar
ADD docker-demo-0.0.1-SNAPSHOT.jar app.jar
# 对外暴露的端口
EXPOSE 8080
# 启动时运行的命令
ENTRYPOINT ["java","-jar","/app.jar"]
```



##### Dockerfile 语法

每一行都以一个关键字为行首，如果一行内容过长，它使用 `\` 把多行连接到一起。以 `#` 开头表示单行注释。

dockerfile 语法是 `command argument argument ...` ，就是 `命令 参数 参数 ...` ，如要输出一句 `hello world` ：

```bash
RUN echo "hello world"
```

##### Dockerfile 内置命令

| 命令       | 功能                                                         | 是否必须 |
| ---------- | ------------------------------------------------------------ | -------- |
| FROM       | 指定基础镜像名称                                             | 是       |
| MAINTAINER | 指定镜像创建者，也可同时填写版本及其他备注信息               | 否       |
| RUN        | 执行指定 shell 命令（多条命令使用 ``），执行完成后将产生一个新文件层 | 否       |
| CMD        | 指定此镜像启动时默认执行命令                                 | 否       |
| LABEL      | 为镜像添加元数据，如版本号、构建日期                         | 否       |
| EXPOSE     | 指定镜像需要暴露的网络端口号                                 | 否       |
| ENV        | 添加环境变量                                                 | 否       |
| ADD        | 向镜像中添加新文件或新目录                                   | 否       |
| COPY       | 从编译主机向镜像复制文件                                     | 否       |
| ENTRYPOINT | 在镜像中设定默认执行的二进制程序                             | 否       |
| VOLUME     | 向镜像中挂载一个卷组                                         | 否       |
| USER       | 在镜像构建过程中切换到另一个用户                             | 否       |
| WORKDIR    | 设置此镜像后续操作的默认工作目录                             | 否       |
| ONBUILD    | 配置构建触发指令集                                           | 否       |

###### FROM

命令是 Dockerfile 命令中唯一一个必填命令，在有效的 Dockerfile 中，FROM 永远是第一个出现的命令。当在一个 Dockerfile 中构建多个镜像时，FROM 可以出现多次。



###### RUN

命令后面的命令都是由 `/bin/sh -C` 负责执行的，当镜像中没有 /bin/sh 时，需要使用 `RUN ["executable", "param1", "param2"]` 方式来执行镜像中的二进制程序。如使用 bash 来执行程序：`RUN ["/bin/bash", "-c", "hello"]` ，这里的参数会按照 JSON 字符串格式解析，因此只能使用双引号，不能使用单引号和其他符号。



###### CMD

设定的命令将作为容器启动时的默认执行命令，用法有三种：

- `CMD ["executable","param1","param2"]` 推荐用法

- `CMD ["param2","param2"]` 其中的参数将作为 ENTERPOINT 的默认参数使用` 
- `CMD command param1 param2` 将后面的命令作为 shell 命令执行，依靠 `/bin/sh -C` 执行

> <span style="background:#ffc">CMD 和 RUN 都是用于执行命令，但 RUN 是在镜像构建过程中执行的命令，CMD 只是设定好需要执行的命令，等到容器启动时才会真正执行。</span>

 

###### LABEL

使用键值对方式给镜像添加元数据信息，用法：

```
LABEL <key>=<value> <key2>=<vlaue2> ...
```

> 如果 value 中有空格，需要使用双引号包括。

可以一次性设置多个信息，也可以拆分成多个命令，但考虑到镜像文件层数限制，不建议这么做。



###### EXPOSE

设定镜像需要暴露的网络端口，在启动容器时需要使用 `-p` 或 `-P` 来使外部能够访问。用法：

```bash
EXPOSE <port> <port> ...
```



###### ENV

设置环境变量，用法：

```bash
ENV key value
ENV <key>=<value> <key>=<value> ...
```

> 第一种用法时，第一个字符串作为 key，后面的所有字符串作为 value。
>
> 第二种用法时，如果value中有空格，需要使用双引号包括，或添加 `\` 进行转义，如 `ENV myName="Zhang San" myFriend=Li\ Si`



###### ADD

将 src 标记的文件添加到镜像添加容器中 dest 标记的路径中取，src 标记的文件可以是本地文件、目录或远程 URL 链接。用法：

- `ADD <src>... <dest>` 
- `ADD ["<src>",... "<dest>"]` 这种方式添加的内容用双引号包括，所以可以用来处理有空格的文件路径。

> src 标记的是本地文件或目录，其相对路径是相对与 Dockerfile 所在目录的路径，可以使用通配符。添加文件时需要确认文件存在于 Dockerfile 目录。
>
> dest 是容器中的目录，如果这个目录不存在，当 ADD 命令执行时，将会在容器中自动创建此目录。dest 必须使用绝对路径，或相对与 WORKDIR 的相对路径。



###### COPY

用于向容器中指定路径下添加文件，在添加文件时也需要确认文件存在于 Dockerfile 目录中。用法：

- `COPY <src> ... <dest>` 
- `COPY ["<src>",... "<dest>"]` 可处理路径带空格的文件路径。

> src 、dest 的用法与 ADD命令 的相同。



###### ENTRYPOINT

用来设定容器运行时默认执行程序的命令。用法：

- `ENTRYPOINT ["executable","param1","param2"]` 官方推荐用法，可以指定执行的二进制程序和参数。
- `ENTRYPOINT command param1 param2` 命令将使用 `/bin/sh -C` 执行。

> CMD 指令和 ENTRYPOINT 指令都是为镜像指定容器启动后的命令，都可以指定 shell 或 exec 函数调用的方式执行命令，当存在多个 CMD 指令或 ENTRYPOINT 指令时，只有最后一个生效。
>
> 他们的差异是：
>
> - CMD 指令指定的容器启动时命令可被 docker run 指定的命令覆盖，而 ENTRYPOINT 指令指定的命令不能被覆盖，而是将 docker run 指定的参数当作 ENTRYPOINT 指定命令的参数。
> - CMD 指令可以为 ENTRYPOINT 指令设置默认参数，而且可以被 docker run 指定的参数覆盖。



###### VOLUME

在容器内部创建指定名称的挂载点。用法：

```bash
VOLUME ["/data"]
```

> 如果在 Dockerfile 中已经声明了某个挂载点，那么以后对此挂载点中文件的操作将不会生效，因此，一般只会在 Dockerfile 的结尾处声明挂载点。



###### USER

切换用户身份，执行完成后，之后的所有命令将会使用新用户身份来执行。用法：

```
USER daemon
```



###### WORKDIR

切换当前工作目录，切换工作目录将会影响后续的 RUN、CMD、ENTRYPOINT、COPY 和 ADD 指令中使用的路径。

```
WORKDIR /path/to/workdir
```



###### ONBUILD

创建触发命令基，由 ONBUILD 创建的命令集在当前 Dockerfile 执行过程中不会触发，当此镜像被其他镜像当作基础镜像使用时，将会触发执行。

##### 编译镜像

进入 Dockerfile 文件目录，使用 `docker build` 命令编译 Dockerfile ，通过 `-t` 选项给镜像指定名字（带版本号）。如：

```bash
docker build -t image_redis:v1.0 .
```

> 注意这个命令要指定编译的路径，最后面的 `.` 表示当前路径，不能忽略。

编译过程有九步，每一步对应 Dockerfile 的一个关键字，每执行完一步，都会生成一个临时文件层，当所有命令都执行成功后，docker 会记录执行过程中用到的所有文件层，并用一个名字来标记这一组文件层。这一组文件层就是镜像。



##### 注意事项

- 制作自己的应用镜像时，应尽量考虑使用相同的底层镜像，这样可以极大地降低后续维护的成本。

- 在选择基础镜像时，尽可能选择适合自己的基础镜像，也可以在已有的基础镜像上进行改造，提交新镜像作为自己项目的基础镜像。

- 基础镜像可以从 docker-hub 上寻找，如果没有合适的，就需要自己构建基础镜像。

  > 自定义基础镜像时，可以使用 **debootstrap** 工具来定制最小化的 Linux 基础镜像。

- docker 镜像的文件层数是有上限的，如果超过上限将会导致构建失败，因此应该尽量将多个命令放到一起执行，减少文件层数。



### 提交镜像

当镜像更新后，可以使用 `docker commit` 命令将修改内容提交，提交时更新镜像版本。这样就获得了新版本的镜像。

本地镜像提交后，可以使用 `docker push` 命令将镜像推送到远端仓库，供其他人拉取使用。



### 参考资料

- 李金榜. 循序渐进学Docker
- 张涛. Docker全攻略
- Docker学习之Dockerfile:CMD与ENTRYPOINT： <https://blog.csdn.net/wuce_bai/article/details/88997725> 



### 总结

镜像是 docker 的基础，所有容器都是基于镜像创建的。虽然官方仓库中有各种第三方的开源镜像供我们使用，可以满足基本的需求，但如果要深入使用 docker 来辅助开发、测试与实施，就需要了解镜像的概念与特性，学习维护镜像。