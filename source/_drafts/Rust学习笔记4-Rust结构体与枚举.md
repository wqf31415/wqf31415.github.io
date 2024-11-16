---
title: Rust学习笔记4-Rust结构体与枚举
tags:
  - 开发
  - Rust
categories:
  - Rust
date: 2024-06-24 20:35:07
---

### 概述

本文介绍了 Rust 中的结构体（struct）与枚举（enum），内容包含结构体的定义、实例化、使用与示例。



### 结构体和枚举

结构体是一种允许用户自行定义的数据类型，可将多种类型的数据打包成有意义的组合，并给每个数据命名。与 C 语言中的结构体不同，Rust 中可以为结构体和枚举声明函数。

枚举是一种允许用户定义所有可能类型的数据类型。

<!-- more -->



### Rust 结构体

#### 定义结构体

Rust 中使用 `struct` 关键字定义结构体，并为结构体命名；

在花括号内，为所有字段（Field）定义名称和类型；

每个字段定义使用逗号 `,` 分隔，最后一个字段后可以加逗号。

示例：

```rust
struct Student {
    name: String,
    age: u8,
    active: bool,
}
```



#### 实例化结构体

要使用结构体，需要创建其实例：

要为每个字段指定具体值，但无需按声明顺序进行指定；

结构体字段赋值使用冒号 `:` 连接，每个字段赋值后使用逗号 `,` 分隔。

```rust
    let zhangsan = Student {
        name: String::from("ZhangSan"),
        age: 18,
        active: true,
    };
```



#### 访问结构体中字段

Rust 中使用点标记法访问结构体字段。

使用 `mut` 关键字声明可变的结构体，只要结构体变量是可变的，其中所有字段都是可变的。

```rust
struct Student {
    name: String,
    age: u8,
    active: bool,
}

fn main() {
    let mut zhangsan = Student { // 使用 mut 关键字将结构体定义为可变的
        name: String::from("ZhangSan"),
        age: 18,
        active: true,
    };

    println!("name: {}", zhangsan.name); // 读取结构体的字段值

    zhangsan.age = 19; // 修改结构体的字段值
    println!("age: {}", zhangsan.age);
}
```



#### 结构体作为函数返回值

使用函数传入参数创建结构体：

```rust
fn build_student(name: String, age: u8)-> Student {
    Student {
        name: name,
        age: age,
        active: false,
    }
}
```



#### 结构体字段初始化简写

当字段名与字段值对应的变量名相同时，就可以使用字段初始化的简写方式。

上一个函数定义可以简化成下面的方式：

```rust
fn build_student(name: String, age: u8)-> Student {
    Student {
        name, //字段名与参数值的变量名相同，使用简写方式
        age,
        active: false,
    }
}
```



#### 结构体更新语法

当需要基于某个结构体实例来创建一个新实例时，可以使用结构体更新语法。

```rust
fn main() {
    let mut zhangsan = Student { // 使用 mut 关键字将结构体定义为可变的
        name: String::from("ZhangSan"),
        age: 18,
        active: true,
    };

    let mut lisi  = Student {
        name: String::from("LiSi"), // 只修改了 name 字段
        ..zhangsan // 其他字段值使用 zhangsan 结构体的值
    };

    println!("name: {}", lisi.name);
    println!("age: {}", lisi.age);
}
```



#### 元组结构体（Tuple Struct）

在Rust 中可以定义类似 tuple 的结构体，叫做 tuple struct：

Tuple struct 整体有命名，但里面的元素没有名；

适用于：想给整个 Tuple 起名，让它不同于其它 Tuple，而且不想给每个元素起名。

定义Tuple struct 的方法：使用 `struct` 关键字，后面是名字，以及里面元素的类型。

```rust
struct Color(i32, i32, i32);
struct Point(i32, i32, i32);
let red = Color(0xFF, 0, 0);
let origin = Point(0, 0 ,0);
```

> 注意：red 和 origin 是不同的类型，是不同 Tuple struct 的实例。



#### Unit-Like Struct（没有任何字段）

Rust 支持定义没有任何字段的 struct，叫做 Unit-Like struct （因为与 `()`，单元类型相似）。

适用于：需要在某个类型上实现某个 trait，但里面没有想要存储的数据。



#### 结构体数据的所有权

```rust
struct Student {
    name: String,
    age: u8,
    active: bool,
}
```

在结构体 `Student` 中，name 使用的是 `String` ，其他字段是标量类型，所以这个结构体持有了其所有字段的所有权，这种情况下，只有它的实例是有效的，那么它的字段都是有效的。

当结构体中字段也可以是引用类型，此时就需要用到生命周期，生命周期保证只要结构体实例是有效的，那么里面的字段都是有效的。

如果结构体中字段是引用类型，又没有使用生命周期就会报错。



#### 使用println输出结构体

Rust中使用 `println` 宏打印数据内容时，要求数据实现 `std::fmt::Display` 的 trait，而创建的结构体默认是没有实现这个 trait 的，直接打印会报错，提示没有实现 `std::fmt::Display` 。

可以使用 `{:?}` 或 `{:#}` 替代原来的格式化占位符 `{}`，其中 `{:#}` 输出格式可读性更好；同时，需要在结构体定义前加上注解 `#[derive(Debug)]` ，如：

```rust
#[derive(Debug)] // 加上注解，让 Student 实现 `Debug` trait
struct Student {
    name: String,
    age: u8,
    active: bool,
}

fn main() {
    let mut zhangsan = Student {
        name: String::from("ZhangSan"),
        age: 18,
        active: true,
    };

    println!("{:?}", zhangsan); // 使用 {:?} 或 {:#} 替换 {}
}
```

> 另外一个方法是给结构体实现 `std::fmt::Display` 。



#### 结构体方法

方法和函数类似，也是使用 `fn` 关键字定义，包含名称、参数与返回值。

方法与函数的不同之处：

- 方法是在结构体（struct）、枚举（enum）或 trait 对象的上下文中定义。
- 方法的第一个参数是 `self`，表示方法被调用的 struct 实例，第一个参数可以是 self 的借用 `&self`，也可以获得其所有权 `self`，也可以是可变借用 `&mut self`。
- 使用 `impl` 关键字，后面跟结构体名，在 impl 声明的代码块中为结构体定义方法。可以在一个 impl 代码块中添加多个方法，也可以有多个 impl 代码块。

```rust
#[derive(Debug)]
struct Student {
    name: String,
    age: u8,
    active: bool,
}

impl Student {
    fn de_active(&mut self) { // 方法内要修改结构体，所以要传可变引用
        self.active = false;
    }
    fn is_older(&self, other: &Student) -> bool { // 包含第二个参数和返回值的方法
        self.age > other.age
    }
    fn new(name: String, age: u8) -> Student { // 关联函数，用于创建一个实例
        Student {
            name,
            age,
            active: false
         }
    }
}

impl Student { // 多个 impl 块
    fn introduce(&self) {
        println!("我叫{}，我{}岁", self.name, self.age);
    }
}

fn main() {
    let mut zhangsan = Student { // 使用 mut 关键字将结构体定义为可变的
        name: String::from("ZhangSan"),
        age: 18,
        active: true,
    };

    zhangsan.de_active(); // 调用结构体方法，方法只有一个 &mut self 参数，不需要传参
    println!("{:?}", zhangsan);
    zhangsan.introduce();

    let lisi = Student::new(String::from("LiSi"), 17);
    println!("zhangsan is older: {}", zhangsan.is_older(&lisi));
}
```



#### 结构体关联函数

可以在结构体 impl 块里定义不把 self 作为第一个参数的函数，它叫做关联函数（不是方法）。

关联函数不使用结构体实例调用，而是使用结构体名加 `::` 调用，例如 `String::from()` 。

关联函数通常用于构造器，就是用来创建被关联类型的一个实例。

> 关联函数类似于 java 的类里面定义的静态方法，java 中使用 `类.方法()` 调用静态方法，Rust 中使用 `结构体名::函数()` 调用关联函数。



### Rust 枚举



### 参考资料



### 总结
