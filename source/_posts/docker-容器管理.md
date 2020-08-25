---
title: docker 容器管理
tags:
  - docker
  - 工具
categories:
  - 工具
date: 2020-08-24 09:03:32
---



### 概述

这篇文章介绍了 docker 中的容器的概念以及docker 容器的操作和应用。

![](http://blog-images.qiniu.wqf31415.xyz/docker_container.jpg)



### 什么是容器

docker 中的容器（container）是独立运行的一个或一组应用，以及它们的运行环境。



<!-- more --> 



### 容器管理

#### 容器的标识符

docker 会给每个创建的容器分配唯一的 ID，后续对容器的操作都需要使用这个容器 ID。容器ID 默认为 128 位，大多数情况下，使用前 16 位就能保证在本机中的唯一性，所以我们一般使用简略形式的容器 ID。

使用 `docker ps` 查看运行的容器，其结果中将会展示缩略的容器ID，如需查看完整的容器 ID，需要使用命令：

```bash
docker ps --no-trunc
```

有了容器 ID ，就可以对容器进行操作了，如停止容器：

```bash
docker stop container-id
```

启动容器：

```bash
docker start container-id
```

由于容器 ID 难以记忆，所以建议在创建容器时，使用 `--name` 为容器取一个别名，使用别名代替容器 ID 来操作容器。



#### 查看容器

使用 `docker ps` 可以查看正在运行的容器，如果需要查看所有容器(包括未运行的)，可以增加参数 `-a` 如：

```bash
docker ps -a
```

此外，还可以使用 `docker container ls` 查看正在运行的容器，使用 `docker container ls -a` 查看所有容器。



#### 查询容器信息

使用 `docker inspect CONTAINER` 命令可以查询容器的所有信息，包括运行情况、存储位置、配置参数、网络配置等。

`docker inspect` 命令展示的信息很多，如果查询指定信息，可以添加 `-f` 使用 golang 的模板来提取指定信息。如查询容器的运行状态：

```bash
docker inspect -f {{.State.Status}} my-redis
```

使用 `docker logs` 命令可以查看容器的日志，如果需要实时打印最新日志，可加上 `-f` 参数。如：

```bash
docker logs -f my-redis
```

使用 `docker stats` 命令实时查询容器所占用的系统资源，如 CPU 使用率、内存、网络等。



#### 容器内部命令

我们经常需要登录容器内部执行命令，可以使用 `docker exec 容器名 容器内执行的命令` ，如查看 `my-redis` 容器中启动了哪些进程：

```bash
docker exec my-redis ps aux
```

如果需要登录容器执行多条命令，可以加上 `-it` 参数，这样相当于以 root 身份登入了容器，在使用完后执行 `exit` 命令退出。

如使用 `my-redis` 容器中的 bash ：

```bash
docker exec -it my-redis bash
```

如使用 `my-redis` 容器中的 redis-cli 连接其他 redis 服务(IP为 192.168.0.11)：

```bash
docker exec -it my-redis redis-cli -h 192.168.0.11
```



#### 在本地和容器间拷贝文件

使用 `docker cp` 命令可以在本地和容器之间拷贝文件，如把本地的 test.txt 文件拷贝到 `my-redis` 容器中的 `/data` 目录：

```bash
docker cp ./test.txt my-redis:/data
```

或将 `my-redis` 容器中 `/data/dump.rdb` 文件拷贝到本地：

```bash
docker cp my-redis:/data/dump.rdb ./
```

把文件拷贝到容器中后，可以使用 `docker exec -it my-redis bash` 进入容器，查看 `/data` 下的文件。



#### 更多操作

使用 `docker container` 可以操作容器，如

- `docker container start` 启动容器
- `docker container stop` 关闭正在运行的容器
- `docker container kill` 杀死正在运行的容器

更多操作可以使用 `docker container --help` 查看帮助信息。



### 多容器管理

> Docker 倡导 `一个容器一个进程`，如果一个服务需要多个进程，就需要创建多个容器组成一个系统，相互分工和配合来对外提供完整的服务。

如果两个容器之间需要数据交互，在同一主机中，可以在使用 `docker run` 命令运行容器时添加 `--link` 选项来建立容器间的互联。需要注意关联容器的启动顺序，连接的目标容器必须事先创建并启动，在运行的时候被连接的容器需要先启动，而关闭时被关联的容器要后关闭。

#### Docker Compose

> GitHub项目地址: <https://github.com/docker/compose> 

Docker Compose 是官方提供的容器编排工具，用于编排和运行多容器的应用。它使用 yml 定义一组关联的容器，这组容器会根据配置模块中的 `--link` 等参数，对启动的优先级自动排序，简单执行一条 `docker-compose up` ，就可以把同一个服务中的多个容器依次创建和启动。

#### 安装 Docker Compose

Ubuntu 中可以使用 apt 工具安装：

```bash
sudo apt install docker-compose
```

或：

```bash
sudo curl -L "https://github.com/docker/compose/releases/download/1.26.2/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose
```

安装完成后，使用 `docker-compose version` 查看版本：

```bash
docker-compose version
```

结果：

```
docker-compose version 1.26.2, build eefe0d31
docker-py version: 4.2.2
CPython version: 3.7.4
OpenSSL version: OpenSSL 1.1.1c  28 May 2019
```

#### 使用 Docker Compose

##### 编写配置

如下为 wordpress 的配置文件，命名为 `docker-compose.yml` 或 `docker-compose.yaml` 。

```yaml
version: '3.1'

services:
  wordpress:
    image: wordpress
    restart: always
    ports:
      - 8080:80
    environment:
      WORDPRESS_DB_HOST: db
      WORDPRESS_DB_USER: exampleuser
      WORDPRESS_DB_PASSWORD: examplepass
      WORDPRESS_DB_NAME: exampledb
    volumes:
      - wordpress:/var/www/html

  db:
    image: mysql:5.7
    restart: always
    environment:
      MYSQL_DATABASE: exampledb
      MYSQL_USER: exampleuser
      MYSQL_PASSWORD: examplepass
      MYSQL_RANDOM_ROOT_PASSWORD: '1'
    volumes:
      - db:/var/lib/mysql

volumes:
  wordpress:
  db:
```

> 如上配置中

##### 启动

进入存放配置的目录，执行 `docker-compose up` 即可运行服务，默认使用当前目录下的 `docker-compose.yml` 配置文件启动，也可以使用 `-f` 参数指定配置文件。如：

```bash
docker-compose -f my-wordpress.yml up
```

如果用到的镜像不存在，将会从 docker 仓库中下载需要的镜像，随后将在前台启动容器，可以另外打开一个终端使用 `docker ps` 查看运行的容器，结果如下：

```
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS              PORTS                    NAMES
8555cf46e4bd        mysql:5.7           "docker-entrypoint.s…"   2 minutes ago       Up 2 minutes        3306/tcp, 33060/tcp      my-wordpress_db_1
38cf4bfc5d85        wordpress           "docker-entrypoint.s…"   2 minutes ago       Up 2 minutes        0.0.0.0:8080->80/tcp     my-wordpress_wordpress_1
```

访问 http://localhost:8080 即可进入 wordpress 界面。

##### 运行与停止服务

进入配置文件目录，使用 `docker-compose stop` 停止正在运行的服务，如果配置文件名不是默认的 `docker-compose.yml` ，需要使用 `-f` 参数指定配置文件，如：

```bash
docker-compose -f my-wordpress.yml stop
```

> 停止服务后，该服务依赖的所有容器都将会关闭。

在配置文件目录中使用 `docker-compose start` 启动服务，同样可以使用 `-f` 参数指定配置文件，如：

```bash
docker-compose -f my-wordpress.yml start
```

#### 删除服务

使用 `docker-compose down` 命令停止并删除由 `docker-compose up` 创建的容器、网络、数据、镜像。可使用 `-f` 参数指定配置文件，如：

```bash
docker-compose -f my-wordpress.yml down
```

> 默认移除的内容包括配置文件中创建的容器、网络，可以增加参数移除镜像和数据卷。

#### 注意

使用 Docker Compose 可以按配置的依赖顺序启动和停止容器，但如果是依赖容器中的某个进程，虽然该容器已经蹄冻，但被依赖的这个进程启动速度很慢，Docker Compose 就无能为力了，需要自行添加一些判断等待和重试的机制。

#### 其他命令

Docker Compose 还有很多命令用来操作服务，如：

- `docker-compose build` 构建或重新构建服务
- `docker-compose restart` 重启服务
- `docker-compose kill` 杀死容器
- `docker-compose pause` 暂停服务
- `docker-compose unpause` 恢复暂停的服务

更多命令可使用 `docker-compose --help` 查看帮助信息。



### 总结

容器就是我们使用 docker 运行的程序，对容器的操作是最常用的，对与单个容器的操作可以使用 `docker container` 的命令，对于多容器服务可以使用 `docker-compose` 来操作。