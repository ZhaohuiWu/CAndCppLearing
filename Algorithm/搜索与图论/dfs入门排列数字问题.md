# dfs入门排列数字问题
## 一、问题概述
给定一个正整数n，将数字1~n排成一排有很多种排列方法。要求输出所有的排列方案。
先上例题链接：[https://www.acwing.com/problem/content/844/](https://www.acwing.com/problem/content/844/)

> 以下内容截取至ACwing网站中例题链接里那个网页
> 给定一个整数 n，将数字 1∼n 排成一排，将会有很多种排列方法。
> 现在，请你按照字典序将所有的排列方法输出。
```powershell
输入格式
共一行，包含一个整数 n。
输出格式
按字典序输出所有排列方案，每个方案占一行。
```
## 二、问题分析
先看一波示例：如输入3，则按字典序输出：
```powershell
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```
分析一波输出，发现输出是**一组排列输出结束，再输出另一种排列**。当然我们思考时也可以这样思考，这也就是 进入dfs **[Depth-First-Search]**（深度优先搜索）的第一步，即，**先把一种情况考虑完再考虑下一种可能的情况**。
我们看输入为三的情况：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210408191715684.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzNTE5ODM3,size_16,color_FFFFFF,t_70)
需要填写三个空来完成排列。按深搜的思路，应该是先找出一组后再找下一组。如图中红色路径：
> 首先三个空都未填满数字，先填第一个空，填为“1”；
> 然后填第二个空，填为“2”；
> 再填写第三个空，为“3”；
> 此时都已经填写完成，输出这一组结果
> 这一组处理结束，则==回溯==到上一个可以操作的节点；
> 然后再次填写......（发现了没，这其实是一个递归）
## 三、代码分析
### （一）、如何表示填写完成
当然是判断**当前填到第几个空**是否和**需要填的空**相等判断。
### （二）、如何判断该填哪个数
由于每个数只能使用一次，所以我们可以用一个 bool 数组(hasUsed)来标记接下来哪个数可以被填入空中。**要注意的是，在填完一组后，回溯时要把相应标记重置为未使用状态。**
### （三）、如何表示填空
同样，我们可以使用一个 int 数组（path）来表示待填的空。
### （四）、实现dfs
如图，我们可以先在用for循环模拟填一个空的数，然后再递归的填写不同的空，伪代码如下：
```powershell
dfs (start, end)
	if start == end
		output
		return
	for  i, 1 : n
		if ( ! hasUsed[i])
			path[start] = i
			mark hasUsed[i]
			dfs(start + 1, end)
			clear mark hasUsed[i]
```
如图为伪代码的解释：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210408194208662.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzMzNTE5ODM3,size_16,color_FFFFFF,t_70)
> 图中“已用”， “可用” 为hasUsed数组中的状态；
> 图中for循环中的1， 2， 3为遍历可能填入空中的数；
> ==图中红色部分为一组填写完成，进行下一组填写==。

==注意，填满后回溯时要将结束使用的数恢复到未使用状态！！！==
以下为dfs函数的代码：
```cpp
//       当前该填的空    需要填的空
void dfs (int start, int end)
{
    if (start == end)
    {
        for (int i = 0; i < end; i++)
            cout << path[i] << " ";
        cout << endl;
        return;
    }

    // 从1开始填
    for (int i = 1; i <= end; i++)
    	// 如果这个数被用过，则看下一个可能的数是否被用过
        if (!hasUsed[i])
        {
        	// 如果没被使用，则填入数字
            path[start] = i;
            hasUsed[i] = true;
            dfs(start + 1, end);    // 递归的填下一个空
            hasUsed[i] = false;		// 不能忘记重置标记
        }
}
```

## 四、代码全览
好了，接下来可以看一下完整代码了。
```cpp
// 深度优先搜索  排列数字
#include <iostream>
#define MAXN 10
using namespace std;

bool hasUsed[MAXN];    // 标记各个数位是否被使用
int path[MAXN];     // 存储可能的序列
void dfs (int, int);

int main (void)
{
    int n = 0;
    cin >> n;

    dfs(0, n);
    return 0;
}

//       当前该填的空    需要填的空
void dfs (int start, int end)
{
    if (start == end)
    {
        for (int i = 0; i < end; i++)
            cout << path[i] << " ";
        cout << endl;
        return;
    }

    // 从1开始填
    for (int i = 1; i <= end; i++)
    	// 如果这个数被用过，则看下一个可能的数是否被用过
        if (!hasUsed[i])
        {
        	// 如果没被使用，则填入数字
            path[start] = i;
            hasUsed[i] = true;
            dfs(start + 1, end);    // 递归的填下一个空
            hasUsed[i] = false;		// 不能忘记重置标记
        }
}
```
## 五、问题升级
如果这个理解的差不多的话可以试一下这个问题的哦：
[https://www.acwing.com/problem/content/95/](https://www.acwing.com/problem/content/95/)

> 摘自Acwing题目描述:
> 从 1∼n 这 n 个整数中随机选出 m 个，输出所有可能的选择方案。
> 
> 输入格式 两个整数 n,m ,在同一行用空格隔开。
> 
> 输出格式 按照从小到大的顺序输出所有方案，每行 1 个。
> 
> 首先，同一行内的数升序排列，相邻两个数用一个空格隔开。
> 
> 其次，对于两个不同的行，对应下标的数一一比较，字典序较小的排在前面（例如 1 3 5 7 排在 1 3 6 8 前面）。

该题的一个代码：

```cpp
#include <iostream>
#define MAXN 50

using namespace std;

int path[MAXN];
bool hasUsed[MAXN];
void dfs(int start, int end, int n);

int main (void)
{
    int n, m;
    cin >> n >> m;
    dfs(0, m, n);
    return 0;
}

void dfs(int start, int end, int n)
{
    if (start == end)
    {
        for (int i = 0; i < end; i++)
            cout << path[i] << " ";
        cout << endl;
        return;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            path[start] = i;
            if (start >= 1 && path[start - 1] >= path[start])
                continue;
            hasUsed[i] = true;
            dfs(start + 1, end, n);
            hasUsed[i] = false;
        }
    }
}
```

## 六、作者相关

- #### （一）、作者简介
    - 作者：馗顺先生
    - 简介：一个热爱程序设计与电子技术的预备猿。后续也会不定期更新一些有趣的代码，以及一些有用的算法实现。大家可以关注以下哦。最后，若有不足，希望各位大佬们不吝赐教。
- #### （二）、联系方式
    - 邮箱：2727144006@qq.com
    - 博客地址: [https://blog.csdn.net/qq_33519837?spm=1001.2100.3001.5113](https://blog.csdn.net/qq_33519837?spm=1001.2100.3001.5113)