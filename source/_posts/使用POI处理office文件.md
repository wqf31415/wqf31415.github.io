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
- java
---

Apache POI 官网：[http://poi.apache.org/](http://poi.apache.org/)

![](https://blog-images.qiniu.wqf31415.xyz/image/pngpb-poi.png "Apache POI")

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

##### 创建 SpringBoot web 项目，并在依赖中添加 POI 的依赖

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

访问：http://localhost:8080/excel/download 即可下载 Excel文档。


### 注意事项
#### 工作表名的命名
Excel 表格的工作表（sheet）名称 **长度不能超过31个字符** ，不能包含 `0x000 0x003 : \ * / ? : [ ]` 
可以用 POI 提供的工具类创建正确的工作表名，非法字符将被替换成空格，以下代码将返回 ` s h e e t 1 ` 

``````java
String sheetName = WorkbookUtil.createSafeSheetName("[s/h*e:e?t\\1]");
``````

#### 表格数据类型
##### 可插入单元格(Cell)的数据类型
单元格(Cell)中支持的数据类型有 **Double** 、**Date** 、**Calendar** 、**String** 、**Boolean** 、**RichTextString** 。
``````java
	Workbook workbook = new HSSFWorkbook();
	// Workbook workbook = new XSSFWorkbook();
	CreationHelper helper = workbook.getCreationHelper();
    Sheet sheet = workbook.createSheet();
    Row row_0 = sheet.createRow(0);
	row_0.createCell(0).setCellValue("Double");
	row_0.createCell(1).setCellValue("Date");
	row_0.createCell(2).setCellValue("Calendar");
	row_0.createCell(3).setCellValue("String");
	row_0.createCell(4).setCellValue("Boolean");
	row_0.createCell(5).setCellValue("RichTextString");

	Row row_1 = sheet.createRow(1);
	Cell cell_1_0 = row_1.createCell(0);
	Double d = 3.14;
	cell_1_0.setCellValue(d);

	Cell cell_1_1 = row_1.createCell(1);
	Date date = new Date();
	cell_1_1.setCellValue(date);

	Cell cell_1_2 = row_1.createCell(2);
	Calendar calendar = Calendar.getInstance();
	cell_1_2.setCellValue(calendar);

	Cell cell_1_3 = row_1.createCell(3);
	String str = "String";
	cell_1_3.setCellValue(str);

	Cell cell_1_4 = row_1.createCell(4);
	boolean b = true;
	cell_1_4.setCellValue(b);

	Cell cell_1_5 = row_1.createCell(5);
	RichTextString richTextString = helper.createRichTextString("富文本");
	cell_1_5.setCellValue(richTextString);
``````

##### 从单元格(Cell)中获取的数据格式
从已有的 Excel 文件中获取的单元格数据类型有：**String** (字符串)、**Numric** (数字类型，包括数字和日期数据)、**boolean** (布尔型)、**Formula** (公式)、**Blank** (空值)，获取方式如下：
``````java
// 获取所有格式的数据，返回字符串
DataFormatter formatter = new DataFormatter();
String text = formatter.formatCellValue(cell);

// 按类型获取数据
CellType cellType = cell.getCellTypeEnum();
switch (cellType) {
	case NUMERIC:
		// 数字类型数据可能是数字，也可能是日期
		if (DateUtil.isCellDateFormatted(cell)){
			Date date = cell.getDateCellValue();
		}else {
			Double d = cell.getNumericCellValue();
		}
		break;
	case STRING:
		String str = cell.getStringCellValue();
		break;
	case BOOLEAN:
		boolean b = cell.getBooleanCellValue();
		break;
	case FORMULA:
		String formula = cell.getCellFormula();
		break;
	case BLANK:
		break;
	default:
		
}
``````

#### 创建 .xls 或 .xlsx 文件
我们知道 .xls 是 Excel 03版的文件扩展名，.xlsx 是 07版的，我们可以分别通过创建 **HSSFWorkbook** 或 **XSSFWorkbook** 对象来新建或打开。
其中，使用 XSSFWorkbook 需要导入 `poi-ooxml` 依赖：

``````xml
<!-- https://mvnrepository.com/artifact/org.apache.poi/poi-ooxml -->
<dependency>
    <groupId>org.apache.poi</groupId>
    <artifactId>poi-ooxml</artifactId>
    <version>3.17</version>
</dependency>
``````

创建或打开 Excel 文件：
``````java
// 创建 xls 文件
Workbook workbook1 = new HSSFWorkbook();

// 打开 xls 文件
InputStream stream1 = new FileInputStream("D:\\test.xls");
Workbook workbook2 = new HSSFWorkbook(stream1);

// 创建 xlsx 文件
Workbook workbook3 = new XSSFWorkbook();

// 打开 xlsx 文件
InputStream stream2 = new FileInputStream("D:\\test.xlsx");
Workbook workbook4 = new HSSFWorkbook(stream2);
``````

##### 设置单元格对齐方式
通过设置单元格(Cell)的样式(CellStyle)中的水平对齐(HorizontalAlignment)和垂直对齐(VerticalAlignment)来控制内容的对齐方式。
水平对齐方式包括：**GENERAL** (常规)、**LEFT**(左对齐)、**CENTER** (居中对齐)、**RIGHT** (右对齐)、**FILL** (填充)、**JUSTIFY** (两端对齐)、**CENTER_SELECTION** (居中选择)、**DISTRIBUTED** (分散对齐)
垂直对齐方式包括：**TOP** (顶部对齐)、**CENTER** (垂直居中)、**BOTTOM** (底部对齐)、**JUSTIFY** (两端对齐)、**DISTRIBUTED**(分散对齐)
``````java
        Workbook workbook = new XSSFWorkbook();
        Sheet sheet = workbook.createSheet("alignSheet");

        Row row_0 = sheet.createRow(0);
        Cell cell_0_0 = row_0.createCell(0);
        CellStyle cellStyle0 = workbook.createCellStyle();
        cellStyle0.setAlignment(HorizontalAlignment.LEFT);
        cellStyle0.setVerticalAlignment(VerticalAlignment.TOP);
        cell_0_0.setCellStyle(cellStyle0);
        cell_0_0.setCellValue("左上");

        Cell cell_0_1 = row_0.createCell(1);
        CellStyle cellStyle1 = workbook.createCellStyle();
        cellStyle1.setAlignment(HorizontalAlignment.CENTER);
        cellStyle1.setVerticalAlignment(VerticalAlignment.CENTER);
        cell_0_1.setCellStyle(cellStyle1);
        cell_0_1.setCellValue("中间");

        Cell cell_0_2 = row_0.createCell(2);
        CellStyle cellStyle2 = workbook.createCellStyle();
        cellStyle2.setAlignment(HorizontalAlignment.RIGHT);
        cellStyle2.setVerticalAlignment(VerticalAlignment.BOTTOM);
        cell_0_2.setCellStyle(cellStyle2);
        cell_0_2.setCellValue("右下");
``````

##### 设置边框
创建单元格样式(CellStyle)，可设置单元格边框类型和颜色。
``````java
Workbook workbook = new HSSFWorkbook();
Sheet sheet = workbook.createSheet("border");
Row row = sheet.createRow(1);
Cell cell = row.createCell(1);
cell.setCellValue("边框");
CellStyle cellStyle = workbook.createCellStyle();
cellStyle.setBorderTop(BorderStyle.DOUBLE);
cellStyle.setTopBorderColor(IndexedColors.BLUE.getIndex());
cellStyle.setBorderRight(BorderStyle.DASH_DOT);
cellStyle.setRightBorderColor(IndexedColors.RED.getIndex());
cellStyle.setBorderBottom(BorderStyle.DOTTED);
cellStyle.setBottomBorderColor(IndexedColors.GREEN.getIndex());
cellStyle.setBorderLeft(BorderStyle.DASH_DOT_DOT);
cellStyle.setLeftBorderColor(IndexedColors.YELLOW.getIndex());
cell.setCellStyle(cellStyle);
``````

#### 大量数据导出

在 Excel 2003 中每个 sheet 最多支持 65536 行数据，对应 POI 中的 HSSF 对象，可以用来处理较少的数据量，如果需要处理大量数据，可以添加多个 sheet。

Excel 2007 以上版本中，每个 sheet 最多支持 1048576 行数据，对应 POI 中 XSSF 对象，这时就可以在一个表格页中导出 100 万条数据了，但要小心堆溢出。

在 POI 3.8 之后版本中新增了 SXSSFWorkbook ，它可以控制 excel 数据占用的内存，通过控制内存中的行数来实现资源管理，当创建对象超过了设定的行数，会自动刷新内存，将数据写入文件。这样占用 CPU 和内存较少。

### 完结鞠躬

![](https://blog-images.qiniu.wqf31415.xyz/meme/meme_bow_05.jpg)

