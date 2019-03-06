---
title: SpringBoot 使用 Elasticsearch
date: 2019-03-05 10:18:05
tags:
- springboot
- elasticsearch
categories:
- 技术
---

### 本文概述
本文简单介绍了 Elasticsearch 是什么，在 windows 环境下的安装 Elasticsearch，在 SpringBoot 项目中使用 Elasticsearch 对数据进行增删改查操作。

### 什么是 Elasticsearch？
> Elasticsearch(简称 ES) 是一个开源的、高扩展性的分布式全文搜索和分析引擎，能够迅速、近乎实时的对大量数据进行存储、分析、检索，可以满足应用复杂的搜索特性和需求。
官网：[https://www.elastic.co/products/elasticsearch](https://www.elastic.co/products/elasticsearch) 

Elasticsearch 的核心是 Lucene ，使用 Java 进行封装，隐藏了 Lucene 的复杂性，提供 Java API 和 RESTful API，方便使用。

![](http://blog-images.qiniu.wqf31415.xyz/search.jpg)

<!-- more -->

### Elasticsearch 的应用场景
- 作为应用的全文搜索引擎，使用关键字在数量巨大的文档中定位；
- 作为 NoSql 存储数据，需要注意的是 ES 不支持事务；

### Elasticsearch 基本概念
|名称|含义|说明|
|:----:|:----:|:----:|
|Cluster|集群|ES可以单独作为一个搜索引擎使用，也可以部署在多台机器上，相互合作处理 PB 级数据，这些相关合作的机器称为集群。|
|Node|节点|在集群中的一台机器称为一个节点，集群中的所有节点使用同一个名称，参与数据存储与集群索引和检索。|
|Shard|分片|当数据量大时，为了响应迅速，ES 将数据分片放到不同服务器上，查询时 ES 再将不同分片上的数据组合起来。|
|Replia|副本|副本是分片的精确复制，当主分片丢失时，ES 将副本提升为新的主分片。|
|Index|索引|类似关系型数据库中的“数据库”，有一个定义多种类型的映射。索引是逻辑名称空间，映射到一个或多个主分片，并且可以有零个或多个副本分片。 |
|Type|类型|类型是索引的逻辑类别/分区，类似于关系型数据库中的“Table”。|
|Document|文档|一条记录，类似关系型数据库中的“Row”。|
|Field|字段|记录中的字段，类似关系型数据库中的“Column”。|

### 在 windows 环境下安装 Elasticsearch
#### 环境与版本
- JDK：1.8（最低 1.7）
- Elasticsearch：5.5.3

#### 下载与安装
- 安装 JAVA 环境并配置环境变量，比较简单，这里不做说明了。
- 下载 ES 5.5.3，下载地址：[https://www.elastic.co/downloads/past-releases/elasticsearch-5-5-3](https://www.elastic.co/downloads/past-releases/elasticsearch-5-5-3)，我这里下载的是 ZIP 压缩包，解压即用。
  > 下载最新版本：[https://www.elastic.co/downloads/elasticsearch](https://www.elastic.co/downloads/elasticsearch)
  > 下载其他历史版本：[https://www.elastic.co/downloads/past-releases](https://www.elastic.co/downloads/past-releases)
- 解压文件，进入 bin 目录下，运行 `elasticsearch.bat` 即可运行 Elasticsearch。运行结果如下：
![](http://blog-images.qiniu.wqf31415.xyz/elasticsearch_1.png)

### 在 SpringBoot 中使用 Elasticsearch


### 参考资料：
+ Elasticsearch 官方文档: [https://www.elastic.co/guide/en/elasticsearch/reference/current/index.html](https://www.elastic.co/guide/en/elasticsearch/reference/current/index.html)
+ Elasticsearch学习，请先看这一篇: [https://blog.csdn.net/makang110/article/details/80596017#](https://blog.csdn.net/makang110/article/details/80596017#)
+ 全文搜索引擎 Elasticsearch 入门教程: [http://www.ruanyifeng.com/blog/2017/08/elasticsearch.html](http://www.ruanyifeng.com/blog/2017/08/elasticsearch.html)
+ Elasticsearch面试题: [https://blog.csdn.net/moakun/article/details/82817611](https://blog.csdn.net/moakun/article/details/82817611)
