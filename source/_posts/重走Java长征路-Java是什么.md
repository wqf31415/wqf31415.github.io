---
title: 重走Java长征路-Java是什么
date: 2018-04-07 13:31:44
tags:
- java
categories:
- 技术
---

### 关于本系列文章
我从2016年8月开始在培训班系统学习 Java，至今已经有近2年时间了，但在使用Java编程过程中发现还有很多基础的东西不明白，很多时候要依靠搜索引擎，恍然发现，过去的学习是为了能尽快会用，能够开展工作，因此很多时候只要求能够使用，而没有去思考内在的思想。思来想去，还是古人说得好，“九层之台，起于垒土”，若想在 Java 这条路上走得远、走得稳，还是要花时间来把基础夯实，不让基础不实影响将来的学习发展。因此，我决定重走Java长征路，重头开始，再来学习一次java，从认识 java 开始，一直学到现在用到的技术框架。

![](http://blog-images.qiniu.wqf31415.xyz/java_coffee.jpg)

### Java是什么？
#### Java简介
Java 是一种 **高级** 的 **面向对象** 的程序设计语言。高级是相对于 机器语言、汇编语言来说的，编程过程接近自然语言，通过编译后生成机器能够识别的语言，从而能够在计算机上运行。面向对象(Object Oriented, OO) 是一种编程设计方式，核心是万事万物皆对象，主要特征有封装、继承、多态、抽象、集合等。
Java 语法规则与 C++ 类似，但比 C++简洁，而且去除了其中的指针和多重继承概念。
Java 编写的程序既是编译型的，又是解释型的，程序代码经过编译后转换成可被 Java 虚拟机识别的字节码，Java 虚拟机(JVM)将字节码解释成机器码，最后在计算机上运行。编译只需执行一次，但在 java 虚拟机中运行时，要对每条字节码进行解释执行，因此在执行效率来看是不及 C++ 的。



<!-- more -->



#### Java历史
- **1991年** Java 前身 Oak，James Gosling博士领导的绿色计划（Green Project）开始启动，此计划的目的是开发一种能够在各种消费性电子产品（如机顶盒、冰箱、收音机等）上运行的程序架构。这个计划的产品就是Java语言的前身：Oak（橡树）。
- **1995年** Java 1.0 ，由Java之父詹姆斯·戈士林博士设计，由Sun公司推出，完成了Java的原始编译器和虚拟机，OAK 重命名为 Java，第一次提出 “一次编译，到处运行” 的概念。

- **1996年** JDK 1.0 ，java 第一个正式版本的运行环境，代表技术包括：Java虚拟机、Applet、AWT等。
- **1997年** JDK 1.1，技术代表有：JAR文件格式、JDBC、JavaBeans、RMI。Java语法也有了一定的发展，如内部类（Inner Class）和反射（Reflection）。
- **1998** JDK 1.2，Java技术体系拆分为3个方向，分别是面向桌面应用开发的J2SE（Java 2 Platform， Standard Edition）、面向企业级开发的J2EE（Java 2 Platform， Enterprise Edition）和面向手机等移动终端开发的J2ME（Java 2 Platform， Micro Edition），代表性技术非常多，如EJB、Java Plug-in、Java IDL、Swing等，并且这个版本中Java虚拟机第一次内置了JIT（Just In Time）编译器。
- **1999年** HotSpot虚拟机发布，它成为了JDK 1.3及之后所有版本的Sun JDK的默认虚拟机。
- **2000年** JDK 1.3，修改了一些类库 api，如数学运算和新的Timer API等。
- **2002年** JDK 1.4，Java真正走向成熟的一个版本，技术特性：正则表达式、异常链、NIO、日志类、XML解析器和XSLT转换器等。
- **2004年** JDK 1.5，语法易用性上做出了非常大的改进，例如，自动装箱、泛型、动态注解、枚举、可变长参数、遍历循环（foreach循环）等，改进了Java的内存模型（Java Memory Model，JMM）、提供了java.util.concurrent并发包等。
- **2016年** JDK 1.6，提供动态语言支持（通过内置Mozilla Java Rhino引擎实现）、提供编译API和微型HTTP服务器API等。同时，这个版本对Java虚拟机内部做了大量改进，包括锁与同步、垃圾收集、类加载等方面的算法都有相当多的改动。
- **2009** JDK 1.7，提供新的G1收集器（G1在发布时依然处于Experimental状态，直至2012年4月的Update 4中才正式“转正”）、加强对非Java语言的调用支持（JSR-292，这项特性到目前为止依然没有完全实现定型）、升级类加载架构等。Sun 公司被 Oracle 公司收购，此后由 Oracle 公司维护。
- **2014年** JDK 8，新特性包括：lambda 表达式、函数式编程、接口可以添加默认实现方法和静态方法、方法引用、引入Optional 避免空指针，引入 Stream api、引入新的日期时间api、JVM使用MetaSpace代替了永久代（PermGen Space）等。
- **2017年** JDK 9，新特性：接口方法可以使用private来修饰、设置G1 为 JVM 默认垃圾收集器、支持http2.0的API等。
- **2018年3月** JDK 10，局部变量类型推断，类似JS可以通过var来修饰局部变量，编译之后会推断出值的真实类型，并行Full GC，来优化G1的延迟，允许在不执行全局VM安全点的情况下执行线程回调，可以停止单个线程，而不需要停止所有线程或不停止线程。
- **2018年9月** JDK 11，ZGC，ZGC可以看做是G1之上更细粒度的内存管理策略。由于内存的不断分配回收会产生大量的内存碎片空间，因此需要整理策略防止内存空间碎片化，在整理期间需要将对于内存引用的线程逻辑暂停，这个过程被称为"Stop the world"。只有当整理完成后，线程逻辑才可以继续运行。（并行回收）。Flight Recorder（飞行记录器），基于OS、JVM和JDK的事件产生的数据收集框架。
- **2019年3月** JDK 12，Shenandoah GC，Switch 表达式表达式，G1收集器的优化。
- **2019年9月** JDK 13，扩展应用程序类-数据共享、增强ZGC以将未使用的堆内存返回给操作系统、使用易于维护和调试的更简单、更现代的实现替换java.net.Socket和java.net.ServerSocket API使用的底层实现、可在生产环境中使用的 switch表达式，将文本块添加到Java语言。

#### Java版本
按Java的应用范围可以分为3个版本：
- **Java SE**：标准版，主要用于桌面应用程序开发，也是Java的基础，包含了Java语言基础、JDBC(Java数据库链接)操作、I/O(输入输出)、网络通信、多线程等技术。
- **Java EE**：企业版，用于开发企业级分布式网络程序，如电子商务和企业资源规划系统，核心是EJB(企业Java组件模型)。
- **Java ME**：移动版，主要应用于嵌入式开发，如掌上电脑、手机等移动通信设备，现在大多数手机都支持Java技术。

### Java能做什么？
Java是独立于平台的，所以它不仅能用于计算机领域，还能用于便携式计算机、电视、电话、手机和其他电子设备。当今java主要用于以下几个方面：
- web应用系统开发
- 分布式系统开发
- 多媒体系统开发
- 交互式系统开发
- 企业级应用开发
- 电子商务系统
- 嵌入式系统开发
- 桌面应用系统开发

### Java的特点
- **跨平台**: Java是一种与平台无关的编程语言，因为java程序可以用过java虚拟机将代码解释为机器码，直接在机器上运行。通过不同系统上的Java虚拟机，Java程序可以在Windows系统电脑、mac 苹果计算机、各种未处理器硬件平台、Unix等系统平台上运行，因此Java程序具有良好的可移植性，一次编写，到处运行。
- **面向对象**: 面向对象是Java语言的基础，在Java的世界里“万事万物皆对象”。
- **安全可靠**: Java删除了类似C语言中的指针和内存释放等语法，有效避免了非法操作内存。运行Java程序需要解释器，解释器会对Java字节码进行检查校验。Java有异常处理机制，将检查并消除编译和运行时的错误。
- **多线程**: 多线程机制能够使Java程序同时并行执行多项任务，提供了相应的同步机制来保证不同线程能够正确共享数据。



### JDK 与 JRE
- **JDK** 全称 Java Development Kit，即 Java 开发工具包，其中包含了 Java 运行环境 (JRE) 以及一些开发使用的编译、调试等工具，如 javac 用于编译 java 源文件，jps 用于查看当前正在运行的 java 程序等，适用于开发者。

- **JRE** 全称 Java Runtime Environment，即 Java 运行时环境，提供了 Java 运行时所必须的环境，包括 JVM 虚拟机以及 Java 核心类库，安装后就可以运行 Java 程序了，适用于普通用户。

  

### 配置Java环境
<div style="text-align: left;"><div style="border: 1px #ccc solid;display: inline-table;width: 30%; height: 40px;text-align: center;line-height: 40px;cursor:pointer;" class="tab" onmouseover="tabHover(this);" onmouseout="tabHoverOut(this)" onclick="clickTabel(0);">windows 系统</div><div style="border: 1px #ccc solid;display: inline-table;width: 30%; height: 40px;text-align: center;line-height: 40px;cursor:pointer;" class="tab" onmouseover="tabHover(this);" onmouseout="tabHoverOut(this)" onclick="clickTabel(1);">Linux 系统</div><div style="border: 1px #ccc solid;display: inline-table;width: 30%; height: 40px;text-align: center;line-height: 40px;cursor:pointer;" class="tab" onmouseover="tabHover(this);" onmouseout="tabHoverOut(this)"  onclick="clickTabel(2);"> mac 系统</div></div><div><div style="width: 100%;border: 1px #ccc solid;text-decoration: none;list-style: none;display: none;" class = "content-label"><h4 style="text-align: center;">在Windows系统电脑上安装jdk</h4><hr/><p style="padding: 0px 5px">1. <a href="http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html" target="_blank">下载jdk8 安装包</a><br/><img width="100%" src="http://blog-images.qiniu.wqf31415.xyz/download_jdk_4_windows.png"></p><hr><p style="padding: 0px 5px">2. 双击下载好的 <b>.exe</b> 文件，开始安装，在安装过程中会提示选择jdk安装路径，可以选择默认的，也可以自己制定，注意安装路径中不要有中文，这个安装路径需要记住，等会配置环境变量时要使用<br/><img style="margin: 0 auto;max-width: 100%" src="http://blog-images.qiniu.wqf31415.xyz/jdk8_exe.png"></p><hr><p style="padding: 0px 5px">3. 安装完成后，按 <b>Windows 键 + R</b> 运行 “cmd”，打开命令行工具，在命令行中运行 <b>java</b> 命令，如果出现类型下面的提示信息，说明 jdk 安装成功<br><img src="http://blog-images.qiniu.wqf31415.xyz/run_java_cmd.png"></p><hr><p style="padding: 0px 5px">4. 配置环境变量，首先我们找到刚才安装jdk的目录，我是使用的默认安装目录： <b>C:\Program Files\Java\jdk1.8.0_181</b> <br>打开系统控制面板，搜索 “编辑系统环境变量”，点击搜索到的按钮，在弹出的“系统属性”面板中点击“环境变量”；(<span style="font-size: smaller;color: gray">ps: 也可以直接点Windows 开始按钮，在下方搜索框中搜索“编辑系统环境变量”</span>)<br><img width="100%" src="http://blog-images.qiniu.wqf31415.xyz/modify_sys_path.png"></p><hr><p style="padding: 0px 5px">5. 点击“系统变量”下方的 <b>新建</b> 按钮，在弹出的对话框中填入变量名： <b>JAVA_HOME</b> ，变量值：<b>C:\Program Files\Java\jdk1.8.0_181</b> ，即本地jdk的安装路径，这样我们就新建了一个系统环境变量<br><img style="max-width: 100%" src="http://blog-images.qiniu.wqf31415.xyz/modify_sys_path_2.png"><br><img style="max-width: 100%" src="http://blog-images.qiniu.wqf31415.xyz/modify_sys_path_3.png"><br><br>使用相同的方法，我们新建一个名为 <b>classpath</b> ，值为 <b>%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar</b> 的环境变量<br><br>修改Path，在“系统变量”中找到 <b>Path</b> 项，点击“编辑”，在最后面添加 <b>;%JAVA_HOME%\bin;%JAVA_HOME%\jre\bin;</b> ，注意前后的分号，所有符号都是英文半角状态的<br><img style="max-width: 100%" src="http://blog-images.qiniu.wqf31415.xyz/modify_sys_path_4.png"></p><hr><p style="padding: 0px 5px">6. 验证配置是否正确，运行 “java -version” 命令查询jdk版本号，运行 “javac -version” 查看java编译器版本，运行 “jps” 查询当前运行的java程序<br><img style="max-width: 100%" src="http://blog-images.qiniu.wqf31415.xyz/check_java_version.png"><br>如果提示 “不是内部或外部命令，也不是可运行的程序或批处理文件。” 说明安装或环境变量配置有误<br><span style="font-size: smaller;color: gray">注意：修改完环境变量之后要重新打开命令行，否则可能会导致运行指令失败</span></p><hr></div><div style="width: 100%;border: 1px #ccc solid;text-decoration: none;list-style: none;display: none;" class = "content-label"><h4 style="text-align: center;">在Linux系统上安装jdk</h4><hr><p style="padding: 0px 5px">1. <a href="http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html" target="_blank">下载jdk8 安装包</a>，我使用的是 ubantu 16.4 LTS ，下载jdk时选择的是64位的 .tar.gz 压缩包版本<br><img style="max-width: 100%" src="http://blog-images.qiniu.wqf31415.xyz/download_jdk_4_ubantu.png"><br><img style="max-width: 100%" src="http://blog-images.qiniu.wqf31415.xyz/jdk8_tar_gz.png"></p><hr><p style="padding: 0px 5px">2. 解压文件。在/usr目录下新建一个名叫 “java-8” 的目录，当然这个目录名称可以随意，将下载好的jdk压缩包移动到这个目录下，并解压出来<br>在ubantu中可以直接右键点击jdk压缩包，选择提取到当前文件夹，也可以通过在命令行执行命令解压 <b>tar -zxvf tar -zxvf jdk-8u161-linux-x64.tar.gz</b> ，解压完成后，在当前目录下就多了一个 “jdk1.8.0_161” 目录，这里面放的就是jdk的文件了<br><img style="max-width: 100%" src="http://blog-images.qiniu.wqf31415.xyz/unpack_jdk_in_ubantu.png"></p><hr><p style="padding: 0px 5px">3. 配置环境变量。编辑 /etc/profile 文件，在最后面添加如下内容：<br>export JAVA_HOME=/usr/java-8/jdk1.8.0_161<br>export JRE_HOME=$JAVA_HOME/jre<br>export CLASSPATH=.:$CLASSPATH:$JAVA_HOME/lib:$JRE_HOME/lib<br>export PATH=$PATH:$JAVA_HOME/bin:$JRE_HOME/bin<br>注意要将 JAVA_HOME 的值配置为刚才解压的jdk的路径(<span style="font-size: smaller;color: gray">可以在命令行执行 pwd 命令查看路径</span>)，修改完成后执行 <b>source /etc/profile</b> 命令使修改的配置生效<br><img src="http://blog-images.qiniu.wqf31415.xyz/midify_java_path_in_ubantu.png"><hr><p style="padding: 0px 5px">4. 验证。打开命令行，运行 “java -version” 命令查询jdk版本号，运行 “javac -version” 查看java编译器版本，运行 “jps” 查询当前运行的java程序<br><img style="max-width: 100%" src="http://blog-images.qiniu.wqf31415.xyz/run_java_cmd_in_ubantu.png"><br>如果打出类似上面的信息，说明安装配置正确。</p><hr><p>ps: 也可以通过 apt 工具安装openjdk，打开命令行执行命令：sudo apt install openjdk-8-jdk<hr>关于openjdk与官网jdk的区别这里就不展开了。</p></div><div style="width: 100%;border: 1px #ccc solid;text-decoration: none;list-style: none;display: none;" class = "content-label"><h4 style="text-align: center;">在苹果电脑上安装jdk</h4><hr><p style="padding: 0px 5px">没有用过苹果电脑，所以没有截图，安装过程也比较简单，直接下载 供 MAC OS 使用的 .dmg 文件，下载完成后直接点击,按提示安装即可。安装完成后也需要配置环境变量，可以参考： <a href="https://blog.csdn.net/vvv_110/article/details/72897142">MAC安装JDK及环境变量配置</a></p><hr><br></div></div>
<script>clickTabel(0);function clickTabel(num){var cls = document.getElementsByClassName("content-label");var tabs = document.getElementsByClassName("tab");for(var i=0;i<cls.length;i++){if(i == num){cls[i].style.display='block';}else{cls[i].style.display = 'none';}}; for(var i = 0;i<tabs.length;i++){if(i == num){tabs[i].style.borderColor='#4b4';tabs[i].style.backgroundColor='#5c5';}else{tabs[i].style.borderColor='#ccc';	tabs[i].style.backgroundColor='white';}}}function tabHover(dd){	dd.style.fontWeight='bold';}function tabHoverOut(dd){dd.style.fontWeight='normal';}</script>



### Java 开发工具

#### IntelliJ IDEA

> 官网地址：http://www.jetbrains.com/idea/

推荐指数：5星

由 JetBrains 公司提供的，非常好用的开发工具，功能完善，插件众多，界面美观，受众多java开发人员喜爱，被称为业内最好用的java集成开发工具。其中 Ultimate 版需要注册，适合web和企业开发者，Community 版是开源的，免费使用的，适合jvm 和 Android 开发者。



#### Eclipse

> 官网地址：http://www.eclipse.org/

推荐指数：4星半

老牌IDE，开源，插件多，功能齐全，java开发工具第二大阵营。



#### MyEclipse
收费
> 官网地址：https://www.genuitec.com/products/myeclipse/
>
> 中文官网：http://www.myeclipsecn.com/

推荐指数：4星

对Eclipse进行优化，增加了很多实用的功能，使用方便，但是需要购买。



#### NetBeans

> 官网地址：https://netbeans.org/

推荐指数：3星





#### JBuilder

> 官网地址: http://edn.embarcadero.com/jbuilder

推荐指数：2星





#### JCreator

> 官网地址：http://www.jcreator.com/

推荐指数：2星



#### 文本编辑器

理论上来说，只要是能编辑文本的工具都可以写java代码，像Windows中的文本编辑器、notepad++、sublime等等，但这种只适合在学习时写一些小的代码片段，不适合开发项目。（大神请忽略，大神基本上也不会看到这里的，哈哈）





