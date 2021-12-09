---
title: 搭建Redis集群
tags:
  - redis
categories:
  - 技术
date: 2021-08-27 14:29:37
---

### 概述

这篇文章主要介绍了 Redis 集群相关的技术概念，以及搭建 Redis 集群的方法。



### 关于 Redis 集群

Redis 集群是一种服务端分片技术，在多个 Redis 节点间共享数据。

集群功能在 3.0 版本开始正式提供。

Redis 集群没有使用一致性 Hash，而是采用 slot（槽）的概念，共可分为 16384 个槽，每个节点分配一些槽，新增节点时会将原有节点上的一些槽分给新节点，删除节点时，需要先把槽移到其他节点，才能删除。

工作时，请求发送到任意节点，接收到请求的节点会将查询节点信息，然后将请求发送到正确的节点上执行。



<!-- more -->

### 基础概念

#### 哈希槽

在 Redis 集群中没有使用一致性 hash，而是引入了哈希槽的概念。

一个 Redis 集群共有 16384 个哈希槽，每个 key 通过 CRC16 校验后对 16384 取模来决定放置哪个槽，集群中每个节点负责一部分哈希槽。新增节点时将现有节点中部分哈希槽分配到新节点上，删除节点时则需要先将其中的哈希槽移到其他节点上，然后再删除该节点。



#### 主从复制

为了保证部分节点失败或大部分节点无法通信时集群仍然可用，集群中使用主从复制模型，每个节点都会有N-1个从节点。

在集群中其中某个主节点失败了，集群会从其从节点中选举一个作为主节点继续服务，如果某一部分的主节点和从节点全部失效，集群会因为缺少这部分哈希槽而不可用。



#### 一致性保证

Redis 并不能保证数据的强一致性，意味着实际集群在特定条件下可能会丢失写操作：

- 集群使用了异步复制，主节点对命令的复制工作发生在返回命令回复之后，这样做是为了提升命令处理速度。
- 集群出现网络分区，一个客户端与至少包括一个主节点在内的少数实例被孤立，集群重新选举了主节点，那么客户端写入孤立主节点的数据将会丢失。



### 搭建 Redis 集群

#### 服务器搭建

Redis 集群运行至少需要 3 个节点，官方建议为最基础的 Redis 集群创建三主三从共 6 个节点。



##### 编译 Reids

从 [Redis 官网](https://redis.io/download)下载源码包，这里示例下载的版本是 `6.2.5` ，下载完成后得到压缩文件 `redis-6.2.5.tar.gz`，将其解压出来：

```bash
tar -zxf redis-6.2.5.tar.gz
```

解压后得到目录 `redis-6.2.5` ，进入该目录，然后进行编译：

```bash
cd redis-6.2.5
make
```

编译完成后，在 `src` 目录下可以找到我们需要的 `redis-server` 和 `redis-cli` 。



##### 创建配置文件

为了测试方便，仅创建最简单的配置文件，配置项如下：

```lua
port 7000
cluster-enabled yes
cluster-config-file nodes.conf
cluster-node-timeout 5000
appendonly yes
```

> 配置说明：
> 
> _port_ 服务端口
>
> _cluster-enabled_ 是否允许集群服务
>
> _cluster-config-file_ 集群配置文件，程序启动后将自动创建，默认为 `nodes.conf` 
>
> _cluster-node-timeout_ 集群节点超时时间，单位：ms
>
> _appendonly_ 是否仅使用追加模式，开启持久化

为了创建集群需要启动 6 个 Redis 服务，为每个服务创建一个配置文件。先创建 6 个目录，按服务端口命名，分别是 `7000`、`7001`、`7002`、`7003`、`7004`、`7005`：

```bash
mkdir 7000 7001 7002 7003 7004 7005
```

将配置文件复制一份到每个目录中，配置文件全命名为 `redis.conf`，并将端口 `port` 修改成和目录对应的值。



##### 启动 Redis 程序

将编译出来的 `redis-server` 文件分别拷贝一份到之前创建的 6 个目录中，分别进入目录中启动 Redis，如：

```bash
cd 7000
./redis-server ./redis.conf
```

> 这里是在前台启动 Redis，所以需要开启 6 个终端，分别启动一个服务。建议使用 tmux 在同一个终端中开启 6 个会话来启动服务，操作方式：
>
> ```bash
> tmux new -s node1
> cd 7000
> ./redis-server ./redis.conf
> ```
>
> 运行起来后按 <kbd>Ctrl</kbd> + <kbd>b</kbd> ，然后按 <kbd>d</kbd> ，隐藏会话，然后创建 6 个会话，分别启动一个服务。



##### 创建集群

使用 `redis-cli` 工具创建集群：

```bash
./redis-cli --cluster create 127.0.0.1:7000 127.0.0.1:7001 127.0.0.1:7002 127.0.0.1:7003 127.0.0.1:7004 127.0.0.1:7005 --cluster-replicas 1
```

> 参数说明：
>
> _--cluster_ 使用集群功能
>
> _create_ 集群创建，后面的是各个节点信息，`ip:port` 
>
> _--cluster-replicas_ 集群副本，`1` 表示为每个节点创建一个从节点
>
> 注意：老版本的 Redis 用的是 `redis-trib.rb` 来创建集群，新版本中创建集群的功能全都集成到了 `redis-cli` 中。

执行命令后，将会给每个节点编写配置文件，会打印出预设的配置出来，如果觉得没问题，可以输入 `yes` ，将配置应用到集群中，让各个节点进行通信。执行结果：

![](http://blog-images.qiniu.wqf31415.xyz/redis_cli_create_cluster.png)



##### 测试

使用 `redis-cli` 连接集群进行简单测试：

```bash
redis-cli -c -p 7000
```

连接到端口 `7000` 的 redis 节点，使用 `set` 命令设置值，会自动重定向到 `7002` 的节点，使用 `get` 也能正确获取到值，说明集群运行正常。

![](http://blog-images.qiniu.wqf31415.xyz/redis_cli_test_cluster.png)



#### create-cluster 脚本搭建

Redis 提供了一个创建集群的脚本（`create-cluster`），使用这个脚本可以快速启动多个集群模式的 Redis 实例，并快速创建集群。在编译 Redis 源码后，脚本在 `utils/create-cluster/` 目录下，文件名为 `create-cluster`。只需执行下述命令，即可快速创建一个 6 节点（3主3从）的 Redis 集群。

##### 启动 Redis 实例

```bash
./create-cluster start
```

默认将创建端口从 `30001` 开始的 6 个集群模式的 Redis 实例。

![](http://blog-images.qiniu.wqf31415.xyz/script_start_cluster.png)



##### 创建集群

```bash
./create-cluster create
```

创建集群，会将预设的主从分配方式打印出来，确认没问题输入 `yes` 。

![](http://blog-images.qiniu.wqf31415.xyz/script_create_cluster.png)



##### 关闭集群

```bash
./create-cluster stop
```

关闭集群中所有实例。

![](http://blog-images.qiniu.wqf31415.xyz/script_stop_cluster.png)



##### 注意事项

使用 `create-cluster` 时，可以自行修改脚本，设置要启动的起始端口、实例数、从节点数等。



#### Docker 搭建

##### Docker 基础

Redis 的官方 Docker 仓库地址：<https://hub.docker.com/_/redis> 

使用 Docker 运行 Redis 集群时，需要使用外部配置文件启动 Redis 容器，方式如下：

```bash
docker run -v /myredis/conf:/usr/local/etc/redis --name myredis -d redis redis-server /usr/local/etc/redis/redis.conf
```

> 命令解析：
>
> `docker run` 是 docker 运行容器的命令
>
> `-v /myredis/conf:/usr/local/etc/redis` 是指定路径映射，将本机 `/myredis/conf` 目录映射为容器中的 `/usr/local/etc/redis` 
>
> `--name myredis` 是为运行的容器命名为 `myredis` 
>
> `-d` 是让容器在后台运行
>
> `redis` 是要运行的镜像，当前没有指定版本，则默认使用最新版，如需指定版本可在后面加冒号和版本号，如 `redis:6.2.5-alpine` 
>
> `redis-server /usr/local/etc/redis/redis.conf` 是容器启动命令，指定容器使用配置文件 `/usr/local/etc/redis/redis.conf` 启动，由于指定了目录映射，实际使用本地 `/myredis/conf/redis.conf` 启动



##### 编写配置文件

创建6个目录，以运行端口命名，分别是: `7000`、`7001`、`7002`、`7003`、`7004`、`7005` 。在目录中创建一份配置文件，内容如下所示，修改端口配置：

```lua
port 7000
cluster-enabled yes
cluster-config-file nodes.conf
cluster-node-timeout 5000
appendonly yes
```


##### 启动容器

使用上一步创建的本地配置文件，运行 redis 容器：

```bash
docker run -v /root/projects/docker-redis-cluster/7000:/usr/local/etc/redis --name redis-node-1 --privileged=true -d redis redis-server /usr/local/etc/redis/redis.conf
```

注意需要将 `-v` 的参数修改成自己的配置存储路径，并修改容器命名，容器名冲突会无法启动。

> 如果启动容器失败，可使用命令 `docker logs redis-node-1` 查看错误日志，如果出现权限错误，如：
>
> ```
> Fatal error, can't open config file '/usr/local/etc/redis/redis.conf': Permission denied
> ```
>
> 解决方法：
>
> 方法一 可以给容器增加特权，在启动命令中增加参数 `--privileged=true` ，完整命令如下：
>
> ```bash
> docker run -v /root/projects/docker-redis-cluster/7000:/usr/local/etc/redis --name redis-node-1 --privileged=true -d redis redis-server /usr/local/etc/redis/redis.conf
> ```
>
> 方式二 临时关闭selinux
>
> ```bash
> setenforce 0
> ```



##### 启动集群

使用 redis-cli 创建并启动集群。

要启动集群需要先知道各个节点的地址，使用 `docker inspect` 命令获取容器的地址：

```bash
docker inspect -f {{.NetworkSettings.Networks.bridge.IPAddress}} redis-node-1
```

我这里获取到的节点地址和端口如下：

| 地址       | 端口 |
| ---------- | ---- |
| 172.17.0.4 | 7000 |
| 172.17.0.5 | 7001 |
| 172.17.0.6 | 7002 |
| 172.17.0.7 | 7003 |
| 172.17.0.8 | 7004 |
| 172.17.0.9 | 7005 |

然后使用 redis-cli 启动集群：

使用 `docker exec` 命令打开某一节点的 bash：

```bash
docker exec -it redis-node-1 bash
```

创建并启动集群：

```bash
redis-cli --cluster create 172.17.0.4:7000 172.17.0.5:7001 172.17.0.6:7002 172.17.0.7:7003 172.17.0.8:7004 172.17.0.9:7005 --cluster-replicas 1
```

![](http://blog-images.qiniu.wqf31415.xyz/docker_create_redis_cluster.png)



##### 测试

在容器的 bash 中连接集群：

```bash
redis-cli -c -p 7000
```

然后使用 set 插入键值对，会看到重定向到不同的节点，说明集群运行正常。



##### 注意事项

上述使用 docker 创建的集群中节点地址是 docker 分配的，如果客户端和集群不在同一个网络中，就无法访问。

解决办法：

使用 `host` 网络模式启动节点容器，让容器和主机共享网络；并且开启端口映射，可以在外部访问。启动容器命令如下：

```bash
docker run -v /root/projects/docker-redis-cluster/7000:/usr/local/etc/redis --name redis-node-1 --p rivileged=true --net host -p 7000 -d redis redis-server /usr/local/etc/redis/redis.conf
```

> 与之前的启动命令相比，增加了参数 `--net host` 用于指定网络模式为 `host`，增加了参数 `-p 7000` 用于开放容器端口的访问。

需要注意的是，这种方式启动容器后，容器的地址即为本机地址，创建集群时直接使用本地地址即可，无需使用 `docker inspect` 命令查看。



### 参考资料

- REDIS cluster-tutorial -- Redis中文资料站: <http://www.redis.cn/topics/cluster-tutorial.html> 
- Redis cluster tutorial – Redis: <https://redis.io/topics/cluster-tutorial> 
- 基于Docker的Redis集群搭建: <https://www.cnblogs.com/niceyoo/p/13011626.html> 

