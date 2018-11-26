---
title: SpringBoot 使用 JPA
date: 2018-11-23 14:27:32
tags:
- java
- SpringBoot
- jpa
- 数据库
categories:
- 技术
---

### 内容概述
这篇文章主要讲解了 JPA 相关的概念，已经如何在一个 SpringBoot 项目中使用 spring-data-jpa 来操作数据库，包括基础的增删改查，自定义查询方法，JPQL，原生sql查询。

### 什么是 JPA ？
JPA，即 Java Persistence API ，中文意为Java持久层API，是 Sun 公司提出的一套标准，用于将运行期对象持久化存储到数据库，具体实现的产品有： Hiberate、Eclipselink、Toplink、Spring Data JPA等。

<!-- more -->

### 使用 spring-data-jpa
#### 创建项目
简单起见，直接使用 http://start.spring.io 来创建项目，添加3个依赖: `JPA` 、 `MySQL` 、 `Web` 。
![](http://blog-images.qiniu.wqf31415.xyz/spring_boot_jpa_start.png '创建 jpademo 项目') 
demo 项目中的 pom.xml 如下：
``````xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
	<modelVersion>4.0.0</modelVersion>

	<groupId>com.example</groupId>
	<artifactId>jpademo</artifactId>
	<version>0.0.1-SNAPSHOT</version>
	<packaging>jar</packaging>

	<name>jpademo</name>
	<description>Demo project for Spring Boot</description>

	<parent>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter-parent</artifactId>
		<version>2.1.0.RELEASE</version>
		<relativePath/> <!-- lookup parent from repository -->
	</parent>

	<properties>
		<project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
		<project.reporting.outputEncoding>UTF-8</project.reporting.outputEncoding>
		<java.version>1.8</java.version>
	</properties>

	<dependencies>
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-data-jpa</artifactId>
		</dependency>
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-web</artifactId>
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

#### 修改配置文件
修改 `application.properties` 文件：
``````properties
spring.datasource.url=jdbc:mysql://localhost:3306/test?useUnicode=true&characterEncoding=utf8&useSSL=false
spring.datasource.username=root
spring.datasource.password=123456
spring.jpa.properties.hibernate.hbm2ddl.auto=create
``````

### JPA 的缺点
- 联表查询不方便。
- 不好优化 sql 查询，不如 mybatis 灵活。

### 注意事项
- 在概念上要理解 JPA 是一套标准，不是具体实现。

- 使用 spring-data-jpa 2.x 版本时，报错：
`Loading class `com.mysql.jdbc.Driver'. This is deprecated. The new driver class is `com.mysql.cj.jdbc.Driver'. The driver is automatically registered via the SPI and manual loading of the driver class is generally unnecessary.`
原因是： `com.mysql.jdbc.Driver` 已经弃用了，现在使用 `com.mysql.cj.jdbc.Driver` ，是通过 SPI 自动注册的，不需要手动加载驱动类。
修改方法：
``````properties
# 将配置文件中的 jdbc 驱动改成现在用的这个
com.mysql.jdbc.Driver=com.mysql.cj.jdbc.Driver
``````

- 使用 spring-data-jpa 2.x 版本时，报错：
`java.sql.SQLException: The server time zone value 'ÖÐ¹ú±ê×¼Ê±¼ä' is unrecognized or represents more than one time` 
原因是：检测到数据库使用的时区不对，mysql默认的是美国的时区，而我们中国大陆要比他们迟8小时，采用+8:00格式。
修改方法：1，修改数据库时区配置；2，修改配置文件中的url，添加时区参数；
``````sql
-- 方法一
-- 以 root 用户登录 mysql 数据库，运行以下命令
set global time_zone='+8:00';
-- 查看是否修改成功： show variables like '%time_zone%';
``````
或者修改 mysql 配置文件：
``````ini
# 配置文件位置：C:\Program Files\MySQL\MySQL Server 5.7\my.ini
# 修改 [mysqld] 下的 default-time-zone 配置为 '+08:00'
[mysqld]
default-time-zone='+08:00'
``````


``````properties
# 方法二
# 在 url 中添加当前系统时区参数
# GMT%2B8 代表： 东八区(GMT+8)
spring.datasource.url=jdbc:mysql://localhost:3306/test?serverTimezone=GMT%2B8
``````

### 总结