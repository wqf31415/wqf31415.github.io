---
title: Redis 数据结构与应用
date: 2020-12-31 16:33:08
tags:
- redis
- nosql
categories:
- 技术
---

### 概述

这篇文章介绍了 redis 支持的数据类型，以及对这些数据类型的操作与使用场景。



### 认识 Redis

Redis 是一个开源的 Key-Value 型的内存中的数据结构存储系统，可作为数据库、缓存和消息中间件，Redis 的数据都在内存中处理，因此具有极高的读写速度。

Redis 存储时的键一般用字符串，但不限于字符串，也可以是任何二进制序列，比如一个 jpeg 文件的内容，但建议不要太长，会消耗内存，而且计算成本很高。存储的值支持多种类型的数据结构，包括：string（字符串）、list（链表）、set（集合）、sorted set（有序集合）、hash（字典）、bitmap（位操作）、hyperloglog（基数统计）、geospatial（地理信息）。

> Redis 官网：
>
> 中文官网：<http://www.redis.cn/> 
>
> 英文官网：<https://redis.io/> 

<!-- more -->



### 其他 Key-Value 型数据库

- **MemcacheDB**：开源的分布式缓存服务器，用 C++ 开发的，新浪网的开发人员开放的项目。MemcacheDB 使用的协议与 memcache 一致，所以很多memcached 客户端都可以跟它连接。官网: <https://www.oschina.net/p/memcachedb> 
- **CouchDB**：开源的面向文档的分布式数据管理系统，CouchDB 适合存储文档，适合 CMS、电话本、地址等。CouchDB 支持使用 REST API ，让用户可以使用 JavaScript 操作 CouchDB。官网：<https://couchdb.apache.org/> 
- **HBase**：分布式的、面向列的开源数据库。官网：<http://hbase.apache.org/> 



### Redis 中与数据类型无关的命令

| 命令      | 说明                                   | 返回结果                                       | 示例                                                         |
| --------- | -------------------------------------- | ---------------------------------------------- | ------------------------------------------------------------ |
| ping      | 测试连接是否可用                       | 成功时返回 `PONG`                              |                                                              |
| exists    | 判断键是否存在(可判断多个键)           | 返回存在的键的数量                             | `exists key1` ，`exists key1 key2`                           |
| del       | 删除指定键（可删除多个键）             | 返回删除的键的数量                             | `del key1` 、`del key1 key2`                                 |
| randomkey | 随机获取一个键                         | 从键空间中随机取一个键                         | `randomkey`                                                  |
| keys      | 查找符合格式的键                       | 返回所有符合匹配格式的键                       | `keys key1` 、`keys ke*` ，`keys key?`                       |
| expire    | 设置键过期时间(单位：s)                | 成功的数量                                     | `expire key1 30`                                             |
| pexpire   | 设置键过期时间（单位：ms）             | 成功的数量                                     | `pexpire key1 30000`                                         |
| pexpireat | 设置键过期时间点(UNIX时间戳)           | 成功的数量                                     | `pexpireat key1 1612520066261`                               |
| persist   | 移除键过期时间                         | 成功的数量                                     | `persist key1`                                               |
| ttl       | 查看键过期时间（秒）                   | 键不存在返 -2；键持久化返 -1；正常返回过期时间 | `ttl key1`                                                   |
| pttl      | 查看键过期时间（毫秒）                 | 同上                                           | `pttl key1`                                                  |
| rename    | 重命名键（将覆盖新键）                 | 成功返回 OK                                    | `rename key1 key2`                                           |
| renamenx  | 重命名键，新键存在时将不会执行         | 成功返回 1，失败返回 0                         | `renamenx key1 key2`                                         |
| type      | 查看指定键存放的数据类型               | 键不存在时返回 none，存在时返回数据类型        | `type key1`                                                  |
| sort      | 对列表、集合、有序集合中的元素进行排序 | 排序后的元素                                   | `sort mylist` 、`sort mylist desc` 、对字符串元素排序 `sort mylist alpha` 、`sort mylist limit 0 10` 、`sort mylist limit 0 5 alpha desc` 、`sort mylist by weight_*` |
| scan      | 按游标对包含键进行遍历                 | 遍历到的键                                     | `scan 0` 、`scan 0 match key* count 10`                      |



### Redis 支持的数据结构

#### String

##### 常用命令

| 命令 | 说明 | 返回结果 | 示例 |
| ---- | ---- | -------- | ---- |
| set  |      |          |      |
| get  |      |          |      |
|      |      |          |      |



#### List



#### Set



#### Sorted Set



#### Hash



#### Bitmap



#### Hypweloglog



#### Geospatial



### 参考资料



### 总结

Redis 是一个很好有的中间件，可用来做消息队列，可以用来做数据缓存，还可以用来做分布式锁，学好基本数据结构的存取，才能更好的用在实际项目中。