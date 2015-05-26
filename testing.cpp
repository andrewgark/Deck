#include "deque.h"
#include <deque>
//#include <gtest/gtest.h>
#include <cassert>

enum EQueryType {
    PUSH_FRONT,
    PUSH_BACK,
    POP_FRONT,
    POP_BACK,
    COMPARE_METHODS,
    NUMBER_TESTS
};

void TestAllQueries(Deque<int> &myDeque)
{
    for (ui32 i = 0; i < GetParam(); ++i)
    {
        EQueryType currentQuery = static_cast<EQueryType>(getRandomInt(0, NUMBER_TESTS - 2));
        switch (currentQuery)
        {
            case PUSH_FRONT:
                myDeque.push_front(getRandomInt());
                break;
            case PUSH_BACK:
                myDeque.push_back(getRandomInt());
                break;
            case POP_BACK:
                if (!myDeque.empty())
                {
                    myDeque.pop_back();
                }
                break;
            case POP_FRONT:
                if (!myDeque.empty())
                {
                    myDeque.pop_front();
                }
                break;
            default:
                assert(false);
        }
    }
}

void TestManyPushQueries(Deque<int> &myDeque)
{
    for (ui32 i = 0; i < GetParam(); ++i)
    {
        EQueryType currentQuery = static_cast<EQueryType>(getRandomInt(0, 1));
        switch (currentQuery)
        {
            case PUSH_BACK:
                myDeque.push_back(getRandomInt());
                break;
            case PUSH_FRONT:
                myDeque.push_back(getRandomInt());
            default:
                assert(false);
        }
    }
}

void TestManyPopQueries(Deque<int> &myDeque)
{
    for (ui32 i = 0; i < GetParam(); ++i)
    {
        EQueryType currentQuery = static_cast<EQueryType>(getRandomInt(0, 1));
        switch (currentQuery)
        {
            case PUSH_BACK:
                myDeque.push_back(getRandomInt());
                break;
            case PUSH_FRONT:
                myDeque.push_back(getRandomInt());
            default:
                assert(false);
        }
    }
}

class ResultTest: public testing::TestWithParam<size_t> {};
class SmallTimeTest: public testing::TestWithParam<size_t> {};
class ManyPushTimeTest: public testing::TestWithParam<size_t> {};
class ManyPushManyPopTimeTest: public testing::TestWithParam<size_t>{};

TEST_P(ResultTest, ResultTest)
{
    Deque<int> myDeque;
    std::deque<int> standartDeque;
    for (ui32 i = 0; i < GetParam(); ++i)
        {
        int randomInt;
        EQueryType currentQuery = static_cast<EQueryType>(getRandomInt(0,  NUMBER_TESTS - 1));
        switch (currentQuery)
        {
            case PUSH_FRONT:
                randomInt = getRandomInt();
                myDeque.push_front(randomInt);
                standartDeque.push_front(randomInt);
                break;
            case PUSH_BACK:
                randomInt = getRandomInt();
                myDeque.push_back(randomInt);
                standartDeque.push_back(randomInt);
                break;
            case POP_FRONT:
                if (!standartDeque.empty())
                {
                    myDeque.pop_front();
                    standartDeque.pop_front();
                }
                break;
            case POP_BACK:
                if (!standartDeque.empty())
                {
                    myDeque.pop_back();
                    standartDeque.pop_back();
                }
                break;
            case COMPARE_METHODS:
                EXPECT_EQ(myDeque.size(), standartDeque.size());
                EXPECT_EQ(myDeque.empty(), standartDeque.empty());
                if (!myDeque.empty())
                {
                    EXPECT_EQ(myDeque.front(), standartDeque.front());
                    EXPECT_EQ(myDeque.back(), standartDeque.back());
                    int randomInt = getRandomInt(0, standartDeque.size());
                    EXPECT_EQ(myDeque[randomInt], standartDeque[randomInt]);
                }
                break;
            default:
                assert(false);
        }
    }
    EXPECT_TRUE(std::equal(myDeque.begin(), myDeque.end(), standartDeque.begin()));
    EXPECT_TRUE(std::equal(myDeque.rbegin(), myDeque.rend(), standartDeque.rbegin()));
    EXPECT_TRUE(std::equal(myDeque.cbegin(), myDeque.cend(), standartDeque.cbegin()));
    EXPECT_TRUE(std::equal(myDeque.crbegin(), myDeque.crend(), standartDeque.crbegin()));
    SUCCEED();
}

TEST_P(SmallTimeTest, SmallTimeTest)
{
    Deque<int> myDeque;
    TestAllQueries(myDeque, getParam());
    SUCCEED();
}

TEST_P(ManyPushTimeTest, ManyPushTimeTest)
{
    Deque<int> myDeque;
    TestManyPushQueries(myDeque, getParam());
    TestAllQueries(myDeque, getParam());
    SUCCEED();
}


TEST_P(ManyPushManyPopTimeTest, ManyPushManyPopTimeTest)
{
    Deque<int> myDeque;
    TestManyPushQueries(myDeque, getParam());
    TestManyPopQueries(myDeque, getParam());
    TestAllQueries(myDeque, getParam());
    SUCCEED();
}

INSTANTIATE_TEST_CASE_P(TestResul, ResultTest, testing::Values(1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7));
INSTANTIATE_TEST_CASE_P(TestSmallTime, SmallTimeTest, testing::Values(1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7));
INSTANTIATE_TEST_CASE_P(TestManyPushTime, ManyPushTimeTest, testing::Values(1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7));
INSTANTIATE_TEST_CASE_P(TestManyPushManyPopTime, ManyPushManyPopTimeTest, testing::Values(1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7));


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return 0;
}
