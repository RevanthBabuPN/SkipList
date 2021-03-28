#include<iostream>
using namespace std;
#include<random>

template<typename T>
class SkipList;

template<typename T>
class SLNode
{
	public:
	SLNode(T value, int level);
	~SLNode();
	friend bool operator<(SLNode<T>& lhs, SLNode<T>& rhs)
	{
		return lhs.value_ < rhs.value_;
	}
	private:
	T value_;
	int level_;
	SLNode<T>** next_;

	friend class SkipList<T>;
};

template<typename T>
SLNode<T>::SLNode(T value, int level)
:value_(value), level_(level), next_(new SLNode<T>*[level + 1])
{
	for(int i(0); i < level + 1; ++i)
	{
		next_[i] = nullptr;
	}
}

template<typename T>
SLNode<T>::~SLNode()
{
	delete [] next_;
}


template<typename T>
class SkipList
{
	public:
	SkipList();
	~SkipList();
	void insert(T value);
	bool find(T value);
	bool remove(T value);

	private:
	static int MAX_LEVEL;
	SLNode<T> *head_;
	int size_;
	int currentMaxLevel_;
	int flipAndIncrementLevel();
};
template<typename T>
int SkipList<T>::MAX_LEVEL = 10;


template<typename T>
SkipList<T>::SkipList()
:head_(new SLNode<T>(-1,SkipList<T>::MAX_LEVEL)), size_(0), currentMaxLevel_(1)
{

}

template<typename T>
SkipList<T>::~SkipList()
{
	delete head_;
}

template<typename T>
void SkipList<T>::insert(T value)
{
	int level = flipAndIncrementLevel();
	SLNode<T> *newNode = new SLNode<T>(value, level);

	SLNode<T> *cur = head_;

	for(int i = currentMaxLevel_-1; i>=0; --i)
	{
		while(cur->next_[i] != nullptr)
		{
			if(cur->next_[i]->value_ > value)
			{
				break;
			}
			cur = cur->next_[i];
		}

		if(i <= level)
		{
			newNode->next_[i] = cur->next_[i];
			cur->next_[i] = newNode;
		}
	}
	++size_;
}

template<typename T>
//SLNode* SkipList<T>::find(T value)
bool SkipList<T>::find(T value)
{
	SLNode<T> *cur = head_;
	for(int i = currentMaxLevel_-1; i >= 0; --i)
	{
		while(cur->next_[i] != nullptr)
		{
			if(cur->next_[i]->value_ > value)
			{
				break;
			}
			if(!(cur->next_[i]->value_ < value) && !(value < cur->next_[i]->value_))//if(cur->next_[i]->value_ == value)// 
			{
				return true;//return cur->next_;
			}
			cur = cur->next_[i];
		}
	}
	return false;//return nullptr
}

template<typename T>
bool SkipList<T>::remove(T value)
{
	SLNode<T> *cur = head_;
	bool res = false;
	for(int i = currentMaxLevel_-1; i >= 0; --i)
	{
		while(cur->next_[i] != nullptr)
		{
			if(cur->next_[i]->value_ > value)
			{
				break;
			}
			if(cur->next_[i]->value_ == value)
			{
				cur->next_[i] = cur->next_[i]->next_[i];
				res = true;
				// --size_;
				break;
			}
			cur = cur->next_[i];
		}
	}
	--size_;
	return res;
}

bool randomBool()
{
	return 0 + (rand() % 2) == 1;
}

template<typename T>
int SkipList<T>::flipAndIncrementLevel()
{
	bool head = true;
	int level = 0;

	for(int i = 0; i < SkipList<T>::MAX_LEVEL; ++i)
	{
		head = head && randomBool();//head && seed.next;
		if(head)
		{
			level++;
			if(level == currentMaxLevel_)
			{
				++currentMaxLevel_;
				break;
			}
		} 
		else
		{
			break;
		}
	}
	return level;
}

int main()
{
	SkipList<int> sl;
	sl.insert(10);
	sl.remove(10);
	sl.insert(20);
	sl.insert(30);
	sl.insert(40);
	sl.insert(50);
	sl.insert(10);
	sl.insert(60);

	cout << boolalpha;
	cout << sl.find(90);
}