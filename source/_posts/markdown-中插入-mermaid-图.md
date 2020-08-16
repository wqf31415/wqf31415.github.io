---
title: markdown 中插入 mermaid 图
date: 2020-08-13 06:47:08
tags:
- markdown
- mermaid
- js
categories:
- 技术
---

### 概述

mermaid 用于在 markdown 插入文档图，本文介绍了在 markdown 中使用 mermaid 插入图形的技巧。 



### 认识 mermaid 图

> mermaid github: <https://github.com/mermaid-js/mermaid> 

mermaid 美人鱼，是用文本语法来描述文档图形的工具，可以描述流程图、时序图、甘特图、类图等。在markdown 文档中可以使用 mermaid 文本插入文档图形，比如：

```mermaid
graph TB;
A-->B
A-->C
B-->D
C-->D
```



<!-- more -->



### mermaid 语法

#### 图表方向

Mermaid 图表支持多种方向的图形，在 mermaid 描述开始时，使用 `graph 方向描述词;` 规定图表方向，将决定图的走向，即箭头的默认方向。

方向描述：

| 方向描述词 | 含义                |
| ---------- | ------------------- |
| TB         | Top-Bottom 从上到下 |
| BT         | Bottom-Top 从下到上 |
| LR         | Left-Right 从左到右 |
| RL         | Right-Left 从右到左 |

举例：

```
graph RL;
A-->B
```

效果：

```mermaid
graph RL;
A-->B
```

#### 节点定义

节点是指文档图中的文本块，比如在流程图中使用圆角矩形表示开始与结束，使用菱形表示条件判断，使用矩形表示流程。mermaid 中定义节点时，必须指定一个节点ID，ID 用于与其他节点创建连线，区分大小写。可以指定节点形状以及描述文字，节点形状缺省为矩形，描述文字缺省为节点ID，如 `start(开始)` 将创建一个圆角矩形的节点，显示内容为 `开始` ，节点ID 为 `start`。

| 语法         | 说明                     |
| ------------ | ------------------------ |
| `id[描述]`   | 矩形                     |
| `id(描述)`   | 圆角矩形                 |
| `id((描述))` | 圆形                     |
| `id>描述]`   | 向右旗帜（没有向左旗帜） |
| `id{描述}`   | 菱形                     |

> 如果节点描述中包含标点符号，需要使用双引号包裹，如要显示 `{{test}}` 需要写作 `id{"{{test}}"}` 。

举例：

```
graph TB;
A
start(圆角矩形)
process[矩形]
circle((圆形))
flag>向右旗帜]
judge{菱形}
```

效果：

```mermaid
graph TB;
A
start(圆角矩形)
process[矩形]
circle((圆形))
flag>向右旗帜]
judge{菱形}
```



#### 节点间的连线

两个节点 ID 中间加连线标识即可连接节点，如使用箭头连接 A 、B节点，写作 `A-->B` 。

| 连线标识                  | 说明                                                         |
| ------------------------- | ------------------------------------------------------------ |
| `>`                       | 加箭头，下面的所有连线都可以在最后面加上 `>` 来绘制带箭头的连线 |
| `-`                       | 不加箭头                                                     |
| `--`                      | 单线                                                         |
| `--描述--` 或 `---|描述|` | 带描述文字的单线                                             |
| `==`                      | 粗线                                                         |
| `==描述==`                | 带描述文字的粗线                                             |
| `-.-`                     | 虚线                                                         |
| `-.描述.-`                | 带描述文字的虚线                                             |

举例：

```
graph TB;
A---B
C-->D
E--描述---F
G===H
I==描述===J
K-.-L
M-.描述.-N

```

效果：

```mermaid
graph TB;
A---B
C-->D
E--描述---F
G===H
I==描述===J
K-.-L
M-.描述.-N
```

> 多个节点顺序连接时可以写成一条，如 `A-->B-->C-->D` 。



#### 子图表





### markdown 里支持的 mermaid 图





### 支持 mermaid 的编辑器及平台



### 在 hexo 博客中使用 mermaid



### 参考资料

- Mermaid 实用教程: <https://blog.csdn.net/fenghuizhidao/article/details/79440583> 0
- Markdown里面使用mermaid画流程图: <https://blog.csdn.net/Subson/article/details/78054689> 
- Hexo中插入mermaid diagrams : <https://blog.csdn.net/Olivia_Vang/article/details/92987859> 
- Hexo中引入Mermaid流程图: <https://tyloafer.github.io/posts/7790/> 



### 总结

在文档中，图形的表现力要远大于文字，在平时用 markdown 写文档的时候，可以采用 mermaid 插入图形，让表述更加准确易读。