#include <iostream>
#include <windows.h>
#include <array>

#include "DebugTools.h"
#include "datastructure.h"
using std::cout;
using std::endl;

void test_array();
void test_queue();
void test_binarytree();
void test_redblacktree();

class Player
{
public:
	Player(int x = 0, int y = 0, int hp = 250, int money = 0):_posX(x), _posY(y), _hp(hp), _money(money)
	{
		static int id = 0;
		_id = ++id;
		_name = new char[sizeof(char) * 10];
		strcpy_s(_name, 10, "Colago");
	}
	~Player()
	{
		delete[] _name;
	}
	void Init(int x, int y, int hp, int money)
	{
		_posX = x; _posY = y;
		_hp = hp; _money = money;
	}
	int GetId() const { return _id; }
	friend std::ostream& operator<<(std::ostream& os, Player& p)
	{
		os << "Id: " << p._id << std::endl;
		os << "Pos: [" << p._posX << ", " << p._posY << "]\n";
		os << "Hp: " << p._hp << std::endl;
		os << "Money: " << p._money << std::endl;
		return os;
	}
	Player(const Player& ref):_posX(ref._posX), _posY(ref._posY), _hp(ref._hp), _money(ref._money), _id(ref._id)
	{
		_name = new char[sizeof(char) * 10];
		strcpy_s(_name, 10, "Colago");
	}
	Player& operator=(const Player& ref)
	{
		_name = new char[sizeof(char) * 10];
		strcpy_s(_name, 10, "Colago");
		_id = ref._id;
		_posX = ref._posX;
		_posY = ref._posY;
		_hp = ref._hp;
		_money = ref._money;
		return *this;
	}
	bool operator<(const Player& other)
	{
		return (_id < other._id);
	}
	bool operator>(const Player& other)
	{
		return (_id > other._id);
	}
	bool operator>=(const Player& other)
	{
		return (_id >= other._id);
	}
	bool operator<=(const Player& other)
	{
		return (_id <= other._id);
	}
	bool operator==(const Player& other)
	{
		return (_id == other._id);
	}
	bool operator!=(const Player& other)
	{
		return !(*this == other);
	}
private:
	int _id;
	int _posX;
	int _posY;
	int _hp;
	long long _money;
	char* _name;
};

int main(void)
{
	test_redblacktree();

	return 0;
}


void test_array()
{
	my::array<int, 5> a = { 1,2,3,4,5 };
	for (my::array<int, 5>::iterator i = a.begin(); i != a.end(); i++)
	{
		cout << *i << endl;
	}
	my::array<Player, 5> p;
	for (my::array<Player, 5>::iterator i = p.begin(); i != p.end(); i++)
	{
		i->Init(10, 5, 150 + i->GetId()*100, 10000 + i->GetId() * 1000);
		cout << *i << endl;
	}
	printf_s("---------------iterator test--------------\n");
	my::array<Player, 5>::iterator iter = p.end();
	cout << *(iter - 3) << endl;
}
void test_queue()
{
	my::queue<Player> p;
	p.reserve(5);
	for (int i = 0; i < 30; i++)
	{
		p.push(Player(i,i,i,i));
	}
	for (int i = 0; i < 15; i++)
	{
		p.pop();
	}
	for (int i = 0; i < 30; i++)
	{
		p.push(Player(i, i, i, i));
	}
	for (int i = 0; i < 15; i++)
	{
		p.pop();
	}
	for (my::queue<Player>::iterator iter = p.begin(); iter != p.end(); iter++)
	{
		cout << *iter << endl;
	}
	p.clear();
	printf_s("size: %zd", p.size());
}
void test_binarytree()
{
	my::binarytree<int> bt;
	bt.insert(15);
	bt.insert(10);
	bt.insert(20);
	bt.insert(4);
	bt.insert(13);
	bt.insert(1);
	bt.insert(2);
	bt.insert(11);
	bt.insert(17);
	bt.insert(25);
	bt.insert(12);
	bt.ShowTree();

	my::binarytree<Player>btp;
	btp.insert(Player());
	btp.insert(Player());
	btp.insert(Player());
	btp.insert(Player());
	btp.insert(Player());
	btp.insert(Player());
	btp.insert(Player());
	btp.ShowTree();
	bt.clear();
	btp.clear();
}
void test_redblacktree()
{
	srand(10);
	my::map<int, Player*> playerTree;
	static int arr[10000];
	for (int i = 0; i < 10000; i++)
	{
		arr[i] = rand() % 10000;
	}
	int falseCount = 0;

	for (int i = 0; i < 10000; i++)
	{
		if (playerTree.insert(arr[i], new Player()) == false)
		{
			falseCount++;
		}
	}
	my::map<int, Player*>::iterator iter = playerTree.begin();
	if ((--iter) == playerTree.end())
	{
		printf_s("����\n");
	}
	playerTree.showInfo();
	printf_s("false cnt: %d, size: %zd\n", falseCount, playerTree.size());
}