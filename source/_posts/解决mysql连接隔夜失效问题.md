---
title: 解决mysql连接隔夜失效问题
date: 2017-02-28 19:39:00
tags:
- 数据库
- mysql
- bug
categories: 
- 技术
---

### 问题描述

> 1. 系统使用hibernate连接数据库；
> 2. 启动服务器后，数据库操作正常，但时间超过8小时后，后台访问数据库时总是报错：com.mysql.jdbc.exceptions.jdbc4.CommunicationsException: The last packet successfully received 
>    from the server was 46,218,269 milliseconds ago.  The last packet sent successfully to the 
>    server was 46,218,270 milliseconds ago. is longer than the server configured value of 
>    'wait_timeout'. You should consider either expiring and/or testing connection validity before 
>    use in your application, increasing the server configured values for client timeouts, or using 
>    the Connector/J connection property 'autoReconnect=true' to avoid this problem.

---



### 原因

+ Mysql服务器默认的“wait_timeout”是8小时，也就是说一个connection空闲超过8个小时，Mysql将自动断开该 connection。而hibernate获取连接的时候认为连接池里的这个连接还是有效的，所以就拿来使用，这时候就报错了。

---

<!-- more -->

### 解决办法

#### 1. url 加参 

+ connection url 加参数：` &autoReconnect=true `

 #### 2. 修改数据库连接的超时时间

修改数据库连接的超时时间，这种方式会影响数据库性能，可能会出现大量休眠连接；

> 参考：http://dwz.cn/5dDEiB
>
> ​	   http://dwz.cn/5dFhRQ

1. 进入mysql，查看变量信息：` show variables like '%timeout%'; ` 结果如下：

| Variable_name       | Value | 说明    |
| ------------------- | ----- | ----- |
| interactive_timeout | 28800 | 默认为8h |
| wait_timeout        | 28800 | 默认为8h |

2. 修改方式

+ 方式一 运行命令：

  `set interactive_timeout=31536000;`

  `set wait_timeout=31536000;`

+ 方式二 打开 **my.ini **文档， 在

  \# The TCP/IP Port the MySQL Server will listen on
  port=3306下面添加

  ``````ini
  # this is myown dinifition for mysql connection timeout
  wait_timeout=31536000
  interactive_timeout=31536000
  ``````

3. 重启mysql服务
4. 查看修改后的超时时间：` show variables like '%timeout%'; ` 若显示以下结果则表名设置成功：

| Variable_name       | Value    | 说明        |
| ------------------- | -------- | --------- |
| interactive_timeout | 31536000 | 设置超时时间为一年 |
| wait_timeout        | 31536000 | 设置超时时间为一年 |

#### 3.修改hibernate配置 

> 参考：Hibernate连接数据库超时设置autoReconnect=true  http://xupo.iteye.com/blog/901327

+ 用hibernate需添加xml 代码：

  ``````xml
  <property name="connection.autoReconnect">true</property>
  <property name="connection.autoReconnectForPools">true</property>
  <property name="connection.is-connection-validation-required">true</property>
  ``````


+ 如需要用c3p0连接池：

  ``````xml
  <property name="hibernate.c3p0.acquire_increment">1</property>  
          <property name="hibernate.c3p0.idle_test_period">0</property> 
          <property name="hibernate.c3p0.timeout">0</property>
  <property name="hibernate.c3p0.validate">true</property>
  ``````

#### 4.采用c3p0或dbcp管理数据库连接池

+   在hibernate.cfg.xml中的c3p0链接池的配置中增加下面项：

    > 参考：Hibernate连接数据库超时设置autoReconnect=true  http://xupo.iteye.com/blog/901327

    ``````xml
    <property name="c3p0.idle_test_period">120</property>  
    <!-- seconds -->
    <!-- default: 0 --> 
    ``````

+   在dbcp中我们要处理好以下几个问题：

    +   对每个连接进行检查

    +   对一次操作数据库超过多少时间的连接进行移除

    +   每隔多少时间检测一次连接

    +   一个连接在连接多少时间后，就必须删除

        > 参考：DBCP连接池防止mysql 8小时超时  http://blog.csdn.net/korder/article/details/45671395
        >
        > ​	    配置_DruidDataSource参考配置  http://dwz.cn/5dLSUr

    ``````xml
     <bean id="dataSource"
                class="org.apache.commons.dbcp.BasicDataSource">
                <property name="driverClassName"
                    value="com.mysql.jdbc.Driver">
                </property>
                <property name="url"
                    value="jdbc:mysql://localhost:3306/mylog">
                </property>
                <property name="maxWait" value="20000">  </property>
                <property name="testOnBorrow" value="true"></property>
                <property name="testOnReturn" value="true"></property>
                <property name="testWhileIdle" value="true"></property>
                <property name="validationQuery" value="SELECT 1"></property>
                <property name="timeBetweenEvictionRunsMillis" value="3600000"></property>
                <property name="numTestsPerEvictionRun" value="50"></property>
                <property name="minEvictableIdleTimeMillis" value="120000"></property>
                <property name="removeAbandoned" value="true"/>
                <property name="removeAbandonedTimeout" value="6000000"/>
                <property name="username" value="root"></property>
                <property name="password" value="123456"></property>
     </bean>
    ``````

    ​