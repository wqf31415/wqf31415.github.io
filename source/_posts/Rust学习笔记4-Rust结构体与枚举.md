---
title: Rust学习笔记4-Rust结构体与枚举
tags:
  - 开发
  - Rust
categories:
  - Rust
date: 2024-11-17 21:06:07
---

### 概述

本文介绍了 Rust 中的结构体（struct）与枚举（enum），内容包含结构体的定义、实例化、使用与示例，枚举的定义与使用。

![](/images/post/crab-7627632_1280.webp)



### 结构体和枚举

结构体是一种允许用户自行定义的数据类型，可将多种类型的数据打包成有意义的组合，并给每个数据命名。与 C 语言中的结构体不同，Rust 中可以为结构体和枚举声明方法。

枚举是一种允许用户列举所有可能类型的数据类型，Rust 中枚举允许携带数据，每个枚举变体可以携带不同类型、不同数量的数据。

<!-- more -->



### Rust 结构体

#### 定义结构体

Rust 中使用 `struct` 关键字定义结构体，定义时为结构体命名；

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

结构体中字段也可以是引用类型，此时就需要用到生命周期，生命周期保证只要结构体实例是有效的，那么里面的字段都是有效的。

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

> 另外一个解决方法是给结构体实现 `std::fmt::Display` 。



#### 结构体方法

方法和函数定义类似，也是使用 `fn` 关键字定义，包含名称、参数与返回值。

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

可以在结构体 impl 块里定义不把 self 作为第一个参数的函数，叫做**关联函数**（不是方法）。

关联函数不使用结构体实例调用，而是使用结构体名加 `::` 调用，例如 `String::from()` 。

关联函数通常用于构造器，就是用来创建被关联类型的一个实例。

> 关联函数类似于 java 的类里面定义的静态方法，java 中使用 `类.方法()` 调用静态方法，Rust 中使用 `结构体名::函数()` 调用关联函数。



### Rust 枚举

#### 定义枚举

枚举允许用户列举所有可能值来定义数据类型，枚举使用 `enum` 关键字定义，后面指定枚举名，在花括号中声明所有可能得值，枚举中所有可能的值被称为枚举的变体。

使用枚举时，用枚举名加 `::` 再加某个变体名。

```rust
enum Weekday {
    Mon,
    Tues,
    Wed,
    Thur,
    Fri,
    Sat,
    Sun,
}
fn main() {
    let today = Weekday::Sun;
    let tomorrow = Weekday::Mon;
}
```

#### 将数据附加到枚举的变体中

Rust 允许为枚举变体设定附加数据，可以为变体设定不同类型和数量的附加数据。

```rust
enum IpAddr {
    V4(u8,u8,u8,u8),
	V6(String),
}
fn main() {
    let a = IpAddr::V4(127, 0, 0, 1);
    let b = IpAddr::V6(String::from("::1"));
}
```

#### 为枚举定义方法

Rust 中允许为枚举定义方法，与结构体相同，使用 `impl` 关键字，在代码块中定义方法，方法第一个参数是 `self`。

```rust
impl IpAddr {
    fn print(&self) {
        // ...方法的代码
    }
}
```

#### 使用 match 匹配枚举

Rust 中使用 `match` 匹配枚举，一旦匹配到其中某个变体，就执行这个代码块，后续的不再进行匹配。

注意，match 匹配必须穷尽所有可能，可以使用下划线 `_` 匹配剩余的可能，注意下划线匹配必须放在最后一个。

```rust
enum Weekday {
    Mon(String),
    Tues,
    Wed,
    Thur,
    Fri,
    Sat,
    Sun,
}

fn is_workday(day: Weekday) -> bool {
    match day {
        Weekday::Mon(content) => { // 如果变体中有附加数据，使用括号声明，然后在代码块中使用
            println!("Monday: {}", content); // 如果有多行代码，需要使用花括号包裹代码块
            true // 代码块最后一句的结果作为返回值
        },
        Weekday::Tues => true, // 直接返回值作为 match 的返回值
        Weekday::Wed => true,
        Weekday::Thur => true,
        Weekday::Fri => true,
        _ => false, // 使用下划线匹配剩余的可能变体
    }
}

fn main() {
    is_workday(Weekday::Mon(String::from("Start work")));
}
```

#### Option 枚举

Option 枚举定义于标准库中，在 Prelude（预导入模块）中，可以直接使用。

在 Rust 中没有 NULL 的概念，有类似 NULL 概念的枚举 Option<T> ，它描述了某个值可能存在（某种类型）或不存在的情况。

Option<T> 枚举包含两个变体：

- Some<T> 表示存在类型 T 的值，要使用其中的 T，需要先将 Option<T> 转换成 T

- None 表示没有值，类似其他编程语言中的 NULL

```rust
fn main() {
    let five = Some(5); // Option 枚举已经预导入，不需要使用 Option::Some()
    let six = plus_one(five);
    let none = plus_one(None);
}

fn plus_one(opt: Option<i32>) -> Option<i32> { // 传入一个 Option 枚举，返回一个 Option 枚举
    match opt {
        Some(i) => Some(i+1), // 如果有值，则将值加一，返回一个Option枚举
        None => None // 如果没值，就返回 None 变体
    }
}
```

#### 枚举与模式匹配

`if let` 可用于处理只关心一种变体匹配，忽略其他变体匹配的情况。

```rust
enum Weekday {
    Mon(String),
    Tues,
    Wed,
    Thur,
    Fri,
    Sat,
    Sun,
}

fn main() {
    let day = Weekday::Fri;
    match day {
        Weekday::Fri => println!("Friday"), // 只关注 `Weekday::Fri` ，其他变体忽略
        _ => (), // 返回空元组，表示什么都不做
    }

    if let Weekday::Fri = day { // 与上面的 match 匹配效果相同
        println!("Friday");
    }
}
```

`if let` 可以配合 `else` 使用：

```rust
fn main() {
    let day = Weekday::Fri;
    match day {
        Weekday::Fri => println!("Friday"),
        _ => println!("other"),
    }

    if let Weekday::Fri = day { // 与上面的 match 匹配效果相同 
        println!("Friday");
    } else {
        println!("other");
    }
}
```



### 参考资料

- Using Structs to Structure Related Data: <https://doc.rust-lang.org/book/ch05-00-structs.html> 
- Enums and Pattern Matching: <https://doc.rust-lang.org/book/ch06-00-enums.html> 



### 总结

Rust 中使用 `struct` 关键字定义结构体，使用 `enum` 关键字定义枚举，使用 `impl` 可以为结构体和枚举定义方法。

可以给结构体定义关联函数，关联函数使用结构名调用，而不是使用实例调用，类似 java 中的静态函数。

Rust 枚举使用 `match` 进行匹配，使用通配符 `_` 匹配剩余可能的变体，通配符匹配要放在最后，类似其他编程语言中 switch 的 default。

Rust 提供了 `if let` 来处理只需要关注一种枚举变体的情况，是 match 的语法糖。
