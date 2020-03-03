---
title: AngularJS 学习笔记1
tags:
  - js
  - angular
  - 前端
categories:
  - js
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

- MVC : 即 Model Controller View 设计模式，Model 为数据模型，View 视图层，负责展示，Controller 为业务逻辑和控制逻辑，使用 MVC 模式使开发职责清晰，代码模块化，方便复用。
- 模块化
- 双向数据绑定
- 依赖注入



### 同类产品

- Vue.js



### AngularJs 特性



### 参考资料



### 总结

非常对不起自己，这篇文章在2年后才完成，中间动都没动过，这样是非常不负责的，这段时间心态不对，太浮躁了，很多事都是开了个头，后来就没坚持下去，大多有头没尾。有的是没有时间，有的是担心做不好，后来学习了那句名言 `Done is batter than perfect.` 恍然大悟，有些时候，可能并不需要把事情做得完美，想做得好反而束手束脚，不如先把它做完，然后在这基础上去修改，去完善，这样至少有东西出来了。不是半吊子，要知道 1 和 0 的差别是质变！引以为戒，先把之前挖的坑尽力填上，然后才去开新坑！



