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

### vim 五大模式

在 vim 中存在 5 中编辑模式，分别是：正常模式(normal)、插入模式(insert)、命令模式(command)、可视模式(visual)、替换模式(replace)。

进入 vim 时处于正常模式，是 vim 核心模式，可以从正常模式切换到其他模式，并通过按 <kbd>Esc</kbd> 或 <kbd>Ctrl</kbd> + <kbd>[</kbd> 键从其他模式返回正常模式。
正常模式下，按 <kbd>a</kbd>、<kbd>A</kbd>、<kbd>i</kbd>、<kbd>I</kbd>、<kbd>o</kbd>、<kbd>O</kbd> 进入插入模式，可编辑文档内容；
正常模式下，输入 `:` 进入命令模式，在 `:` 后加上命令即可执行命令，如 `:wq` 保存修改并退出 vim， `:set nu` 设置 vim 显示行号；
正常模式下，按 <kbd>v</kbd>、<kbd>V</kbd>、<kbd>Ctrl</kbd> + <kbd>v</kbd> 可进入可视模式，用于文档内容选择；
正常模式下，按 <kbd>r</kbd> 键进入替换模式，输入内容将会替换光标所在位置的字符。

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
|`:q!` | 强制退出，不保存修改内容 |
|`:qa` | 退出所有窗口 |
|`:qa!` | 强制退出所有窗口 |
|`:help`  | 查看在线帮助|
|`:help version8`  | 查看版本信息|


#### 编辑与保存

在进入 vim 后，我们首先进入的是 <span style="background:red;color:white"> normal 模式 </span> ，需要按小写字母 <kbd>a</kbd> 、 <kbd>i</kbd> 、<kbd>o</kbd> 或大写字母 <kbd>A</kbd> 、 <kbd>I</kbd> 、<kbd>O</kbd> 键进入 <span style="background:red;color:white"> insert 模式 </span> ，这样就可以正常编辑文本，修改与输入内容了，与常规文本编辑器相同，可以用键盘上的上下左右键移动光标。按 <kbd>Esc</kbd> 键回到 normal 模式。

![](http://blog-images.qiniu.wqf31415.xyz/vim_insert_mode.png) 

在插入模式中可以使用键盘上下左右键移动光标，编辑内容，使用退格键或 Delete 键删除内容。编辑完成后，按 <kbd>Esc</kbd> 键回到 normal 模式，输入 `:wq` <kbd>回车</kbd> 保存文件，也可以输入 `:wq` <kbd>回车</kbd> 保存并退出。 

| 指令                   | 作用                                                         |
| ---------------------- | ------------------------------------------------------------ |
| `a`                    | **追加(Append)** , 在当前光标后面添加内容                    |
| `A`                    | 在行尾追加内容，光标自动跳到行尾                             |
| `i`                    | **插入(Insert)** , 在当前光标前添加内容                      |
| `I`                    | 在行首添加内容                                               |
| `o`                    | 在当前行下发添加空行(open a line below)                      |
| `O`                    | 在当前行上方添加空行                                         |
| `u`                    | 撤销修改(Undo)                                               |
| `:w`                   | 写入文件(Written) ，即保存，如果是编辑一个新文件，可以在后面指定文件名，如 `:w test.txt` |
| `:wq`  或 `:x` 或 `ZZ` | 保存并退出                                                   |
| `:wqa`                 | 保存并退出所有窗口                                           |



#### 快捷修改

在 normal 模式下可以快速修改内容

| 命令 | 作用                                                         |
| ---- | ------------------------------------------------------------ |
| `s`  | 替换(Substitute)，删除当前字符并进入插入模式                 |
| `c`  | 修改(Change)，配合文本对象进行快速修改并进入插入模式，如 ciw 删除光标处的单词并进入插入模式 |
| `r`  | 替换(Respace)，输入新字符替换当前字符                        |



#### 光标移动

vim 在 normal 模式下，提供了很多的命令来移动光标，用来快速定位。可以使用键盘上下左右键移动光标，也可以使用 <kbd>h</kbd> 、 <kbd>j</kbd> 、 <kbd>k</kbd> 、 <kbd>l</kbd> 来移动光标，在 insert 模式下使用 上下左右 键移动光标。

| 命令                           | 作用                                                         |
| ------------------------------ | ------------------------------------------------------------ |
| `h`                            | 左移一个字符                                                 |
| `{n}h`                         | 左移 n 个字符                                                |
| `j`                            | 下移一行                                                     |
| `{n}j`                         | 下移 n 行                                                    |
| `k`                            | 上移一行                                                     |
| `{n}k`                         | 上移 n 行                                                    |
| `l`                            | 右移一个字符                                                 |
| `{n}l`                         | 右移 n 个字符                                                |
| `^` 或 `0` 或`g0`              | 移动到行首                                                   |
| `$`                            | 移动到行尾                                                   |
| `gg`                           | 移到文档头                                                   |
| `G`                            | 移动到文档尾                                                 |
| `:{n}` 或 `{n}G`               | 跳转到第 n 行                                                |
| `ge`                           | 跳转到上一个单词开头                                         |
| `gi`                           | 快速跳转到上次编辑的地方                                     |
| `w` 或 `W`                     | 移动到下个单词开头，`w` 是以非空白符分割的单词，`W` 是以空白符分割的单词 |
| `e` 或 `E`                     | 移动到下个单词结尾                                           |
| `b` 或 `B`                     | 移动到上一个单词开头                                         |
| `f{char}`                      | 移动到当前行下一个 char 字符处                               |
| `F{char}`                      | 移动到当前行上一个 char 字符处                               |
| `t{char}`                      | 移动到当前行下一个 char 字符前                               |
| `T{char}`                      | 移动到当前行上一个 char 字符前                               |
| `{`                            | 移动到上一段                                                 |
| `}`                            | 移动到下一段                                                 |
| `(`                            | 移动到上一个句子                                             |
| `)`                            | 移动到下一个句子                                             |
| <kbd>Ctrl</kbd> + <kbd>f</kbd> | 向下翻页(Forward)                                            |
| <kbd>Ctrl</kbd> + <kbd>b</kbd> | 向上翻页(Backward)                                           |
| <kbd>Ctrl</kbd> + <kbd>d</kbd> | 向下翻半页(Down)                                             |
| <kbd>Ctrl</kbd> + <kbd>u</kbd> | 向上翻半页(Up)                                               |
| <kbd>Ctrl</kbd> + <kbd>o</kbd> | 快速返回                                                     |
| `H` 、 `M` 、 `L`              | 跳转到屏幕开头(Head)、中间(Middle)和结尾(Lower)              |
| `zz`                           | 把屏幕置为中间                                               |

> 注意: 在当前行使用 f、F、t、T 查找字符时，可以使用 <kbd>;</kbd> 跳转到下一个匹配处，使用 <kbd>,</kbd> 跳转到上一个匹配处。

Insert 模式下的快捷键：

| 快捷键                         | 功能           |
| ------------------------------ | -------------- |
| <kbd>Ctrl</kbd> + <kbd>h</kbd> | 删除上一个字符 |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> | 删除上一个单词 |
| <kbd>Ctrl</kbd> + <kbd>u</kbd> | 删除整行       |




#### 复制与粘贴

在 vim 的 normal 中的复制与粘贴不是我们熟悉 Ctrl + C 与 Ctrl + V ，而是 <kbd>y</kbd> 和 <kbd>p</kbd> ，而且无法使用鼠标来选择，需要先在 normal 模式中按 <kbd>v</kbd> 键进入 visual 模式，通过按键移动光标来选择需要复制的内容。在 insert 模式中可以使用 <kbd>Ctrl</kbd> + <kbd>C</kbd> 和 <kbd>Ctrl</kbd> + <kbd>V</kbd> 来复制与粘贴。

> 在 vim 中粘贴代码时，如果设置了自动缩进 (autoindent)，粘贴内容的缩进会出错，需要在粘贴前执行 `:set paste` 命令 ，完成粘贴后使用 `:set nopaste` 命令设置回来。

| 命令                           | 作用                                                         |
| ------------------------------ | ------------------------------------------------------------ |
| `y`                            | 复制(yank)，The text is pulled (yanked) into the clipboard for later use |
| `yy` 或 `Y`                    | 复制整行                                                     |
| `p`                            | 粘贴(paste)，粘贴到光标位置后                                |
| `P`                            | 粘贴到光标位置前                                             |
| `d`                            | 剪切(delete)                                                 |
| `dd`                           | 剪切整行                                                     |
| `daw`                          | 删除光标处的单词                                             |
| `dt{char}`                     | 从当前位置删除到指定 char 处                                 |
| `D`                            | 剪切光标位置到行尾的内容                                     |
| `v`                            | 进入可视(visual)模式                                         |
| `V`                            | 进入行级可视模式，可以按行进行选择                           |
| <kbd>Ctrl</kbd> + <kbd>v</kbd> | 进入块级可视模式，可以纵向的按块选择                         |

> 在使用 `y` 或 `d` 来复制或剪切内容时，可以在后面加上光标移动命令，如 `y10k` 向上复制 10 行，`d2j` 向下删除 2 行。

#### 检索与替换

| 命令                                  | 功能                     |
| ------------------------------------- | ------------------------ |
| `/text` <kbd>回车</kbd>               | 查找下一个 text          |
| `?text` <kbd>回车</kbd>               | 查找上一个 text          |
| `*`                                   | 向下查找光标所在处的单词 |
| `#`                                   | 向上查找光标所在处的单词 |
| `:substitute/abc/def` 或 `:s/abc/def` | 将下一个 abc 替换成 def  |

> 成功查找到目标内容后，按 <kbd>n</kbd> 跳转到下一个匹配处，按 <kbd>N</kbd> 跳转到上一个匹配处。

vim 替换命令的格式：
```
:[range]s/[pattern]/[string]/[option][count]
```

- **range**  作用范围，可以用数字表示行，如 `:2s/abc/def` 表示作用于第二行，`:2,4s/abc/def` 表示作用于第二到四行；可以用 `$` 表示最后一行，用 `%` 或 `1,` 表示所有行，使用 `.,` 表示从当前行到行尾。
- **pattern**  内容检索模式，特殊字符用 `\` 转义，可以使用正则表达式。
- **string**  替换成的内容，特殊字符用 `\` 转义。
- **option**  替换时的选项，`c` 表示替换时需要确认，`g` 表示替换行中所有命中内容，`i` 表示忽略大小写，`n` 表示只统计匹配次数而不进行替换，可以用来查询匹配次数。不添加 option 项时，只会对每行第一个匹配进行替换。
- **count**  替换行数，从 range 中指定的最后一条开始计算，如果没有指定 range 则从当前行开始计算，如 `:2,4s/abc/def/g2` 将从第四行开始计算的两行(即第 4，5 行)中的 abc 替换成 def。

vim 替换命令示例：

`:%s/^/  /`  在所有行前增加两个空格

#### 文本对象操作

在 Vim 中可以把单词 、句子 、段落当作一个文本对象来操作，如 `diw` 可以删除光标处的一个单词。

```
[number]<command>[text object]
```

- number 表示操作次数
- command 是操作命令，如 块选 v、删除 d、修改 c、复制 y
- text object 是要操作的文本对象，如单词 w、句子 s、段落 p

`iw` 表示 inner word，将选中光标处的单词，如 `viw` 将选中光标处的单词，`diw` 将删除光标处的单词，`yiw` 将复制光标处的单词

`aw` 表示 a word，将选中光标处的单词和单词后的空格，如 `vaw` 将选中光标处的单词和单词后的空格，`daw` 将删除光标处的单词和单词后的空格，`yaw` 将复制光标处的单词和单词后的空格

`is` 、`as` 、`ip` 、`ap` 功能同上。

### 进阶操作

#### 缓冲区

Vim 打开一个文件后会加载文件内容到缓冲区，之后修改的内容都是针对内存中的缓冲区，并不会直接保存到文件，直到我们执行 `:w` 的时候才会把修改内容写入到文件里。

| 命令             | 作用                                                         |
| ---------------- | ------------------------------------------------------------ |
| `:e newfile.txt` | 编辑新文件，会新增一个缓冲区                                 |
| `:ls`            | 列举当前缓冲区                                               |
| `:b n`           | 跳转到第 n 个缓冲区                                          |
| `:bpre`          | 跳转到上一个缓冲区                                           |
| `:bnext`         | 跳转到下一个缓冲区                                           |
| `:bfirst`        | 跳转到第一个缓冲区                                           |
| `:blast`         | 跳转到最后一个缓冲区                                         |
| `:b buffer_name` | 跳转到指定名字的缓冲区，缓冲区名可以使用 <kbd>Tab</kbd> 键补全 |



#### 窗口

Vim 一个缓冲区可以分割成多个窗口，每个窗口可以打开不同的缓冲区。

| 命令               | 作用                         |
| ------------------ | ---------------------------- |
| `:sp` 或 `:split`  | 水平分屏(split)              |
| `:vs` 或 `:vsplit` | 垂直分屏(vertical split)     |
| `:5sp`             | 划分一个 5 行的水平窗口      |
| `:5vs`             | 划分一个 5 列的垂直窗口      |
| `:sp test.txt`     | 水平分屏并编辑 test.txt 文件 |
| `:vs test.txt`     | 垂直分屏并编辑 test.txt 文件 |

在多个窗口中移动时，可以在正常模式下先按 <kbd>Ctrl</kbd> + <kbd>w</kbd> 键，然后按 <kbd>k</kbd>、<kbd>j</kbd>、<kbd>h</kbd>、<kbd>l</kbd> 键或 <kbd>↑</kbd>、<kbd>↓</kbd>、<kbd>←</kbd>、<kbd>→</kbd> 左右键，在上下左右窗口间切换。

窗口操作快捷键：

> 以下快捷键需要先按下 <kbd>Ctrl</kbd> + <kbd>w</kbd> ，松开后，再次按下 `;` 后指定的按键。

| 快捷键                                            | 功能                      |
| ------------------------------------------------- | ------------------------- |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>n</kbd>     | 新建空窗口                |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>s</kbd>     | 水平切分窗口              |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>v</kbd>     | 垂直切分窗口              |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>w</kbd>     | 在多个窗口中切换          |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>=</kbd>     | 等分各窗口大小            |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>+</kbd>     | 加大当前窗口              |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>-</kbd>     | 缩小当前窗口              |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>_</kbd>     | 最大化活动窗口的高度      |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>\|</kbd>    | 最大化活动窗口宽度        |
| [N]<kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>_</kbd>  | 把活动窗口的高度设为[N]行 |
| [N]<kbd>Ctrl</kbd> + <kbd>w</kbd> ；<kbd>\|</kbd> | 把活动窗口的宽度设为[N]行 |

#### 标签页

标签(Tab)是可以容纳一系列窗口的容器，可以一个 Tab 全用来编辑 html 文件，另一个 Tab 用来编辑 txt 文件。

> 在 normal 模式下可以使用 `:h tabpage` 查看标签页帮助信息。

| 命令                                           | 作用                                 |
| ---------------------------------------------- | ------------------------------------ |
| `:tabn`                                        | 创建一个新的标签页                   |
| `:tabe[dit] {filename}`                        | 在新标签页中打开 {filename}          |
| <kbd>Ctrl</kbd> + <kbd>w</kbd> ； <kbd>T</kbd> | 把当前窗口移到一个新的标签页         |
| `:tabs`                                        | 列出所有标签页                       |
| `:tabc[lose]`                                  | 关闭当前标签页及其中的所有窗口       |
| `:tabo[nly]`                                   | 只保留活动标签页，关闭所有其他标签页 |
| `:tabn[ext]`                                   | 切换到下一个标签页                   |
| `:tabn[ext] {N}`                               | 切换到编号为 {N} 的标签页            |
| `:tabp[revious]`                               | 切换到上一个标签页                   |



### 高级操作

#### 寄存器

在 vim 中删除、复制的内容都会被存入寄存器，可以使用 `p` 将寄存器中的内容粘贴到文档中。默认将内容存入了无名寄存器中，可以使用引号指定使用的寄存器，如复制时 `"ayiw` 及可以将光标处的单词复制到寄存器 a 中，同样的在粘贴时使用 `"ap` 即可将 a 寄存器中的内容粘贴到文档中。

| 命令           | 作用                        |
| -------------- | --------------------------- |
| `"{register}`  | 使用指定的寄存器 {register} |
| `:reg[isters]` | 查看所有寄存器              |
| `:reg {a}`     | 查看 {a} 寄存器             |

可以使用 a-z 对寄存器命名，这些被称为有名寄存器。vim 中还有一些常见的寄存器：

- `""` 无名寄存器
- `"0` 复制专用寄存器，使用 `y` 命令复制文本时，同时会拷贝一份到复制寄存器 0
- `"+` 系统剪贴板，可以将 vim 中内容拷贝到系统剪贴板，或是粘贴系统剪贴板中的内容
- `"%` 为当前文件名的寄存器
- `".` 上次插入的文本
- `"#` 轮换文件名
- `"_` 黑洞寄存器，放进去的东西不会恢复
- `"=` 表达式寄存器，用于计算
- `":` 上次执行的命令
- `"/` 上次查找的模式

#### 宏

宏(macro) 可以看作是一系列命令的集合，可以使用宏录制一系列操作，然后用于回放，宏可以非常方便的把一系列命令用在多行文本上。

在正常模式下，按一下 <kbd>q</kbd> ，然后再按一个字母作为宏名，然后就可以开始录制宏(如 `qa` 录制宏并保存到寄存器 a)，录制完成后回到正常模式，按 <kbd>q</kbd> 结束录制。录制完成后即可使用 `@{register}` ，来执行宏，如 `@a` 执行宏 a。 按 `@@` 执行上一个宏。

#### 自动补全

> 以下命令，有些需要按两次快捷键，先按一次 <kbd>Ctrl</kbd> + <kbd>x</kbd> ，然后再按后面的快捷键。自动补全需要开启文件类型检查，安装插件。

| 命令                                                         | 作用             |
| ------------------------------------------------------------ | ---------------- |
| <kbd>Ctrl</kbd> + <kbd>n</kbd>                               | 普通关键字       |
| <kbd>Ctrl</kbd> + <kbd>x</kbd> ； <kbd>Ctrl</kbd> + <kbd>n</kbd> | 当前缓冲区关键字 |
| <kbd>Ctrl</kbd> + <kbd>x</kbd> ； <kbd>Ctrl</kbd> + <kbd>i</kbd> | 包含文件关键字   |
| <kbd>Ctrl</kbd> + <kbd>x</kbd> ； <kbd>Ctrl</kbd> + <kbd>]</kbd> | 标签文件关键字   |
| <kbd>Ctrl</kbd> + <kbd>x</kbd> ； <kbd>Ctrl</kbd> + <kbd>k</kbd> | 字典查找         |
| <kbd>Ctrl</kbd> + <kbd>x</kbd> ； <kbd>Ctrl</kbd> + <kbd>l</kbd> | 整行补全         |
| <kbd>Ctrl</kbd> + <kbd>x</kbd> ； <kbd>Ctrl</kbd> + <kbd>f</kbd> | 文件名补全       |
| <kbd>Ctrl</kbd> + <kbd>x</kbd> ； <kbd>Ctrl</kbd> + <kbd>o</kbd> | 全能(Omni) 补全  |
| <kbd>Ctrl</kbd> + <kbd>p</kbd>                               | 补全单词         |



### 插件


### 参考资料
- [Vim from GitHub : vim online](https://www.vim.org/git.php) 
- [How to install Vim Text Editor on Windows 10/8/7](https://www.thewindowsclub.com/install-vim-text-editor-on-windows) 
- [Modes in Vim | freeCodeCamp Guide](https://guide.freecodecamp.org/vim/modes/) 
- [vim全局替换命令 - lixixi - CSDN博客](https://blog.csdn.net/u013043762/article/details/80461666) 
- [强悍的 vim —— g s 替换区别 - Zhang's Wikipedia - CSDN博客](https://blog.csdn.net/lanchunhui/article/details/51588586) 


### 小结


