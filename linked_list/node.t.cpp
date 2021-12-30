
#include <gtest/gtest.h>

#include <algorithm>
#include <ostream>

#include "node.h"

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

// --- ReverseConcatenatedList ---

struct ReverseConcatenatedList_TestCase {
    std::vector<std::string> values{};
};

class ReverseConcatenatedList
    : public ::testing::TestWithParam<ReverseConcatenatedList_TestCase> {
   public:
    using TestCase = ReverseConcatenatedList_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(ReverseConcatenatedList, ReverseConcatenatedList,
                         testing::Values(

                             ReverseConcatenatedList::TestCase{
                                 {"a", "b", "c", "d"}},
                             ReverseConcatenatedList::TestCase{{"a", "b", "c"}},
                             ReverseConcatenatedList::TestCase{{"a", "b"}},
                             ReverseConcatenatedList::TestCase{{"a"}}

                             ),
                         &ReverseConcatenatedList::getTestName);

TEST_P(ReverseConcatenatedList, testReverseList) {
    const auto &values = ReverseConcatenatedList::GetParam().values;

    auto actualList = reverseList(createList(values).value());
    auto actualValues = traverseList(actualList);

    auto expectedValues = values;
    std::reverse(expectedValues.begin(), expectedValues.end());

    EXPECT_EQ(expectedValues, actualValues);
}

auto ReverseConcatenatedList::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out,
                const ReverseConcatenatedList::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"values\": \"" << toString(testCase.values) << "\"}";
    return out;
}

// --- FindNLastNode ---

class FindNLastNode : public ::testing::Test {};

TEST_F(FindNLastNode, findNLastNode_base) {
    const auto &values = std::vector<std::string>{"a", "b", "c", "d", "e", "f"};
    auto list = createList(values);

    for (auto n = 0; n < values.size(); n++) {
        auto expectedValue = values.at(values.size() - 1 - n);
        SCOPED_TRACE("with expected value: " + expectedValue);

        auto nLast = findNLastNode(*list, n);
        EXPECT_TRUE(nLast);
        if (nLast) {
            EXPECT_EQ(expectedValue, nLast->value());
        }
    }

    EXPECT_FALSE(findNLastNode(*list, values.size()));
}

// --- TraverseList ---

struct TraverseList_TestCase {
    std::vector<std::string> values{};
};

class TraverseList : public ::testing::TestWithParam<TraverseList_TestCase> {
   public:
    using TestCase = TraverseList_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(TraverseList, TraverseList,
                         testing::Values(

                             TraverseList::TestCase{{"a", "b", "c", "d"}},
                             TraverseList::TestCase{{"a", "b", "c"}},
                             TraverseList::TestCase{{"a", "b"}},
                             TraverseList::TestCase{{"a"}}

                             ),
                         &TraverseList::getTestName);

TEST_P(TraverseList, testTraverse) {
    const auto &values = TraverseList::GetParam().values;
    auto list = createList(values).value();

    auto index = 0;
    traverseList(list, [&values, &index](const std::string &value) {
        ASSERT_LT(index, values.size());
        EXPECT_EQ(values.at(index), value);
        index++;
    });
    EXPECT_EQ(values.size(), index);
}

TEST_P(TraverseList, testTraverseListInReverseOrder) {
    const auto &values = TraverseList::GetParam().values;
    auto list = createList(values).value();

    auto index = 0;
    traverseListInReverseOrder(
        list, [&values, &index](const std::string &value) {
            ASSERT_LT(index, values.size());
            EXPECT_EQ(values.at(values.size() - 1 - index), value);
            index++;
        });
    EXPECT_EQ(values.size(), index);
}

auto TraverseList::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out, const TraverseList::TestCase &testCase)
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
    RemoveDuplicates, RemoveDuplicates,
    testing::Values(

        RemoveDuplicates::TestCase{{"a", "b", "c"}, {"a", "b", "c"}},
        RemoveDuplicates::TestCase{{"a", "a", "b"}, {"a", "b"}},
        RemoveDuplicates::TestCase{{"a", "b", "b"}, {"a", "b"}},
        RemoveDuplicates::TestCase{{"a", "b", "a"}, {"a", "b"}},
        RemoveDuplicates::TestCase{{"b", "a", "b"}, {"b", "a"}},
        RemoveDuplicates::TestCase{{"a", "b", "a", "a"}, {"a", "b"}},
        RemoveDuplicates::TestCase{{"a"}, {"a"}}

        ),
    &RemoveDuplicates::getTestName);

TEST_P(RemoveDuplicates, testRemoveDuplicates) {
    const auto &values = RemoveDuplicates::GetParam().values;

    auto list = createList(values).value();
    removeDuplicates(&list);

    auto actualResult = traverseList(list);
    const auto &expectedResult = RemoveDuplicates::GetParam().expectedResult;
    EXPECT_EQ(expectedResult, actualResult);
}

TEST_P(RemoveDuplicates, testRemoveDuplicatesSortedList) {
    auto values = RemoveDuplicates::GetParam().values;
    std::sort(values.begin(), values.end());

    auto list = createList(values).value();
    removeDuplicatesSortedList(&list);

    auto actualResult = traverseList(list);

    auto expectedResult = RemoveDuplicates::GetParam().expectedResult;
    std::sort(expectedResult.begin(), expectedResult.end());

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

// --- SplitListInTwoHalves ---

struct SplitListInTwoHalves_TestCase {
    std::vector<std::string> values{};
    std::vector<std::string> expectedHead{};
    std::vector<std::string> expectedTail{};
};

class SplitListInTwoHalves
    : public ::testing::TestWithParam<SplitListInTwoHalves_TestCase> {
   public:
    using TestCase = SplitListInTwoHalves_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(
    SplitListInTwoHalves, SplitListInTwoHalves,
    testing::Values(

        SplitListInTwoHalves::TestCase{
            {"a", "b", "c", "d"}, {"a", "b"}, {"c", "d"}},
        SplitListInTwoHalves::TestCase{{"a", "b", "c"}, {"a", "b"}, {"c"}},
        SplitListInTwoHalves::TestCase{{"a", "b"}, {"a"}, {"b"}},
        SplitListInTwoHalves::TestCase{{"a"}, {"a"}, {}}

        ),
    &SplitListInTwoHalves::getTestName);

TEST_P(SplitListInTwoHalves, testSplitListInTwoHalves) {
    const auto &testCase = SplitListInTwoHalves::GetParam();

    auto list = createList(testCase.values).value();
    auto [actualHead, actualTail] = splitListInTwoHalves(std::move(list));

    EXPECT_EQ(testCase.expectedHead, traverseList(actualHead));

    if (testCase.expectedTail.empty()) {
        EXPECT_FALSE(actualTail);
    } else {
        ASSERT_TRUE(actualTail);
        EXPECT_EQ(testCase.expectedTail, traverseList(actualTail.value()));
    }
}

auto SplitListInTwoHalves::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out,
                const SplitListInTwoHalves::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"values\": \"" << toString(testCase.values)
        << "\", \"expectedHead\": \"" << toString(testCase.expectedHead)
        << "\", \"expectedTail\": \"" << toString(testCase.expectedTail)
        << "\"}";
    return out;
}

// --- MergeSortedLists ---

struct MergeSortedLists_TestCase {
    std::vector<std::string> listA{};
    std::vector<std::string> listB{};
    std::vector<std::string> expectedMergedList{};
};

class MergeSortedLists
    : public ::testing::TestWithParam<MergeSortedLists_TestCase> {
   public:
    using TestCase = MergeSortedLists_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(
    MergeSortedLists, MergeSortedLists,
    testing::Values(

        MergeSortedLists::TestCase{
            {"a", "c"}, {"b", "d"}, {"a", "b", "c", "d"}},
        MergeSortedLists::TestCase{
            {"a", "c", "d"}, {"b"}, {"a", "b", "c", "d"}},
        MergeSortedLists::TestCase{
            {"b", "c", "d"}, {"a"}, {"a", "b", "c", "d"}},
        MergeSortedLists::TestCase{
            {"a", "b", "c"}, {"d"}, {"a", "b", "c", "d"}},
        MergeSortedLists::TestCase{{"b"}, {"a"}, {"a", "b"}},
        MergeSortedLists::TestCase{{"a"}, {"b"}, {"a", "b"}}

        ),
    &MergeSortedLists::getTestName);

TEST_P(MergeSortedLists, testMergeSortedLists) {
    const auto &testCase = MergeSortedLists::GetParam();

    auto listA = createList(testCase.listA).value();
    auto listB = createList(testCase.listB).value();
    auto actualMergedList = mergeSortedLists(listA, listB);

    EXPECT_EQ(testCase.expectedMergedList, traverseList(actualMergedList));
}

auto MergeSortedLists::getTestName(
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

auto operator<<(std::ostream &out, const MergeSortedLists::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"listA\": \"" << toString(testCase.listA);
    out << "\", \"listB\": \"" << toString(testCase.listB);
    out << "\", \"expectedMergedList\": \""
        << toString(testCase.expectedMergedList) << "\"}";
    return out;
}

// --- MergeSort ---

struct MergeSort_TestCase {
    std::vector<std::string> values{};
    std::vector<std::string> expectedResult{};
};

class MergeSort : public ::testing::TestWithParam<MergeSort_TestCase> {
   public:
    using TestCase = MergeSort_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(
    MergeSort, MergeSort,
    testing::Values(

        MergeSort::TestCase{{"a", "b", "c", "d"}, {"a", "b", "c", "d"}},
        MergeSort::TestCase{{"b", "a", "d", "c"}, {"a", "b", "c", "d"}},
        MergeSort::TestCase{{"d", "c", "b", "a"}, {"a", "b", "c", "d"}},
        MergeSort::TestCase{{"a", "b", "c"}, {"a", "b", "c"}},
        MergeSort::TestCase{{"a", "c", "b"}, {"a", "b", "c"}},
        MergeSort::TestCase{{"c", "b", "a"}, {"a", "b", "c"}},
        MergeSort::TestCase{{"a", "b"}, {"a", "b"}},
        MergeSort::TestCase{{"b", "a"}, {"a", "b"}},
        MergeSort::TestCase{{"a"}, {"a"}}

        ),
    &MergeSort::getTestName);

TEST_P(MergeSort, testMergeSort) {
    const auto &testCase = MergeSort::GetParam();

    auto list = createList(testCase.values).value();
    auto sortedList = mergeSort(list);

    auto actualResult = traverseList(sortedList);
    EXPECT_EQ(testCase.expectedResult, actualResult);
}

auto MergeSort::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
    -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out, const MergeSort::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"values\": \"" << toString(testCase.values)
        << "\", \"expectedResult\": \"" << toString(testCase.expectedResult)
        << "\"}";
    return out;
}

}  // namespace linked_list
