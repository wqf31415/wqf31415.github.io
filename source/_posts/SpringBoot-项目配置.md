---
title: SpringBoot 项目配置
date: 2020-08-08 15:57:16
tags:
- java
- spring
- springboot
categories:
- java

---

### 概述

springboot 的出现大大方便了 java 者使用 spring 开发项目，springboot 项目中使用配置简化了代码，同时也增加了项目的灵活性。这篇文章讲解了在springboot 项目中使用的常见配置项，还介绍了如何使用自定义的配置项，以及让自定义的配置项拥有代码提示。



### SpringBoot 的配置文件

在 springboot 项目中，配置文件默认是在 `src/main/resources` 目录下的 `application.properties` 文件，同时 springboot 支持使用 yml 格式的配置文件，只需要将文件 `application.properties` 的文件后缀改为 `.yml` 即可，使用 yml 配置文档结构鲜明，阅读和书写起来也更加友好。

- application.properties

  ```properties
  server.port=8080
  ```

  

- application.yml

  ```yml
  server:
      port: 8080
  ```

  

<!-- more -->



### 不同环境的配置

我们可以为不同运行场景添加不同的配置，比如分别为开发环境和生产环境添加配置文件，这样在平时开发时就使用开发环境配置运行，在打包部署时就使用开发环境配置打包，这样就不需要来回修改配置文件了。

为不同环境添加配置文件，需要添加配置文件，命名是需要以 `application-` 作为前缀，如 `application-xxx.yml` ，其中 xxx 是环境名。比如为开发环境添加配置 `application-dev.yml` ，为测试环境添加配置 `application-test.yml` ，为生产环境添加配置 `application-prod.yml` 。

添加不同环境配置文件后，修改主配置文件 `application.yml` ，修改 `spring.profiles.include` 配置需要包含的配置文件，修改 `spring.profiles.active` 配置需要激活的配置文件，配置时只需要填环境名。

```yml
spring:
  profiles:
    active: dev
    include: dev
```



### 自定义配置文件

#### 自定义 properties 配置文件

springboot 项目的默认配置文件是 `application.properties` ，我们也可以修改配置使用我们自己定义的配置文件，只需要在 springboot 启动类上加上注解 `@PropertySource` 并在其中的 value 参数中指定自定义配置文件即可。

- my-conf.properties

  ```properties
  server.port=8090
  ```

  

- SbConfDemoApplication.java

  ```java
  @SpringBootApplication
  // 使用 @PropertySource 注解指定自定义的配置文件
  @PropertySource(value = "classpath:my-conf.properties")
  public class SbConfDemoApplication {
  
      public static void main(String[] args) {
          SpringApplication app = new SpringApplication(SbConfDemoApplication.class);
          Environment env = app.run(args).getEnvironment();
          System.out.println("server.port: "+env.getProperty("server.port"));
      }
  
  }
  ```



#### 自定义 yml 配置文件

如果使用的是 yml 配置文件，在使用 `@PropertySource` 注解时还需要指定配置源工场类 factory 参数，将值设置为实现 `PropertySourceFactory` 的自定义类 `YamlPropertySourceFactory` 。 

- my-conf.yml

  ```yaml
  server:
      port: 8090
  ```

  

- YamlPropertySourceFactory.java

  ```java
  public class YamlPropertySourceFactory implements PropertySourceFactory {
      @Override
      public PropertySource<?> createPropertySource(String name, EncodedResource resource) throws IOException {
          return new YamlPropertySourceLoader().load(name,resource.getResource()).get(0);
      }
  }
  ```

- SbConfDemoApplication.java

  ```java
  @SpringBootApplication
  @PropertySource(value = "classpath:my-conf.yml",encoding = "utf-8",factory = YamlPropertySourceFactory.class)
  public class SbConfDemoApplication {
  
      public static void main(String[] args) {
          SpringApplication app = new SpringApplication(SbConfDemoApplication.class);
          Environment env = app.run(args).getEnvironment();
          System.out.println("server.port: "+env.getProperty("server.port"));
      }
  
  }
  ```



### 自定义配置项

除了 springboot 中自带的配置项，我们还可以在配置文件中添加自己的配置项，让项目变得更加灵活。

#### 简单配置项

对于简单的配置项，可以直接写在配置文件中，然后在代码中使用 `@Value` 注入，需要注意的是 @Value 注解需要在 spring 容器类中使用，如使用 `@Service` 、`@Component` 、`@Controller` 等注解定义的类。

- application.yml

  ```yml
  my:
      name: abc
      age: 18
      enable: true
      contact-info:
          email: abc@abc
  ```

- MyServer.java

  ```java
  @Service
  public class MyService {
      @Value("${my.name}")
      private String name;
      
      @Value("${my.age}")
      private Integer age;
      
      @Value("${my.enable}")
      private Boolean enable;
      
      @Value("${my.contact-info.email}")
      private Strign email;
  }
  ```

  

#### 系列配置项

对于多个配置项，我们可以创建配置类来批量获取，需要在配置类上添加 `@ConfigurationProperties` 来标记一个配置类，参数 `prefix` 指定配置的前缀。添加 `@Component` 注解，将这个配置类注册到 spring 容器，或者在 springboot 启动类上使用 `@EnableConfigurationProperties({MyProperties.class})` 注解来注册自定义的配置类。在使用的时候，直接使用 `@Autowired` 注解注入配置类即可。

- application.yml

  ```yml
  my:
      name: abc
      age: 18
      enable: true
      contact-info:
          email: abc@abc
          qq: 1234567890
  ```

- MyProperties.java

  ```java
  package xyz.wqf.demo.config;
  // @Component 注解让这个类交由 spring 容器管理
  @Component
  // @ConfigurationProperties 注解表明这是一个配置
  @ConfigurationProperties(prefix = "my")
  public class MyProperties{
      private String name;
      
      private Integer age;
      
      private Boolean enable;
      
      private ContactInfo contactInfo;
      
      public static class ContactInfo{
          private String email;
          private String qq;
          // 为了节省篇幅，省略了 setter 和 getter 方法
      }
      
      // 为了节省篇幅，省略了 setter 和 getter 方法
  }
  ```

- MyService.java

  ```java
  @Service
  public class MyService {
      @Autowired
      private MyProperties myProperties;
  }
  ```



#### 给自定义配置项添加代码提示

在使用 IDEA 开发 springboot 项目时，最方便的一点就是其强大的代码提示功能，在修改配置文件时，只需要输入关键的单词，就能把可能的配置项给我们展示出来，还能显示配置项的默认值，非常方便。对于我们自己定义的配置项，也可以达到这种提示效果的，我们要做的只是在项目的 maven 依赖中引入 `spring-boot-configuration-processor` 的依赖。

- pom.xml

  ```xml
  <!-- 为了节约篇幅省略了 xml 中其他内容 -->
  <dependencies>
      <!-- 添加配置处理器 -->
      <dependency>
          <groupId>org.springframework.boot</groupId>
          <artifactId>spring-boot-configuration-processor</artifactId>
          <optional>true</optional>
      </dependency>
  
      <dependency>
          <groupId>org.springframework.boot</groupId>
          <artifactId>spring-boot-starter-web</artifactId>
      </dependency>
  </dependencies>
  ```

  

- MyProperties.java

  自定义的配置类需要使用 `@ConfigurationProperties` 标识，才能被自动扫描到。配置类中字段上加的 java doc 注释会在提示时显示，有值的字段则为该字段的默认值。

  ```java
  @ConfigurationProperties(prefix = "my")
  public class MyProperties {
      /**
       * My Name
       */
      private String name;
  
      /**
       * My age, default 18
       */
      private Integer age = 18;
  
      /**
       * Is enable?
       */
      private Boolean enable = true;
  
      private ContactInfo contactInfo;
  
      public static class ContactInfo{
          private String email;
          private String qq;
          // 节约篇幅省略 setter、getter
      }
      // 节约篇幅省略 setter、getter
  }
  ```

  

- SbConfDemoApplication.java

  在启动类中使用 `@EnableConfigurationProperties` 注解声明需要扫描的配置类。

  ```java
  @SpringBootApplication
  @EnableConfigurationProperties(value = {MyProperties.class})
  public class SbConfDemoApplication {
  
      public static void main(String[] args) {
          SpringApplication.run(SbConfDemoApplication.class, args);
      }
  
  }
  ```

  

- application.properties

  在配置文件中，只需要输入我们自定义的配置前缀，就会有相应的提示出现，提示内容包括配置项、说明、默认值以及字段类型。
  
  ![](http://blog-images.qiniu.wqf31415.xyz/springboot-custom-conf-hint.gif)



### SpringBoot 中的配置提示

Spring Boot 的 jar包中包含了一个元数据（metadata）文件，其中包含了所有支持的配置项的说明，这个文件为 IDE 提供了帮助文本和代码提示，在 `application.yml` 或 `application.properties` 配置文件中可展示配置项代码提示。springboot 项目中的配置项元数据文件在 `spring-boot-autoconfigure` 包中，路径为：`META-INF/spring-configuration-metadata.json` 。

在自己项目中，元数据文件通常情况下是在代表编译时生成，在编译时通过扫描项目中被 `@ConfigurationProperties` 注解标识的类，生成配置项信息。当然，也可以手动修改这个元数据文件来实现特殊效果或高级效果。**注意，需要引入 `spring-boot-configuration-processor` 依赖才能自动生成元数据文件。**

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-configuration-processor</artifactId>
    <!-- 使用maven时，应将 optional 置为 true -->
    <optional>true</optional>
</dependency>
```

元数据文件在项目编译时生成，在 `target/classes/META-INF/spring-configuration-metadata.json` ，元数据文件以 json 格式呈现，其中：

- `groups` 为配置项分组，如 `server.port` 和 `server.address` 都是 `server` 组。
- `properties` 为具体的配置项。
- `hints` 为额外添加的提示项。

> 元数据文件中具体字段参考：<https://docs.spring.io/spring-boot/docs/2.5.0/reference/html/configuration-metadata.html> 



### 骚操作

#### @Value 注解对值进行处理

在使用 `@Value` 注解时，可以对值进行处理，让他变成我们需要的数据对象。

如将字符串转换成字符串列表。配置如下：

```yaml
my:
  likes: ball,dance,read
```

java 代码：

```java
@Value("#{'${my.likes}'.split(',')}")
private List<String> likes;
```



### 参考资料

- Configuration Metadata: <https://docs.spring.io/spring-boot/docs/2.5.0/reference/html/configuration-metadata.html> 

- SpringBoot基本配置详解 : <https://www.cnblogs.com/eknown/p/11897014.html> 

- SpringBoot 配置提示功能(超详细)_java_脚本之家: <https://www.jb51.net/article/173209.htm> 

- Spring boot加载自定义配置路径文件之EnvironmentPostProcessor: <https://blog.csdn.net/yaomingyang/article/details/99463212> 

- SpringBoot 如何让yml,properties配置文件有提示: <https://blog.csdn.net/xiongmaojiuxianfly/article/details/86630219> 

  

