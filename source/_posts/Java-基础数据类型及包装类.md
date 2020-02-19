---
title: Java 基本数据类型及包装类
tags:
  - java
categories:
  - 技术
date: 2020-02-12 22:03:21
---

### 概述

这篇文章总结了 Java 中的基本数据类型和对应的封装类，以及各种类型数据之间的转换操作。

### 什么是基础数据类型

![](http://blog-images.qiniu.wqf31415.xyz/coffee.png)

在 Java 语言中，提供了 8 种基本数据类型，6 种数字类型(4 种整数类型，2 种浮点型)， 2 种字符型，这些基本数据类型从 Java 发布以来就是 java 语言的一部分。



<!-- more -->



### java 基本数据类型

#### byte

#### short

#### int

#### long

#### float

#### double

#### char

#### boolean

### 基本数据类型对应的包装类

Java 中基本数据类型对应的包装类都在 `java.lang` 包中，这个包是 java 语言的核心，除了这些基本数据类型的包装类，还包括 Object 类、 Class 类、String 类、基本数学类等最基本的类。

#### Byte

#### Short

#### Integer

#### Long

#### Float

#### Double

#### Character

#### Boolean

### 不同数据类型的转换



### 总结

基本数据类型是最基础的知识，这些数据类型和包装类中的方法都要用的滚瓜烂熟才行。这些基本数据类型里面有些跟 C 语言是一样的，但没有 C 语言中的无符号类型数据，因此在处理一些协议数据的时候，对于无符号类型要特别注意。

