#include "SkipList.h"
#include <iostream>
#include <algorithm>
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
	friend bool operator==(const Complex& lhs, const Complex& rhs){
		return lhs.rp == rhs.rp && lhs.ip == rhs.ip;
	}
	friend bool operator<(const Complex& lhs, const Complex& rhs){
		return lhs.rp < rhs.rp ;
	}
};

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

int main()
{
	cout << "SkipList of Complex type\n------------------------------------------------------------------------------\n";
	SkipList<Complex> sl;
	sl.insert({1,1});
	sl.insert({2,4});
	sl.insert({3,2});
	sl.insert({10,3});
	sl.insert({11,4});
	sl.insert({5,6});
	sl.insert_unique({5,7});
	sl.insert_unique({6,7});
	sl.insert({5,8});
	sl.remove({2,4});

	// SkipList<Complex> sl1(sl);
	Complex c1 = {10,3};
	cout << "Elements:\t";
	disp(sl.begin(), sl.end());
	cout << "Number of elements:\t" << sl.size() << "\n";

	SkipList<Complex>::iterator it = sl.find(c1);
	if (it != sl.end())
	{
		cout << *it << " \tFound" << "\n";
	}
	else
	{
		cout << c1 <<" \tNot found\n";
	}

	cout << "\nUsing functions of <algorithm>\n---------------------------------\n";
	it = max_element(sl.begin(), sl.end());
	cout << "Max element:\t" << *it << "\n";

	it = min_element(sl.begin(), sl.end());
	cout << "Min element:\t" << *it << "\n";

	int c = count(sl.begin(), sl.end(), c1);
	cout << "Count of {10,3}'s:\t" << c << "\n";

	c = count_if(sl.begin(), sl.end(), [](Complex x){return x.rp >= 5;});
	cout << "Count of elements greater than or equal to 5:\t" << c << "\n";

	cout << "Using for_each to print elements with rp greater than or eq to 5\n";
	for_each(sl.begin(), sl.end(), [](Complex x){if(x.rp >= 5)cout << x << '\t';});
	cout << "\n";

	cout << boolalpha;
	cout << "is_sorted:\t" << is_sorted(sl.begin(), sl.end()) << "\n";
}