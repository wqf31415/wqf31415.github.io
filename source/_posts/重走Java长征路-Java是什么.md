---
title: 重走Java长征路-Java是什么
date: 2018-04-07 13:31:44
tags:
- java
categories:
- 技术
---

### 关于本系列文章
我从2016年8月开始在培训班系统学习Java，至今已经有近2年时间了，但在使用Java编程过程中发现还有很多基础的东西不明白，很多时候还要依靠搜索引擎，恍然发现，过去的学习是为了能尽快学成，能够开展工作，因此很多时候只要求能够使用，而没有去思考内在的思想。思来想去，觉得古人说得好，“九层之台，起于垒土”，我要想在Java这条路上走得远、走得稳，还是要花时间来把基础夯实，不让基础不实影响将来的学习发展。因此，我决定重走Java长征路，重头开始，再来学习一次java，从java是什么开始，一直学到现在用到的技术。

### Java是什么？
#### Java简介
Java是一种高级的面向对象的程序设计语言。
Java语法规则与C++类似，但比C++简洁，而且去除了其中的指针和多重继承概念。
Java编写的程序既是编译型的，又是解释型的，程序代码经过编译后转换成可被Java虚拟机识别的字节码，Java虚拟机(JVM)将字节码解释成机器码，最后在计算机上运行。编译只需执行一次，但每次执行时都要进行解释，因此在执行效率来看是不及C++的。

#### Java历史
1995年 由Java之父詹姆斯`戈士林博士设计，由Sun公司推出，完成了Java的原始编译器和虚拟机。Java最初的名字叫OAK，1995年被重命名为Java。



<!-- more -->



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



### 配置Java环境
<div style="text-align: left;"><div style="border: 1px #ccc solid;display: inline-table;width: 30%;min-width:130px; height: 40px;text-align: center;line-height: 40px;cursor:pointer;" class="tab" onmouseover="tabHover(this);" onmouseout="tabHoverOut(this)" onclick="clickTabel(0);">windows 系统</div><div style="border: 1px #ccc solid;display: inline-table;width: 30%;min-width:130px; height: 40px;text-align: center;line-height: 40px;cursor:pointer;" class="tab" onmouseover="tabHover(this);" onmouseout="tabHoverOut(this)" onclick="clickTabel(1);">Linux 系统</div><div style="border: 1px #ccc solid;display: inline-table;width: 30%;min-width:130px; height: 40px;text-align: center;line-height: 40px;cursor:pointer;" class="tab" onmouseover="tabHover(this);" onmouseout="tabHoverOut(this)"  onclick="clickTabel(2);"> mac 系统</div></div><div><div style="width: 100%;border: 1px #ccc solid;text-decoration: none;list-style: none;display: none;" class = "content-label"><h4 style="text-align: center;">在Windows系统电脑上安装jdk</h4><hr/><p style="padding: 0px 5px">1. <a href="http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html" target="_blank">下载jdk8 安装包</a><br/><img width="100%" src="http://okbn8yrzu.bkt.clouddn.com/download_jdk_4_windows.png"></p><hr><p style="padding: 0px 5px">2. 双击下载好的 <b>.exe</b> 文件，开始安装，在安装过程中会提示选择jdk安装路径，可以选择默认的，也可以自己制定，注意安装路径中不要有中文，这个安装路径需要记住，等会配置环境变量时要使用<br/><img style="margin: 0 auto;max-width: 100%" src="http://okbn8yrzu.bkt.clouddn.com/jdk8_exe.png"></p><hr><p style="padding: 0px 5px">3. 安装完成后，按 <b>Windows 键 + R</b> 运行 “cmd”，打开命令行工具，在命令行中运行 <b>java</b> 命令，如果出现类型下面的提示信息，说明 jdk 安装成功<br><img src="http://okbn8yrzu.bkt.clouddn.com/run_java_cmd.png"></p><hr><p style="padding: 0px 5px">4. 配置环境变量，首先我们找到刚才安装jdk的目录，我是使用的默认安装目录： <b>C:\Program Files\Java\jdk1.8.0_181</b> <br>打开系统控制面板，搜索 “编辑系统环境变量”，点击搜索到的按钮，在弹出的“系统属性”面板中点击“环境变量”；(<span style="font-size: smaller;color: gray">ps: 也可以直接点Windows 开始按钮，在下方搜索框中搜索“编辑系统环境变量”</span>)<br><img width="100%" src="http://okbn8yrzu.bkt.clouddn.com/modify_sys_path.png"></p><hr><p style="padding: 0px 5px">5. 点击“系统变量”下方的 <b>新建</b> 按钮，在弹出的对话框中填入变量名： <b>JAVA_HOME</b> ，变量值：<b>C:\Program Files\Java\jdk1.8.0_181</b> ，即本地jdk的安装路径，这样我们就新建了一个系统环境变量<br><img style="max-width: 50%" src="http://okbn8yrzu.bkt.clouddn.com/modify_sys_path_2.png"><img style="max-width: 50%" src="http://okbn8yrzu.bkt.clouddn.com/modify_sys_path_3.png"><br><br>使用相同的方法，我们新建一个名为 <b>classpath</b> ，值为 <b>%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar</b> 的环境变量<br><br>修改Path，在“系统变量”中找到 <b>Path</b> 项，点击“编辑”，在最后面添加 <b>;%JAVA_HOME%\bin;%JAVA_HOME%\jre\bin;</b> ，注意前后的分号，所有符号都是英文半角状态的<br><img style="max-width: 100%" src="http://okbn8yrzu.bkt.clouddn.com/modify_sys_path_4.png"></p><hr><p style="padding: 0px 5px">6. 验证配置是否正确，运行 “java -version” 命令查询jdk版本号，运行 “javac -version” 查看java编译器版本，运行 “jps” 查询当前运行的java程序<br><img style="max-width: 100%" src="http://okbn8yrzu.bkt.clouddn.com/check_java_version.png"><br>如果提示 “不是内部或外部命令，也不是可运行的程序或批处理文件。” 说明安装或环境变量配置有误<br><span style="font-size: smaller;color: gray">注意：修改完环境变量之后要重新打开命令行，否则可能会导致运行指令失败</span></p></div><div style="width: 100%;border: 1px #ccc solid;text-decoration: none;list-style: none;display: none;" class = "content-label"><h4>在Linux系统上安装jdk</h4><hr></div><div style="width: 100%;border: 1px #ccc solid;text-decoration: none;list-style: none;display: none;" class = "content-label"><h4>在苹果电脑上安装jdk</h4><hr></div></div>
<script>clickTabel(0);function clickTabel(num){var cls = document.getElementsByClassName("content-label");var tabs = document.getElementsByClassName("tab");for(var i=0;i<cls.length;i++){if(i == num){cls[i].style.display='block';}else{cls[i].style.display = 'none';}}; for(var i = 0;i<tabs.length;i++){if(i == num){tabs[i].style.borderColor='#4b4';tabs[i].style.backgroundColor='#5c5';}else{tabs[i].style.borderColor='#ccc';	tabs[i].style.backgroundColor='white';}}}function tabHover(dd){	dd.style.fontWeight='bold';}function tabHoverOut(dd){dd.style.fontWeight='normal';}</script>



### Java 开发工具

#### IntelliJ IDEA

> 官网地址：http://www.jetbrains.com/idea/

推荐指数：5星

非常好用的开发工具，功能完善，插件众多，界面美观，受众多java开发人员喜爱。



#### Eclipse

> 官网地址：http://www.eclipse.org/

推荐指数：4星半

老牌IDE，开源，插件多，功能齐全，java开发工具第二大阵营。



#### MyEclipse

> 官网地址：https://www.genuitec.com/products/myeclipse/
>
> 中文官网：http://www.myeclipsecn.com/

推荐指数：4星

对Eclipse进行优化，增加了很多实用的功能，实用方便，但是需要购买。



#### NetBeans

> 官网地址：https://netbeans.org/

推荐指数：3星





#### JBuilder

> 官网地址：http://edn.embarcadero.com/jbuilder

推荐指数：2星





#### JCreator

> 官网地址：http://www.jcreator.com/

推荐指数：2星



#### 文本编辑器

理论上来说，只要是能编辑文本的工具都可以写java代码，像Windows中的文本编辑器、notepad++、sublime等等，但这种只适合在学习时写一些小的代码片段，不适合开发项目。





