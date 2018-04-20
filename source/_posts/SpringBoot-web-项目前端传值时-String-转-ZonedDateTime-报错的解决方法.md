---
title: SpringBoot web 项目前端传值时 String 转 ZonedDateTime 报错的解决方法
date: 2018-04-20 11:14:47
tags:
- springboot
- java8
- ZonedDateTime
categories:
- 技术

---



### 问题描述 

最近在用 springboot 做 web 项目，其中一个实体中使用了 java8 中的 ZonedDateTime 来记录时间，但是前端页面在使用 POST 或 PUT 提交请求，出错了，错误主要提示信息如下：

``````console
org.springframework.validation.BindException: 
Failed to convert property value of type 'java.lang.String' to required type 'java.time.ZonedDateTime'
``````



读过错误提示后知道是在数据验证绑定时，字段的类型转换错误，前端传的是一个字符串格式的时间，格式为：yyyy-MM-dd HH:mm:ss ，后端方法接收的参数是一个对象，交由spring 自动绑定，绑定时发现参数值不是一个 ZonedDateTime 对象，所以报了类型转换错误。因此，解决思路是写一个方法来完成这个字符串格式时间 和 ZonedDateTime 对象的转换。



<!-- more -->



### 解决方法

- 编写自定义的绑定编辑器

需要继承 java.beans.PropertyEditorSupport 类，并复写其中 setAsText 和 getAsText 方法：

``````java
import java.beans.PropertyEditorSupport;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;

public class MyCustomDateEditor extends PropertyEditorSupport {
    private DateTimeFormatter dateTimeFormat;
    private boolean allowEmpty;

    public MyCustomDateEditor(DateTimeFormatter dateTimeFormat, boolean allowEmpty) {
        this.allowEmpty = allowEmpty;
        this.dateTimeFormat = dateTimeFormat;
    }

    /**
     * Parse the Date from the given text, using the specified DateTimeFormatter.
     */
    @Override
    public void setAsText(String text) throws IllegalArgumentException {
        if (this.allowEmpty && !org.springframework.util.StringUtils.hasText(text)) {
            // Treat empty String as null value.
            setValue(null);
        } else {
            try {
                setValue(ZonedDateTime.of(LocalDateTime.parse(text, this.dateTimeFormat), ZoneId.of("Asia/Shanghai")));
            } catch (Exception ex) {
                throw new IllegalArgumentException("Could not parse date: " + ex.getMessage(), ex);
            }
        }
    }

    /**
     * Format the Date as String, using the specified DateTimeFormatter.
     */
    @Override
    public String getAsText() {
        ZonedDateTime zonedDateTime = (ZonedDateTime) getValue();
        return zonedDateTime.format(dateTimeFormat);
    }
}
``````



- 在 controller 中使用自定义的绑定编辑器

``````java
@InitBinder
protected void initBinder(WebDataBinder binder) {
    DateTimeFormatter dateFormat = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
    binder.registerCustomEditor(ZonedDateTime.class, new MyCustomDateEditor(dateFormat, true));
}
``````



### 完整代码示例

- 实体类

``````java
@Entity
@Table(name = "company")
public class Company implements Serializable {
    private static final long serialVersionUID = 1L;

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;

    /**
     * 公司名称
     */
    @NotNull
    @Size(min = 4,max = 20)
    @Column(name = "name",nullable = false,length = 20)
    private String name;

    /**
     * 公司地址
     */
    @Size(min = 2,max = 25)
    @Column(name = "address",length = 25)
    private String address;

    /**
     * 信息是否隐藏
     */
    @Column(name = "hidden")
    private Boolean hidden;

    /**
     * 备注
     */
    @Column(name = "remark")
    private String remark;

    /**
     * 创建人
     */
    @Size(max = 50)
    @Column(name = "created_by",length = 50)
    private String createdBy;

    /**
     * 创建时间
     */
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @Column(name = "created_date")
    private ZonedDateTime createdDate;
    
    /**
     * 最后修改人
     */
    @Size(max = 50)
    @Column(name = "last_modified_by",length = 50)
    private String lastModifiedBy;

    /**
     * 最后修改日期
     */
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    @Column(name = "last_modified_date")
    private ZonedDateTime lastModifiedDate;
    
    // 节省篇幅，省略了 setter 和 getter
}
``````



- Repository

````java
public interface CompanyRepository extends JpaRepository<Company,Long> {
	// 使用SpringBoot JPA
}
````



- Controller

``````java
@RestController
@RequestMapping("/api")
public class CompanyResource {
    private final Logger logger = LoggerFactory.getLogger(CompanyResource.class);
    @Autowired
    private CompanyRepository companyRepository;

    /**
     * 使用自定义的绑定器
     */
    @InitBinder
    protected void initBinder(WebDataBinder binder) {
        DateTimeFormatter dateFormat = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        binder.registerCustomEditor(ZonedDateTime.class, new MyCustomDateEditor(dateFormat, true));
    }
    
    /**
     * 创建公司
     */
    @RequestMapping(method = RequestMethod.POST,value = "/companies",produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity<Company> createCompany(Company company) throws URISyntaxException {
        if (company.getId() != null) {
            return ResponseEntity.badRequest()
                    .body(null);
        }
        company.setCreatedDate(ZonedDateTime.now());
        Company result = companyRepository.save(company);
        return ResponseEntity.created(new URI("/api/companies/" + result.getId()))
                .body(result);
    }

    /**
     * 修改公司信息
     */
    @RequestMapping(method = RequestMethod.PUT,value = "/companies",produces = MediaType.APPLICATION_JSON_VALUE)
    public ResponseEntity<Company> updateCompany( Company company) throws URISyntaxException {
        if (company.getId() == null) {
            return createCompany(company);
        }
        company.setLastModifiedDate(ZonedDateTime.now());
        Company result = companyRepository.save(company);
        return ResponseEntity.ok()
                .body(result);
    }
}
``````







### 以上