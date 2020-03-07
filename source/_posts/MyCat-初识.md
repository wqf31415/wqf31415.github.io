---
title: MyCat 初识
tags:
  - 数据库
  - mysql
categories:
  - 工具
date: 2020-02-19 13:38:58
---

### 概述

互联网时代，海量数据的存储和访问成为了系统设计与使用的瓶颈问题。这篇文章介绍了一个解决大数据量存储和查询新能问题的数据库中间件——MyCat，主要介绍了 MyCat 的一下概念，以及安装测试过程。

### 认识 MyCat

![](http://blog-images.qiniu.wqf31415.xyz/mycat_logo.png)

> 官网：<http://www.mycat.io> 

MyCat 是一个国内的、开源的、通用（兼容绝大多数数据库）的、高性能的、分布式的数据库中间件。Mycat 是用 java 语言编写的，基于阿里开源稳定的 Cobar 演变而来，经过开发团队彻底重构，使用 NIO 重构网络模块，优化 Buffer 内核，增强聚合、Join 等功能，是一个强大的数据库中间件。



<!-- more -->



用户可以把 MyCat 看作是一个数据库代理，可以直接使用 MySql 客户端或命令行访问，后端程序只需要改一下数据库连接配置就可以直接使用。而 MyCat 还支持跨数据库使用，不仅支持 MySql、Oracle、PostgreSql 等关系型数据库，还支持 MongoDB 这种 NoSQL ，但从业务端来看，面对的还是一个传统的数据库表，使用标准 SQL 进行操作，对于开发者来说就无需修改代码和增加复杂的配置，提高了开发速度。

MyCat 崇尚开源，承诺永不收费，永不闭源，持续推送开源社区的发展。

### 相关概念

#### MyCat 中的概念

##### 数据库中间件

数据库中间件是介于数据库和应用之间，进行数据处理与交互的中间服务，数据库中间件可以帮我们完成分片数据的读取，处理多个数据源、事务、聚合等任务。数据库中间件的性能与处理能力直接决定应用的读写性能。

##### 逻辑库（Schema）

对于应用来说，并不需要知道中间件的存在，开发人员只需要知道数据库的概念，所以数据库中间件可以被看做是一个或多个数据库集群构成的逻辑库。

##### 逻辑表（Table）

在分布式数据库中，对应用来说，读写数据的表就是逻辑表。

- 分片表，指那些原本很大数据的表，需要切分到多个数据库的表，每个分片都有一部分数据，所有分片构成了完整的数据。

- 非分片表，数据量比较小的不需要做切分的表

- ER 表，基于实物关系模型(Entity-Relationship Model) 的数据分片策略，字表的记录与所关联的父表记录存放在同一个数据分片上，即字表依赖于父表，通过表分组保证数据 join 不会跨库操作。

- 全局表，在业务系统中变动很少，类似字典表的表。特点是变动不频繁，数据量总体变化不大，数据规模不大，很少有超过数十万条记录。

  > MyCat 中通过数据冗余来解决字典表的 join，即所有分片上都有一份数据的拷贝，将所有字典表或具有字典表特性的表定义成全局表。

##### 分片节点（dataNode）

数据切分后，一张大表被分到不同的分片数据库上，每个表分片所在的数据库就是分片节点。

##### 节点主机（dataHost）

数据切分后，每个分片节点不一定独占一台机器，同一机器上面可以有多个分片数据库，这样一个或多个分片节点所在的机器就是节点主机。

为了规避单节点主机并发数限制，尽量将读写压力高的分片节点均衡的放在不同的节点主机上。

##### 分片规则（rule）

要将一张大表切分成数个分片表，就需要一定的规则，选择合适的分片规则非常重要，将极大地避免后续数据处理的难度。

##### 全局序列号（sequence）

数据切分后，原有的关系数据库主键约束在分布式条件下将无法使用，因此需要引入外部机制保证数据唯一性标识，这种保证全局性的数据唯一标识的机制就是全局序列号。

#### 数据切分

数据切分是按某种特定的条件，将存放在同一数据库中的数据分散存放到多个数据库，达到分散单台设备负载的效果。根据切分规则不同，可以分为垂直（纵向）切分、水平（横向）切分。

##### 垂直切分

垂直切分是按不同的表（或 schema）来切分到不同的数据库上。垂直拆分的优点是规则简单，实施方便，尤其适合各业务之间耦合度非常低，相互影响很小，业务逻辑非常清晰的系统。对于按模块开发的应用，垂直切分就非常方便，比如拆分成用户系统、订单系统、支付系统等。

> 在实际开发中，往往有些表难以做到完全独立，存在着 join 的情况，对于这类的表，就需要去做平衡，是数据库让步业务，共用一个数据源，还是分成多个库，业务之间通过接口来调用。

一般业务存在复杂 join 的场景是难以切分的，业务独立的易于切分。



##### 水平切分

水平切分是根据表中的数据的逻辑关系，将一个表中的数据按照某种条件拆分到多台数据库上。水平拆分稍微复杂一些，需要将一个表中数据拆分到不同数据库，拆分规则本身比按表名拆分更复杂，后期的数据维护也会更为复杂一些。

水平拆分是按照某个字段的某种规则来分散到多个库中，每个库中包含一部分数据。

常见的水平分片规则：

- 按用户 ID 求模，将数据分散到不同数据库，具有相同 ID 用户的数据都被分到一个库中
- 按照日期，将不同月、日的数据分散到不同库中
- 按照某个特定字段求模，或根据特定范围分散到不同库中，比如按地区切分



#### 不同人眼中的 MyCat

##### DBA

> MyCat 就是 MySQL Server，而 MyCat 后面连接的 MySQL Server，就好像是 MySQL 的存储引擎，如 InnoDB、MyISAM 等。因此，MyCat 本身并不存储数据，数据是在后端的 MySQL 上存储的，因此数据可靠性以及事物等都是 MySQL 保证的。简单说，MyCat 就是 MySQL 最佳伴侣，它在一定程度上让 MySQL 拥有跟 Oracle PK 的能力。

##### 软件工程师

> MyCat 就是一个近似等于 MySQL 的数据库服务器，你可以用连接 MySQL 的方式去连接 MyCat（除了端口不同，MyCat 默认端口 8066，而非 MySQL 的 3306），大多数情况，可以用你熟悉的对象映射框架使用 MyCat，但建议对于分片表，尽量使用基础的 SQL 语句，因为这样能达到最佳性能，特别是几千万甚至几百亿条记录的情况下。

##### 架构师

> MyCat 是一个强大的数据库中间件，不仅可以做读写分离、分库分表、容灾备份，还可以用于多租户应用开发、云平台基础设施、让你的架构具有很强的适应性和灵活性，借助即将发布的 MyCat 智能优化模块，系统的数据访问瓶颈和热点一目了然，根据这些统计分析数据，你可以自动或手动调整后端存储，将不同的表映射到不同存储引擎上，而整个应用的代码一行也不用改。



#### MyCat 原理

MyCat 原理中最重要的一个动作是 `拦截` ，它拦截了用户发过来的 SQL 语句，先对 SQL 做一些特定的分析，如：分片分析、路由分析、读写分离分析、缓存分析等，然后将此 SQL 发往后端的真实数据库并将返回的结果做适当的处理，最终再返回给用户。



#### MyCat 应用场景

- 读写分离、主从切换
- 分库分表，对超过 1000 万的表进行分片，最大支持 1000 亿的单表分片
- 多租户应用，每个应用一个库，但应用程序只连接 MyCat，从而不改造程序本身，实现多租户化
- 报表系统，借助于 MyCat 的分表能力，处理大规模报表的统计
- 替代 Hbase，分析大数据
- 海量数据实时查询的一种简单有效方案，比如 100 亿条频繁查询的记录需要在 3 秒内查询出结果，处理基于主键的查询，还可能存在范围查询或其他属性查询，此时 MyCat 可能是最简单有效的选择



### 安装体验

#### 环境

- jdk，需要1.7 及以上版本的 JDK。

- MySQL，MyCat 支持多种数据库，推荐使用 MySQL 做集群。可以使用 docker 开启多个 mysql 实例来进行测试。
- MyCat，官网 <http://www.mycat.io>  下载，提供编译好的安装包，支持 Windows、Linux、Mac、Solaris等系统。

#### 启动

我使用的是 Windows 操作系统来做测试，下载对应压缩包后，将其解压出来，放到一个没有中文和空格的目录下。

进入 `bin` 目录，运行命令 `mycat.bat console` 就可以在控制台中启动程序，也可以运行 `startup_nowrap.bat` 启动。

正确启动后，MyCat 默认连接端口是 `8066` ，可以使用数据库管理工具连接，或使用mysql 在命令中连接，如使用命令： `mysql -P8066 -uroot -p` 

![](http://blog-images.qiniu.wqf31415.xyz/mysql_connect_mycat.png)

> 注意：登陆用户名和密码在 `/conf/server.xml` 中配置，在其中的 `user` 标签中指定了用户名、密码和访问权限。



#### MyCat 配置

##### 防火墙配置

在 `server.xml` 中可以配置白名单和黑名单，限定访问 IP 和权限。

如：

```xml
<firewall>
    <whitehost>
    	<host user="mycat" host="127.0.0.1"></host> 
    </whitehost>
    <blacklist check="true">
    	<property name="selelctAllow">false</property> 
    </blacklist>
</firewall>
```

##### Schema 标签

在 `Schema.xml` 中可以配置 MyCat 逻辑库、表、分片规则、DataNode 和 DataSource，搞懂这些配置是使用 MyCat 的基础。

在 `Schema.xml` 文件中， `schema` 标签用来定义逻辑库，可有有多个逻辑库，每个逻辑库有自己相关的配置。

```xml
<schema name="TESTDB" checkSQLschema="false" sqlMaxLimit="100">
	<table name="travelrecord" dataNode="dn1,dn2,dn3" rule="auto-sharding-long" ></table>
</schema>
```

以上配置定义了一个逻辑库 `TESTDB` ，不检查 SQL 语句中的 schema，如果查询语句中没有 `limit` 限制查询数量，将自动添加 `limit 100` 限制查询 100 条记录；在逻辑库中定义了一张逻辑表 `travelrecord` 。

`schema` 标签相关属性：

| 属性           | 功能                                                         | 值          | 数量限制 |
| -------------- | ------------------------------------------------------------ | ----------- | -------- |
| dataNode       | 指定数据分片节点                                             | 任意 String | (0..1)   |
| checkSQLschema | 是否检查 SQL语句中的 schema，如果跟当前 `schema` 中名称相同，则会将 sql 中的 schema 去掉 | Boolean     | (1)      |
| sqlMaxLimit    | 如果 sql 语句中没有 limit 限定查询条数，将自动添加查询限定条数 | Integer     | (1)      |

##### table 标签

在 `Schema.xml` 中 `table` 标签用于定义逻辑表，所有需要拆分的表都需要在这个标签中定义。

```xml
<table name="travelrecord" dataNode="dn1,dn2,dn3" rule="auto-sharding-long"></table>
```

以上配置定义了一张逻辑表，名叫 `travelrecord` ，使用数据节点 `dn1` 、`dn2` 、 `dn3` ，数据将被分片存储到这三个节点上，指定分片规则使用 `auto-sharding-long` ，具体规则要到 `/conf/rule.xml` 文件中找到名为 `auto-sharding-long` 的配置。

相关属性：

| 属性          | 功能                                                         | 值      | 数量     |
| ------------- | ------------------------------------------------------------ | ------- | -------- |
| name          | d                                                            | String  | （1）    |
| dataNode      | 逻辑表所属的分片节点，如果只有一个节点即为不分片表，<abbr title="这个属性的值需要和 dataNode 标签中的 name 属性值相互对应">注</abbr> | String  | （1..*） |
| rule          | 逻辑表使用的规则名称，规则名称在 `rule.xml` 中定义，<abbr title="这个属性值必须与 tableRule 标签中的 name 属性值对应">注</abbr> | String  | （0..1） |
| ruleRequired  | 指定表是否绑定分片规则，<abbr title="如果值为 true 但未配置具体 rule 程序会报错">注</abbr> | Boolean | （0..1） |
| primaryKey    | 逻辑表对应真实表的主键，<abbr title="分片规则是使用非主键进行分片，在使用主键查询时，将会发送查询语句到所有配置的 DN 上；如果使用该属性配置真实表的主键，那么MyCat会缓存主键与具体DN的信息，下次再使用非主角进行查询时就不会进行广播式查询，而是直接发送查询语句给具体的 DN">例如</abbr> | String  | （1）    |
| type          | 定义逻辑表的类型，目前只有：全局表(`global`) 和普通表(不指定该值) | String  | （0..1） |
| autoIncrement | 指定表有使用自增长主键，默认值 `false`                       | Boolean | （0..1） |
| subTables     | 分表，添加方式：`subTables="t_order$1-2,t_order3"`           | String  | （1）    |
| needAddLimit  | 是否需要自动在每条语句后面加上 limit 限制。默认为 `true` ，默认限制数量为 `100` | Boolean | （0..1） |

###### childTable 标签

在 `table` 标签内，可以使用 `childTable` 来定义 E-R 分片的子表，通过标签上的属性与父表进行关联。

```xml
<table name="customer" primaryKey="ID" dataNode="dn1,dn2" rule="sharding-by-intfile">
    <childTable name="orders" primaryKey="ID" joinKey="customer_id" parentKey="id">
        <childTable name="order_items" joinKey="order_id" parentKey="id" />
    </childTable>
    <childTable name="customer_addr" primaryKey="ID" joinKey="customer_id" parentKey="id" />
</table>
```

以上配置定义了子表 `orders` 和 `customer_addr` ，子表中的 `customer_id` 与父表 `customer` 中的 `id` 关联；在 `orders` 表中又定义了子表 `order_items` 。

| 属性         | 功能                                         | 值      | 数量     |
| ------------ | -------------------------------------------- | ------- | -------- |
| name         | 子表表名                                     | String  | （1）    |
| joinKey      | 插入子表时用这个列的值查找父表存储的数据节点 | String  | （1）    |
| parentKey    | 父表中建立关系的列名                         | String  | （1）    |
| primaryKey   | 当前表主键                                   | String  | （0..1） |
| needAddLimit | 是否需要添加 limit 限制                      | Boolean | （0..1） |

##### dataNode 标签

在 `schema.xml` 中的 `datanode` 标签用来定义数据节点，也就是所谓的数据分片。一个 dataNode 就是一个独立的数据分片。

```xml
<dataNode name="dn1" dataHost="lch3307" database="db1" ></dataNode>
```

上述配置定义了一个名为 `dn1` 的数据节点，使用名为 `lch3307` 的数据库实例上的 `db1` 物理数据库。

| 属性     | 功能                                                         | 值     | 数量  |
| -------- | ------------------------------------------------------------ | ------ | ----- |
| name     | 数据节点名称，需要唯一，在 `table` 标签中会用到这个名字      | String | （1） |
| dataHost | 定义这个分片属于哪个数据库实例，属性值引用的是 `dataHost` 标签的 `name` 属性 | String | （1） |
| database | 定义分片属于哪个具体数据库实例的具体数据库                   | String | （1） |

##### dataHost 标签

`schema.xml` 中的 `dataHost` 标签用于定义数据库实例、读写分离配置、心跳语句。

```xml
<dataHost name="localhost1" maxCon="1000" minCon="10" balance="0"
writeType="0" dbType="mysql" dbDriver="native">
    <heartbeat>select user()</heartbeat>
    <!-- can have multi write hosts -->
    <writeHost host="hostM1" url="localhost:3306" user="root" 
    password="123456">
    <!-- can have multi read hosts -->
    <!-- <readHost host="hostS1" url="localhost:3306" user="root" password="123456"
    /> -->
    </writeHost>
    <!-- <writeHost host="hostM2" url="localhost:3316" user="root" password="123456"/> -->
</dataHost>
```



| 属性      | 功能                                                         | 值      | 数量  |
| --------- | ------------------------------------------------------------ | ------- | ----- |
| name      | 数据主机名称，在 `dataNode` 标签中会引用                     | String  | （1） |
| maxCon    | 每个读写实例连接池最大连接，<abbr title="标签内嵌的 writeHost 和 readHost 都会使用这个属性值来确定实例化连接池的最大连接数">注</abbr> | Integer | （1） |
| minCon    | 每个读写实例连接池最小连接，初始化连接池的大小               | Integer | （1） |
| balance   | 负载均衡类型：<br /> `0` 不开启读写分离，所有读操作都发送到当前可用的 writeHost 上；<br /> `1` 全部的 readHost 的 stand by writeHost 参与 select 语句的负载均衡，<abbr title="当双主双从模式（M1→S1，M2→S2，且 M1 和 M2 互为主备），正常情况下，M2，S1，S2 都参与 select 语句的负载均衡">举例</abbr>；<br /> `2` 所有读操作都随机在 writeHost、readHost 上分发；<br /> `3` 所有读请求随机分发到 writeHost 对应的 readHost 执行，writeHost 不负担读压力。 | Integer | （1） |
| writeType | 负载均衡类型：<br /> `0` 所有写操作都发送到第一个配置的 writeHost ，第一个挂了切到第二个还生存的 writeHost，重启后以切换后的为准，切换记录在配置文件 `dnindex.properties` ；<br /> `1` 所有写操作都随机打发送到配置的 writeHost，1.5 版本后废弃不推荐 | Integer | （1） |
| dbType    | 后端连接的数据库类型，目前支持二级制的 mysql 协议，还有其他使用 JDBC 连接的数据库，如 MongoDB、Oracle、spark 等 | String  | （1） |
| dbDriver  | 连接后端数据库使用的 Driver，目前可选值有 `native` (使用二进制 mysql 协议，可以使用 MySQL 和 MariaDB)、`JDBC` 可以连接使用 JDBC 驱动的数据库。 | String  | （1） |

######  heartbeat 标签

指定用于检测后端数据库的心跳语句。MySQL 可以使用 `select user()` ，Oracle 可以使用 `select 1 from dual` 。

###### writeHost 、 readHost 标签

指定数据库相关配置，用于实例化后端连接池，writeHost 指定写实例，readHost 指定读实例。

在一个 dataHost 内可以定义多个 writeHost 和 readHost，但是如果 writeHost 指定的数据库宕机，那么这个 writeHost 绑定的所有 readHost 都将不可用。另一方面由于这个 writeHost 宕机系统会自动检测到，并切换到备用的 writeHost 。

```xml

```



| 属性         | 功能                                                         | 值     | 数量  |
| ------------ | ------------------------------------------------------------ | ------ | ----- |
| host         | 标识不同的实例，一般 writeHost 使用 *M1，readHost 使用 *S1   | String | （1） |
| url          | 后端实例连接地址，如果使用 `native` 的 dbDriver，一般是 `host:port` 形式；<br />如果是 JDBC 或其他 dbDriver，则需要特殊指定，如使用 JDBC 时指定为 `jdbc:mysql://localhost:3306` | String | （1） |
| password     | 数据库连接密码                                               | String | （1） |
| user         | 数据库用户名                                                 | String | （1） |
| weight       | 在 readHost 中作为 readHost 中作为读节点的权重               | String | （1） |
| usingDecrypt | 是否读密码加密：`0` 不加密，`1` 使用加密程序对密码加密       | String | （1） |

> 对密码加密的命令：
>
> `java -cp Mycat-server-xxx.jar io.mycat.util.DecryUtil 1:host:user:password`
>
> 参数中的 `1` 是 db 端加密标志，`host` 为 dataHost 的 host 名称



##### server.xml 配置

保存了 MyCat 需要的系统配置信息，在代码内的直接映射类为 `SystemConfig` 类。

###### user 标签

用于定义登陆用户和权限。

```xml
<user name="user">
    <property name="password">123456</property>
    <property name="schemas">TESTDB,db1</property>
    <property name="readOnly">true</property>
</user>
```

如上配置，定义了一个名叫 `user` 的用户，密码是 `123456` ，可以访问 `TESTDB` 和 `db1` 数据库，但只有读取权限。

在 `user` 标签里可以指定一些属性，可以修改对应名称属性标签中的值：

| 属性名称   | 功能                                                         |
| ---------- | ------------------------------------------------------------ |
| password   | 密码                                                         |
| schemas    | 可访问的数据库，多个数据库以 `,` 分隔                        |
| readOnly   | 限制用户是否只读                                             |
| benchmark  | mycat 连接服务器处理：benchmark 基准，当前端的整体连接数达到基准数值时，开始拒绝该用户的连接，0 或者不设置表示不限制 |
| useDecrypt | 是否对密码加密，默认值 0 不加密，1 加密                      |

> 使用加密程序对密码进行加密，加密命令是执行 mycat.jar 程序：
>
> `java -cp Mycat-server-xxx.jar io.mycat.util.DecryptUtil 0:user:password`
>
> `Mycat-server-xxx.jar` 是mycat download 目录文件
>
> `0:user:password` 中 0 是前端加密标志

###### privileges 标签

对用户 scheme 和下级的 table 进行精细化权限控制，其中 check 属性指定是否进行权限检查，默认值 false。

privileges 下可以配置多个 scheme，对多个库和表进行精细的 DML 权限控制。

在 scheme 和 table 中的 dml 值为四位数字，依次用于指定 insert、update、select、delete 权限，有权限则将对应位置的数字值为1，没有权限则值为 0。如只有查询权限则 `dml="0010"` 。

```xml
<user name="user">
    <property name="password">123456</property>
    <property name="schemas">TESTDB,db1</property>
    <privileges check="true">
    	<scheme name="TESTDB" dml="0110">
    		<table name="table_1" dml="0111"/>
    	</scheme>
    </privileges>
</user>
```

###### system 标签

system 标签用于配置系统参数，这个标签中全都使用 property 子标签来配置参数，property 标签中的 name 属性就是要配置的系统参数。

- **charset 属性** ：设置字符集

  ```xml
  <system>
  	<property name="charset">utf8</property>
  </system>
  ```

  > 如果需要使用 utf8mb2 等特殊字符集，可以在 index_to_charset.properties 配置中配置数据库短的字符集 ID=字符集
  >
  > 配置字符集时，一定要保持 mycat 和后端数据库的字符集一致。

- **defaultSqlParser 属性** ：指定 sql 解析器，1.4 以后默认值为：`druidparser` ，可选值 `fdbparser` 

- **processors** ： 指定系统可用线程数，默认为 CPU 核心线程数，影响 `processorBufferPool`、`processorBufferLocalPercent`、`processorExecutor` 属性，`NIOProcessor` 的个数也是由这个参数指定的，所以调优的时候可以适当调高这个数值。

- TCP 连接相关参数

- MySql 连接相关参数

- 心跳属性

- 服务相关属性：`bindIp` 服务绑定 IP 地址，默认 `0.0.0.0` ；`serverPort` 服务端口，默认 8066；`managePort` myCat 管理端口，默认 9066

- *fakeMySQLVersion* ：模拟的 MySQL 版本，默认值为 5.6 版本，支持 5.5、5.6。不建议修改这个值，可能会导致错误

- 全局表一致性检测

##### rule.xml 配置

`rule.xml` 中配置了表拆分的规则，可以灵活的对表使用不同的分片算法，或对表使用相同算法，但参数不同。

###### tableRule 标签

定义表规则

```xml
<tableRule name="rule1">
    <rule>
        <columns>id</columns>
        <algorithm>func1</algorithm>
    </rule>
</tableRule>
```

> name 指定唯一名称，区分不同的表规则
>
> rule 中指定分片使用的列和算法
>
> columns 指定分片使用的列
>
> algorithm 指定分片算法，指定算法时引用 function 标签中的 name 属性

###### function 标签

```xml
<function name="hash-int"
class="io.mycat.route.function.PartitionByFileMap">
	<property name="mapFile">partition-hash-int.txt</property>
</function>
```

> name 为分片算法名称
>
> class 为算法具体类名称
>
> property 为算法中使用的一些属性



#### 测试

修改好 mycat 配置，使用命令 `mycat console` 启动，启动后可以使用 mysql 自带的命令行工具连接 mycat：

```bash
mysql -P8066 -uroot -p
```

也可以使用像 navicat 之类的数据库管理工具连接，数据库类型选择 MySQL，修改端口为 mycat 端口 8066，填入设定的用户名，密码即可完成连接。

正确连接 mycat 后，可以查看到在 scheme.xml 中配置的逻辑库。

在使用 sql 插入数据前，需要先到具体的后端数据库中创建相应的实体库和表，否则插入数据会报错。



### 遇到的问题

#### JRE 环境中缺少 'server' JVM

使用命令 `mycat.bat console` 启动 MyCat 时，提示 `Error: missing 'server' JVM at 'G:\develop\Java\jre1.8.0_121\bin\server\jvm.dll'.` ，具体错误日志如下：

```
wrapper  | --> Wrapper Started as Console
wrapper  | Launching a JVM...
jvm 1    | Error: missing `server' JVM at `G:\develop\Java\jre1.8.0_121\bin\server\jvm.dll'.
jvm 1    | Please install or use the JRE or JDK that contains these missing components.
wrapper  | JVM exited while loading the application.
```

##### 解决方法

将 `JAVA_HOME/jdk1.8.0_121/jre/bin` 目录下的 `server` 文件夹复制到 `jre1.8.0_121/bin/` 目录下。



#### JVM 配置参数无效

我是用的是 JDK 8 ，在使用 `mycat.bat console` 启动 MyCat 时，提示设置最大堆容量 `-Xmx4G` 无效，超过了最大可用空间。

```
wrapper  | --> Wrapper Started as Console
wrapper  | Launching a JVM...
jvm 1    | Error: Could not create the Java Virtual Machine.
jvm 1    | Error: A fatal exception has occurred. Program will exit.
jvm 1    | Java HotSpot(TM) Server VM warning: ignoring option MaxPermSize=64M; support was removed in 8.0
jvm 1    | Invalid maximum heap size: -Xmx4G
jvm 1    | The specified size exceeds the maximum representable size.
wrapper  | JVM exited while loading the application.
```



##### 解决办法

打开 `/conf/wrapper.conf` 文件，搜索 `-Xmx4G` ，大概在 36 行，在这一行前面加一个 `#` ，将其注释掉即可。

![](http://blog-images.qiniu.wqf31415.xyz/mycat_jvm_param_error.png)



### 参考资料

- [《MyCat 权威指南》](http://www.mycat.io/document/mycat-definitive-guide.pdf) 
- [MyCat WiKi](https://github.com/MyCATApache/Mycat-Server/wiki)



### 总结

官方文档真的特别良心，从基本原理到实际应用场景，应有尽有，而且**都是中文**，真是太棒了！只是有一点不太好，pdf 文档阅读没有目录大纲，内容又特别多，导致看的时候想要跳一下要翻到文档开头的目录去找。另外文档中有个别错别字，不过影响不大。总的来说，这次 MyCat 初体验非常舒心！

