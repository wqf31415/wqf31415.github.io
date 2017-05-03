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

### 第一个 Demo
```html
<script src="http://onrk0ex3b.bkt.clouddn.com/angular/angular.min.js"></script>
<div ng-app="">
     <p>名字 : <input type="text" ng-model="name"></p>
     <p>名字：<span ng-bind="name"></span></p>
</div>
```
<div ng-app=""><p>名字 : <input type="text" ng-model="name"></p><p>名字：<span ng-bind="name"></span></p></div>


------


### 