#include<iostream>
#include<gtest/gtest.h>

#define _cpp

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
