#include <iostream>
#include <memory>

#include "median.hpp"

using std::cout;
using std::cin;

int main(int argc, char**argv)
{
	cout << "Trying to find median.\n Input all numbers or enter not a number or EOF to end:\n";

	heap_median<int> m;
	int n;
	while (cin >> n)
	{
		m.push(n);
		cout << "\nCurrent median value: " << m.median() << std::endl;
	}

	return 0;
}
