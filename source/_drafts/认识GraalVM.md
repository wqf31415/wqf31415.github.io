---
title: 认识GraalVM
date: 2021-05-31 10:04:08
tags:
- java
- jvm
categories:
- java
---

### 概述

这篇文章介绍了 GraalVM 是什么，它能做什么，以及怎么使用 GraalVM。



### 关于 GraalVM

> GraalVM 官网: <https://www.graalvm.org/> 

GraalVM 是一个高性能的 JDK 发行版，旨在加速 java 和其他 JVM 语言编写的应用程序的执行，同时还为 JavaScript、Ruby、Python 和其他许多流行语言提供了运行环境，允许用户编写多语言应用程序，通过 Truffle 语言实现的框架将值从一种语言无缝的传递到另一种语言。

<!-- more -->

### GraalVM 优势

按 GraalVM 官方介绍，GraalVM 是一个高级的 JDK，用于构建更快、更小、更精简的应用程序。GraalVM 的主要特性包括：

- **资源消耗少**：相较传统 JDK，GraalVM编译的原生可执行文件大大降低对内存和CPU的消耗，提高了资源利用率，降低使用成本。
- **高安全性**：原生可执行文件中只包含应用程序必要的类、方法和字段，大大降低了可能被攻击的可能。
- **高启动速度**：使用提前编译的原生可执行文件可立即启动，无需预热，运行效率更高。
- **紧凑的打包**：GraalVM 编译得到的原生可执行程序更小，提供了一系列链接选项，使它们易于部署在最小的容器镜像中。
- **支持流行的开发框架**：GraalVM支持流行的开发框架，如 [SpringBoot](https://spring.io/projects/spring-boot)、[Micronaut](https://micronaut.io/)、[Helidon](https://helidon.io/)、[Quarkus](https://cn.quarkus.io/)。
- **支持主流云平台**： 支持集成到主流云平台，如AWS、Microsoft Azure、GCP、Oracle Cloud。





### 参考资料

- Pedal to the metal: High-performance Java with GraalVM Native Image: <https://blogs.oracle.com/javamagazine/pedal-to-the-metal-high-performance-java-with-graalvm-native-image> 
- GraalVM：微服务时代的Java: <https://zhuanlan.zhihu.com/p/137836206> 
- 历数GraalVM的十大用途: <https://www.infoq.cn/article/graalvm-ten-things> 



