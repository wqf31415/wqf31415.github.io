---
title: Java内网开发攻略
tags:
  - java
  - 开发
  - maven
  - springboot
categories:
  - 技术
date: 2021-10-31 20:37:13
---

### 概述

在工作中，有时会遇到保密要求较高的项目，开发时不能连接互联网，会产生很多问题，带来许多不便。这篇文章总结了在没有外网的环境下开发 java 项目的一些经验，介绍了一些常见问题的解决方案，主要是离线环境下的 maven 环境、springboot 环境搭建。



![](http://blog-images.qiniu.wqf31415.xyz/coffee-beans.jpg)



<!-- more -->



### 离线环境

其实，在内网中开发最重要的问题就是环境问题，从环境安装到依赖的类库下载，都会有点不方便。

#### java

需要从公网下载好需要的 jdk 包，拷贝到内网进行安装，此外建议下载相同版本的 jre，方便项目部署时使用。



#### maven

Maven 是一个广泛使用的 java 项目构建工具，它能够帮我们管理复杂的项目依赖，但在没有公网的环境中，无法直接下载 maven 依赖包，需要手动维护。

这时我们需要一台能上网的电脑，在电脑上搭建 maven，然后创建一个maven 项目，引入项目需要的maven依赖，使用maven下载好所有依赖，然后把 maven 的本地仓库打包，拷贝到内网中。最后修改内网 maven 的本地仓库配置，指向拷贝进来的仓库路径，这样就可以愉快的开发了。

##### 快速下载maven依赖包

在断网开发场景中，下载公网资源往往只能到指定的开放电脑上进行，但这台电脑不一定有我们需要的 java 和 maven 环境，这时可以用下述方法快速搭建环境下载需要的依赖库。

- 下载 jre 压缩包：从Oracle官网下载 java 8 的 jre 压缩包，解压后新建系统环境变量 JAVA_HOME，指向jre根目录，不用安装。

- 下载 maven 压缩包：从 Apache maven 官网下载 maven 压缩包，解压，添加 bin 路径到系统环境变量 path 中，然后修改配置文件，添加阿里镜像源，提升下载速度。

- 创建 pom.xml：创建最简单的 maven 项目依赖文件，添加自己需要的依赖，依赖的信息可以从 maven 在线仓库 <https://mvn repository.com> 中搜索得到。

  ```xml
  <project>
  <groupId>xx</groupId>
  <artifactId>xx</artifactId>
  <version>x</version>
  <dependencies>
  <!-- 把要下载的依赖定义粘贴到这里 -->
  </dependencies>
  </project>
  ```

- 执行命令下载依赖：在pom.xml 目录中打开命令行执行命令: `mvn -f pom.xml dependency:copy-dependencies` ，等待依赖下载完成。

- 拷贝依赖包：将下载到本地的依赖文件打包，默认本地依赖保存路径是 `~/.m2` ，将其压缩打包后，传输到内网，使用时直接将其中内容解压，与内网原有依赖放在一起即可使用。

- 更新idea本地仓库索引：进入 idea，点击菜单栏 File ，点 `Settings...` 进入设计界面，进入 `Build, Execution, Deployment` - `Build Tools` - `Maven` - `Repositories`，在右侧选择本地仓库（Type为Local），点击 `Update`。

#### springboot

当我们使用 idea 创建 SpringBoot 项目时，idea 会访问 spring 官方提供的项目初始化网站 <https://start.spring.io/> 生成初始化的项目文件。在内网环境中，无法访问该网站，导致无法创建项目。

其实这个网站的是开源的，github 地址是：<https://github.com/spring-io/start.spring.io.git> 

我们可以把这个项目的源码拉下来，到内网中运行起来，然后修改 idea 创建 SpringBoot 项目的 Server URL，改成我们运行的地址。

但是有一个问题，当我们请求自己搭建的 start 服务创建项目时，start 服务会访问 spring 官网获取 SpringBoot 项目版本信息，地址是：<https://spring.io/project_metadata/spring-boot> ，内容类似下面的<small>(这个项目元信息会随着 SpringBoot 的版本更新而更新)</small>：

```json
{
    "id":"spring-boot",
    "name":"Spring Boot",
    "projectReleases":[
        {
            "version":"2.6.0-SNAPSHOT",
            "versionDisplayName":"2.6.0-SNAPSHOT",
            "current":false,
            "releaseStatus":"SNAPSHOT",
            "snapshot":true
        },
        {
            "version":"2.6.0-RC1",
            "versionDisplayName":"2.6.0-RC1",
            "current":false,
            "releaseStatus":"PRERELEASE",
            "snapshot":false
        },
        {
            "version":"2.5.7-SNAPSHOT",
            "versionDisplayName":"2.5.7-SNAPSHOT",
            "current":false,
            "releaseStatus":"SNAPSHOT",
            "snapshot":true
        },
        {
            "version":"2.5.6",
            "versionDisplayName":"2.5.6",
            "current":true,
            "releaseStatus":"GENERAL_AVAILABILITY",
            "snapshot":false
        },
        {
            "version":"2.4.13-SNAPSHOT",
            "versionDisplayName":"2.4.13-SNAPSHOT",
            "current":false,
            "releaseStatus":"SNAPSHOT",
            "snapshot":true
        },
        {
            "version":"2.4.12",
            "versionDisplayName":"2.4.12",
            "current":false,
            "releaseStatus":"GENERAL_AVAILABILITY",
            "snapshot":false
        },
        {
            "version":"2.3.12.RELEASE",
            "versionDisplayName":"2.3.12.RELEASE",
            "current":false,
            "releaseStatus":"GENERAL_AVAILABILITY",
            "snapshot":false
        }
    ]
}
```

为了能够创建项目，我们需要让内网的 start 服务能够获取到这个元信息。首先访问项目元信息的地址，获取信息数据。

然后可以修改电脑 hosts 文件，让 `spring.io` 域名指向本地，然后在本地使用 nginx 让请求 `/project_metadata/spring-boot` 返回之前获取的元信息数据。这样就可以方便的创建项目了。

或者修改 `start.spring.io` 项目的配置，修改 `initializr.env.spring-boot-metadata-url` 配置，指向本地能够返回项目元信息的请求地址即可。

### 遇到的问题

#### 打包时 maven 总是从远端仓库下载依赖

离线环境中，maven 依赖需要在公网环境下载好，再拷贝到开发机，有时会出现明明本地仓库有依赖包，在idea开发中运行也正常，但一到打包时，maven就从远端下载依赖，导致打包失败。

导致这种现象的原因是maven将依赖包的远端仓库源信息记录在依赖目录下的 `_remote.repositories` 文件中，如果源头不存在或不存在依赖的jar包，maven 在 resolve 时就会失败，导致项目构建失败。删除这个文件后，maven将不再从远程仓库执行这个操作，问题得以解决。

解决办法：删除依赖目录下的 `_remote.repositories` 文件

> Tips: 可以写个简单的程序遍历仓库路径下所有文件，将  `_remote.repositories` 文件删除。

```java
public class App {
  private static final String TARGET_FILE_NAME = "_remote.repositories";
  public static void main(String[] args){
    // 待处理的仓库目录
    String basePath = "D:/develop/.m2/repo";
    File pth = new File(basePath);
    if (path.exists()){
      handleFile(path, "|");
    } else {
      System.out.println("path ["+basePath+"] not exist");
    }
  }
  
  private static void handleFile(File file, String s){
    System.out.println(s+file.getName());
    if (file.isDirectory()){
      File fs = file.listFiles();
      for(File f: fs){
        handleFile(f, s+"  ");
      }
    } else {
      if(TARGET_FILE_NAME.equals(file.getName())){
        file.delete();
      }
    }
  }
}
```


### 总结

断网开发在一些银行项目、国家项目或科技项目中比较常见，其实也不用太担心，只要解决了开发环境问题就可以了。
