#include "SkipList.h"
#include <iostream>

using namespace std;

struct Complex
{
	int rp;
	int ip;
	friend std::ostream& operator<<(std::ostream& o,const Complex& rhs)
	{
		o << rhs.rp << ":" << rhs.ip ;
		return o;
	}
};

struct ComplexCompare
{
	int operator()(Complex &a, Complex &b)
	{
		return a.rp < b.rp;
	}
};

template<typename T>
void disp(T first, T last)
{
	while(first != --last)
	{
		std::cout << (*last).rp << ":" << (*last).ip << "\t";
		// --last;
	}
	std::cout << (*last).rp << ":" << (*last).ip << "\t";
	std::cout << "\n";
}

int main()
{
	SkipList<Complex, ComplexCompare> sl;
	sl.insert({1,2});
	sl.insert({2,4});
	sl.insert({1,1});
	sl.insert({10,3});
	sl.insert({11,4});
	sl.insert({5,6});
	sl.insert({12,7});
	sl.insert_unique({5,7});
	sl.insert({5,8});
	sl.display();
	std::cout << "\n--------\n";
	// sl.remove1({5,6});
	sl.remove({5,6});
	sl.remove({5,6});
	sl.remove({12,6});
	sl.remove({10,6});

	SkipList<Complex, ComplexCompare>::iterator it = sl.find({5,6});
	cout << "found: " << (*it).rp << ":" << (*it).ip << "\n";
	// disp(sl.begin(), sl.end());
	sl.display();
	std::cout << "\n\n";
	sl.display_reverse();
}