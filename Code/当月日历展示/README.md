# C语言在控制台输出当月日历

## 一、概述
在学完C语言的大致语法后，是否感觉有力无处施展呢？这个输出日历的小程序可以帮助大家获得一点成就感！

## 二、提前知识准备
由于本程序使用到了C语言标准库的`time.h`这个头文件，建议提前了解一下：

> 注： 以下介绍多引用自这两个网站，侵删！

[菜鸟教程time.h](https://www.runoob.com/cprogramming/c-standard-library-time-h.html)

[cppreference上的介绍](https://en.cppreference.com/w/cpp/header/ctime)

### （1）、tm结构体

```c
struct tm {
   int tm_sec;         /* 秒，范围从 0 到 59        */
   int tm_min;         /* 分，范围从 0 到 59        */
   int tm_hour;        /* 小时，范围从 0 到 23        */
   int tm_mday;        /* 一月中的第几天，范围从 1 到 31    */
   int tm_mon;         /* 月，范围从 0 到 11        */
   int tm_year;        /* 自 1900 年起的年数        */
   int tm_wday;        /* 一周中的第几天，范围从 0 到 6    */
   int tm_yday;        /* 一年中的第几天，范围从 0 到 365    */
   int tm_isdst;       /* 夏令时                */
};
```

### （2）、一些用到的库变量类型
|类型|介绍|说人话|
|:-:|:--|:--|
|time_t|能够代表时间的算术类型。虽然没有定义，这几乎总是一个整体值持有秒数（不包括闰秒）自00：00，1970年1月1日UTC，对应POSIX时间|一个长整形存储着从前一个表格里说的那天到现在的秒数|
|struct tm|保留日历日期和时间的结构细分为其组件|这是一个用来保存时间和日期的结构。|

### （3）、asctime函数
char *asctime(const struct tm *timeptr)

返回一个指向字符串的指针，它代表了结构 timeptr 的日期和时间。

### （4）、localtime函数
struct tm *localtime(const time_t *timer)

timer 的值被分解为 tm 结构，并用本地时区表示。

### （3）、time函数
C 库函数 time_t time(time_t *seconds) 返回自纪元 Epoch（1970-01-01 00:00:00 UTC）起经过的时间，以秒为单位。如果 seconds 不为空，则返回值也存储在变量 seconds 中。

## 三、运行界面
运行起来就像下面这个样子的啦！！！在控制台的话界面是不是还不错呢？

![运行界面](https://img-blog.csdnimg.cn/eebb937caebe4574ab83d6a71fcd5150.png)