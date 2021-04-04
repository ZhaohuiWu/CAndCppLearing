// 给定一个迷宫，找最短的出去的路
// 例题来源 : Acwing 844. 走迷宫
// 链接 : https://www.acwing.com/problem/content/846/
#include <iostream>
#include <queue>
#define MAXN 120
#define pii pair<int, int>
using namespace std;

// 地图的起点为(1, 1)不是0
int map[MAXN][MAXN];

// 标记地图上的路是否已经被走过了
bool hasUsed[MAXN][MAXN];

// 记录经过每个点的步数
int steps[MAXN][MAXN];

// 遍历一个点时的偏移量
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};
int bfs(int row, int col, int startx, int starty, int endx, int endy);

int main(void)
{
	int row, col;
	cin >> row >> col;

	// 读入迷宫
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
			cin >> map[i][j];

	// 标记第一行，第一列为已经走过
	for (int i = 0; i < MAXN; i++)
	{
		hasUsed[0][i] = true;
		hasUsed[i][0] = true;
	}

	// 广度优先搜索找答案
	cout << bfs(row, col, 1, 1, row, col) << endl;
	return 0;
}

// 广搜最短路径
// 参数 : 地图行数 | 地图列数 | 起点横坐标 | 起点纵坐标 | 终点横坐标 | 终点纵坐标
int bfs(int row, int col, int startx, int starty, int endx, int endy)
{
	// 使用队列记录路径
	queue<pii> path;
	int x, y;

	// 将起点入队，并且标记起点已经走过
	path.push({startx, starty});
	hasUsed[startx][starty] = true;

	// 当队列不为空时遍历各个可行的点找路径
	while (!path.empty())
	{
		// 取出当前要遍历的点
		pii temp = path.front();
		path.pop();

		// 如果该点就是要遍历的点，那么就提前结束
		if (temp.first == endx && temp.second == endy)
			break;

		// 如果该点不是终点，看看该点可以往那儿走
		for (int i = 0; i < 4; i++)
		{
			x = temp.first + dx[i];
			y = temp.second + dy[i];

			// 查看当前的点是否可以走，如果可以走的话将其入队
			if (x >= 1 && y >= 1 && x <= row && y <= col 
				&& !hasUsed[x][y] && map[x][y] == 0)
			{
				hasUsed[x][y] = true;
				path.push({x, y});
				steps[x][y] = steps[temp.first][temp.second] + 1;
			} // end if
		} // end for
	} // end while

	// 最后返回要求的点的步数
	return steps[endx][endy];
}
