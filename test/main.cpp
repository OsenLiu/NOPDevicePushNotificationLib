// CMakeProject1.cpp : Defines the entry point for the application.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[])
{
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
