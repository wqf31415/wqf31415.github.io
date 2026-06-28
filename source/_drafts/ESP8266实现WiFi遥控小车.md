---
title: ESP8266实现WiFi遥控小车
tags:
  - esp8266
  - arduino
  - 开发板
  - 硬件
categories:
  - Arduino
date: 2026-06-01 10:52:47
---

### 概述
本项目使用 ESP8266 开发板和 L298N 电机驱动模块实现 WiFi 遥控小车，并使用 Blinker APP 进行遥控。


### 核心组件

ESP8266 开发板是基于 ESP8266 微控制器的开发板，它集成了 WiFi 功能，可以通过 WiFi 连接到网络，实现遥控控制。
L298N 电机驱动模块是双电机驱动模块，用于控制小车的运动方向。

<!-- more -->

### 物料

#### 硬件

|名称|数量|总价|备注|
|--|--|--|--|--|
|ESP8266|1|10元||
|小车底盘+电机*4|1套|￥23.7||
|L298N电机驱动模块|1|￥7.4||
|18650锂电池（带线）|2|￥24||
|18650锂电池盒（2节）|1|￥2.4|连接到电机驱动模块|
|杜邦线（母对母）|6|￥0.6|用于连接开发板和电机驱动模块|
|导线|8|￥0.4|用于连接电机驱动模块和电机，红黑各4根|

#### 软件

|名称|版本|下载链接|备注|
|--|--|--|--|--|
|Arduino|1.8.9|https://www.arduino.cc/en/software|用于编写代码|
|Blinker|2.6.5|https://diandeng.tech/home|用于WiFi遥控|

#### 工具

|名称|用途|备注|
|--|--|--|--|
|电脑|编写代码|Windows 11|
|手机|安装Blinker APP|华为Mate 30，鸿蒙4.2|
|螺丝刀|安装小车组件||
|数据线|连接开发板和电脑||
|电烙铁|将导线焊接到电机上||
|直流电源|测试电机转动方向|可用电池替代|



### 原理

#### 电源

使用两节 18650 电池（3.7V），串联提供 7.4V 电压。

#### 电机驱动

使用 L298N 电机驱动模块，有两组控制输出引脚，分别对应左侧电机和右侧电机。

#### 运动控制

使用 ESP8266 开发板作为主控，实现对电机驱动模块的控制，根据按钮的状态切换电机的运动方向。

#### 远程遥控

使用 Blinker APP 进行遥控，点击 APP 中的按钮，小车会根据按钮的状态进行运动。


### 安装小车组件与连线

#### 确定电机安装位置与正负极接线

指定4个电机在底盘上的安装位置，用马克笔或标签纸标记安装位置（如左前、右前、左后、右后），通过直流电源提供3V电压测试电机转动方向，当电机转动方向为向前时，将此时通电的胜负极标注好。

使用电烙铁将导线焊接到电机上，正极焊接红色导线，负极焊接黑色导线。

用电烙铁将小车同侧的同色导线焊接到一起，后续一起接入到电机驱动模块的对应引脚。

#### 安装小车底盘

用固定片、螺丝、螺母将电机固定在小车下层底盘上，按照标记的位置安装，安装轮子。

然后使用螺丝和塑料柱将小车底盘的上层板安装到底盘上，将电机线从底盘孔洞拉出。

#### 连接电机驱动模块

将左侧电机正极导线连接到 L298N 电机驱动模块的 OUT1 引脚，将左侧电机负极导线连接到 L298N 电机驱动模块的 OUT2 引脚。

将右侧电机正极导线连接到 L298N 电机驱动模块的 OUT4 引脚，将右侧电机负极导线连接到 L298N 电机驱动模块的 OUT3 引脚。

#### 安装电池盒

用螺丝将电池盒固定在小车底盘上，将电池盒正极导线接到 L298N 电机驱动模块的 `+12V` 引脚，将电池盒负极导线接到 L298N 电机驱动模块的 `GND` 引脚。

#### 连接开发板

用杜邦线将 ESP8266 的 `D1`、`D2`、`D3`、`D4` 引脚分别连接到 L298N 电机驱动模块的 IN1、IN2、IN3、IN4 引脚。

用杜邦线将 ESP8266 的 `VIN` 引脚连接到 L298N 电机驱动模块的 `+5V` 引脚，将 ESP8266 的 `GND` 引脚连接到 L298N 电机驱动模块的 `GND` 引脚。



### Blinker APP 配置

从[点灯科技官网](https://diandeng.tech/home) 下载 Blinker APP 并安装到手机上，注册账号并登录。

点击 APP 右上方角的 `+` 按钮，添加一个新的设备，设备类型选择 `独立设备`，然后选择 `网络接入`，等待设备注册完成。注册完成后会给此设备生成一个认证码，记录下来用于后续的遥控控制。

进入设备的可视化UI配置页面，添加5个按键，分别对应前进、后退、左转、右转、停止操作，组件名称分别为 `btn-forward`、`btn-backward`、`btn-left`、`btn-right`、`btn-stop`，这里的组件名称需要记录下来，后续在代码中会使用到这些名称。

所有按键类型选择 `普通按键` 类型，修改显示文本和图标为对应的操作图标。

### 代码

#### 安装 Blinker 库

打开 Arduino 软件，进入 `项目` -> `加载库` -> `管理库`，搜索 `Blinker`，安装 `Blinker` 库。

#### 编写控制代码

在 Arduino 中新建一个项目，选择 ESP8266 作为开发板，将代码保存为 `ESP8266WiFiRemoteCar.ino`。

```c++

#include <Blinker.h>

#define BLINKER_WIFI

// 填写你的WiFi信息和秘钥
char auth[] = "blinker_auth_code"; // 从Blinker APP中获取的认证码
char ssid[] = "wifi_ssid"; // WiFi名称
char pswd[] = "wifi_password"; // WiFi密码

// 定义引脚
const int in1 = 5;  // D1
const int in2 = 4;  // D2
const int in3 = 0;  // D3
const int in4 = 2;  // D4

// 定义按钮对象，注意：按钮名称要和Blinker APP中配置的按钮名称一致
BlinkerButton ButtonForward("btn-forward");
BlinkerButton ButtonBackward("btn-backward");
BlinkerButton ButtonLeft("btn-left");
BlinkerButton ButtonRight("btn-right");
BlinkerButton ButtonStop("btn-stop");

void setup(){
  Serial.begin(115200);
  BLINKER_DEBUG.stream(Serial);
  Blinker.begin(auth, ssid, pswd);
  // 设置引脚为输出模式
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // *** 重要！将按钮对象与它的回调函数关联起来 ***
  ButtonForward.attach(forwardCallback);
  ButtonBackward.attach(backwardCallback);
  ButtonLeft.attach(leftCallback);
  ButtonRight.attach(rightCallback);
  ButtonStop.attach(stopCallback);
}

void forwardCallback(const String & state) {
  // 控制台输出日志，方便调试
  BLINKER_LOG("get button state: ", state); 

  // state 是按钮的状态，当按住时前进，松开时停止
  if (state == BLINKER_CMD_BUTTON_PRESSED) {
    moveForward();      // 按钮被“按住”：小车前进
  } else if (state == BLINKER_CMD_BUTTON_RELEASED) {
    stopMove();        // 按钮被“放开”：小车停止
  }
  // 关键！将ESP8266端的按钮状态同步回App[reference:9]
  ButtonForward.print(state); 
}

void backwardCallback(const String & state) {
  BLINKER_LOG("get button state: ", state); 
  
  if (state == BLINKER_CMD_BUTTON_PRESSED) {
    moveBackward();
  } else if (state == BLINKER_CMD_BUTTON_RELEASED) {
    stopMove();
  }
  ButtonBackward.print(state); 
}

void leftCallback(const String & state) {
  BLINKER_LOG("get button state: ", state); 
  
  if (state == BLINKER_CMD_BUTTON_PRESSED) {
    turnLeft();
  } else if (state == BLINKER_CMD_BUTTON_RELEASED) {
    stopMove();
  }
  ButtonLeft.print(state); 
}

void rightCallback(const String & state) {
  BLINKER_LOG("get button state: ", state); 
  
  if (state == BLINKER_CMD_BUTTON_PRESSED) {
    turnRight();
  } else if (state == BLINKER_CMD_BUTTON_RELEASED) {
    stopMove();
  }
  ButtonRight.print(state); 
}

void stopCallback(const String & state) {
  BLINKER_LOG("get button state: ", state); 
  
  if (state == BLINKER_CMD_BUTTON_TAP) {
    stopMove();
  }
  ButtonRight.print(state); 
}

// 定义动作函数
void moveForward() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
}
void moveBackward() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}
void turnRight() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}
void turnLeft() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
}
void stopMove() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
}

void loop() {
  Blinker.run(); // 运行Blinker库，处理按钮状态
}
```

#### 上传代码

使用数据线将 ESP8266 开发板连接到电脑，然后在 Arduino 中点击 `上传` 按钮，将代码上传到 ESP8266 开发板上，等待上传完成。

上传完成后，点击开发板上复位按钮，等待开发板重新启动接入WiFi，然后就可以在 Blinker APP 中看到设备在线了。

### 测试

断开开发板和电脑的连接，将 18650 电池安装到电池盒中，等待开发板上电完成，在 Blinker APP 中查看设备是否在线。

等到设备在线后，按住 APP 中的前进按钮，小车开始前进，说明功能正确。依次测试其它按钮功能，确认是否正常。


### 参考资料

- 点灯科技官网：<https://diandeng.tech/home> 
- 点灯科技WiFi按钮示例代码：<https://github.com/blinker-iot/blinker-library/blob/master/examples/Blinker_Widgets/Blinker_Button/Button_WiFi/Button_WiFi.ino> 


### 总结

通过这个项目，学习到了 L298N 驱动电机的使用方法，以及如何使用 Blinker 库实现 WiFi 远控小车的功能。
