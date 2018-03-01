---
title: 使用POI处理office文件
date: 2018-02-28 10:17:29
tags:
- java
- apache
- poi
- office
- excel
categories:
- 技术
---

Apache POI 官网：[http://poi.apache.org/](http://poi.apache.org/)

![](http://okbn8yrzu.bkt.clouddn.com/image/pngpb-poi.png "Apache POI")

### POI 是什么？
> POI 是 Apache 软件基金会开源的项目，根据官网的解释，POI提供了操作Office Open XML (OOXML)标准和微软 OLE 2 Compound Document (OLE2)格式文档的接口。OLE2 文件包括微软office 中的 xls、doc、ppt 文件，ooxml格式是新的格式标准，包含 xlsx、docx、pptx 文件。

简单来说，**POI 让你能用 java 读/写 Excel、Word、PPT文件。**

POI 的组件：

|    组件名    |        应用 类型        |
| :-------: | :-----------------: |
|   POIFS   |      OLE2 文件系统      |
|   HPSF    |      OLE2 属性集       |
|   HSSF    |      Excel xls      |
|   HSLF    |   PowerPoint ppt    |
|   HWPF    |      Word doc       |
|   HDGF    |      Visio vsd      |
|   HPBF    |    Publisher pub    |
|   HSMF    |     Outlook msg     |
|    DDF    |       埃舍尔通用图纸       |
|   HWMF    |        WMF图纸        |
| OpenXML4j |        OOXML        |
|   XSSF    |     Excel xlsx      |
|   XSLF    |   PowerPoint pptx   |
|   XWPF    |      Word docx      |
|   XDGF    |     Visio vsdx      |
| Common SL | PowerPoint ppt和pptx |
| Common SS |   Excel xls和xlsx    |
> 参考地址：[http://poi.apache.org/overview.html](http://poi.apache.org/overview.html)

<!-- more -->



### POI 能做什么？
POI 被设计来用 java 处理 office 文件，处理 Excel 文件非常好用，处理 word 和 ppt 文件的功能相对差一点。此外，POI还对 Outlook、Visio、TNEF、Publisher 文件提供支持。
POI 多被用于文本抽取应用，如网络爬虫、索引构建和内容管理系统。
如果你需要用 java 来读写 OLE2 文件，POI是至今最完整和正确的实现方式。POI 提供最简单的接口来操作各种 Excel 文件，而且拥有高级接口实现（SXSSF）可以优化内存来写很大的 Excel 文件。



### 同类产品有什么？

- **jExcelAPI** 也称为 JXL，可用于读写 Excel 文件，是一个成熟，开源的用来操作Excel电子表格的Java类库，支持读取，修改，写入等操作，对中文有很好的支持。（已经停止更新）

- **FastExcel** 是一个用 java 开发的 Excel 读写组件，只能读取单元格字符信息，不读取字体、颜色等属性信息，因此需要的内存较小。

  参考资料：[POI、JXL、FastExcel比较](http://blog.sina.com.cn/s/blog_7de5c6210101adqi.html)

  ​

### 使用 POI 操作 Excel 文件

#### 使用 POI 读、写 Excel 文件的流程

* 获得工作簿对象（HSSFWorkBook），可以创建新的，也可以从输入流打开
* 获得工作表（HSSFSheet），可以通过工作簿对象创建或获取
* 获得行（HSSFRow），通过工作表创建或获取
* 获得列（HSSFCell），通过行创建或获取
* 设置、获取表格中的数据

#### 在 maven 项目使用 POI 读写 Excel 文件 

##### 创建maven项目

创建好 maven 项目，导入 Apache POI 的依赖：

``````xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>xyz.wqf31415</groupId>
    <artifactId>poi-demo</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <!-- https://mvnrepository.com/artifact/org.apache.poi/poi -->
        <dependency>
            <groupId>org.apache.poi</groupId>
            <artifactId>poi</artifactId>
            <version>3.17</version>
        </dependency>
    </dependencies>
</project>
``````

##### 将数据写入到 Excel 文件（createExcelFile）、从 Excel 文件中读取数据（readExcelFile）

``````java
public class PoiDemoApp {
    public static void main(String[] args) {
        createExcelFile();
        readExcelFile();
    }

    public static void createExcelFile(){
        // 创建 Excel 工作簿
        HSSFWorkbook workbook = new HSSFWorkbook();
        // 创建 Excel 工作表
        HSSFSheet sheet = workbook.createSheet("名单");
        // 创建 行
        HSSFRow row0 = sheet.createRow(0);
        // 创建3列，并设置表格内容
        row0.createCell(0).setCellValue("姓名");
        row0.createCell(1).setCellValue("性别");
        row0.createCell(2).setCellValue("年龄");

        // 创建第二行，并添加3列内容
        HSSFRow row1 = sheet.createRow(1);
        row1.createCell(0).setCellValue("张三");
        row1.createCell(1).setCellValue("男");
        row1.createCell(2).setCellValue(18);

        // 创建第三行，并添加3列内容
        HSSFRow row2 = sheet.createRow(2);
        row2.createCell(0).setCellValue("李四");
        row2.createCell(1).setCellValue("女");
        row2.createCell(2).setCellValue(17);

        // 导出文件
        File excelFile = new File("F:\\list.xls");
        try {
            // 创建文件输出流
            FileOutputStream outPutStream = new FileOutputStream(excelFile);
            //将 Excel 工作簿内容写入输出流
            workbook.write(outPutStream);
            outPutStream.flush();
            outPutStream.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void readExcelFile(){
        // 要读取的 Excel 文件
        File excelFile = new File("F:\\list.xls");
        try {
            // 创建文件输入流
            FileInputStream inputStream = new FileInputStream(excelFile);
            // 创建工作簿对象
            HSSFWorkbook workbook = new HSSFWorkbook(inputStream);
            // 从工作簿对象中获取工作表
            HSSFSheet sheet = workbook.getSheet("名单");
            // 从工作表中获取行记录
            HSSFRow row0 = sheet.getRow(0);
            // 从行中获取列的值
            System.out.print(row0.getCell(0)+"\t");
            System.out.print(row0.getCell(1)+"\t");
            System.out.print(row0.getCell(2)+"\n");

            // 获取第二行的值
            HSSFRow row1 = sheet.getRow(1);
            System.out.print(row1.getCell(0)+"\t");
            System.out.print(row1.getCell(1)+"\t");
            System.out.print(row1.getCell(2)+"\n");

            // 获取第三行的值
            HSSFRow row2 = sheet.getRow(2);
            System.out.print(row2.getCell(0)+"\t");
            System.out.print(row2.getCell(1)+"\t");
            System.out.print(row2.getCell(2)+"\n");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
``````

运行之后将在 F 盘根目录创建 `list.xls` 文件，并在控制台打出从 `list.xls` 文件中获取的数据。

#### 在 java 项目中使用 POI

到 Apache 官网下载 POI 的 jar 包并导入项目中即可使用。



#### 在 SpringBoot 项目中使用 POI

##### 创建 SpringBoot 项目，并在依赖中添加 POI 的依赖

> demo 项目的 git 地址：https://git.coding.net/wqf31415/spring-boot-poi.git

创建 SpringBoot 项目的过程不再赘述，可参考<a href="/2017/11/27/%E5%88%9B%E5%BB%BASpringBoot%E9%A1%B9%E7%9B%AE/">《创建SpringBoot项目》</a>，项目 pom.xml 如下所示：

``````xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
	<modelVersion>4.0.0</modelVersion>

	<groupId>xyz.wqf31415</groupId>
	<artifactId>spring-boot-poi</artifactId>
	<version>0.0.1-SNAPSHOT</version>
	<packaging>jar</packaging>

	<name>spring-boot-poi</name>
	<description>Demo project for Spring Boot</description>

	<parent>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter-parent</artifactId>
		<version>1.5.10.RELEASE</version>
		<relativePath/> <!-- lookup parent from repository -->
	</parent>

	<properties>
		<project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
		<project.reporting.outputEncoding>UTF-8</project.reporting.outputEncoding>
		<java.version>1.8</java.version>
	</properties>

	<dependencies>
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-web</artifactId>
		</dependency>

		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-test</artifactId>
			<scope>test</scope>
		</dependency>
		<!-- https://mvnrepository.com/artifact/org.apache.poi/poi -->
		<dependency>
			<groupId>org.apache.poi</groupId>
			<artifactId>poi</artifactId>
			<version>3.17</version>
		</dependency>

	</dependencies>

	<build>
		<plugins>
			<plugin>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-maven-plugin</artifactId>
			</plugin>
		</plugins>
	</build>
</project>
``````

##### 下载 Excel 文件的 Controller 类

用 POI 创建并生成 Excel 工作簿，添加表格内容，使用工作簿对象的 `write(OutPutStream stream)` 方法将内容写到 http 响应的输出流中。

``````java
@RestController
@RequestMapping("/excel")
public class ExcelController {
    /**
     * 下载excel表格
     *
     * @param response
     */
    @RequestMapping("/download")
    public void download(HttpServletResponse response){
      	// 创建工作簿对象
        HSSFWorkbook workbook = new HSSFWorkbook();
      	// 创建工作表
        HSSFSheet sheet = workbook.createSheet("sheet0");
      	// 添加表格内容
        HSSFRow row0 = sheet.createRow(0);
        row0.createCell(0).setCellValue("姓名");
        row0.createCell(1).setCellValue("年龄");
        row0.createCell(2).setCellValue("性别");
        row0.createCell(3).setCellValue("电话");

        HSSFRow row1 = sheet.createRow(1);
        row1.createCell(0).setCellValue("张三");
        row1.createCell(1).setCellValue(18);
        row1.createCell(2).setCellValue("男");
        row1.createCell(3).setCellValue("87878787");

		// 导出的 Excel 文件名
        String excelFileName = "details.xls";
        try {
          	// 获取相应体的输出流
            ServletOutputStream out = response.getOutputStream();
          	// 清除响应体中缓存的内容，包括状态码和响应头
            response.reset();
          	// 设置响应头
            response.setHeader("Content-disposition", "attachment; filename=" + excelFileName);
          	// 设置响应体内容的类型
            response.setContentType("application/msexcel");
          	// 将工作簿对象写入输出流
            workbook.write(out);
          	// 关闭输出流
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
``````

访问：http://localhost:\<port\>/excel/download 即可下载 Excel文档。



### 完结鞠躬

![](http://okbn8yrzu.bkt.clouddn.com/meme/meme_bow_05.jpg)

