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

### 先安装需要的组件
#### JDK
JHipster 是一个创建 java-web 项目的工具，所以说最基本的就是 java 开发环境。
#### Maven 或 Gradle
为了创建 java 后台框架，我们用 Maven 或 Gradle 来管理所有的依赖资源。
#### Git
在创建项目过程中需要通过 Git 下载资源。
#### NodeJS
需要用到 npm 来下载前端需要的组件资源。
#### Yarn

#### Yeoman

#### Bower

#### Gulp

#### JHipster



### 先来一个 demo 试试看

打开命令行，执行指令：
`yo jhipster`

根据需要，填写信息选项

选项选完后会自动运行 `npm intall && bower install` ，这个过程需要等待很长一段时间，为了能快一点，我们按 **Ctrl + C** 停止，执行下面的指令
`cnpm install`
这是用的淘宝npm镜像，在国内用速度更快更稳定，运行完成后，执行下面命令：
`bower install`

再运行 `gulp install` ，完成后即可导入IDEA

下载相关依赖后就可以开始运行了。

打开 [http://127.0.0.1:8080/](http://127.0.0.1:8080/)  进行预览


