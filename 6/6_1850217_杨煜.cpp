#include <iostream>
#include <string>
using namespace std;

struct TreeNode
{
	string data;//数据内容
	TreeNode* firstChild, * nextSibling;//子孙及兄弟
	TreeNode() { firstChild = NULL; nextSibling = NULL; }
};
//构造函数构造了一个新的节点，作为祖先节点，内容存放祖先的姓名
class Tree
{
private:
	TreeNode* root, * current;//根节点
	bool Find(string s, TreeNode* p);//搜索
	void addChild(string str, TreeNode* p);//添加子节点
	void printChild(TreeNode* p);//打印孩子节点
public:
	Tree();//构造函数
	~Tree() {}//析构函数
	void Insertsubtree();//添加子树
	void Insertnode();//添加子节点
	void Remove();//移除
	void Revise();//修改
};

//查找函数接受的参数为名字和开始的节点，然后判断节点数据是否为名字，如果是则直接返回。
//如果不是则节点移动到子节点递归搜索，如果任然不是则移动到兄弟节点。
bool Tree::Find(string s, TreeNode* p)//搜索
{
	if (p->data == s)//如果根节点是要找的
	{
		current = p;
		return true;
	}
	else
	{
		TreeNode* q = p->firstChild;//移到子节点
		while (!(q == NULL))
		{
			if (Find(s, q))//递归
			{
				return true;
			}
			else
			{
				q = q->nextSibling;//移到兄弟节点
			}
		}
	}
	return false;
}

//函数的参数为名字和所要添加的双亲节点。
//如果双亲节点没有子节点则添加入，否则，寻找子节点的兄弟节点直到为空，再添加节点。
void Tree::addChild(string str, TreeNode* p)//添加子节点
{
	TreeNode* child = new TreeNode;
	child->data = str;
	if (p->firstChild == NULL)//子节点为空
	{
		p->firstChild = child;
	}
	else
	{
		TreeNode* lastChild = p->firstChild;
		while (lastChild->nextSibling != NULL) //寻找兄弟节点为空的子节点
		{
			lastChild = lastChild->nextSibling;
		}
		lastChild->nextSibling = child;
	}
}

//通过递归寻找子节点的兄弟节点，将该节点的子节点内容全部输出。
void Tree::printChild(TreeNode* p)//打印子节点
{
	TreeNode* child = p->firstChild;
	while (child->nextSibling != NULL) //循环查找尾结点
	{
		cout << child->data << '\t';
		child = child->nextSibling;
	}
	cout << child->data;
}

Tree::Tree()//构造函数
{
	root = new TreeNode; 
	cout << "首先建立一个家谱" << endl;
	cout << "请输入祖先的姓名：";
	cin >> root->data;
	cout << "此家谱的祖先是：" << root->data;
}

//输入要建立家庭的人名，如果找到则返回正确，如果未找到则，输出错误信息。
//随后输入子女个数通过调用addChild，依次插入。
//结束后，调用printChild，依次输出其中的内容。
void Tree::Insertsubtree()//插入子树
{
	cout << "输入要建立家庭的人的姓名：";
	string name;
	cin >> name;
	if (!(Find(name,root))) //如果没有找到要建立的人的名字
	{
		cout << "没有找到这个人" << endl;
	}
	else 
	{
		int num;
		cout << "请输入" << name << "的儿女人数：";
		cin >> num;
		cout << "请依次输入" << name << "的儿女姓名：";
		TreeNode* node = current;
		while (num > 0) //依次插入
		{
			string child;
			cin >> child;
			addChild(child, node);
			num--;
		}
		cout << node->data << "的第一代子孙是：";
		printChild(node);
	}
}
//找到要插入节点的双亲节点随后插入该节点。
void Tree::Insertnode()//插入子节点
{
	cout << "输入要添加儿子（或女儿）的人的姓名：";
	string name;
	cin >> name;
	if (!(Find(name, root))) 
	{
		cout << "没有找到这个人" << endl;
	}
	else 
	{
		TreeNode* node = current;
		cout << "请输入" << name << "新添加的儿子（或女儿）的姓名：";
		string child;
		cin >> child;
		addChild(child, node);//插入节点
		cout << node->data << "的第一代子孙是：";
		printChild(node);
	}
}
//首先找到要删除的子树的根节点，即祖先节点，随后依次递归删除节点。
void Tree::Remove()//移除
{
	cout << "输入要解散家庭的人的目前姓名：";
	string name;
	cin >> name;
	if (!(Find(name, root))) //如果找不到
	{
		cout << "没有找到这个人" << endl;
	}
	else 
	{
		TreeNode* node = current;
		cout << "要解散家庭的人的姓名是" << name << endl;
		if (node->firstChild == NULL)
		{
			cout << node->data << "已经没有家庭了";
		}
		else 
		{
			cout << node->data << "的第一代子孙是：";
			printChild(node);
			node->firstChild = NULL;
		}
	}
}
//首先通过调用find函数找到，所要修改的节点，随后依次修改节点所在内容。
void Tree::Revise()//修改
{
	cout << "输入要更改姓名的人的目前姓名：";
	string name;
	cin >> name;
	if (!(Find(name, root))) //如果找不到
	{
		cout << "没有找到这个人" << endl;
	}
	else 
	{
		TreeNode* node = current;
		cout << "请输入更改后的姓名：";
		string new_name;
		cin >> new_name;
		node->data = new_name;
		cout << name << "已更名为" << new_name;
	}
}


//首先建立输出的表格，随后依据输入内容，使用switch，分别进行相应的函数调用。
int main()
{
	Tree A;
	int loop = 1;
	cout << "**" << "              " << "家谱管理系统" << "                " << "**" << endl;//制表
	cout << "==============================================" << endl;
	cout << "**" << "             " << "请选择要执行的操作" << "           " << "**" << endl;
	cout << "**" << "             " << "A --- 完善家谱" << "               " << "**" << endl;
	cout << "**" << "             " << "B --- 添加家庭成员" << "           " << "**" << endl;
	cout << "**" << "             " << "C --- 解散局部家庭" << "           " << "**" << endl;
	cout << "**" << "             " << "D --- 更改家庭成员姓名" << "       " << "**" << endl;
	cout << "**" << "             " << "E --- 退出程序" << "               " << "**" << endl;
	cout << "==============================================" << endl;
	while (loop) //主循环
	{
		cout << endl << endl << "请选择要执行的操作：";
		char id;
		cin >> id;
		switch (id)//不同情况下调用函数
		{
		case 'A':
			A.Insertsubtree();
			break;
		case 'B':
			A.Insertnode();
			break;
		case 'C':
			A.Remove();
			break;
		case 'D':
			A.Revise();
			break;
		case 'E':
			loop = 0;
			break;
		default:
			cout << "请输入正确的序号" << endl;
			break;
		}
	}
}