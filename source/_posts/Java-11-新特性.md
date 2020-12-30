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



![](http://blog-images.qiniu.wqf31415.xyz/coffee-java11.jpg)



<!-- more -->



### JAVA 11 新特性

#### var 定义局部变量与类型自动推测

JDK 10 中引入了局部变量推断，可以使用 var 定义局部变量。

在 jdk11 中，关键字 var 可以用在 lambda 表达式中，用来定义 lambda 中的局部变量。



#### 支持 Unicode 10 标准字符编码

Unicode 10 新增了 8518 个字符，总字符数达到 136690 个，新增了 4 个语种，新增了 56 个新 emoji 字符。



#### HTTP 客户端

现在可以使用官方的 http 客户端了，不用再用第三方库，如 Apache HttpClient 。



#### 新的 Collection.toArray 默认方法

JDK 11 中，`java.util.Collection` 接口中新增了 `default <T> T[] toArray(IntFunction<T[]> generator)` 默认实现的方法。



#### 嵌套访问控制

直接支持嵌套成员内部的私有访问，而不再通过自动生成的桥接方法 `access$100` 。新的嵌套 API 用于验证并允许嵌套成员内的私有反射访问。

Class 类中新增了用于嵌套类的操作方法：`getNestHost()` 方法用于获得嵌套的最外层类，`getNestMembers()` 方法用于获取所有与当前类有嵌套关系的类（包括外层的和内层的），`isNestmateOf(Class c)` 方法用于判断与其他类是否有嵌套关系。



#### 编译线程动态分配

新增了命令行参数 `-XX:+UseDynamicNumberOfCompilerThreads` 用于动态控制编译线程。在分层编译模式下自动开启，虚拟机不考虑用内存大小和编译请求数量，直接在开始时使用系统多个 CPU 开启大量编译线程，这将导致过多的线程处于闲置状态，无意义的消耗内存资源。针对这个问题，新的实现方式只为每个类型开启一个编译线程，然后动态处理后续线程的分配。



#### 可扩展低延迟的垃圾收集器

JDK 11 中的 ZGC 是一个可扩展低延迟的垃圾收集器，ZGC 的优势包括：

- 暂停时间不超过 10ms；
- 暂停时间不增加堆和 live-set 大小；
- 可处理几百字节到超过兆字节的堆。

ZGC 是并发垃圾收集器，意味着在线程执行同时就能完成繁重的挖掘工作（标记、压缩、引用处理、清除字符串表等），这极大程度上降低了对应用响应时间的影响。

ZGC 当前还是一个实验特性，如需启用需要组合使用参数 `-XX:+UnlockExperimentalVMOptions` 和 `-XX:+UseZG` 。



#### 低开销堆分析

提供了一种低开销的对分配取样方式，可用 JVMTI  访问。



#### 加密相关

##### Curve25519 与 Curve448 密钥协商

> 基于椭圆曲线密码算法由于出色的计算效率，被广泛用于密钥交换协议。Curve25519 由著名密码学家 Bernstein 教授于 2005 年提出，2013 年开始广泛运用，2016 年 IETF 发布了 RFC7748，推荐使用 Curve25519 和 Curve 448 用于 ECDH 密钥交换协议 X25519 和 X448。



##### chacha20-poly1305 加密算法

> ChaCha20-Poly1305 是 Google 所采用的一种新式加密算法，性能强大，在 CPU 为精简指令集的 ARM 平台上尤为显著（ARM v8前效果较明显），在同等配置的手机中表现是 AES 的4倍。



##### 加强型密钥库机制

引入了新的安全属性 `jceks.key.serialFilter` ，配置这个过滤器后，JCEKS KeyStore 在反序列化 SecretKeyEntry 中的加密 Key 对象时使用。



##### 实现 TLS 1.3 

> TLS，即 Transport Layer Security，安全传输层协议，广泛用于基于 IP 的网络协议，如 HTTP、SMTP、FTP 等。TLS 1.3 移除了很多过时的密码学原理和功能，更加安全。TLS 1.3 只需要一个 RTT 就能完成握手，并且支持 *0-RTT* 模式，访问速度提升。



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

> Oracle JDK 11 下载地址：<https://www.oracle.com/java/technologies/javase-jdk11-downloads.html> 

> 我的电脑（Windows）上原本装了 JDK8，用于日常开发，现在想体验 JDK11，可以装两个版本 JDK ，通过修改环境变量中的 *JAVA_HOME* 来切换使用。

下载 Oracle 官方的 JDK 11 压缩包后，将其解压到本地，然后配置环境变量，添加一个环境变量 `JDK11_HOME` ，值为解压的 JDK11 根目录，如：`G:\develop\Java\jdk-11.0.9` ，将 `JAVA_HOME` 配置改成 `%JDK11_HOME%` ，这样就可以使用新安装的 JDK 11 了。同时可以给原本的 JDK 8 也创建一个环境变量 `JDK8_HOME` ，值为 JDK 8 的根目录。需要切换时，只需要将 `JAVA_HOME` 的值修改为 `%JDK8_HOME%` 即可。

完成配置后，打开命令行执行 `java -version` 查看 JAVA 版本信息：

```
PS C:\Users\Administrator\Desktop> java -version
java version "11.0.9" 2020-10-20 LTS
Java(TM) SE Runtime Environment 18.9 (build 11.0.9+7-LTS)
Java HotSpot(TM) 64-Bit Server VM 18.9 (build 11.0.9+7-LTS, mixed mode)
```



### 参考资料

- JDK 11 Release Notes: <https://www.oracle.com/java/technologies/javase/jdk-11-relnote.html> 
- Unicode 10.0.0: <http://www.unicode.org/versions/Unicode10.0.0/> 
- java10 var关键字浅析: <https://blog.csdn.net/guohengcook/article/details/81266957> 
- java11新特性HttpClient: <https://www.cnblogs.com/liubaihui/p/12125461.html> 
- java11新特性---Nest-Based Access Control(嵌套访问控制): <https://blog.csdn.net/weixin_34013044/article/details/91466789> 
- Java 11 –基于嵌套的访问控制: <https://blog.csdn.net/cyan20115/article/details/106541001> 
- 成娟娟, 郑昉昱, 林璟锵, 董建阔. Curve25519椭圆曲线算法GPU高速实现[J]. 信息网络安全, 2017, 17(9): 122-127.
- Curve25519加密算法: <https://blog.csdn.net/u011897062/article/details/89633193> 
- Curve25519加密解密: <https://blog.csdn.net/marko_zheng/article/details/100882231> 
- 浅谈 TLS 1.3: <http://blog.itpub.net/31559359/viewspace-2286705/> 
- Java黑科技之源：JVMTI完全解读:<https://blog.csdn.net/duqi_2009/article/details/94518203> 



### 总结

从官方网站看到的 JDK11 新特性，在学习 JDK 新特性的同时，也认识到了很多新技术，扩展了知识面。所以，想要获得成长和保持自身的不断更新状态，不妨花点时间关注一下正在用的技术栈的新特性，这些新特性的引入是开发团队深思熟虑才引入的，从这些更新点又能扩展到当前流行且稳定的新技术，这样不仅学到了新技术，又能扩展见识，是个不错的提升方式。

