---
title: Arduino 初识
tags:
- arduino
- Iot
categories:
- 技术
---

### 摘要

这篇文章主要介绍了 Arduino 的概念，分析了 Arduino 在硬件开发中的优势，从硬件、软件角度认识什么是 Arduino，最后体验了使用 Arduino IDE 开发点亮 LED 灯的项目，分析了项目代码。



### Arduino 是什么？

> 官网：<https://www.arduino.cc/> 

Arduino 诞生于 2005年，是一个开源的，简单易用的电子开发平台。在这里除了 Arduino 这个名字被注册成了商标，需要授权才能以 Arduino 命名，其他的都是开源的，其中包括电路板等硬件资源，也包括开发使用的软件 IDE。Arduino 抛开了传统硬件开发的复杂操作，不需要了解硬件的内部结构和寄存器设置，也不需要过多的电子知识和编程知识，只需要简单的学习，了解各个引脚和函数的作用，就可以开发出各种出色的项目。还可以跟其他硬件结合，开发出更有趣的作品。

![](http://blog-images.qiniu.wqf31415.xyz/arduino_logo.png)

<!-- more -->



### 一些基于 Arduino 开发的项目

- ArduPilot，<http://ardupilot.org/> ，基于 Arduino 开发的无人机控制系统。

  ![](http://blog-images.qiniu.wqf31415.xyz/ArduPilot.jpg)

  

- MakerBot，<https://www.makerbot.com/> ，使用 ArduinoMega 作为主控制器的 3D 打印机。

  ![](http://blog-images.qiniu.wqf31415.xyz/MakerBot.png)

  

- ArduSat，<https://www.kickstarter.com/projects/575960623/ardusat-your-arduino-experiment-in-space> ，采用 Arduino 的人造卫星项目。

  ![](http://blog-images.qiniu.wqf31415.xyz/ArduSat.png)





### Arduino 的优势

#### 跨平台

Arduino 支持 Windows、Mac OS、Linux 三大主流操作系统。

#### 开发简单易上手

Arduino 语言是基于 Wiring 语言开发的，对 AVR、GCC 库进行二次封装，用户不需要太多的单片机基础和编程基础，简单学习一下就可以进行项目开发了，学习成本低、开发周期短。

#### 开放性

Arduino 的硬件原理图、电路图、IDE软件、核心库文件都是开源的，因此在国内才可以以非常便宜的价格买到可用的开发板。

#### 活跃的社区环境

Arduino 拥有众多的开发者和活跃的社区，很容易获得实例代码和硬件设计，也很容易获取到第三方硬件、类库的支持。



### 硬件

Arduino 诞生至今出现了很多硬件设备，包括核心的控制器（也可以称之为开发板）、外围设备和扩展板。

#### Arduino UNO

使用最广泛的 Arduino 控制器，价格便宜，初学者首选。

![](http://blog-images.qiniu.wqf31415.xyz/arduino_uno_r3.jpg)

#### Arduino MEGA

增强版，比 UNO 具有更多的 I/O 接口，可以控制更多的设备，同时也拥有更大的程序空间和内存，适合较大型项目。

#### Arduino Leonardo

2012 年推出，具有其他型号控制器的所有功能，还能模拟鼠标、键盘等 USB 设备。

#### Arduino Due

2012 年推出，首次使用 32 位 ARM Cortex M3 作为主控芯片，而其他的使用的是 8 位 AVR 单片机，性能上远低于 Due，同时，它还具有多种外设，是目前最强大的 Arduino 控制器。

#### Arduino Zero

目前最新的 Arduino 控制器方案，使用 Atmel 公司的 ARM Cortex-M0 芯片，最大特点是提供 EDBG 调试端口，可以联机进行单步调试，降低了开发调试的难度。

#### 小型化的 Arduino

为了应对特殊需求的设计方案，常见的有 Arduino Nano、Arduino Mini、Arduino Micro、Arduino Lilypad 等。

#### 衍生控制器

由第三方硬件公司或 Arduino 爱好者基于 Arduino 设计理念在其他单片机上完成的类似 Arduino 的开发工具，具有与 Arduino 兼容的硬件外形设计，使用相同的开发环境和核心类库，只要学会了 Arduino 开发方式，就可以使用这些衍生控制器进行开发了。

#### Intel Galileo

Intel 公司推出的 Arduino 衍生控制器，使用 x86 内核的夸克处理器，同时运行一套 Linux 系统，既可以当作 Arduino 开发，也可以进行 Linux 开发。

#### Maple

LeafLabs 公司基于意法半导体的 STM32 芯片开发的，以 ARM Cortex M3 为核心，有着与 Arduino 相似的开发方式。

#### ChipKit

DIGLENT 公司推出的，基于微芯公司 PIC32 芯片开发的，以MIPS 为核心的 Arduino 控制器，与 Arduino 具有相似的开发方式。

#### Google ADK 2012

Google 公司推出的，基于 Arduino Due 的控制器，主要用于结合 Android 设备制作各种项目。

#### 外围模块

可以与 Arduino 连接使用的的模块，包括传感器、开关、通信设备、显示设备等，组合使用完成不同功能。

#### Arduino 扩展板

可以插到 Arduino 上的电路板，不同扩展板有着不同功能，使用扩展板不需要考虑接口位置，堆叠插到 Arduino 上即可，有的扩展板可以重叠多个，达到扩展多个功能的目的。



#### Arduino UNO R3

这是入门首选的 Arduino 控制器，我也在某宝上买了一个，带线二十块钱左右。

- 电源(Power)：UNO 支持 USB 供电(5V)、DC 电源供电(5V)、VIN 端口供电(7~12V)
- 指示灯(LED)：
  - ON：电源指示灯，通电时会亮
  - TX：串口发送指示灯，使用USB连接电脑且向电脑传输数据时会亮
  - RX：串口接送指示灯，使用USB连接电脑且接收到计算机传输的数据时会亮
  - L：可编程控制指示灯，通过特殊电路连接到 Arduino 的 13 号引脚，当13 号引脚为高电平时会亮，为低电平时不亮，可以通过编程控制 13 号引脚的电平高低来控制 L 灯
- 复位按键(Reset Button)：按下后 Arduino 重启，程序重新执行
- 存储空间(Memory)：Arduino 的存储空间是指主控芯片所集成的存储空间，可以通过使用外设芯片的方式扩展存储空间。
  - Flash：32KB，其中 0.5 K 用于存储引导程序，其他 31.5 K 用于存储用户程序
  - SRAM：2KB，相当于计算机内存，cpu 运算时使用，断电或重启后数据消失
  - EEPROM：1KB，用户可更改的只读存储器，全称为电科擦写的可编程只读存储器，Arduino 断电或重启，数据不会消失
- 输入/输出端口(Input/Output Port)：Arduino 上有多个输入输出端口，以 Arduino UNO 为例，有 14 个数字输入/输出端口，6个模拟输入端口。
  - UART通信：0 (RX) 用于接收串口数据，1 (TX) 用于发送串口数据，外部中断为 2, 3 引脚，可以输入外部中断信号
  - PWM 输出：3,5,6,9,10和11 引脚，用于输出 PWM 波
  - SPI通信：10 (SS)，11 (MOSI)，12 (MISO)，13 (MCK) 
  - TWI 通信：A4 (SDA)，A5 (SCL)，用于 TWI 通信，兼容 IIC 通信
  - AREF：模拟输入参考电压的输入端口
  - Reset：复位端口，接低电平时会使 Arduino 复位。按下复位键时，会使该端口接到低电平，从而使 Arduino 复位



### 软件

#### 下载与安装

> 下载地址：<https://www.arduino.cc/en/Main/Software> 

Arduino IDE 支持三大主流的操作系统，其中在 Windows 8 和 Windows 10 中可以在应用商店中直接下载安装，Windows 7 可以使用 exe 安装文件进行安装。在 Ubantu 系统中，可以使用软件中心安装。

运行 Arduino 需要 JAVA 环境，如果没有安装过，在安装过程中会提示安装。



#### Hello World

硬件开发时的 Hello World 是点亮 LED 灯，我们从点亮第一盏灯开始 Arduino 之旅，也是第一次体验使用 Arduino 进行硬件开发。

##### 打开官方示例代码

第一步，打开 Arduino IDE，点击 **"文件"** - **"示例"** - **"01.Basics"** - **"Blink"** ，即可打开官方自带的 LED 灯闪烁示例

![](http://blog-images.qiniu.wqf31415.xyz/arduino_example_blink.png)

可以简单阅读一下代码，其中说明内容比较完善，这个程序(在 Arduino 中叫做 sketch) 的作用是让控制器板上内嵌的 LED 闪烁。

##### 连接控制器(开发板)

通过 USB 连接线将控制器连接到电脑上，可能需要安装驱动程序，连接正确时，可以在设备管理器中看到，如下图所示：

![](http://blog-images.qiniu.wqf31415.xyz/arduino_connect_computer.png)

在 Windows 系统中，通过设备管理器查看 “端口”，即可看到连接上的 Arduino 控制器，如上图中显示的，我的控制器是使用 CH340 进行数据传输的，在电脑的 3 号串口上进行通信。

在 Mac OS 或 Linux 中，串口名称一般为 `/dev/tty.usbmodem` 加数字编号，或者 `/dev/cu.usbmodem` 加数字编号

##### 参数设置

在上传程序代码到控制器前，首先要选择使用的开发板，配置相应的参数，如下图所示，我选择的开发板是 Arduino UNO，选择的端口是刚才在设备管理器中看到的 "COM3"

![](http://blog-images.qiniu.wqf31415.xyz/arduino_connect_config.png)

##### 编译并上传程序代码

代码编辑完成后，可以点击 Arduino IDE 工具栏中的 “验证” 按钮，检验代码是否存在问题，确认没问题后，点击 “上传” 按钮即可将程序上传到控制器，上传期间，标为 “TX” 和 “RX” 的 LED 灯快速闪烁，说明正在写入。上传完成后，UNO 将自动开始执行代码，板子上标为 “L” 的 LED 灯开始闪烁。

![](http://blog-images.qiniu.wqf31415.xyz/arduino_ide_upload_btn.png)



#### 代码解析

Arduino 中使用的是 **C++** 和 **C** 语言进行编程，但是我们在示例代码中并没有找到 main 函数，并不是不需要 main 函数，而是main 函数被包含在了 Arduino 核心库中了，不需要用户手动添加了。

下面是 Arduino IDE 官方的 Blink 示例代码：

```c
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
```

在 Arduino 程序中，默认包含两个必须的函数，**setup** 函数在开发板通电或重启时执行，只会执行一次，一般用于初始化程序所需的资源，如开启串口、连接 wifi等。**loop** 函数在 setup 函数执行完成后开始执行，将一直循环执行，一般用于处理关键功能，如采集数据、网络通信等。

在程序中我们看到使用了 **pinMode** 函数，这是 Arduino 核心库提供的 api，用于设置引脚工作模式，在传统硬件开发时需要用户设置寄存器实现，Arduino 为我们屏蔽了与硬件交互的复杂性，对底层交互进行了封装。这个函数接收两个参数，第一个参数是引脚的值，第二个参数是引脚模式。在这里的引脚是 **LED_BUILTIN** ，它的值在开发板的核心库文件中定义，选择不同的开发板，这个参数的值是不同的。指定引脚的工作模式是 **OUTPUT** ，即输出模式，值为 0 ，此外还可以定义成 INPUT，输入模式，值为 1，INPUT_PULLUP，输入上拉模式。

在 loop 函数中，实现了让 led 灯循环闪烁的功能，其中 **digitalWrite** 函数使引脚输出高电平或低电平，第一个参数是控制的引脚号，第二个参数是指定高低电平，使用 **HIGH** (值为 1) 指定高电平，对于 Arduino UNO 来说是 5V (开发板的工作电压)，使用 **LOW** (值为 0) 输出低电平，对于 Arduino UNO来说是 0V。

> 使用 **digitalRead** 函数可以读取引脚的电平状态，当 Arduino 以 5V 供电时，-0.5 ~ 1.5V的输入电压作为低电平识别，3 ~ 5.5V 的输入电压被当做高电平识别。

**delay** 函数用于暂停程序，参数为暂停时间的毫秒数。



### 总结

这篇文章主要是对 Arduino 的初步认识，了解这是什么，能干什么，有什么优势，使用官方示例体验 Arduino 开发硬件。



