---
title: Linux终端复用神器——Tmux
date: 2021-1-16 17:53:32
tags:
- 工具
- linux
categories:
- 工具
---

### 概述

这篇文章介绍了 linux 或 mac 系统中使用的终端复用工具——Tmux，支持多终端窗口，还支持在后台运行，方便完成一些耗时操作。



### 认识 Tmux

![](http://blog-images.qiniu.wqf31415.xyz/tmux_pane.png)

Tmux （terminal multiplexer），是一个开源的 unix 系统终端复用器，能够在一个窗口中启动一系列终端会话；能够让会话在后台持续运行；在一个会话中可开启多个窗口执行不同命令。

> Tmux：<https://github.com/tmux/tmux> 

<!-- more -->

### 相关概念

- 会话（session）：是指用户与计算机之前开启的一次交互，就像两个人开始一次交谈。我们通过 ssh 远程连接到服务器上时，就开启了一个会话，当这个连接关闭时，这个会话就结束了，下次再次连接上来就是一个新的会话了，如果用上了 tmux ，就可以让会话在后台运行，下次再连上来时就可以进入上次的会话了。
- 窗口（window）：再一个 tmux 会话中，可以开启多个窗口，在同一个页面中进行切换，同时执行不同命令。
- 窗格：在一个窗口中，可以将窗口切分成多块，每一块即为一个窗格。



### 安装 

#### 使用终端安装

Tmux 可以直接使用系统的包管理工具安装：

- Ubuntu 或 Debian：`sudo apt install tmux` 
- CentOS 或 Fedora：`sudo yum install tmux` 
- Mac：`brew install tmux` 



#### 编译安装

Tmux 是一个开源工具，可以从 Github 仓库下载 Tmux 源码，然后自行编译安装。

> Tmux Github: <https://github.com/tmux/tmux> 



### 基本使用 （会话）

#### 进入与退出

打开系统终端或通过 ssh 工具远程连接到服务器，执行如下命令即可进入 tmux，开启一个 tmux 会话。

```bash
tmux 
```

在窗口最下发将显示 session 信息，包含会话名，窗口序号和窗口名。结果如下图所示。

> 未指定窗口名时，默认窗口名为数字，从 0 开始。

![](http://blog-images.qiniu.wqf31415.xyz/tmux.png) 

退出方式，执行 `exit` 命令，或按快捷键 <kbd>Ctrl</kbd> + <kbd>D</kbd> 。



#### 指定 session 名与后台运行

在开启 session 时可以指定 session 名称，这样方便识别。如下命令将启动一个名叫 foo 的会话，启动后查看下方状态信息发现会话名为 `foo` ：

```bash
tmux new -s foo
```

Tmux 支持让当前 session 在后台运行，处于后台时，正在运行的命令不受影响。在 tmux 会话中执行下述命令，也可以让会话在后台运行：

```bash
tmux detach
```

快捷键： <kbd>Ctrl</kbd> + <kbd>B</kbd>  <kbd>d</kbd> 

> 快捷键说明：
>
> 本文中所有快捷键需要在 tmux 会话中使用，需要先按 <kbd>Ctrl</kbd> + <kbd>B</kbd> 进入命令接收模式，然后输入命令，这里按 <kbd>d</kbd> 键即可让会话在后台运行。



#### 查看与进入后台运行的会话

查看运行的 tmux 会话：

```bash
tmux ls
# 或
tmux list-session
```

在会话中可以使用快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>s</kbd> 

执行结果如下：

```bash
$ tmux ls
foo: 1 windows (created Sat Jan 16 16:06:10 2021) [80x23]
```

进入后台运行的 foo 会话：

```bash
tmux attach -t foo
```



#### 切换会话

在 tmux 会话中，执行如下命令即可切换到指定会话：

```bash
tmux switch -t boo
```

切换后，查看下方状态栏中的会话名，看是否切换成功。



#### 杀死会话

```bash
tmux kill-session -t foo
```



#### 重命名会话

```bash
tmux rename-session -t boo new-boo
```

在会话中可使用快捷：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>$</kbd> 



### 使用窗口

#### 创建窗口

```bash
tmux new-window
# 指定窗口名
tmux new-window -n wname
```

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>c</kbd> 

> 注意下方的状态栏，多了两个窗口，编号 1 和编号 2 的窗口，窗口名分表为 `bash` 和 `wname`。其中的 `*` 号表明当前所在的窗口。

![](http://blog-images.qiniu.wqf31415.xyz/tmux_window.png)

#### 切换窗口

```bash
# 按窗口名切换
tmux select-window -t wname

# 按窗口编号切换
tmux select-window -t 1
```

快捷键切换：

- 切换到上一个窗口：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>p</kbd> 
- 切换到下一个窗口：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>n</kbd> 
- 切换到指定编号的窗口：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>窗口编号</kbd> 
- 从列表中选择窗口：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>w</kbd> 



#### 重命名窗口

```bash
tmux rename-window new-name
```

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>,</kbd> 



### 使用窗格

#### 划分窗格

命令：

```bash
# 划分上下两个窗格
tmux split-window

# 划分左右两个窗格
tmux split-window -h
```

快捷键：

- 划分左右两个窗格：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>%</kbd> 
- 划分上下两个窗格：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>"</kbd> 

![](http://blog-images.qiniu.wqf31415.xyz/tmux_pane.png)



#### 光标移动

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>方向键</kbd> ，将光标移动到箭头方向的窗格中。

##### 光标移动到上方窗格

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>;</kbd> 

```bash
tmux select-pane -U
```

##### 光标移动到下方窗格

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>o</kbd> 

```bash
tmux select-pane -D
```

##### 光标移动到左边窗格

```bash
tmux select-pane -L
```

##### 光标移动到右边窗格

```bash
tmux select-pane -R
```



#### 交换窗格位置

> 注意这里的前移和后移，是指与上一个编号的窗格交换位置，和与下一个编号的窗格交换位置，而不是视觉上的上下。

##### 当前窗格前移

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>{</kbd> 

```bash
tmux swap-pane -U
```

##### 当前窗格后移

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>}</kbd> 

```bash
tmux swap-pane -D
```

##### 所有窗格向后移动

最后一个窗格将变成第一个窗格。

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>Alt</kbd> + <kbd>o</kbd> 



##### 所有窗格向前移动

第一个窗格将变成最后一个窗格。

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>Ctrl</kbd> + <kbd>o</kbd> 



#### 查看窗格编号

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>q</kbd> 



#### 关闭窗格

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>x</kbd> 



#### 调整窗格大小

- 按箭头方向调整窗格大小：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>Ctrl</kbd> + <kbd>方向键</kbd> 
- 当前窗格全屏显示或恢复原本大小：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>z</kbd> 



#### 窗格转成窗口

将当前窗格转成一个独立窗口。

快捷键：<kbd>Ctrl</kbd> + <kbd>b</kbd> <kbd>!</kbd> 



### 参考资料

- 十分钟学会 tmux: <https://www.jianshu.com/p/c217318a9380> 
- tmux使用教程: <https://zhuanlan.zhihu.com/p/98384704> 
- Tmux 使用教程: <http://www.ruanyifeng.com/blog/2019/10/tmux.html> 
- tmux 终端复用详解: <https://www.cnblogs.com/wangqiguo/p/8905081.html> 



### 总结

Tmux 是一个非常方便的工具，使用方式有点类似于 vim，这个配合 vim 使用一定很酷。 