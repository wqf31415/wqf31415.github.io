---
title: docker 打包 springbot 项目
tags:
  - docker
  - springboot
  - 工具
categories:
  - java
date: 2021-01-13 10:37:05
---

### 概述

这篇文章介绍了将 springboot 项目打包成 docker 镜像，以 docker 运行。



### 原理

将 springboot 项目打包后，使用 Dockerfile 创建镜像，然后就可以使用 docker 运行。如果项目还依赖第三方软件，如数据库等，可以使用 docker-compose 来启动项目和相关依赖。



<!-- more -->

### 简单项目示例

这个示例项目只包含单独的 springboot 项目，不依赖其他软件与程序。

#### 创建示例用的 springboot 项目

使用喜欢的方式创建一个 springboot 项目，以 maven 构建。

pom.xml :

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.4.1</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>
    <groupId>xyz.wqf</groupId>
    <artifactId>docker-demo</artifactId>
    <version>0.0.1-SNAPSHOT</version>
    <name>docker-demo</name>
    <description>Demo project for Spring Boot</description>

    <properties>
        <java.version>1.8</java.version>
    </properties>

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
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
```

修改项目启动类，添加一个接口用来测试。DockerDemoApplication.java ：

```java
package xyz.wqf.dockerdemo;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.core.env.Environment;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.net.InetAddress;
import java.net.UnknownHostException;

@SpringBootApplication
@RestController
public class DockerDemoApplication {
    private final static Logger log = LoggerFactory.getLogger(DockerDemoApplication.class);

    public static void main(String[] args) throws UnknownHostException {
        SpringApplication app = new SpringApplication(DockerDemoApplication.class);
        Environment env = app.run(args).getEnvironment();
        log.info("\n--+---+---+---+---+---+---+---+---+---+---+--\n" +
                "Application is running! Access URLs:\n" +
                "\tLocal:\thttp://localhost:{}\n" +
                "\tExternal:\thttp://{}:{}\n" +
                "--+---+---+---+---+---+---+---+---+---+---+--",
                env.getProperty("server.port"),
                InetAddress.getLocalHost().getHostAddress(),
                env.getProperty("server.port"));
    }

    @GetMapping("/hello")
    public String hello(){
        return "world";
    }
}

```



#### 方式一：打包后使用 Dockerfile 创建镜像

最简单的方式是先打包项目获得 jar 包，然后与 Dockerfile 文件放到一起，然后运行 docker 命令构建镜像。

操作步骤：

- 创建 docker 目录，并创建一个 `Dockerfile` 文件，Dockerfile 配置如下所示。

- 将项目打包，把打包后的文件复制到 Dockerfile 同级目录下。

- 创建镜像，使用 `-t` 指定镜像名为 `myapp` 版本号为 `1.0` 。（注意命令最后有个 `.` 表示在当前目录创建镜像）。

  ```bash
  docker build -t myapp:1.0 .
  ```

Dockerfile :

```cmake
# 这是一个最简单的 Dockerfile 示例
# 使用 openjdk8 镜像，添加 java 环境
FROM openjdk:8-jre-alpine
# 将打包后的项目文件添加到镜像中，并改名为 app.jar
ADD docker-demo-0.0.1-SNAPSHOT.jar app.jar
# 对外暴露的端口
EXPOSE 8080
# 启动时运行的命令
ENTRYPOINT ["java","-jar","/app.jar"]
```

#### 方式二：使用 dockerfile-maven 插件打包

使用 `dockerfile-maven` 插件直接将项目打包成 docker 镜像。以前使用 [docker-maven-plugin](https://github.com/spotify/docker-maven-plugin) ，但这个项目已经不活跃了，建议使用 [dockerfile-maven](https://github.com/spotify/dockerfile-maven) 。

> dockerfile-maven 项目：<https://github.com/spotify/dockerfile-maven> 

操作步骤：

- 修改 pom.xml，引入 dockerfile-maven 插件依赖，添加配置信息：

  ```xml
  <?xml version="1.0" encoding="UTF-8"?>
  <project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
           xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
      <modelVersion>4.0.0</modelVersion>
      <parent>
          <groupId>org.springframework.boot</groupId>
          <artifactId>spring-boot-starter-parent</artifactId>
          <version>2.4.1</version>
          <relativePath/> <!-- lookup parent from repository -->
      </parent>
      <groupId>xyz.wqf</groupId>
      <artifactId>docker-demo</artifactId>
      <version>1.0</version>
      <name>docker-demo</name>
      <description>Demo project for Spring Boot</description>
  
      <properties>
          <java.version>1.8</java.version>
      </properties>
  
      <dependencies>
          <dependency>
              <groupId>org.springframework.boot</groupId>
              <artifactId>spring-boot-starter-web</artifactId>
          </dependency>
  
          <dependency>
              <groupId>org.springframework.boot</groupId>
              <artifactId>spring-boot-starter-test</artifactId>
              <scope>test</scope>
          </dependency>
      </dependencies>
  
      <build>
          <plugins>
              <!-- springboot 打包插件 -->
              <plugin>
                  <groupId>org.springframework.boot</groupId>
                  <artifactId>spring-boot-maven-plugin</artifactId>
              </plugin>
              <plugin>
                  <!-- dockerfile 打包插件 -->
                  <groupId>com.spotify</groupId>
                  <artifactId>dockerfile-maven-plugin</artifactId>
                  <version>1.4.13</version>
                  <executions>
                      <execution>
                          <id>default</id>
                          <goals>
                              <goal>build</goal>
                          </goals>
                      </execution>
                  </executions>
                  <configuration>
                      <!-- 打包后的镜像名 -->
                      <repository>myapp</repository>
                      <!-- 指定 Dockerfile 文件 -->
                      <!--<dockerfile>src/main/docker/Dockerfile</dockerfile>-->
                      <!-- 版本号 -->
                      <tag>${project.version}</tag>
                      <!-- 构建参数，将传入 Dockerfile 中使用 -->
                      <buildArgs>
                          <!-- 打包后的 jar 包名 -->
                          <JAR_FILE>${project.build.finalName}.jar</JAR_FILE>
                      </buildArgs>
                  </configuration>
              </plugin>
          </plugins>
      </build>
  </project>
  ```

  > 注意上述示例中，dockerfile-maven 插件版本是 `1.4.13` ，在配置项中，配置项 `dockerfile` 用于指定 Dockerfile 文件，这个配置在 Windows 系统中会出错，构建时会报 `build failed: Could not acquire image ID` 错误，将 Dockerfile 文件放在项目根目录并去除这个配置项即可成功打包。

- 在项目根目录创建 `Dockerfile` 文件，内容如下：

  ```cmake
  # 指定基础镜像
  FROM openjdk:8-jre-alpine
  # 构建参数
  ARG JAR_FILE
  ADD target/${JAR_FILE} app.jar
  # 暴露的端口号
  EXPOSE 8080
  # 运行时执行的命令
  ENTRYPOINT ["java","-jar","/app.jar"]
  ```

- 运行 maven 构建命令 `mvn clean package` 即可完成项目打包并生成 docker 镜像。

  ```bash
  $ mvn clean package -Dmaven.test.skip=true
  [INFO] Scanning for projects...
  [INFO]
  [INFO] ------------------------< xyz.wqf:docker-demo >-------------------------
  [INFO] Building docker-demo 1.0
  [INFO] --------------------------------[ jar ]---------------------------------
  [INFO]
  [INFO] --- maven-clean-plugin:3.1.0:clean (default-clean) @ docker-demo ---
  [INFO] Deleting D:\myGithub\docker-demo\target
  [INFO]
  [INFO] --- maven-resources-plugin:3.2.0:resources (default-resources) @ docker-demo ---
  [INFO] Using 'UTF-8' encoding to copy filtered resources.
  [INFO] Using 'UTF-8' encoding to copy filtered properties files.
  [INFO] Copying 1 resource
  [INFO] Copying 0 resource
  [INFO]
  [INFO] --- maven-compiler-plugin:3.8.1:compile (default-compile) @ docker-demo ---
  [INFO] Changes detected - recompiling the module!
  [INFO] Compiling 1 source file to D:\myGithub\docker-demo\target\classes
  [INFO]
  [INFO] --- maven-resources-plugin:3.2.0:testResources (default-testResources) @ docker-demo ---
  [INFO] Not copying test resources
  [INFO]
  [INFO] --- maven-compiler-plugin:3.8.1:testCompile (default-testCompile) @ docker-demo ---
  [INFO] Not compiling test sources
  [INFO]
  [INFO] --- maven-surefire-plugin:2.22.2:test (default-test) @ docker-demo ---
  [INFO] Tests are skipped.
  [INFO]
  [INFO] --- maven-jar-plugin:3.2.0:jar (default-jar) @ docker-demo ---
  [INFO] Building jar: D:\myGithub\docker-demo\target\docker-demo-1.0.jar
  [INFO]
  [INFO] --- spring-boot-maven-plugin:2.4.1:repackage (repackage) @ docker-demo ---
  [INFO] Replacing main artifact with repackaged archive
  [INFO]
  [INFO] --- dockerfile-maven-plugin:1.4.13:build (default) @ docker-demo ---
  [INFO] dockerfile: null
  [INFO] contextDirectory: D:\myGithub\docker-demo
  [INFO] Building Docker context D:\myGithub\docker-demo
  [INFO] Path(dockerfile): null
  [INFO] Path(contextDirectory): D:\myGithub\docker-demo
  [INFO]
  [INFO] Image will be built as myapp:1.0
  [INFO]
  [INFO] Step 1/5 : FROM openjdk:8-jre-alpine
  [INFO]
  [INFO] Pulling from library/openjdk
  [INFO] Digest: sha256:f362b165b870ef129cbe730f29065ff37399c0aa8bcab3e44b51c302938c9193
  [INFO] Status: Image is up to date for openjdk:8-jre-alpine
  [INFO]  ---> f7a292bbb70c
  [INFO] Step 2/5 : ARG JAR_FILE
  [INFO]
  [INFO]  ---> Running in 6e45bf1b1d5b
  [INFO] Removing intermediate container 6e45bf1b1d5b
  [INFO]  ---> effefe64df84
  [INFO] Step 3/5 : ADD target/${JAR_FILE} app.jar
  [INFO]
  [INFO]  ---> fe444ba3d4bc
  [INFO] Step 4/5 : EXPOSE 8080
  [INFO]
  [INFO]  ---> Running in 76bbd4c0432a
  [INFO] Removing intermediate container 76bbd4c0432a
  [INFO]  ---> 7834b4d0ed33
  [INFO] Step 5/5 : ENTRYPOINT ["java","-jar","/app.jar"]
  [INFO]
  [INFO]  ---> Running in 34223d0a41c4
  [INFO] Removing intermediate container 34223d0a41c4
  [INFO]  ---> e0db2c430636
  [INFO] Successfully built e0db2c430636
  [INFO] Successfully tagged myapp:1.0
  [INFO]
  [INFO] Detected build of image with id e0db2c430636
  [INFO] Building jar: D:\myGithub\docker-demo\target\docker-demo-1.0-docker-info.jar
  [INFO] Successfully built myapp:1.0
  [INFO] ------------------------------------------------------------------------
  [INFO] BUILD SUCCESS
  [INFO] ------------------------------------------------------------------------
  [INFO] Total time:  45.092 s
  [INFO] Finished at: 2021-01-13T14:47:33+08:00
  [INFO] ------------------------------------------------------------------------
  ```

#### 方式三：使用 jib-maven-plugin 插件打包

同样的使用 maven 插件，还可以选用 google 提供的容器化工具 jib。

> GoogleContainerTools/jib: <https://github.com/GoogleContainerTools/jib/tree/master/jib-maven-plugin> 

操作步骤：

- 引入 jib 插件，添加配置。pom.xml：

  ```xml
  <?xml version="1.0" encoding="UTF-8"?>
  <project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
           xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
      <modelVersion>4.0.0</modelVersion>
      <parent>
          <groupId>org.springframework.boot</groupId>
          <artifactId>spring-boot-starter-parent</artifactId>
          <version>2.4.1</version>
          <relativePath/> <!-- lookup parent from repository -->
      </parent>
      <groupId>xyz.wqf</groupId>
      <artifactId>docker-demo</artifactId>
      <version>1.0</version>
      <name>docker-demo</name>
      <description>Demo project for Spring Boot</description>
  
      <properties>
          <java.version>1.8</java.version>
      </properties>
  
      <dependencies>
          <dependency>
              <groupId>org.springframework.boot</groupId>
              <artifactId>spring-boot-starter-web</artifactId>
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
              <plugin>
                  <!-- jib 打包插件 -->
                  <groupId>com.google.cloud.tools</groupId>
                  <artifactId>jib-maven-plugin</artifactId>
                  <version>2.7.1</version>
                  <executions>
                      <execution>
                          <!-- 在 maven 打包(package)时执行 -->
                          <phase>package</phase>
                          <goals>
                              <!-- 打包发布到本地 docker -->
                              <goal>dockerBuild</goal>
                          </goals>
                      </execution>
                  </executions>
                  <configuration>
                      <from>
                          <!-- 指定基础镜像，使用本地的 openjdk8 镜像 -->
                          <image>docker://openjdk:8-jre-alpine</image>
                      </from>
                      <to>
                          <!-- 构建的目标镜像，镜像名为 myapp -->
                          <image>myapp</image>
                          <tags>
                              <!-- 指定版本标签，可指定多个标签，默认会有一个 latest 标签 -->
                              <tag>1.0</tag>
                          </tags>
                      </to>
                      <container>
                          <ports>
                              <!-- 要暴露的接口 -->
                              <port>8080</port>
                          </ports>
                      </container>
                  </configuration>
              </plugin>
          </plugins>
      </build>
  </project>
  ```

  

- 使用命令打包，因为在配置中我们指定构建docker 镜像的动作与 maven 的生命周期 package 绑定，所以我们只需要执行 maven 打包命令，即可同时完成构建 maven 镜像。打包命令为：

  ```bash
  mvn clean package
  ```

  此外，我们还可以使用 jib 插件进行打包，打包命令为：

  ```bash
  mvn compile jib:dockerBuild
  ```

  

#### 运行镜像

打包完成后，使用 `docker image ls` 命令可查看本地的镜像，然后使用 `docker run` 命令运行镜像。

> 命令参数说明：
>
> - 使用 `--name` 指定运行的容器名称为 `my-app` 
>
> - 使用 `-p` 指定访问端口，将本机的 `8080` 端口映射到容器内的 `8080` 端口
>
> - 运行的镜像是之前创建的镜像 `myapp:1.0` 

```bash
docker run --name=my-app -p8080:8080 myapp:1.0
```

运行结果：

![](https://blog-images.qiniu.wqf31415.xyz/springboot-docker-run.png)

访问测试接口 <http://localhost:8080/hello> ，页面显示 `world` 说明运行正确。



#### 后续管理

创建容器并运行后，可使用 docker 进行管理：

- 关闭运行的容器：`docker stop my-app` 
- 删除容器：`docker container rm my-app` 
- 删除镜像：`docker image rm myapp:1.0` 



### 关联其他容器的项目

很多时候，项目会依赖其他程序，如数据库，这时也可以使用 docker 打包并使用 docker-compose 创建并启动所有相关的容器。

#### 示例项目代码

创建一个 springboot + jpa 使用 mysql 数据库的示例项目。

##### 项目 pom.xml 

在项目中引入 jpa、mysql 连接相关依赖，然后添加构建 docker 镜像的插件与配置。

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>2.4.1</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>
    <groupId>xyz.wqf</groupId>
    <artifactId>docker-demo</artifactId>
    <version>1.0</version>
    <name>docker-demo</name>
    <description>Demo project for Spring Boot</description>

    <properties>
        <java.version>1.8</java.version>
    </properties>

    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-jpa</artifactId>
        </dependency>
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>8.0.21</version>
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
            <plugin>
                <!-- dockerfile 打包插件 -->
                <groupId>com.spotify</groupId>
                <artifactId>dockerfile-maven-plugin</artifactId>
                <version>1.4.13</version>
                <executions>
                    <execution>
                        <id>default</id>
                        <goals>
                            <goal>build</goal>
                        </goals>
                    </execution>
                </executions>
                <configuration>
                    <!-- 打包后的镜像名 -->
                    <repository>myapp</repository>
                    <!-- 指定 Dockerfile 文件 -->
                    <!--<dockerfile>docker/Dockerfile</dockerfile>-->
                    <!-- 版本号 -->
                    <tag>${project.version}</tag>
                    <!-- 构建参数，将传入 Dockerfile 中使用 -->
                    <buildArgs>
                        <!-- 打包后的 jar 包名 -->
                        <JAR_FILE>${project.build.finalName}.jar</JAR_FILE>
                    </buildArgs>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>
```

##### 项目配置 application.yml

添加数据源相关配置。

```yaml
server:
  port: 8080
spring:
  application:
    name: DockerDemo
  datasource:
    url: jdbc:mysql://localhost:3306/docker-demo?serverTimezone=UTC&useUnicode=true&characterEncoding=utf8&useSSL=false
    username: root
    password:
    type: com.zaxxer.hikari.HikariDataSource
  jpa:
    hibernate:
      ddl-auto: create
```

##### 实体类 Student.java

添加一个测试用的实体类——Student 类。

```java
package xyz.wqf.dockerdemo.domain;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Student {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String name;

    private Short age;

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

    public Short getAge() {
        return age;
    }

    public void setAge(Short age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Student{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
```

##### Jpa 仓库类 StudentRepository.java

```java
package xyz.wqf.dockerdemo.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import xyz.wqf.dockerdemo.domain.Student;

public interface StudentRepository extends JpaRepository<Student, Long> {
}
```

##### 控制器 StudentResource.java

```java
package xyz.wqf.dockerdemo.web.rest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import xyz.wqf.dockerdemo.domain.Student;
import xyz.wqf.dockerdemo.repository.StudentRepository;

import java.util.List;

@RestController
public class StudentResource {
    @Autowired
    private StudentRepository studentRepository;

    @GetMapping("/students")
    public List<Student> findAll(){
        return studentRepository.findAll();
    }

    @GetMapping("/students/{id}")
    public Student findOne(@PathVariable(name = "id") Long id){
        return studentRepository.findById(id).orElse(null);
    }

    @PostMapping("/students")
    public Student createOne(Student student){
        return studentRepository.save(student);
    }

    @PutMapping("/students")
    public Student modifyOne(Student student){
        return studentRepository.save(student);
    }

    @DeleteMapping("/students/{id}")
    public void deleteOne(@PathVariable Long id){
        studentRepository.deleteById(id);
    }
}
```

##### 自动插入示例数据 import.sql

在 `src/main/resources` 目录下创建文件 ``

```sql
insert into student(id,name,age) values (1,"张三",18),(2,"李四",20),(3,"王五",23);
```

#### Dockerfile

在项目跟目录创建 `Dockerfile` 文件，配置如下：

> **注意这里修改了项目启动时执行的命令，启动时休眠了 30 秒，是为了让依赖的其他容器启动起来，然后再启动应用容器，否则应用容器可能会启动失败。** 

```dockerfile
# 指定基础镜像
FROM openjdk:8-jre-alpine
# 构建参数
ARG JAR_FILE
ADD target/${JAR_FILE} app.jar
# 暴露的端口号
EXPOSE 8080
# 运行时执行的命令
# 打印了一句提示信息，然后等待 30s，等其他依赖的容器启动起来，最后再启动应用容器
CMD echo "The application will start in 30s" && \
 sleep 30 && \
 java -jar /app.jar
```

#### docker-compose 配置

在项目根目录下创建 `docker` 目录，用于存放 docker-compose 配置，需要创建两个配置文件，分别是数据库的和应用的。

##### 数据库配置 mysql.yml

创建一个 `mysql.yml` 配置文件，用于使用 docker-compose 创建数据库容器。这里使用的是 mysql 5.7，访问用户名为 `root` ，密码为空，创建了一个 `docker-demo` 数据库。

```yaml
version: '3.1' # docker-compose 版本
services: # 要启动的服务
  dockerdemo-mysql: # 服务名
    container_name: dockerdemo-mysql # 生成的容器名
    image: mysql:5.7 # 使用的镜像
    environment: # 环境变量
      - MYSQL_USER=root # 用户名
      - MYSQL_ALLOW_EMPTY_PASSWORD=yes # 使用空密码
      - MYSQL_DATABASE=docker-demo # 创建数据库
    ports: # 暴露的端口
      - 4306:3306
    # 启动命令
    command: mysqld --lower_case_table_names=1 --skip-ssl --character_set_server=utf8mb4 --explicit_defaults_for_timestamp 
```

在开发时，可以使用 docker-compose 启动一个数据库服务用来开发，启动命令为：

```bash
docker-compose -f docker/mysql.yml up
```

> `-f` 用于指定配置文件

##### 项目配置 app.yml

app.yml 配置文件，用于启动应用程序的容器。

这个配置中同时启动了一个数据库服务（`dockerdemo-mysql`），然后配置应用的数据库访问地址，指向启动的数据库服务（`dockerdemo-mysql`）。

> 注意：这里的访问地址是 `dockerdemo-mysql` 是数据库容器名，访问端口是 `3306` 是数据库容器内的访问端口，而不是对外暴露的端口 `4306` 。

```yaml
version: '3.1'
services:
  my-app:
    links: # 关联的容器
      - dockerdemo-mysql
    image: myapp:1.0 # 使用自己构建的镜像 mysql：1.0
    container_name: my-app # 容器名
    environment:
      # 指定数据库访问 url，指向关联的 dockerdemo-mysql 容器
      - SPRING_DATASOURCE_URL=jdbc:mysql://dockerdemo-mysql:3306/docker-demo?serverTimezone=UTC&useUnicode=true&characterEncoding=utf8&useSSL=false
    ports: # 暴露的端口
      - 8080:8080
  dockerdemo-mysql: # 数据库服务
    extends: # 配置信息继承自文件 mysql.yml
      file: mysql.yml
      service: dockerdemo-mysql
```

#### 启动应用容器

使用 maven 打包项目，打包时会自动构建镜像 `myapp:1.0` ，打包命令：

```bash
mvn clean package
```

使用 docker-compose 启动应用容器：

```bash
docker-compose -f docker/app.yml up
```

执行命令后，将自动启动 mysql 容器和 app 容器。

![](https://blog-images.qiniu.wqf31415.xyz/springboot-docker-compose-up.png) 

启动成功后，访问 <http://localhost:8080/students> ，能查询到自动插入数据中的数据表明启动成功。

> 如果数据库容器启动太慢，在应用容器启动时还未启动，将导致应用容器启动失败，这时可以再次尝试使用 docker-compose 启动。

#### docker-compose 管理命令

- 创建并启动：`docker-compose -f docker/app.yml up` 
- 创建并在后台启动：`docker-compose -f docker/app.yml up -d` 
- 停止并删除容器：`docker-compose -f docker/app.yml down` 



### 参考资料

- Docker部署SpringBoot项目: <https://www.jianshu.com/p/397929dbc27d> 
- 使用Maven插件构建Docker镜像: <https://www.cnblogs.com/guoyinghome/p/11220317.html> 
- spotify/dockerfile-maven: <https://github.com/spotify/dockerfile-maven> 
- dockerfile-maven-plugin:1.4.10:build failed: Could not acquire image ID: <https://blog.csdn.net/baidu_38332802/article/details/104391324> 
- Jib使用小结(Maven插件版): <https://blog.csdn.net/boling_cavalry/article/details/100179709> 



### 总结

通过开源的 maven 插件，能够非常方便的将 springboot 项目打包并制作成镜像，能够方便的使用容器技术来部署项目。尤其是微服务项目，能够方便的开启多个服务来进行测试。

示例项目地址：<https://github.com/wqf31415/docker-demo.git> 