---
title: SpringBoot 使用 JPA
date: 2018-11-23 14:27:32
tags:
- java
- spring
- springboot
- jpa
- 数据库
- database
categories:
- java
---

### 内容概述

这篇文章主要讲解了 JPA 相关的概念，以及如何在一个 SpringBoot 项目中使用 spring-data-jpa 来操作数据库，包括创建 Entity，自动建表，基础的增删改查，自定义查询方法，JPQL，原生sql查询，Specification 查询。

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

修改 `application.properties` 文件，添加连接数据源需要的 url、username、password ：

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

实体类与数据库表对应，实体类中包含对象属性，相应的 setter、getter方法和 toString 方法。在 JPA 中通过给类添加 `@Entity` 注解表明这个类是实体类。
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

在 springboot jpa 项目配置文件中添加配置项 `spring.jpa.hibernate.ddl-auto=create` ，项目启动时会自动扫描全部实体类，并在数据库中创建相应的表。
添加完实体类后，运行一下项目，发现打出的 sql 语句如下：

``````
Hibernate: drop table if exists hibernate_sequence
Hibernate: drop table if exists student
Hibernate: create table hibernate_sequence (next_val bigint) engine=MyISAM
Hibernate: insert into hibernate_sequence values ( 1 )
Hibernate: create table student (id bigint not null, active bit, age integer, birthday datetime, name varchar(255), primary key (id)) engine=MyISAM
``````

查看数据库，发现多了两张表: `hibernate_sequence` 和 `student`。**但是我们使用的 mysql 数据库，不需要sequence来做主键，只需要设置主键值自增就行了**。所以，我们把上面的 `Student` 类改一下，给 `id` 字段的 `@GeneratedValue` 加上主键生成策略参数，修改为 `@GeneratedValue(strategy = GenerationType.IDENTITY)` 。
主键生成策略的可选项：

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
**请注意建表语句的最后面 “engine=MyISAM” **，发现使用的存储引擎是 `MyISAM` ，即 My Indexed Sequential Access Method，`MyISAM` 读取速度很快，不占用大量内存和存储资源，但不支持事务、外来键、索引，适用于有很多 count() 、查询频繁插入不频繁、不需要事务的表。
我们一般需要事务，所以使用的存储引擎是 `InnoDB` ，如果想改成这种存储引擎，需要在项目配置文件 `application.properties` 中添加如下配置项：

``````properties
# 不加这句则默认为 MyISAM 引擎
spring.jpa.database-platform=org.hibernate.dialect.MySQL5InnoDBDialect
``````
经过上面的修改后，建表语句变成了:

``````sql
create table student (id bigint not null auto_increment, active bit, age integer, birthday datetime, name varchar(255), primary key (id)) engine=InnoDB
``````

观察后发现：**name 字段的最大长度为 255 ，而实际上我们并不需要这么大的容量**，所以我们需要限制一下，在 `name` 字段的 `@Column` 注解中添加 length 参数，改为 `@Column(length = 20)` ，这样修改后，生成的表将限制最大长度为 20。
`@Column` 注解参数说明：

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

 `@Entity` 注解表明这个类是需要 orm 映射的，只有 `name` 一个参数，而 `@Table` 注解中可以修改一些映射的规则。
 `@Table` 注解参数：

|名称|说明|默认值|
|:----:|:----:|:----:|
|name|(可选) 表名|当前类名|
|catalog|(可选) 数据库名|配置中指定的数据库|
|schema|(可选) 查询数据时使用的用户名|配置中指定的用户名|
|uniqueConstraints|(可选) 创建单个或联合唯一约束，可以在建表时添加索引|{}|

例如：

``````java
@Table(name = "tb_student",catalog = "test",schema = "testjpa",uniqueConstraints = {@UniqueConstraint(columnNames = {"name","age"})})
// 将在 test 数据库中创建名为 tb_student 的表，查询时使用 testjpa 的用户查询，并给这张表添加 name 与 age 的唯一约束
``````

建表时运行的 sql 如下，在建表完成后，给表添加了约束条件：

``````sql
drop table if exists test.tb_student;
create table test.tb_student (id bigint not null auto_increment, active bit, age smallint COMMENT '学生年龄', birthday datetime, name varchar(20), primary key (id)) engine=InnoDB;
alter table test.tb_student add constraint UKjryppi07bm3jtculd9mtfjtjf unique (name, age);
``````

#### 自动插入初始数据

当配置项 `spring.jpa.hibernate.ddl-auto` 的值为 `create` 或 `create-drop` 时，项目启动建表完成后，会扫描 classpath 下(默认为resource目录)的 `import.sql` 文件，如果有就会执行这个脚本，我们可以在这里面添加插入数据的 sql，初始化数据库中的数据。

#### 创建 Repository

##### 方式一 继承 JpaRepository 接口 (推荐)

创建包 `repository` ，创建接口 `StudentRepository` 继承 `JpaRepository<T,ID>` ，其中 `JpaRepository` 需要指定两个泛型约束，T 为 Entity 实体类，ID 为该实体类的主键类型。这个接口包含了很多基本的增删改查方法，可以直接使用。

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

推荐使用第一种方式创建 Repository ，其从父类继承了一些基本的 CRUD 方法，使用这些方法可以创建一个基础的 Service 。

``````java
package com.example.jpademo.service;

import com.example.jpademo.domain.Student;
import com.example.jpademo.repository.StudentRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

@Service
@Transactional
public class StudentService {
    @Autowired
    private StudentRepository studentRepository;

    public Optional<Student> findOne(Long id){
        return studentRepository.findById(id);
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

使用上面创建的 Service 可以创建一个 Controller ，提供 restful 风格的 api 接口。

``````java
package com.example.jpademo.web.rest;

import com.example.jpademo.service.StudentService;
import com.example.jpademo.domain.Student;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping(value = "/api")
public class StudentResource {
    @Autowired
    private StudentService studentService;

    /**
     * 添加学生
     *
     * @param student 学生
     * @return 学生id为空时添加存储并返回学生信息，否则不添加，返回错误信息，
     */
    @RequestMapping(value = "/students", method = RequestMethod.POST, produces = MediaType.APPLICATION_JSON_UTF8_VALUE)
    public ResponseEntity<Student> save(@RequestBody Student student) throws URISyntaxException {
        if (student.getId() != null) {
            return ResponseEntity.badRequest().body(null);
        }
        student = studentService.save(student);
        return ResponseEntity.created(new URI("/api/students/"+student.getId())).body(student);
    }

    /**
     * 修改学生信息
     *
     * @param student 学生
     * @return 学生 ID 为空时返回错误信息，否则返回修改后的学生信息
     */
    @RequestMapping(value = "/students", method = RequestMethod.PUT, produces = MediaType.APPLICATION_JSON_UTF8_VALUE)
    public ResponseEntity<Student> update(@RequestBody Student student) {
        if (student.getId() == null) {
            return ResponseEntity.badRequest().body(null);
        }
        student = studentService.save(student);
        return ResponseEntity.ok(student);
    }

    /**
     * 删除学生信息
     *
     * @param id 学生ID
     * @return
     */
    @RequestMapping(value = "/students/{id}", method = RequestMethod.DELETE, produces = MediaType.APPLICATION_JSON_UTF8_VALUE)
    public ResponseEntity<Void> delete(@PathVariable Long id) {
        studentService.delete(id);
        return ResponseEntity.ok().build();
    }

    /**
     * 查询一个学生
     *
     * @param id 学生 ID
     * @return 学生信息
     */
    @RequestMapping(value = "/students/{id}", method = RequestMethod.GET, produces = MediaType.APPLICATION_JSON_UTF8_VALUE)
    public ResponseEntity<Student> getOne(@PathVariable Long id) {
        Optional<Student> student = studentService.findOne(id);
        return student
                .map(result->new ResponseEntity(result, HttpStatus.OK))
                .orElse(new ResponseEntity(HttpStatus.NOT_FOUND));
    }

    /**
     * 查询所有学生
     *
     * @return 所有学生信息
     */
    @RequestMapping(value = "/students", method = RequestMethod.GET, produces = MediaType.APPLICATION_JSON_UTF8_VALUE)
    public ResponseEntity<List<Student>> getStudents() {
        List<Student> students = studentService.findAll();
        return ResponseEntity.ok(students);
    }
}
``````


#### 单元测试

创建一个测试类，用来测试我们 controller 提供的接口。

``````java
package com.example.jpademo.web.rest;

import com.example.jpademo.JpademoApplication;
import com.example.jpademo.domain.Student;
import com.example.jpademo.repository.StudentRepository;
import com.example.jpademo.service.StudentService;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.MockitoAnnotations;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.data.web.PageableHandlerMethodArgumentResolver;
import org.springframework.http.MediaType;
import org.springframework.http.converter.json.MappingJackson2HttpMessageConverter;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.util.ReflectionTestUtils;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;

import javax.annotation.PostConstruct;
import javax.persistence.EntityManager;
import javax.transaction.Transactional;

import java.time.Instant;
import java.time.ZoneId;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;
import static org.hamcrest.Matchers.hasItem;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

/**
 * Created by Administrator on 2018/12/13.
 *
 * @author wqf31415
 */
@RunWith(SpringRunner.class)
@SpringBootTest(classes = JpademoApplication.class)
public class StudentResourceTest {
    private static final String DEFAULT_NAME = "ZhangSan";
    private static final String UPDATED_NAME = "LiSi";

    private static final Integer DEFAULT_AGE = 1;
    private static final Integer UPDATED_AGE = 2;

    private static final ZonedDateTime DEFAULT_BIRTHDAY = ZonedDateTime.ofInstant(Instant.ofEpochMilli(0L), ZoneId.systemDefault());
    private static final ZonedDateTime UPDATED_BIRTHDAY = ZonedDateTime.now(ZoneId.systemDefault()).withNano(0);
    private static final String DEFAULT_BIRTHDAY_STR = DateTimeFormatter.ISO_OFFSET_DATE_TIME.format(DEFAULT_BIRTHDAY);

    private static final Boolean DEFAULT_ACTIVE = false;
    private static final Boolean UPDATED_ACTIVE = true;

    @Autowired
    private StudentRepository studentRepository;

    @Autowired
    private StudentService studentService;

    @Autowired
    private MappingJackson2HttpMessageConverter mappingJackson2HttpMessageConverter;

    @Autowired
    private PageableHandlerMethodArgumentResolver pageableHandlerMethodArgumentResolver;

    @Autowired
    private EntityManager em;

    private MockMvc restStudentMockMvc;

    private Student student;

    @PostConstruct
    public void setup(){
        MockitoAnnotations.initMocks(this);
        StudentResource studentResource = new StudentResource();
        ReflectionTestUtils.setField(studentResource,"studentService",studentService);
        this.restStudentMockMvc = MockMvcBuilders.standaloneSetup(studentResource)
                .setCustomArgumentResolvers(pageableHandlerMethodArgumentResolver)
                .setMessageConverters(mappingJackson2HttpMessageConverter)
                .build();
    }

    public static Student createEntity(EntityManager em){
        Student s = new Student();
        s.setName(DEFAULT_NAME);
        s.setAge(DEFAULT_AGE);
        s.setBirthday(DEFAULT_BIRTHDAY);
        s.setActive(DEFAULT_ACTIVE);
        return s;
    }

    @Before
    public void init(){
        student = createEntity(em);
    }

    @Test
    @Transactional
    public void save() throws Exception {
        int databaseSizeBeforeCreate = studentRepository.findAll().size();

        restStudentMockMvc.perform(post("/api/students")
        .contentType(TestUtil.APPLICATION_JSON_UTF8)
        .content(TestUtil.convertObjectToJsonBytes(student)))
        .andExpect(status().isCreated());

        List<Student> students = studentRepository.findAll();
        assertThat(students).hasSize(databaseSizeBeforeCreate+1);
        Student testStudent = students.get(students.size()-1);
        assertThat(testStudent.getName()).isEqualTo(DEFAULT_NAME);
        assertThat(testStudent.getAge()).isEqualTo(DEFAULT_AGE);
        assertThat(testStudent.getBirthday()).isEqualTo(DEFAULT_BIRTHDAY);
        assertThat(testStudent.getActive()).isEqualTo(DEFAULT_ACTIVE);
    }

    @Test
    @Transactional
    public void update() throws Exception {
        studentRepository.saveAndFlush(student);

        int databaseSizeBeforeUpdate = studentRepository.findAll().size();

        Student updateStudent = studentRepository.findById(student.getId()).get();
        updateStudent.setName(UPDATED_NAME);
        updateStudent.setAge(UPDATED_AGE);
        updateStudent.setBirthday(UPDATED_BIRTHDAY);
        updateStudent.setActive(UPDATED_ACTIVE);

        restStudentMockMvc.perform(put("/api/students")
                    .contentType(TestUtil.APPLICATION_JSON_UTF8)
                    .content(TestUtil.convertObjectToJsonBytes(updateStudent)))
                .andExpect(status().isOk());

        List<Student> students = studentRepository.findAll();
        assertThat(students).hasSize(databaseSizeBeforeUpdate);
        Student testStudent = students.get(students.size()-1);
        assertThat(testStudent.getName()).isEqualTo(UPDATED_NAME);
        assertThat(testStudent.getAge()).isEqualTo(UPDATED_AGE);
        assertThat(testStudent.getBirthday()).isEqualTo(UPDATED_BIRTHDAY);
        assertThat(testStudent.getActive()).isEqualTo(UPDATED_ACTIVE);
    }

    @Test
    @Transactional
    public void deleteStudent() throws Exception {
        studentRepository.saveAndFlush(student);

        int databaseSizeBeforeUpdate = studentRepository.findAll().size();

        restStudentMockMvc.perform(delete("/api/students/{id}",student.getId()).accept(TestUtil.APPLICATION_JSON_UTF8))
                .andExpect(status().isOk());

        List<Student> students = studentRepository.findAll();

        assertThat(students).hasSize(databaseSizeBeforeUpdate-1);
    }

    @Test
    @Transactional
    public void getOne() throws Exception {
        studentRepository.saveAndFlush(student);

        restStudentMockMvc.perform(get("/api/students/{id}",student.getId()))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON_UTF8_VALUE))
                .andExpect(jsonPath("$.id").value(student.getId().intValue()))
                .andExpect(jsonPath("$.name").value(DEFAULT_NAME.toString()))
                .andExpect(jsonPath("$.age").value(DEFAULT_AGE.intValue()))
                .andExpect(jsonPath("$.birthday").value(DEFAULT_BIRTHDAY_STR))
                .andExpect(jsonPath("$.active").value(DEFAULT_ACTIVE.booleanValue()));
    }

    @Test
    @Transactional
    public void getNotExistStudent() throws Exception {
        restStudentMockMvc.perform(get("/api/students/{id}",Long.MAX_VALUE))
                .andExpect(status().isNotFound());
    }

    @Test
    @Transactional
    public void getStudents() throws Exception {
        studentRepository.saveAndFlush(student);

        restStudentMockMvc.perform(get("/api/students"))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON_UTF8_VALUE))
                .andExpect(jsonPath("$.[*].id").value(hasItem(student.getId().intValue())))
                .andExpect(jsonPath("$.[*].name").value(hasItem(DEFAULT_NAME)))
                .andExpect(jsonPath("$.[*].age").value(hasItem(DEFAULT_AGE.intValue())))
                .andExpect(jsonPath("$.[*].birthday").value(hasItem(DEFAULT_BIRTHDAY_STR)))
                .andExpect(jsonPath("$.[*].active").value(hasItem(DEFAULT_ACTIVE.booleanValue())));
    }
}
``````


其中新添加了一个测试工具类，代码如下：

``````java
package com.example.jpademo.web.rest;

import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule;
import org.springframework.http.MediaType;

import java.io.IOException;
import java.nio.charset.Charset;

public class TestUtil {

    public static final MediaType APPLICATION_JSON_UTF8 = new MediaType(
            MediaType.APPLICATION_JSON.getType(),
            MediaType.APPLICATION_JSON.getSubtype(), Charset.forName("utf8"));

    public static byte[] convertObjectToJsonBytes(Object object)
            throws IOException {
        ObjectMapper mapper = new ObjectMapper();
        mapper.setSerializationInclusion(JsonInclude.Include.NON_NULL);

        JavaTimeModule module = new JavaTimeModule();
        mapper.registerModule(module);

        return mapper.writeValueAsBytes(object);
    }

    public static byte[] createByteArray(int size, String data) {
        byte[] byteArray = new byte[size];
        for (int i = 0; i < size; i++) {
            byteArray[i] = Byte.parseByte(data, 2);
        }
        return byteArray;
    }
}
``````


### 自定义查询方法

#### 创建查询方法

以上创建的 demo 项目，已经可以自动建表，并具有基本的 CRUD 功能接口，并进行了单元测试。在实际项目中，查询需求多种多样，下面我们来看一下，在 spring data jpa 中可以怎么创建独特的查询方法。
**在使用 spring data jpa 时，我们可以在 `Repository` 中定义一些方法，来实现一些查询功能。**
如：我们要查询所有年龄大于 18 岁并且信息激活了的学生信息，只需要在 `StudentRepository` 中添加一个方法 `List<Student> findByAgeGreaterThanAndActiveTrue(int age);` ，不需要写任何实现类，就可以在 `StudentService` 中调用了。

在 Spring Data 中，查询方法以 **find** 或 **read** 或 **get** 开头，后面跟字段名(字段名首字母大写)，再加上限制条件；
JPA 自定义查询方法关键字：

|关键词|方法示例|JPQL语句|备注|
|:----:|:----:|:----:|:----:|
|And|findByNameAndAge(String name,int age)| ..where x.name = ?1 and x.age = ?2|并且，注意条件名称与参数的位置与数量要一一对应|
|Or|findByNameOrAge(String name,int age)| ..where x.name = ?1 or x.age = ?2|或|
|Is,Equals|findByNameIs(String name),findByNameEquals(String name)| ..where x.name = ?1|等于|
|Between|findByAgeBetween(int start,int end)| .. where x.age>?1 and x.age < ?2|两者之间|
|LessThan|findByAgeLessThan(int age)| .. where x.age < ?1|小于|
|LessThanEqual|findByAgeLessThanEqual(int age)| .. where x.age <= ?1|小于等于|
|GreaterThan|findByAgeGreaterThan(int age)| .. where x.age > ?1|大于|
|GreaterThanEqual|findByAgeGreaterThanEqual(int age)| .. where x.age >= ?1|大于等于|
|After|findByBirthdayAfter(String birthday)| .. where x.birthday > ?1|之后(时间)|
|Before|findByBirthdayBefore(String birthday)| .. where x.birthday < ?1|之前(时间)|
|IsNull|findByAgeIsNull()| .. where x.age is null|等于 null|
|IsNotNull/NotNull|findByAgeIsNotNull()/findByAgeNotNull()| .. where x.age is not null|不等于 null|
|Like|findByNameLike(String name)| .. where x.name like ?1|模糊查询，查询条件中需要自己加 %|
|NotLike|findByNameNotLike(String name)| .. where x.name not like ?1|不再模糊范围内，查询条件中需要自己加%|
|StartingWith|findByNameStartingWith(String name)| .. where x.name like ?1|以某开头，参数后面会添加 %|
|EndingWith|findByNameEndingWith(String name)| .. where x.name like ?!|以某结尾，参数前会添加 %|
|Containing|findByNameContaining(String name)| .. where x.name like ?1|包含某，参数前后添加 %|
|OrderBy|findByAgeOrderByNameDesc(int age)| .. where x.age = ?1 order by x.name desc|排序，Desc 为倒序排列，Asc 为正序排列，默认使用正序排列，所以正序排列可以不显式声明|
|Not|findByNameNot(String name)| .. where x.name != ?!|不等于|
|In| `findByNameIn(List<String> nameList)` | .. where x.name in ?1|在某范围内，参数类型为 Collection|
|NotIn| `findByNameNotIn(List<String> nameList)` | .. where x.name not in ?1|不在某范围内，参数类型为Collection|
|True|findByActiveTrue()| .. where x.active = true|真|
|False|findByActiveFalse()| .. where x.active = false|假|
|IgnoreCase|findByNameIgnoreCase(String name)| .. where UPPER(x.name) = UPPER(?1)|忽略大小写|

#### 排序与分页

可以在上述方法中加入 Sort 或 Pageable 参数，对结果进行排序或分页，如:

```java
List<Student> findByAgeGreaterThan(int age, Pageable pageable);
```


#### 查询方法的解析流程

> 参考：SpringDataJpa：JpaRepository增删改查 - 琦彦 - CSDN博客  https://blog.csdn.net/fly910905/article/details/78557110

- Spring Data JPA 框架在解析方法名时，首先解析 前缀，如 find、findBy、read、readBy、get、getBy，然后解析剩下的部分，例如 Entity 为 Student，查询方法为 findByParentPhoneNumber

- 首先去除 `findBy` 前缀后，解析剩下的 `ParentPhoneNumber` ，将其首字母转成小写，判断是否是实体 Student 的属性，如果是就根据这个属性进行查询，如果不是则进入下一步；

- 从右往左去除 **ParentPhoneNumber** 第一个大写字母开头的字符串，本例中是 **Number**，检查剩下的部分 **ParentPhone** ，首字母转小写后判断是否是 **Student** 的属性，如果是则按该属性进行查询；否则重复此步骤，继续从右往左截取；假设最终 **parent** 是 Student 的一个属性；

- 接着处理剩下的部分（**PhoneNumber**），先判断整体 **phoneNumber** 是否是 **parent** 的属性，如果是则按 **Student.parent.phoneNumber** 进行查询；否则继续从右往左截取判断，最终表示根据 **Student.parent.phone.number** 的值进行查询；

> 注意：可能会有一种特殊情况，如在 **Student** 中包含一个 **parent** 属性，也有一个 **parentPhone** 属性，此时就会存在混淆。可以在属性间加上下划线 “_” 明确表达意图，如 `findByParent_PhoneNumber()` 或 `findByParentPhone_Number()` 。
> **强烈建议：无论是否存在混淆，都要在不同类层级之间加上下划线 “_” 分隔，增加代码可读性。**


#### 查询结果限制

查询第一条记录：

``````java
Student findFirstByAgeLessThanOrderByNameDesc(int age);
Student findTopByOrderByAge();
``````

分页查询排序考前10条记录：

``````java
Page<Student> queryFirst10ByName(String name, Pageable pageable);
Slice<Student> findTop10ByLastName(String lastName,Pageable package);
List<Student> findFirst10ByLastName(String lastName, Sort sort);
List<Student> findTop10ByLastName(String lastName, Pageable package);
``````


#### 计数查询与删除方法

计数查询方法以 **countBy** 开头，如：

``````java
Long countByAgeLessThan(int age);
``````

删除方法以 **deleteBy** 开头，如：

``````java
void deleteByName(String name);
``````


### JPQL 查询

> JPQL 全称 Java Persistence Query Language，即 Java 持久化查询语言，与原生 SQL 语句类似，完全面向对象，通过实体名与属性名访问，不是表名和表的字段名，不支持 INSERT 操作。
**注意：这里用的是实体名，默认为类名，可以在 @Entity 注解中修改实体名，如 @Entity("tb_student") 查询时要使用 tb_student **

#### JPQL 的 SELECT

语法：
``````sql
SELECT ... FROM ... [WHERE ...] [GROUP BY ... [HAVING ...]] [ORDER BY ...] 
``````
where 子句条件关键字：

|含义|关键字|
|:----:|:----:|
|比较|=、>、>=、<、<=、<>|
|between|[not] between|
|模糊匹配|[not] like|
|包含|[not] in|
|空|is [not] null|
|empty|is [not] empty|
|存在|[not] exists|

在 Spring Data JPA 中使用时，需要在 Repository 接口中的方法上加上 @Query 注解，在注解中申明查询语句。

参数绑定：

- 按参数位置传参，使用 “?X”  ，X 为方法中参数位置，从 1 开始计算，参数的个数与顺序要与方法参数保持一致；
- 使用参数名传参，使用 “:paramName” 的方式，这种方式不用管参数顺序，paramName 为参数名，参数名需要使用 @Param("paramName") 注解指定的名称，而不是方法的参数名称；
- 使用 SPEL 的取值表达式进行参数绑定；
下面的 UPDATE 和 DELETE 语句中都可以使用这些方式传参。示例：

``````java
	// 按参数位置绑定
    @Query("select student from Student as student where student.birthday between ?1 and ?2")
    List<Student> findStudentByBirthdayBetween(String startTime,String endTime);
	
	// 按参数名绑定
	@Query("select student from Student student where student.age between :startAge and :endAge")
    List<Student> findStudentByAgeBetween(@Param("startAge") int startAge, @Param("endAge") int endAge);
	
	// JPQL查询语句中可以不写 seleect ，从 from 开始写就可以
    @Query("from Student s where s.name = ?1 and s.age = ?2")
    Student findStudentByNameAndAge(String name, int age);	
	
	// 模糊查询时要在参数前后添加 “%”
	@Query("select s from Student s where s.name like %?1%")
    List<Student> findStudentLikeName(String likeName);
	
	// 参数为集合
	@Query("select s from Student s where s.id in ?1")
    List<Student> findByStudentIds(List<Long> idList);
	
	// 传入Bean进行查询（SPEL表达式查询）
    @Query(value = "from Student s where s.name=:#{#std.name} and s.age=:#{#std.age}")
    Student findByNameAndAge(@Param("std")Student student);
	
	// 分页
    @Query("from Student s")
    Page<Student> findAllStudent(Pageable pageable);
	
	// 带查询条件的分页
    @Query("select s from Student s where s.age >?1")
    Page<Student> findStudentAgeGreaterThan(int age, Pageable pageable);
	
``````

> 注意语句中使用的都是实体名和属性名，不是表名和表中字段名。

查询结果分页，可以在查询方法中加入 Pageable pageable 参数，即可对查询结果进行分页。

#### JPQL 的 UPDATE
语法：

``````sql
UPDATE ... SET ... [WHERE ...]
``````

**温馨提示：在使用时需要添加 @Modified 和 @Query 注解，在调用的 Service 方法上要添加 @Transaction 注解，否则会报缺少事务控制的错。**
示例：

``````java
    @Modifying
    @Query("update Student s set s.age = ?1 where name = ?2")
    long modifyStudentAgeByName(int age, String name);
``````

#### JPQL 的 DELETE

语法：

``````sql
DELETE FROM ... [WHERE ...]
``````

**与 UPDATE 的使用方式相同，也需要添加 @Modified 和 @Query 注解，在调用的 Service 方法上要添加 @Transaction 注解，否则会报错。**
示例：

``````java
    @Modifying
    @Query("delete from Student s where s.name = ?1")
    void deleteStudentByName(String name);
``````

#### 联合查询

在 JPQL 中可以使用 **join** 、**left join** 、**right join** 进行联表查询，用法与原生 sql 相同。
示例：

``````java
    @Query(value = "SELECT d FROM Device d JOIN d.pole p JOIN p.circuit c WHERE c.id = :circuitId AND d.hidden = 0")
    List<Device> findDevicesByGivenCircuitId(@Param("circuitId") Long circuitId);
``````

#### 关联查询与部分字段映射投影

当需要从多张表或一张字段很多的表中查询，但结果只需要一部分字段数据时，就需要用到投影了。
第一种方法，使用 VM （View Module）
查询两张表，取部分字段组成新的对象，如取 Student 的 id、name、age字段，取 Classes 的 name 字段，组成 StudentVM 对象，可以分页查询，需要创建 StudentVM 类，并创建包含所需字段的构造方法。
查询方法：

``````java
	// 查询结果转VM
    @Query("select new com.example.jpademo.web.rest.vm.StudentVM(s.id,s.name,s.age,c.name as className) from Student s left join s.classes c")
    Page<StudentVM> findStudentAndClass(Pageable pageable);
``````

StudentVM 类：

``````java
package com.example.jpademo.web.rest.vm;

public class StudentVM {
    private Long id;
    private String name;
    private Integer age;
    private String classsName;

    public StudentVM() {
    }

	// 一定要有这个构造方法，在查询方法中使用时须注意参数的位置
    public StudentVM(Long id, String name, Integer age, String classsName) {
        this.id = id;
        this.name = name;
        this.age = age;
        this.classsName = classsName;
    }
	// 为了节约篇幅，省略 setter、getter、toString 方法
}
``````

第二种方法，使用 projection 接口。
创建 StudentProjection 接口，添加需要字段的 getXXX 方法，其中 XXX 要与查询语句中的别名对应，不一致时可以使用 `@Value` 注解调整，如：

``````java
package com.example.jpademo.web.rest.vm;

import org.springframework.beans.factory.annotation.Value;

public interface StudentProjection {

    Long getId();

    String getName();

    Integer getAge();

    // 当别名与 getXXX 名称不一致时，可以使用 @Value 注解调整，target 不能省略，className 是在查询语句中设定的别名
    @Value("#{target.className}")
    String getCname();
}
``````

在Repository 中添加查询方法
``````java
    // projection 投影映射
    @Query("select s.id as id, s.name as name, s.age as age, c.name as className from tb_student s left join s.classes c ")
    Page<Student> findAllStudentAndClass(Pageable pageable);
``````

#### JPQL 命名查询

命名查询的查询语句会在加载类的时候就生成，在后续的查询中直接使用，可以提高后续的查询速度。
定义命名查询时，需要在实体类上添加 @NamedQueries 注解，只有一个参数，接收 @NamedQuery 注解的数组；@NamedQuery 注解主要两个参数，一个是查询名称 name，命名方式为 `实体名.查询方法名` ，查询方法名为 Repository 中的查询名，另一个参数为查询语句 query。
实体类例如：

``````java
package com.example.jpademo.domain;

import javax.persistence.*;

@Entity
@Table
@NamedQueries({
				@NamedQuery(name = "Classes.findClassById",query = "select c from Classes c where c.id = ?1"),
				@NamedQuery(name="Classes.findAllPage",query = "select c from Classes c")
				})
public class Classes {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column
    private String name;

    @Column
    private String info;
	// 为了节约篇幅，省略 setter、getter、toString 方法
}
``````

对应的 Repository 为：

``````java
package com.example.jpademo.repository;

import com.example.jpademo.domain.Classes;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;

public interface ClassesRepository extends JpaRepository<Classes,Long> {

    Classes findClassById(Long id);

    Page<Classes> findAllPage(Pageable pageable);
}
``````

#### JPQL 函数

JPQL 中提供了一些内嵌的函数，可以处理字符串、计算和日期。

- 字符串处理函数

|函数|功能|示例|
|:----:|:----:|:----:|
|concat(String s1, String s2)|连接两个字符串|concat("hello ","world") ---> "hello world"|
|substring(String s, int start, int length)|截取字符串|substring("hello",1,3) ---> "ell"|
|trim([leading|trailing|both,][char c,] String s)|从字符串中去掉首/尾指定的字符或空格|trim("hello world") ---> "helloworld"|
|lower(String s)|转成小写|lower("HeLLo") ---> "hello"|
|upper(String s)|转成大写|lower("HeLLo") ---> "HELLO"|
|length(String s)|求字符串长度|length("hello") ---> 5|
|locate(String s1, String s2[, int start])|从 s1 中查找 s2 出现的位置，没有返回0|locate("hello",l) ---> 2|

- 算术函数

|函数|功能|示例|
|:----:|:----:|:----:|
|abs(x)|取绝对值|abs(-1) ---> 1|
|mod(int x, int y)|取模，即 x/y 的余数|mod(10,4) ---> 2|
|sqrt(x)|取平方根值|sqrt(25) ---> 5|

- 日期函数

|函数|功能|示例|
|:----:|:----:|:----:|
|current_date()|取当前日期|current_date() ---> 2019-01-15|
|current_time()|取当前时间|current_time() ---> 15:54:45|
|current_timestamp()|取当前时间戳|current_timestamp() ---> 2019-01-15 15:54:45|

### 原生查询

#### 简单的原生查询

使用原生的 sql 语句进行查询，在一些复杂的，或 JPQL 无法实现的情况下可以使用。需要添加 @Query 注解，在 value 参数中声明使用的 sql 语句，nativeQuery 参数设置为 true 。
原生查询时传参方式与 JPQL 一致。
示例：

``````java
    @Query(value = "select s.* from tb_student s where s.active = 1 and s.age = :age",nativeQuery = true)
    List<Student> findActiveStudentByAge(@Param("age") int age);

    @Query(value = "select count(id) from tb_student where age = ?1",nativeQuery = true)
    long countStudentByAge(int age);
	
	// 可以实现增删改查各种操作
``````


#### 分页的原生查询

需要分页查询时，需要传 Pageable pageable 参数，在 @Query 注解中声明 countQuery，值为统计查询结果数量的 sql 语句。

``````java
    @Query(value = "select s.* from tb_student s where s.active = 1",countQuery = "select count(s.id) from tb_student s where s.active = 1",nativeQuery = true)
    Page<Student> findActiveStudentPage(Pageable pageable);
``````

#### 联表的原生查询

使用原生 sql 进行联表查询后，不能自动封装成对象，查询结果返回的类型是 Object，多个结果则返回 `List<Object>` 或 `Page<Object>` ，其中的每一个 Object 实际是一个 Object 数组，数组每个元素则是查询的字段值，查询完成后需要自己转换成对象。
举个例子，查询 Student 中的 id、name、age 与 Classes 中的 name ，查询方法如下：

``````java
    @Query(value = "SELECT s.id,s.name,s.age,c.name FROM tb_student s LEFT JOIN classes c ON s.classes_id = c.id",nativeQuery = true)
    List<Object> findStudentInfo();
``````
在 Service 中调用查询方法，转成需要的对象：
``````java
    public List<StudentVM> findStudentInfo(){
        List<Object> list = studentRepository.findStudentInfo();
        return list.stream()
			.map(o->{
				StudentVM vm = new StudentVM();
				// 将结果对象强转成对象数组
				Object[] os = (Object[]) o;
				// 对象数组里每个元素对应查询语句中的字段，将其取出封装到需要的对象中
				// 注意：有些字段查出结果可能为空，最后是先进行判断
				vm.setId((Long) os[0]);
				vm.setName(os[1].toString());
				vm.setAge((int) os[2]);
				vm.setClasssName(os[3].toString());
				return vm;
			}).collect(Collectors.toList());
    }
``````


分享一下，下面是我写过最复杂的原生查询方法：

``````java
    /**
     * 查询给定时间和id列表的设备上下线记录，包括上下线时间
     * @param deviceIdList
     * @param startTime
     * @param endTime
     * @return
     */
    @Query(value = "select t.* from (SELECT o.device_id,o.device_code," +
        "SUM(CASE WHEN o.state = 'offline' THEN 1 ELSE 0 END) offline_count," +
        "SUM(CASE WHEN o.state = 'Online' THEN 1 ELSE 0 END) online_count," +
        "MAX(CASE WHEN o.state = 'offline' THEN o.time_span END) longest_offline_time " +
        "FROM " +
        "(" +
        "SELECT A.device_id,A.device_code,A.state,A.collection_time," +
        "timestampdiff(SECOND,A.collection_time,B.collection_time) time_span " +
        "FROM " +
        "(" +
        "SELECT ds.*,(@i \\:= @i + 1) as ord_num " +
        "FROM device_state ds,(select @i \\:= 1) d " +
        "WHERE ds.device_id IN ?#{#deviceIdList} " +
        "AND ds.hidden = 0 " +
        "AND ds.collection_time BETWEEN ?#{#startTime} AND ?#{#endTime} " +
        "AND NOT ISNULL(ds.device_code) " +
        "ORDER BY ds.device_code,ds.collection_time ASC " +
        ")" +
        "as A LEFT JOIN " +
        "(" +
        "SELECT ds.*,(@j \\:= @j + 1) as ord_num " +
        "FROM device_state ds,(select @j \\:= 0) d " +
        "WHERE ds.device_id IN ?#{#deviceIdList} " +
        "AND ds.hidden = 0 " +
        "AND ds.collection_time BETWEEN ?#{#startTime} AND ?#{#endTime} " +
        "AND NOT ISNULL(ds.device_code) " +
        "ORDER BY ds.device_code,ds.collection_time ASC " +
        ") " +
        "as B on A.ord_num = B.ord_num and A.device_code=B.device_code " +
        ") o " +
        "GROUP BY o.device_code "+
        "ORDER BY ?#{#pageable} ) t order by longest_offline_time DESC ",
        countQuery = "select count(*) "+
        "FROM ("+
        "SELECT ds.* FROM device_state ds " +
        "WHERE ds.device_id IN ?#{#deviceIdList} " +
        "AND ds.hidden = 0 " +
        "AND ds.collection_time BETWEEN ?#{#startTime} AND ?#{#endTime} " +
        "AND NOT ISNULL(ds.device_code) " +
        "GROUP BY ds.device_code) o",
        nativeQuery = true)
    Page<Object> countDeviceStateByGivenDeviceIdsAndCollectionTime(
        @Param("deviceIdList") List<Long> deviceIdList,
        @Param("startTime") String startTime,
        @Param("endTime") String endTime,
        Pageable pageable
    );
``````


### Specification 查询

以上的查询方法使用的查询语句都是固定的，使用起来有时会不灵活，在 Spring Data JPA 中可以使用 Specification 接口实现动态 sql 查询。

要使用 Specification 就需要让 Repository 接口继承 `JpaSpecificationExecutor<T>` 接口，这个接口指定的泛型类型是当前 Repository 对应的实体类型。如：

``````java
public interface StudentRepository extends JpaRepository<Student,Long>,JpaSpecificationExecutor<Student> {

}
``````

查看 Specification 接口源码，发现其中有 5 个查询方法，有查单条记录的，有查列表的，可以分页、排序，但其中都有一个 Specification 类型的参数：

``````java
package org.springframework.data.jpa.repository;

import java.util.List;
import java.util.Optional;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.lang.Nullable;

/**
 * Interface to allow execution of {@link Specification}s based on the JPA criteria API.
 *
 * @author Oliver Gierke
 * @author Christoph Strobl
 */
public interface JpaSpecificationExecutor<T> {

	/**
	 * Returns a single entity matching the given {@link Specification} or {@link Optional#empty()} if none found.
	 *
	 * @param spec can be {@literal null}.
	 * @return never {@literal null}.
	 * @throws org.springframework.dao.IncorrectResultSizeDataAccessException if more than one entity found.
	 */
	Optional<T> findOne(@Nullable Specification<T> spec);

	/**
	 * Returns all entities matching the given {@link Specification}.
	 *
	 * @param spec can be {@literal null}.
	 * @return never {@literal null}.
	 */
	List<T> findAll(@Nullable Specification<T> spec);

	/**
	 * Returns a {@link Page} of entities matching the given {@link Specification}.
	 *
	 * @param spec can be {@literal null}.
	 * @param pageable must not be {@literal null}.
	 * @return never {@literal null}.
	 */
	Page<T> findAll(@Nullable Specification<T> spec, Pageable pageable);

	/**
	 * Returns all entities matching the given {@link Specification} and {@link Sort}.
	 *
	 * @param spec can be {@literal null}.
	 * @param sort must not be {@literal null}.
	 * @return never {@literal null}.
	 */
	List<T> findAll(@Nullable Specification<T> spec, Sort sort);

	/**
	 * Returns the number of instances that the given {@link Specification} will return.
	 *
	 * @param spec the {@link Specification} to count instances for. Can be {@literal null}.
	 * @return the number of instances.
	 */
	long count(@Nullable Specification<T> spec);
}
``````

Specification 是一个接口，我们需要自己创建实现类，在下例中为了演示方便，直接创建的匿名类。在这个接口中有 3 个参数，`Root<T>` 指定查询的实体类型，`CriteriaQuery<?>` 定义高级查询功能，**CriteriaBuilder** 用于创建标准查询、联合查询、表达式、条件、排序。
示例：

``````java
@Service
@Transactional
public class StudentService {
    public List<Student> findStudentByCondition(String nameLike, Integer startAge, Integer endAge, ZonedDateTime startBirthday,ZonedDateTime endBirthday,Long classId){
        Specification<Student> spec = new Specification<Student>() {
            @Override
            public Predicate toPredicate(Root<Student> root, CriteriaQuery<?> query, CriteriaBuilder criteriaBuilder) {
                List<Predicate> predicates = new ArrayList<>();
                predicates.add(criteriaBuilder.like(root.get("name"),"%"+nameLike+"%"));
                // 参数不为空时添加查询条件
                if (startAge != null){
                    // 大于
                    predicates.add(criteriaBuilder.greaterThan(root.get("age"),startAge));
                }
                if (endAge != null){
                    // 小于
                    predicates.add(criteriaBuilder.le(root.get("age"), endAge));
                }
                if (startBirthday != null && endBirthday != null){
                    // between
                    predicates.add(criteriaBuilder.between(root.get("birthday"), startBirthday, endBirthday));
                }
                return criteriaBuilder.and(predicates.toArray(new Predicate[predicates.size()]));
            }
        };
        
        // 其他查询条件
        Specification<Student> spec2 = ((root, query, criteriaBuilder) -> {
            List<Predicate> predicates = new ArrayList<>();
            if (classId != null){
                // 带关联关系的查询条件
                predicates.add(criteriaBuilder.equal(root.get("classes").get("id"),classId));
            }
            return criteriaBuilder.and(predicates.toArray(new Predicate[predicates.size()]));
        });
        // 多个 Specification 可以用 and 或 or 连接使用
        return studentRepository.findAll(Specification.where(spec).and(spec2));
    }
}
``````

### 多数据源

#### 相同数据库

##### 配置多数据源

修改配置文件，添加多个数据源的配置信息。

``````properties
server.port=8989
spring.application.name=JpaDemo

# 主数据源
spring.datasource.primary.driver-class-name=com.mysql.jdbc.Driver
spring.datasource.primary.jdbc-url=jdbc:mysql://172.16.19.233:3306/testjpa?useUnicode=true&characterEncoding=utf8&useSSL=false&serverTimezone=GMT%2B8
spring.datasource.primary.username=root
spring.datasource.primary.password=123456

# 第二数据源
spring.datasource.secondary.driver-class-name=com.mysql.jdbc.Driver
spring.datasource.secondary.jdbc-url=jdbc:mysql://172.16.19.229:3306/u_testjpa?useUnicode=true&characterEncoding=utf8&useSSL=false&serverTimezone=GMT%2B8
spring.datasource.secondary.username=root
spring.datasource.secondary.password=root

# 自动建表
spring.jpa.hibernate.ddl-auto=create
# 打印 sql 语句
spring.jpa.show-sql=true
#不加这句则默认为 MyISAM 引擎，加上之后使用 InnoDB 引擎
spring.jpa.database-platform=org.hibernate.dialect.MySQL5InnoDBDialect

spring.data.elasticsearch.cluster-name=my-application
spring.data.elasticsearch.cluster-nodes=127.0.0.1:9300
``````

添加数据源配置类

``````java
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.boot.jdbc.DataSourceBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;

import javax.sql.DataSource;

@Configuration
public class DataSourceConfig {
    @Primary
    @Bean("primaryDataSource")
    @Qualifier("primaryDataSource")
    @ConfigurationProperties("spring.datasource.primary")
    public DataSource primaryDataSource(){
        return DataSourceBuilder.create().build();
    }


    @Bean("secondaryDataSource")
    @Qualifier("secondaryDataSource")
    @ConfigurationProperties("spring.datasource.secondary")
    public DataSource secondaryDataSource(){
        return DataSourceBuilder.create().build();
    }
}
``````

不同数据源的 JPA 属性配置

> entityManagerFactoryRef → 配置的连接工厂
transactionManagerRef → 事务管理器
basePackages → 扫描 Repository 的包


主数据源: 

``````java
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.boot.autoconfigure.orm.jpa.HibernateSettings;
import org.springframework.boot.autoconfigure.orm.jpa.JpaProperties;
import org.springframework.boot.orm.jpa.EntityManagerFactoryBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;
import org.springframework.orm.jpa.JpaTransactionManager;
import org.springframework.orm.jpa.LocalContainerEntityManagerFactoryBean;
import org.springframework.transaction.PlatformTransactionManager;
import org.springframework.transaction.annotation.EnableTransactionManagement;

import javax.persistence.EntityManager;
import javax.sql.DataSource;
import java.util.Map;

@Configuration
@EnableTransactionManagement
@EnableJpaRepositories(entityManagerFactoryRef = "entityManagerFactoryPrimary",
	transactionManagerRef = "transactionManagerPrimary",
	basePackages = {"com.example.jpademo.repository"})
public class PrimaryConfig {
    @Autowired
    @Qualifier("primaryDataSource")
    private DataSource primaryDataSource;

    @Autowired
    private JpaProperties jpaProperties;

    @Primary
    @Bean(name = "entityManagerPrimary")
    public EntityManager entityManager(EntityManagerFactoryBuilder builder) {
        return entityManagerFactoryPrimary(builder).getObject().createEntityManager();
    }

    @Primary
    @Bean(name = "entityManagerFactoryPrimary")
    public LocalContainerEntityManagerFactoryBean entityManagerFactoryPrimary (EntityManagerFactoryBuilder builder) {
        return builder
                .dataSource(primaryDataSource)
                .properties(getVendorProperties(primaryDataSource))
                .packages("com.example.jpademo.domain") //设置实体类所在位置
                .persistenceUnit("primaryPersistenceUnit")
                .build();
    }

    private Map getVendorProperties(DataSource dataSource) {
        HibernateSettings hibernateSettings = new HibernateSettings();
        return jpaProperties.getHibernateProperties(hibernateSettings);
    }

    @Primary
    @Bean(name = "transactionManagerPrimary")
    public PlatformTransactionManager transactionManagerPrimary(EntityManagerFactoryBuilder builder) {
        return new JpaTransactionManager(entityManagerFactoryPrimary(builder).getObject());
    }
}
``````

第二数据源:

``````java
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.boot.autoconfigure.orm.jpa.HibernateSettings;
import org.springframework.boot.autoconfigure.orm.jpa.JpaProperties;
import org.springframework.boot.orm.jpa.EntityManagerFactoryBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;
import org.springframework.orm.jpa.JpaTransactionManager;
import org.springframework.orm.jpa.LocalContainerEntityManagerFactoryBean;
import org.springframework.transaction.PlatformTransactionManager;
import org.springframework.transaction.annotation.EnableTransactionManagement;

import javax.persistence.EntityManager;
import javax.sql.DataSource;
import java.util.Map;

@Configuration
@EnableTransactionManagement
@EnableJpaRepositories(entityManagerFactoryRef = "entityManagerFactorySecondary",
    transactionManagerRef = "transactionManagerSecondary",
    basePackages = {"com.example.jpademo.repository2"})
public class SecondaryConfig {
    @Autowired
    @Qualifier("secondaryDataSource")
    private DataSource secondaryDataSource;

    @Autowired
    private JpaProperties jpaProperties;

    @Bean(name = "entityManagerSecondary")
    public EntityManager entityManager(EntityManagerFactoryBuilder builder) {
        return entityManagerFactorySecondary(builder).getObject().createEntityManager();
    }


    @Bean(name = "entityManagerFactorySecondary")
    public LocalContainerEntityManagerFactoryBean entityManagerFactorySecondary (EntityManagerFactoryBuilder builder) {
        return builder
                .dataSource(secondaryDataSource)
                .properties(getVendorProperties(secondaryDataSource))
                .packages("com.example.jpademo.domain2") //设置实体类所在位置
                .persistenceUnit("secondaryPersistenceUnit")
                .build();
    }

    private Map getVendorProperties(DataSource dataSource) {
        HibernateSettings hibernateSettings = new HibernateSettings();
        return jpaProperties.getHibernateProperties(hibernateSettings);
    }

    @Bean(name = "transactionManagerSecondary")
    public PlatformTransactionManager transactionManagerPrimary(EntityManagerFactoryBuilder builder) {
        return new JpaTransactionManager(entityManagerFactorySecondary(builder).getObject());
    }
}
``````


##### 将不同数据域的实体类、Repository 放到不同包下

如上面配置类中配置的，分别将不同数据实体类放到 `com.example.jpademo.domain` 和 `com.example.jpademo.domain2` 包中，将对应的 Repository 分别放到 `com.example.jpademo.repository` 和 `com.example.jpademo.repository2` 包中。

##### 编写服务类与接口进行测试

剩下的 Service 类和 Controller 跟正常的没有差别了，这里不再赘述。

#### 不同数据库

如在我的项目中要使用到关系型数据库 MySql 和全文检索 Elasticsearch（简称ES） ，可以在存入 MySql 中的实体类上添加 `@Entity` 注解，在需要存入 ES 的实体上添加 `@Document` 注解，如果两边都要存，可以同时添加两个注解。

``````java
// 存入 MySql 的数据实体
@Entity
public class User{
	// ...
}

// 存入 ES 的数据实体
@Document
public class Book{
	// ...
}

// 两个数据库都要存入的数据
@Entity
@Document
public class Author{
	// ...
}
``````

创建对应的 Repository

``````java
// 存入 MySql 的数据实体仓库
interface UserRepository extends JpaRepository<User,Long>{
}

// 存入 ES 的数据实体仓库
public interface BookSearchRepository extends ElasticsearchRepository<Book, String> {
}
``````

### JPA 的缺点

- 联表查询不方便，两个没有关联的表做 join 操作比较繁琐。
- 框架定制重，不便优化 sql 查询，不如 mybatis 自由度高。

### 注意事项

#### JPA 是一套标准

在概念上要理解 JPA 是一套标准，而不是具体实现。

#### 驱动错误 
使用 spring-data-jpa 2.x 版本时，报错：

``````
Loading class 'com.mysql.jdbc.Driver'. This is deprecated. The new driver class is 'com.mysql.cj.jdbc.Driver'. The driver is automatically registered via the SPI and manual loading of the driver class is generally unnecessary.
``````

原因是： `com.mysql.jdbc.Driver` 已经弃用了，现在使用 `com.mysql.cj.jdbc.Driver` ，是通过 SPI 自动注册的，不需要手动加载驱动类。
修改方法：

``````properties
# 将配置文件中的 jdbc 驱动改成现在用的这个
com.mysql.jdbc.Driver=com.mysql.cj.jdbc.Driver
``````

#### 时区错误

使用 spring-data-jpa 2.x 版本时，报错：

``````
java.sql.SQLException: The server time zone value 'ÖÐ¹ú±ê×¼Ê±¼ä' is unrecognized or represents more than one time
``````

原因是：检测到数据库使用的时区不对，mysql默认的是美国的时区，而我们中国大陆要比他们迟8小时，采用+8:00格式。
修改方法：

- 方法一: 修改数据库时区配置；

  ``````sql
-- 以 root 用户登录 mysql 数据库，运行以下命令
set global time_zone='+8:00';
-- 查看是否修改成功： 
-- show variables like '%time_zone%';
  ``````

或者修改 mysql 配置文件：

> 配置文件位置：C:\Program Files\MySQL\MySQL Server 5.7\my.ini
> 修改 [mysqld] 下的 default-time-zone 配置为 '+08:00'

  ```ini
[mysqld]
default-time-zone='+08:00'
  ```

- 方法二: 修改配置文件中的url，添加时区参数；

> 在 url 中添加当前系统时区参数, `GMT%2B8` 代表： 东八区(GMT+8)

  ``````properties
spring.datasource.url=jdbc:mysql://localhost:3306/test?serverTimezone=GMT%2B8
  ``````

#### 实体匹配错误

在 Repository 查询方法中使用 JPQL 时，项目启动报错
查询方法为：

``````java
    @Modifying
    @Query("DELETE FROM Student s WHERE s.name = ?1")
    void deleteStudentByName(String name);
``````

错误日志主要内容如下：

  ``````
org.springframework.beans.factory.UnsatisfiedDependencyException: Error creating bean with name 'studentService': Unsatisfied dependency expressed through field 'studentRepository'; nested exception is org.springframework.beans.factory.BeanCreationException: Error creating bean with name 'studentRepository': Invocation of init method failed; nested exception is java.lang.IllegalArgumentException: Validation failed for query for method public abstract void com.example.jpademo.repository.StudentRepository.deleteStudentByName(java.lang.String)!
...
Caused by: java.lang.IllegalArgumentException: org.hibernate.hql.internal.ast.QuerySyntaxException: Student is not mapped [DELETE FROM Student s WHERE s.name = ?1]
...
  ``````

错误的意思是 Student 实体不能匹配，这时首先需要检查实体的属性名和查询语句中的是否对应；如果能够对应，再检查实体类，是否在 @Entity 注解中指定了名称，例如注解为 `@Entity("tb_student")` ，则在 JPQL 查询语句中要使用 tb_student ，而不能使用 Student，正确的查询方法如下：

```java
    @Modifying
    @Query("DELETE FROM tb_student s WHERE s.name = ?1")
    void deleteStudentByName(String name);
```

#### 原生 sql 进行分页查询时报错提示不能使用排序和分页

查询方法：

``````java
    @Query(value = "select d.* from device d where d.sensor & ?1 = ?1 "
        ,nativeQuery = true
        ,countQuery = "select count(*) from Device d where d.sensor & ?1 = ?1")
    Page<Device> findBySensorType(Long sensorType,Pageable pageable);
``````

错误提示信息如下：

``````
org.springframework.data.jpa.repository.query.InvalidJpaQueryMethodException: 
Cannot use native queries with dynamic sorting and/or pagination in method public abstract org.springframework.data.domain.Page com.xx.xxxx.repository.XxxRepository.findBySensorType(java.lang.Long,org.springframework.data.domain.Pageable)
``````

解决方法是在查询语句中加上 ``ORDER BY ?#{ #pageable }`` ，修改后如下：

``````
    @Query(value = "select d.* from device d where d.sensor & ?1 = ?1 order by ?#{ #pageable }"
        ,nativeQuery = true
        ,countQuery = "select count(*) from Device d where d.sensor & ?1 = ?1")
    Page<Device> findBySensorType(Long sensorType,Pageable pageable);
``````

### 参考资料

- springboot(十三)：springboot小技巧: [http://www.ityouknow.com/springboot/2017/06/22/springboot-tips.html](http://www.ityouknow.com/springboot/2017/06/22/springboot-tips.html)
- SpringBoot 2.x 整合 jpa实现多数据源: [https://blog.csdn.net/qq_26440803/article/details/83316743](https://blog.csdn.net/qq_26440803/article/details/83316743)

### 其它

DEMO：https://git.dev.tencent.com/wqf31415/springboot-jpa-demo.git
由于笔者能力有限，文章中若有错误与不足之处希望大佬们能够指出。

