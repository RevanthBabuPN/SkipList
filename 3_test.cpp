#include "SkipList.h"
#include <iostream>
#include <algorithm>
using namespace std;

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
	{
		cout << "SkipList of integers\n----------------------------\n";
		int arr[] = {10, 1, 1, 5, 6, 0};
		SkipList<int> intsl1(begin(arr), end(arr));
		// cout << "size: " << intsl1.size() << "\n";
		// intsl1.insert(10);
		// intsl1.insert(1);
		// intsl1.insert(1);
		// intsl1.insert(5);
		// intsl1.insert_unique(6);
		// intsl1.insert_unique(0);
		// intsl1.remove(1);

		SkipList<int> intsl(intsl1);

		cout << "Elements:\t";
		disp(intsl.begin(), intsl.end());
		cout << "Number of elements:\t" << intsl.size() << "\n";

		SkipList<int>::iterator it = find(intsl.begin(), intsl.end(), 60);
		if (it != intsl.end())
		{
			cout << "Found:\t" << *it << "\n";
		}
		else
		{
			cout << "not found\n";
		}
		
		it = max_element(intsl.begin(), intsl.end());
		cout << "Max element:\t" << *it << "\n";

		it = min_element(intsl.begin(), intsl.end());
		cout << "Min element:\t" << *it << "\n";

		int c = count(intsl.begin(), intsl.end(), 1);
		cout << "Count of 1's:\t" << c << "\n";

		c = count_if(intsl.begin(), intsl.end(), [](int x){return x >= 5;});
		cout << "Count of elements greater than or equal to 5:\t" << c << "\n";

		cout << "Using for_each to print elements greater than or eq to 5\n";
		for_each(intsl.begin(), intsl.end(), [](int x){if(x >=5 )cout << x << '\t';});
		cout << "\n";

		cout << boolalpha;
		cout << "is_sorted:\t" << is_sorted(intsl.begin(), intsl.end()) << "\n";

		
		// replace(intsl.begin(), intsl.end(), 10, 50);
		// reverse(intsl.begin(), intsl.end());
	}
	cout << "\n========================================\n\n";
	#if 0
	{
		cout << "SkipList of floats\n\n";
		SkipList<float> floatsl;
		floatsl.insert(1.5);
		floatsl.insert(2.1);
		floatsl.insert(5.5);
		floatsl.insert_unique(5.4);
		floatsl.insert_unique(2.2);
		// floatsl.remove(2.1);
		floatsl.display();
		cout << "----------------------------------------\n";
		// floatsl.display_reverse();
		floatsl.clear();
		cout << "size: " << floatsl.size() << "\n";
	}
	#endif
}