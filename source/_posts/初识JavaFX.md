---
title: 初识JavaFX
tags:
  - java
  - javaFx
categories:
  - java
date: 2021-09-23 15:00:34
---

### 概述

这篇文章介绍了 Java FX ，以及创建 java FX 项目。

![](http://images.qiniu.wqf31415.xyz/desk_1280.jpg)

### 关于 JavaFX

JavaFX 是一个开源的、使用 java 开发桌面应用的技术，包含了一组强大的图形和多媒体处理 API，同时具有 java 的跨平台特性。从 Java8开始，JDK 包含了 JavaFX 库，Oracle 在 jdk 11 及后续版本中开源了 JavaFX，[参考文档](https://wiki.openjdk.java.net/display/OpenJFX)。

> JDK SE 8 参考文档: <https://docs.oracle.com/javase/8/javase-clienttechnologies.htm> 
>
> OpenJFX: <https://openjfx.io/> 



<!-- more -->



### JavaFX 特性

- **Java API**：JavaFX 使用 java 开发，能够调用丰富的 Java 接口，同时对使用 JVM 的编程语言支持友好，如 JRuby、Scala。
- **FXML**：JavaFX 中使用 fxml （基于 xml 的描述标记语言）来定义 UI 界面，使用 java 编码程序逻辑，实现展示和逻辑分离。
- **WebView**：使用 WebKitHTML 技术在 JavaFX 应用中集成 web 组件，支持 heml5 特性，支持 JavaScript 调用 Java API。
- **Swing 互操作性**：在 JavaFX 中可直接使用 Swing，使用 `SwingNode` 类将 Swing 内容嵌入到 JavaFX 程序中。
- **CSS**：JavaFX 支持内嵌样式和使用 css 定义 UI 样式。
- **3D图形功能**：支持 Shape3D（Box、Cylinder、MeshView、Sphere 子类）、SubScene、Material、PickResult、LightBase、SceneAntialiasing。
- **Canvas**：使用 Canvas API，支持在 javaFX 场景上绘制。
- **打印**：在 Java SE 8 的 `javafx.print` 包中提供了操作打印机的接口。
- **富文本**：支持增强文本，包括双向文本和复杂的文本脚本，如多行、多风格文本。
- **多点触控**：支持多点触控操作。
- **Hi-DPI**：JavaFX 8 已支持 Hi-DPI 显示。
- **硬件加速图形管道**：JavaFX 支持图形显卡加速渲染。
- **高性能媒体引擎**：提供基于 GStreamer 的稳定、低延迟的媒体框架。
- **自包含应用部署模式**：JavaFX程序可包括所有需要的资源及 Java、JavaFX 运行时的私有副本，可作为本机可安装包分发，并提供与该操作系统本机应用程序相同的安装和启动体验。



### JavaFX 程序基本结构

JavaFX 程序结构内容包括舞台（Stage）、场景（Scene）、容器（Container）、布局（Layout）和控件（Controls）。

![](https://blog-images.qiniu.wqf31415.xyz/javafx_program_frame.jpg)



### 创建 JavaFX 项目

#### 环境

需要 JDK 8 或以上的 java 环境。

IDE 可使用 Intellij IDEA 、 Eclipse 或 NetBeans ，其中 IDEA 和 NetBeans 支持直接创建 JavaFX 项目，Eclipse 需要安装 `e(fx)clipse` 插件。



#### 创建项目

点击 IDEA 菜单栏 “File” - “New” - “Project...” ，然后在新建项目对话框中选择 Java FX，点击 “NEXT” 填写项目名称、路径等信息创建项目，使用 idea 创建的项目包含示例代码。

![](https://blog-images.qiniu.wqf31415.xyz/idea_create_javafx.png) 



#### 项目代码

##### Main.java

项目主类，程序入口。项目运行后将呈现一个空白窗口，标题为 `Hello World` 。

```java
package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
// JavaFX 应用需要继承 javafx.application.Application 类
public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        // 引入 fxml
        Parent root = FXMLLoader.load(getClass().getResource("sample.fxml"));
        // 设置标题栏
        primaryStage.setTitle("Hello World");
        // 设置 Scene
        primaryStage.setScene(new Scene(root, 300, 275));
        // 显示界面
        primaryStage.show();
    }

    public static void main(String[] args) {
        // 启动 JavaFX 应用
        launch(args);
    }
}

```



##### sample.fxml

fxml 中定义了应用界面结构。`fx:controller` 参数中定义了控制类。

```xml
<?import javafx.geometry.Insets?>
<?import javafx.scene.layout.GridPane?>

<?import javafx.scene.control.Button?>
<?import javafx.scene.control.Label?>
<GridPane fx:controller="sample.Controller"
          xmlns:fx="http://javafx.com/fxml" alignment="center" hgap="10" vgap="10">
</GridPane>
```



##### Controller.java

控制类。

```java
package sample;

public class Controller {
}
```



### 使用 maven 构建项目

使用 maven 构建 JavaFX 项目时，只需要在普通 maven 项目的主类中启动 JavaFX 即可，然后在 `pom.xml` 中指定打包配置即可。

#### 创建 maven 项目

使用 IDE 创建一个空白的 maven 项目。



#### 创建程序主类

创建包和主类 `Main.java` ，继承 `javafx.application.Application` ，实现 `start` 方法，在 `main` 方法中调用 `launch` 方法。

```java
package xyz.wqf.mavenfx;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        primaryStage.setTitle("Hello");
        StackPane root = new StackPane();
        Button btn = new Button();
        btn.setText("hello");
        btn.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                System.out.println("hello world");
            }
        });
        root.getChildren().add(btn);
        Scene scene = new Scene(root,480,320);
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
```



#### 修改 pom.xml

在 maven 项目的 `pom.xml` 中添加打包配置，指定程序入口类，这样使用 maven 打包后的包才能正确运行。

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>xyz.wqf</groupId>
    <artifactId>maven-fx</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>jar</packaging>

    <dependencies>

    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <configuration>
                    <source>1.8</source>
                    <target>1.8</target>
                    <encoding>UTF-8</encoding>
                </configuration>
            </plugin>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-jar-plugin</artifactId>
                <version>3.0.2</version>
                <configuration>
                    <archive>
                        <manifest>
                            <addClasspath>true</addClasspath>
                             <!-- 指定程序主入口 -->
                            <mainClass>xyz.wqf.mavenfx.Main</mainClass>
                        </manifest>
                    </archive>
                </configuration>
            </plugin>
        </plugins>
    </build>

</project>
```



### 使用 JavaFX Scene Builder

JavaFX Scene Builder 是一个可视化布局工具，直接通过推拽方式添加组件，修改组件属性，可快速设计 JavaFX 程序界面，保存后可得到界面结构的 fxml 代码文件。

> JavaFX Scene Builder 下载链接：<http://javafxchina.net/code/download/SceneBuilder.jar> 

![](https://blog-images.qiniu.wqf31415.xyz/javafx_scene_builder.png)



### 参考资料

- JavaFX China: <http://www.javafxchina.net/main/> 
- JavaFX教程™: <https://www.yiibai.com/javafx/> 



