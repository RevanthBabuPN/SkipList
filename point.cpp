#include <iostream>
#include "SkipList.h"
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

struct Point
{
	int x;
	int y;

	friend std::ostream& operator<<(std::ostream& o,const Point& p)
	{
		o << "(" << p.x << "," << p.y << ")";
		return o;
	}

	#if 1
	friend bool operator<(const Point& p1, const Point& p2)
	{
		return (abs(p1.x) + abs(p1.y)) < (abs(p2.x) + abs(p2.y));
	}

	friend bool operator==(const Point& p1, const Point& p2)
	{
		return p1.x == p2.x && p1.y == p2.y;
	}
	#endif
};

// Manhattan distance from origin
struct CompareByManhattan
{
	Point p = {0, 0};
	bool operator()(Point &p1, Point &p2)
	{
		return (abs(p1.x - p.x) + abs(p1.y - p.y)) < (abs(p2.x - p.x) + abs(p2.y - p.y));
	}
};

int main()
{
	cout << "SkipList of Points\n---------------------------------------------------------------\n";
	Point arr[] = { 
		{-1, 1},
		{2, 1},
		{-1, 3},
		{-2, -2},
		{-2, 3},
		{-4, -2},
		{2, 1}
	};

	SkipList<Point, CompareByManhattan> pointsl(begin(arr), end(arr));

	cout << "Elements:\t";
	disp(pointsl.begin(), pointsl.end());
	cout << "Number of elements:\t" << pointsl.size() << "\n";
	
	Point p1 = {2,1};
	SkipList<Point, CompareByManhattan>::iterator it = pointsl.find(p1);

	if (it != pointsl.end())
	{
		cout << *it << ":\tFound"  << "\n";
	}
	else
	{
		cout << p1 <<":\tNot found\n";
	}

	#if 1
	cout << "\nUsing functions of <algorithm>\n------------------------------\n";
	it = max_element(pointsl.begin(), pointsl.end());
	cout << "Max element:\t" << *it << "\n";

	it = min_element(pointsl.begin(), pointsl.end());
	cout << "Min element:\t" << *it << "\n";

	int c = count(pointsl.begin(), pointsl.end(), p1);
	cout << "Count of "<< p1 << ":\t" << c << "\n";

	cout << "\nUsing for_each to print manhattan distance from origin\n";
	for_each(pointsl.begin(), pointsl.end(), [](Point p){cout << abs(p.x) + abs(p.y) << "\t";});
	cout << "\n\n";
	
	cout << "\nUsing for_each to print Points with manhattan distance > 3\n";
	for_each(pointsl.begin(), pointsl.end(), [](Point p){if((abs(p.x) + abs(p.y)) > 3) cout << p << "\t";});
	cout << "\n\n";

	cout << boolalpha;
	cout << "is_sorted:\t" << is_sorted(pointsl.begin(), pointsl.end()) << "\n";
	
	// replace(pointsl.begin(), pointsl.end(), 10, 50);
	// reverse(pointsl.begin(), pointsl.end());
	#endif
}