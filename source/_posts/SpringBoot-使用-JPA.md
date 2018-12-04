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
这篇文章主要讲解了 JPA 相关的概念，以及如何在一个 SpringBoot 项目中使用 spring-data-jpa 来操作数据库，包括创建 Entity，自动建表，基础的增删改查，自定义查询方法，JPQL，原生sql查询。

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
spring.datasource.url=jdbc:mysql://localhost:3306/testjpa?useUnicode=true&characterEncoding=utf8&useSSL=false
spring.datasource.username=root
spring.datasource.password=123456
# 下面这个配置项表示是否需要自动创建数据库表，可选值有：none 不自动创建; create 每次项目启动时自动创建; create-drop 项目启动时创建表，项目关闭时删除; update 有需要时更新数据库; validate 验证数据库，但不更新; 
spring.jpa.hibernate.ddl-auto=create
# 打印出sql语句，可用于开发调试
spring.jpa.show-sql=true
``````

#### 创建实体
创建一个 `domain` 包，创建一个 `Student` 类，给这个类加上 `@Entity` 注解，给主键字段加上 `@Id` 和 `@GeneratedValue` 注解，给其它字段加上 `@Column` 注解。
``````java
package com.example.jpademo.domain;

import javax.persistence.*;
import java.time.ZonedDateTime;

@Entity
public class Student {
    @Id
    @GeneratedValue
    private Long id;
    @Column
    private String name;
    @Column
    private Integer age;
    @Column
    private ZonedDateTime birthday;
    @Column
    private Boolean active;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public ZonedDateTime getBirthday() {
        return birthday;
    }

    public void setBirthday(ZonedDateTime birthday) {
        this.birthday = birthday;
    }

    public Boolean getActive() {
        return active;
    }

    public void setActive(Boolean active) {
        this.active = active;
    }

    @Override
    public String toString() {
        return "Student{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", age=" + age +
                ", birthday=" + birthday +
                ", active=" + active +
                '}';
    }
}
``````

#### 自动建表
添加完实体类后，运行一下项目，发现打出的 sql 语句如下：
``````
Hibernate: drop table if exists hibernate_sequence
Hibernate: drop table if exists student
Hibernate: create table hibernate_sequence (next_val bigint) engine=MyISAM
Hibernate: insert into hibernate_sequence values ( 1 )
Hibernate: create table student (id bigint not null, active bit, age integer, birthday datetime, name varchar(255), primary key (id)) engine=MyISAM
``````
查看数据库，发现多了两张表: `hibernate_sequence` 和 `student`。**但是我们使用的 mysql 数据库，不需要sequence来做主键，只需要设置主键值自增就行了**。所以，我们把上面的 `Student` 类改一下，给 `id` 字段的 `@GeneratedValue` 加上主键生成策略参数，修改为 `@GeneratedValue(strategy = GenerationType.IDENTITY)` 。strategy 生成策略的可选参数有：
|名称|说明|
|:----:|:----:|
|GenerationType.AUTO|(默认值)，主键由 jpa 自动生成|
|GenerationType.IDENTITY|使用数据库自增值作为主键值，适用于HSQL、SQL Server、MySQL、DB2、Derby 等数据库|
|GenerationType.SEQUENCE|使用数据库序列号作为主键值，适用于Oracle、PostgreSQL 等数据库|
|GenerationType.TABLE|使用数据中一张表中某个字段作为主键|
重新运行项目，查看日志，发现打出了下面的 sql 语句：
``````
Hibernate: drop table if exists student
Hibernate: create table student (id bigint not null auto_increment, active bit, age integer, birthday datetime, name varchar(255), primary key (id)) engine=MyISAM
``````
**请注意建表语句的最后面 “engine=MyISAM” **，发现使用的存储引擎是 `MyISAM` ，即 My Indexed Sequential Access Method，`MyISAM` 读取速度很快，不占用大量内存和存储资源，但不支持事务、外来键、索引，适用于有很多 count() 、查询频繁插入不频繁、没有事务的表。
我们一般使用的存储引擎是 `InnoDB` ，如果想改成这种存储引擎，需要在项目配置文件 `application.properties` 中添加如下配置项：

``````properties
# 不加这句则默认为 MyISAM 引擎
spring.jpa.database-platform=org.hibernate.dialect.MySQL5InnoDBDialect
``````
经过上面的修改后，建表语句变成了:
``````sql
create table student (id bigint not null auto_increment, active bit, age integer, birthday datetime, name varchar(255), primary key (id)) engine=InnoDB
``````
观察后发现：**name 字段的最大长度为 255 ，而实际上我们并不需要这么大的容量**，所以我们需要限制一下，在 `name` 字段的 `@Column` 注解中添加 length 参数，改为 `@Column(length = 20)` ，这样修改后，生成的表将限制最大长度为 20。此外 `@Column` 注解中还有其它参数：
|名称|说明|默认值|
|:----:|:----:|:----:|
|name|(可选) 建表时使用的字段名|默认为实体类中的字段名|
|unique|(可选) 该字段是否唯一| false|
|nullable|(可选) 是否可为空|true|
|insertable|(可选) 使用的 insert 语句中包含该字段时，该字段是否要插入值|true|
|updatable|(可选) 使用的 update 语句中包含该字段时，该字段是否要更新，用于表中的只读字段|true|
|columnDefinition|(可选) 字段描述，在用来定义建表时数据库字段属性，如指定字段类型与注释: @Column(columnDefinition = "smallint COMMENT '学生年龄'")|""|
|table|(可选) 包含当前字段的表名。默认值为主表的表名。|""|
|length|(可选) 最大长度，只有字段类型是字符串类型时生效|255|
|precision|(可选) 小数的精度，小数数据的长度，仅小数数据类型字段可用|0|
|scale|(可选) 小数数据的小数位数，仅小数数据类型字段可用|0|

在自动建表时， **指定表名**：
- 给 `@Entity` 注解加上 `name` 参数，改为 `@Entity(name = "tb_student")`。
- 或添加 `@Table` 注解，并添加 `name` 参数：`@Table(name = "tb_student")`。

 `@Entity` 注解表明这个类是需要 orm 映射的，只有 `name` 一个参数，而 `@Table` 注解中可以修改一些映射的规则，可添加的参数有：
|名称|说明|默认值|
|:----:|:----:|:----:|
|name|(可选) 表名|当前类名|
|catalog|(可选) 数据库名|配置中指定的数据库|
|schema|(可选) 查询数据时使用的用户名|配置中指定的用户名|
|uniqueConstraints|(可选) 创建单个或联合唯一约束|{}|
例如：
``````java
@Table(name = "tb_student",catalog = "test",schema = "testjpa",uniqueConstraints = {@UniqueConstraint(columnNames = {"name","age"})})
// 将在 test 数据库中创建名为 tb_student 的表，查询时使用 testjpa 的用户查询，并给这张表添加 name 与 age 的唯一约束
``````
建表时运行的 sql 如下：
``````sql
drop table if exists test.tb_student;

create table test.tb_student (id bigint not null auto_increment, active bit, age smallint COMMENT '学生年龄', birthday datetime, name varchar(20), primary key (id)) engine=InnoDB;

alter table test.tb_student add constraint UKjryppi07bm3jtculd9mtfjtjf unique (name, age);
``````

#### 创建 Repository
##### 方式一 继承 JpaRepository 接口
创建包 `repository` ，创建接口 `StudentRepository` 继承 `JpaRepository<T,ID>` ，其中 `JpaRepository` 的接收的两个泛型约束，T 为 Entity 实体类，ID 为该实体类的主键类型。这个接口继承了很多基本的方法，可以直接使用。
``````java
package com.example.jpademo.repository;

import com.example.jpademo.domain.Student;
import org.springframework.data.jpa.repository.JpaRepository;

public interface StudentRepository extends JpaRepository<Student,Long> {
}
``````

##### 方式二 使用 @RepositoryDefinition 注解
创建接口 `TeacherRepository` ，添加注解 `@RepositoryDefinition`，这个注解有两个参数，`domainClass` 为实体类 class，`idClass` 为实体类主键的 class。这种方法创建的 Repository 接口中没有方法，需要自己添加。
``````java
package com.example.jpademo.repository;

import com.example.jpademo.domain.Teacher;
import org.springframework.data.repository.RepositoryDefinition;

@RepositoryDefinition(domainClass = Teacher.class,idClass = Long.class)
public interface TeacherRepository {
	Teacher findById(Long id);
}
``````


#### 创建 Service
用以上两种方式创建的 Repository 具有一些基本的 CRUD 功能，使用这些功能可以创建一个基础的 Service 。
``````java
package com.example.jpademo.service;

import com.example.jpademo.domain.Student;
import com.example.jpademo.repository.StudentRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import java.util.List;

@Service
@Transactional
public class StudentService {
    @Autowired
    private StudentRepository studentRepository;
    
    public Student findOne(Long id){
        return studentRepository.findById(id).orElse(null);
    }

    public List<Student>  findAll(){
        return studentRepository.findAll();
    }

    public Student save(Student student){
        return studentRepository.save(student);
    }

    public void delete(Long id){
        studentRepository.deleteById(id);
    }
}
``````

#### 创建 Controller


### JPA 的缺点
- 联表查询不方便。
- 框架定制重，不便优化 sql 查询，不如 mybatis 灵活。

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
修改方法：
1. 修改数据库时区配置；
``````sql
-- 方法一
-- 以 root 用户登录 mysql 数据库，运行以下命令
set global time_zone='+8:00';
-- 查看是否修改成功： 
-- show variables like '%time_zone%';
``````
或者修改 mysql 配置文件：
``````ini
# 配置文件位置：C:\Program Files\MySQL\MySQL Server 5.7\my.ini
# 修改 [mysqld] 下的 default-time-zone 配置为 '+08:00'
[mysqld]
default-time-zone='+08:00'
``````

2. 修改配置文件中的url，添加时区参数；
``````properties
# 方法二
# 在 url 中添加当前系统时区参数
# GMT%2B8 代表： 东八区(GMT+8)
spring.datasource.url=jdbc:mysql://localhost:3306/test?serverTimezone=GMT%2B8
``````

### 总结