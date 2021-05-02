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
		cout << "SkipList of integers\n---------------------------------------------------------------\n";
		SkipList<int> intsl;
		cout << "size: " << intsl.size() << "\n";
		intsl.insert(10);
		intsl.insert(1);
		intsl.insert_unique(1);
		intsl.insert(2);
		intsl.insert(5);
		intsl.insert_unique(6);
		intsl.insert_unique(0);
		intsl.remove(1);
		intsl.insert(1);

		// SkipList<int> intsl1(intsl);

		cout << "Elements:\t";
		disp(intsl.begin(), intsl.end());
		cout << "Number of elements:\t" << intsl.size() << "\n";

		cout << "\nusing functions of <algorithm>\n------------------------------\n";
		int x = 60;
		SkipList<int>::iterator it = find(intsl.begin(), intsl.end(), x);
		if (it != intsl.end())
		{
			cout << *it << ":\tFound"  << "\n";
		}
		else
		{
			cout << x <<":\tNot found\n";
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
	cout << "\n===============================================================\n\n";
	#if 1
	{
		cout << "SkipList of floats\n---------------------------------------------------------------\n";
		float arr[] = {1.5, 2.1, 5.5, 5.4, 2.2, 7.5};
		SkipList<float> floatsl(begin(arr), end(arr));
		// floatsl.insert(1.5);
		// floatsl.insert(2.1);
		// floatsl.insert(5.5);
		// floatsl.insert_unique(5.4);
		// floatsl.insert_unique(2.2);
		// floatsl.insert_unique(2.1);
		// floatsl.remove(2.4);
		// floatsl.insert(7.5);

		cout << "Elements:\t";
		disp(floatsl.begin(), floatsl.end());
		cout << "Number of elements:\t" << floatsl.size() << "\n";

		float x = 7.5;
		SkipList<float>::iterator it = floatsl.find(x);
		if (it != floatsl.end())
		{
			cout << *it << ":\tFound"  << "\n";
		}
		else
		{
			cout << x <<":\tNot found\n";
		}
		cout << "\nusing functions of <algorithm>\n-------------------------------\n";
		
		it = max_element(floatsl.begin(), floatsl.end());
		cout << "Max element:\t" << *it << "\n";

		it = min_element(floatsl.begin(), floatsl.end());
		cout << "Min element:\t" << *it << "\n";

		int c = count(floatsl.begin(), floatsl.end(), 1);
		cout << "Count of 1's:\t" << c << "\n";

		c = count_if(floatsl.begin(), floatsl.end(), [](float x){return x > 5;});
		cout << "Count of elements greater than to 5:\t" << c << "\n";

		cout << boolalpha;
		cout << "is_sorted:\t" << is_sorted(floatsl.begin(), floatsl.end()) << "\n";
		floatsl.clear();
		cout << "\nAfter clearing, size:\t" << floatsl.size() << "\n";
	}
	#endif
}