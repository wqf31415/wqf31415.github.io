---
title: Windows脚本编写
date: 2021-01-27 11:06:08
tags:
- Windows
- bat
categories:
- 技术
---

### 概述

灵活使用脚本可以完成一些重复性的工作，提高工作效率，这篇文章介绍了 Windows 系统脚本的编写规则和一些常用命令。



### 认识 Windows 脚本

Windows 脚本又被称为批处理脚本，是包含一系列 DOS 命令的文本文件，用于自动执行重复性任务，脚本文件以 `.bat` 或 `.cmd` 为后缀。

> bat 与 cmd 文件的异同：
>
> 他们都是 Windows 脚本，编码方式相同，使用的命令行代码也是共同的。
>
> bat 为 Windows 批处理文件，是 batch 的简写，所有 windows 系统都可以执行，可用命令相对较少。
>
> cmd 为 Windows 脚本文件，cmd 文件只能在 Windows2000 以上的系统才能运行，可用命令更多。

<!-- more -->

### 语法规则

#### 官方文档

本文中用到的和没用到的命令都可以从官方文档中查到，讲解非常全面，而且可以按首字母查询，有问题可以去查阅：

<https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/windows-commands> 



#### 总纲

- 关键字与变量名不区分大小写，例如：`REM` = `rem` = `rEM` ，`%JAVA_HOME%` = `%java_home%` = `%jAva_hOmE%` 
- 按行读取命令，每次处理一行



#### 注释

在 Windows 脚本中以 `REM` 、`::` 注释一行代码。

```powershell
REM 这是注释
:: 这是注释
```

> `RME` 和 `::` 的区别：
>
> 1. 任何以冒号 `:` 开头的字符行，在处理中都被视作标号，而直接忽略其后面的所有内容。
>
>    有效标号：冒号后紧跟一个以字母数字开头的字符串，goto 语句可识别。
>
>    无效标号：冒号后紧跟一个非字母数字的一个特殊符号，goto 无法识别的标号，可以起到注释作用。所以 `::` 常被用做注释，其实 `:+` 也可起注释作用。
>
> 2. 与 `REM` 不同的是，`REM` 行会回显；`::` 后的字符在执行时不会回显，无论是否用 `echo on` 开启命令回显功能，因为命令解释器不认为它是一个有效命令行。

如果想注释多行，可以使用 `GOTO` 的跳转实现，如注释两行内容：

```powershell
GOTO next
echo 要注释的内容
echo 要注释的内容
:next
```



#### @ 关闭单行命令回显

`@` 符号放在命令前将关闭该行命令回显，无论 echo 是否开启回显。



#### 参数

参数是指在执行脚本时，在脚本后以空格符分隔的内容。理论上可支持无限多个参数，但脚本内对前 9 个参数可直接获取，使用 `%number` 方式即可获取执行脚本时指定的参数。如：

- `%0` 为第一个参数，即当前脚本
- `%1` 到 `%9` 为脚本后的第 1 到第 9 个参数
- `%*` 获取从第 1 个开始的所有参数

如创建一个 `hello.bat` 脚本，内容如下：

```powershell
@echo off
echo Current script is: %0
echo First param is: %1
```

使用命令行执行命令 `hello world` ，结果如下：

```
C:\Users\Administrator\Desktop>hello world
Current script is: hello
First param is: world
```

> 注意，如果执行的命令是 `hello.bat world` ，第一个参数值为 `hello.bat` 

##### 参数增强处理

使用 `%` 引用参数时，可使用 `~` 加增强标识，对参数进行扩展增强处理。以第一个参数 `%1` 为例：

| 扩展          | 效果                                                         |
| ------------- | ------------------------------------------------------------ |
| `%~1`         | 清除字符串首尾引号（仅当字符串首有引号或首尾都有引号时生效） |
| `%~a1`        | 扩展到文件属性                                               |
| `%~d1`        | 扩展到一个驱动器号                                           |
| `%~f1`        | 扩展到一个完全合格的驱动器号                                 |
| `%~n1`        | 扩展到一个文件名                                             |
| `%~p1`        | 扩展到一个路径                                               |
| `%~s1`        | 扩展的路径指含有短名                                         |
| `%~t1`        | 扩展到文件的日期/时间                                        |
| `%~x1`        | 扩展到文件扩展名                                             |
| `%~z1`        | 扩展到文件大小                                               |
| `%~$PATH:1`   | 查找列在 PATH 环境变量的目录，并将 `%1` 扩展到找到的第一个完全合格的名称，如果环境变量名未定义，或者没有找到文件，此组合键会扩展到空字符串 |
| `%~dp1`       | 扩展到驱动器号和路径                                         |
| `%~nx1`       | 扩展到文件名和扩展名                                         |
| `%~dp$PATH:1` | 在列在 PATH 环境变量中的目录里查找 `%1` ，并扩展到找到的第一个文件的驱动器和路径 |
| `%~ftza1`     | 若 `%1` 为目录或文件，会转变成 dir 的输出行                  |

> 用法示例：
>
> - `%~dp0` 返回当前脚本所在目录的全路径
> - `%~n0` 返回当前脚本文件名（不含扩展名）
> - `%~nx0` 返回当前脚本文件名（包括扩展名）

#### 变量

- dos 中只能进行整数计算，不能进行浮点数运算。

- 只能精确到 32 位，有效值范围：-2147483648至2147483647

- 十六进制前缀为 `0x` ，八进制前缀为 `0` 。

##### 自定义变量

使用 `set` 关键字定义变量，使用 `%param_name%` 访问变量。

```
set [<variable>=[<string>]]
```

使用 `set` 定义的变量，不能改变，只能覆盖，如果要删除可执行 `set var=` ，会将 var 变量删除，置为 `not defined` 状态。

> 使用 `set` 定义的变量只在当前上下文中生效，即同一个 cmd 窗口。如果要定义长期有效的变量可以使用  `setx` ，具体参考：<https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/setx> 

例如：

```powershell
set name=world
echo The name is %name%
```

结果：`The name is world` 

> **注意：设置变量时等号前后不能有空格，如果设置 `set name = abc` ，那么等号前的空格是变量名 `name` 的一部分 ，在使用时要带上这个空格，使用 `%name %` ；等号后面的空格是值的一部分，打印出来前面有一个空格。** 

##### 获取用户输入变量值

使用 `set` 定义变量时，可增加参数 `/p` ，能够获取用户输入的值。

```
set [/p] <variable>=[<promptString>]
```

如 `set /p var=Please input name:` ，将打印提示文字 `Please input name:` ，此时用户可输入，输入完成后按回车键确认，这样就能将用户输入值赋给变量 `name` 。

##### 定义可计算变量

使用 `set` 定义变量时，可增加参数 `/a` ，定义一个数值型的变量，赋值内容可以是一个表达式。如 `set /a sum=var1+var2` 

```
set /a <variable>=<expression>
```

> 使用 `/a` 定义变量时，表达式中的变量可不加 `%` ，直接使用变量名引用

使用 `/a` 参数后，可用如下运算符（优先级由高到低排序）

| 运算符                                 | 执行的操作       |
| -------------------------------------- | ---------------- |
| `(` `)`                                | 小括号，聚合     |
| `!` `~` `-`                            | 一元计算符       |
| `*` `/` `%`                            | 算术运算符       |
| `+` `-`                                | 算术运算符       |
| `<<` `>>`                              | 二进制移位运算   |
| `&`                                    | 按位与           |
| `^`                                    | 按位异或         |
| `|`                                    | 按位或           |
| `=` `*=` `/=` `%=` `+=` `-=` `&=` `^=` | 算术赋值         |
| `&=` `^=` `|=` `<<=` `>>=`             | 二进制运算赋值   |
| `,`                                    | 逗号表达式分隔符 |

> 注意：`%` 、`<<` 、`>>` 、`&` 、`|` 是特殊符号，所以在用于计算时要使用双引号 `""` 括起来进行转义。如：
>
> ```powershell
> set /a var="1&0"
> set /a var=1"^"1
> set /a var=1^<&<4
> ```
>
> 

示例：计算从 1 加到 100 的和，结果输出：`Sum: 5050` 

```powershell
@echo off
set /a sum=0
for /l %%i in (1,1,100) do (
    set /a sum=sum+%%i
) 
echo Sum: %sum%
```



##### 系统变量

使用 `%%` 可以获取系统变量，如 `%JAVA_HOME%` 。

一些常用的系统变量：

| 系统变量            | 描述                                                         |
| ------------------- | ------------------------------------------------------------ |
| `%random%`          | 获取 [0,32767] 之间的随机数                                  |
| `%allusersprofile%` | 所有用户配置文件的位置                                       |
| `%appdata%`         | 默认情况下应用程序存储数据的位置                             |
| `%cd%`              | 当前目录字符串                                               |
| `%cmdcmdline%`      | 启动当前的 cmd.exe 的准确命令行                              |
| `%cmdextversion%`   | 当前的命令处理程序扩展的版本号                               |
| `%computername%`    | 计算机名称                                                   |
| `%comspec%`         | 命令行解释器可执行程序的准确路径                             |
| `%date%`            | 当前日期                                                     |
| `%errorlevel%`      | 上一条命令的错误代码，通常用非零值表示错误                   |
| `%homedrive%`       | 连接到用户主目录的本地工作站驱动器号。基于主目录值而设置。用户主目录是在“本地用户和组”中指定的 |
| `%homepath%`        | 用户主目录的完整路径。基于主目录值而设置。用户主目录是在“本地用户和组”中指定的 |
| `%homeshare%`       | 用户的共享主目录的网络路径。基于主目录值而设置。用户主目录是在“本地用户和组”中指定的 |
| `%logonserver%` |  验证当前登录会话的域控制器的名称|
| `%number_of_processors%` |  指定安装在计算机上的处理器的数目|
| `%os%` |  操作系统名称。windows 2000显示其操作系统为 windows_nt|
| `%path%`|  指定可执行文件的搜索路径|
| `%pathext%`|  操作系统认为可执行的文件扩展名的列表|
| `%processor_architecture%` |  处理器的芯片体系结构。值：x86 或 ia64 基于itanium|
| `%processor_identfier%`|  处理器说明|
| `%processor_level%` |  计算机上安装的处理器的型号|
| `%processor_revision%`|  处理器的版本号|
| `%prompt%`|  当前解释程序的命令提示符设置。由 cmd.exe 生成|
| `%systemdrive%`|  包含系统根目录的驱动器|
| `%systemroot%` |  系统根目录的位置|
| `%temp%` `%tmp%`|  对当前登录用户可用的应用程序所使用的默认临时目录。有些应用程序需要 temp，而其他应用程序则需要 tmp|
| `%time%`|  当前时间。使用与 time /t 命令相同的格式|
| `%userdomain%`|  包含用户帐户的域的名称|
| `%username%`|  当前登录的用户的名称|
| `%userprofile%`|  当前用户的配置文件的位置|
| `%windir%`|  操作系统目录的位置|

##### 临时变量

在 `setlocal` 和 `endlocal` 之间定义的变量是临时变量，只在这个区域内生效。

```powershell
@echo off
echo %path%
setlocal
set path=D:/
echo %path%
endlocal
echo %path%
```

> 脚本中三个 echo 的输出结果：第一个输出环境变量中的 path，第二个输出设置的变量值 `D:/` ，第三个输出环境变量中的 path

> 关于 `setlocal enabledelayedexpansion` :
>
> 这个命令的作用是设置环境变量延迟扩展，能够让变量延迟赋值，延迟赋值的变量使用双叹号 `!!` 括起来。如：
>
> ```powershell
> @echo off 
> setlocal enabledelayedexpansion 
> set a=4 
> set a=5&echo !a! 
> pause
> ```

##### 字符串变量的处理




#### 路径

- 文件及目录路径使用反斜杠 `\` 分隔，如：`D:\test\abc.txt` 
- 文件及目录路径中包含空格时要用双引号括起来，如： `C:\Program Files\test\abc.txt` 



#### 中文

Windows 系统命令行默认使用 GBK 编码（编号: 936），如果需要显示中文，编写的脚本可以使用 `ANSI` 或 `GB2312` 编码。

如果脚本使用 `utf8` 编码，可以在命令行中执行 `chcp 65001` 命令，将当前命令行设置成使用 `utf8` 编码。



### 常用命令

#### TITLE

设置命令行窗口的标题。

```powershell
TITLE my_cmd
```

将命令行窗口名设置成当前脚本名： `TITLE %0` 



#### ECHO

输出信息，如 `echo hello`；

开启/关闭命令回显，开启回显 `echo on` ，关闭回显 `echo off`。

```
@ECHO OFF
ECHO hello world
```

> 为了防止脚本中所有命令都回显，一般都会在脚本最开头使用 `echo off` 关闭命令回显，加上 `@` 是为了关闭 `echo off` 这条命令的回显。 

特殊输出:

- `echo` 不带内容，将输出当前命令回显状态
- `echo.` 输出空行（注意 `echo` 和 `.` 之间不能有空格）



#### PAUSE

暂停执行，并输出提示语 `请按任意键继续. . .` ，英文的话输出 `Press any key to continue . . .` 。

如需更改提示信息可：

```powershell
echo 其他提示语信息 && pause > nul
```



#### GOTO 和 :

`GOTO` 跳转到指定标签处执行，如 `GOTO work` 跳转到 `work` 标签处。

`:` 用于指定标签，如 `:work` 设定标签名为 `work` 

如果要跳出执行当前脚本可用 `GOTO :eof` ，`:eof`  是文件结尾标签。



#### IF



#### FOR







### 参考资料

- windows批处理(cmd/bat)编程详解: <https://blog.csdn.net/qqlixiao2014/article/details/79172654> 
- 批处理（bat）遍历文件夹下所有文件: <https://blog.csdn.net/bigbear00007/article/details/105759830> 
- 批处理脚本遍历指定文件夹下的文件: <https://www.cnblogs.com/liangblog/p/9835940.html> 
- BAT脚本编写教程简单入门篇: <https://blog.csdn.net/daoming1112/article/details/77197558> 
- Windows bat 编程基本语法: <https://blog.51cto.com/8686505/2438270> 
- Windows commands | Microsoft Docs: <https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/windows-commands> 
- BAT命令: <https://www.cnblogs.com/liuweida/p/11062750.html> 



### 总结

Windows 官方说，命令比用户界面执行效率更高，可以执行很多诡异的操作而不受界面的限制，合理的使用脚本能帮我们处理很多重复性工作。