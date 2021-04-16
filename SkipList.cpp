#include<iostream>
// using namespace std;
#include<random>
// #include<set>


template<class Key, class Compare = std::less<Key> >
class SkipList
{
	using key_type = Key;
	using value_type = Key;
	using size_type = std::size_t;
	using key_compare = Compare;
	using value_compare = Compare;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	private:
	struct SLNode
	{
		SLNode(key_type value, int level)	
		:value_(value), level_(level), next_(new SLNode*[level + 1]), prev_(new SLNode*[level + 1])
		{
			for(int i(0); i < level + 1; ++i)
			{
				next_[i] = nullptr;
				prev_[i] = nullptr;
			}
		}
		
		SLNode(int level)	
		:level_(level), next_(new SLNode*[level + 1]), prev_(new SLNode*[level + 1])
		{
			for(int i(0); i < level + 1; ++i)
			{
				next_[i] = nullptr;
				prev_[i] = nullptr;
			}
		}

		~SLNode()
		{
			delete [] next_;
		}

		friend bool operator<(SLNode& lhs, SLNode& rhs)
		{
			return lhs.value_ < rhs.value_;
		}

		key_type value_;
		int level_;
		SLNode** next_;
		SLNode** prev_;
		//friend class SkipList<Key>;
	};

	
	static int MAX_LEVEL;
	SLNode *head_;
	SLNode *tail_;
	int size_;
	int currentMaxLevel_;
	//int flipAndIncrementLevel();

	static bool randomBool()
	{
		return 0 + (rand() % 2) == 1;
	}

	static int flipAndIncrementLevel(int currentMaxLevel_, int MAX_LEVEL)
	{
		bool head = true;
		int level = 0;

		// for(int i = 0; i < SkipList<Key, Compare>::MAX_LEVEL; ++i)
		for(int i = 0; i < MAX_LEVEL; ++i)
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

	public:
	SkipList()
	//:head_(new SLNode(-1,SkipList<Key, Compare>::MAX_LEVEL)), size_(0), currentMaxLevel_(1)
	:head_(new SLNode(MAX_LEVEL)), tail_(new SLNode(MAX_LEVEL)), size_(0), currentMaxLevel_(1)
	{
		for(int i = 0; i < MAX_LEVEL + 1; ++i)
		{
			head_->next_[i] = tail_;
			tail_->prev_[i] = head_;
		}
	}
	~SkipList()
	{
		delete head_;
	}

	void insert(Key value)
	{
		//int level = flipAndIncrementLevel();


		int level = flipAndIncrementLevel(currentMaxLevel_, 10);
		if (level >= currentMaxLevel_)
			currentMaxLevel_ = level + 1;
		

		SLNode *newNode = new SLNode(value, level);
		SLNode *cur = head_;

		for(int i = currentMaxLevel_-1; i>=0; --i)
		{
			while(cur->next_[i]->next_[i] != nullptr && Compare()(cur->next_[i]->value_, value)) //while(cur->next_[i] != nullptr)
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
				cur->next_[i]->prev_[i] = newNode;
				newNode->prev_[i] = cur;
				cur->next_[i] = newNode;
			}
		}
		++size_;
	}

	void insert_unique(Key value)	
	{
		//int level = flipAndIncrementLevel();


		int level = flipAndIncrementLevel(currentMaxLevel_, 10);
		if (level >= currentMaxLevel_)
			currentMaxLevel_ = level + 1;


		SLNode *newNode = new SLNode(value, level);
		SLNode *cur = head_;
		SLNode *old[level]; 

		for(int i = currentMaxLevel_ - 1; i >= 0; --i)
		{
			/*
			while(cur->next_[i] != nullptr)
			{
				if(!Compare()(cur->next_[i]->value_, value))//if(cur->next_[i]->value_ > value)
				{
					if(!Compare()(value, cur->next_[i]->value_))
					{
						return;
					}
					break;
				}
				cur = cur->next_[i];
			}
			*/
			while(cur->next_[i]->next_[i] != nullptr && Compare()(cur->next_[i]->value_, value))
			{
				cur = cur->next_[i];
			}

			if(cur->next_[i]->next_[i] != nullptr && (!Compare()(cur->next_[i]->value_, value) && !Compare()(value, cur->next_[i]->value_))) // not unique
			{
				// std::cout << "equal: " << cur->next_[i]->value_ << ":" << value << "\n";
				for(int j = level; j > i; --j)
				{
					old[j]->next_[j] = newNode->next_[j]; 
					newNode->next_[j]->prev_[j] = old[j];
				}
				for (int j = level; j >= 0; --j)
				{
					newNode->next_[j] = nullptr;
					newNode->prev_[j] = nullptr;
				}
				delete newNode;
				return;
			}
			
			if(i <= level)
			{
				newNode->next_[i] = cur->next_[i];
				cur->next_[i]->prev_[i] = newNode;
				newNode->prev_[i] = cur;
				cur->next_[i] = newNode;
				// std::cout << "level i: "<< i << "\n";
				old[i] = cur;
			}
		}
		++size_;
	}

	bool remove(Key value)	
	{
		SLNode *cur = head_;
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

	void display()
	{
		for(int i = currentMaxLevel_ - 1; i >= 0; --i)
		{
			SLNode *cur = head_;
			// int i = 0;
			while(cur->next_[i]->next_[i] != nullptr)
			{
				std::cout << cur->next_[i]->value_ << '\t';
				cur = cur->next_[i];
			}
			std::cout << '\n';
		}
	}
	class Iterator
	{
		private:
		SLNode *p_it_;
		
		public:
		typedef std::bidirectional_iterator_tag iterator_category;

		Iterator()
		{}

		Iterator(SLNode *p_it)
		:p_it_(p_it)
		{
			
		}

		Iterator(const Iterator& rhs)
		{
			p_it_ = rhs.p_it_;
		}

		Iterator& operator=(const Iterator& rhs)
		{
			p_it_ = rhs.p_it_;
			return *this;
		}

		Iterator& operator++() // pre
		{
			p_it_ = p_it_ -> next_[0];
			return *this;
		}

		Iterator operator++(int) // post
		{
			Iterator temp(*this);
			++*this;
			return temp;
		}

		Iterator& operator--() // pre
		{
			p_it_ = p_it_ -> prev_[0];
			return *this;
		}

		Iterator operator--(int) // post
		{
			Iterator temp(*this);
			--*this;
			return temp;
		}

		const_reference operator*() const
		{
			return p_it_ -> value_;
		}
		
		bool operator==(const Iterator& rhs) const
		{
			return p_it_ == rhs.p_it_; //if the pointers point to same location we can say they are equal
		}
		
		bool operator!=(const Iterator& rhs) const
		{
			return !(*this == rhs);
		}
	};

	using iterator = Iterator;

	Iterator begin()
	{
		return Iterator(head_->next_[0]);
	}

	Iterator end()
	{
		return Iterator(tail_);
	}

	Iterator find(Key value)
	{
		SLNode *cur = head_;
		for(int i = currentMaxLevel_-1; i >= 0; --i)
		{
			while(cur->next_[i] != nullptr)
			{
				//if(!(cur->next_[i]->value_ < value) && !(value < cur->next_[i]->value_))//if(cur->next_[i]->value_ == value)// 
				if(!Compare()(cur->next_[i]->value_, value) && !Compare()(value, cur->next_[i]->value_))
				{
					//return true;//
					return Iterator(cur->next_[i]);
				}
				//if(cur->next_[i]->value_ > value)
				if(!Compare()(cur->next_[i]->value_, value))
				{
					break;
				}
				cur = cur->next_[i];
			}
		}
		return end();//false;
	}

	inline std::bidirectional_iterator_tag
	iterator_category(const Iterator&) 
	{
		return std::bidirectional_iterator_tag();
	}
};
template<class Key, class Compare>
int SkipList<Key, Compare>::MAX_LEVEL = 10;
/*
bool randomBool()
{
	return 0 + (rand() % 2) == 1;
}

//template<class Key, class Compare>
int SkipList<Key, Compare>::flipAndIncrementLevel()
{
	bool head = true;
	int level = 0;

	// for(int i = 0; i < SkipList<Key, Compare>::MAX_LEVEL; ++i)
	for(int i = 0; i < MAX_LEVEL; ++i)
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

*/
template<typename T>
void disp(T first, T last)
{
	while(first != last)
	{
		std::cout << *first << "\t";
		++first;
	}
	std::cout << "\n";
}

template<typename T>
struct MyGreater
{
	bool operator()(T& x, T&y)
	{
		return x > y;
	}
};

struct A
{
	int a;
	int b;
	friend std::ostream& operator<<(std::ostream& o,const A& rhs)
	{
		o << rhs.a << ":" << rhs.b ;
		return o;
	}
};
typedef struct A A;

struct mycomp
{
	bool operator()(A x, A y)
	{
		return x.a < y.a;
	}
};

int main()
{	
	#if 1
	{
		// SkipList<int, MyGreater<int> > sl;
		SkipList<float> sl;
		sl.insert(10.1);
		sl.insert_unique(10.2);
		sl.insert_unique(10.2);
		sl.insert_unique(10);
		sl.insert(20);
		sl.insert(30);
		sl.insert(40);
		sl.insert(50);
		sl.insert_unique(10);
		sl.insert(60);
		sl.display();

		SkipList<float>::iterator it1 = sl.find(10.2);
		if (it1 != sl.end())
			std::cout << "found:\t" << *it1 << "\n";
		else
			std::cout << "not found\n";
		
		SkipList<float>::iterator it2(it1);
		it1++;
		it1 = it2;
		std::cout << "\nit2 ->" << *it2 <<"\n";
		std::cout << "\nit1 ->" << *it1 <<"\n\n";
		// SkipList<float>::Iterator it = sl.begin();
		// std::cout << "\n" << *it << "\n\n";
		disp(std::begin(sl), std::end(sl));
	}
	#endif
	#if 0
	{
		SkipList<A, mycomp> sl;
		sl.insert(A{1,2});
		sl.insert(A{1,5});
		sl.insert_unique({1,4});
		sl.insert(A{3,10});
		sl.insert(A{2,5});	
		// sl.display();
		disp(std::begin(sl), std::end(sl));
		SkipList<A, mycomp>::Iterator it = sl.begin();
		std::cout << "\n" << *it << "\n";
	}
	#endif
}
/*
		30		50
10		30	40	50
10	20	30	40	50	60
*/