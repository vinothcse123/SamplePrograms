#include<iostream>
#include "gtest/gtest.h"


struct MyClass
{
	int myInMember;
	int myOutMember;

	void MyClassMemberFunc();
};


void MyClass::MyClassMemberFunc()
{
	myOutMember=10;
}

TEST(VinothSampleTesting, VinothTests) {

	MyClass m;
	m.myInMember=5;
	m.MyClassMemberFunc();

	EXPECT_EQ(10, m.myOutMember);
	EXPECT_EQ(20, m.myOutMember);
}


int main(int argc, char *argv[])
{	

	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();

	return 0;
}
