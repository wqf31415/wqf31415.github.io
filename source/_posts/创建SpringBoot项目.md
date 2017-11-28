---
title: 创建SpringBoot项目
date: 2017-11-27 22:52:41
tags:
- java
- spring
- springboot
categories:
- 技术
---

## 什么是 SpringBoot ?
> 官网：[http://projects.spring.io/spring-boot/](http://projects.spring.io/spring-boot/ "springboot官网")

简单来说，SpringBoot 的出现是为了简化Spring项目的创建、运行、调试、部署过程，boot的意思是启动，springboot 并不是一个新的框架，它只是spring的一个封装，从根本上讲就是一些库的集合，帮助开发者快速构建java web项目，项目里面还是使用spring框架，所以Spring能做的，SpringBoot也能做，而且做的更好。

在初学Spring的时候，我们在写项目时有大量的xml要编写，随着快速开发的流行，这种方式已经不能满足需要了，springboot的出现帮我们简化了项目配置，同时提供了很多注解，让我们编码也变得简单了。传统Spring 的xml配置文件被转化成 java config，直接利用@Autowire注解注入Bean，而环境变量中的 properties、xml文件集中到一个application.yml中。同时，springboot也使项目部署变得简单，传统的Spring项目需要外部的tomcat容器来运行，而在springboot中以及集成了tomcat，我们将项目打包成一个jar包，直接通过 `java -jar xxx.jar` 就可以运行项目，这也方便后续使用docker。

## 创建 SpringBoot 项目
### 前提条件
**java开发环境** springboot 是Javaweb开发框架，所以java开发环境是必要的，从[Oracle官网](http://www.oracle.com/)上下载java1.8的安装包，安装到计算机上，并配置好环境变量。
**maven工具** 利用maven下载管理项目中需要的依赖资源，从 [maven官网](http://maven.apache.org/) 下载maven，解压到本地，将bin目录配置到环境变量 path 中，方便使用，为了提升依赖下载速度，建议配置阿里镜像。
**开发工具-IDEA** 我们利用 IntelliJ IDEA 工具来创建spring boot 项目，所谓“工欲善其事必先利其器”，我任务IDEA用来开发java是非常好用的工具。
**版本控制-Git** （可选）在开发过程中版本控制工具的使用实在太广泛了，因为现在的软件开发很少是单人独立开发，多是团队协作开发，用Git来管理每个人负责的模块是非常必要的。

<!-- more -->

### 创建 SpringBoot 项目
#### 用IDEA创建maven项目框架
- 打开IDEA，点击 **Create New Project** 创建项目
![](http://okbn8yrzu.bkt.clouddn.com/spring_boot_project_create_01.png "创建项目")

- 选择maven项目，Project SDK 选择 java1.8（如果没有，点击 **New...** 选择java安装路径），点击 **Next**
![](http://okbn8yrzu.bkt.clouddn.com/spring_boot_project_create_02.png "选择maven项目和java版本")

- 填入 GroupId 和 ArtifactId，点击 **Next**
![](http://okbn8yrzu.bkt.clouddn.com/spring_boot_project_create_03.png "填写项目信息")
> GroupId 一般是公司域名倒序，如域名为 xxx.com，GroupId 就写com.xxx。ArtifactId 为模块名，也就是项目名。

- 填写项目名和存储路径，点击 **Finish**
![](http://okbn8yrzu.bkt.clouddn.com/spring_boot_project_create_04.png "填写项目名称及存储路径")

- 完成项目创建，这是一个maven项目，目前还只有项目骨架
![](http://okbn8yrzu.bkt.clouddn.com/spring_boot_project_create_05.png "")


#### 添加 SpringBoot 的依赖
- 将springboot 最基础的依赖包加入到maven项目的 **pom.xml** 中
``````xml
<parent>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-parent</artifactId>
    <version>1.5.8.RELEASE</version>
</parent>
<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>
``````

- 用IDEA下载需要的包，将自动导入springframework的包，以及tomcat、日志等web项目需要的包
![](http://okbn8yrzu.bkt.clouddn.com/spring_boot_project_create_06.png "导入的包") 


#### 编写项目逻辑代码
- 写一个简单的 controller 用来测试，在 src/main/java 下新建一个包 **hello** ，在其中新建一个java类 **SampleController**，其中代码如下：
``````java
package hello;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * Created by wqf31 on 2017/11/27.
 */
@SpringBootApplication
@RestController
public class SampleController {

    @RequestMapping("/")
    public String home(){
        return "hello springboot!";
    }

    public static void main(String[] args) {
        SpringApplication.run(SampleController.class,args);
    }
}
``````

#### 运行项目
- 在IDEA中点击 **Run** 菜单中的 **Edit Configuration**，进入配置编辑界面
![](http://okbn8yrzu.bkt.clouddn.com/spring_boot_project_create_07.png "点击 Edit Configuration")

- 点击左上角的 “**+**”，选择 **SpringBoot**
![](http://okbn8yrzu.bkt.clouddn.com/spring_boot_project_create_08.png "新增一个SpringBoot配置项目")

- Main Class 选择刚才创建的类，点击 **OK** 完成配置
![](http://okbn8yrzu.bkt.clouddn.com/spring_boot_project_create_09.png "选择刚才创建的类")

- 运行项目，点击IDEA工具栏中的运行图标
![](http://okbn8yrzu.bkt.clouddn.com/idea_run.png "运行项目")

- 运行结果，如果项目启动，并在控制台打出如下日志信息，说明已经成功启动
![](http://okbn8yrzu.bkt.clouddn.com/spring_boot_project_create_10.png "项目启动成功")

- 访问 [http://localhost:8080](http://localhost:8080 ) ，页面显示 hello springboot! 


### 项目打包

