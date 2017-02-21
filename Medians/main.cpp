#include <iostream>
#include <memory>

#include "vec.hpp"

using std::cout;
using std::cin;

int main(int argc, char**argv)
{
	cout << "Trying to find median.\n Input all numbers or enter letter to end:\n";

	vec<int> numbers;
	int n;
	while (cin >> n)
	{
		numbers.push_back(n);
	}

	cout << "\nMedian for this set: ";

	for (auto it : numbers)
	{
		cout << it << ", ";
	}

	return 0;
}
