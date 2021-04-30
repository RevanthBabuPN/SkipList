#include "SkipList.h"

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

		SkipList<float>::iterator it1 = sl.find(60);
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

		std::cout << sl.size() << "\n\n";
		sl.remove(60);
		std::cout << sl.size() << "\n\n";
	}
	#endif
	std::cout << "\n\n";
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