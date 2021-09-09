#include "pch.h"
#include "../Translator/addons/BasicTest.cpp"

TEST(TestCaseName, TestName) {
	BasicTest test;
	test.setCount(3);
  EXPECT_EQ(test.getCount(), 3);
}