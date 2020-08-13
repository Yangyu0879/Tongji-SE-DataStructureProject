#include<iostream>
using namespace std;

char maze[7][7];
int number1[49] = { 0 };
int number2[49] = { 0 };
int path = 0;
//dfs�����������������������������������i��j�����������������˵�ǰ�Ľڵ��λ�á�
//���ȣ��жϽڵ�������Ƿ�Ϊ��ֹ���꣬
//����ǣ�������ΪXȻ�󲽳���һ����¼·����
//���������ֹ����������������ж���
//����������п������ߵ�ͨ·0���򽫸õ���Ϊ@��Ȼ��ݹ����dfs��i,j-1����
//����ܹ��ﵽ���յĳ��ڽڵ㣬�򽫸õ���ΪX������¼�½ڵ�λ�ã��Լ�������һ����������򲻼�¼��
//����÷����ܾ����������һ�����Դ����ơ�
//���ϣ��ú���ʹ��������������ŵķ�ʽ��������ѭ���Ĳ�����
bool dfs(int i, int j)
{
	if (i == 5 && j == 5)//�ж��Ƿ�Ϊ��ֹ����
	{
		maze[i][j] = 'X';//��¼�ڵ�
		number1[path] = i;
		number2[path] = j;
		path++;
		return 1;
	}
	if (maze[i][j - 1] == '0')//���Ƿ���ͨ·
	{
		maze[i][j] = '@';
		if (dfs(i, j - 1))//�ݹ�
		{
			maze[i][j] = 'X';
			number1[path] = i;
			number2[path] = j;
			path++;
			return 1;
		}
	}
	if (maze[i - 1][j] == '0')//�ж��Ϸ�
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
	if (maze[i][j + 1] == '0')//�ж��ҷ�
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
		if (maze[i + 1][j] == '0')//�ж��·�
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
	return 0;//û��ͨ·������false
}




int main()
{
	for (int i = 0; i < 7; i++)//�����Թ�
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
	dfs(1, 1);//����ڿ�ʼ����
	cout << "	0��	1��	2��	3��	4��	5��	6��" << endl;
	for (int i = 0; i < 7; i++)
	{
		printf("%d��	", i);
		for (int j = 0; j < 7; j++)
		{
			if (maze[i][j] == '@')//ȥ�����
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
	cout << "�Թ�·����";
	for (int i = path; i >= 0; i--)//�������·��
	{
		printf("<%d,%d> ", number1[i], number2[i]);
		if (i != 0)
		{
			cout << "--> ";
		}
	}
	return 0;
}
