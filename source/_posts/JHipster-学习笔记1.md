---
title: JHipster 学习笔记1
date: 2017-04-25 13:58:44
tags:
- JHipster
- java
- web
categories:
- 技术
---

> 摘要：初次接触 JHipster ，认识它是什么，并创建一个 demo 项目来体验一下。

### JHipster 是什么？能吃吗？
#### 下定义
> 根据官方自己的描述：JHipster就是一个用来创建 Spring Boot - Angular 项目的 Yeoman 代码生成器。

简单的说 **JHipster就是一个代码生成器** ，帮我们自动生成一个 java web 项目源码，后台使用 Spring Boot ，前端使用 Angular 。

![](http://okbn8yrzu.bkt.clouddn.com/image/what_is_jhipster.png "这就是 Jhipster") 

<!-- more -->

#### 类似的技术
一些 java web 项目代码生成工具：
- rapid-generator ：提供了struts2，springmvc，ibatis， hibernate的相应模板，可分别生成model，dao，manager和controller的代码， 包括hibernate的hbm.xml，ibatis的mapper.xml，jsp文件都可以生成。
- AutoJCode ：一个在线生成 java web 项目的网站，[http://www.autojcode.com/](http://www.autojcode.com/)。

#### 与同类技术相比的优缺点
JHipster 生成的是完整的现代的 web 应用项目，具有时尚、现代、高性能、稳定等特点，集合了多种最新的开发技术。

#### 组成部分
jhipster 采用的核心技术栈是 **Spring Boot** 和 **Angular** ,分别用于后端和前端。整体构建采用 **Yeoman** ，其中后端采用 **maven** 或 **gradle** 工具构建，前端采用 **Bower** 构建。

客户端涉及到的组件：**HTML5** 、 **CSS3** 、 **Bootstrap** 、 **AngularJS** 、 **JQuery** 、 **Websockets** 、 **Yarn** 、 **Webpack** 、 **Bower** 、 **Gulp** 、 **Sass** 、 **Browsersync** 、 **Karma** 、 **Protractor**

服务器端组件：**Spring Boot** 、 **Spring Security** 、 **Netflix OSS** 、 **Consul** 、 **Gradle** 、 **Maven** 、 **Hibernate** 、 **Liquibase** 、 **MySQL** 、 **PostgreSQL** 、 **Oracle** 、 **MongeDB** 、 **Cassandra** 、 **EhCache** 、 **Hazelcast** 、 **ElasticSearch** 、 **Kafka** 、 **Swagger** 、 **ELK Stack** 、 **Prometheus** 、 **Thymeleaf** 、 **Gatling** 、 **Cucumber**

部署组件：**Docker** 、 **Kubernates** 、 **Heroku** 、 **CloudFoundry** 、 **AWS** 、 **Rancher**

### 为什么会出现 JHipster？
#### 解决什么问题？
一键搭建 web 应用，简化了很多重复的工作环节，自动创建实体相关的增删改查，自动补全相关配置，开发者只需关注业务逻辑的实现即可。

#### 没有 JHipster 前怎么做？
打开 IDE 创建 java web 项目，慢慢创建实体，创建数据库表，增删改查的方法都要自己一点一点的写，手动添加配置信息。

### 干一波？
#### 预备，安装需要的组件
##### JDK
JHipster 是一个创建 java-web 项目的工具，所以说最基本的就是 java 开发环境。

##### Maven 或 Gradle （可选）
为了创建 java 后台框架，我们用 Maven 或 Gradle 来管理所有的依赖资源。

##### Git
在创建项目过程中需要通过 Git 下载资源。

##### NodeJS
需要用到 npm 来下载前端需要的组件资源。
从官网下载并安装 Node.js ，蒋自动安装 npm 包管理器。

##### Yeoman
能快速构建漂亮的网络应用，Yeoman主要提供了三个工具：脚手架（yo），构建工具（grunt），包管理器（bower）。这三个工具是分别独立开发的，但是需要配合使用，来实现我们更高效的工作流模式。
`npm install -g yo`

##### Bower
前端包管理器。
`npm install -g bower`

##### Gulp
gulp是前端开发过程中对代码进行构建的工具，是自动化项目的构建利器；她不仅能对网站资源进行优化，而且在开发过程中很多重复的任务能够使用正确的工具自动完成；使用她，我们不仅可以很愉快的编写代码，而且大大提高我们的工作效率。
`npm install -g gulp-cli`

##### JHipster
安装 JHipster 的构建器。
`npm install -g generator-jhipster`


#### 搞点实际的，跟着官方说明建一个 demo 
##### 快速开始
打开命令行，进入到想要的目录下： `f:` （我将demo项目放在了F盘根目录下）
创建项目目录： `mkdir myJHipsterDemo` ；
进入目录下： `cd myJHipsterDemo`；
执行构建命令： `yo jhipster` ；

##### 根据需要，填写信息和选项
###### 你要创建哪种类型的应用程序？
- Monolithic application：典型的，单页面应用，方便开发和使用，官方默认推荐，我们选择默认的。
- Microservice application：微服务，再微服务应用中这是服务之一。
- Microservice gateway：微服务网关。
- JHipster UAA server [BETA]：在微服务中，这是一个保护微服务的 OAuth2 认证服务器。

###### 你的应用程序的基础名称是什么？
输入创建的项目名，这里我们输入 **myJHipsterDemo**

###### 你默认的 Java 包名称是什么？
一般我们取名的习惯是倒写的域名加项目名，这里我们输入：**xyz.wqf31415.myJHipsterDemo**

###### 你想要使用哪种类型的身份验证？
- 典型的基于会话的认证机制，大多数人习惯使用的方式。可以使用 **Spring Social** 选项，这样就能使用社交登陆，如 Google、Facebook、Twitter，这是由 SpringBoot为 Spring Social 提供的配置。
- OAuth 2.0 认证机制，JHipster 随后提供必要的 OAuth2 服务器代码和数据库表。
- 使用 JSON Web 令牌（JWT）的机制。

###### 你想使用的数据库类型？
- 无数据库，仅在微服务应用程序时使用。
- SQL 数据库，使用Spring Data JPA 访问，如 H2 , MySQL , MariaDB , PostgreSQL , MSSQL , Oracle
- MongoDB 
- Cassandra

###### 你要使用哪个生产数据库？
选择用于生产环境的数据库，如果要使用 Oracle 数据库，需要手动安装 Oracle JDBC 驱动程序 

###### 你要使用哪个开发数据库？
选择用于开发环境的数据库，可选的有：
- H2 内存中运行，这是使用 JHipster 最简单的方法，重启服务器时数据将丢失；
- H2 数据存储在磁盘上，功能还在测试（不支持 windows 系统）
- 与生产环境数据库相同

###### 要使用 Hibernate 中使用二级缓存吗？
在实际开发中，为了性能考虑，建议使用缓存，选择 **encache** 开启本地缓存，或选择 **Hazelcast** 开启分布式缓存，用于集群环境。

###### 你要使用 Maven 或 Gradle 吗？
可以选择构建 java 应用的程序，Maven 更稳定，更成熟，Gradle 更灵活，更易于扩展。

###### 你想要使用哪些其他技术？
这是一个多项选择，可以为应用程序添加一个或几个其他技术。选项有：
- Social login ：社交登陆，如 Google、Facebook、Twitter，这一选项只有在选择 SQL 数据库或 MongoDB 时可用；
- Search engine using ElasticSearch ：使用 ElasticSearch 搜索引擎，将使用 Spring Data ElasticSearch 进行配置；
- Clustered HTTP sessions using Hazelcast ：使用 Hazelcast 的聚合 HTTP 会话，默认情况 JHipster 仅使用 HTTP 会话来存储 Spring Security 的身份验证和授权信息。如果正在集群中运行，使用 HTTP会话将导致问题，特别是如果不使用带有“粘性会话”的负载平衡器。如果要在群集中复制会话，请选择此选项以配置 Hazelcast；
- WebSockets using Spring Websocket ：使用 Spring Websocket 启用 Websockets；
- Asynchronous messages using Apache Kafka ：使用 Apache Kafka 作为发布/订阅消息代理。

###### 你希望客户端使用哪个框架？
- AngularJS 1.x 版本
- Angular 2+ 版本（测试），正处于测试阶段，可能不适合生产使用

###### 是否为 CSS 使用 LibSass 样式表预处理器？
Node-sass 是简化 CSS 设计的很好方式，如需自动配置，需要运行 Gulp 服务器。

###### 是否启动 Angular 翻译功能？
 默认情况，JHipster 的客户端和服务器端都支持国际化，但国际化会让管理稍微困难一些，可以选择不安装此功能
 
###### 要使用的测试框架？
- Performance tests using Gatling ：使用 Gatling 的性能测试；
- Behaviour tests using Cucumber ：使用 Cucumber 的行为测试；
- Angular integration tests with Protractor ：使用 Protractor 进行 Angular 积分测试。

##### 下载安装依赖包
以上所有选项根据项目需要来选，现在只是为了建个 demo 体验下，所以能不选的就不选，能少选的就少选，哈哈~~
完成选项后会自动运行 `npm intall && bower install` ；
这个过程需要等待很长一段时间，为了能快一点，我们按 **Ctrl + C** ，温柔的把进程停止，执行下面的指令：
`cnpm install`
这是用的淘宝npm镜像，在国内用速度更快更稳定，如果没有设定淘宝镜像，可以参考这里的方法：淘宝 NPM 镜像 [https://npm.taobao.org/](https://npm.taobao.org/)，运行完成后，执行下面命令：
`bower install`

再运行 `gulp install` ，完成后即可导入IDEA

##### 运行和测试
下载相关依赖后就可以开始运行了，可以再 IDE 中运行，也可以使用 Maven 或 Gradle 运行项目。

打开 [http://127.0.0.1:8080/](http://127.0.0.1:8080/)  进行预览


### 踩过的一些小坑
#### 运行 gulp install 时报错：
```
Bower components directory does not exist at E:\testJHipster\src\main\webapp\bower_components
```
说明 bower 组件目录不存在，手动创建该目录。但还是重新运行 `bower install` 命令来的更靠谱点

#### 导入 IDEA 后能运行，但打开页面显示产生了一个错误
在项目根目录下打开命令行，依次执行 `bower install` 和 `gulp install`

#### 运行 bower install 命令时报错：
```
bower swagger-ui#2.1.5      ECMDERR Failed to execute "git ls-remote --tags --heads https://github.com/wordnik/swagger-ui.git", exit code of #128 fatal: unable to access 'https://github .com/wordnik/swagger-ui.git/': SSL read: error:00000000:lib(0):func(0):reason(0), errno 10054
```
原因是 git SSH 配置有问题，重新配置 SSH 即可。


### 他山之石
1. [JHipster 官网](https://jhipster.github.io/)
2. [使用Rapid generator 4.0.6 自动生成代码](http://jy03100000.iteye.com/blog/2279525)
3. [AutoJCode](http://www.autojcode.com/)
4. [淘宝 NPM 镜像](https://npm.taobao.org/)