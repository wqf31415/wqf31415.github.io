---
title: Windows脚本编写
date: 2021-02-03 18:55:08
tags:
  - Windows
  - bat
categories:
  - 技术
---

### 概述

灵活使用脚本可以完成一些重复性的工作，提高工作效率，这篇文章介绍了 Windows 系统脚本的编写规则和一些常用命令。

![](http://blog-images.qiniu.wqf31415.xyz/plant-computer.jpg)

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

本文中用到的和没用到的命令都可以从官方文档中查到，讲解非常全面，而且可以按首字母查询，有疑惑可以去查阅：

<https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/windows-commands> 



#### 总纲

- 脚本文件后缀为 `.cmd` 或 `.bat` 
- 关键字与变量名不区分大小写，例如：`REM` = `rem` = `rEM` ，`%JAVA_HOME%` = `%java_home%` = `%jAva_hOmE%` 
- 一行为一条命令，按行读取命令，每次处理一行



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

- `%0` 为第一个参数，即当前脚本。这个参数可以用于调用当前脚本本身，达到循环执行当前脚本功能，也可以用于复制文件自身，如: `copy %0 d:\\test.bat` (注意，调用时要使用脚本全称(包括扩展名)，才能完成复制脚本本身文件)
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
set [变量名=[变量值]]
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

> 变量名可以是中文，如：
>
> ```powershell
> @echo off
> set 你=张三
> echo 你：%你%
> ```



##### 获取用户输入变量值

使用 `set` 定义变量时，可增加参数 `/p` ，能够获取用户输入的值。

```
set /p 变量名=[提示文字]
```

如 `set /p var=Please input name:` ，将打印提示文字 `Please input name:` ，此时用户可输入，输入完成后按回车键确认，这样就能将用户输入值赋给变量 `name` 。



##### 定义算术变量

使用 `set` 定义变量时，可增加参数 `/a` ，定义一个可计算的数值型变量，赋值内容可以是一个表达式。如 `set /a sum=var1+var2` 

```
set /a 变量名=表达式
```

> 注意：使用 `/a` 定义变量时，表达式中的变量可不加 `%` ，直接使用变量名引用
>
> 注意：Windows 脚本中只能进行整数计算，3/2 结果为 1

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

> 注意：`%` 、`<<` 、`>>` 、`&` 、`|` 等是特殊符号，所以在用于计算时要把表达式使用双引号 `""` 括起来，其中 `<` 、`>` 、`&` 可使用 `^` 进行转义，取模使用 `%%`。
>
> 用法示例：
>
> ```powershell
> @echo off
> set /a a=(1+1)*2
> set /a b=!0
> set /a c=~4
> set /a d=-4
> set /a e=10%%3
> set /a f=1^<^<3
> set /a g=1024^&512
> set /a h=1024"^"512
> set /a i=1024"|"512
> set /a j="1024^512"
> 
> echo (1+1)*2 = %a%
> echo !0 = %b%
> echo ~4 = %c%
> echo -4 = %d%
> echo 10%%3 = %e%
> echo 1^<^<3 = %f%
> echo 1024^&512 = %g%
> echo 1024^^512 = %h%
> echo 1024^|512 = %i%
> echo 1024^^512 = %j%
> ```
>
> 结果：
>
> ```
> (1+1)*2 = 4
> !0 = 1
> ~4 = -5
> -4 = -4
> 10%3 = 1
> 1<<3 = 8
> 1024&512 = 0
> 1024^512 = 1536
> 1024|512 = 1536
> 1024^512 = 1536
> ```



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

###### 截取

可以按开始位置和结束位置截取；也可以按开始位置截取指定长度。截取时第一个参数是开始位置，第二个参数是正数时，表示截取长度，第二个参数为负数时，表示结束位置（不包含结束位置的字符）。

```
%str:~start,end%
%str:~start,length%
```

> 注意：位置从前向后计数时从 0 开始，从后向前倒数时从 -1 开始。

示例：

```powershell
@echo off
set str=abcde12345
echo 原字符串：%str%
echo 前三个：%str:~0,3%
echo 后三个：%str:~-3,3%
echo 第五到第八：%str:~4,4%
echo 第三到倒数第三：%str:~2,-3%
```



###### 替换

使用新字符串替换旧字符串

```powershell
%str:old=new%
```

示例：

```powershell
@echo off
set str=hello world
echo 替换后:%str:world=bat%
```



###### 合并

```powershell
@echo off
set str1=hello
set str2=world
set str3=%str1% %str2%
echo 合并：%str3%
```



#### 路径

Windows 脚本中的路径写法规则如下：

- 文件及目录路径使用反斜杠 `\` 分隔，如：`D:\test\abc.txt` 
- 文件及目录路径中包含空格时要用双引号括起来，如： `C:\Program Files\test\abc.txt` 
- **不区分大小写** 



#### 特殊符号

一些符号在 Windows 脚本中有特定功能。

| 特殊符号 | 功能               | 说明                                                         |
| -------- | ------------------ | ------------------------------------------------------------ |
| `@`      | 命令回显屏蔽符     | 放在行首，屏蔽改行命令回显                                   |
| `%`      | 变量引导符         | 用于获取变量值，如 `%1` 、 `%name%`                          |
| `>`      | (覆盖)输出重定向符 | 将输出结果以覆盖的方式传递到后面的范围，后写入的内容将覆盖之前的内容，如写入文件：`echo hello > hello.txt` ；写入控制台：`echo hello > con` ；将执行成功结果输出到控制台，执行失败结果输出到文件：`dir test 1> con 2> log.txt` |
| `>>`     | (追加)输出重定向符 | 将输出结果以追加的方式传递到后面的范围，后写入的内容将追加在之前内容的后面，如写入文件: `echo hello >> hello.txt` 这种方式可用来输出日志 |
| `<`      | 输入重定向符       | 从文件或设备中读取命令输入，默认从读取键盘输入               |
| `<&`     | 输入重定向符       | 从后一个句柄读取输入并写入前一个句柄的输入中                 |
| `|`      | 命令管道符         | 将上一条命令的输出结果作为下一条命令的输入参数，如查找占用 8080 端口的程序： `netstat -ano | findstr 8080` |
| `^`      | 转义字符           | 消除特殊字符 `<` 、`>` 、`&` 的特殊功能，将其转成字符本身，如 `echo 2^>1` ，将打印 `2>1` 而不是写入文件。放在行尾可当作连字符，因为其可以转义换行符，使换行符失效 |
| `&`      | 组合命令           | 顺序执行多条命令，不管是否成功，如 `dir test & echo ok` ，不管 `dir test` 命令是否成功，都会输出 `ok` |
| `&&`     | 组合命令           | 顺序执行多条命令，当其中一条执行失败，后续命令不执行，如 `dir test && echo ok` |
| `||`     | 组合命令           | 同时执行多条命令，当前一条命令执行失败后才会执行后一条，某一条执行成功后，后续命令不执行，如 `dir test || echo ok || echo hhh` |
| `\"\"`   | 字符串界定符       | 双引号运行字符串包含空格，如进入包含空格的目录：`cd \"program files\"` |
| `,`      | 逗号               | 在一些情况下，逗号可当作空格，如 `dir,a` 和 `dir a` 效果相同 |
| `;`      | 分号               | 当命令相同时，可以用分号来隔离不同目标，如 `mkdir a;b;c` 将创建 a、b、c 三个文件夹 |
| `()`     | 括号               | 括号中可包含多条命令，这些命令将会看作一个整体处理，         |
| `!`      | 感叹号             | 用在对延迟变量取值，如 `!name!`                              |



#### 系统句柄

| 句柄      | 句柄号 | 说明                                                         |
| --------- | ------ | ------------------------------------------------------------ |
| STDIN     | 0      | 标准输入，默认从键盘输入                                     |
| STDOUT    | 1      | 标准输出，默认输出到命令提示符，如将执行成功结果输出到文件：`echo ok 1> success.log` |
| STDERR    | 2      | 标准错误输出，默认输出到命令提示符，如将错误信息输出到文件：`dir abc 2> error.log` |
| UNDEFINED | 3-9    | 未定义句柄，由程序和各个具体工具单独定义                     |
| nul       |        | 空设备，如将结果输出到空设备，即不显示执行结果：`ping -n 2 localhost > nul` |
| con       |        | 控制台，如输出结果到控制台：`echo hello > con`               |
| prn       |        | 打印机                                                       |



#### 中文

Windows 系统命令行默认使用 GBK 编码（编号: 936），如果需要显示中文，编写的脚本可以使用 `ANSI` 或 `GB2312` 编码。

如果脚本使用 `utf8` 编码，可以使用 `chcp 65001` 命令，将当前命令行设置成使用 `utf8` 编码即可显示中文。



### 常用命令

#### TITLE

设置命令行窗口的标题，执行后当前命令行窗口标题显示为设置的名称。

```powershell
TITLE my_title
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

如需更改提示信息，可自己用 echo 输出提示文字，同时将 pause 命令的输出内容重定向到 `nul` ：

```powershell
echo 其他提示语信息 && pause > nul
```



#### GOTO 和 :

`GOTO` 跳转到指定标签处执行，如 `GOTO work` 跳转到 `work` 标签处。

`:` 用于指定标签，如 `:work` 设定标签名为 `work` 

如果要跳出执行当前脚本可用 `GOTO :eof` ，`:eof`  是文件结尾标签。当用标签定义一个方法函数时，在最后也要用 `goto :eof` 跳出，否则会执行后面的命令。



#### IF

条件判断。

语法：

```bash
if [not] ERRORLEVEL <number> <command> [else <expression>]
if [not] <string1>==<string2> <command> [else <expression>]
if [not] exist <filename> <command> [else <expression>]
```

> 判断时加 `not` 对判断条件取反。

##### 错误码判断

使用错误码判断命令是否执行成功。

```powershell
@echo off
dir abc
echo errorlevel: %errorlevel%
if errorlevel 0 (echo ok) else (echo fail)
```

> 注意：上面脚本执行失败时将输出 `ok` ，因为 `errorlevel 0` 判断的是 errorlevel >= 0，errorlevel 值为 1，满足条件，因此输出了 `ok`。

还可以直接使用错误码变量进行判断：

```
@echo off
dir abc
echo errorlevel: %errorlevel%
if %errorlevel% == 0 (echo ok) else (echo fail)
```

> 上面脚本是判断 errorlevel 是否等于 0，如果执行失败将打出 `fail`。



##### 字符串比较

判断字符串是否相同时，默认是区分大小写的，可以加 `/i` 参数，忽略大小写。如下脚本将输出 `equal` 

```powershell
@echo off
set a=hello
set b=hellO
if /i %a%==%b% (echo equal) else (echo not equal)
```



##### 判断文件是否存在

```powershell
@echo off
if exist test.cmd (echo exist) else (echo not exist)
```



##### 判断数字的比较符

由于 `<` 、`>` 是特殊符号，所以不能用来判断，要用比较关键字：

| 关键字 | 功能     |
| ------ | -------- |
| `EQU`  | 等于     |
| `NEQ`  | 不等于   |
| `LSS`  | 小于     |
| `LEQ`  | 小于等于 |
| `GTR`  | 大于     |
| `GEQ`  | 大于等于 |

例如：

```powershell
@echo off
if 3 gtr 2 (echo right) else (echo wrong)
```

> 将输出 `right` 



#### FOR

循环遍历，可用于递归遍历目录中的文件。

语法：

```bash
for [参数] %%变量 in (匹配规则) do 执行的命令
```

> 注意 `in` 、`do` 和括号之间是有空格的，如果连在一起会报错。

参数：

- 不带参数：遍历当前路径下的文件夹下的**文件**，但也可在（匹配规则）中指定路径。如遍历 D盘下 test 目录下的所有文件：`for /d %%i in (D:\\test\*) do echo %%i` 
- `/d` ：遍历当前路径下的文件夹下的**文件夹**，但也可在（匹配规则）中指定路径。如遍历 D盘下 test 目录下的所有目录：`for /d %%i in (D:\\test\*) do echo %%i` 
- `/r [路径]` ：递归遍历指定路径下的所有文件，将遍历所有子目录下的文件。如遍历 D盘下 test 目录中的所有 `.txt` 文件：`for /r D:\\test\ %%i in (*.txt) do echo %%i` 
- `l` ：在一个范围内迭代，此时匹配规则为 `(start,step,end)` ，start 为开始值，step 为每次迭代递增值，end 为结束遍历的值，类似其他编程语言中的 for 循环： `for(int i = start; i< end; i += step)` 。示例打印 1 到 100：`for /l %%i in (1,1,100) echo %%i` 
- `f` ：遍历文件中的内容。如逐行打印文件中的内容：`for /f %%i in (list.txt) do echo %%i` 

变量：用来指向每次遍历的值，只能用单个字符，如 `%%a` 、`%%B` 、`%%i` 。变量名区分大小写，`%%a` 和 `%%A` 不同。

匹配规则：`*` 匹配多个字符，`?` 匹配单个字符。如遍历所有 `.txt` 文件 `*.txt` 。规则可以有多个，如遍历所有 `.jpg` 和 `.jpeg` 图片：`*.jpg *.jpeg` 。

执行的命令：可执行单条命令，或使用括号包括以执行多条命令



#### CALL

调用其他脚本或标签。

语法：

```powershell
call [盘符:][路径]<脚本文件> [批处理参数] [:<标签> [<参数>]]
```

##### 调用其他脚本

使用 call 可以在当前脚本中调用其他脚本，在调用时可以传递参数。在调用的脚本执行完成后，接着执行下面的命令。

hello.bat 脚本：

```powershell
@echo off
call hi xiaoming
echo over
```

被调用的脚本 `hi.bat` ：

```powershell
@echo off
echo Hi, %1
```

执行结果：

```
Hi, xiaoming
over
```



##### 调用标签

使用 call 能够调用当前脚本中的其他标签。

脚本 call.bat

```powershell
@echo off
if %1 equ 1 call :isOne
goto :eof

:isOne
echo it is one
goto :eof
```

> 上面脚本判断参数是否为 1，如果是 1，就调用标签，否则就退出。
>
> 当运行 `call 1` 时，将输出 `it is one` 。



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