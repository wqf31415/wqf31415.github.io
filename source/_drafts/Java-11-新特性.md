---
title: Java 11 新特性
tags:
  - java 
  - jdk
categories:
  - java
date: 2019-12-24 18:12:43
---

### 概述

Oracle JDK 每半年发布一个版本，现在最新的已经到 15 了，不过在这么多 JDK 版本中，JAVA8 是目前使用最多的，也比较稳定。其次 JAVA11 现在是 LTS （长期支持）版本，说明其稳定性也比较好，可以列入学习列表了。这篇文章介绍了 JAVA 11 中的一些新特性。



<!-- more -->



### JAVA 11 新特性

#### var 定义变量与类型自动推测

在 jdk11 中，var 可以用在 lambda 表达式中，用来定义局部变量。



#### JEP 327 支持 Unicode 10 标准字符编码



#### JEP 321 HTTP 客户端



#### 新的 Collection.toArray 默认方法



#### 嵌套访问控制





#### 编译线程动态分配



#### 可扩展低延迟的垃圾收集器



#### 低开销堆分析



#### 加密相关

##### Curve25519 与 Curve448 密钥协商



##### chacha20-poly1305 加密算法



##### 加强型密钥库机制



##### 实现 TLS 1.3 



#### 运行源码文件

java 11 中可以直接用 `java` 运行 `.java` 源码文件，如使用命令 `java Hello.java` 运行 Hello.java 文件，不需要像之前的版本先用 javac 编译出 `.class` 文件，再用 java 命令运行 `.class` 文件。



### 移除的特性

已下特性已从 JDK 11 中移除，部分工具和模块被分离出来了，可单独下载。

- **com.sun.awt.AWTUtilities** 类
- **Lucida** 字体
- 小程序查看器
- **javax.imageio JPEG** 插件
- **sun.misc.Unsafe.defineClass** 类
- **Thread.destroy()** 和 **Thread.stop(Throwable)** 方法
- **sun.nio.ch.disableSystemWideOverlappingFileLockCheck** 属性
- **sun.locale.formatasdefault** 属性
- **SNMP** 代理
- Java Mission Control (JMC)
- **JavaFX** 
- **Java EE** 和 **CORBA** 模块



### 废弃的特性

- **ThreadPoolExecutor** 的 finalize 方法不再处理依赖
- **Nashorn JavaScript** 引擎
- JVM 选项 **-XX+AggressiveOpts** 
- **Pack200** 工具和接口
- 基于流的 **GSSContext** 方法



### 安装 JDK 11



### 参考资料

- JDK 11 Release Notes: <https://www.oracle.com/java/technologies/javase/jdk-11-relnote.html> 
- java11新特性---Nest-Based Access Control(嵌套访问控制): <https://blog.csdn.net/weixin_34013044/article/details/91466789> 



### 总结



