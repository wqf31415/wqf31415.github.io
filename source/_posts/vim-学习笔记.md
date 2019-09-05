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
- <del> 看起来很高深，可以用来装逼。</del>



### 安装  vim 分几步？

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
Linux 系统下安装 vim 只需要 1 步，使用 linux 的安装包管理工具安装, 如:

```bash
sudo apt install vim
```

#### Apple OS X

在 mac 下安装 vim 也只需要 1 步：

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

划重点：在 vim 中存在 5 种编辑模式，分别是：正常模式(normal)、插入模式(insert)、命令模式(command)、可视模式(visual)、替换模式(replace)。

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



#### 光标移动（重点）

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

```bath
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



#### 修改 vim 主题配色

vim 提供了多种内置主题配色方案，网络中也有很多优秀的第三方配色主题可选。

| 命令                                          | 作用                             |
| --------------------------------------------- | -------------------------------- |
| `:colorscheme`                                | 显示当前主题颜色，默认为 default |
| `:colorscheme` <kbd>Ctrl</kbd> + <kbd>d</kbd> | 显示所有可选配色                 |
| `:colorscheme {name}`                         | 使用指定名称为 {name} 的配色主题 |

其他主题

> vim-hybird: https://github.com/flazz/vim-colorschemes
>
> solarized: https://github.com/altercation/solarized
>
> gruvbox: https://github.com/morhetz/gruvbox

安装方法：

```bash
mkdir ~/.vim
git clone https://github.com/flazz/vim-colorschemes.git ~/.vim
```

> 注意，以上的安装方法将下载很多配色主题，如果只需要部分，可以只将需要的 `.vim` 文件拷贝到 `~/.vim/colors` 目录下。如果使用了 vim 插件管理器，也可以直接使用插件管理器安装，如后面提到的 vim-plug 。

#### vim 配置

在 vim 的 normal 模式下，我们可以执行命令来临时设置 vim，如 `:set nu` 设置显示行号，`:syntax on` 开启代码高亮，`:colorscheme default` 使用默认主题配色等等。这种配置方式在关闭 vim 后就失效了，我们可以将配置项写到 `~/.vimrc` 文件中，实现持久化配置。

> windows 系统 (Win 10) 使用 windows shell ，`cd ~` 进入根目录，如管理员的根目录在 `C:\Users\Administrator` ，创建 `.vimrc` 或 `_vimrc` 文件。
>
> 在任意操作系统中查找 vimrc 文件的位置，只需要打开 vim 执行命令 `:echo $MYVIMRC` ，即可打印出当前操作系统 vimrc 文件的位置。

我们可以将 vim 配置命令写到 `.vimrc` 文件中，实现持久化配置，需要注意的是，配置命令写到配置文件时，不需要再加 `:` 了，vim 会将所有配置解析为命令。如 设置显示行号 `set nu` 。配置文件中每一行为一个配置命令，使用 `"` 添加注释。

在 `.vimrc` 文件中除了可以添加常用配置项外，还可以添加快捷键映射，以及自定义的 vimscript 函数和插件配置。

下面是一份示例配置：

```vimrc
" 常用配置
" 设置行号
set nu

" 主题配色
colorscheme hybrid

 " 按 F2 进入粘贴模式
set pastetoggle=<F2>

" 高亮搜索
set hlsearch

" 设置折叠方式
set foldmethod=indent

" vim 映射
" 设置 leader
let mapleader=','
let g:mapleader=','

" 使用 jj 进入normal 模式，`^ 用于退出插入模式时保持光标位置，可以在 vim 中使用 :help `^ 查看帮助信息
inoremap jj <Esc>`^

" 使用 leader+w 直接保存(插入模式)
inoremap <leader>w <Esc>:w<cr>

" 使用 leader+w 直接保存(正入模式)
noremap <leader>w :w<cr>
 
" 切换 buffer
nnoremap <silent> [b :bprevious<cr>
nnoremap <silent> [n :bnext<cr>

" 使用 Ctrl+h/j/k/l 切换窗口
noremap <C-h> <C-w>h
noremap <C-j> <C-w>j
noremap <C-k> <C-w>k
noremap <C-l> <C-w>l

```

> 在 vim 中修改完 vimrc 文件后，可以执行 `:source ~/.vimrc` 命令使其立即生效。

**vim 的映射**

vim 中的映射有点复杂，源于 vim 有多种模式，每种模式都可以设置不同的映射规则。

**设置 leader 键** `let mapleader=','` ，常用的 leader 键是空格或逗号，使用 `inoremap <leader>w <Esc>:w<cr>` 在插入模式下，输入 `,w` 即可直接保存修改内容。

**基本映射** ，指在 normal 模式下的映射，使用 `map` 就可以实现映射。如 `:map - x` 即可将 `-` 映射为 `x` ，按 `-` 完成删除字符的功能。如 `:map <space> viw` 可以按空格键选择光标处的单词。如 `:map <c-d> dd` 就可以使用 <kbd>Ctrl</kbd> + <kbd>d</kbd> 执行 dd 命令删除一行。

> 使用 `:unmap` 来取消映射，如可以使用 `:unmap -` 取消 `-` 的映射规则。

**不同模式下的映射** ，分别使用 nmap/vmap/imap 定义只在 normal/visual/insert 模式下的映射，如 `:vmap \ U` 把在 visual 模式下选择的文本转为大写(U/u 转换大小写)。

**递归映射与非递归映射**，递归映射会将映射层层解析，直到解析到最终的命令，这种映射方式可能会导致映射与插件中的映射冲突，使得冲突的映射有一个失效，所以一般 **建议任何时候都应该使用非递归映射** 。

使用 nnoremap/vnoremap/inoremap 来定义在 normal/visual/insert 模式下的非递归映射。`nore` 意为 `not recursive，非递归的。

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

> 例如我们想给文档中每一行开头和结尾都添加一个引号 `"` ，可以如下操作：
>
> 1. 打开文档: `vim test.txt` 
> 2. 将光标移动到开头: `gg`
> 3. 开始录制宏: `qa`
> 4. 将光标移动到行首: `^`
> 5. 插入引号后回到 normal 模式: `i"` <kbd>Esc</kbd>
> 6. 将光标移动到行尾: `$`
> 7. 添加引号后回到 normal 模式: `a"` <kbd>Esc</kbd>
> 8. 将光标移动到下一行: `j`
> 9. 结束宏录制: `q`
> 10. 回放宏: `@a` ，或执行 100 次: `100@a` 

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



#### 插件

vim 插件是使用 vimscript 或其他语言编写的 vim 功能扩展，github 中由很多开源的 vim 插件，这些插件大大扩充了 vim 的功能。

##### 安装方式

- 原始方式：拷贝插件代码到 vim 路径下
- 使用插件管理工具：如 vim-plug，Vundle，Pathogen，Dein.Vim，volt 等。综合性能、易用性、文档等方便，推荐使用 **vim-plug**  。

##### vim-plug

> github: <https://github.com/junegunn/vim-plug>

安装方式参考 vim-plug 的 github 仓库说明。如 unix 中使用的 vim，执行命令：

```bash
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```

配置 vimrc ，编辑 vimrc 文件，添加如下配置：

```vimrc
" 指定插件安装的路径
" 要注意避免使用 vim 标准路径名，如 'plugin'
call plug#begin('~/.vim/plugged')

" 插件列表，将要安装的插件添加到这里
" 可以使用插件的简单引用, 如 https://github.com/mhinz/vim-startify
Plug 'mhinz/vim-startify'

" 也可以使用完整的 git 地址，如
" Plug 'https://github.com/mhinz/vim-startify.git'

" 多个插件可以写到一行，使用 | 分隔
" Plug 'xxx/xxx' | Plug 'yyy/yyy'

" 还可以指定使用的 git 分支、tag 版本等信息，具体参考官方文档

" 初始化插件系统
call plug#end()
```

使用 vim-plug 安装插件：

1. 在配置文件中添加了需要的插件，在 `call plug#begin('~/.vim/plugged')` 和 `call plug#end()`  之间增加插件的名称，如安装 vim-startify 插件，添加 `Plug 'mhinz/vim-startify'`
2. 重启 vim ，或者使用 source 重新加载一下 vimrc 文件 `:source ~/.vimrc` 
3. 在 vim 中执行命令 `:PlugInstall` ，之后 vim-plug 就会自动下载插件并安装好。

  重新打开 vim 发现安装的 vim-startify 插件已经生效：![](http://blog-images.qiniu.wqf31415.xyz/vim_plug_startify.png "vim-startify")



##### 查找 vim 插件

- 直接到 GitHub 上找，很多插件都托管在 GitHub 上了。
- Vim Awesome 上汇总了各种类型的vim插件： <https://vimawesome.com/> 

##### 插件推荐

- 修改启动界面: <https://github.com/mhinz/vim-startify> 

- 状态栏美化: <https://github.com/vim-airline/vim-airline> 

  ![](http://blog-images.qiniu.wqf31415.xyz/vim_plug_airline.png "vim-airline") 

- 增加代码缩进线条: https://github.com/Yggdroot/indentLine

- 文件目录树: https://github.com/scrooloose/nerdtree

  使用 `:NERDTreeToggle` 命令打开文件树，可以添加映射到配置项： `map <C-n> :NERDTreeToggle<CR>` 使用快捷键 <kbd>ctrl</kbd> + <kbd>n</kbd> 快速打开/关闭文件目录树。

  启动 vim 时打开文件树: `autocmd vimenter * NERDTree` 

  查找当前文件位置: `nnoremap <leader>v :NERDTreeFind<cr>` 

  ![](http://blog-images.qiniu.wqf31415.xyz/vim_plug_nerdtree.png "nerdtree")

- 模糊搜索: ctrlp.vim，<https://github.com/ctrlpvim/ctrlp.vim> 

- 移动到任意位置: vim-easymotion， 大大增强了 vim 本就强大的移动功能，<https://github.com/easymotion/vim-easymotion> 

- 包裹操作: vim-surround，对于成对操作的内容很有帮助，如编辑 html 文档， <https://github.com/tpope/vim-surround> 

- 在项目文件中模糊搜索: fzf.vim， <https://github.com/junegunn/fzf.vim> 

- 批量搜索替换: far.vim，<https://github.com/brooth/far.vim> 

- golang 插件，vim-go，代码补全、重构、自动格式化、自动导入等: <https://github.com/fatih/vim-go> 

- python 插件: python-mode， 使用 vim 开发 python， <https://github.com/python-mode/python-mode> 

- 代码大纲: tagbar，方便快捷浏览代码，快速跳转， <https://github.com/majutsushi/tagbar> 

- 高亮你感兴趣的词: vim-interestingwords， <https://github.com/lfv89/vim-interestingwords> 

- 异步补全插件: deoplete.nvim，支持异步补全，防止插件运行时导致 vim 操作卡顿， <https://github.com/Shougo/deoplete.nvim> 

- 格式化插件: vim-autoformat 和 Neoformat，需要安装对应语言的格式化库，如 python 格式化的 autopep8，js 的 prettier 等

- 静态检查: neomake 和 ale 是两种常用的静态检查插件，需要安装对应语言的静态检查库，如 eslint、pylint、golint 等

- 注释插件: vim-commentary ，可以根据文件类型不同使用不同的注释风格，使用命令 gc 注释和取消注释

- vim 中使用 git : Fugitive，直接在 vim 中执行命令调用 git，如 Gedit、Gdiff、Gblame、Gcommit 等

- 在 vim 中显示文件变动: vim-gitgutter ，修改文件后可以显示当前文件的变动

### 成神

#### vimscript

vim 脚本可以实现功能强大的 vim 插件，vimscript 是一种简单的脚本语言，可以实现更多 vim 的控制，开发自己的插件。

> 推荐学习资料: 《笨方法学 Vimscript》
>
> GitHub: <https://github.com/sjl/learnvimscriptthehardway> 
>
> 中文: <http://learnvimscriptthehardway.onefloweroneworld.com/> 

### 其他

#### Tmux

Tmux 是一个强大的终端复用工具，通过 brew (mac) 或 apt-get (ubantu) 命令安装，可以复用终端、分屏、托管进程等。

#### Neovim

Neovim 是一个新的 vim 版本，支持异步特性，具有更加丰富的特性和扩展，开发更活跃，而且可以嵌入到很多 GUI 中，界面更加美观。

### 参考资料

- [Vim from GitHub : vim online](https://www.vim.org/git.php) 
- [How to install Vim Text Editor on Windows 10/8/7](https://www.thewindowsclub.com/install-vim-text-editor-on-windows) 
- [Modes in Vim | freeCodeCamp Guide](https://guide.freecodecamp.org/vim/modes/) 
- [vim全局替换命令 - lixixi - CSDN博客](https://blog.csdn.net/u013043762/article/details/80461666) 
- [强悍的 vim —— g s 替换区别 - Zhang's Wikipedia - CSDN博客](https://blog.csdn.net/lanchunhui/article/details/51588586) 


### 小结

这篇文章总体上介绍了 vim 编辑器的用法，包含的面比较广，但并不是很深入，属于走马观花式的概览，目的是希望能够对 vim 有个概念，知道它能做什么，有什么用法，激发对 vim 的兴趣就最好了。
