---
title: docker 仓库管理
tags:
  - docker
  - 工具
categories:
  - 工具
date: 2020-09-12 20:09:51
---

### 概述

这篇文章讲解了 docker 的相关概念，使用 docker 官方仓库管理镜像，搭建私有的 docker 仓库。

![](https://blog-images.qiniu.wqf31415.xyz/docker_whale.jpg)



### 什么是docker仓库

Docker 仓库用于存储镜像，是镜像分发、部署的关键，概念类似于 maven 仓库和 git 仓库。



<!-- more -->



### 使用仓库

在实际场景中，由开发或运维人员制作应用程序镜像，然后上传到镜像仓库，需要使用时直接从仓库中拉取镜像来运行。

相关命令：

- `docker search` 从仓库中检索镜像

- `docker push` 推送镜像到仓库
- `docker pull` 从仓库拉取镜像
- `docker login` 登录仓库



### 官方仓库

Docker 官方维护了一个共有仓库 Docker Hub：<https://hub.docker.com/> ，docker 默认使用官方仓库，从官方仓库中搜索和拉取镜像不需要登录账户。如果需要上传和分享自己的镜像，就需要登录 Docker Hub 账户。



### 国内仓库

在国内使用 Docker 官方仓库可能受网速影响较大，此时，我们可以修改配置使用国内的镜像仓库，如使用网易的镜像源：

修改 docker 配置文件 `/etc/docker/daemon.json` ，添加内容：

```json
"registry-mirrors":["http://hub-mirror.c.163.com"]
```

国内一些云平台提供了 docker 镜像仓库服务，如：

- 阿里云：<https://www.aliyun.com/> 
- 网易数帆：<https://www.163yun.com/> 



### 私有仓库

使用官方仓库也可以上传私有镜像，如果应用程序的保密性要求较高或处于封闭的网络环境，则可以选择创建自己的私有仓库。

Docker 官方提供了 **docker-registry** 组件用于创建私有镜像仓库。

#### 使用镜像运行仓库

可以使用官方提供的 docker-registry 镜像来运行仓库，如：

```bash
docker run -p 5000:5000 registry
```



#### 使用 apt 工具安装仓库

在 Ubuntu 环境下使用 apt 安装 docker-registry：

```
sudo apt install docker-registry
```



#### 仓库配置

默认情况下，docker-registry 使用 `config_sample.yml` 进行各种配置，rpm 方式则使用 `/etc/docker-registry.yml`  。配置文件提供了不同的模板，可以针对不同的环境选择不同的模板。



#### 仓库安全

目前 docker-registry 没有提供安全认证，所有知道 URL 的人都可以上传镜像，为了防止安全问题，可以使用 Nginx 构建一个带认证功能的私有仓库。



### 参考资料

- Docker 国内仓库和镜像：<https://www.cnblogs.com/wushuaishuai/p/9984228.html> 
- Docker 使用国内镜像仓库： <https://blog.csdn.net/qq_32510597/article/details/105873846> 



### 总结

团队协同使用 docker 时，必然需要用仓库来管理和分享镜像，一般情况下使用官方仓库或国内云平台商家提供的云仓库服务就可以满足需求。如果对资源保密性要求较高，则需要自己搭建私有的 docker 仓库，对于私有仓库需要注意安全相关配置。