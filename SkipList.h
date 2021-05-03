#ifndef SKIPLIST_H
#define SKIPLIST_H

#include<random>

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
	using difference_type = std::ptrdiff_t;

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
			delete [] prev_;
		}

		friend bool operator<(SLNode& lhs, SLNode& rhs)
		{
			return lhs.value_ < rhs.value_;
		}

		key_type value_;
		int level_;
		SLNode** next_;
		SLNode** prev_;
	};

	size_t MAX_LEVEL;
	SLNode *head_;
	SLNode *tail_;
	size_t size_;
	size_t currentMaxLevel_;

	static bool randomBool()
	{
		return 0 + (rand() % 2) == 1;
	}

	static size_t flipAndIncrementLevel(int currentMaxLevel_, int MAX_LEVEL)
	{
		bool head = true;
		size_t level = 0;

		for(size_t i = 0; i < MAX_LEVEL; ++i)
		{
			head = head && randomBool();
			if(head)
			{
				level++;
				if(level == currentMaxLevel_)
				{
					// ++currentMaxLevel_;
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
	SkipList(size_t max = 10)
	:MAX_LEVEL(max), head_(new SLNode(max)), tail_(new SLNode(max)), size_(0), currentMaxLevel_(1)
	{
		for(size_t i = 0; i < MAX_LEVEL + 1; ++i)
		{
			head_->next_[i] = tail_;
			tail_->prev_[i] = head_;
		}
	}

	template<class InputIterator>
	SkipList(InputIterator first, InputIterator last)
	{
		this->MAX_LEVEL = 10;
		this->currentMaxLevel_ = 1;
		this->size_ = 0;
		this->head_ = new SLNode(MAX_LEVEL);
		this->tail_ = new SLNode(MAX_LEVEL);
		for(size_t i = 0; i < MAX_LEVEL + 1; ++i)
		{
			head_->next_[i] = tail_;
			tail_->prev_[i] = head_;
		}

		while(first != last)
		{
			this->insert(*first);
			++first;
		}
	}

	SkipList(SkipList<Key, Compare>& rhs)
	{
		this->MAX_LEVEL = rhs.MAX_LEVEL;
		this->currentMaxLevel_ = 1;
		this->size_ = 0;
		this->head_ = new SLNode(MAX_LEVEL);
		this->tail_ = new SLNode(MAX_LEVEL);
		for(size_t i = 0; i < MAX_LEVEL + 1; ++i)
		{
			head_->next_[i] = tail_;
			tail_->prev_[i] = head_;
		}

		SLNode *cur = rhs.head_;
		while(cur->next_[0]->next_[0] != nullptr)
		{
			this->insert(cur->next_[0]->value_);
			cur = cur->next_[0];
		}
	}

	SkipList<Key, Compare>& operator=(const SkipList<Key, Compare>& rhs)
	{
		if(this != &rhs)
		{	
			SLNode *pre = nullptr;
			SLNode *cur = this->head_;
			while (cur != nullptr)
			{
				pre = cur;
				cur = cur->next_[0];
				delete pre;
			}
			
			this->MAX_LEVEL = rhs.MAX_LEVEL;
			this->currentMaxLevel_ = 1;
			this->size_ = 0;
			this->head_ = new SLNode(MAX_LEVEL);
			this->tail_ = new SLNode(MAX_LEVEL);
			for(size_t i = 0; i < MAX_LEVEL + 1; ++i)
			{
				head_->next_[i] = tail_;
				tail_->prev_[i] = head_;
			}

			cur = rhs.head_;
			while(cur->next_[0]->next_[0] != nullptr)
			{
				this->insert(cur->next_[0]->value_);
				cur = cur->next_[0];
			}
		}
		return *this;
	}

	~SkipList()
	{
		SLNode* pre = nullptr;
		SLNode *cur = head_;
		while(cur != nullptr)
		{
			pre = cur;
			cur = cur->next_[0];
			delete pre;
		}
	}

	size_t size() const
	{
		return size_;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	void clear()
	{
		SLNode* pre = head_;
		SLNode *cur = head_->next_[0];
		while(cur->next_[0] != nullptr)
		{
			pre = cur;
			cur = cur->next_[0];
			delete pre;
		}
		for(size_t i = 0; i < MAX_LEVEL + 1; ++i)
		{
			head_->next_[i] = tail_;
			tail_->prev_[i] = head_;
		}
		currentMaxLevel_ = 1;
		size_ = 0;
	}

	void insert(Key value)
	{
		size_t level = flipAndIncrementLevel(currentMaxLevel_, MAX_LEVEL);
		if (level >= currentMaxLevel_)
			currentMaxLevel_ = level + 1;
		
		SLNode *newNode = new SLNode(value, level);
		SLNode *cur = head_;

		for(long i = currentMaxLevel_-1; i>=0; --i)
		{
			while(cur->next_[i]->next_[i] != nullptr && Compare()(cur->next_[i]->value_, value)) //while(cur->next_[i] != nullptr)
			{
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
		size_t level = flipAndIncrementLevel(currentMaxLevel_, MAX_LEVEL);
		size_t oldMaxLevel_ = currentMaxLevel_;
		if (level >= currentMaxLevel_)
			currentMaxLevel_ = level + 1;

		SLNode *newNode = new SLNode(value, level);
		SLNode *cur = head_;
		SLNode *old[level]; 

		for(long i = currentMaxLevel_ - 1; i >= 0; --i)
		{
			while(cur->next_[i]->next_[i] != nullptr && Compare()(cur->next_[i]->value_, value))
			{
				cur = cur->next_[i];
			}

			if(cur->next_[i]->next_[i] != nullptr && (!Compare()(cur->next_[i]->value_, value) && !Compare()(value, cur->next_[i]->value_))) // not unique
			{
				for(int j = level; j > i; --j)
				{
					old[j]->next_[j] = newNode->next_[j]; 
					newNode->next_[j]->prev_[j] = old[j];
				}
				// for (int j = level; j >= 0; --j)
				// {
				// 	newNode->next_[j] = nullptr;
				// 	newNode->prev_[j] = nullptr;
				// }
				currentMaxLevel_ = oldMaxLevel_;
				delete newNode;
				return;
			}
			
			if(i <= level)
			{
				newNode->next_[i] = cur->next_[i];
				cur->next_[i]->prev_[i] = newNode;
				newNode->prev_[i] = cur;
				cur->next_[i] = newNode;
				old[i] = cur;
			}
		}
		++size_;
	}

	bool remove(Key value)	
	{
		SLNode *cur = head_;
		bool res = false;
		cur = cur->next_[currentMaxLevel_ - 1];

		for(long i = currentMaxLevel_ - 1; i >= 0; --i)
		{
			// while(cur->next_[i] != nullptr && cur->next_[i]->next_[i] != nullptr)
			while(cur->next_[i]->next_[i] != nullptr)
			{
				if(!Compare()(cur->value_, value))
				{
					if(!Compare()(cur->value_, value) && !Compare()(value, cur->value_))
					{
						SLNode *temp = cur;
						for(int k = i; k >= 0; --k)
						{
							cur->next_[k]->prev_[k] = cur->prev_[k];
							cur->prev_[k]->next_[k] = cur->next_[k];
						}
						--size_;
						{
							if (head_->next_[currentMaxLevel_ - 1]->next_[0] == nullptr)
								--currentMaxLevel_;
							delete temp;
						}
						return true;
					}
					else
					{
						break;
					}
				}
				cur = cur->next_[i];
			}
			if(!Compare()(cur->value_, value))
			{
				if(!Compare()(cur->value_, value) && !Compare()(value, cur->value_))
				{
					SLNode *temp = cur;
					for(int k = i; k >= 0; --k)
					{
						cur->next_[k]->prev_[k] = cur->prev_[k];
						cur->prev_[k]->next_[k] = cur->next_[k];
					}
					--size_;
					{
						if (head_->next_[currentMaxLevel_ - 1]->next_[0] == nullptr)
							--currentMaxLevel_;
						delete temp;
					}
					return true;
				}
			}
			cur = cur->prev_[i];
		}
		return false;
	}

	#if 0
	void display() const
	{
		for(long i = currentMaxLevel_ - 1; i >= 0; --i)
		{
			SLNode *cur = head_;
			while(cur->next_[i]->next_[i] != nullptr)
			{
				std::cout << cur->next_[i]->value_ << '\t';
				cur = cur->next_[i];
			}
			std::cout << '\n';
		}
	}

	void display_reverse() const
	{
		for(long i = currentMaxLevel_ - 1; i >= 0; --i)
		{
			SLNode *cur = tail_;
			while(cur->prev_[i]->prev_[i] != nullptr)
			{
				std::cout << cur->prev_[i]->value_ << '\t';
				cur = cur->prev_[i];
			}
			std::cout << '\n';
		}
	}
	#endif

	class Iterator
	{
		private:
		SLNode *p_it_;
		
		public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef Key value_type;
        typedef std::ptrdiff_t difference_type;
        typedef Key* pointer;
        typedef Key& reference;

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
	using const_iterator = Iterator;

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
		for(long i = currentMaxLevel_-1; i >= 0; --i)
		{
			while(cur->next_[i]->next_[i] != nullptr)
			{
				if(!Compare()(cur->next_[i]->value_, value) && !Compare()(value, cur->next_[i]->value_))
				{
					return Iterator(cur->next_[i]);
				}

				if(!Compare()(cur->next_[i]->value_, value))
				{
					break;
				}
				cur = cur->next_[i];
			}
		}
		return end();
	}

	inline std::bidirectional_iterator_tag
	iterator_category(const Iterator&) 
	{
		return std::bidirectional_iterator_tag();
	}
};

#endif
