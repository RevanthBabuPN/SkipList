#include "SkipList.h"
#include <iostream>
using namespace std;

int main()
{
	{
		SkipList<int> intsl;
		cout << "size: " << intsl.size() << "\n";
		intsl.insert(10);
		intsl.insert(1);
		intsl.insert(5);
		intsl.insert_unique(6);
		intsl.insert_unique(0);
		// intsl.remove(1);
		intsl.display();
		cout << "----------------------------------------\n";
		// intsl.display_reverse();
		cout << "size: " << intsl.size() << "\n";
	}
	cout << "\n========================================\n";
	{
		SkipList<float> floatsl;
		cout << "size: " << floatsl.size() << "\n";
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
}