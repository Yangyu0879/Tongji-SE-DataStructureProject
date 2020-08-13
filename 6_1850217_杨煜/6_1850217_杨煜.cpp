#include <iostream>
#include <string>
using namespace std;

struct TreeNode
{
	string data;//��������
	TreeNode* firstChild, * nextSibling;//���Ｐ�ֵ�
	TreeNode() { firstChild = NULL; nextSibling = NULL; }
};
//���캯��������һ���µĽڵ㣬��Ϊ���Ƚڵ㣬���ݴ�����ȵ�����
class Tree
{
private:
	TreeNode* root, * current;//���ڵ�
	bool Find(string s, TreeNode* p);//����
	void addChild(string str, TreeNode* p);//����ӽڵ�
	void printChild(TreeNode* p);//��ӡ���ӽڵ�
public:
	Tree();//���캯��
	~Tree() {}//��������
	void Insertsubtree();//�������
	void Insertnode();//����ӽڵ�
	void Remove();//�Ƴ�
	void Revise();//�޸�
};

//���Һ������ܵĲ���Ϊ���ֺͿ�ʼ�Ľڵ㣬Ȼ���жϽڵ������Ƿ�Ϊ���֣��������ֱ�ӷ��ء�
//���������ڵ��ƶ����ӽڵ�ݹ������������Ȼ�������ƶ����ֵܽڵ㡣
bool Tree::Find(string s, TreeNode* p)//����
{
	if (p->data == s)//������ڵ���Ҫ�ҵ�
	{
		current = p;
		return true;
	}
	else
	{
		TreeNode* q = p->firstChild;//�Ƶ��ӽڵ�
		while (!(q == NULL))
		{
			if (Find(s, q))//�ݹ�
			{
				return true;
			}
			else
			{
				q = q->nextSibling;//�Ƶ��ֵܽڵ�
			}
		}
	}
	return false;
}

//�����Ĳ���Ϊ���ֺ���Ҫ��ӵ�˫�׽ڵ㡣
//���˫�׽ڵ�û���ӽڵ�������룬����Ѱ���ӽڵ���ֵܽڵ�ֱ��Ϊ�գ�����ӽڵ㡣
void Tree::addChild(string str, TreeNode* p)//����ӽڵ�
{
	TreeNode* child = new TreeNode;
	child->data = str;
	if (p->firstChild == NULL)//�ӽڵ�Ϊ��
	{
		p->firstChild = child;
	}
	else
	{
		TreeNode* lastChild = p->firstChild;
		while (lastChild->nextSibling != NULL) //Ѱ���ֵܽڵ�Ϊ�յ��ӽڵ�
		{
			lastChild = lastChild->nextSibling;
		}
		lastChild->nextSibling = child;
	}
}

//ͨ���ݹ�Ѱ���ӽڵ���ֵܽڵ㣬���ýڵ���ӽڵ�����ȫ�������
void Tree::printChild(TreeNode* p)//��ӡ�ӽڵ�
{
	TreeNode* child = p->firstChild;
	while (child->nextSibling != NULL) //ѭ������β���
	{
		cout << child->data << '\t';
		child = child->nextSibling;
	}
	cout << child->data;
}

Tree::Tree()//���캯��
{
	root = new TreeNode; 
	cout << "���Ƚ���һ������" << endl;
	cout << "���������ȵ�������";
	cin >> root->data;
	cout << "�˼��׵������ǣ�" << root->data;
}

//����Ҫ������ͥ������������ҵ��򷵻���ȷ�����δ�ҵ������������Ϣ��
//���������Ů����ͨ������addChild�����β��롣
//�����󣬵���printChild������������е����ݡ�
void Tree::Insertsubtree()//��������
{
	cout << "����Ҫ������ͥ���˵�������";
	string name;
	cin >> name;
	if (!(Find(name,root))) //���û���ҵ�Ҫ�������˵�����
	{
		cout << "û���ҵ������" << endl;
	}
	else 
	{
		int num;
		cout << "������" << name << "�Ķ�Ů������";
		cin >> num;
		cout << "����������" << name << "�Ķ�Ů������";
		TreeNode* node = current;
		while (num > 0) //���β���
		{
			string child;
			cin >> child;
			addChild(child, node);
			num--;
		}
		cout << node->data << "�ĵ�һ�������ǣ�";
		printChild(node);
	}
}
//�ҵ�Ҫ����ڵ��˫�׽ڵ�������ýڵ㡣
void Tree::Insertnode()//�����ӽڵ�
{
	cout << "����Ҫ��Ӷ��ӣ���Ů�������˵�������";
	string name;
	cin >> name;
	if (!(Find(name, root))) 
	{
		cout << "û���ҵ������" << endl;
	}
	else 
	{
		TreeNode* node = current;
		cout << "������" << name << "����ӵĶ��ӣ���Ů������������";
		string child;
		cin >> child;
		addChild(child, node);//����ڵ�
		cout << node->data << "�ĵ�һ�������ǣ�";
		printChild(node);
	}
}
//�����ҵ�Ҫɾ���������ĸ��ڵ㣬�����Ƚڵ㣬������εݹ�ɾ���ڵ㡣
void Tree::Remove()//�Ƴ�
{
	cout << "����Ҫ��ɢ��ͥ���˵�Ŀǰ������";
	string name;
	cin >> name;
	if (!(Find(name, root))) //����Ҳ���
	{
		cout << "û���ҵ������" << endl;
	}
	else 
	{
		TreeNode* node = current;
		cout << "Ҫ��ɢ��ͥ���˵�������" << name << endl;
		if (node->firstChild == NULL)
		{
			cout << node->data << "�Ѿ�û�м�ͥ��";
		}
		else 
		{
			cout << node->data << "�ĵ�һ�������ǣ�";
			printChild(node);
			node->firstChild = NULL;
		}
	}
}
//����ͨ������find�����ҵ�����Ҫ�޸ĵĽڵ㣬��������޸Ľڵ��������ݡ�
void Tree::Revise()//�޸�
{
	cout << "����Ҫ�����������˵�Ŀǰ������";
	string name;
	cin >> name;
	if (!(Find(name, root))) //����Ҳ���
	{
		cout << "û���ҵ������" << endl;
	}
	else 
	{
		TreeNode* node = current;
		cout << "��������ĺ��������";
		string new_name;
		cin >> new_name;
		node->data = new_name;
		cout << name << "�Ѹ���Ϊ" << new_name;
	}
}


//���Ƚ�������ı����������������ݣ�ʹ��switch���ֱ������Ӧ�ĺ������á�
int main()
{
	Tree A;
	int loop = 1;
	cout << "**" << "              " << "���׹���ϵͳ" << "                " << "**" << endl;//�Ʊ�
	cout << "==============================================" << endl;
	cout << "**" << "             " << "��ѡ��Ҫִ�еĲ���" << "           " << "**" << endl;
	cout << "**" << "             " << "A --- ���Ƽ���" << "               " << "**" << endl;
	cout << "**" << "             " << "B --- ��Ӽ�ͥ��Ա" << "           " << "**" << endl;
	cout << "**" << "             " << "C --- ��ɢ�ֲ���ͥ" << "           " << "**" << endl;
	cout << "**" << "             " << "D --- ���ļ�ͥ��Ա����" << "       " << "**" << endl;
	cout << "**" << "             " << "E --- �˳�����" << "               " << "**" << endl;
	cout << "==============================================" << endl;
	while (loop) //��ѭ��
	{
		cout << endl << endl << "��ѡ��Ҫִ�еĲ�����";
		char id;
		cin >> id;
		switch (id)//��ͬ����µ��ú���
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
			cout << "��������ȷ�����" << endl;
			break;
		}
	}
}