---
title: AngularJS 学习笔记1
tags:
  - Angular
  - 前端
categories:
  - 技术
date: 2017-05-03 13:41:21
---


> 摘要：初步认识 Angular ，写点 demo 来体验一下！



<script src="http://onrk0ex3b.bkt.clouddn.com/angular/angular.min.js"></script>
### 第一个 Demo 体验 Angular 的双向数据绑定
```html
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<script src="http://onrk0ex3b.bkt.clouddn.com/angular/angular.min.js"></script>
	</head>
	<body>
		<div ng-app="">
			<p>名字 : <input type="text" ng-model="name"></p>
			<h1>你好，{{name}}</h1>
		</div>
	</body>
</html>
```

<iframe src="http://wqf31415.coding.me/Demo/angularJSDemo/1.html" name="iframe_a" style="border: 1px solid #ccc"></iframe>
<!-- more -->
------


### 下定义，一句话说明 AngularJS 是什么

> AngularJS 是前端 javascript 框架，是以 javascript 编写的编写的库。

AngularJS 最大的四个特点是： **MVC模式** ， **模块化** ， **双向数据绑定** ， **依赖注入**

![](http://blog-images.qiniu.wqf31415.xyz/AngularJS-Shield.svg "AngularJS") 

MVC : 即 Model Controller View 设计模式，Model 为数据模型，View 视图层，负责展示，Controller 为业务逻辑和控制逻辑，使用 MVC 模式使开发职责清晰，代码模块化，方便复用。

### 







