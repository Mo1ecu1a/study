#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bubble.hpp"

TEST(ArraysEqual, AnyElementsCount) {
	std::vector<int> a = {1, 8, 2, 5, 3, 11};
	bubble::sort(a);
	std::vector<int> arr = {1, 2, 3, 5, 8, 11};

	ASSERT_EQ(arr.size(), a.size())
		<< "Разные размеры";

	for (int i = 0; i < a.size(); i++) {
		ASSERT_EQ(arr[i], a[i]) 
			<< "Массивы разные в индексе";
			<< i;
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
