---
title: Redis 数据结构与应用
date: 2021-04-09 18:40:08
tags:
- redis
- nosql
categories:
- 技术
---

### 概述

这篇文章介绍了 redis 支持的数据类型，以及对这些数据类型的操作与使用场景。



### 认识 Redis

Redis ，全称 **Remote Dictionary Server**（远程数据服务），是一个使用 C 开发的开源的 Key-Value 型的内存中的数据结构存储系统，可作为数据库、缓存和消息中间件，Redis 的数据都在内存中处理，因此具有极高的读写速度。

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

#### Keys

以下是与 Redis 中键相关的操作命令，能够查询键是否存在，查看键的过期时间或设置过期时间，查看键中存储数据的类型。

| 命令      | 说明                                   | 返回值                                         | 示例                                                         |
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



#### Pub/Sub

发布订阅，让 Redis 成为一个消息中间件。

| 命令         | 说明                    | 返回值               | 示例                                         |
| ------------ | ----------------------- | -------------------- | -------------------------------------------- |
| subscribe    | 订阅通道                |                      | `subscribe channel1 channel2`                |
| psubscribe   | 订阅指定模式的通道      |                      | `psubscribe channel?`                        |
| unsubscribe  | 取消订阅                |                      | `unsunscribe channel1 channel2`              |
| punsunscribe | 取消订阅指定模式的通道  |                      | `punscribe channel?`                         |
| publish      | 发布消息                | 收到消息的客户端数量 | `publish channel hello`                      |
| pubsub       | 检测PUB/SUB子系统的状态 |                      | `PUBSUB CHANNELS channel?` 、`PUBSUB NUMPAT` |



### Redis 支持的数据结构

#### String

字符串类型，可以存储字符串或数字，当内容为数字时可以对其做加减运算处理。

| 命令        | 说明                               | 返回值                 | 示例                             |
| ----------- | ---------------------------------- | ---------------------- | -------------------------------- |
| set         | 设置一个键的值                     | ok                     | `set a 123`                      |
| setnx       | 当键不存在时设置键的值             | `1` 成功，`0` 失败     | `setnx a 123`                    |
| setex       | 设置键的值并指定过期时间（秒）     | `OK`                   | `setex key 30 value`             |
| psetex      | 设置键的值并指定过期时间（毫秒）   | `OK`                   | `psetex key 30000 value`         |
| mset        | 设置多个键值                       | `OK`                   | `mset key1 value1 key2 value2`   |
| msetnx      | 设置多个键值，当键不存在时设置成功 | `1` 成功，`0` 失败     | `msetnx key1 value1 key2 value2` |
| setrange    | 覆盖key对应的string的一部分        | 修改完成后的字符串长度 | `setrange key 2 00000000`        |
| get         | 获取键的值                         | 值或(nil)              | `get key`                        |
| mget        | 获取多个键的值                     | 值或(nil)              | `mget key1 key2`                 |
| getrange    | 获取字符串指定范围内容             | 字符串或`""`           | `getrange key 0 2`               |
| getset      | 获取键的值并设置为新的值           | 键原来的值或(nil)      | `getset key 123`                 |
| append      | 将值追加到原来值的后面             | 追加后的字符串长度     | `append key abc`                 |
| decr        | 将键中的数字减一                   | 操作后的值             | `decr key`                       |
| decrby      | 将键中的值减去指定值               | 操作后的值             | `decrby key 100`                 |
| incr        | 将键中值加一                       | 操作后的值             | `incr key`                       |
| incrby      | 将键中值加上指定值                 | 操作后的值             | `incrby key 10`                  |
| incrbyfloat | 加上指定浮点值                     | 操作后的值             | `incrbyfloat key 1.1`            |
| strlen      | 查看值的长度                       | 值得长度               | `strlen key`                     |



#### List

队列，可以作为队列或栈使用。队列操作时的左（l）是队列头，右（r）是队列尾。

| 命令       | 说明                                                         | 返回值                   | 示例                              |
| ---------- | ------------------------------------------------------------ | ------------------------ | --------------------------------- |
| lpush      | 从队列左边加入元素                                           | 操作完成后list的长度     | `lpush list abc`                  |
| lpushx     | 当队列存在时从左边加入元素                                   | 操作完成后list的长度或0  | `lpushx list 123`                 |
| rpush      | 从队列右边加入元素                                           | 操作完成后list的长度     | `rpush list abc`                  |
| rpushx     | 当队列存在时从右边加入元素                                   | 操作完成后list的长度或0  | `rpushx list1 abc`                |
| rpoplpush  | 把源队列最后一个元素移到目标队列的头部并返回该元素           | 元素或(nil)              | `rpoplpush list list2`            |
| brpoplpush | `rpoplpush` 的阻塞版本，当源队列中没有元素时会阻塞，直到超时或获取到元素 | 读到的元素，或超时(nil)  | `brpoplpush list2 list 5`         |
| lpop       | 弹出队列左侧第一个元素                                       | 元素或(nil)              | `lpop list`                       |
| blpop      | 阻塞的弹出队列左侧元素，如果没有元素将会阻塞住直到超时或获取到元素 | 读到的元素，或超时(nil)  | `blpop list 5`                    |
| rpop       | 弹出队列右侧第一个元素                                       | 元素或(nil)              | `rpop list`                       |
| brpop      | 阻塞的弹出队列右侧元素                                       | 读到的元素，或超时(nil)  | `brpop list 5`                    |
| lindex     | 返回队列中指定索引位置的元素（索引从0开始）                  | 元素或(nil)              | `lindex list 2`                   |
| linsert    | 在指定元素前/后插入元素                                      | 插入后的list长度，或`-1` | `linsert list before world hello` |
| llen       | 查看队列元素个数                                             | 元素个数                 | `llen list`                       |
| lrange     | 查询指定索引范围内的元素（索引从0开始，倒数时从-1开始）      | 元素列表或空列表提示     | `lrange list 0 -1`                |
| lrem       | 删除队列中的元素                                             | 删除的元素量             | `lrem list 1 abc`                 |
| lset       | 设置指定索引位置的元素值                                     | `OK` 或索引超出范围提示  | `lset list 1 hello`               |
| ltrim      | 修剪队列，只保留指定范围内的元素                             | `OK`                     | `ltrim list 1 3`                  |



#### Set

集合，能够排除重复值，多个集合可以进行并、交处理。

| 命令        | 说明                                 | 返回值               | 示例                  |
| ----------- | ------------------------------------ | -------------------- | --------------------- |
| sadd        | 给集合添加元素                       | `1` 成功，`0` 失败   | `sadd setName a`      |
| spop        | 删除并获取一个元素                   | 元素或(nil)          | `spop setName`        |
| smembers    | 获取集合中所有元素                   | 元素列表或空列表提示 | `smembers setName`    |
| srandmember | 从集合中随机获取元素                 | 元素或(nil)          | `srandmember setName` |
| sismember   | 判断值是否是指定集合中的元素         | `1` 是，`0` 否       | `sismember setName a` |
| srem        | 从集合中删除一个或多个元素           | 删除的元素数量       | `srem setName a b c`  |
| scard       | 获取集合中元素个数                   | 元素数量             | `scard setName`       |
| smove       | 在集合间移动元素                     | `1` 成功，`0` 失败   | `smove set1 set2 2`   |
| sscan       | 迭代集合中的元素                     |                      |                       |
| sdiff       | 查询一个集合和另一个集合的差集       |                      |                       |
| sdiffstore  | 获取集合的差集并将结果存到目标集合中 |                      |                       |
| sinter      | 查询集合的交集                       |                      |                       |
| sinterstore | 获取集合的交集并存到目标集合         |                      |                       |
| sunion      | 获取多个集合的并集                   |                      |                       |
| suinonstore | 获取多个集合的并集并存到目标集合     |                      |                       |



#### Sorted Set

有序集合，在集合的基础上，给每个值增加了一个分数（score），按分数进行排序。

| 命令             | 说明                                                         | 返回值 | 示例 |
| ---------------- | ------------------------------------------------------------ | ------ | ---- |
| zadd             | 添加元素或更新元素的分值                                     |        |      |
| zcard            | 获取集合元素数量                                             |        |      |
| zcount           | 获取分值范围内的元素数量                                     |        |      |
| zincrby          | 元素分值增加指定值                                           |        |      |
| zinterstore      | 获取集合的交集并存到指定集合                                 |        |      |
| zlexcount        | 计算指定元素间的元素数量                                     |        |      |
| zpopmax          | 弹出分数最高的元素                                           |        |      |
| zpopmin          | 弹出分数最低的元素                                           |        |      |
| zrange           | 获取指定索引范围内的元素                                     |        |      |
| zrangebylex      | 返回指定成员区间内的成员，按成员字典正序排序, 分数必须相同   |        |      |
| zrevrangebylex   | 返回指定成员区间内的成员，按成员字典倒序排序, 分数必须相同。 |        |      |
| zrangebyscore    | 查询分值范围内的元素                                         |        |      |
| zrank            | 查询元素的排名                                               |        |      |
| zrem             | 删除元素                                                     |        |      |
| zremrangebylex   | 删除名称按字典由低到高排序成员之间所有成员                   |        |      |
| zremrangebyrank  | 删除排名区间内的元素                                         |        |      |
| zremrangebyscore | 删除得分范围内的元素                                         |        |      |
| zrevrange        | 获取得分倒序排时指定索引范围内元素                           |        |      |
| zrevrangebyscore | 获取得分倒序排列时指定得分范围内元素                         |        |      |
| zrevrank         | 获取元素排名（按得分倒序排）                                 |        |      |
| zscore           | 获取元素得分                                                 |        |      |
| zunionstore      | 获取并集并存储到目标集合                                     |        |      |
| zscan            | 遍历集合元素                                                 |        |      |



#### Hash

字典，按键值进行存储，相当于 java 中的 Map。

| 命令         | 说明                           | 返回值 | 示例 |
| ------------ | ------------------------------ | ------ | ---- |
| hset         | 设置hash字段值                 |        |      |
| hsetnx       | 当指定hash中不存在字段时才设置 |        |      |
| hmset        | 设置指定hash中字段的值（多个） |        |      |
| hget         | 获取指定hash中指定字段的值     |        |      |
| hmget        | 获取hash中多个字段的值         |        |      |
| hgetall      | 获取hash中所有的字段和值       |        |      |
| hexists      | 判断hash中指定字段是否存在     |        |      |
| hdel         | 删除hash中指定字段             |        |      |
| hincrby      | 给hash中指定字段值增加值       |        |      |
| hincrbyfloat | 给hash中指定字段值增加小数值   |        |      |
| hkeys        | 获取hash中所有的字段名         |        |      |
| hlen         | 获取hash中的字段数量           |        |      |
| hstrlen      | 获取hash中指定字段中值的长度   |        |      |
| hvals        | 获取hash中所有字段的值         |        |      |
| hscan        | 遍历hash中的字段               |        |      |



#### Bitmap

位图，实际内容存储为 String，但可以按位来取值和运算。

| 命令     | 说明                                               | 返回值 | 示例 |
| -------- | -------------------------------------------------- | ------ | ---- |
| setbit   | 设置或清除指定位数上的值                           |        |      |
| getbit   | 获取指定位数上的值                                 |        |      |
| bitcount | 统计指定范围内值为1的位数                          |        |      |
| bitfield | 对变长位宽和任意未字节对齐的指定整型位域进行寻址。 |        |      |
| bitop    | 对多个二进制位字符串进行位操作，将结果存到目标键上 |        |      |
| bitpos   | 返回字符串里面第一个被设置为1或者0的bit位          |        |      |



#### Hyperloglog

Hyperloglog 用来做基数统计，用来估算大数据集中不重复的元素数量。其优势在于输入元素的数量或体积非常大时，计算基数所需的空间总是固定的，而且很小，因为 Hyperloglog 只会根据输入元素来计算基数，而不会存储输入的元素本身。每个 Hyperloglog 键只需要花费 12KB 内存就可以计算接近 2<sup>64</sup> 个不同元素的基数。

> 基数：集合中包含的元素的“个数”，如数据集 {1, 2, 3, 2, 1} ，其基数集是 {1, 2, 3}，基数(不重复元素)是 3。

| 命令    | 说明                | 返回值     | 示例                  |
| ------- | ------------------- | ---------- | --------------------- |
| pfadd   | 添加元素            |            | `pfadd hll 1 2 3 2 1` |
| pfcount | 返回基数估算值      | 基数估算值 | `pfcount hll`         |
| pfmerge | 合并多个Hyperloglog |            | `pfmerge hll hll2`    |



#### Geospatial

地理空间位置，包括经度、纬度、名称。地理位置信息将会存储到 sorted set 中，录入的经纬度将通过 [Geohash](https://en.wikipedia.org/wiki/Geohash) 技术进行填充，转化成一个独特的 52 位整数。

| 命令              | 说明                                                         | 返回值     | 示例                                                         |
| ----------------- | ------------------------------------------------------------ | ---------- | ------------------------------------------------------------ |
| geoadd            | 添加指定的空间位置                                           | 添加的数量 | `geoadd sichuan 103.963905 30.735666 chengdu` 、`geoadd sichuan 104.391022 31.166052 deyang` |
| geohash           | 一个或多个位置元素的 [Geohash](https://en.wikipedia.org/wiki/Geohash) 表示 |            | `geohash sichuan chengdu`                                    |
| geopos            | 查询指定元素的位置                                           |            | `geopos sichuan chengdu`                                     |
| geodist           | 计算两个位置间的距离                                         | 距离值     | `geodist sichuan chengdu deyang km`                          |
| georadius         | 查询指定范围内的元素                                         |            | `georadius sichuan 103.963905 30.735666 70 km`               |
| georadiusbymember | 以指定元素为中心查找半径内的元素                             |            | `georadiusbymember sichuan chengdu 70 km`                    |





#### Stream

| 命令       | 说明                                               | 返回值                                 | 示例 |
| ---------- | -------------------------------------------------- | -------------------------------------- | ---- |
| xadd       | 将指定的流条目追加到指定key的流中                  |                                        |      |
| xinfo      | 检索关于流和关联的消费者组的不同的信息             |                                        |      |
| xread      | 从一个或者多个流中读取数据                         | 返回ID大于调用者报告的最后接收ID的条目 |      |
| xdel       | 从指定流中移除指定的条目                           | 成功删除的条目的数量                   |      |
| xlen       | 返回流中的条目数                                   |                                        |      |
| xack       | 从流的消费者组的待处理条目列表中删除一条或多条消息 |                                        |      |
| xclaim     | 改变待处理消息的所有权                             |                                        |      |
| xgroup     | 管理流数据结构关联的消费者组                       |                                        |      |
| xpending   | 过消费者组从流中获取数据                           |                                        |      |
| xreadgroup | `XREAD`命令的特殊版本，支持消费者组                |                                        |      |
| xrange     | 返回流中满足给定ID范围的条目                       |                                        |      |
| xrevrange  | 与`xrange`相同，但顺序相反                         |                                        |      |
| rtrim      | 将流裁剪为指定数量的项目                           |                                        |      |



### 使用场景

#### 缓存

Redis 读取速度快，还提供多种数据类型能够满足各种缓存场景。

一般有两种方式：

- 读取前，先去读 Redis，如果没有数据，读取数据库，将数据存入Redis。
- 插入数据时，同时写入 Redis。



#### 消息队列

使用 Redis 中 List 的丰富操作方式，能够轻松构建消息队列或栈，达到异步处理的效果，还能让程序解耦合。



#### 实时消息广播

使用 Pub/Sub 能够实现实时的消息广播，能够构建实时聊天系统。



#### 最新数据

比如新闻网站查找最新的新闻，可以将最新的 5000 条的 id 放到 redis 的 list 中，超出的部分再从数据库中获取。



#### 排行榜

使用 Sorted Set 能够轻松完成排行榜。比如玩家的分数排行榜：

- 添加分数记录：`zadd 排行榜名 分数 玩家标识` 
- 查询玩家分数：`zscore 排行榜名 玩家标识` 
- 按名次查看排行榜：`zrevrange 排行榜名 起始位置 结束位置` 
- 查看玩家排名：`zrevrank 排行榜名 玩家标识` 
- 增减玩家分数：`zincrby 排行榜名 分数增量 玩家标识` 
- 移除玩家记录：`zrem 排行榜名 玩家标识` 
- 删除排行榜：`del 排行榜名` 

> 相同分数问题：
>
> 当两个玩家分数相同时，redis 排名是按字典排序，而一般应按达到这个分数的时间先后排序，即先达到这个分数的玩家排在前面。
>
> 为了解决这个问题可以使用带时间戳的分数：
>
> `带时间戳的分数 = 实际分数*10000000000 + (9999999999 – timestamp) ` 
>
> 时间戳占10位，需要取分数时去掉后10位即可。
>
> 这样会带来一个问题，Redis 的 score 最大能表示的整数范围是 -2<sup>53</sup> 至 2<sup>53</sup> ，最大能表示的整数为：9007199254740992，去除后10位后，玩家分数最高只能表示到 900719，可能不够用。此时可以采取缩小时间戳的长度来扩大分数表示范围。 



#### 计数器

Redis 的命令都是原子性的，可以轻松利用 incr 、decr 命令构建计数器。

使用场景如：

- 高并发的秒杀活动
- 分布式序列号的生成
- 限制一个手机号发多少条短信
- 一个接口一分钟限制多少请求
- 一个接口限制调用多少次



#### 分布式锁

在分布式系统中锁能够保证共享资源的同步，使用 redis 命令原子性的特点能够实现分布式锁。

锁要满足的条件：

- 互斥性：任何时刻只能有一个客户端持有锁。
- 不会发生死锁，即使持有锁的客户端崩溃未能主动解锁，也能保证后续其他客户端能够获取到锁。
- 容错性，只要大部分 redis 节点正常运行，客户端就能正确加锁、解锁。
- 解铃还须系铃人，加锁和解锁必须是同一个客户端，客户端不能解其他客户端加的锁。

实现方式：

- 加锁：给加锁的键设置一个值，并给定过期时间，命令：`set lock_key random_value NX PX 5000` ，`NX` 表示只有不存在时才能设置（当键存在时说明其他客户端获取了锁），`PX 5000` 是设置键过期时间 5000 毫秒，键自动过期可防止死锁。
- 解锁：判断锁的键中存的值是否等于当前客户端的，相等则删除键，即完成解锁。由于解锁时有两个步骤（判断值、删除键），为了保证操作原子性，需要使用 lua 脚本来执行两个操作：`if redis.call('get', KEYS[1]) == ARGV[1] then return redis.call('del', KEYS[1]) else return 0 end` 

> 注意事项：**加锁和解锁必须保证过程的原子性**，加锁时可以通过一条命令完成，不能先使用 `setnx` 设置键，然后再用 `expire` 设置过期时间；解锁时需要借助 lua 脚本一次执行，不能先 `get` 值，然后 `del` 删除值。



#### 签到

利用 Redis 的位操作能够实现大量用户的签到记录。比如使用用户的id（整形）作为要记录的位置，用户签到后，将这一位置的值置为 1，这样就能方便的记录大量用户的签到记录。



#### 定时操作

使用 Sorted Set，设置 score 为定时操作的时间戳，这样就能通过时间排序，查出需要定时处理的内容，如定时清理过期数据。

另外，还可以利用 Redis 的键过期功能，创建监听器监听 key 失效事件，在 key 过期时，完成定时处理的逻辑。



#### 去重

利用 Redis 的 Set 能够自动排除重复元素，只需要将元素往 set 中添加即可，还能够方便的对多个集合取交集、并集。



### 参考资料

- Redis 的 8 大应用场景: <https://segmentfault.com/a/1190000016188385> 
- Redis的7个应用场景: <https://www.cnblogs.com/NiceCui/p/7794659.html> 
- 使用Redis实现实时排行榜: <https://www.cnblogs.com/zhaoyan001/p/10782260.html> 
- Redis分布式锁的正确实现方式: <https://www.cnblogs.com/moxiaotao/p/10829799.html> 
- 分布式锁之Redis实现: <https://www.jianshu.com/p/47fd7f86c848> 
- Redis 入门：Redis 概念和基础: <https://toutiao.io/posts/47fg3nq> 



### 总结

Redis 是一个很好有的中间件，可用来做消息队列，可以用来做数据缓存，还可以用来做分布式锁，学好基本数据结构的存取，才能更好的用在实际项目中。