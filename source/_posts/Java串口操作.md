---
title: Java串口操作
tags:
  - java 
  - 工具
  - 开发
  - 硬件
categories:
  - java
date: 2021-05-28 17:35:43
---

### 概述

这篇文章讲解了使用 rxtx 工具包在 java 程序中连接串口，并使用串口收发数据。

![](http://blog-images.qiniu.wqf31415.xyz/serial_interface.png)



### 认识串口

串行接口（Serial Interface）简称串口，也称串行通信接口或串行通讯接口（通常是指COM接口），是采用串行通信方式的扩展接口，串口传输时数据一位一位地顺序传送。串行通信具有通信线路简单的特点，只需要一对传输线就可以实现双向通信，降低了成本，适合远距离通信，缺点是传输速度较慢。

串口标准分类：

- **RS-232**: 也称标准串口，最常用的串行通信接口。
- **RS-422**: 全称“平衡电压数字接口电路的电气特性”，它定义了接口电路的特性。
- **RS-485**: 在 RS-422 基础上发展而来。



<!-- more -->

### 驱动下载

这里使用的连接工具是 [JavaRXTX](http://rxtx.qbang.org/wiki/index.php/Main_Page)，用于在java中实现串口和并行通信，它能够在64位/32位的Windows和Linux系统上使用。

RXTX for Java: <http://fizzed.com/oss/rxtx-for-java> 

注意：下载时要区分平台，网站提供了Windows版和Linux版，此外还需要区分系统架构，即区分64位和32位的 JVM，特别注意是 JVM 的版本，而不是系统的版本。

下载解压后，需要将包和驱动拷贝到Java目录下：

Windows：

- `RXTXcomm.jar` 拷贝到 `<JAVA_HOME>\jre\lib\ext` 
- `rxtxSerial.dll` 拷贝到 `<JAVA_HOME>\jre\bin` 
- `rxtxParallel.dll` 拷贝到 `<JAVA_HOME>\jre\bin` 

Linux:

+ `RXTXcomm.jar` 拷贝到 `<JAVA_HOME>/jre/lib/ext` 
+ `librxtxSerial.so` 拷贝到 `<JAVA_HOME>/jre/lib/i386/` 
+ `librxtxParallel.so` 拷贝到 `<JAVA_HOME>/jre/lib/i386/` 



### 代码示例

#### 导入串口通信jar包

下载 rxtx 的 jar 包导入项目，或在 `pom.xml` 中添加依赖：

```xml
<dependency>
    <groupId>org.rxtx</groupId>
    <artifactId>rxtx</artifactId>
    <version>2.1.7</version>
</dependency>
```



#### 查看可用串口

使用 `CommPortIdentifier` 类的静态方法 `getPortIdentifiers()` 获取当前主机中可有的串口列表，返回结果是一个 `Enumeration` （列举），使用 while 循环遍历其中元素，即为串口信息。通过 `getName()` 方法获取串口名称，以此判断是否是我们想要开启的串口。

```java
Enumeration<CommPortIdentifier> em = CommPortIdentifier.getPortIdentifiers();
while (em.hasMoreElements()) {
    String name = em.nextElement().getName();
    System.out.println(name);
}
```



#### 使用串口

- 获取所有可用的串口信息列表，遍历列表，通过串口名找到想要开启的串口，串口信息对象的类型为 `CommPortIdentifier` 。
- 使用 `CommPortIdentifier` 的 `open(String owner, int timeOut)` 方法开启串口通信，方法参数分别是：`owner` 串口使用者（名称随意），`timeOut` 开启串口的超时时间，单位毫秒。
- 开启串口后将对象类型强转成 `SerialPort` 类型，即为我们可用于传输数据的对象，然后需要使用 `setSerialPortParams(int baudRate, int dataBit, int stopBit, int checkType)` 方法为串口对象设定参数，包括波特率、数据位、停止位、校验方式。
- 使用串口对象的 `addEventListener(SerialPortEventListener listener)` 方法添加串口事件监听器，`SerialPortEventListener ` 是一个接口，需要自己实现它。
- 添加串口事件监听器后，还需要使用 `notifyOnDataAvailable(boolean b)` 开启数据可用时的通知，开启后，收到数据时才会触发事件，监听器才会收到通知。
- 收数据：在串口事件监听器中，需要实现 `serialEvent(SerialPortEvent serialPortEvent)` 方法，通过 `SerialPortEvent ` 类的 `getEventType()` 方法获取事件类型，当事件类型为 `SerialPortEvent.DATA_AVAILABLE` 时，说明有可读数据，通过串口对象的 `getInputStream()` 方法获取输入流，使用输入流即可从流中读取数据。
- 发数据：使用串口对象的 `getOutputStream()` 方法获取输出流，通过输出流即可发送数据。

```java
import gnu.io.*;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;
import java.util.TooManyListenersException;

public class Test {
  private static SerialPort mySerialPort = null;
  
  public static void main(String[] args) {
    String myCommName = "COM2"; // 要开启的端口名
    int baudRate = 9600; // 通信波特率
    int dataBit = SerialPort.DATABITS_8; // 数据位，8
    int stopBit = SerialPort.STOPBITS_1; // 停止位，1
    int checkBit = SerialPort.PARITY_NONE; // 校验方式，无

    // 获取所有可用的串口信息
    Enumeration<CommPortIdentifier> commPorts = CommPortIdentifier.getPortIdentifiers();
    while (commPorts.hasMoreElements()) {
      CommPortIdentifier port = commPorts.nextElement();
      System.out.println("Port: " + port.getName());
      if (CommPortIdentifier.PORT_SERIAL == port.getPortType() && myCommName.equals(port.getName())) {
        try {
          // 开启串口，参数: 程序名称; 开启端口超时时间：ms
          mySerialPort = (SerialPort) port.open("TestProgram", 2000); 
            
          // 设置串口通讯参数: 波特率，数据位，停止位, 校验方式
          mySerialPort.setSerialPortParams(baudRate, dataBit, stopBit, checkBit);
            
          // 添加串口事件监听器
          mySerialPort.addEventListener(new SerialPortEventListener() {
            public void serialEvent(SerialPortEvent serialPortEvent) {
              switch (serialPortEvent.getEventType()) {
                case SerialPortEvent.BI: // 通讯中断
                case SerialPortEvent.OE: // 溢位错误
                case SerialPortEvent.FE: // 帧错误
                case SerialPortEvent.PE: // 奇偶校验错误
                case SerialPortEvent.CD: // 载波检测
                case SerialPortEvent.CTS: // 清除发送
                case SerialPortEvent.DSR: // 数据设备准备好
                case SerialPortEvent.RI: // 响铃侦测
                case SerialPortEvent.OUTPUT_BUFFER_EMPTY: // 输出缓冲区已清空
                  break;
                case SerialPortEvent.DATA_AVAILABLE: // 有数据到达
                  // 读取数据
                  InputStream inputStream = null;
                  try {
                    // 获取输入流
                    inputStream = mySerialPort.getInputStream();
                    byte[] readBuffer = new byte[inputStream.available()];
                    int len = 0;
                    while ((len = inputStream.read(readBuffer)) > 0) {
                      System.out.println("Data len: " + len);
                      String data = new String(readBuffer, 0, len).trim();
                      System.out.println("Receive data: " + data);
                      // 打印字节
                      System.out.print("Hex data: ");
                      for (byte b : readBuffer) {
                        String s = Integer.toHexString(0xFF & b);
                        System.out.print(b < 16 ? "0" + s : s);
                      }
                      System.out.println();
                    }
                  } catch (IOException e) {
                    e.printStackTrace();
                  } finally {
                    if (inputStream != null) {
                      try {
                        inputStream.close();
                      } catch (IOException e) {
                        e.printStackTrace();
                      }
                    }
                  }
                  break;
                default:
                  break;
              }
            }
          });
          // 开启当有数据时的通知
          mySerialPort.hnotifyOnDataAvailable(true); 

          // 发送数据
          // 获取串口输出流
          OutputStream outputStream = mySerialPort.getOutputStream(); 
          outputStream.write("hello".getBytes());
          outputStream.flush();
          if (outputStream != null) outputStream.close();

        } catch (PortInUseException e) {
          e.printStackTrace();
        } catch (TooManyListenersException e) {
          e.printStackTrace();
        } catch (UnsupportedCommOperationException e) {
          e.printStackTrace();
        } catch (IOException e) {
          e.printStackTrace();
        }
        break;
      }
    }
  }
}
```



### 测试

如果没有硬件用来测试串口，可以使用模拟串口软件来模拟，这里使用到的是 [Virtual Serial Port Driver](https://www.eltima.com/products/vspdxp/) 工具，收费软件，可免费使用 14 天。用这个软件可以创建虚拟串口组，我们可以开启两个串口程序分别连接，即可进行通信测试。

软件操作很简单，创建一个 `Pair` 即可，我创建的是 `COM2` 和 `COM3` ，是两个虚拟串口，通过程序连上这两个串口后，软件上会显示串口连接信息，包括连接的程序、配置、收发字节数。

![](http://blog-images.qiniu.wqf31415.xyz/vspd.gif) 

将上述的 java 代码再复制一份，并将代码中的连接串口名分别改成创建的虚拟串口 `COM2` 和 `COM3` ，运行代码后，查看 Virtual Serial Port Driver ，发现串口已经被连接上了。查看java程序控制台，发现其中一个程序控制台输出收到的数据，说明程序运行成功。

```
Data len: 5
Receive data: hello
Hex data: 68656c6c6f
```



### 参考资料

- java 串口通信实现流程: <https://www.cnblogs.com/zhylioooo/p/7886189.html> 
- java读写串口数据: <https://www.cnblogs.com/new-life/p/9345849.html> 
- java串口通信编程实例: <http://www.elecfans.com/d/627763.html> 
- 几款优秀的 Windows 虚拟串口模拟器: <https://blog.csdn.net/ybhuangfugui/article/details/106088618> 



### 总结

串口通信在硬件开发时经常用到，学会用 java 操作串口，对于想要接触或配合硬件开发的 java 程序员来说，还是挺重要的。需要注意的是，对于硬件的操作需要区分平台，所以需要根据运行环境下载安装不同版本的工具包。另外， java 操作串口的库已经很久没有更新过了，随着硬件的发展，不知道以后这些库会不会有问题。