---
title: 利用Excel和bat对文件批量重命名
date: 2018-08-03 18:54:54
tags:
- Excel
- bat
categories:
- 技术
---

### 如何快速对批量文件进行重命名？

现在有一个需求，把文件夹中图片添加上前缀，每张图片的名称不同，而且每张图片的前缀也不一样。

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_01.png "原图") 

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_14.png "效果图") 

想想该怎么做呢？

传统的办法是不是要一张一张的去改？

数量少的时候还可以，如果有很多需要改，那怎么办呢？

可以用下面的方法试试看！

<!-- more -->

### 环境

- Windows 电脑，其它系统没有测试过
- Excel，或其他类似的表格处理软件，需要支持函数处理数据

### 操作步骤

#### 获取文件夹中的文件名列表

我这里需要获取桌面上 `picture` 文件夹中的图片文件名列表，进入到该图片文件夹，在空白处按住键盘 `shift` 键 + 鼠标右键，选择 `在此处打开命令窗口` ；当然也可以直接按 `Windows + R` 快捷键，运行 `cmd` 直接打开命令行窗口，然后再进入到需要的目录下；

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_02.png ) 

在命令行窗口中输入命令：

``````
dir C:\Users\Administrator\Desktop\picture /b -> list.txt
``````

其中参数含义如下：

| 值                                     | 含义                 | 备注                                                         |
| -------------------------------------- | -------------------- | ------------------------------------------------------------ |
| dir                                    | 查看目录和文件       | Windows 命令行指令                                           |
| C:\Users\Administrator\Desktop\picture | 当前存放图片的目录   | 可以右键单击后选择 “标记” ，选中命令行中的当前目录，按回车键复制过来 |
| /b                                     | 不显示标题信息或摘要 | dir 命令的参数                                               |
| ->                                     | 将信息输入到文件     |                                                              |
| list.txt                               | 存放数据的文件       | 文件名随意，后缀可以是 **txt** 或者 **xls**                  |

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_03.png) 

命令输入完成后，按回车运行命令，将会在文件夹中生成一个 `list.txt` 文件，里面就是需要的内容了；

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_04.png) 

注意：我们看到 `list.txt` 中也包含了自己，在执行命令时可以进行筛选，只选择其中后缀为 `jpg` 的文件，只需要修改刚才的命令，在要读取的目录后面添加 `\*.jpg` ，这样获得的数据就只要 jpg 格式的图片了，当文件夹中有其他文件时，添加筛选是非常必要的：

``````
dir C:\Users\Administrator\Desktop\picture\*.jpg /b -> list.txt
``````



#### 生成重命名命令

我们把图片名前缀需要的信息导入 Excel 表格中，我这里是直接从数据库中导出来的数据，如下所示：

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_05.png) 

需要的图片前缀格式为：`circuit-pole-` ，我们可以用 Excel 来拼接不通单元格内容，并添加需要的分隔符，以此获得图片命名的前缀，在图片名称前缀一栏的第一格中输入函数：

``````
=B2&"-"&C2&"-" 
``````

注： **B2** 为 circuit 栏的单元格，**C2** 是 pole 栏的单元格，再添加 “-”分隔就是需要的前缀了

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_06.png) 

 将鼠标放到图中所示的填充按钮处，按住鼠标左键向下拖动，直到拖到最后一条数据，这样Excel 就帮我们填充生成了剩余的图片名称前缀；

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_07.png) 

选中 Excel 中图片文件一栏的第一个单元格，打开上一步在文件夹中生成的 `list.txt` 文件，将其中的图片文件名全部选中复制，到 Excel 中粘贴，这样我们就获取到了图片名前缀和图片名了；

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_08.png) 

下一步就要生成重命名图片的命令了！

在“重命名命令” 一栏的第一个单元格中输入函数，同样填充所有需要的行：

``````
="ren "&E2&" "&D2&E2
``````

注：`ren` 是重命名(rename)的命令，第一个参数是原文件名，第二个参数是新文件名，参数中间以空格分隔

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_09.png) 

这样，我们就获取到了重命名文件的命令了！

#### 执行重命名命令

##### 直接执行命令

进入图片存储目录，打开命令行工具，把上述 Excel 表格中生成的重命名一列的单元格选中并复制，在命令行中右键单击，选择粘贴即可；

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_10.png) 

此时，再看看文件名，发现已经修改成想要的格式；

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_11.png)

##### 创建 bat 批处理文件

在图片目录中创建新的文本文档，命名为 `ren.txt` ，打开此文档，将上述 Excel 中生成的命令复制，粘贴到此文本文档中，点击菜单栏中 **文件** -> **另存为** ，另存时将文件名改为 `ren.bat` ，下面的编码选择 `ANSI` ，点击保存，这样就生成了一个批处理文件 ；

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_12.png) 

在此目录下打开命令行，执行指令 `ren.bat`，或直接双击这个 `.bat` 文件，即可运行，运行完成后，查看文件名，发现已经修改成功；

![](http://blog-images.qiniu.wqf31415.xyz/excel_bat_modify_filename_13.png) 



### 完结

这篇文章讲解了利用 Excel 批量生成 windows 命令行指令，并创建 bat 批处理文件，以此来批量修改文件名。希望这个方法可以为你打开新的思路来使用 Excel 和 windows 命令！



