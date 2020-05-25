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

### 概述

初步接触 AngularJS ，这篇文章记录了学习 AngularJS 的一些心得，文章内容包括 AngularJS 的特点以及简单的使用示例。


<script src="http://javascript.qiniu.wqf31415.xyz/angular/angular.min.js"></script>
### 第一个 Demo 体验 Angular 的双向数据绑定

```html
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<script src="http://javascript.qiniu.wqf31415.xyz/angular/angular.min.js"></script>
	</head>
	<body>
		<div ng-app="">
			<p>名字 : <input type="text" ng-model="name"></p>
			<h1>你好，{{name}}</h1>
		</div>
	</body>
</html>
```

<iframe src="http://demo.x99.ink/angularJSDemo/1.html" name="iframe_a" style="border: 1px solid #ccc"></iframe>
<!-- more -->

------


### 下定义，一句话说明 AngularJS 是什么

AngularJS 是一个 js 框架，用于开发动态 web 应用。AngularJs 可以使用 HTML 作为模板语言，使用Angular 指令扩展 HTML 语法，使用组件化开发使系统结构更加简洁清晰，通过数据绑定和依赖注入减少了大量代码。

AngularJS 最大的特点包括： **MVC模式** ， **模块化** ， **双向数据绑定** ， **依赖注入**

![](http://blog-images.qiniu.wqf31415.xyz/AngularJS-Shield.svg "AngularJS") 



### 同类产品

#### Vue.js

> 官网：<https://cn.vuejs.org/> 

> Vue 是一套用于构建用户界面的渐进式框架。与其它大型框架不同的是，Vue 被设计为可以自底向上逐层应用。Vue 的核心库只关注视图层，不仅易于上手，还便于与第三方库或既有项目整合。



### AngularJs 重要概念

#### 指令（Directive）

指令就是一些附加在 html 元素上的自定义标记（如属性、元素或 css 类），它告诉 angularJs 的 html 编译器（$compile）在元素上附加某些指定的行为，甚至操作 DOM、改变 DOM 元素，以及它的各级子节点。

<span style="background:#ffa">AngularJs 中内置了一整套指令，内置的指令都带有前缀 `ng-` </span>，如 `ng-app` 、`ng-init` 、`ng-model` 等。

```html
<div ng-app="" ng-init="name='Tom'">
    <p>姓名：<input type="text" ng-model="name"/></p>
	<p>你输入的是：{{name}}</p>
</div>
```

> `ng-app` 指令初始化一个 AngularJs 应用程序；
>
> `ng-init` 指令初始化应用程序数据；
>
> `ng-model` 指令把元素值绑定到应用程序。

同时 <span style="background:#ffa">AngularJs 允许用户自定义指令，自定义指令可以在元素、属性、类名、注释中使用。</span> 例如：

```html
<body ng-app="myApp">
    <!-- html 元素 -->
    <my-directive></my-directive>
    <!-- 属性 -->
    <div my-directive></div>
    <!-- 类名 -->
    <div class="my-directive"></div>
    <!-- 注释 -->
    <!-- directive: my-directive -->
</body>
<script>
    var app = angular.module("myApp",[]);
    app.directive("myDirective",function(){
        return {
            restrict : "EACM",
            replace : true,
            template: "<h2>我的自定义指令</h2>"
        };
    });
</script>
```

> 如上所示，创建了一个名为 `myDirective` 的指令，在使用的时候需要使用 `my-directive` 来引用指令。
>
> 返回结果：
>
> - `restrict` ：指定该指令可以使用的范围，默认为 `EA` 即元素和属性，`E` 表示元素（Element），`A` 表示属性（Attribute），`C` 表示类名（Class），`M` 表示注释（Comment）。
> - `replace` ：指定指令替换原标签，当指令使用在注释中时，需要将这个字段设定为 true 才能生效。
> - `template` ：即为指令模板，将把内容解析到视图中展示出来。



#### 表达式（Expression）

表达式是一种类似 JavaScript 的代码片段，通常在视图中以双大括号 `{{expression}}` 形式使用，表达式由 `$parse` 服务解析，解析之后经常会使用过滤器来格式化成一种更加用户友好的形式。

AngularJs 表达式可以包含文字、运算符、变量，如 `{{1 + 2}}` 、`{{firstName + " " + lastName}}` ，还可以使用数组 `{{ arr[2] }}` 。



#### 模块（Module）

AngularJs 模块定义了一个应用程序，是应用程序中不同部分的容器，是应用控制器的容器，控制器一般属于一个模块。

通过 `angular.module("moduleName", [])` 来创建模块，即一个应用，可以在这个模块中添加控制器、服务、指令、过滤器等。如：

```html
<div ng-app="myApp" ng-controller="myCtrl">
    {{firstName + " " + lastName}}
</div>
<script>
	var app = angular.module("myApp",[]);
    app.controller("myCtrl", function($scope){
        $scope.firstName = "San";
        $scope.lastName = "Zhang";
    });
</script>
```



#### 作用域（Scope）

作用域是一个存储应用数据模型的对象，有可用的方法和属性，作为视图（html）和控制器（javascript）之间的纽带，为表达式提供一个执行上下文，作用域的层级结构对应于 DOM 树结构，作用域可以监听表达式的变化并传播事件。

作用域中可以添加自定义的方法，同时 Angular 也提供了一些自带的方法：

- `$watch` 方法监听数据模型变化；
- `$apply` 方法把不是由 Angular 触发的数据模型的改变引入 Angular 的控制范围内，如控制器、服务、Angular 事件处理器等；

示例：

```html
<body ng-app="myApp" ng-controller="myCtrl">
    <input type="text" ng-model="name" />
    <button ng-click="sayHi()">Say Hi</button>
    <p>{{msg}}</p>
</body>
<script>
    var app = angular.module("myApp",[]);
    app.controller("myCtrl",function($scope){
        $scope.name = "Tom";
        $scope.sayHi = function(){
            $scope.msg = "Hi, " + $scope.name;
        }
    });
</script>
```



#### 控制器（Controller）

AngularJs 控制器是一个常规的 JavaScript 对象，用来增强 Angular 的作用域。当一个控制器通过 `ng-controller` 指令添加到 DOM 中时，ng 会调用该控制器的构造函数来生成一个控制器对象，这样就创建了一个新的子级作用域（scope）。在这个构造函数中，作用域（scope）会作为 `$scope` 参数注入其中，并允许用户代码访问它。

在控制器中可以初始化 `$scope` 对象，还可以为 `$scope` 对象添加方法、属性。



#### 过滤器（Filter）

过滤器用来格式化表达式中的值，如格式化日期时间显示格式、取两位小数等，过滤器可以用在视图模板（templates）、控制器（controllers）或服务（services）中。

过滤器的使用方式是：`{{ expression | filter }}` ，过滤器支持链式使用：`{{ expression | filter1 | filter2 }}` 

##### AngularJs 过滤器

| 过滤器    | 描述                                           | 示例                                                         |
| --------- | ---------------------------------------------- | ------------------------------------------------------------ |
| currency  | 格式化数字为货币格式，如果不加参数，默认为 `$` | ``{{num|currency:"￥"}}``                                    |
| date      | 日期格式化                                     | ``{{dateObj|date:'yyyy-MM-dd hh:mm:ss'}}``                   |
| filter    | 从数组中选择出符合条件的子集                   | ``{{arr|filter:'d'}}`` 选出数组中含有字母 `d` 的元素，并以数组形式返回 |
| json      | 格式化json对象                                 | ``{{jsonStr|json}}``                                         |
| limitTo   | 限制数组长度或字符串长度                       | ``{{arr|limitTo:'3'}}``                                      |
| lowercase | 格式化字符串为小写                             | ``{{str|lowercase}}``                                        |
| uppercase | 格式化字符串为大写                             | ``{{str|uppercase}}``                                        |
| number    | 格式化数字                                     | ``{{num|number:2}}`` 保留2位小数                             |
| orderBy   | 根据某个表达式排列数组                         | ``{{arr|orderBy:'age':true}}`` 按 `age` 属性从大到小排序     |

##### 自定义过滤器

AngularJs 支持自定义过滤器，使用 `filter` 方法给模块添加过滤器。

示例：

```html
	<body ng-app="myApp" ng-controller="myCtrl">
		<p>数字：{{score|number:2}}</p>
		<p>货币：{{money|currency:"￥"}}</p>
		<p>时间：{{time|date:'yyyy-MM-dd HH:mm:ss'}}</p>
		<p>数组：{{arr|filter:'c'}}</p>
		<p>JSON：{{obj|json}}</p>
		<p>限制长度：{{arr|limitTo:'2'}}</p>
		<p>小写：{{name|lowercase}}</p>
		<p>大写：{{name|uppercase}}</p>
		<p>排序：{{objArr|orderBy:'age':true}}</p>
		<p>自定义：{{name|hello}}</p>
	</body>
	<script>
		var app = angular.module("myApp",[]);
		app.filter("hello",function(){
			return function(text){
				return "hello " + text;
			}
		});
		app.controller("myCtrl",function($scope){
			$scope.money = 1024.32;
			$scope.time = new Date();
			$scope.arr = ["java","go","python","c","c++","c#","javascript","php","css","html"];
			$scope.obj = {
				name: "Tom",
				age: 18
			};
			$scope.objArr = [
				{name:"Tom",age:18},
				{name:"Jack",age:21},
				{name:"Licy",age:16},
				{name:"Rose",age:20},
			];
			$scope.name = "Tom";
			$scope.score = 745103;
		});
	</script>
```



#### 服务（Service）

AngularJs 中的服务是一个函数或对象，可以在 AngularJs 应用中使用。AngularJs 中内建了许多服务，也可以创建自己的服务。

##### 一些常用的服务

- `$http` 服务用于向服务器请求数据：

  ```javascript
  var app = angular.module("myapp",[]);
  app.controller("myApp", function($scope, $http){
      $http.get("/api/data").then(function(resp){
          $scope.data = response.data;
      });
  });
  ```

- `$timeout` 服务用于设置单次定时器：

  ```javascript
  angular.module('myApp',[])
  	.controller('myCtrl',function($scope, $timeout){
      	$timeout(function(){
              $scope.msg = "time is over!";
          },2000);
  });
  ```

- `$interval` 服务用于设置循环的定时器：

  ```javascript
  angular.module('myApp',[])
  	.controller('myCtrl', function($scope,$interval){
      	$scope.theTime = new Date();
      	$interval(function(){
              $scope.theTime = new Date();
          },1000);
  });
  ```

##### 自定义服务

```html
<body ng-app="myApp" ng-controller="myCtrl">
    <p>过滤器：{{name|hi}}</p>
    <p>
        <button ng-click="sayHi()">点击这里</button>
    	<p>{{time|date:'HH:mm:ss '}}{{msg}}</p>
    </p>
</body>
<script>
    var app = angular.module("myApp",[]);
    // 定义服务
    app.service("myService",function(){
        this.sayHi = function(name){
            return "Hi " + name;
        };
    });
    // 在过滤器中使用服务
    app.filter("hi",["myService",function(myService){
        return function(text){
            return myService.sayHi(text);
        }
    }]);
    // 在控制器中使用服务
    app.controller("myCtrl",function($scope, myService){
        $scope.name = "Tom";
        $scope.sayHi = function(){
            $scope.time = new Date();
            $scope.msg = myService.sayHi($scope.name);
        };
    });
</script>
```



### AngularJs 特点

#### MVC 设计

MVC : 即 Model Controller View 设计模式，Model 为数据模型，即视图中可用的数据；View 视图层，即 html 页面负责展示；Controller 为业务逻辑和控制逻辑，即 JavaScript 函数，可以添加或修改属性。使用 MVC 模式使开发职责清晰，代码分层模块化，方便复用。



#### 模块化

在 AngularJs 中，可以按业务逻辑分模块开发，降低耦合性，在单元测试时，可以只加载需要的模块。第三方的代码可以打包成可重用的模块轻松引入。

创建模块，使用 `angular.module("moduleName", [])` 创建名为 `moduleName` 的模块并重写已有的同名模块，参数 `[]` 中放的是模块所需的依赖，如果没有就写空数组，不能省略，因为 `angular.module('moduleName')` 用于获取已有的模块示例。示例：

```javascript
var myModule = angular.module('myModule',[]);
// 添加一些指令和服务
myModule.service('myService',...);
myModule.directive("myDirective",...);
```



#### 双向数据绑定

传统的模板系统中一般使用的都是单向数据绑定，将模板和数据合并起来加入到视图中，合并完成后，任何对数据模型或相关内容的改变都不会自动反应到视图中去，同时在视图中的改变也不会同步到数据模型中。

双向数据绑定是指视图和数据模型是双向绑定的，数据模型的变化会立即反应在视图上，而且在视图上的修改也同样立即改变数据模型。AngularJs 中模板是在浏览器中编译的，编译阶段生成了动态视图，保持动态视图从而实现了视图和数据模型的双向绑定。



#### 依赖注入

依赖注入（Dependency Injection）是指程序运行所依赖的对象（如系统模块、服务模块等）自动传递进来，不用自己创建，在需要的时候直接使用就行了。例如在控制器中注入依赖：

```javascript
angular
    .module('myApp') // 模块 myApp
	.controller("MyController",MyController); // 控制器 MyController

MyController.$inject = ['$scope','dep1','dep2']; // 注入依赖

function Mycontroller($scope,dep1,dep2){ // 控制器中直接使用
    //...
    $scope.aMethod = function(){
        //...
    }
    //...
}
```



#### 表单及验证

AngularJs 中提供了一些表单控件，也提供了表单验证的功能，在用户输入信息有误时进行提示。

示例：

```html
<!DOCTYPE html>
<html>
	<head>
		<title>AngularJs 表单及验证 Demo</title>
		<meta charset="utf-8">
		<script src="http://javascript.qiniu.wqf31415.xyz/angular/angular.min.js"></script>
	</head>
	<body ng-app="myApp" ng-controller="MyAppController">
		<div >
			<h2>表单验证</h2>
			<form name = "myForm" novalidate>
				<p>
					姓名:<br/>
					<input type="text" name="userName" ng-model="user.name" required />
					<span style="color:red" ng-show-"myForm.userName.$dirty && myForm.userName.$invalid>
						<span ng-show="myForm.userName.$error.required">姓名是必须的。</span>
					</span>
				</p>
				<p>
					邮箱：<br/>
					<input type="email" name="email" ng-model="user.email" required />
					<span style="color:red" ng-show="myForm.email.$dirty && myForm.email.$invalid">
						<span ng-show="myForm.email.$error.required">邮箱是必须的。</span>
						<span ng-show="myForm.email.$error.email">邮箱地址非法。</span>
					</span>
				</p>
				<p>
					性别：<br/>
					<input type="radio" name="gender" ng-model="user.gender" value="male" />男
					<input type="radio" name="gender" ng-model="user.gender" value="female" />女
					<input type="radio" name="gender" ng-model="user.gender" value="unknow" />保密
					
				</p>
				<p>
					喜欢的水果：<br>
					<input type="checkbox" value="apple" ng-model="user.fruit.apple">苹果</input>
					<input type="checkbox" value="banana" ng-model="user.fruit.banana">香蕉</input>
					<input type="checkbox" value="banpeachana" ng-model="user.fruit.peach">桃子</input>
				</p>
				<p>
					所在省：<br/>
					<select ng-model="user.province">
						<option value="SiChuan">四川</option>
						<option value="BeiJing">北京</option>
						<option value="ShangHai">上海</option>
					</select>
				</p>
				<button ng-click="save(user)" >保存</button>
				<button ng-click="reset()" >清除</button>
			</form>
		</div>
		<hr/>
		<p>用户信息：{{saveUser}}</p>
	</body>
	<script>
		angular
			.module('myApp',[])
			.controller('MyAppController',MyAppController);
		MyAppController.$inject = ['$scope'];
		function MyAppController($scope){
			var defaultUser = {
				name: 'Tom',
				email : 'tom@mail.com'
			};
			
			$scope.save=function(user){
				$scope.saveUser = angular.copy(user);
			}
			
			$scope.reset=function(){
				$scope.user=angular.copy(defaultUser);
			}
                                          
			$scope.reset();
		}
	</script>
</html>
```



### AngularJs 的一些问题

#### 双向数据绑定带来的性能问题

由于在 AngularJs 中实现了双向数据绑定，所以一旦绑定的数据变化，就会触发检查机制从而更新页面。当绑定的数据越来越多时，一个小小的改变就会引起整个页面的检查更新，降低了整体性能表现。

#### 太简单的路由功能

AngularJs 中的路由功能 ng-view 只能有一个，不能嵌套使用，如果要使用嵌套的路由只能使用第三方的库。

#### 作用域隔离

AngularJs 中作用域把执行环境和浏览器环境隔离开，浏览器原生事件不能直接作用于作用域，只能使用相应的指令实现。



### 参考资料

- AngularJS中文网：<https://www.angularjs.net.cn/> 
- 菜鸟教程AngularJs：<https://www.runoob.com/angularjs/angularjs-tutorial.html> 
- AngularJs过滤器：<https://www.cnblogs.com/zhen-prz/p/10525920.html> 



### 总结

这篇文章在2年后才完成，中间动都没动过，这样是非常不负责的，这段时间心态不对，太浮躁了，很多事都是开了个头，后来就没坚持下去，大多有头没尾。有的是没有时间，有的是担心做不好，后来学习了那句名言 `Done is batter than perfect.` 恍然大悟，有些时候，可能并不需要把事情做得完美，想做得好反而束手束脚，不如先把它做完，然后在这基础上去修改，去完善，这样至少有东西出来了。不是半吊子，要知道 1 和 0 的差别是质变！引以为戒，先把之前挖的坑尽力填上，然后才去开新坑！



