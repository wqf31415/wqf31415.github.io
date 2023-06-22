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

这篇文章介绍了一个前端绘制矢量化图形的 js 库——RaphaelJs，文章阐述了 Raphael 中的基础概念，展示了一些基础的用法示例。



### 关于 Raphael

<svg height="200" version="1.1" width="600" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" style="overflow: hidden; position: relative; top: -0.6px;"><desc style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Created with Raphaël 2.3.0</desc><defs style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></defs><circle cx="100" cy="100" r="30" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><rect x="160" y="70" width="80" height="60" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><ellipse cx="300" cy="100" rx="40" ry="30" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></ellipse><path fill="none" stroke="#000000" d="M360,130L380,70L420,130L440,70" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><image x="460" y="70" width="80" height="60" preserveAspectRatio="none" xlink:href="/example/raphaeljs/cat.jpg" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></image><text x="100" y="150" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.200003147125244" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Circle</tspan></text><text x="200" y="150" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.200003147125244" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Rect</tspan></text><text x="300" y="150" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.200003147125244" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Ellipse</tspan></text><text x="400" y="150" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.200003147125244" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Path</tspan></text><text x="500" y="150" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.200003147125244" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Image</tspan></text></svg>

Raphael (读音：['ræfeɪəl]， <small>猜测原意为拉斐尔，意大利文艺复兴时期著名画家</small>)，Raphael 是一个开源的、轻量易用的、跨浏览器的前端矢量绘图工具库。Raphael 基于 SVG 与 VML 实现图形绘制，所有使用 Raphael 绘制的图形对象同时也是 DOM 对象，可以修改它们或给它们添加 JavaScript 事件处理函数。Raphael 设计目标是跨浏览器和易用，现已支持的浏览器包括 Firefox 3.0+、Safari 3.0+、Chrome 5.0+、Opera 9.5+、Internet Explorer 6.0+。

> 官网: <https://dmitrybaranovskiy.github.io/raphael/> 
>
> Github: <https://github.com/DmitryBaranovskiy/raphael> 
>
> 下载: <https://github.com/DmitryBaranovskiy/raphael/releases> 



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
| `setViewBox(x, y, w, h, fit)`   | 设置画纸的视图框，<small>可用于缩放画纸</small>              | 新的 x 位置、新的 y 位置、宽度、高度、图形是否适配新的视图框 | 无               |



#### Element(图形元素)

使用 paper 提供的函数绘制的图形，包括圆形（circle）、椭圆形（ellipse）、矩形（rect）、路径（path）、文本（text）。



##### 图形元素的主要属性

这里的元素属性是指 Raphael 的元素对象的属性，而不是 svg 图形元素的属性。

| 属性      | 类型   | 说明                                                         |
| --------- | ------ | ------------------------------------------------------------ |
| `id`      | number | 元素ID，可用于函数 `getById()` 查找元素                      |
| `next`    | object | 元素的层级关系的下一个元素                                   |
| `prev`    | object | 元素层级关系的上一个元素                                     |
| `node`    | object | 元素的DOM对象<small>(因此你可以为其指定事件处理函数)</small> |
| `paper`   | object | 元素所在的画纸对象                                           |
| `raphael` | object | raphael 对象                                                 |
| `matrix`  | object | 矩阵对象                                                     |



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
| `drag(onmove, onstart, onend, [mcontext], [scontext], [econtext])` | 设置鼠标拖拽事件处理器       | 1. 移动过程中的事件处理函数(dx,dy,x,y,event);<br>2. 拖拽开始事件处理函数(x,y,event);<br>3. 拖拽结束事件处理函数(event);<br>4. 拖拽过程函数上下文;<br>5. 拖拽开始函数上下文;<br>6. 拖拽结束函数上下文; | 元素对象 |
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



#### 图形元素的属性

在 RaphaelJs 中，可以使用图形元素对象的 `attr()` 函数设置或获取元素的属性值，由于 RaphaelJs 是使用 svg 实现的，所以支持 svg 中的图形属性。

##### 常用的一些 svg 属性

| 属性               | 说明                                     | 值                                                          |
| ------------------ | ---------------------------------------- | ----------------------------------------------------------- |
| `cx`               | 圆心x坐标<small>(圆形和椭圆支持)</small> | 数值                                                        |
| `cy`               | 圆心y坐标<small>(圆形和椭圆支持)</small> | 数值                                                        |
| `r`                | 圆形半径                                 | 数值                                                        |
| `rx`               | 椭圆x方向半径                            | 数值                                                        |
| `ry`               | 椭圆y方向半径                            | 数值                                                        |
| `dx`               | 元素或内容沿x轴方向移动距离              | 数值                                                        |
| `dy`               | 元素或内容沿y轴方向移动距离              | 数值                                                        |
| `fill`             | 图形内部填充颜色                         | 颜色字符串, 如 `'#f00'`、`'#ff0000'`、`'red'`               |
| `fill-opacity`     | 填充透明度                               | 数值(0\~1), 如 `0.75`                                       |
| `font-family`      | 字体                                     | 字符串, 如 `"Times New Roman"`                              |
| `font-size`        | 字号                                     | 尺寸值, 如 `12px`、`1.2em`                                  |
| `font-style`       | 字体样式，正常或斜体                     | `normal`、`italic`、`oblique`、`inherit`                    |
| `font-weight`      | 字粗                                     | `normal`、`bold`、`bolder`、`lighter`、`inherit`            |
| `height`           | 高度                                     | 数值                                                        |
| `width`            | 宽度                                     | 数值                                                        |
| `href`             | 链接                                     | 字符串                                                      |
| `stroke`           | 轮廓颜色                                 | 颜色字符串                                                  |
| `stroke-dasharray` | 轮廓虚线                                 | 表示虚线间隔长度的字符串, 如 `'--.'`、`-.`                  |
| `stroke-opacity`   | 轮廓透明度                               | 数值(0\~1)                                                  |
| `stroke-width`     | 轮廓线宽                                 | 宽度值, 如 `1.2em`、`3px`                                   |
| `text-anchor`      | 文字对齐方式                             | `start`、`middle`、`end`                                    |
| `title`            | 鼠标悬停时的提示文字                     | 字符串                                                      |
| `transform`        | 变换                                     | 包含变换指令的字符串, 如 `"translate(30) rotate(45 50 50)"` |



##### Raphael 中的属性

| 属性          | 说明         | 值                                                           |
| ------------- | ------------ | ------------------------------------------------------------ |
| `arrow-end`   | 路径尾部箭头 | `<type>[-<width>[-<length>]]`, types: `classic`, `block`, `open`, `oval`, `diamond`, `none`, width: `wide`, `narrow`, `medium`, length: `long`, `short`, `midium` |
| `arrow-start` | 路径头部箭头 | 同上                                                         |



#### 路径字符串(path string)

>用于描述路径的字符串，格式为命令（command）+ 参数，多个参数以空格或逗号分隔，多条命令依次追加。
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
>
>注：路径字符串中的命令也可以是小写字母，大写字母表示绝对定位，小写字母表示相对定位。



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

RaphaelJs 使用非常简单，首先引入 raphael.js 文件，然后创建一个容器元素并指定 id，然后创建画布，调用画布提供的函数绘制图形，随后可以给图形添加样式和事件处理函数。

以下示例代码绘制了一个圆形，点击圆形可以改变颜色。

查看示例效果: <a href="/example/raphaeljs/raphael.quickstart.html">/example/raphaeljs/raphael.quickstart.html</a>

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



#### 基础图形元素

RaphaelJs 六大基础图形：圆形、矩形、椭圆形、路径、图像、文字。

示例代码:

```javascript
let paper = Raphael('raphael-view',600,200);
paper.circle(100, 100, 30); // 圆形
paper.rect(160, 70, 80, 60); // 矩形
paper.ellipse(300, 100,40, 30); // 椭圆形
paper.path("M360,130L380,70L420,130L440,70"); // 路径
paper.image("cat.jpg",460, 70, 80, 60); // 图像
paper.text(100, 150, "Circle"); // 文字
paper.text(200, 150, "Rect");
paper.text(300, 150, "Ellipse");
paper.text(400, 150, "Path");
paper.text(500, 150, "Image");
```

显示效果: 

<svg height="200" version="1.1" width="600" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" style="overflow: hidden; position: relative; top: -0.6px;"><desc style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Created with Raphaël 2.3.0</desc><defs style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></defs><circle cx="100" cy="100" r="30" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><rect x="160" y="70" width="80" height="60" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><ellipse cx="300" cy="100" rx="40" ry="30" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></ellipse><path fill="none" stroke="#000000" d="M360,130L380,70L420,130L440,70" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><image x="460" y="70" width="80" height="60" preserveAspectRatio="none" xlink:href="/example/raphaeljs/cat.jpg" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></image><text x="100" y="150" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.200003147125244" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Circle</tspan></text><text x="200" y="150" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.200003147125244" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Rect</tspan></text><text x="300" y="150" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.200003147125244" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Ellipse</tspan></text><text x="400" y="150" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.200003147125244" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Path</tspan></text><text x="500" y="150" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.200003147125244" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Image</tspan></text></svg>

查看示例效果: <a href="/example/raphaeljs/raphael.element.html" target="_self">/example/raphaeljs/raphael.element.html</a> 



#### 图形样式属性

示例：

```javascript
let paper = Raphael('view', 800, 480);
paper.circle(50, 50, 30);
// 填充颜色及轮廓
paper.circle(150, 50, 30).attr('fill', 'red').attr('stroke', 'blue');
paper.circle(250, 50, 30).attr({fill: 'red', stroke: 'blue'});
paper.circle(350, 50, 30).attr({fill: 'red', 'fill-opacity': 0.5, stroke: 'blue'});
paper.circle(450, 50, 30).attr({stroke: 'blue', 'stroke-width': '5px', 'stroke-opacity': 0.5});
paper.circle(550, 50, 30).attr({r: 40});
// 虚线轮廓
paper.circle(650, 50, 30).attr({'stroke-dasharray': '-'});
paper.circle(750, 50, 30).attr({'stroke-dasharray': '.'});
paper.circle(50, 150, 30).attr({'stroke-dasharray': '-.'});
paper.circle(150, 150, 30).attr({'stroke-dasharray': '-..'});
paper.circle(250, 150, 30).attr({'stroke-dasharray': '. '});
paper.circle(350, 150, 30).attr({'stroke-dasharray': '- '});
paper.circle(450, 150, 30).attr({'stroke-dasharray': '--'});
paper.circle(550, 150, 30).attr({'stroke-dasharray': '- .'});
paper.circle(650, 150, 30).attr({'stroke-dasharray': '--.'});
paper.circle(750, 150, 30).attr({'stroke-dasharray': '--..'});
// 路径箭头
paper.path('M20,220L80,250').attr('arrow-end','classic-wide-long');
paper.path('M120,220L180,250').attr('arrow-end','block-wide-long');
paper.path('M220,220L280,250').attr('arrow-end','open-wide-long');
paper.path('M320,220L380,250').attr('arrow-end','oval-wide-long');
paper.path('M420,220L480,250').attr('arrow-end','diamond-wide-long');
paper.path('M520,220L580,250').attr('arrow-end','classic-narrow-long');
paper.path('M620,220L680,250').attr('arrow-end','classic-medium-long');
paper.path('M720,220L780,250').attr('arrow-end','classic-wide-midium');
paper.path('M20,290L80,320').attr('arrow-start','classic-wide-long');
paper.path('M120,290L180,320').attr('arrow-start','block-wide-long');
paper.path('M220,290L280,320').attr('arrow-start','open-wide-long');
paper.path('M320,290L380,320').attr('arrow-start','oval-wide-long');
paper.path('M420,290L480,320').attr('arrow-start','classic-wide-long').attr('arrow-end','classic-wide-long');
paper.path('M520,290L580,320').attr('arrow-start','oval-wide-long').attr('arrow-end','classic-wide-long');
paper.path('M620,290L680,320').attr('arrow-start','diamond-wide-long').attr('arrow-end','classic-wide-long');
paper.path('M720,290L780,320').attr('arrow-start','oval-wide-midium').attr('arrow-end','classic-wide-long');
// 文本位置、尺寸及粗细
paper.rect(20, 360, 60, 30);
paper.text(50, 375, "Text")
paper.rect(120, 360, 60, 30);
paper.text(150, 375, "Text").attr('text-anchor', 'start');
paper.rect(220, 360, 60, 30);
paper.text(250, 375, "Text").attr('text-anchor', 'middle');
paper.rect(320, 360, 60, 30);
paper.text(350, 375, "Text").attr('text-anchor', 'end');
paper.rect(420, 360, 60, 30);
paper.text(450, 375, "Text").attr('font-size', '18px');
paper.rect(520, 360, 60, 30);
paper.text(550, 375, "Text").attr('font-weight', 'bold');
paper.rect(620, 360, 60, 30);
paper.text(650, 375, "Text").attr('font-weight', 'bolder');
paper.rect(720, 360, 60, 30);
paper.text(750, 375, "Text").attr('font-weight', 'lighter');
// 字体、样式及链接
paper.rect(20, 430, 60, 30);
paper.text(50, 445, "Text").attr('font','10px "Bookman Old Style"')
paper.rect(120, 430, 60, 30);
paper.text(150, 445, "Text").attr('font-family', 'Comic Sans MS');
paper.rect(220, 430, 60, 30);
paper.text(250, 445, "Text").attr('font-style', 'normal');
paper.rect(320, 430, 60, 30);
paper.text(350, 445, "Text").attr('font-style', 'italic');
paper.rect(420, 430, 60, 30);
paper.text(450, 445, "Text").attr('font-style', 'oblique');
paper.rect(520, 430, 60, 30);
paper.text(550, 445, "Text").attr('font-style', 'inherit');
paper.rect(620, 430, 60, 30);
paper.text(650, 445, "Link").attr('href', 'index.html');
paper.rect(720, 430, 60, 30);
paper.text(750, 445, "Link").attr('href', 'index.html').attr('target','new');
```

效果：

<svg height="480" version="1.1" width="800" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" style="overflow: hidden; position: relative;"><desc style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Created with Raphaël 2.3.0</desc><defs style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><path stroke-linecap="round" d="M5,0 0,2.5 5,5 3.5,3 3.5,2z" id="raphael-marker-classic" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><marker id="raphael-marker-endclassic55-objyxiv8" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-classic" transform="rotate(180 2.5 2.5) scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><path stroke-linecap="round" d="M5,0 0,2.5 5,5z" id="raphael-marker-block" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><marker id="raphael-marker-endblock55-objb2zqm" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-block" transform="rotate(180 2.5 2.5) scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><path stroke-linecap="round" d="M6,1 1,3.5 6,6" id="raphael-marker-open" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><marker id="raphael-marker-endopen77-objhwiag" markerHeight="7" markerWidth="7" orient="auto" refX="4" refY="3.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-open" transform="rotate(180 3.5 3.5) scale(1,1)" stroke-width="1.0000" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><path stroke-linecap="round" d="M2.5,0A2.5,2.5,0,0,1,2.5,5 2.5,2.5,0,0,1,2.5,0z" id="raphael-marker-oval" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><marker id="raphael-marker-endoval55-objlusqf" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-oval" transform="rotate(180 2.5 2.5) scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><path stroke-linecap="round" d="M2.5,0 5,2.5 2.5,5 0,2.5z" id="raphael-marker-diamond" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><marker id="raphael-marker-enddiamond55-objf4quz" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-diamond" transform="rotate(180 2.5 2.5) scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-endclassic52-objcmeky" markerHeight="2" markerWidth="5" orient="auto" refX="2.5" refY="1" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-classic" transform="rotate(180 2.5 1) scale(1,0.4)" stroke-width="1.4286" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-endclassic53-obju2p4z" markerHeight="3" markerWidth="5" orient="auto" refX="2.5" refY="1.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-classic" transform="rotate(180 2.5 1.5) scale(1,0.6)" stroke-width="1.2500" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-endclassic35-objqovqd" markerHeight="5" markerWidth="3" orient="auto" refX="1.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-classic" transform="rotate(180 1.5 2.5) scale(0.6,1)" stroke-width="1.2500" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-startclassic55-objsvfco" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-classic" transform="scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-startblock55-objin0l1" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-block" transform="scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-startopen77-objjip7p" markerHeight="7" markerWidth="7" orient="auto" refX="1" refY="3.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-open" transform="scale(1,1)" stroke-width="1.0000" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-startoval55-objie2so" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-oval" transform="scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-startclassic55-objwjj11" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-classic" transform="scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-endclassic55-objwjj11" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-classic" transform="rotate(180 2.5 2.5) scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-startoval55-obj0308v" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-oval" transform="scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-endclassic55-obj0308v" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-classic" transform="rotate(180 2.5 2.5) scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-startdiamond55-obj2qjw1" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-diamond" transform="scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-endclassic55-obj2qjw1" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-classic" transform="rotate(180 2.5 2.5) scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-startoval35-objyzghd" markerHeight="5" markerWidth="3" orient="auto" refX="1.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-oval" transform="scale(0.6,1)" stroke-width="1.2500" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker><marker id="raphael-marker-endclassic55-objyzghd" markerHeight="5" markerWidth="5" orient="auto" refX="2.5" refY="2.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><use xlink:href="#raphael-marker-classic" transform="rotate(180 2.5 2.5) scale(1,1)" stroke-width="1.0000" fill="#000" stroke="none" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></use></marker></defs><circle cx="50" cy="50" r="30" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="150" cy="50" r="30" fill="#ff0000" stroke="#0000ff" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="250" cy="50" r="30" fill="#ff0000" stroke="#0000ff" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="350" cy="50" r="30" fill="#ff0000" stroke="#0000ff" fill-opacity="0.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); fill-opacity: 0.5;"></circle><circle cx="450" cy="50" r="30" fill="none" stroke="#0000ff" stroke-width="5px" stroke-opacity="0.5" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); stroke-opacity: 0.5;"></circle><circle cx="550" cy="50" r="40" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="650" cy="50" r="30" fill="none" stroke="#000" stroke-dasharray="3,1" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="750" cy="50" r="30" fill="none" stroke="#000" stroke-dasharray="1,1" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="50" cy="150" r="30" fill="none" stroke="#000" stroke-dasharray="3,1,1,1" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="150" cy="150" r="30" fill="none" stroke="#000" stroke-dasharray="3,1,1,1,1,1" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="250" cy="150" r="30" fill="none" stroke="#000" stroke-dasharray="1,3" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="350" cy="150" r="30" fill="none" stroke="#000" stroke-dasharray="4,3" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="450" cy="150" r="30" fill="none" stroke="#000" stroke-dasharray="8,3" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="550" cy="150" r="30" fill="none" stroke="#000" stroke-dasharray="4,3,1,3" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="650" cy="150" r="30" fill="none" stroke="#000" stroke-dasharray="8,3,1,3" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><circle cx="750" cy="150" r="30" fill="none" stroke="#000" stroke-dasharray="8,3,1,3,1,3" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></circle><path fill="none" stroke="#000000" d="M20,220L80,250" marker-end="url(#raphael-marker-endclassic55-objyxiv8)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M120,220L180,250" marker-end="url(#raphael-marker-endblock55-objb2zqm)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M220,220L280,250" marker-end="url(#raphael-marker-endopen77-objhwiag)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M320,220L380,250" marker-end="url(#raphael-marker-endoval55-objlusqf)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M420,220L480,250" marker-end="url(#raphael-marker-enddiamond55-objf4quz)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M520,220L580,250" marker-end="url(#raphael-marker-endclassic52-objcmeky)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M620,220L680,250" marker-end="url(#raphael-marker-endclassic53-obju2p4z)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M720,220L780,250" marker-end="url(#raphael-marker-endclassic35-objqovqd)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M20,290C20,290,80,320,80,320" marker-start="url(#raphael-marker-startclassic55-objsvfco)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M120,290C120,290,180,320,180,320" marker-start="url(#raphael-marker-startblock55-objin0l1)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M220,290C220,290,280,320,280,320" marker-start="url(#raphael-marker-startopen77-objjip7p)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M320,290C320,290,380,320,380,320" marker-start="url(#raphael-marker-startoval55-objie2so)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M420,290C420,290,480,320,480,320" marker-start="url(#raphael-marker-startclassic55-objwjj11)" marker-end="url(#raphael-marker-endclassic55-objwjj11)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M520,290C520,290,580,320,580,320" marker-start="url(#raphael-marker-startoval55-obj0308v)" marker-end="url(#raphael-marker-endclassic55-obj0308v)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M620,290C620,290,680,320,680,320" marker-start="url(#raphael-marker-startdiamond55-obj2qjw1)" marker-end="url(#raphael-marker-endclassic55-obj2qjw1)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><path fill="none" stroke="#000000" d="M720,290C720,290,780,320,780,320" marker-start="url(#raphael-marker-startoval35-objyzghd)" marker-end="url(#raphael-marker-endclassic55-objyzghd)" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></path><rect x="20" y="360" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="50" y="375" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="120" y="360" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="150" y="375" text-anchor="start" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: start; font-family: Arial; font-size: 10px;"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="220" y="360" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="250" y="375" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="320" y="360" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="350" y="375" text-anchor="end" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: end; font-family: Arial; font-size: 10px;"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="420" y="360" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="450" y="375" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="18px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 18px;"><tspan dy="6" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="520" y="360" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="550" y="375" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px; font-weight: bold;" font-weight="bold"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="620" y="360" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="650" y="375" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px; font-weight: bolder;" font-weight="bolder"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="720" y="360" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="750" y="375" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px; font-weight: lighter;" font-weight="lighter"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="20" y="430" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="50" y="445" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font: 10px &quot;Bookman Old Style&quot;;" font="10px &quot;Bookman Old Style&quot;"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="120" y="430" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="150" y="445" text-anchor="middle" font-family="Comic Sans MS" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: &quot;Comic Sans MS&quot;; font-size: 10px;"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="220" y="430" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="250" y="445" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px; font-style: normal;" font-style="normal"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="320" y="430" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="350" y="445" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px; font-style: italic;" font-style="italic"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="420" y="430" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="450" y="445" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px; font-style: oblique;" font-style="oblique"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="520" y="430" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><text x="550" y="445" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px; font-style: inherit;" font-style="inherit"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Text</tspan></text><rect x="620" y="430" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><a xlink:href="index.html" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><text x="650" y="445" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Link</tspan></text></a><rect x="720" y="430" width="60" height="30" rx="0" ry="0" fill="none" stroke="#000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"></rect><a xlink:href="index.html" xlink:show="new" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);"><text x="750" y="445" text-anchor="middle" font-family="&quot;Arial&quot;" font-size="10px" stroke="none" fill="#000000" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0); text-anchor: middle; font-family: Arial; font-size: 10px;"><tspan dy="3.1999878883361816" style="-webkit-tap-highlight-color: rgba(0, 0, 0, 0);">Link</tspan></text></a></svg>

查看示例效果: <a href="/example/raphaeljs/raphael.attribute.html" target="_self">/example/raphaeljs/raphael.attribute.html</a> 



#### 交互事件

在 RaphaelJs 中，我们可以给元素添加事件处理函数，包括点击、双击、拖拽、鼠标悬停、鼠标移入移出等，在图形中实现丰富的交互功能。

示例（<a href="/example/raphaeljs/raphael.event.html" target="_self">查看示例效果</a>）：

```javascript
let paper = Raphael('view', 350, 200);
let rect = paper.rect(0, 0, 300, 200);
rect.attr({fill: 'white'}); // 设置图形填充，否则只能点击边框
let text = null;
// 点击矩形显示点击位置坐标
rect.click(function (event, x, y) {
    console.log('Click event: ', event, x, y);
    if (text != null) {
        text.remove();
    }
    text = paper.text(325, 10, "(" + event.layerX + "," + event.layerY + ")");
});
// 双击切换背景颜色，双击时会触发两次单击事件
rect.dblclick(function (event, x, y) {
    if (rect.attr("fill") === 'white') {
        rect.attr({fill: 'gray'});
    } else {
        rect.attr({fill: 'white'});
    }
});
// 绘制一个圆形，实现拖动效果
circle = paper.circle(50, 50, 20).attr({fill: 'white'});
circle.drag(function (dx, dy, x, y, event) {
    console.log('On move: ', dx, dy, x, y, event);
    circle.attr("cx", event.layerX);
    circle.attr("cy", event.layerY);
}, function (x, y, event) {
    console.log('Move start: ', x, y, event)
}, function (event) {
    console.log('Move end: ', event);
});
// 给圆形添加hover处理函数，实现鼠标移入切换颜色
circle.hover(function (event, x, y) {
    console.log('Hover in: ', event, x, y);
    circle.attr('fill', 'red');
}, function (event, x, y) {
    console.log('Hover out: ', event, x, y);
    circle.attr('fill', 'white');
});
```



#### 动画效果

在 RaphaelJs 中，可以给图形元素添加动画效果，有两种方式：

- 使用 `Raphael.animation()` 函数创建动画对象 ，然后使用元素对象的 `animate()` 函数绑定动画对象。
- 使用元素对象的 `animate()` 函数直接添加动画效果。

> 区别：创建动画对象可以复用动画，同时可以给动画添加延迟执行和重复执行；直接给元素对象添加动画则不能实现延迟和重复执行。

创建动画时，函数的第一个参数是动画结束时的元素属性对象，第二个参数是动画时长（单位毫秒），第三个参数是动画缓和效果，第四个参数是动画结束回调函数。

示例（<a href="/example/raphaeljs/raphael.animate.html" target="_self">查看示例效果</a>）：

```javascript
let paper = Raphael('view', 400, 200);
// 一个闪烁的圆圈
let circle1 = paper.circle(50, 50, 30).attr({fill: 'white'});
// 创建一个动画对象
let anim1 = Raphael.animation({fill: 'red'}, 500);
// 动画对象的 repeat() 函数用于设置动画重复次数，参数为重复次数，如果一直循环则传 Infinity
anim1 = anim1.repeat(Infinity);
// 动画对象的 delay() 函数用于设置动画延迟开始时间，单位毫秒
// 注意，如果是循环的动画，则每次开始前都会延迟
anim1 = anim1.delay(1000);
circle1.animate(anim1);

// 点击切换颜色动画的圆圈
let circle2 = paper.circle(150, 50, 30).attr({fill: 'white'});
circle2.click(function (event, x, y) {
    if (circle2.attr("fill") === 'white') {
        circle2.animate({fill: 'red'}, 500, "liner", function () {
            // 动画结束时的回调函数
            console.log("Animation end callback");
        });
    } else {
        circle2.animate({fill: 'white'}, 500);
    }
});

// 半径扩大的圆形
let circle3 = paper.circle(250, 50, 1).attr({fill: 'white'});
let anim3 = Raphael.animation({r: 30}, 1000).repeat(Infinity);
circle3.animate(anim3);

// 移动的圆形
let circle4 = paper.circle(320, 50, 30).attr({fill: 'white'});
let anim4 = Raphael.animation({cx: 370}, 1000).repeat(Infinity);
circle4.animate(anim4);

// 使用 Raphael.animation() 函数创建动画对象时，第三个参数是动画缓和效果
// 不同的动画缓和效果
let anim5 = Raphael.animation({cy: 190}, 1000, "linear"); // 线性
paper.circle(10, 110, 10).attr({fill: 'white'}).animate(anim5);

let anim6 = Raphael.animation({cy: 190}, 1000, "<"); // 缓入，等同  “easeIn” 、 “ease-in”
paper.circle(30, 110, 10).attr({fill: 'white'}).animate(anim6);

let anim7 = Raphael.animation({cy: 190}, 1000, ">"); // 缓出，等同 “easeOut” 、 “ease-out”
paper.circle(50, 110, 10).attr({fill: 'white'}).animate(anim7);

let anim8 = Raphael.animation({cy: 190}, 1000, "<>"); // 缓入缓出，等同 “easeInOut” 、 “ease-in-out”
paper.circle(70, 110, 10).attr({fill: 'white'}).animate(anim8);

let anim9 = Raphael.animation({cy: 190}, 1000, "backIn"); // 后移进入，向后移动后进入，等同 “back-in”
paper.circle(90, 110, 10).attr({fill: 'white'}).animate(anim9);

let anim10 = Raphael.animation({cy: 190}, 1000, "backOut"); // 后移结束，结束时先冲出一段再向后移动，等同 “back-out”
paper.circle(110, 110, 10).attr({fill: 'white'}).animate(anim10);

let anim11 = Raphael.animation({cy: 190}, 1000, "elastic"); // 弹跳
paper.circle(130, 110, 10).attr({fill: 'white'}).animate(anim11);

let anim12 = Raphael.animation({cy: 190}, 1000, "bounce"); // 弹回
paper.circle(150, 110, 10).attr({fill: 'white'}).animate(anim12);

// 多个动画效果
paper.circle(170, 110, 10).attr({fill: 'white'}).animate({cy: 190}, 1000).animate({fill: 'red'}, 1000); // 移动的同时改变颜色
// paper.circle(170, 110, 10).attr({fill: 'white'}).animate({cy: 190, fill: 'red'}, 1000); // 与上面效果相同

// 变形动画：向右平移 100 像素，同时旋转 90 度，同时 x 方向扩大 2 倍
let anim13 = Raphael.animation({transform: 't100,0r90s2,1'}, 1000).repeat(Infinity);
paper.circle(190, 110, 10).attr({fill: 'white'}).animate(anim13); // 变形动画
```



### 总结

RaphaelJs 是一个偏底层基础的矢量绘图库，支持绘制的图形包括圆形、椭圆、矩形、路径、文字，支持的交互事件包括点击、双击、拖拽、鼠标悬停、鼠标移入移出等，支持动画效果，支持设置修改 svg 标准属性，支持创建图形集合。RaphaelJs 能够完成最基础图形绘制功能，其优势在于轻量和支持跨平台，如果要实现复杂的图形绘制就需要自己编码和封装，比如要实现统计图，就需要自己绘制坐标轴，这需要根据数据计算坐标轴的位置、长度，绘制坐标轴上的刻度等等，如果要实现绘制图形的自适应就需要更多的编码和封装了。Raphael 的官网提供了很多精美的示例，实现了很酷炫的效果，但没提供代码，所以学习起来不太方便，只能看 api 文档，自己摸索，因此我把自己摸索的成果写成了这篇文章，记录下来将来使用时有所参考。

本文示例: <a href="/example/raphaeljs/">/example/raphaeljs/</a> 



### 参考资料

- CSS3中的矩阵: <https://blog.csdn.net/flqbestboy/article/details/78110019> 
- SVG参考手册: <http://www.verydoc.net/svg/> 
