---
title: SpringBoot 使用 Liquibase
date: 2019-03-12 16:33:42
tags:
- springboot
- liquibase
- database
categories:
- 技术
---

### 概述
本文主要介绍了 什么是 Liquibase，以及在 SpringBoot 项目中集成使用 Liquibase 对数据库表进行管理，包括自动创建数据库表、自动初始化数据、更新表结构。

### 认识 Liquibase
> 官网：Liquibase | Database Refactoring | Liquibase: [http://www.liquibase.org/](http://www.liquibase.org/)
Liquibase 是用于数据库重构、管理、记录变化与回滚的开源工具。
在写代码的时候，我们使用 Git 或 subversion 对代码进行版本控制，在数据库中，我们可以使用 liquibase 对数据库表进行版本控制。

<!-- more -->

### Liquibase 特点
- 支持项目代码多人多分支开发与合并；
- 支持多种数据库类型：MySQL、PostgreSQL、Oracle、Sql Server、DB2、H2等，更多信息请移步官网：  [http://www.liquibase.org/databases.html](http://www.liquibase.org/databases.html) ；
- 支持多种变化日志格式：XML、YML、JSON、SQL；
- 支持自定义上下文执行逻辑，可指定需要运行的上下文；
- 集群安全的数据库更新；
- 可生成数据库修改文档(HTML)；
- 使用命令对比两个数据库；
- 可以使用 build 工具(Command Line、Ant、Maven)运行，也可以嵌入到 Application 中；
- 可以自动生成数据库 SQL 脚本，供 DBA 重构代码使用；
- 可以使用离线数据库；

### 使用 Liquibase
#### 环境依赖
+ windows 操作系统 PC
+ Java 1.8 运行环境，liquibase 2.x 依赖 java 1.5+，3.x 依赖 java1.6+
+ Maven 3.0
+ MySQL 5.7
+ liquibase 3.6.3
+ (可选)Navicat for MySQL ，用于查看数据库表结构与数据

#### 使用命令行体验 Liquibase
##### 下载压缩包
> 官网下载地址：[https://download.liquibase.org/download/?frm=n](https://download.liquibase.org/download/?frm=n "download liquibase")
> liquibase-3.6.3-bin.zip: [我的下载地址](http://source.qiniu.wqf31415.xyz/liquibase-3.6.3-bin.zip "我的下载地址")

![](http://blog-images.qiniu.wqf31415.xyz/liquibase_download.png "download liquibase")

##### 解压文件、下载 JDBC jar 包
将上一步下载好的 liquibase zip 包解压出来。
我电脑上使用的 MySQL ，所以我需要下载 mysql-connector-java 用来连接操作数据库，我这里使用的版本是 8.0.13，下载下来后将这个 jar 包放到 liquibase 根目录下的 `lib` 文件夹中，使用 liquibase 时，会自动扫描 `lib` 下的包。
> 下载地址：[mysql-connector-java-8.0.13](http://source.qiniu.wqf31415.xyz/mysql-connector-java-8.0.13.jar "mysql-connector-java-8.0.13")

##### 创建数据库修改日志文件(database chanagelog file)
liquibase 支持多种格式的日志文件，包括 XML、YML、JSON、SQL，官方推荐使用 xml，个人喜欢更加简洁的 yml 格式。在 liquibase 根目录下创建文件夹 `chanagelog` ，用来存储修改日志文件。从官网拷贝示例，存储到 `chanagelog` 目录下，文件名为 `master.yml` ，文件内容如下：
> 注意直接从官方文档中考出来的，要修改 databaseChangeLog.preConditions.runningAs.username ，改为自己数据库的用户名，我使用的是 root 。

  ``````yml
databaseChangeLog:
  - preConditions:
    - runningAs:
        username: root

  - changeSet:
      id: 1
      author: nvoxland
      changes:
        - createTable:
            tableName: person
            columns:
              - column:
                  name: id
                  type: int
                  autoIncrement: true
                  constraints:
                    primaryKey: true
                    nullable: false
              - column:
                  name: firstname
                  type: varchar(50)
              - column:
                  name: lastname
                  type: varchar(50)
                  constraints:
                    nullable: false
              - column:
                  name: state
                  type: char(2)

  - changeSet:
      id: 2
      author: nvoxland
      changes:
        - addColumn:
            tableName: person
            columns:
              - column:
                  name: username
                  type: varchar(8)

  - changeSet:
      id: 3
      author: nvoxland
      changes:
        - addLookupTable:
            existingTableName: person
            existingColumnName: state
            newTableName: state
            newColumnName: id
            newColumnDataType: char(2)

   
  ``````

##### 运行命令
在数据库中新建数据库 `test_liquibase`，在 liquibase 根目录打开命令行，执行命令

``````
liquibase.bat --url="jdbc:mysql://localhost:3306/test_liquibase?useUnicode=true&characterEncoding=utf8&serverTimezone=GMT%2B8" --changeLogFile="/chanagelog/master.yml" --username=root --password=123456 --driver=com.mysql.cj.jdbc.Driver update 
``````

> liquibase 命令中必须的必须选项有：
  --url=数据库连接，其中 serverTimezone=GMT%2B8 参数用来指定时区，在使用高版本 jdbc 时需要，不指定可能会报时区错误
  --chanagelog=数据库修改日志文件
  --username=数据库用户名
  --password=数据库密码
  --driver=数据库连接驱动
  最后的 update 是 liquibase 命令，必须放到选项的后面。
  关于命令的更多内容可以使用 `liquibase --help` 命令查看帮助信息，也可以到官网查询详细信息: [http://www.liquibase.org/documentation/command_line.html](http://www.liquibase.org/documentation/command_line.html)

执行结果：
![](http://blog-images.qiniu.wqf31415.xyz/liquibase_update_by_cmd.png "update success")

##### 检查数据库
查看 `test_liquibase` 数据库，发现多了 4 张表：
![](http://blog-images.qiniu.wqf31415.xyz/liquibase_create_table.png "数据库表")

打开 databasechanagelog 表，发现在 `master.yml` 中的 3 个修改都已经被执行了(表中 EXECTYPE 值为 EXECUTED)。
![](http://blog-images.qiniu.wqf31415.xyz/liquibase_create_table_2.png "databasechanagelog")

#### SpringBoot 项目集成 Liquibase
SpringBoot 提供了自动装配，大大降低了其它组件的使用难度，在使用 Liquibase 时，可以说非常简单了。

##### 创建项目
创建一个 SpringBoot 项目，添加依赖 web、jpa、liquibase，最终项目 `pom.xml` 如下：
``````xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
	<modelVersion>4.0.0</modelVersion>
	<parent>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter-parent</artifactId>
		<version>2.1.3.RELEASE</version>
		<relativePath/> <!-- lookup parent from repository -->
	</parent>
	<groupId>xyz.wqf</groupId>
	<artifactId>liquibasedemo</artifactId>
	<version>0.0.1-SNAPSHOT</version>
	<name>liquibasedemo</name>
	<description>Demo project for Spring Boot with Liquibase</description>

	<properties>
		<java.version>1.8</java.version>
	</properties>

	<dependencies>
		<!--jpa-->
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-data-jpa</artifactId>
		</dependency>
		
		<!--web-->
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-web</artifactId>
		</dependency>
		
		<!--liquibase-->
		<dependency>
			<groupId>org.liquibase</groupId>
			<artifactId>liquibase-core</artifactId>
		</dependency>
		<dependency>
			<groupId>mysql</groupId>
			<artifactId>mysql-connector-java</artifactId>
			<scope>runtime</scope>
		</dependency>
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-test</artifactId>
			<scope>test</scope>
		</dependency>
	</dependencies>

	<build>
		<plugins>
			<plugin>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-maven-plugin</artifactId>
			</plugin>
		</plugins>
	</build>
</project>
``````

##### 添加 changelog 与数据
为了放管理，我们在项目 `resources` 目录下创建 `liquibase` 目录用于存放 liquibase 相关的配置文件，在 `liquibase` 目录下创建 `changelog` 目录存放所有 changelog 文件，创建 `initdata` 目录用于存放初始化项目时的数据。
![](http://blog-images.qiniu.wqf31415.xyz/liquibase_springboot_resources.png "项目 resources 目录")

###### changelog
在 `liquibase` 目录下的 `master.xml` 为 liquibase 的入口，通过 include 标签将其它的 changelog 文件引入进来。
- master.xml
  ``````xml
  <?xml version="1.0" encoding="UTF-8"?>
  <databaseChangeLog
        xmlns="http://www.liquibase.org/xml/ns/dbchangelog"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xmlns:ext="http://www.liquibase.org/xml/ns/dbchangelog-ext"
        xsi:schemaLocation="http://www.liquibase.org/xml/ns/dbchangelog http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.1.xsd
        http://www.liquibase.org/xml/ns/dbchangelog-ext http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-ext.xsd">

    <include file="classpath:liquibase/changelog/init_00000000000000.xml" relativeToChangelogFile="false"/>
    <include file="classpath:liquibase/changelog/user_20190313171720.xml" relativeToChangelogFile="false"/>
	
  </databaseChangeLog>
  ``````

- init_00000000000000.xml
  ``````xml
<databaseChangeLog
        xmlns="http://www.liquibase.org/xml/ns/dbchangelog"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xmlns:ext="http://www.liquibase.org/xml/ns/dbchangelog-ext"
        xsi:schemaLocation="http://www.liquibase.org/xml/ns/dbchangelog http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.1.xsd
        http://www.liquibase.org/xml/ns/dbchangelog-ext http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-ext.xsd">

    <property name="now" value="now()" dbms="mysql,h2"/>
    <property name="now" value="current_timestamp" dbms="postgresql"/>
    <property name="now" value="sysdate" dbms="oracle"/>

    <property name="autoIncrement" value="true" dbms="mysql,h2,postgresql,oracle"/>

    <property name="floatType" value="float4" dbms="postgresql, h2"/>
    <property name="floatType" value="float" dbms="mysql, oracle"/>

    <changeSet id="20190313172000" author="wqf31415">
        <createTable tableName="book">
            <column name="id" type="bigint" autoIncrement="${autoIncrement}">
                <constraints nullable="false" primaryKey="true"/>
            </column>

            <column name="title" type="varchar(255)" remarks="书名">
                <constraints nullable="false"/>
            </column>

            <column name="description" type="text" remarks="描述">
                <constraints nullable="true"/>
            </column>

            <column name="price" type="${floatType}" remarks="价格">
                <constraints nullable="true"/>
            </column>

            <column name="add_time" type="timestamp" defaultValue="${now}">
                <constraints nullable="true"/>
            </column>
        </createTable>
    </changeSet>
</databaseChangeLog>
  ``````
  
- user_20190313171720.xml
  ``````xml
  <databaseChangeLog
        xmlns="http://www.liquibase.org/xml/ns/dbchangelog"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xmlns:ext="http://www.liquibase.org/xml/ns/dbchangelog-ext"
        xsi:schemaLocation="http://www.liquibase.org/xml/ns/dbchangelog http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.1.xsd
        http://www.liquibase.org/xml/ns/dbchangelog-ext http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-ext.xsd">
  
    <property name="now" value="now()" dbms="mysql,h2"/>
    <property name="now" value="current_timestamp" dbms="postgresql"/>
    <property name="now" value="sysdate" dbms="oracle"/>
  
    <property name="autoIncrement" value="true" dbms="mysql,h2,postgresql,oracle"/>
  
    <property name="floatType" value="float4" dbms="postgresql, h2"/>
    <property name="floatType" value="float" dbms="mysql, oracle"/>
  
    <changeSet id="20190313172800" author="wqf31415">
        <createTable tableName="user">
            <column name="id" autoIncrement="${autoIncrement}" type="bigint">
                <constraints nullable="false" primaryKey="true" />
            </column>
  
            <column name="name" type="varchar(255)" remarks="姓名">
                <constraints nullable="true"/>
            </column>
  
            <column name="password" type="varchar(255)" remarks="密码">
                <constraints nullable="true"/>
            </column>
  
            <column name="age" type="tinyint" remarks="年龄">
                <constraints nullable="true"/>
            </column>
  
            <column name="birthday" type="date" remarks="生日">
                <constraints nullable="true"/>
            </column>
        </createTable>
  
  	<!--导入数据-->
        <loadData tableName="user" file="classpath:liquibase/initdata/user.csv" separator=";" encoding="UTF-8"/>
    </changeSet>
  </databaseChangeLog>
  ``````
  
###### 数据
在项目初始化，liquibase 完成建表后，可以导入预先定义好的数据。

- user.csv
``````csv
id;name;password;age;birthday
1;zhangsan;abc123;18;2001-03-23
2;lisi;ls1990;27;1990-11-08
``````

##### 修改配置文件
修改项目配置文件，添加数据库相关的配置，指定 liquibase 的 changelog文件。
``````yml
server:
  port: 8909
spring:
  datasource:
    url: jdbc:mysql://172.16.19.229:3306/liquibase_demo?useUnicode=true&characterEncoding=utf8&serverTimezone=GMT%2B8
    username: root
    password: root
    driver-class-name: com.mysql.cj.jdbc.Driver
  jpa:
    show-sql: true
  application:
    name: LiquibaseDemo
  liquibase:
    change-log: classpath:liquibase/master.xml # 指定 changelog 文件
``````

##### 运行项目
在运行项目前需要提前创建 url 中指定的数据库，我这里需要创建名为 `liquibase_demo` 的数据库。
运行项目，查看数据库，建表正确且 `user` 表中数据正确。
![](http://blog-images.qiniu.wqf31415.xyz/liquibase_data.png "初始化的数据")

### 注意事项
#### SpringBoot 配置项
> 下表是在 SpringBoot 2.1.3.RELEASE 使用 liquibase 的配置项
  在 SpringBoot 1.x 版本中 liquibase 配置项少一些，且配置项没有 spring，如 2.x 中的 `spring.liquibase.change-log` ，在 1.x 中为 `liquibase.change-log`。

|配置项|默认值|注释|
|:----:|:----:|:----|
|spring.liquibase.change-log|classpath:/db/changelog/db.changelog-master.yaml|changeLogFile 配置路径|
|spring.liquibase.check-change-log-location|true|是否检查 changelog 配置路径存在|
|spring.liquibase.contexts||只有指定的 context 的 changelog 才会被执行，多个 context 之间以逗号分隔|
|spring.liquibase.default-schema||默认数据库|
|spring.liquibase.liquibase-schema||用于存储 liquibase 对象的数据库|
|spring.liquibase.liquibase-tablespace||用于 liquibase 对象的表空间|
|spring.liquibase.database-change-log-table|DATABASECHANGELOG|存储数据库改变记录执行情况的表名|
|spring.liquibase.database-change-log-lock-table|DATABASECHANGELOGLOCK|存储当前使用 liquibase 的用户信息表名|
|spring.liquibase.drop-first|false|是否先删除表|
|spring.liquibase.enabled|true|是否启用 liquibase|
|spring.liquibase.user||liquibase 使用的数据库用户名，不指定时使用 spring.datasource 中的|
|spring.liquibase.password||liquibase 使用的数据库用户密码，不指定时使用 spring.datasource 中的|
|spring.liquibase.url||liquibase 使用的数据库url，不指定时使用 spring.datasource 中的|
|spring.liquibase.labels||指定标签的才会运行，多个标签以逗号分隔|
|spring.liquibase.parameters||changelog 参数|
|spring.liquibase.rollback-file||当执行升级时写回滚 SQL 的文件|
|spring.liquibase.test-rollback-on-update||执行更新前是否验证回滚|

#### changelog 文件编写
在上面示例中演示了 liquibase 的创建表(createTable)、加载数据(loadData)功能，除此之外，还可以创建索引(createIndex)、添加主键(addPrimaryKey)、添加唯一约束(addUniqueConstraint)、修改数据类型(modifyDataType)、添加查询表(addLookupTable)、添加自增(addAutoIncrement)、添加默认值(addDefaultValue)、添加外键约束(addNotNullConstraint)等等
changelog 文件 xml 根目录为 databaseChangeLog，可以使用 include 标签引入其它 changelog 文件，使用 includeAll 标签引入 changelog 目录，使用 property 标签定义参数，使用 preConditions 标签添加前置条件，在 chageSet 标签内定义修改内容。
``````xml
<databaseChangeLog
        xmlns="http://www.liquibase.org/xml/ns/dbchangelog"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xmlns:ext="http://www.liquibase.org/xml/ns/dbchangelog"
        xsi:schemaLocation="http://www.liquibase.org/xml/ns/dbchangelog http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.1.xsd
        http://www.liquibase.org/xml/ns/dbchangelog http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.6.xsd">
    <property name="now" value="now()" dbms="mysql,h2"/>
    <property name="now" value="current_timestamp" dbms="postgresql"/>
    <property name="now" value="sysdate" dbms="oracle"/>

    <property name="autoIncrement" value="true" dbms="mysql,h2,postgresql,oracle"/>

    <property name="floatType" value="float4" dbms="postgresql, h2"/>
    <property name="floatType" value="float" dbms="mysql, oracle"/>
	
	<!-- property 标签中定义的参数，可以使用取值表达式获取 ${property-name} -->
	
	<include file="classpath:liquibase/changelog/init_00000000000000.xml" relativeToChangelogFile="false"/>
	
	<includeAll path="classpath:liquibase/changelog" />
	
	<preConditions>
        <tableExists tableName="changelog_example"/>
    </preConditions>
	
	<changeSet id="20190313172800" author="wqf31415">
		<createTable tableName="user">
			<column name="id" autoIncrement="${autoIncrement}" type="bigint">
				<constraints nullable="false" primaryKey="true" />
			</column>

			<column name="name" type="varchar(255)" remarks="姓名">
				<constraints nullable="true"/>
			</column>
		</createTable>
	</changeSet>
</databaseChangeLog>
``````

##### 修改集(changeSet)
变化集，一个变化集中可以有多个修改，每个变化集都需要指定 id 和修改人(author)，要求 id + author + filepath 必须唯一，id另外还可以指定上下文(context)、数据库系统(dbms)等信息。
Liquibase changeSet 常用属性(基于 liquibase-3.6)
|属性名|值类型|默认值|注释|
|:----:|:----:|:----:|:----|
|id|String||(必需)修改集编号|
|author|String||(必需)修改人|
|context|String||修改上下文，指定后可以修改 springboot 配置文件中 `spring.liquibase.context` 项，来指定需执行的修改|
|labels|String||标签，与 context 功能相同|
|dbms|String||数据库系统，只用使用指定的数据库时才会执行，如 mysql、h2、postgresql、oracle等，多个数据库系统时以逗号分隔|
|alwaysRun|Boolean|false|如果为 true 则每次 update 时都会执行|
|runOnChange|Boolean|false|如果未 true，则每次 checksum 改变时都会执行|
|ignore|Boolean|false|是否忽略此修改集|
|failOnError|Boolean|true|如果为 false ，在执行修改时出现错误，liquibase 不会停止，会继续执行其他修改|
|runInTransaction|Boolean|true|是否在执行时使用数据库事务管理|
|onValidationFail|枚举，可选值：HALT、MARK_RAN|HALT|验证失败后的处理方式，停止运行或记录运行状态|
示例：
``````xml
<databaseChangeLog
        xmlns="http://www.liquibase.org/xml/ns/dbchangelog"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xmlns:ext="http://www.liquibase.org/xml/ns/dbchangelog"
        xsi:schemaLocation="http://www.liquibase.org/xml/ns/dbchangelog http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.1.xsd
        http://www.liquibase.org/xml/ns/dbchangelog http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.6.xsd">
    <changeSet id="20190314135820" author="wqf31415" context="dev" dbms="mysql"
               failOnError="true" onValidationFail="HALT"  >
		<!-- 修改集内容 -->
	</changeSet>
</databaseChangeLog>
``````

###### 创建表(createTable)
用于创建新的数据库表，写在 changeSet 标签内。
createTable 标签属性(基于 Liqubase-3.6)
|属性名|值类型|默认值|注释|
|:----:|:----:|:----:|:----|
|tableName|String||(必需)表名|
|catalogName|String||目录名|
|schemaName|String||数据库名|
|tablespace|String||表空间|
|remarks|String||注释|
示例：
``````xml
    <changeSet id="20190314135820" author="wqf31415" context="dev" dbms="mysql"
               failOnError="true" onValidationFail="HALT" labels="lab" ignore="false" runOrder="">
        <createTable tableName="changelog_example" catalogName="liquibase_demo" schemaName="liquibase_demo"
                     remarks="创建表changelog_example" tablespace="ts_changelog_example">
            <column name="id" type="bigint" autoIncrement="${autoIncrement}">
                <constraints primaryKey="true" nullable="false"/>
            </column>

            <column name="name" type="varchar(255)" remarks="姓名" >
                <constraints nullable="true" unique="true" uniqueConstraintName="unique_name"/>
            </column>

            <column name="active" type="bit" defaultValueBoolean="true" defaultValue="0">
                <constraints nullable="true" />
            </column>
        </createTable>
    </changeSet>
``````

####### 列(column)
在创建表或给表添加列时，需要添加 column 标签，用来指定列的属性。
column 标签常用属性
|属性名|值类型|默认值|注释|
|:----:|:----:|:----:|:----|
|name|String||字段名|
|type|String||数据类型|
|defaultValue|String||默认值|
|autoIncrement|Boolean||自增|
|remarks|String||注释|

####### 约束(constraints)
在 column 标签中可以给字段添加约束，如可否为空、主键、唯一等约束条件。
constraints 标签常用属性
|属性名|值类型|默认值|注释|
|:----:|:----:|:----:|:----|
|nullable|Boolean|true|可否为空|
|notNullConstraintName|String||非空约束名|
|primaryKey|Boolean||是否主键|
|primaryKeyName|String||主键名|
|unique|Boolean|false|是否唯一|

##### 添加字段(addColumn)
给已经创建的表添加字段，写在 changeSet 标签内，此标签内用 column 标签定义要添加的字段属性。
|属性名|值类型|默认值|注释|
|:----:|:----:|:----:|:----|
|tableName|String||(必需)表名|
|catalogName|String||目录名|
|schemaName|String||数据库名|
示例：
``````xml
    <changeSet id="20190314154000" author="wqf" context="dev">
        <comment>增加 email 字段</comment>
        <addColumn tableName="changelog_example" catalogName="liquibase_demo" schemaName="liquibase_demo">
            <column name="email" type="varchar(255)">
                <constraints nullable="false"/>
            </column>
        </addColumn>
    </changeSet>
``````

##### 删除字段(dropColumn)
dropColumn 标签用于删除已存在表中的字段，写在 changeSet 标签内，注意这个标签内部不能有内容，否则会报错。
|属性名|值类型|默认值|注释|
|:----:|:----:|:----:|:----|
|tableName|String||(必需)表名|
|name|String||要删除的列名|
|catalogName|String||目录名|
|schemaName|String||数据库名|
``````xml
	<changeSet id="20190314181622" author="wqf" context="dev">
        <comment>删除字段 name</comment>
        <dropColumn tableName="changelog_example" columnName="name" schemaName="liquibase_demo" catalogName="liquibase_demo"/>
    </changeSet>
``````

##### 插入数据(insert)
insert 标签用于在表中插入数据，写在 changeSet 标签内，需要指定表名等属性，在标签内使用 column 标签指定数据值。
|属性名|值类型|默认值|注释|
|:----:|:----:|:----:|:----|
|tableName|String||(必需)表名|
|dbms|String||数据库类型，只有在指定的这种数据库下才会执行|
|catalogName|String||目录名|
|schemaName|String||数据库名|
``````xml
    <changeSet id="20190314183320" author="wqf">
        <comment>插入数据</comment>
        <insert tableName="changelog_example" dbms="mysql" catalogName="liquibase_demo" schemaName="liquibase_demo">
            <column name="email" value="abc@abc.com"/>
            <column name="login_name" value="abc"/>
            <column name="password" value="abc123"/>
        </insert>
    </changeSet>
``````

##### 加载批量数据(loadData)
在 changeSet 中添加 loadData 标签，用来加载数据。
|属性名|值类型|默认值|注释|
|:----:|:----:|:----:|:----|
|tableName|String||(必需)表名|
|file|String||要加载的数据文件路径|
|separator|String||分隔符|
|encoding|String||编码格式|
|quotchar|String|&quot;|引号|
|catalogName|String||目录名|
|schemaName|String||数据库名|
``````xml
	 <changeSet id="20190314183320" author="wqf">
        <loadData tableName="user" file="classpath:liquibase/initdata/user.csv" separator=";" encoding="UTF-8" 
                  quotchar="&quot;" schemaName="liquibase_demo" catalogName="liquibase_demo"/>
	 </changeSet>
``````

##### 修改列表(renameColumn)
在 changeSet 中添加 renameColumn 标签用于修改列名。
|属性名|值类型|默认值|注释|
|:----:|:----:|:----:|:----|
|tableName|String||(必需)表名|
|oldColumnName|String||原列名|
|newColumnName|String||新列名|
|columnDataType|String||数据类型|
|remarks|String||注释|
|catalogName|String||目录名|
|schemaName|String||数据库名|
``````xml
    <changeSet id="20190314184833" author="wqf">
        <comment>修改字段名</comment>
        <renameColumn tableName="changelog_example" oldColumnName="password" newColumnName="pwd" catalogName="liquibase_demo"
                      schemaName="liquibase_demo" columnDataType="varchar(255)" remarks="修改字段名"/>
    </changeSet>
``````

关于配置项与参数可以参考：[http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.1.xsd](http://www.liquibase.org/xml/ns/dbchangelog/dbchangelog-3.1.xsd)

更具体的信息可以参考官方文档或使用 IDE 时查看提示即可完成：[http://www.liquibase.org/documentation/index.html](http://www.liquibase.org/documentation/index.html "官方文档")。

### 参考资料
- 官网：Liquibase | Database Refactoring | Liquibase: [http://www.liquibase.org/](http://www.liquibase.org/)

### End
Demo 项目 Git 地址：https://git.dev.tencent.com/wqf31415/springboot-liquibase-demo.git
