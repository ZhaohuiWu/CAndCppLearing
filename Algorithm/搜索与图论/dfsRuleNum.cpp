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

// 排列数字  当前开始    深搜结束
void dfs (int start, int end)
{
    if (start == end)
    {
        for (int i = 0; i < end; i++)
            cout << path[i] << " ";
        cout << endl;
        return;
    }

    // 从一开始遍历
    for (int i = 1; i <= end; i++)
        if (!hasUsed[i])
        {
            path[start] = i;
            hasUsed[i] = true;
            dfs(start + 1, end);    // 递归
            hasUsed[i] = false;
        }
}