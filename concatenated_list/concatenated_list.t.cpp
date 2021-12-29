
#include <gtest/gtest.h>

#include <algorithm>
#include <ostream>

#include "concatenated_list.h"


namespace concatenated_list {
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
                             ReverseConcatenatedList::TestCase{{"a"}},
                             ReverseConcatenatedList::TestCase{}

                             ),
                         &ReverseConcatenatedList::getTestName);

TEST_P(ReverseConcatenatedList, testReverseList) {
    auto values = ReverseConcatenatedList::GetParam().values;

    auto actualList = reverseList(createList(values));
    auto actualValues = actualList ? traverseList(*actualList)  //
                                   : std::vector<std::string>();

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
    auto values = std::vector<std::string>{"a", "b", "c", "d", "e", "f"};
    auto list = createList(values);

    for (auto n = 0; n < values.size(); n++) {
        auto expectedValue = values.at(values.size() - 1 - n);
        SCOPED_TRACE("with expected value: " + expectedValue);

        auto nLast = findNLastNode(*list, n);
        EXPECT_TRUE(nLast);
        if (nLast) {
            EXPECT_EQ(expectedValue, nLast->value);
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
    auto values = TraverseList::GetParam().values;
    auto list = createList(values);

    auto index = 0;
    traverseList(*list, [&values, &index](const std::string &value) {
        ASSERT_LT(index, values.size());
        EXPECT_EQ(values.at(index), value);
        index++;
    });
    EXPECT_EQ(values.size(), index);
}

TEST_P(TraverseList, testTraverseListInReverseOrder) {
    auto values = TraverseList::GetParam().values;
    auto list = createList(values);

    auto index = 0;
    traverseListInReverseOrder(
        *list, [&values, &index](const std::string &value) {
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
        RemoveDuplicates::TestCase{{"a"}, {"a"}},
        RemoveDuplicates::TestCase{{}, {}}

        ),
    &RemoveDuplicates::getTestName);

TEST_P(RemoveDuplicates, testRemoveDuplicates) {
    auto values = RemoveDuplicates::GetParam().values;
    auto list = createList(values);

    removeDuplicates(list.get());

    auto actualResult = list ? traverseList(*list) : std::vector<std::string>();
    auto expectedResult = RemoveDuplicates::GetParam().expectedResult;
    EXPECT_EQ(expectedResult, actualResult);
}

TEST_P(RemoveDuplicates, testRemoveDuplicatesNoExtraMemory) {
    auto values = RemoveDuplicates::GetParam().values;
    auto list = createList(values);

    list = removeDuplicatesNoExtraMemory(std::move(list));

    auto actualResult = list ? traverseList(*list) : std::vector<std::string>();

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
        SplitListInTwoHalves::TestCase{{"a"}, {"a"}, {}},
        SplitListInTwoHalves::TestCase{{}, {}, {}}

        ),
    &SplitListInTwoHalves::getTestName);

TEST_P(SplitListInTwoHalves, testSplitListInTwoHalves) {
    const auto &testCase = SplitListInTwoHalves::GetParam();

    auto list = createList(testCase.values);
    auto [actualHead, actualTail] = splitListInTwoHalves(std::move(list));

    if (testCase.expectedHead.empty()) {
        EXPECT_FALSE(actualHead);
    } else {
        EXPECT_EQ(testCase.expectedHead, actualHead
                                             ? traverseList(*actualHead)
                                             : std::vector<std::string>{});
    }

    if (testCase.expectedTail.empty()) {
        EXPECT_FALSE(actualTail);
    } else {
        EXPECT_EQ(testCase.expectedTail, actualTail
                                             ? traverseList(*actualTail)
                                             : std::vector<std::string>{});
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
        MergeSort::TestCase{{"a"}, {"a"}}, MergeSort::TestCase{{}, {}}

        ),
    &MergeSort::getTestName);

TEST_P(MergeSort, testMergeSort) {
    const auto &testCase = MergeSort::GetParam();

    auto sortedList = mergeSort(createList(testCase.values));
    auto actualResult = sortedList ? traverseList(*sortedList)  //
                                   : std::vector<std::string>{};
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

}  // namespace concatenated_list
