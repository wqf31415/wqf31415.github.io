---
title: 前端矢量化图库RaphaelJs入门
tags:
  - js
  - 前端
  - 可视化
  - 库
categories:
  - js
date: 2023-01-05 21:52:48
---

### 概述

这篇文章介绍了一种前端绘制矢量化图形的 js 库——RaphaelJs，文章阐述了 Raphael 中的基础概念，展示了一些基础的用法示例。



### 关于 Raphael

Raphael (读音：['ræfeɪəl]， <small>猜测原意为拉斐尔，意大利文艺复兴时期著名画家</small>)，Raphael 是一个开源的、轻量易用的、跨浏览器的前端矢量绘图工具库。Raphael 基于 SVG 与 VML 实现图形绘制，所有使用 Raphael 绘制的图形对象同时也是 DOM 对象，可以修改它们或给它们添加 JavaScript 事件处理函数。Raphael 设计目标是跨浏览器和易用，现已支持的浏览器包括 Firefox 3.0+、Safari 3.0+、Chrome 5.0+、Opera 9.5+、Internet Explorer 6.0+。

> 官网：<https://dmitrybaranovskiy.github.io/raphael/> 
>
> Github: <https://github.com/DmitryBaranovskiy/raphael> 
>
> 下载：<https://github.com/DmitryBaranovskiy/raphael/releases> 



<!-- more -->

### Raphael 概念及函数接口

#### Paper(画纸)

也可称为画布，是绘制图形的基础容器，用于绘制基础图形，如圆形、椭圆形、矩形、路径等，或用于创建集合（`paper.set()`）。此外 paper 中还提供了一些工具函数，如清空画纸（`paper.clear()`）、遍历元素（`paper.forEach()`）、获取元素（`paper.getById()`）等。

使用 `Raphael()` 函数创建画纸：

```javascript
// 方法一
// 指定画布的父元素节点创建，函数参数：
// 父元素的dom节点，使用 document.getElementById('view') 获取了id为 view 的节点
// 画布宽度 300
// 画布高度 200
var paper = Raphael(document.getElementById('view'), 300, 200);

// 方法二
// 或指定画布父元素ID创建，实现的效果与上面的一致
var paper = Raphael('view', 300, 200);
```

`Raphael()` 函数最多可以接收 6 个参数：

- container： 画布的容器，可选值为 dom 节点或节点 id 值
- x：起始点 x 坐标
- y：起始点 y 坐标
- width：画布宽度
- height：画布宽度
- callback：画布创建成功后的回调函数



##### 画纸绘图函数

| 函数                                                 | 说明     | 参数                                                         | 返回值                             |
| ---------------------------------------------------- | -------- | ------------------------------------------------------------ | ---------------------------------- |
| `circle(x, y, radius)`                               | 绘制圆形 | 圆形 x 坐标、圆心 y 坐标，半径                               | 类型为 circle 的 Raphael 元素对象  |
| `ellipse(x, y, horizontalRadius, verticalRadius)`    | 绘制椭圆 | 圆心 x 坐标、圆心 y 坐标、水平方向半径、垂直方向半径         | 类型为 ellipse 的 Raphael 元素对象 |
| `rect(x, y, width, height, radiusForRoundedCorners)` | 绘制矩形 | 左上角 x 坐标、左上角 y 坐标、宽度、高度、圆角半径（可不填，默认值为 0） | 类型为 rect 的 Raphael 元素对象    |
| `path(pathString)`                                   | 绘制路径 | SVG 路径字符串                                               | 类型为 path 的 Raphael 元素对象    |
| `image(src, x, y, width, height)`                    | 绘制图像 | 图像链接、左上角 x 坐标、左上角 y 坐标、宽度、高度           | 类型为 image 的 Raphael 元素对象   |
| `text(x, y, text)`                                   | 绘制文本 | 起始位置 x 坐标、起始位置 y 坐标、文本内容                   | 类型为 text 的 Raphael 元素对象    |



##### 画纸功能函数

| 函数                            | 说明                                                         | 参数                                                         | 返回值           |
| ------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ---------------- |
| `clear()`                       | 清空画纸                                                     | 无                                                           | 无               |
| `forEach(callback, contextObj)` | 遍历元素                                                     | 遍历回调函数、上下文对象                                     | paper 对象       |
| `getById(id)`                   | 按id查找元素                                                 | 元素ID                                                       | Raphael元素对象  |
| `getElementByPoint(x, y)`       | 查找指定坐标点的元素(最上层的)                               | x坐标、y坐标                                                 | Raphael元素对象  |
| `remove()`                      | 从dom中移除画纸                                              | 无                                                           | 无               |
| `set()`                         | 创建集合                                                     | 无                                                           | Raphael 集合对象 |
| `setSize(width, height)`        | 修改画纸尺寸                                                 | 画纸新宽度、高度                                             | 无               |
| `setStart()`                    | 集合记录开始，<small>从此函数开始到 `setFinish()` 函数中间绘制的元素添加并创建一个集合</small> | 无                                                           | 无               |
| `setFinish()`                   | 集合记录结束                                                 | 无                                                           | Raphael 集合对象 |
| `setViewBox(x, y, w, h, fit)`   | 设置画纸的视图框，<small>可用于缩放画纸</small>              | 新的 x 位置、<br>新的 y 位置、<br>宽度、<br>高度、<br>图形是否适配新的视图框 | 无               |



#### Element(图形元素)

使用 paper 提供的函数绘制的图形，包括圆形（circle）、椭圆形（ellipse）、矩形（rect）、路径（path）、文本（text）。



##### 图形元素的主要属性

| 属性      | 类型   | 说明                                                         |
| --------- | ------ | ------------------------------------------------------------ |
| `id`      | number | 元素ID，可用于函数 `getById()` 查找元素                      |
| `next`    | object | 元素的层级关系的下一个元素                                   |
| `prev`    | object | 元素层级关系的上一个元素                                     |
| `node`    | object | 元素的DOM对象<small>(因此你可以为其指定事件处理函数)</small> |
| `paper`   | object | 元素所在的画纸对象                                           |
| `raphael` | object | raphael 对象                                                 |



##### 图形元素控制函数

| 函数                          | 说明                                                         | 参数                                                         | 返回值                                                       |
| ----------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `attr(…)`                     | 获取<small>(传参数名或参数名数组时)</small>或修改<small>(传参数名与值或传参数对象时)</small>元素属性值 | 1. 无参;<br>2. 参数名;<br>3. 参数名与参数值;<br>4. 属性对象;<br>5. 参数名数组; | 1. 无参时返回元素对象自身;<br>2. 传参数名时返回参数值;<br>3. 传参数名与值时返回元素对象;<br>4. 传属性对象时返回元素对象;<br>5. 传参数名数组时返回参数值数组; |
| `clone()`                     | 克隆当前元素                                                 | 无                                                           | 克隆的元素对象                                               |
| `data(key, [value])`          | 查询<small>(只传key参数时)</small>或设置<small>(传key与value参数时)</small>元素附带的数据 | 1. 数据名;<br>2. 数据名与值                                  | 1. 传数据名时返回该数据的值;<br>2. 传数据名与值时返回元素对象; |
| `getBBox(isWithoutTransform)` | 获取图形元素占据的区域框                                     | 是否获取变形前的区域框                                       | 包含图形区域框的起始点坐标与宽高的对象                       |
| `getPointAtLength(length)`    | 获取指定长度的点的坐标(仅path可用)                           | 长度                                                         | 包含点坐标与角度的对象                                       |
| `getSubpath(from, to)`        | 获取指定位置间的路径(仅path可用)                             | 开始位置、结束位置                                           | 路径字符串(pathString)                                       |
| `getTotalLength()`            | 获取路径总像素长度(仅path可用)                               | 无                                                           | 路径像素长度值                                               |
| `glow([glow])`                | 返回光晕效果的元素集合                                       | 光晕效果参数对象                                             | 集合对象                                                     |
| `hide()`                      | 隐藏元素                                                     | 无                                                           | 元素对象本身                                                 |
| `insertAfter()`               | 将当前元素插入到指定元素后                                   | 元素对象                                                     | 当前元素对象                                                 |
| `insertBefore()`              | 将当前元素插入到指定元素前                                   | 元素对象                                                     | 当前元素对象                                                 |
| `remove()`                    | 移除元素                                                     | 无                                                           | 无                                                           |
| `removeData([key])`           | 移出元素数据                                                 | 要移出的数据key                                              | 元素对象                                                     |
| `rotate(deg, [cx], [cy])`     | 旋转元素                                                     | 角度、旋转中心x坐标、旋转中心y坐标                           | 元素对象                                                     |
| `scale(sx, sy, [cx], [cy])`   | 缩放元素                                                     | 水平缩放尺度、垂直缩放尺度、缩放中心x坐标、缩放中心y坐标     | 元素对象                                                     |
| `show()`                      | 显示图形元素                                                 | 无                                                           | 元素对象                                                     |
| `toBack()`                    | 移至底层                                                     | 无                                                           | 元素对象                                                     |
| `toFront()`                   | 移至顶层                                                     | 无                                                           | 元素对象                                                     |
| `transform([tstr])`           | 元素变形                                                     | 1. 无参数;<br />2. 变形字符串;                               | 1. 元素的变形字符串;<br />2. 元素对象;                       |
| `translate(dx, dy)`           | 移动元素                                                     | 水平移动距离、垂直移动距离                                   | 元素对象                                                     |



##### 图形元素的事件处理器函数

| 函数                                                         | 说明                         | 参数                                                         | 返回值   |
| ------------------------------------------------------------ | ---------------------------- | ------------------------------------------------------------ | -------- |
| `click(handler)`                                             | 设置对象的鼠标点击事件处理器 | 处理点击事件的函数，该函数可接受3个参数：event、x、y         | 元素对象 |
| `dblclick(handler)`                                          | 设置对象的鼠标双击事件处理器 | 处理双击事件的函数，该函数可接受3个参数：event、x、y         | 元素对象 |
| `drag(onmove, onstart, onend, [mcontext], [scontext], [econtext])` | 设置鼠标拖拽事件处理器       | 1. 移动过程中的事件处理函数(x,y,event);<br>2. 拖拽开始事件处理函数(dx,dy,x,y,event);<br>3. 拖拽结束事件处理函数(event);<br>4. 拖拽过程函数上下文;<br>5. 拖拽开始函数上下文;<br>6. 拖拽结束函数上下文; | 元素对象 |
| `hover(f_in, f_out, [icontext], [ocontext])`                 | 设置鼠标悬停事件             | 1. 鼠标移入事件处理函数;<br>2. 鼠标移出事件处理函数;<br>3. 鼠标移入函数上下文;<br>4. 鼠标移出函数上下文; | 元素对象 |
| `mousedown(handler)`                                         | 设置鼠标按下事件处理函数     | 鼠标按下事件处理函数                                         | 元素对象 |
| `mousemove(handler)`                                         | 设置鼠标拖动事件处理函数     | 鼠标拖动事件处理函数                                         | 元素对象 |
| `mouseout(handler)`                                          | 设置鼠标移出事件处理函数     | 鼠标移出事件处理函数                                         | 元素对象 |
| `mouseover(handler)`                                         | 设置鼠标滑过事件处理函数     | 鼠标滑过事件处理函数                                         | 元素对象 |
| `mouseup(handler)`                                           | 设置鼠标抬起事件处理函数     | 处理函数                                                     | 元素对象 |
| `onDragOver(f)`                                              | 设置元素拖过事件处理函数     | 处理函数                                                     | 元素对象 |
| `touchcancel(handler)`                                       | 设置触摸取消事件处理函数     | 处理函数                                                     | 元素对象 |
| `touchend(handler)`                                          | 设置触摸事件处理函数         | 处理函数                                                     | 元素对象 |
| `touchmove(handler)`                                         | 设置触摸移动事件处理函数     | 处理函数                                                     | 元素对象 |
| `touchstart(handler)`                                        | 设置触摸开始事件处理函数     | 处理函数                                                     | 元素对象 |
| `unclick(handler)`                                           | 移除点击事件处理函数         | 处理函数                                                     | 元素对象 |
| `undblclick(handler)`                                        | 移除双击事件处理函数         | 处理函数                                                     | 元素对象 |
| `undrag()`                                                   | 移除所有拖拽事件处理函数     | 处理函数                                                     | 元素对象 |
| `unhover(f_in, f_out)`                                       | 移除鼠标悬停事件处理函数     | 处理函数                                                     | 元素对象 |
| `unmousedown(handler)`                                       | 移除鼠标按下事件处理函数     | 处理函数                                                     | 元素对象 |
| `unmousemove(handler)`                                       | 移除鼠标移动事件处理函数     | 处理函数                                                     | 元素对象 |
| `unmouseout(handler)`                                        | 移除鼠标移出事件处理函数     | 处理函数                                                     | 元素对象 |
| `unmouseover(handler)`                                       | 移除鼠标滑过事件处理函数     | 处理函数                                                     | 元素对象 |
| `unmouseup(handler)`                                         | 移除鼠标按键抬起事件处理函数 | 处理函数                                                     | 元素对象 |
| `untouchcancel(handler)`                                     | 移除触摸取消事件处理函数     | 处理函数                                                     | 元素对象 |
| `untouchend(handler)`                                        | 移除触摸事件处理函数         | 处理函数                                                     | 元素对象 |
| `untouchmove(handler)`                                       | 移除触摸移动事件处理函数     | 处理函数                                                     | 元素对象 |
| `untouchstart(handler)`                                      | 移除触摸开始事件处理函数     | 处理函数                                                     | 元素对象 |



##### 图形元素动画函数

| 函数                      | 说明               | 参数                                                         | 返回值                                                       |
| ------------------------- | ------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `pause([anim])`           | 暂停元素动画       | 要暂停的动画对象                                             | 元素对象                                                     |
| `resume([anim])`          | 恢复暂停的动画     | 要恢复的动画对象                                             | 元素对象                                                     |
| `setTime(anim, value)`    | 设置动画时间       | 动画对象、时间(ms)                                           | 元素对象                                                     |
| `status([anim], [value])` | 设置或获取动画状态 | 1. 无参数;<br />2. 动画对象;<br />3. 动画对象、状态值(0\~1); | 1. 动画及状态的对象数组;<br />2. 动画状态值;<br />3. 元素对象； |
| `stop([anim])`            | 停止动画           | 动画对象                                                     | 元素对象                                                     |



#### Set(集合)

多个图形元素组合成一个集合，使用 `paper.set()` 函数创建，或使用 `paper.setStart()` 配合 `paper.setFinish()` 函数创建。创建集合后可使用 `set.push()` 添加元素、使用 `set.forEach()` 遍历元素、使用 `set.clear()` 清除集合，可以方便的对集合中的元素进行控制，如修改集合元素的填充颜色：

```javascript
let paper = Raphael('view', 300, 200);
let set = paper.set(); // 创建集合
set.push(paper.circle(100,100, 50)); // 添加元素
set.push(paper.circle(200,100, 50)); // 添加元素
set.attr('fill', 'red'); // 设置集合元素的填充颜色为红色 red
```

效果：

<svg height="200" version="1.1" width="300" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" style="overflow: hidden; position: relative;"><desc style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Created with Raphaël 2.3.0</desc><defs style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></defs><circle cx="100" cy="100" r="50" fill="#ff0000" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="200" cy="100" r="50" fill="#ff0000" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle></svg>



##### 集合提供的函数

| 函数                                   | 说明                                                         | 参数                                 | 返回值           |
| -------------------------------------- | ------------------------------------------------------------ | ------------------------------------ | ---------------- |
| `clear()`                              | 清空集合                                                     | 无                                   | 无               |
| `exclude(element)`                     | 移除元素                                                     | 要移除的元素对象                     | 移除结果 boolean |
| `forEach(callback, contextObj)`        | 遍历元素                                                     | 遍历回调函数、给回调函数的上下文对象 | Raphael集合对象  |
| `pop()`                                | 移除最后一个元素并返回它                                     | 无                                   | Raphael元素对象  |
| `push(element)`                        | 添加元素到集合                                               | 要添加的Raphael元素对象              | 添加的原始对象   |
| `splice(index, count, [insertion...])` | 移除从 index 开始的 count 个元素，并返回它们，然后插入元素 insertion | 索引、元素数量、要添加的元素         | 删除的元素       |



#### Animation(动画)

动画对象，使用 `Raphael.animation(params, ms, [easing], [callback])` 创建，可以传递给图形元素的 `element.animate()` 或 `element.animateWith()` 函数，给图形元素添加动画效果。



##### 动画对象函数

| 函数             | 说明                                 | 参数                               | 返回值         |
| ---------------- | ------------------------------------ | ---------------------------------- | -------------- |
| `delay(delay)`   | 为动画对象创建一个延迟的拷贝动画对象 | 延迟时间(ms)                       | 拷贝的动画对象 |
| `repeat(repeat)` | 为动画创建一个循环播放的拷贝动画对象 | 循环次数，传 `Infinity` 则不停循环 | 拷贝的动画对象 |



#### Matrix(矩阵)

矩阵，使用 `Raphael.matrix(a, b, c, d, e, f)` 函数创建，或使用 `element.matrix` 获取元素的矩阵。

矩阵是实现高级动画、变形效果的工具，可以参考 CSS3 的矩阵变换。



##### 矩阵提供的函数

| 函数                            | 说明                            | 参数    | 返回值             |
| ------------------------------- | ------------------------------- | ------- | ------------------ |
| `add(a, b, c, d, e, f, matrix)` | 添加给定的矩阵到已有矩阵        |         |                    |
| `clone()`                       | 拷贝矩阵                        | 无      | 拷贝的矩阵对象     |
| `invert()`                      | 逆矩阵                          | 无      | 返回逆矩阵对象     |
| `rotate(a, x, y)`               | 旋转矩阵                        | a、x、y | 无                 |
| `scale(x, [y], [cx], [cy])`     | 缩放矩阵                        |         | 无                 |
| `split()`                       | 分裂矩阵，转为原始的变形数据    | 无      | 包含变形信息的对象 |
| `toTransformString()`           | 转换成变形字符串                | 无      | 变形字符串         |
| `translate(x, y)`               | 转换矩阵                        | x、y    | 无                 |
| `x(x, y)`                       | 返回给定点经过矩阵变换后的x坐标 | x、y    | x 坐标             |
| `y(x, y)`                       | 返回给定点经过矩阵变换后的y坐标 | x、y    | y 坐标             |



#### 路径字符串(path string)

>用于描述路径的字符串，格式为命令（command）+ 参数，多命令依次追加。
>
>示例：`M10,30L30,40` 、`M10 20L10 40` 
>
>参考 w3.org 的 svg path 标准: <https://www.w3.org/TR/SVG/paths.html#PathElement> 
>
>| 命令 | 名称                                                         | 参数                                                |
>| ---- | ------------------------------------------------------------ | --------------------------------------------------- |
>| M    | 移动到(moveto)                                               | `(x y)+`                                            |
>| Z    | 闭合路径(closePath)                                          | 无                                                  |
>| L    | 连线到(lineto)                                               | `(x y)+`                                            |
>| H    | 水平连线到(horizontal lineto)                                | `x+`                                                |
>| V    | 垂直连线到(vertial lineto)                                   | `y+`                                                |
>| C    | 曲线连线(curveto)                                            | `(x1 y1 x2 y2 x y)+`                                |
>| S    | 平滑曲线连线(smooth curveto)                                 | `(x2 y2 x y)+`                                      |
>| Q    | 贝塞尔曲线连线(quadratic bezier curveto)                     | `(x1 y1 x y)+`                                      |
>| T    | 平滑贝塞尔曲线连线(smooth quadratic bezier curveto)          | `(x y)+`                                            |
>| A    | 弧线(elliptical arc)                                         | `(rx ry x-axis-rotation large-arc-flag sweep x y)+` |
>| R    | [ Catmull-Rom](http://en.wikipedia.org/wiki/Catmull–Rom_spline#Catmull.E2.80.93Rom_spline) 曲线 | `x1 y1 (x y)+`                                      |



#### 变形字符串(transformation string)

用于描述图形变形效果的字符串，格式与路径字符串相似，有四个命令字符：

| 命令 | 说明            | 参数               |
| ---- | --------------- | ------------------ |
| `t`  | 移动(translate) | dx, dy             |
| `r`  | 旋转(rotate)    | deg, [cx], [cy]    |
| `s`  | 缩放(scale)     | sx, sy, [cx], [cy] |
| `m`  | 矩阵(matrix)    | a, b, c, d, e, f   |



示例：

```
t100,100r30,100,100s2,2,100,100r45s1.5
```

实现效果为：移动 100,100 ；以 (100,100) 为中心旋转 30 度；以 (100,100) 为中心缩放 2 倍；以自身中心旋转 45 度；按自身中心缩放 1.5 倍。



### 使用示例

#### 快速开始

```html
<!DOCTYPE html>
<html lang="zh">
<head>
    <meta charset="UTF-8">
    <title>Raphael 快速开始</title>
    <script src="raphael.min.js"></script>
</head>
<body>
<div id="view"></div>
<script>
    // 创建画布, 宽 300， 高 200
    const paper = Raphael('view', 300, 200);
    // 绘制圆形, 圆心坐标(150,100), 半径 50
    let circle = paper.circle(150, 100, 50);
    // 圆形填充为红色(red)
    circle.attr('fill', 'red');
    // 给圆形添加点击事件处理函数, 实现点击切换颜色
    circle.click(function (pointerEvent , x, y) {
        if (this.attr('fill') === 'red') {
            // 获取圆形填充属性值，值为 red 时，设置填充颜色为蓝色 blue
            this.attr('fill', 'blue');
        } else {
            // 否则设置填充颜色为红色 red
            this.attr('fill', 'red');
        }
    });
</script>
</body>
</html>
```



### 总结

RaphaelJs 是一个偏底层基础的矢量绘图库，支持绘制的图形包括圆形、椭圆、矩形、路径、文字，支持的交互事件包括点击、双击、拖拽、鼠标悬停、鼠标移入移出等，支持动画效果，支持设置修改 svg 标准属性，支持创建图形集合。RaphaelJs 能够完成最基础图形绘制功能，如果要实现复杂的图形绘制就需要自己编码和封装，比如要实现统计图，就需要自己绘制坐标轴，这需要根据数据计算坐标轴的位置、长度，绘制坐标轴上的刻度等等，如果要实现绘制图形的自适应就需要更多的编码和封装了。Raphael 的官网提供了很多精美的示例，实现了很酷炫的效果，但没提供代码，所以学习起来不太方便，只能看 api 文档，自己摸索，因此我把自己摸索的成果写成了这篇文章，记录下来将来使用时有所参考。

本文示例: <a href="/example/raphaeljs/">/example/raphaeljs/</a> 



### 参考资料

