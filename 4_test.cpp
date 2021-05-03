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
	friend bool operator<(const Date& lhs,const Date& rhs)
	{
		if(lhs.yy < rhs.yy)
			return true;
		else if(lhs.yy == rhs.yy)
		{
			if(lhs.mm < rhs.mm)
				return true;
			else if(lhs.mm == rhs.mm)
			{	
				if(lhs.dd < rhs.dd)
					return true;
			}
		}
		return false;
	}
	friend bool operator==(const Date& lhs,const Date& rhs){
		return (lhs.yy == rhs.yy && lhs.mm == rhs.mm && lhs.dd == rhs.dd);
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
		cout << "SkipList of Dates\n------------------------------------------------------------------------------------------\n";
		Date arr[] = { 
			{11, 9, 2001},
			{26, 1, 2001},
			{11, 1, 1966},
			{30, 1, 1948},
			{26, 12, 2004},
		};
		SkipList<Date, byyear> datesl(begin(arr), end(arr));
		SkipList<Date, byyear> sl(datesl);

		cout << "Elements:\t";
		disp(datesl.begin(), datesl.end());
		cout << "Number of elements:\t" << datesl.size() << "\n";
		
		cout << "\nUsing functions of <algorithm>\n------------------------------\n";
		Date d1 = {18,5,2000};
		SkipList<Date, byyear>::iterator it = find(datesl.begin(), datesl.end(), d1);

		if (it != datesl.end())
		{
			cout << *it << ":\tFound"  << "\n";
		}
		else
		{
			cout << d1 <<":\tNot found\n";
		}
		
		it = max_element(datesl.begin(), datesl.end());
		cout << "Max element:\t" << *it << "\n";

		it = min_element(datesl.begin(), datesl.end());
		cout << "Min element:\t" << *it << "\n";

		int c = count(datesl.begin(), datesl.end(), d1);
		cout << "Count of "<< d1 << "\t" << c << "\n";

		cout << "Using for_each to print dates before 2002 \n";
		for_each(datesl.begin(), datesl.end(), [](Date x){if(x.yy < 2002) cout<<x<<"\t";});
		cout << "\n";

		cout << boolalpha;
		cout << "is_sorted:\t" << is_sorted(datesl.begin(), datesl.end()) << "\n";
		
		// replace(datesl.begin(), datesl.end(), 10, 50);
		// reverse(datesl.begin(), datesl.end());
	}
}