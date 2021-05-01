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

struct Date
{
	int dd;
	int mm;
	int yy;
	friend std::ostream& operator<<(std::ostream& o,const Date& rhs)
	{
		o << rhs.dd << "-" << rhs.mm << "-" << rhs.yy;
		return o;
	}
};

struct bymonth
{
	int operator()(Date &a, Date &b)
	{
		return a.mm < b.mm;
	}
};

struct byyear
{
	int operator()(Date &a, Date &b)
	{
		return a.yy < b.yy;
	}
};

int main()
{
	{
		cout << "SkipList of Dates\n----------------------------\n";
		Date arr[] = { 
			{11, 9, 2001},
			{26, 1, 2001},
			{11, 1, 1966},
			{30, 1, 1948},
			{26, 12, 2004},
		};
		SkipList<Date, byyear> datesl(begin(arr), end(arr));
		SkipList<Date, byyear> sl(datesl);
		// cout << "size: " << datesl1.size() << "\n";
		// datesl1.insert(10);
		// datesl1.insert(1);
		// datesl1.insert(1);
		// datesl1.insert(5);
		// datesl1.insert_unique(6);
		// datesl1.insert_unique(0);
		// datesl1.remove(1);


		cout << "Elements:\t";
		disp(datesl.begin(), datesl.end());
		cout << "Number of elements:\t" << datesl.size() << "\n";
		
		#if 0
		SkipList<Date, byyear>::iterator it = find(datesl.begin(), datesl.end(), 60);
		if (it != datesl.end())
		{
			cout << "Found:\t" << *it << "\n";
		}
		else
		{
			cout << "not found\n";
		}
		
		it = max_element(datesl.begin(), datesl.end());
		cout << "Max element:\t" << *it << "\n";

		it = min_element(datesl.begin(), datesl.end());
		cout << "Min element:\t" << *it << "\n";

		int c = count(datesl.begin(), datesl.end(), 1);
		cout << "Count of 1's:\t" << c << "\n";

		// c = count_if(datesl.begin(), datesl.end(), [](Date x){return x >= 5;});
		// cout << "Count of elements greater than or equal to 5:\t" << c << "\n";

		// cout << "Using for_each to prdate elements greater than or eq to 5\n";
		// for_each(datesl.begin(), datesl.end(), [](Date x){if(x >=5 )cout << x << '\t';});
		// cout << "\n";

		cout << boolalpha;
		cout << "is_sorted:\t" << is_sorted(datesl.begin(), datesl.end()) << "\n";
		#endif
		
		// replace(datesl.begin(), datesl.end(), 10, 50);
		// reverse(datesl.begin(), datesl.end());
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