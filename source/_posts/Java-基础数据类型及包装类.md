---
title: Java 基本数据类型及包装类
tags:
  - java
categories:
  - 技术
date: 2020-02-12 22:03:21
---

### 概述

这篇文章总结了 Java 中的基本数据类型和对应的封装类，以及各种类型数据之间的转换操作。

### 什么是基础数据类型

![](http://blog-images.qiniu.wqf31415.xyz/coffee.png)

在 Java 语言中，提供了 8 种基本数据类型，6 种数字类型(4 种整数类型，2 种浮点型)， 2 种字符型，这些基本数据类型从 Java 发布以来就是 java 语言的一部分。



<!-- more -->



### java 基本数据类型

#### byte

字节，长度 1 字节，存储范围： `-128` \~ `127` ，即 -2<sup>7</sup> \~ 2<sup>7</sup>-1。

在给字节变量赋值时，有两种方式：

- 一是可以使用单引号包裹字符形式，使用单引号包裹字符形式时，单引号内只能有一个字符，字符是 ASCII 码中包含的字符，可以是转义字符；
- 二是可以使用数字形式，在使用数字形式赋值时，要注意数值不能超出 byte 数据的存储范围，即必须在 -128 \~ 127 之间，如果赋值超过此范围，一般编译器会报错提示定义错误。使用数字时，可以使用各种进制定义，如二进制、八进制、十进制、十六进制。

```java
byte b = '1'; // 字节
byte b2 = 1; // 数字
byte b3 = '\t'; // 转义字符
byte b4 = 0x0F; // 十六进制数
```

> 注意，以上代码中定义的字节类型变量 b 和 b2 不相等，如果我们使用 `System.out.println()` 方法将两个变量打印出来，发现 第一个输出 `49`，第二个输出 `1` 。
>
> 原因是：
>
> 使用 `System.out.println()` 方法输出字节类型变量值时，输出的实际是这个值的整数形式。对于字符类型数据来说，输出的就是该字符的 ASCII 值，而在ASCII 码中字符 `'1'` 的 ASCII 值就是 49。



#### short

短整型，长度 2 字节，存储范围：`-32768` \~ `32767`，即 -2<sup>15</sup> \~ 2<sup>15</sup>-1。

short 类型变量用于存储小一些的整数。



#### int

整形，长度 4 字节，存储范围：`-2147483648` \~ `2147483647` ，即 -2<sup>31</sup> \~ 2<sup>31</sup>-1 。

int 类型大概是 java 中用的最多的类型了吧。



#### long

长整型，长度 8 字节，存储范围： -2<sup>63</sup> \~ 2<sup>63</sup>-1。

长整型用来存储大的整数，但是也是有极限的，如果要存储的数超出了 long 类型的存储范围，需要使用 `BigDecimal` 类型。

在定义长整型数据时，为了跟整形区别，可以在数字后面加 `l` 或 `L` 后缀，如：

```java
long l = 123;
long l2 = 123l;
long l3 = 123L;
```

> 因为小写字母 `l` 容易跟数字 `1` 混淆，所以一般使用大写字母 `L` 作为整形数字的后缀。



#### float

单精度浮点型，长度 4 字节，存储范围：1.17549435 x 10<sup>-38</sup> \~ 3.4028235 x 10<sup>38</sup> 。

浮点型的数据计算是有误差的，所以有些时候，我们会在计算的时候会使用整形来计算，比如计算价格的时候，价格是 19.80，我们会把它转成 1980 来计算，计算完成后，需要输出的时候，再除以 100 ，转成浮点型。

为了跟其它类型区分，在定义 float 类型数据时，可以在数字后面加 `f` 或 `F` 作为后缀，如：

```java
float f = 3.14;
float f2 = 3.14f;
float f3 = 3.14F;
```

> 在 IntelliJ IDEA 中，默认小数是 double 类型，所以定义 float 类型数据时必须加上后缀 `f` 或 `F` ，否则会提示类型不匹配。



#### double

双精度浮点型，长度 8字节，存储范围：2.2250738585072014 x 10<sup>-308</sup> \~ 1.7976931348623157 x 10<sup>308</sup> 。

double 类型变量存储的范围更大，而且精度比 float 更高。

为了与 float 区分，在定义 double 类型数据时，可以在后面加上 `d` 或 `D` 作为后缀，如：

```java
double d = 3.14;
double d2 = 3.14d;
double d3 = 3.14D;
```



#### char

字符型，长度 2 字节，存储范围：`‘\u0000’` \~ `'\uFFFF'` 。

在 java 中的字符指的是广义的 Unicode 字符集中的字符，包括英文、中文、希腊文、藏文等等各种语言文字，也包括各种中英文标点、数学符号、特殊字符等等。

```java
char c = 'a';
char c2 = '好';
char c3 = '⑤';
char c4 = '\u00BE';
```



#### boolean

布尔型，长度 1 位，值为 `true` 或 `false` 。

在 java 中 boolean 类型的值只有 `true` 、`false` ，在条件判断时也只有这两个值，不像其他编程语言 0 可以当 false 使用。



#### 数值格式

在定义数值类型数据后，可以直接给该变量赋值，在数字可以使用下划线 `_` 来分隔数字，便于阅读；还可以使用科学计数法表示数值。如：

```java
int i = 1_000; // 1000
long l = 1_2000_0000L; // 一亿两千万
float f = 1_234.56f; // 1234.56
double d = 1.23e-3D; // 0.00123
double d2 = 1_1.23E3D; // 11230.0
```



####小结

对于整形数据类型的最大值与最小值，就看它的存储空间的位数 x，最小值就是 -2<sup>x-1</sup> ，最大值就是 2<sup>x-1</sup> - 1，指数减一是因为整形数据的首位是符号位要去掉。比如整形 int，4 字节，存储空间有 4 × 8 = 32 位，所以整形数据类型的最大值就是  -2<sup>31</sup> ，最大值就是 2<sup>31</sup>-1 。

此外，在这些基本数据类型对应的封装类中，存在常量 `MIN_VALUE` 和 `MAX_VALUE` ，通过获取这两个常量值也可以知道此类型数据的值存储范围。



### 基本数据类型对应的包装类

Java 中基本数据类型对应的包装类（或称为封装类）都在 `java.lang` 包中，这个包是 java 语言的核心，除了这些基本数据类型的包装类，还包括 Object 类、 Class 类、String 类、基本数学类等最基本的类。



#### 自动拆包

在 java 中封装类在使用时，和基本数据类型一样使用，不需要手动转换，因为 jvm 将自动完成拆包的动作。



#### equals() 方法

在基本数据类型的封装类中，使用 `equals()` 方法与另一个对象进行比较时，实际比较的是两个对象的值，不是比较对象的内存地址。如 Byte 类中的 `equals()` 方法：

```java
public boolean equals(Object obj) {
    if (obj instanceof Byte) {
        return value == ((Byte)obj).byteValue();
    }
    return false;
}
```



#### 都有的属性和方法

在基本数据类型的封装类中有一些属性和方法，是所有封装类都有的。

##### 属性

都有的属性：最大值（`MAX_VALUE`）、最小值（`MIN_VALUE`）、字节数（`BYTES`）、位数（`SIZE`）



##### compareTo() 方法

这些封装类都实现了 `Comparable` 接口，都实现了该接口中的 `compareTo()` 方法，这个方法用来比较相同类型数据的大小，返回结果类型是 int，但返回值不太一样：

- 对于 `Byte` 、 `Short` 和 `Character` 数据返回值是当前对象值减其他对象值的差；
- 对于`Integer` 、`Long` 以及浮点型是比较值大小，大于返回 1，小于返回 -1，等于返回 0；
- 对于 `Boolean` 类型，当值相同时返回 0，不同时看本对象的值，为 `true` 返回 1，为 `false` 则返回 -1。



##### 与字符串类型的转换

所有基本数据类型的封装类都提供了与 String 类型的转换方法，提供了 `toString()` 方法转换成字符串类型，提供了 `valueOf()` 和 `parseXxx()` 方法用于将字符串形式的值转换成对应类型，Xxx 是峰值类型，如 Integer 中的 `parseInt()`。同时每种封装类都提供了带 String 类型参数的构造方法，可以直接创建响应对象，如 Short 类型的构造方法：

```java
public Short(String s) throws NumberFormatException {
    this.value = parseShort(s, 10);
}
```



##### 数据转换方法

`Byte` 、`Short` 、`Integer` 、`Long` 、`Float` 、`Double` 这几个类都继承自 `Number` 类，所以都实现了 `Number` 中用于转换数据类型的方法： `byteValue()` 、`shortValue` 、`intValue()` 、`longValue()` 、`floatValue()` 、`doubleValue()` 。



##### 整形数据的无符号值

 对于整形数据，有无符号数值，即原来首位是符号位，现在首位也用来表示数字，这样只能存储非负数，但存储范围变大。在 java 中，各个整形数据类型的封装类中提供了将数转换成无符号值的方法：

- `Byte` 、`Short` 类，有 `toUnsignedInt()` 、 `toUnsignedLong()` 方法，用于将值转成无符号整数或无符号长整型数；
- `Integer` 类有 `toUnsignedLong()` 方法将值转成无符号长整型数；
- `Long` 类有 `toUnsignedBigInteger()` 方法，用于将长整型数转成无符号大整数。



#### Byte

字节类型 byte 的封装类，字节类型是 java 中最小的数据单位。



#### Short

短整型 short 的封装类，在这个类中还提供了 `reverseByBytes(short)` 方法，用于得到字节逆序的 short 值。



#### Integer

整形 int 的封装类，这是用的最多的数据类型，在这个封装类中提供了很多实用方法：

- 无符号类型整数的运算：比较 `compareUnsigned(int,int)` ，除法 `divideUnsigned(int,int)` ，解析无符号字符串为整形 `parseUnsignedInt(String)` 等
- 字符串解码成整形：`decode(String)` 将十进制、十六进制、八进制形式的数字字符串解码成整数。
- 获取按字节逆序值：`reverse(int)` 
- 转换成各种进制字符串：二进制 `toBinaryString(int)` 、十六进制 `toHexString(int)` 、八进制 `toOctalString(int)` 。



#### Long

长整型 long 的封装类，使用的也很多，也提供了很多方法，大多与 Integer 中的类似。



#### Float

单精度浮点型 float 类型的封装类。

在 FLoat 类中，提供了一些特别的常量：

- `NaN` 非数字，值为 `0.0f / 0.0` 
- `NEGATIVE_INFINITY` 负数极限值，值为 `-1.0f / 0.0f` 
- `POSITIVE_INFINITY` 正数极限值，值为 `1.0f / 0.0f` 

提供了很多方法：

- 转换成整形数值的方法：`floatToIntBits(float)` 

- 判断数值合法的方法：`isFinite(float)` ， `isNaN()` 

- 转换成十六进制字符串的方法：`toHexString(float)` 
- 等



#### Double

双精度浮点型 double 类型的封装类。

常量与方法与 Float 类型类似。



#### Character

字符型 char 类型的封装类。

提供了很多个常量。

提供很多方法：

- 判断字符大小写和转换大小写的方法
- 字符属性判断方法
- 等



#### Boolean

布尔类型 boolean 的封装类。

在这个类中提供了布尔运算方法，与运算 `logicalAnd(boolean,boolean)` ，或运算 `logicalOr(boolean,boolean)` ，异或运算 `logicalXor(boolean,boolean)` 。

Boolean 类中的 `compareTo(Boolean)` 方法在两个对象值相同时，返回 0，否则根据当前对象的值决定返回值，当前对象值为 true 返回 1，否则返回 -1 。



### 不同数据类型的转换

数值类型数据可以直接通过各自封装类中的 `byteValue()` 、`shortValue()` 、`IntegerValue()` 、`longValue()` 、`floatValue()` 、`doubleValue()` 方法转换成想要的类型。

> 注意：长度更大的类型转换成长度小的类型时，会损失精度。

字符类型和布尔类型不能转换成数值类型。



### 总结

基本数据类型是最基础的知识，这些数据类型和包装类中的方法都要用的滚瓜烂熟才行。这些基本数据类型里面有些跟 C 语言是一样的，但没有 C 语言中的无符号类型数据，因此在处理一些协议数据的时候，对于无符号类型要特别注意。

