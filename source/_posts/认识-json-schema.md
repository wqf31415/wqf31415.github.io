---
title: 认识 json-schema
tags:
  - json
categories:
  - 技术
date: 2020-04-02 10:33:29
---

### 概述

本文介绍了 json schema。



### 什么是 json schema

JSON Schema 是一种用来定义 json 数据结构的文件，JSON Schema 自身也是以 json 文档形式存在。JSON Schema 被设计用于对 json 文件进行校验、注释、链接导航、交互控制。官方提出了一种用于描述 JSON Schema 的新媒体类型（Media Type）：`application/schema+json` 。

> 官网: <http://json-schema.org> 
>
> GitHub: <https://github.com/json-schema-org/json-schema-spec> 
>
> JSON Schema Tool: <https://jsonschema.net/home> 



<!-- more -->



### 相关概念

#### 什么是 json

> 官网：<https://www.json.org/json-zh.html> 

> JSON（JavaScript Object Notation），是一种轻量级的数据交换格式，具有易阅读编写，也易于机器解析和生成。json 采用完全独立于语言的文本格式，但也使用了类似于 C 语言家族的习惯（包括C, C++, C#, Java, JavaScript, Perl, Python等）。这些特性使JSON成为理想的数据交换语言。

json 中的数据值类型包括：

json 对象包含在 `{}` 中，内容是一个无序的**键(key)/值(value)对**集合，键都是字符串

### 使用



#### maven

```xml
<dependency>
    <groupId>com.github.fge</groupId>
    <artifactId>json-schema-validator</artifactId>
    <version>2.2.6</version>
</dependency>

```



### 参考资料

- 使用JSON Schema校验JSON数据是否合规: <https://blog.csdn.net/zjg379569986/article/details/84634803>
- JSON Schema 详解: <https://blog.csdn.net/swinfans/article/details/89231247> 
- 