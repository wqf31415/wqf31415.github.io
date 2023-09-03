---
title: 认识 json-schema
tags:
  - json
categories:
  - 技术
date: 2020-04-02 10:33:29
---

### 概述

本文介绍了 json schema 的概念和用法。



### 什么是 json schema

![](https://blog-images.qiniu.wqf31415.xyz/json.png)

JSON Schema 是一种用来定义 json 数据结构的文件，JSON Schema 自身也是以 json 文档形式存在。JSON Schema 被设计用于对 json 文件进行校验、注释、链接导航、交互控制。官方提出了一种用于描述 JSON Schema 的新媒体类型（Media Type）：`application/schema+json` 。

> 官网: <http://json-schema.org> 
>
> GitHub: <https://github.com/json-schema-org/json-schema-spec> 
>
> JSON Schema Tool: <https://jsonschema.net/home> 



<!-- more -->



### 相关概念

#### 什么是 json

> 官网：<https://www.json.org/json-zh.html> 
>
> JSON 在线工具: <https://json.cn/> 

> JSON（JavaScript Object Notation），是一种轻量级的数据交换格式，具有易阅读编写，也易于机器解析和生成。json 采用完全独立于语言的文本格式，但也使用了类似于 C 语言家族的习惯（包括C, C++, C#, Java, JavaScript, Perl, Python等）。这些特性使JSON成为理想的数据交换语言。

json 对象包含在 `{}` 中，内容是一个无序的**键(key)/值(value)对**集合，键都是字符串

json 中的数据值类型包括：

- 字符串：用双引号 `""` 包括，如 `"name"` 、 "ZhangSan"
- 数值：可以是整形数字或浮点型数字，如 `12`、`-21`、`3.14`、`1.23E4` 
- 空：`null` 
- 布尔型：包括 `false` 和 `true` 
- json 对象：json对象以 `{}` 包含，内容可以是 0 到多个键值对，如 `{"name":"ZhangSan","age":18}`
- 数组：以 `[]` 包含，数组值可以是字符串、数值、空、布尔型、json对象、数组，可以是其中一类，也可以是它们的组合，每个值用英文逗号 `,` 分隔 ，如 `["string",123,null,false,{"a":"b"}]` 



#### 什么是 schema

schema 意为纲要、模式，是对事物结构性特征的描述。

json schema 就是用于描述 json 对象结构的工具，可以限定 json 的组成结构、键值类型、可选值等，在生成 json 文档时可以作为指导，也可以用 json schema 来验证 json 结构是否正确。

类似的技术还有 xml 的 DTD（文档类型定义），其作用是定义合法的 xml 文档构建模块，可以用来验证 xml 文档的结构合法性。



### Json Schema

#### 定义一个 json schema

在 json schema 中， `type` 关键字用于限定值的类型，如下限定类型为字符串：

```json
{"type":"string"}
```

#### 标识一个 json schema

由于 json schema 本身也是一个 json，所以很难与常规的 json 数据区分，所以推荐在 json schema 中增加一个属性 `$schema` ，用来标识这个 json 是个 json schema，如：

```json
{
    "$schema":"http://json-schema.org/schema#"
}
```

#### json schema 唯一标识

在构建复杂的模式时，多个 json schema 之间往往难以区别，所以建议在每个 json schema 中添加一个 `$id` 属性，一般是公司域名的 url，如：

```json
{
  "$id":"http://yourdomain.com/schemas/myschema.json"
}
```

#### type 关键字

在 json schema 中， `type` 关键字用于限定值的类型，可选值包括组成 json 的基本类型：

string、number、object、array、boolean、null

在使用 type 关键字时，可以限定单一数据类型，也可以是多个可选类型，多个可选类型时使用数组包含所有可选类型，如：

```json
{"type":"string"}
{"type":["string","number"]}
```

#### json schema 中的类型

##### 字符串 string

在 json schema 中，type 属性设置为 `"string"` ，即可限定值为字符串。

###### 字符串长度（length）

json schema 可以限定字符串的长度，使用 `minLength` 属性设定字符串最小长度，使用 `maxLength` 属性设定字符串最大长度。

```json
{
    "type":"string",
    "minLength":2,
    "maxLength":5
}
```

###### 正则表达式限定（pattern）

字符串类型可以添加 `pattern` 属性，使用正则表达式来限定字符串格式，如用来限定字符串为电话号码或 email 地址。

如：

```json
{
    "type":"string",
    "pattern":"^(\\([0-9]{3}\\))?[0-9]{3}-[0-9]{4}$"
}
```



###### 数据格式（format）

`format` 用于指定字符串的格式化方式，如日期时间的字符串格式化方式 `date-time` 格式化结果为 `2029-04-19T17:01:39+08:00` 。

可选项示例：

- 时期和时间格式化：`date-time`、`time` 、`date` 

- 邮箱地址：`email` 、`idn-email` 
- 主机名：`hostname` 、`idn-hostname` 
- IP 地址：`ipv4` 、`ipv6` 
- URI：`uri` 、`uri-reference` 、`iri` 、`iri-reference` 
- URL 模板：`url-template` 
- json 指针：`json-pointer` 、`relative-json-pointer`
- Regular 表达式：`regex` 

> 更多选项请参考：<http://json-schema.org/understanding-json-schema/reference/string.html#format> 



##### 数值 number

###### 整数（integer）

类型值 `integer` 用于指定整数，如 `12`，`-32`，带小数的数值和字符串形式的整数都不能通过校验 ，如 `1.23`，`"123"` 

```json
{
    "type":"integer"
}
```

###### 数值（number）

类型值 `number` 用来指定数值类型限定，整数、浮点数和科学计数法表示的数都能通过校验，如 `12` ，`-32` ，`3.14` ，`1.42E3` 。

```json
{
    "type":"number"
}
```

###### 倍乘数（multipleOf）

属性 `multipleOf` 属性用来限定数值是指定数的倍乘数，如属性值设定为 `10`，则 `0`，`20`， `120` 可以通过校验，`24` 不能通过校验，因为不是 10 的倍数。

```json
{
    "type":"number",
    "multipleOf":10
}
```

###### 范围（range）

限定数值范围的属性有四种： 

- `minimum`  最小值（包含该值）
- `exclusiveMinimum` 最小值（不包含该值）  
- `maximum`  最大值（包含该值）
- `exclusiveMaximum`  最大值（不包含该值）

上限和下限的属性可以同时使用，如限定 `0 ≤ X < 60` ：

```json
{
    "type":"number",
    "minimum":0,
    "exclusiveMaximum":60
}
```



##### 对象 object

类型值 `object` 用来限定值为 json 对象，任何非法的 json 对象或 json 数组都不能通过校验。

```json
{"type":"object"}
```

###### 属性（properties）

当类型指定为 `object` 时，可以使用 `properties` 属性来限定 json 对象中的属性，如：

```json
{
    "type":"object",
    "properties":{
        "age":{"type":"integer","minimum":0},
        "name":{"type":"string"},
        "sex":{
            "type":"string",
            "enum":["man","woman"]
        }
    }
}
```

###### 是否可附加属性（additionalProperties）

当类型指定为 `object` 时，可以添加 `additionalProperties` 属性来限定是否可以添加限定之外的附件属性。当这个值为 `false` 时，json 对象的属性只能是 `properties` 中指定的，不能有其它的属性。

###### 必需属性（required）

属性 `required` 可以限定 json 对象必需包含指定的属性。如：

```json
{
    "type":"object",
    "properties":{
        "name":{"type":"string"},
        "email":{"type":"string"},
        "address":{"type":"string"},
        "telephone":{"type":"string"}
    },
    "required":["name","email"]
}
```

如上 json schema 限定值为 json 对象，且必需包含 `name` 和 `email` 属性。

###### 属性名（propertyNames）

属性 `propertyNames` 用于限定 json 对象的属性名。

```json
{
  "type": "object",
  "propertyNames": {
    "pattern": "^[A-Za-z_][A-Za-z0-9_]*$"
  }
}
```

###### 属性数量（size）

`minProperties` 属性用于限定 json 对象中最少属性数量，属性数大于等于设定值的 json 对象可通过校验。

`maxProperties` 属性用于限定 json 对象中最大属性数量，属性数量小于等于这个值的 json 对象可以通过限定。

```json
{
    "type":"object",
    "minProperties":2,
    "maxProperties":3
}
```



###### 属性依赖（property dependencies）

属性依赖是指一个属性出现的时候，另一个依赖也必须出现，如有信用卡信息就必须有账单地址信息：

```json
{
  "type": "object",

  "properties": {
    "name": { "type": "string" },
    "credit_card": { "type": "number" },
    "billing_address": { "type": "string" }
  },

  "required": ["name"],

  "dependencies": {
    "credit_card": ["billing_address"]
  }
}
```

如上 json schema 所示，当 json 对象中有 `credit_card` 属性时，`billing_address` 也必须存在，否则无法通过校验；当 `credit_card` 和 `billing_address` 属性都不存在时也可以通过校验。

###### json schema 依赖（schema dependencies）

类似于对象属性依赖，json schema 依赖可以引用。用法：

```json
{
  "type": "object",

  "properties": {
    "name": { "type": "string" },
    "credit_card": { "type": "number" }
  },

  "required": ["name"],

  "dependencies": {
    "credit_card": {
      "properties": {
        "billing_address": { "type": "string" }
      },
      "required": ["billing_address"]
    }
  }
}
```

效果与上一个示例一致，写法不同。

###### 模式属性（pattern properties）

`patternProperties` 用于限定对象中的属性名称模式，如限定所有属性名以 `s_` 开头的属性都是字符串类型，所有以 `i_` 开头的属性的值都是整形：

```json
{
    "type":"object",
    "patternProperties":{
        "^s_":{"type":"string"},
        "^i_":{"type":"integer"}
    },
    "additionalProperties":false
}
```

> 限定方式与正则表达式相同，如果要限制属性名后缀，可以使用 `xxx$` 来限定。这个例子中的 `additionalProperties` 作用是排除不满足匹配格式的属性，是必须的。



##### 数组 array

类型值设置为 `array` 可以限定值是一个 json 数组。

```json
{"type":"array"}
```

###### 数组值（items）

用于限定数组中元素的类型，可以限定数组中的元素只能是一种类型，如一个数值类型的数组：

```json
{
    "type":"array",
    "items":{
        "type":"number"
    }
}
```

版本 6 中的写法：

```json
{
    "type":"array",
    "contains":{
        "type":"number"
    }
}
```

###### 元组校验（tuple validation）

元组校验可以对数组中每一个元素进行校验。

```json
{
  "type": "array",
  "items": [
    {
      "type": "number"
    },
    {
      "type": "string"
    },
    {
      "type": "string",
      "enum": ["Street", "Avenue", "Boulevard"]
    },
    {
      "type": "string",
      "enum": ["NW", "NE", "SW", "SE"]
    }
  ]
}
```

> 这个示例中，对数组前四个元素做了限定，如果数组元素数量不足 4 个，但满足前几个的约束条件，也可以通过校验；如果数组元素个数超过 4，只需要前 4 个元素满足约束条件，也是能够通过校验的。

###### 数组长度（length）

使用 `minItems` 限制最低长度，使用 `maxItems` 属性限定数组最大长度，如：

```json
{
    "type":"array",
    "minItems":2,
    "maxItems":4
}
```

###### 元素唯一限定（uniqueness）

`uniqueItems` 属性用于限定数组元素是否唯一，数组元素唯一即是指数组是一个集合（set）。

```json
{
    "type":"array",
    "unqueItems":true
}
```



##### 布尔型 boolean

```json
{
    "type":"boolean"
}
```

类型值 `boolean` 用来限定值为布尔型，只有 `true` 和 `false` 可以通过校验。



##### 空值 null

```json
{"type":"null"}
```

类型值 `null` 用来限定值为空，即 `null` 。

#### 注解

在 json schema 中使用注解属性增加了附加信息，增强了可读性。注解包括：

- `title` 标题
- `description` 描述
- `default` 默认值
- `examples` 示例

示例：

```json
{
  "title" : "Match anything",
  "description" : "This is a schema that matches anything.",
  "default" : "Default value",
  "examples" : [
    "Anything",
    4035
  ]
}
```



#### 枚举（enum）

枚举可以用来限定值的可选范围。

```json
{
    "type":"string",
    "enum":["red","amber","green"]
}
```



#### 常量（const）

`const` 属性用于限定值只能是指定的值。如：

```json
{
    "properties":{
        "country":{
            "const":"China"
        }
    }
}
```



#### 字符串编码的非 json 数据

使用 `contentMediaType` 属性指定内容的 MediaType，使用 `contentEncoding` 属性指定内容的编码方式。如

```json
{
  "type": "string",
  "contentEncoding": "base64",
  "contentMediaType": "image/png"
}
```



#### 组合模式

- `allOf` 需要满足所有限定条件

  ```json
  {
    "allOf": [
      { "type": "string" },
      { "maxLength": 5 }
    ]
  }
  ```

  

- `anyOf` 需要满足一个或多个条件

  ```json
  {
    "anyOf": [
      { "type": "string", "maxLength": 5 },
      { "type": "number", "minimum": 0 }
    ]
  }
  ```

  

- `oneOf` 满足其中一个条件

  ```json
  {
    "oneOf": [
      { "type": "number", "multipleOf": 5 },
      { "type": "number", "multipleOf": 3 }
    ]
  }
  ```

  

- `not` 不满足限定条件

  ```json
  { "not": { "type": "string" } }
  ```



#### 条件

在 draft 7 版本中，可使用 `if` 、`then` 和 `else` 关键字来组合限定条件。如：

```json
{
  "type": "object",
  "properties": {
    "street_address": {
      "type": "string"
    },
    "country": {
      "enum": ["United States of America", "Canada"]
    }
  },
  "if": {
    "properties": { "country": { "const": "United States of America" } }
  },
  "then": {
    "properties": { "postal_code": { "pattern": "[0-9]{5}(-[0-9]{4})?" } }
  },
  "else": {
    "properties": { "postal_code": { "pattern": "[A-Z][0-9][A-Z] [0-9][A-Z][0-9]" } }
  }
}
```



#### `$schema` 关键字

`$schema` 关键字用于声明一个 json 是一个 json schema，同时还声明了 json schema 的版本，建议每一个 json schema 中都添加一个 `$schema` 属性，且放到根目录中。

```json
{"$schema": "http://json-schema.org/draft/2019-09/schema#"}
```

`$schema` 的值应该是针对特定版本的 json schema 标准编写的，并在路径中包括使用的版本，如：

```
http://json-schema.org/draft/2019-09/schema#
http://json-schema.org/draft-07/schema#
http://json-schema.org/draft-06/schema#
http://json-schema.org/draft-04/schema#
```



#### 重用

##### 结构定义（definitions）

在 json schema 中定义结构的意义在于重用已有定义，让结构更加简洁，建议将结构定义放在父架构中，然后使用 `$ref` 关键字在其他地方引用此模式片段，在逻辑上用它所指向的东西替换它。

```json
{
  "$schema": "http://json-schema.org/draft-07/schema#",

  "definitions": {
    "address": {
      "type": "object",
      "properties": {
        "street_address": { "type": "string" },
        "city":           { "type": "string" },
        "state":          { "type": "string" }
      },
      "required": ["street_address", "city", "state"]
    }
  },

  "type": "object",

  "properties": {
    "billing_address": { "$ref": "#/definitions/address" },
    "shipping_address": { "$ref": "#/definitions/address" }
  }
}
```

##### 递归

使用 `$ref` 创建引用自身即可达到递归的效果，如一个 `person` 架构，其中包含一个数组 `children` ，每个数组也是一个 `person` 实例。

```json
{
  "$schema": "http://json-schema.org/draft-07/schema#",

  "definitions": {
    "person": {
      "type": "object",
      "properties": {
        "name": { "type": "string" },
        "children": {
          "type": "array",
          "items": { "$ref": "#/definitions/person" },
          "default": []
        }
      }
    }
  },

  "type": "object",

  "properties": {
    "person": { "$ref": "#/definitions/person" }
  }
}
```



##### `$id` 属性

`$id` 属性时一个 URI 引用，它可以为模式声明唯一的标识符，还可以声明一个基本 URI，可以针对该基本 URI `$ref` 引用进行解析。建议在每个顶级 schema 的 `$id` 应使用绝对 URI，而不是相对引用。如引用 `foo.bar` 中的 `address` 架构：

```json
{ "$id": "http://foo.bar/schemas/address.json" }
```

最佳使用模式是将 `$id` 与 `$ref` 一起使用，如：

```json
{
  "$schema": "http://json-schema.org/draft-07/schema#",

  "definitions": {
    "address": {
      "$id": "#address",
      "type": "object",
      "properties": {
        "street_address": { "type": "string" },
        "city":           { "type": "string" },
        "state":          { "type": "string" }
      },
      "required": ["street_address", "city", "state"]
    }
  },

  "type": "object",

  "properties": {
    "billing_address": { "$ref": "#address" },
    "shipping_address": { "$ref": "#address" }
  }
}
```





### 使用

json schema 是一个概念，有很多第三方提供的实现，包括各种编程语言的，如 C、C++、Java、JavaScript 等，可以用来校验 json，或生成 json。

> 官方推荐的实现：<http://json-schema.org/implementations.html> 



#### maven

```xml
<dependency>
    <groupId>com.github.fge</groupId>
    <artifactId>json-schema-validator</artifactId>
    <version>2.2.6</version>
</dependency>

```



### 参考资料

- 使用JSON Schema校验JSON数据是否合规: <https://blog.csdn.net/zjg379569986/article/details/84634803> 
- JSON Schema 详解: <https://blog.csdn.net/swinfans/article/details/89231247> 

- JSON简介 - 简书: <https://www.jianshu.com/p/1970a209672f> 
- JSON: <https://www.json.org/json-zh.html> 