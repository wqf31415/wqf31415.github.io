---
title: vim 学习笔记
date: 2019-06-13 15:35:22
tags:
- vim
- 工具
categories:
- 工具
---

### 概述
这篇文章介绍了文本编辑器 vim 的用法, 以及一些实用插件。


### vim 是个啥?

Vim 是一个开源的、高度可配置的文本编辑器, 能够高效的创建、修改多种类型文本。在多数 UNIX 系统和 Apple OS X 中集成了 vi。vi 是 vim 的子集, vim 具有 vi 的所有功能, 且拥有更多的实用特性。
> 官网: <https://www.vim.org/> 
> Github: <https://github.com/vim/vim> 

![](http://blog-images.qiniu.wqf31415.xyz/vim_logo.png "vim")

<!-- more -->

### 为啥要用 vim ?

- vim 是一个强大而高效的文本编辑工具, 具有很多实用特性, 如: 能够多级撤销, 具有语法高亮, 记录命令历史, 能够检查拼写, 文件名补全, 文章块操作。

- vim 是 linux 系统中常用的文本编辑器, 在运维 linux 服务器时经常使用, 比如用来修改配置文件。

- vim 是一款开源软件, 可高度自定义, 可以自己开发功能。而且有很多好用的开源插件, 功能丰富。

- 装逼。



### 安装 vim

#### Windows
在 Windows 系统中安装 vim 非常简单, 只有三步: 下载、安装、使用。

- 下载安装程序, 地址： <https://www.vim.org/download.php> 

- 执行安装程序
  安装时建议勾选 `Create .bat files for command line use` , 这样安装完成后可以在 Windows 命令行中直接使用 vim
  ![](http://blog-images.qiniu.wqf31415.xyz/vim_install_on_win.png) 
  
- 打开 vim 
  安装完成后, 可以在命令行中使用, 也可以使用 GUI 版, 使用 `gvim` 即可打开, 如下图: 
  ![](http://blog-images.qiniu.wqf31415.xyz/vim_on_win.png)
  
> 此外, 在 Windows 中安装 git 后, 在 gitbash 中也可以使用 vim 。

#### Linux
使用 linux 的安装包管理工具安装, 如:

```bash
sudo apt install vim
```

#### Apple OS X

```bash
 brew install vim
```

#### 自己编译
vim 的源码在 github 上, 可以自行克隆源码进行编译, 这样可以使用到最新开发的版本。大致的流程如下:

```bash
git clone https://github.com/vim/vim.git

cd vim

cd src

make distclean  # if you build Vim before

make

sudo make install
```


### 基础操作

以下操作内容全是在命令行中进行，在 windows 的 vim GUI 中，图形界面提供了一些便捷的操作按钮，也可以使用按键指令完成操作。

#### 进入与退出
进入终端(或命令行)，执行命令 `vim` 即可进入 vim , 如下图所示，左边是 Windows powershell ，右边是 gitbash 进入 vim 的初始界面。
![](http://blog-images.qiniu.wqf31415.xyz/vim_start.png ) 

正如初始界面中提示的，我们可以输入命令查看帮助、保存或退出，输入命令后按 <kbd>回车</kbd> 执行：
|指令|作用|
|:----|:----|
|`:help iccf`  | 查看说明|
|`:q`  | **退出(Quit)** |
|`:help`  | 查看在线帮助|
|`:help version8`  | 查看版本信息|


#### 编辑与保存

在进入 vim 后，我们首先进入的是 <span style="background:red;color:white"> normal 模式 </span> ，需要按小写字母 <kbd>a</kbd> 、 <kbd>i</kbd> 、<kbd>o</kbd> 或大写字母 <kbd>A</kbd> 、 <kbd>I</kbd> 、<kbd>O</kbd> 键进入 <span style="background:red;color:white"> insert 模式 </span> ，这样就可以正常编辑文本，修改与输入内容了，与常规文本编辑器相同，可以用键盘上的上下左右键移动光标。按 <kbd>Esc</kbd> 键回到 normal 模式。

![](http://blog-images.qiniu.wqf31415.xyz/vim_insert_mode.png) 

在插入模式中可以使用键盘上下左右键移动光标，编辑内容，使用退格键或 Delete 键删除内容。编辑完成后，按 <kbd>Esc</kbd> 键回到 normal 模式，输入 `:wq` <kbd>回车</kbd> 保存文件，也可以输入 `:wq` <kbd>回车</kbd> 保存并退出。 

| 指令  | 作用                                                         |
| ----- | ------------------------------------------------------------ |
| `a`   | **追加(Append)** , 在当前光标后面添加内容                    |
| `A`   | 在行尾追加内容，光标自动跳到行尾                             |
| `i`   | **插入(Insert)** , 在当前光标前添加内容                      |
| `I`   | 在行首添加内容                                               |
| `o`   | 在当前行下发添加空行(open a line below)                      |
| `O`   | 在当前行上方添加空行                                         |
| `:W`  | 写入文件(Written) ，即保存，如果是编辑一个新文件，可以在后面指定文件名，如 `:w test.txt` |
| `:wq` | 保存并退出                                                   |



#### 光标移动

vim 在 normal 模式下可以使用键盘上下左右键移动光标，也可以使用 <kbd>h</kbd> 、 <kbd>j</kbd> 、 <kbd>k</kbd> 、 <kbd>l</kbd> 来移动光标。在 insert 模式下使用 上下左右 键移动光标。

| 命令              | 作用                                                         |
| ----------------- | ------------------------------------------------------------ |
| h                 | 左移                                                         |
| j                 | 下移                                                         |
| k                 | 上移                                                         |
| l                 | 右移                                                         |
| `^` 或 `0` 或`g0` | 移动到行首                                                   |
| `$`               | 移动到行尾                                                   |
| `gg`              | 移到文档头                                                   |
| `G`               | 移动到文档尾                                                 |
| gi                | 快速跳转到上次编辑的地方                                     |
| `w` 或 `W`        | 移动到下个单词开头，`w` 是以非空白符分割的单词，`W` 是以空白符分割的单词 |
| `e` 或 `E`        | 移动到下个单词结尾                                           |
| `b` 或 `B`        | 移动到上一个单词开头                                         |
| `f{char}`         | 移动到 char 字符                                             |
| `t{char}`         | 移动到 char 字符前                                           |

Normal 模式下的快捷键：

| 快捷键                         | 功能           |
| ------------------------------ | -------------- |
| <kbd>Ctrl</kbd> + <kbd>h</kbd> | 删除上一个字符 |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> | 删除上一个单词 |
| <kbd>Ctrl</kbd> + <kbd>u</kbd> | 删除整行       |




#### 复制与粘贴

在 vim 中的复制与粘贴不是我们熟悉 Ctrl + C 与 Ctrl + V ，而是 <kbd>y</kbd> 和 <kbd>p</kbd> 。

| 命令 | 作用                 |
| ---- | -------------------- |
| `y`  | 复制                 |
| `p`  | 粘贴                 |
| `d`  | 剪切                 |
| `v`  | 进入可视(visual)模式 |



#### 检索与替换



### 进阶操作

#### 分屏

| 命令  | 作用                     |
| ----- | ------------------------ |
| `sp`  | 分屏(split)              |
| `:vs` | 垂直分屏(vertical split) |
|       |                          |
|       |                          |



### 高级操作



### 插件


### 参考资料
- [Vim from GitHub : vim online](https://www.vim.org/git.php) 
- [How to install Vim Text Editor on Windows 10/8/7](https://www.thewindowsclub.com/install-vim-text-editor-on-windows) 


### 小结


