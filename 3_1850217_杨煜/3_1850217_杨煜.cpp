#include<iostream>
using namespace std;

char maze[7][7];
int number1[49] = { 0 };
int number2[49] = { 0 };
int path = 0;
//dfs函数即深度优先搜索函数，接受两个参数i，j，这两个参数代表了当前的节点的位置。
//首先，判断节点的坐标是否为终止坐标，
//如果是，则将其标记为X然后步长加一，记录路径。
//如果不是终止调节则进行正常的判读，
//如果它的左方有可以行走的通路0，则将该点标记为@，然后递归调用dfs（i,j-1），
//如果能够达到最终的出口节点，则将该点标记为X，并记录下节点位置，以及步长加一。如果不能则不记录。
//如果该方向不能经过则查找下一方向，以此类推。
//以上，该函数使用了填充其他符号的方式避免了死循环的产生。
bool dfs(int i, int j)
{
	if (i == 5 && j == 5)//判断是否为终止条件
	{
		maze[i][j] = 'X';//记录节点
		number1[path] = i;
		number2[path] = j;
		path++;
		return 1;
	}
	if (maze[i][j - 1] == '0')//左方是否有通路
	{
		maze[i][j] = '@';
		if (dfs(i, j - 1))//递归
		{
			maze[i][j] = 'X';
			number1[path] = i;
			number2[path] = j;
			path++;
			return 1;
		}
	}
	if (maze[i - 1][j] == '0')//判断上方
	{
		maze[i][j] = '@';
		if (dfs(i - 1, j))
		{
			number1[path] = i;
			number2[path] = j;
			path++;
			maze[i][j] = 'X';
			return 1;
		}
	}
	if (maze[i][j + 1] == '0')//判断右方
	{
		maze[i][j] = '@';
		if (dfs(i, j + 1))
		{
			number1[path] = i;
			number2[path] = j;
			path++;
			maze[i][j] = 'X';
			return 1;
		}
	}
		if (maze[i + 1][j] == '0')//判断下方
		{
			maze[i][j] = '@';
			if (dfs(i + 1, j))
			{
				number1[path] = i;
				number2[path] = j;
				path++;
				maze[i][j] = 'X';
				return 1;
			}
		}
	return 0;//没有通路，返回false
}




int main()
{
	for (int i = 0; i < 7; i++)//建立迷宫
	{
		maze[0][i] = '#';
		maze[i][0] = '#';
		maze[6][i] = '#';
		maze[i][6] = '#';
	}
	maze[1][2] = '#';
	maze[2][2] = '#';
	maze[2][4] = '#';
	maze[2][5] = '#';
	maze[3][4] = '#';
	maze[4][2] = '#';
	maze[5][2] = '#';
	maze[5][4] = '#';
	for (int i = 1; i < 6; i++)
	{
		for (int j = 1; j < 6; j++)
		{
			if (maze[i][j] != '#')
			{
				maze[i][j] = '0';
			}
		}
	}
	dfs(1, 1);//从入口开始搜索
	cout << "	0列	1列	2列	3列	4列	5列	6列" << endl;
	for (int i = 0; i < 7; i++)
	{
		printf("%d行	", i);
		for (int j = 0; j < 7; j++)
		{
			if (maze[i][j] == '@')//去除标记
			{
				cout << "0" << "	";
			}
			else
			{
				cout << maze[i][j] << "	";
			}
		}
		cout << endl;
	}
	cout << "迷宫路径：";
	for (int i = path; i >= 0; i--)//逆序输出路径
	{
		printf("<%d,%d> ", number1[i], number2[i]);
		if (i != 0)
		{
			cout << "--> ";
		}
	}
	return 0;
}
