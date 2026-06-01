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



### 核心



<!-- more ->

### 物料



### 原理



### 代码



```c++

#define BLINKER_WIFI
#include <Blinker.h>

// 填写你的WiFi信息和秘钥
char auth[] = "blinker_auth_code";
char ssid[] = "wifi_ssid";
char pswd[] = "wifi_password";
// 定义引脚
const int in1 = 5;  // D1
const int in2 = 4;  // D2
const int in3 = 0;  // D3
const int in4 = 2;  // D4

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
  Blinker.run();
}
```





### 测试



### 参考资料

- 点灯科技官网：<https://diandeng.tech/home> 
- 点灯科技WiFi按钮示例代码：<https://github.com/blinker-iot/blinker-library/blob/master/examples/Blinker_Widgets/Blinker_Button/Button_WiFi/Button_WiFi.ino> 

### 总结

