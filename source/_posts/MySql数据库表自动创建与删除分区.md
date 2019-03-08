---
title: MySql数据库表自动创建与删除分区
date: 2019-02-14 14:31:18
tags:
- mysql
- 数据库
categories:
- 技术
---

### 简述

数据库中表数据量太大时，查询速度变慢，而且在进行数据迁移时不方便。我们可以对数据量较大（超2GB）的表进行分区，以提高查询效率，方便数据维护。文章中示例了按时间对数据库表进行分区，并使用数据库存储过程与事件完成数据库表分区的自动创建与删除。

### 环境

- 数据库：MySQL 5.7
- 工具：Navicat for MySQL 10.1.7

![](http://blog-images.qiniu.wqf31415.xyz/database_patition_1.jpg)

<!-- more -->

### 数据库与表

- 数据库：cma

  ``````sql
  CREATE DATABASE cma；
  ``````

- 表：meteorology_sensor

  ``````sql
  create table meteorology_sensor (id bigint COMMENT '主键，自动生成' not null auto_increment, collected_time timestamp COMMENT '数据采集时间', component_id char(17) COMMENT '被监测设备ID', device_code char(17) COMMENT '设备编号' not null, device_id bigint COMMENT '设备Id', protocol_version char(5) COMMENT '数据上传时使用的版本号,值为：v2010、v2015', send_state tinyint(1) COMMENT '推送CAG状态，1 成功，0 未推送，-1 推送失败', air_pressure decimal(10,1) COMMENT '气压，浮点数，精确到小数点后1位，单位：hPa', air_temperature decimal(10,1) COMMENT '气温，浮点数，精确到小数点后1位，单位：℃', alarm_flag smallint COMMENT '报警标识，新协议没有这个字段', average_wind_direction10min smallint COMMENT '10分钟平均风向，无符号整数，单位：°', average_wind_speed10min decimal(10,1) COMMENT '十分钟平均风速，浮点数，精确到小数点后1位，单位：m/s', extreme_wind_speed decimal(10,1) COMMENT '极大风速，浮点数，精确到小数点后1位，单位：m/s', humidity smallint COMMENT '湿度，无符号整数，单位：%RH', max_wind_speed decimal(10,1) COMMENT '最大大风速，浮点数，精确到小数点后1位，单位：m/s', precipitation decimal(10,1) COMMENT '降雨量，浮点数，精确到小数点后1位，单位：mm', precipitation_intensity decimal(10,1) COMMENT '降水强度，浮点数，精确到小数点后1位，单位：mm/min', radiation_intensity smallint COMMENT '光辐射强度，无符号整数，单位：W/m2', second_time_stamp Timestamp COMMENT '报文中的时间戳', standard_wind_speed decimal(10,1) COMMENT '标准风速，浮点数，精确到小数点后1位，单位：m/s', primary key (id)) ENGINE=InnoDB
  ``````

### 数据库表分区

#### 添加主键

> **注意：分区字段必须是主键。** 在这里，我们需要使用表中的时间字段(collected_time)进行分区，所以需要将其添加为主键，与原有主键(id)组成联合主键。

使用 Navicat 打开数据库，对表结构进行修改，将 collected_time 设置为主键。

![](http://blog-images.qiniu.wqf31415.xyz/modify_primary_key_by_navicat.png "使用 Navicat 修改数据库表主键")

或执行 SQL 语句修改表结构：

``````sql
ALTER TABLE `meteorology_sensor` DROP PRIMARY KEY ,ADD PRIMARY KEY ( `id`,`collected_time`);
``````

#### 初始分区

按时间范围分区，每年按季度分区，每3个月为一个分区。
> 注意：最后要建一个 less than (maxvalue) 的分区(p_future)，将超过设定分区时间的数据都放到这个分区里。

- 使用 Navicat 进行分区

  1. 设计表 -> 选项 -> 分割区

  ![](http://blog-images.qiniu.wqf31415.xyz/create_partition_by_navicat_1.png "Navicat 分区1")

  2. 添加分区( less than )

  ![](http://blog-images.qiniu.wqf31415.xyz/create_partition_by_navicat_2.png "Navicat 分区2")
  
  3. 添加最后一个分区( less than maxvalue)
  
  ![](http://blog-images.qiniu.wqf31415.xyz/create_partition_by_navicat_3.png "Navicat 分区3")
  
  4. 确定分区后，点击确定回到设计表界面，点击 “保存” 完成分区。

- 使用 SQL 语句进行分区

  ``````sql
  ALTER TABLE cma.meteorology_sensor PARTITION by RANGE (UNIX_TIMESTAMP(collected_time))
  (
  PARTITION p201803 VALUES less than (UNIX_TIMESTAMP('2018-04-01')),
  PARTITION p201806 VALUES less than (UNIX_TIMESTAMP('2018-07-01')),
  PARTITION p201809 VALUES less than (UNIX_TIMESTAMP('2018-10-01')),
  PARTITION p201812 VALUES less than (UNIX_TIMESTAMP('2019-01-01')),
  PARTITION p201903 VALUES less than (UNIX_TIMESTAMP('2019-04-01')),
  PARTITION p_future VALUES LESS THAN (MAXVALUE)
  );
  ``````
  
- 查看分区文件
  进入 MySQL 的数据存储目录下，查看数据库的文件，发现出现了如下的分区文件：
  ![](http://blog-images.qiniu.wqf31415.xyz/partition_file.png "分区文件")

#### 创建新分区的存储过程

  ``````sql
DROP PROCEDURE IF EXISTS cma.create_new_partitions;

DELIMITER $$
CREATE PROCEDURE cma.create_new_partitions(p_schema varchar(64), p_table varchar(64), p_months_to_add int)
-- 参数：
-- p_schema: 数据库名
-- p_table: 表名
-- p_months_to_add: 要多添加的月数
   LANGUAGE SQL
   NOT DETERMINISTIC
   SQL SECURITY INVOKER
   comment '给指定数据库(p_schema)的指定数据表(p_table)创建分区，分区数为当前月加上随后(p_months_to_add)个月的'
BEGIN  
   DECLARE done INT DEFAULT FALSE;
   DECLARE current_partition_name varchar(64);
   DECLARE current_partition_ts int;
   
   -- We'll use this cursor later to check
   -- whether a particular already exists.
   -- @partition_name_to_add will be
   -- set later.
   DECLARE cur1 CURSOR FOR 
   SELECT partition_name 
   FROM information_schema.partitions 
   WHERE TABLE_SCHEMA = p_schema 
   AND TABLE_NAME = p_table 
   AND PARTITION_NAME != 'p_first'
   AND PARTITION_NAME != 'p_future'
   AND PARTITION_NAME = @partition_name_to_add;
   
   -- We'll also use this cursor later 
   -- to query our temporary table.
   DECLARE cur2 CURSOR FOR 
   SELECT partition_name, partition_range_ts 
   FROM partitions_to_add;
   
   DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
   
   DROP TEMPORARY TABLE IF EXISTS partitions_to_add;
   
   CREATE TEMPORARY TABLE partitions_to_add (
      partition_name varchar(64),
      partition_range_ts int
   );
   
   SET @partitions_added = FALSE;
   SET @months_ahead = 0;
   
   -- Let's go through a loop and add each month individually between
   -- the current month and the month p_months_to_add in the future.
   WHILE @months_ahead <= p_months_to_add DO
      -- We figure out what the correct month is by adding the
      -- number of months to the current date
      SET @date = CURDATE();
      SET @q = 'SELECT DATE_ADD(?, INTERVAL ? MONTH) INTO @month_to_add';
      PREPARE st FROM @q;
      EXECUTE st USING @date, @months_ahead;
      DEALLOCATE PREPARE st;
      SET @months_ahead = @months_ahead + 1;
      
      -- Then we format the month in the same format used
      -- in our partition names.
      SET @q = 'SELECT DATE_FORMAT(@month_to_add, ''%Y%m'') INTO @formatted_month_to_add';
      PREPARE st FROM @q;
      EXECUTE st;
      DEALLOCATE PREPARE st;
      
      -- And then we use the formatted date to build the name of the
      -- partition that we want to add. This partition name is
      -- assigned to @partition_name_to_add, which is used in
      -- the cursor declared at the start of the procedure.
      SET @q = 'SELECT CONCAT(''p'', @formatted_month_to_add) INTO @partition_name_to_add';
      PREPARE st FROM @q;
      EXECUTE st;
      DEALLOCATE PREPARE st;
     
      SET done = FALSE; 
      SET @first = TRUE;
     
      -- And then we loop through the results returned by the cursor,
      -- and if a row already exists for the current partition, 
      -- then we do not need to create the partition.
      OPEN cur1;

      read_loop: LOOP
         FETCH cur1 INTO current_partition_name;
      
         -- The cursor returned 0 rows, so we can create the partition.
         IF done AND @first THEN
            SELECT CONCAT('Creating partition: ', @partition_name_to_add);

            -- Now we need to get the end date of the new partition.
            -- Note that the date is for the non-inclusive end range,
            -- so we actually need the date of the first day of the *next* month.

            -- First, let's get a date variable for the first of the partition month
            SET @q = 'SELECT DATE_FORMAT(@month_to_add, ''%Y-%m-01 00:00:00'') INTO @month_to_add';
            PREPARE st FROM @q;
            EXECUTE st;
            DEALLOCATE PREPARE st; 

            -- Then, let's add 1 month
            SET @q = 'SELECT DATE_ADD(?, INTERVAL 1 MONTH) INTO @partition_end_date';
            PREPARE st FROM @q;
            EXECUTE st USING @month_to_add;
            DEALLOCATE PREPARE st;

            -- We need the date in UNIX timestamp format.  
            SELECT UNIX_TIMESTAMP(@partition_end_date) INTO @partition_end_ts;
         
            -- Now insert the information into our temporary table
            INSERT INTO partitions_to_add VALUES (@partition_name_to_add, @partition_end_ts);
            SET @partitions_added = TRUE;
         END IF;
        
         -- Since we had at least one row returned, we know the
         -- partition already exists.
         IF ! @first THEN
            LEAVE read_loop;
         END IF;
        
         SET @first = FALSE;
      END LOOP;
     
     CLOSE cur1;
   END WHILE;
   
   -- Let's actually add the partitions now.
   IF @partitions_added THEN
      -- First we need to build the actual ALTER TABLE query.
      SET @schema = p_schema;
      SET @table = p_table;
      SET @q = 'SELECT CONCAT(''ALTER TABLE '', @schema, ''.'', @table, '' REORGANIZE PARTITION p_future INTO ( '') INTO @query';
      PREPARE st FROM @q;
      EXECUTE st;
      DEALLOCATE PREPARE st;
     
      SET done = FALSE;
      SET @first = TRUE;
     
      OPEN cur2;

      read_loop: LOOP
         FETCH cur2 INTO current_partition_name, current_partition_ts;
       
        IF done THEN
            LEAVE read_loop;
         END IF;
      
         -- If it is not the first partition, 
         -- then we need to add a comma
         IF ! @first THEN
            SET @q = 'SELECT CONCAT(@query, '', '') INTO @query';
            PREPARE st FROM @q;
            EXECUTE st;
            DEALLOCATE PREPARE st;
         END IF;

         -- Add the current partition
         SET @partition_name =  current_partition_name;
         SET @partition_ts =  current_partition_ts;         
         SET @q = 'SELECT CONCAT(@query, ''PARTITION '', @partition_name, '' VALUES LESS THAN ('', @partition_ts, '')'') INTO @query';
         PREPARE st FROM @q;
         EXECUTE st;
         DEALLOCATE PREPARE st;
       
         SET @first = FALSE;
      END LOOP;
     
      CLOSE cur2;
     
      -- We also need to include the p_future partition
      SET @q = 'SELECT CONCAT(@query, '', PARTITION p_future VALUES LESS THAN (MAXVALUE))'') INTO @query';
      PREPARE st FROM @q;
      EXECUTE st;
      DEALLOCATE PREPARE st;
     
      -- And then we prepare and execute the ALTER TABLE query.
      PREPARE st FROM @query;
      EXECUTE st;
      DEALLOCATE PREPARE st;  
   END IF;
   
   DROP TEMPORARY TABLE partitions_to_add;
END$$
DELIMITER ;
  ``````

#### 创建删除分区存储过程

  ``````sql
  DROP PROCEDURE IF EXISTS cma.drop_old_partitions;

DELIMITER $$
CREATE PROCEDURE cma.drop_old_partitions(p_schema varchar(64), p_table varchar(64), p_months_to_keep int, p_seconds_to_sleep int)
-- 参数：
-- p_schema: 数据库名
-- p_table: 数据库表名
-- p_months_to_keep: 保留的分区数
-- p_seconds_to_sleep: 删除分区时等待时间，单位：秒
   LANGUAGE SQL
   NOT DETERMINISTIC
   SQL SECURITY INVOKER
   comment '删除指定数据库(p_schema)的指定数据表(p_table)的老分区，保留的分区数为(p_months_to_keep) +1 个，每次删除分区时会等待(p_seconds_to_sleep)秒'
BEGIN  
   DECLARE done INT DEFAULT FALSE;
   DECLARE current_partition_name varchar(64);
   
   -- We'll use this cursor later to get
   -- the list of partitions to drop.
   -- @last_partition_name_to_keep will be
   -- set later.
   DECLARE cur1 CURSOR FOR 
   SELECT partition_name 
   FROM information_schema.partitions 
   WHERE TABLE_SCHEMA = p_schema 
   AND TABLE_NAME = p_table 
   AND PARTITION_NAME != 'p_first'
   AND PARTITION_NAME != 'p_future'
   AND PARTITION_NAME < @last_partition_name_to_keep;
   
   DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
   
   -- Now we get the last month of data that we want to keep
   -- by subtracting p_months_to_keep from the current date.
   -- Note that it will actually keep p_months_to_keep+1 partitions,
   -- since the current month is not complete.
   SET @date = CURDATE();
   SET @months_to_keep = p_months_to_keep;   
   SET @q = 'SELECT DATE_SUB(?, INTERVAL ? MONTH) INTO @last_month_to_keep';
   PREPARE st FROM @q;
   EXECUTE st USING @date, @months_to_keep;
   DEALLOCATE PREPARE st;
   
   -- Then we format the last month in the same format used
   -- in our partition names.
   SET @q = 'SELECT DATE_FORMAT(@last_month_to_keep, ''%Y%m'') INTO @formatted_last_month_to_keep';
   PREPARE st FROM @q;
   EXECUTE st;
   DEALLOCATE PREPARE st;
   
   -- And then we use the formatted date to build the name of the
   -- last partition that we want to keep. This partition name is
   -- assigned to @last_partition_name_to_keep, which is used in
   -- the cursor declared at the start of the procedure.
   SET @q = 'SELECT CONCAT(''p'', @formatted_last_month_to_keep) INTO @last_partition_name_to_keep';
   PREPARE st FROM @q;
   EXECUTE st;
   DEALLOCATE PREPARE st;
   
   SELECT CONCAT('Dropping all partitions before: ', @last_partition_name_to_keep);
   
   SET @first = TRUE;
   
   -- And then we loop through all partitions returned by the cursor,
   -- and those partitions are dropped.
   OPEN cur1;

   read_loop: LOOP
      FETCH cur1 INTO current_partition_name;
   
      IF done THEN
         LEAVE read_loop;
      END IF;
     
      IF ! @first AND p_seconds_to_sleep > 0 THEN
         SELECT CONCAT('Sleeping for ', p_seconds_to_sleep, ' seconds');
         SELECT SLEEP(p_seconds_to_sleep);
      END IF;

      SELECT CONCAT('Dropping partition: ', current_partition_name);
   
      -- First we build the ALTER TABLE query.
      SET @schema = p_schema;
      SET @table = p_table;
      SET @partition = current_partition_name;
      SET @q = 'SELECT CONCAT(''ALTER TABLE '', @schema, ''.'', @table, '' DROP PARTITION '', @partition) INTO @query';
      PREPARE st FROM @q;
      EXECUTE st;
      DEALLOCATE PREPARE st;
      
      -- And then we prepare and execute the ALTER TABLE query.
      PREPARE st FROM @query;
      EXECUTE st;
      DEALLOCATE PREPARE st;
     
      SET @first = FALSE;
   END LOOP;
   
   CLOSE cur1;
   
   -- If no partitions were dropped, then we can also skip this.
   IF ! @first THEN
      -- Then we need to get the date of the new first partition.
      -- We need the date in UNIX timestamp format.
      SET @q = 'SELECT DATE_FORMAT(@last_month_to_keep, ''%Y-%m-01 00:00:00'') INTO @new_first_partition_date';
      PREPARE st FROM @q;
      EXECUTE st;
      DEALLOCATE PREPARE st;     
      SELECT UNIX_TIMESTAMP(@new_first_partition_date) INTO @new_first_partition_ts;
     
      -- We also need to get the date of the second partition
      -- since the second partition is also needed for REORGANIZE PARTITION.
      SET @q = 'SELECT DATE_ADD(@new_first_partition_date, INTERVAL 1 MONTH) INTO @second_partition_date';
      PREPARE st FROM @q;
      EXECUTE st;
      DEALLOCATE PREPARE st;
      SELECT UNIX_TIMESTAMP(@second_partition_date) INTO @second_partition_ts;
  
      SELECT CONCAT('Reorganizing first and second partitions. first partition date = ', @new_first_partition_date, ', second partition date = ', @second_partition_date);
   
      -- Then we build the ALTER TABLE query.
      SET @schema = p_schema;
      SET @table = p_table;
      SET @q = 'SELECT CONCAT(''ALTER TABLE '', @schema, ''.'', @table, '' REORGANIZE PARTITION p_first, '', @last_partition_name_to_keep, '' INTO ( PARTITION p_first VALUES LESS THAN ( '', @new_first_partition_ts, '' ), PARTITION '', @last_partition_name_to_keep, '' VALUES LESS THAN ( '', @second_partition_ts, '' ) ) '') INTO @query';
      PREPARE st FROM @q;
      EXECUTE st;
      DEALLOCATE PREPARE st;
     
      -- And then we prepare and execute the ALTER TABLE query.
      PREPARE st FROM @query;
      EXECUTE st;
      DEALLOCATE PREPARE st;
   END IF;
END$$
DELIMITER ;
  ``````

#### 创建删除老分区并创建新分区的存储过程

  ``````sql
DROP PROCEDURE IF EXISTS cma.perform_partition_maintenance;

DELIMITER $$
CREATE PROCEDURE cma.perform_partition_maintenance(p_schema varchar(64), p_table varchar(64), p_months_to_add int, p_months_to_keep int, p_seconds_to_sleep int)
	-- 先删除老的分区，再生成新的分区
	-- 参数：p_chema: 数据库名；
	-- p_table: 数据表名；
	-- p_months_to_add: 创建分区时，添加的分区数量，例如：当值为0时，只会创建当前月的分区，当值为2时，会创建当前月和后2个月的分区；
	-- p_months_to_keep: 删除分区时， 保留的分区数量，保留的分区数会多1，例如：当值为3时，会保留4个分区；
	-- p_seconds_to_sleep: 删除分区时，等待删除的时间，单位：秒；
   LANGUAGE SQL
   NOT DETERMINISTIC
   SQL SECURITY INVOKER
   comment '指定数据库(p_schema)的指定数据表(p_table)，先删除老分区，再创建新分区，删除时保留的分区数为(p_months_to_keep) +1 个，每次删除分区时会等待(p_seconds_to_sleep)秒，创建的新分区数为当前月加上随后(p_months_to_add)个月的'
BEGIN 
   CALL cma.drop_old_partitions(p_schema, p_table, p_months_to_keep, p_seconds_to_sleep);
   CALL cma.create_new_partitions(p_schema, p_table, p_months_to_add);
END$$
DELIMITER ;
  ``````
  
#### 创建定时执行的事件

  ``````sql
DROP EVENT if EXISTS cma.monthly_event_meteorology_sensor;

-- 创建定时事件：从现在时间开始，每隔一个月执行一次，自动删除老的分区，创建新的分区
CREATE EVENT cma.monthly_event_meteorology_sensor
   ON SCHEDULE
   EVERY 1 MONTH
   STARTS NOW()
COMMENT '微气象数据，从现在开始，每月定时删除分区、创建新分区'
DO
   CALL cma.perform_partition_maintenance('cma', 'meteorology_sensor', 3, 6, 5);
  ``````
  
### 注意事项
- 作为分区的字段需要设置为外键，否则无法分区。
- 被分区的表中不能有外键，否则无法分区，分区时 mysql 会报 **1506** 错误。

### MySQL 中其它分区方式
在上面的示例中，我们按字段值的范围(RANGE)进行分区，在 MySQL 中还提供的分区方式：
- 范围分区(RANGE): 按连续的区间范围把数据分到不同分区中，要求分区范围不能重叠，而且必须连续。
- 列表分区(LIST): 按枚举出的值进行分区，如按地理位置不同将数据分到不同区，东北、华北、华南...。
- 散列分区(HASH): 基于给定的分区数，通过用户定义的计算后，将数据分到不同分区。这个函数可以包含MySQL 中有效的、产生非负整数值的任何表达式。
- 键分区(KEY): 类似 HASH 分区，区别在于 KEY 分区只支持一列或多列，且MySQL服务器提供其自身的哈希函数。必须有一列或多列包含整数值。
- 线性散列分区(LINEAR_HASH): 与常规哈希的区别在于，线性哈希功能使用的一个线性的2的幂（powers-of-two）运算法则，而常规哈希使用的是求哈希函数值的模数
- 线性键(LINEAR_KEY): 与常规 KEY 的区别也是使用的一个线性的2的幂（powers-of-two）运算法则。


### 参考资料
- 数据库分区及分区优点: [https://blog.csdn.net/liukun321/article/details/45823795](https://blog.csdn.net/liukun321/article/details/45823795)
- Automatic Partition Maintenance in MySQL and MariaDB: Part 3: [http://www.geoffmontee.com/automatic-partition-maintenance-in-mysql-and-mariadb-part-3/](http://www.geoffmontee.com/automatic-partition-maintenance-in-mysql-and-mariadb-part-3/)
- MySQL表的四种分区类型: [https://www.cnblogs.com/mliudong/p/3625522.html](https://www.cnblogs.com/mliudong/p/3625522.html)

### 总结
最后，由于作者水平有限，文章中内容如有疏漏或错误之处，还请各位读者不吝指出！
