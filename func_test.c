#include <limits>
#include <list>
#include "func.h"
#include "gtest/gtest.h"

class fooEnvironment : public testing::Environment
{
	public:
		virtual void SetUp()
		{
			std::cout << "foo setup" << std::endl;
		}
		virtual void TearDown()
		{
			std::cout << "foo teardown" << std::endl;
		}
};


template<typename T>
class footype
{
public:
	void bar() { testing::StaticAssertTypeEq<int,T>(); }
};

TEST(DISABLED_TypeAssert,demo)
{
	footype<int> footype1;
	footype1;

	footype<bool> footype2;
	footype2;
}

//////////////////////////////////////////////////////////////////////
template <typename T>
class FooTest : public testing::Test
{
	public:

		typedef std::list<T> List;
		static T shared_;
		T value_;
};

TYPED_TEST_CASE_P(FooTest);
TYPED_TEST_P(FooTest,Does)
{
	TypeParam n = 0;
	this->value_ = n;
	typename FooTest<TypeParam>::List values;
	values.push_back(n);
	EXPECT_EQ(1,values.size());
	EXPECT_EQ(0,this->value_);
}
TYPED_TEST_P(FooTest,Demoo)
{

}
REGISTER_TYPED_TEST_CASE_P(FooTest,Does,Demoo);
typedef testing::Types<char,int,unsigned int> MyTypes;
INSTANTIATE_TYPED_TEST_CASE_P(my,FooTest,MyTypes);

////////////////////////////////////////////////////////////////////////

class IsPrimeParamTest : public testing::TestWithParam<int>
{
};

TEST_P(IsPrimeParamTest,HandleTrueRet)
{
	int n = GetParam();
	EXPECT_TRUE(IsPrime(n));
}

INSTANTIATE_TEST_CASE_P(paramtest,IsPrimeParamTest,testing::Range(1,3));

///////////////////////////////////////////////////////////////////////////////////

void crashtest()
{
	int *pInt = 0;
	*pInt =42;
}


TEST(crashtestDeathTest,demo1)
{
	EXPECT_EXIT(_exit(1),testing::ExitedWithCode(1),"");
}

////////////////////////////////////////////////////////////////////////////








/*
TEST(Func_test,test_negtive)
{
	//EXPECT_EQ(-1,func(-1));
	//EXPECT_EQ(-1,func(-5));
	ASSERT_ANY_THROW(func(-5));
	EXPECT_THROW(func(-1),unsigned char*);
}

TEST(Func_test,test_zero)
{
	EXPECT_EQ(1,func(0));
}

TEST(Func_test,test_positive)
{
	//FAIL() << "sorry" ;
	ADD_FAILURE() << "failure";
	ASSERT_EQ(1,func(2));
	EXPECT_EQ(6,func(3));
}

*/


int main(int argc,char* argv[])
{
	//testing::GTEST_FLAG(output) = "xml:";
	testing::AddGlobalTestEnvironment(new fooEnvironment());
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
