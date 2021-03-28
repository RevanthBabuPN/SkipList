#include<iostream>
using namespace std;
#include<random>

// template<class Key, class Compare>
// class SkipList;

template<class Key>
class SLNode
{
	public:
	SLNode(Key value, int level);
	~SLNode();
	friend bool operator<(SLNode<Key>& lhs, SLNode<Key>& rhs)
	{
		return lhs.value_ < rhs.value_;
	}
	//private:
	Key value_;
	int level_;
	SLNode<Key>** next_;

	//friend class SkipList<Key>;
};


template<typename Key>
SLNode<Key>::SLNode(Key value, int level)
:value_(value), level_(level), next_(new SLNode<Key>*[level + 1])
{
	for(int i(0); i < level + 1; ++i)
	{
		next_[i] = nullptr;
	}
}

template<typename Key>
SLNode<Key>::~SLNode()
{
	delete [] next_;
}


template<class Key, class Compare = less<Key> >
class SkipList
{
	public:
	SkipList();
	~SkipList();
	void insert(Key value);
	void insert_unique(Key value);
	bool find(Key value);
	bool remove(Key value);

	private:
	static int MAX_LEVEL;
	SLNode<Key> *head_;
	int size_;
	int currentMaxLevel_;
	int flipAndIncrementLevel();
};
template<class Key, class Compare>
int SkipList<Key, Compare>::MAX_LEVEL = 10;


template<class Key, class Compare>
SkipList<Key, Compare>::SkipList()
:head_(new SLNode<Key>(-1,SkipList<Key, Compare>::MAX_LEVEL)), size_(0), currentMaxLevel_(1)
{

}

template<class Key, class Compare>
SkipList<Key, Compare>::~SkipList()
{
	delete head_;
}

template<class Key, class Compare>
void SkipList<Key, Compare>::insert(Key value)
{
	int level = flipAndIncrementLevel();
	SLNode<Key> *newNode = new SLNode<Key>(value, level);

	SLNode<Key> *cur = head_;

	for(int i = currentMaxLevel_-1; i>=0; --i)
	{
		while(cur->next_[i] != nullptr && Compare()(cur->next_[i]->value_, value)) //while(cur->next_[i] != nullptr)
		{
			// if(!Compare()(cur->next_[i]->value_, value)) //if(cur->next_[i]->value_ > value)
			// {
			// 	break;
			// }
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

template<class Key, class Compare>
void SkipList<Key, Compare>::insert_unique(Key value)
{
	int level = flipAndIncrementLevel();
	SLNode<Key> *newNode = new SLNode<Key>(value, level);

	SLNode<Key> *cur = head_;

	for(int i = currentMaxLevel_-1; i>=0; --i)
	{
		// while(cur->next_[i] != nullptr)
		// {
		// 	if(!Compare()(cur->next_[i]->value_, value))//if(cur->next_[i]->value_ > value)
		// 	{
		// 		if(!Compare()(value, cur->next_[i]->value_))
		// 		{
		// 			return;
		// 		}
		// 		break;
		// 	}
		// 	cur = cur->next_[i];
		// }
		while(cur->next_[i] != nullptr && Compare()(cur->next_[i]->value_, value))
		{
			cur = cur->next_[i];
		}

		if(cur->next_[i] != nullptr && !Compare()(value, cur->next_[i]->value_)) // not unique
		{
			return;
		}
		
		if(i <= level)
		{
			newNode->next_[i] = cur->next_[i];
			cur->next_[i] = newNode;
		}
	}
	++size_;
}

template<class Key, class Compare>
//SLNode* SkipList<T>::find(T value)
bool SkipList<Key, Compare>::find(Key value)
{
	SLNode<Key> *cur = head_;
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

template<class Key, class Compare>
bool SkipList<Key, Compare>::remove(Key value)
{
	SLNode<Key> *cur = head_;
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

template<class Key, class Compare>
int SkipList<Key, Compare>::flipAndIncrementLevel()
{
	bool head = true;
	int level = 0;

	for(int i = 0; i < SkipList<Key, Compare>::MAX_LEVEL; ++i)
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

template<typename T>
struct MyGreater
{
	bool operator()(T& x, T&y)
	{
		return x > y;
	}
};
int main()
{
	SkipList<int, MyGreater<int> > sl;
	sl.insert(10);
	sl.insert_unique(10);
	sl.insert_unique(10);
	sl.insert(20);
	sl.insert(30);
	sl.insert(40);
	sl.insert(50);
	sl.insert_unique(10);
	sl.insert(60);

	cout << boolalpha;
	cout << sl.find(90);
}