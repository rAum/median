#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char**argv)
{
	::testing::InitGoogleTest(&argc, argv);
	auto result = RUN_ALL_TESTS();
	std::cin.get();
	return result;
}