# 实践free()在C语言中的作用
## 一、问题背景
某天在做数据结构留下的实验报告时，知道了malloc()和free()必须同时调用以**避免内存泄漏**，然而并不知道free究竟干了那些操作，所以尝试**用实践的方法解释free()这个函数**到底有啥用。
## 二、实践
### （一）、实践代码
```c
// 看看free到底有啥用, 为了方便查看，就不把输出封装成函数了
#include <stdlib.h>
#include <stdio.h>

int * a = NULL;		// 定义一个全局整形指针

int main (void)
{
    a = (int *)malloc(sizeof(int));		// 让全局指针指向一个malloc分配的空间
    int * c = (int *)malloc(sizeof(int));	// 定义一个局部指针并指向malloc分配的空间
    int * p = a;	// 再定义两个局部指针存储a，c指向的内存空间
    int * q = c;

    *a = 15;	// 为两块内存空间内置入值
    *c = 30;
    printf("*a = %d\t*c = %d\n", *a, *c);
    printf("*p = %d\t*q = %d\n", *p, *q);
    printf("a = %p\tc = %p\n", a, c);
    printf("p = %p\tq = %p\n", p, q);
    puts("");

    free(a);	// 释放内存空间
    free(c);
    printf("*a = %d\t*c = %d\n", *a, *c);
    printf("*p = %d\t*q = %d\n", *p, *q);
    printf("a = %p\tc = %p\n", a, c);
    printf("p = %p\tq = %p\n", p, q);
    puts("");

    *p = 20;	// 尝试对已经释放的内存空间赋值
    *q = 50;
    printf("*a = %d\t*c = %d\n", *a, *c);
    printf("*p = %d\t*q = %d\n", *p, *q);
    printf("a = %p\tc = %p\n", a, c);
    printf("p = %p\tq = %p\n", p, q);
    puts("");

    return 0;
}
```
### （二）、gcc version 9.2.0编译运行结果

```powershell
*a = 15 *c = 30
*p = 15 *q = 30
a = 007D16D8    c = 007D1678
p = 007D16D8    q = 007D1678

*a = 8197752    *c = 8197808
*p = 8197752    *q = 8197808
a = 007D16D8    c = 007D1678
p = 007D16D8    q = 007D1678

*a = 20 *c = 50
*p = 20 *q = 50
a = 007D16D8    c = 007D1678
p = 007D16D8    q = 007D1678

```
### （三）、Dev C++中TDM-GCC 4.9.2 64bit release编译运行结果

```powershell
*a = 15 *c = 30
*p = 15 *q = 30
a = 0000000000BB13C0    c = 0000000000BB13E0
p = 0000000000BB13C0    q = 0000000000BB13E0

*a = 12255568   *c = 30
*p = 12255568   *q = 30
a = 0000000000BB13C0    c = 0000000000BB13E0
p = 0000000000BB13C0    q = 0000000000BB13E0

*a = 20 *c = 50
*p = 20 *q = 50
a = 0000000000BB13C0    c = 0000000000BB13E0
p = 0000000000BB13C0    q = 0000000000BB13E0

```
### （四）、Visual Studio 2019编译运行结果

```powershell
*a = 15 *c = 30
*p = 15 *q = 30
a = 0000024428A00850    c = 0000024428A099E0
p = 0000024428A00850    q = 0000024428A099E0

*a = -572662307 *c = -572662307
*p = -572662307 *q = -572662307
a = 0000024428A00850    c = 0000024428A099E0
p = 0000024428A00850    q = 0000024428A099E0

*a = 20 *c = 50
*p = 20 *q = 50
a = 0000024428A00850    c = 0000024428A099E0
p = 0000024428A00850    q = 0000024428A099E0

```
VS报的warning。
![VS报Warning](https://img-blog.csdnimg.cn/20210330164934158.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzNTE5ODM3,size_16,color_FFFFFF,t_70)
## 三、实践结果结论
 - 在以上三个编译器的运行结果中，free函数只是释放了内存，并没有改变指针所指向的值；
 - 在free释放内存之后，**仍然可以通过指针访问修改释放掉内存的空间**；
 - 在free释放内存之后，**除Dev C++编译结果的局部指针变量所指向的内容还保留外，其余内容都改变为一个随机的值**。

## 四、实践意义

 1. 知道了free作用后产生的效果；
 2. 明白了在释放掉内存空间后还应把指向该内存空间的指针置为空，避免程序出现过多的 **“ 野指针 ”**。

## 五、作者相关
- #### （一）、作者简介
    - 作者：馗顺先生
    - 简介：一个热爱程序设计与电子技术的预备猿。后续也会不定期更新一些有趣的代码，以及一些有用的算法实现。大家可以关注以下哦。最后，若有不足，希望各位大佬们不吝赐教。
- #### （二）、联系方式
    - 邮箱：2727144006@qq.com
    - 博客地址: [https://blog.csdn.net/qq_33519837?spm=1001.2100.3001.5113](https://blog.csdn.net/qq_33519837?spm=1001.2100.3001.5113)
