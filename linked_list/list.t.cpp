
#include <gtest/gtest.h>

#include <algorithm>
#include <ostream>

#include "list.h"

namespace linked_list {
namespace {

auto toString(const std::vector<std::string> &values) -> std::string {
    std::stringstream buf;
    buf << "[";
    auto sep = "";
    for (const auto &value : values) {
        buf << sep << value;
        sep = ", ";
    }
    buf << "]";
    return buf.str();
}

}  // namespace

// --- TestReverse ---

struct TestReverse_TestCase {
    std::vector<std::string> values{};
};

class TestReverse : public ::testing::TestWithParam<TestReverse_TestCase> {
   public:
    using TestCase = TestReverse_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(TestList, TestReverse,
                         testing::Values(

                             TestReverse::TestCase{{"a", "b", "c", "d"}},
                             TestReverse::TestCase{{"a", "b", "c"}},
                             TestReverse::TestCase{{"a", "b"}},
                             TestReverse::TestCase{{"a"}},
                             TestReverse::TestCase{{}}

                             ),
                         &TestReverse::getTestName);

TEST_P(TestReverse, testListFromValues) {
    const auto &originalValues = TestReverse::GetParam().values;

    auto actualList = List(originalValues);
    auto actualValues = actualList.extractValues();

    EXPECT_EQ(originalValues, actualValues);
}

TEST_P(TestReverse, testReverseList) {
    const auto &values = TestReverse::GetParam().values;

    auto actualList = List(values);
    actualList.reverse();
    auto actualValues = actualList.extractValues();

    auto expectedValues = values;
    std::reverse(expectedValues.begin(), expectedValues.end());

    EXPECT_EQ(expectedValues, actualValues);
}

auto TestReverse::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out, const TestReverse::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"values\": \"" << toString(testCase.values) << "\"}";
    return out;
}

// --- TestTailN ---

class TestList_TailN : public ::testing::Test {};

TEST_F(TestList_TailN, findNLastNode_base) {
    const auto &values = std::vector<std::string>{"a", "b", "c", "d", "e", "f"};
    auto list = List(values);

    for (auto n = 0; n < values.size(); n++) {
        auto expectedValue = values.at(values.size() - 1 - n);
        SCOPED_TRACE("with expected value: " + expectedValue);

        auto actualResult = list.tail(n);
        EXPECT_TRUE(actualResult);
        if (actualResult) {
            EXPECT_EQ(expectedValue, actualResult->value());
        }
    }

    EXPECT_FALSE(list.tail(values.size()));
}

// --- TestVisit ---

struct TestVisit_TestCase {
    std::vector<std::string> values{};
};

class TestVisit : public ::testing::TestWithParam<TestVisit_TestCase> {
   public:
    using TestCase = TestVisit_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(TestList, TestVisit,
                         testing::Values(

                             TestVisit::TestCase{{"a", "b", "c", "d"}},
                             TestVisit::TestCase{{"a", "b", "c"}},
                             TestVisit::TestCase{{"a", "b"}},
                             TestVisit::TestCase{{"a"}}, TestVisit::TestCase{{}}

                             ),
                         &TestVisit::getTestName);

TEST_P(TestVisit, testVisitValues) {
    const auto &values = TestVisit::GetParam().values;
    auto list = List(values);

    auto index = 0;
    list.visitValues([&values, &index](const std::string &value) {
        ASSERT_LT(index, values.size());
        EXPECT_EQ(values.at(index), value);
        index++;
    });
    EXPECT_EQ(values.size(), index);
}

TEST_P(TestVisit, testVisitValuesReverse) {
    const auto &values = TestVisit::GetParam().values;
    auto list = List(values);

    auto index = 0;
    list.visitValuesReverse([&values, &index](const std::string &value) {
        ASSERT_LT(index, values.size());
        EXPECT_EQ(values.at(values.size() - 1 - index), value);
        index++;
    });
    EXPECT_EQ(values.size(), index);
}

auto TestVisit::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
    -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out, const TestVisit::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"values\": \"" << toString(testCase.values) << "\"}";
    return out;
}

// --- RemoveDuplicates ---

struct RemoveDuplicates_TestCase {
    std::vector<std::string> values{};
    std::vector<std::string> expectedResult{};
};

class RemoveDuplicates
    : public ::testing::TestWithParam<RemoveDuplicates_TestCase> {
   public:
    using TestCase = RemoveDuplicates_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(
    TestList, RemoveDuplicates,
    testing::Values(

        RemoveDuplicates::TestCase{{"a", "b", "c"}, {"a", "b", "c"}},
        RemoveDuplicates::TestCase{{"c", "b", "a"}, {"c", "b", "a"}},
        RemoveDuplicates::TestCase{{"a", "a", "b"}, {"a", "b"}},
        RemoveDuplicates::TestCase{{"b", "b", "a"}, {"b", "a"}},
        RemoveDuplicates::TestCase{{"a", "b", "b"}, {"a", "b"}},
        RemoveDuplicates::TestCase{{"a", "b", "a"}, {"a", "b"}},
        RemoveDuplicates::TestCase{{"b", "a", "b"}, {"b", "a"}},
        RemoveDuplicates::TestCase{{"a", "b", "a", "a"}, {"a", "b"}},
        RemoveDuplicates::TestCase{{"a"}, {"a"}},
        RemoveDuplicates::TestCase{{}, {}}

        ),
    &RemoveDuplicates::getTestName);

TEST_P(RemoveDuplicates, testRemoveDuplicates) {
    const auto &values = RemoveDuplicates::GetParam().values;

    auto list = List(values);
    list.removeDuplicates();

    auto actualResult = list.extractValues();
    const auto &expectedResult = RemoveDuplicates::GetParam().expectedResult;
    EXPECT_EQ(expectedResult, actualResult);
}

auto RemoveDuplicates::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out, const RemoveDuplicates::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"values\": \"" << toString(testCase.values)
        << "\", \"expectedResult\": \"" << toString(testCase.expectedResult)
        << "\"}";
    return out;
}

// --- TestSplit ---

struct TestSplit_TestCase {
    std::vector<std::string> values{};
    std::vector<std::string> expectedHead{};
    std::vector<std::string> expectedTail{};
};

class TestSplit : public ::testing::TestWithParam<TestSplit_TestCase> {
   public:
    using TestCase = TestSplit_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(
    TestList, TestSplit,
    testing::Values(

        TestSplit::TestCase{{"a", "b", "c", "d"}, {"a", "b"}, {"c", "d"}},
        TestSplit::TestCase{{"a", "b", "c"}, {"a", "b"}, {"c"}},
        TestSplit::TestCase{{"a", "b"}, {"a"}, {"b"}},
        TestSplit::TestCase{{"a"}, {"a"}, {}}, TestSplit::TestCase{{}, {}, {}}

        ),
    &TestSplit::getTestName);

TEST_P(TestSplit, testSplit) {
    const auto &testCase = TestSplit::GetParam();
    auto [actualHead, actualTail] = List(testCase.values).split();

    EXPECT_EQ(testCase.expectedHead.size(), actualHead.size());
    EXPECT_EQ(testCase.expectedTail.size(), actualTail.size());

    EXPECT_EQ(testCase.expectedHead, actualHead.extractValues());
    EXPECT_EQ(testCase.expectedTail, actualTail.extractValues());
}

auto TestSplit::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
    -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out, const TestSplit::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"values\": \"" << toString(testCase.values)
        << "\", \"expectedHead\": \"" << toString(testCase.expectedHead)
        << "\", \"expectedTail\": \"" << toString(testCase.expectedTail)
        << "\"}";
    return out;
}

// --- TestMergeSortedLists ---

struct TestMergeSortedLists_TestCase {
    std::vector<std::string> listA{};
    std::vector<std::string> listB{};
    std::vector<std::string> expectedMergedList{};
};

class TestMergeSortedLists
    : public ::testing::TestWithParam<TestMergeSortedLists_TestCase> {
   public:
    using TestCase = TestMergeSortedLists_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(
    TestList, TestMergeSortedLists,
    testing::Values(

        TestMergeSortedLists::TestCase{
            {"a", "c"}, {"b", "d"}, {"a", "b", "c", "d"}},
        TestMergeSortedLists::TestCase{
            {"a", "c", "d"}, {"b"}, {"a", "b", "c", "d"}},
        TestMergeSortedLists::TestCase{
            {"b", "c", "d"}, {"a"}, {"a", "b", "c", "d"}},
        TestMergeSortedLists::TestCase{
            {"a", "b", "c"}, {"d"}, {"a", "b", "c", "d"}},
        TestMergeSortedLists::TestCase{{"b"}, {"a"}, {"a", "b"}},
        TestMergeSortedLists::TestCase{{"a"}, {"b"}, {"a", "b"}},
        TestMergeSortedLists::TestCase{{"a"}, {}, {"a"}},
        TestMergeSortedLists::TestCase{{}, {"b"}, {"b"}},
        TestMergeSortedLists::TestCase{{}, {}, {}}

        ),
    &TestMergeSortedLists::getTestName);

TEST_P(TestMergeSortedLists, testTestMergeSortedLists) {
    const auto &testCase = TestMergeSortedLists::GetParam();

    auto listA = List(testCase.listA);
    ASSERT_TRUE(listA.isSorted());
    auto listB = List(testCase.listB);
    ASSERT_TRUE(listB.isSorted());

    auto actualMergedList = List::mergeSortedLists(listA, listB);

    EXPECT_TRUE(actualMergedList.isSorted());
    EXPECT_EQ(listA.size() + listB.size(), actualMergedList.size());
    EXPECT_EQ(testCase.expectedMergedList, actualMergedList.extractValues());
}

auto TestMergeSortedLists::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.listA) {
        name.append("_").append(value);
    }
    name.append("_with");
    for (auto &value : testInfo.param.listB) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out,
                const TestMergeSortedLists::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"listA\": \"" << toString(testCase.listA);
    out << "\", \"listB\": \"" << toString(testCase.listB);
    out << "\", \"expectedMergedList\": \""
        << toString(testCase.expectedMergedList) << "\"}";
    return out;
}

// --- TestSort ---

struct TestSort_TestCase {
    std::vector<std::string> values{};
    std::vector<std::string> expectedResult{};
};

class TestSort : public ::testing::TestWithParam<TestSort_TestCase> {
   public:
    using TestCase = TestSort_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(
    TestList, TestSort,
    testing::Values(

        // TestSort::TestCase{{"a", "b", "c", "d"}, {"a", "b", "c", "d"}},
        // TestSort::TestCase{{"b", "a", "d", "c"}, {"a", "b", "c", "d"}},
        // TestSort::TestCase{{"d", "c", "b", "a"}, {"a", "b", "c", "d"}},
        // TestSort::TestCase{{"a", "b", "c"}, {"a", "b", "c"}},
        // TestSort::TestCase{{"a", "c", "b"}, {"a", "b", "c"}},
        TestSort::TestCase{{"c", "b", "a"}, {"a", "b", "c"}},
        TestSort::TestCase{{"a", "b"}, {"a", "b"}},
        TestSort::TestCase{{"b", "a"}, {"a", "b"}},
        TestSort::TestCase{{"a"}, {"a"}}, TestSort::TestCase{{}, {}}

        ),
    &TestSort::getTestName);

TEST_P(TestSort, testSort) {
    const auto &testCase = TestSort::GetParam();

    auto actualList = List(testCase.values);
    actualList.sort();

    EXPECT_EQ(testCase.expectedResult, actualList.extractValues());
}

auto TestSort::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
    -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out, const TestSort::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"values\": \"" << toString(testCase.values)
        << "\", \"expectedResult\": \"" << toString(testCase.expectedResult)
        << "\"}";
    return out;
}

}  // namespace linked_list
