---
title: docker 容器管理
tags:
  - docker
categories:
  - 工具
date: 2020-08-24 09:03:32
---



### 概述

这篇文章介绍了 docker 中的容器的概念以及docker 容器的操作和应用。



### 什么是容器

docker 中的容器（container）是独立运行的一个或一组应用，以及它们的运行环境。



<!-- more --> 



### 容器的标识符

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



### 查询容器信息

使用 `docker inspect CONTAINER` 命令可以查询容器的所有信息，包括运行情况、存储位置、配置参数、网络配置等。

`docker inspect` 命令展示的信息很多，如果查询指定信息，可以添加 `-f` 使用 golang 的模板来提取指定信息。如查询容器的运行状态：

```bash
docker inspect -f {{. State.Status}} my-redis
```

我们可以使用 `docker logs` 命令来查看容器的日志，如果需要实时打印最新日志，可加上 `-f` 参数。

使用 `docker stats` 命令实时查询容器所占用的系统资源，如 CPU 使用率、内存、网络等。



### 容器内部命令

我们经常需要登录容器内部执行命令，可以使用 `docker exec 容器名 容器内执行的命令` ，如查看 `my-redis` 容器中启动了哪些进程：

```bash
docker exec my-redis ps aux
```

如果需要登录容器执行多条命令，可以加上 `-it` 参数，这样相当于以 root 身份登入了容器，在使用完后执行 `exit` 命令退出。



### 多容器管理

> Docker 倡导的是 `一个容器一个进程`，如果一个服务需要多个进程，就需要创建多个容器组成一个系统，相互分工和配合来对外提供完整的服务。