---
title: MySQL开启密码复杂度验证
date: 2021-02-23 19:09:08
tags:
- mysql
- database
- 数据库
categories:
- mysql
---

### 概述

数据库密码的复制程度关系的数据的安全性，这篇文章介绍了在 MySQL 和 MariaDB 数据库中开启密码复杂度校验的方法，开启校验功能后，用户不能再创建简单密码的账户，能够大大提升安全性。

![](https://blog-images.qiniu.wqf31415.xyz/lock.jpg)



### 关于密码复杂度

安全的密码通常要求长度不低于8位，包含字母、数字、特殊字符。



<!-- more -->



### MariaDB 开启密码复杂度验证

在 MariaDB 中使用 simple_password_check 插件进行密码复杂度校验。

#### 查看数据库密码相关的变量

```sql
show variables like '%password%';
```

结果：

```
+----------------------------+-------+
| Variable_name              | Value |
+----------------------------+-------+
| old_passwords              | OFF   |
| report_password            |       |
| strict_password_validation | ON    |
+----------------------------+-------+
```

此时没有开启密码复杂度验证，可以创建简单密码的用户：

```sql
CREATE USER 'mytest'@'localhost' IDENTIFIED BY '12345';
```



#### MariaDB 安装密码检查插件

```sql
install SONAME 'simple_password_check';
```

安装成功后，即开启密码复杂度验证，此时再查询密码相关的变量，结果：

```
+-----------------------------------------+-------+
| Variable_name                           | Value |
+-----------------------------------------+-------+
| old_passwords                           | OFF   |
| report_password                         |       |
| simple_password_check_digits            | 1     |
| simple_password_check_letters_same_case | 1     |
| simple_password_check_minimal_length    | 8     |
| simple_password_check_other_characters  | 1     |
| strict_password_validation              | ON    |
+-----------------------------------------+-------+
```

> 参数说明：
>
> - *simple_password_check_digits* ：密码至少要包含数字的个数
> - *simple_password_check_letters_same_case* ：密码至少要包含大写字母个数和小写字母个数
> - *simple_password_check_minimal_length* ：密码最小长度
> - *simple_password_check_other_characters* ：密码至少要包含的特殊字符个数
>
> 当前密码要求：至少8位，且包含大写字母、小写字母、数字、特殊字符。

安装插件后，已不能创建简单密码的用户，当密码复杂度不满足要求时，报错：

```
ERROR 1819 (HY000): Your password does not satisfy the current policy requirements
```

用户密码需要至少8位，且包含大小写字母、数字、特殊字符，如：

```sql
CREATE USER 'mytest1'@'localhost' IDENTIFIED BY 'Qq@12345';
```



#### 修改复杂度配置

如修改特殊字符数量，其他同理：

```sql
set global simple_password_check_other_characters=2;
```



#### 卸载密码检查插件

```sql
uninstall SONAME 'simple_password_check';
```



### MySQL 

MySQL 中使用 validate_password 插件进行密码复杂度校验，这里以 MySQL 5.7.33 为例。

#### 先查看系统变量

默认未启用密码复杂度校验，可创建简单密码用户：

```sql
CREATE USER 'mytest'@'localhost' IDENTIFIED BY '12345';
```

查询与密码相关的系统参数：

```sql
show variables like '%password%';
```

结果：

```
+----------------------------------------+-----------------+ 
| Variable_name                          | Value           | 
+----------------------------------------+-----------------+ 
| default_password_lifetime              | 0               | 
| disconnect_on_expired_password         | ON              | 
| log_builtin_as_identified_by_password  | OFF             | 
| mysql_native_password_proxy_users      | OFF             | 
| old_passwords                          | 0               | 
| report_password                        |                 | 
| sha256_password_auto_generate_rsa_keys | ON              | 
| sha256_password_private_key_path       | private_key.pem | 
| sha256_password_proxy_users            | OFF             | 
| sha256_password_public_key_path        | public_key.pem  | 
+----------------------------------------+-----------------+ 
```



#### 安装密码校验插件

```sql
install plugin validate_password soname 'validate_password.so';
```

再查看系统参数：

```
+----------------------------------------+-----------------+
| Variable_name                          | Value           |
+----------------------------------------+-----------------+
| default_password_lifetime              | 0               |
| disconnect_on_expired_password         | ON              |
| log_builtin_as_identified_by_password  | OFF             |
| mysql_native_password_proxy_users      | OFF             |
| old_passwords                          | 0               |
| report_password                        |                 |
| sha256_password_auto_generate_rsa_keys | ON              |
| sha256_password_private_key_path       | private_key.pem |
| sha256_password_proxy_users            | OFF             |
| sha256_password_public_key_path        | public_key.pem  |
| validate_password_check_user_name      | OFF             |
| validate_password_dictionary_file      |                 |
| validate_password_length               | 8               |
| validate_password_mixed_case_count     | 1               |
| validate_password_number_count         | 1               |
| validate_password_policy               | MEDIUM          |
| validate_password_special_char_count   | 1               |
+----------------------------------------+-----------------+
```

>参数说明：
>
>- *validate_password_check_user_name* ：用户名监测（新版本的才有）
>- *validate_password_dictionary_file* ：插件用于验证密码强度的字典文件路径
>- *validate_password_length* ：密码最小长度
>- *validate_password_mixed_case_count* ：密码至少要包含的小写字母个数和大写字母个数 
>- *validate_password_number_count* ：密码至少要包含的数字个数
>- *validate_password_policy* ：密码强度检查等级
>  - `0`/`LOW` ：只检查长度
>  - `1`/`MEDIUM`：检查长度、数字、大小写、特殊字符
>  - `2`/`STRONG`：检查长度、数字、大小写、特殊字符字典文件
>- *validate_password_special_char_count* ：密码至少要包含的特殊字符数

插件安装成功后，即启用密码校验，再次创建简单密码用户，将报错:

```
ERROR 1819 (HY000): Your password does not satisfy the current policy requirements
```

创建密码复杂度符合要求的用户：

```sql
CREATE USER 'mytest1'@'localhost' IDENTIFIED BY 'Qq@12345';
```



#### 修改密码复杂度校验配置

使用修改 MySQL 变量参数的方法修改密码复杂度校验配置，如修改密码最小长度，其他项同理：

```sql
set global validate_password_length=10;
```



#### 卸载密码校验插件

```sql
uninstall PLUGIN validate_password;
```



### 参考资料

- mariadb:简单密码检查插件(转载) : <https://www.cnblogs.com/huiy/p/13461596.html> 
- MySQL密码强度审计插件:validate_password的使用说明: <http://www.xuchanggang.cn/archives/1033.html> 
- mysql新版本中的validate_password插件测试：<https://www.58jb.com/html/162.html> 
- mysql之validate_password_policy: <https://blog.csdn.net/wltsysterm/article/details/79649484> 



### 总结

这篇文章介绍的方式是在线安装插件，不需要重启数据库，方便使用。