
#include <gtest/gtest.h>

#include <algorithm>

#include "concatenated_list.h"


namespace concatenated_list {

// --- ReverseConcatenatedList
// --------------------------------------------------------------------

struct ReverseConcatenatedList_TestCase {
    std::vector<std::string> values{};
};

class ReverseConcatenatedList
    : public ::testing::TestWithParam<ReverseConcatenatedList_TestCase> {
   public:
    using TestCase = ReverseConcatenatedList_TestCase;

    static auto getTestName(
        const ::testing::TestParamInfo<ReverseConcatenatedList_TestCase>
            &testInfo) -> std::string;
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

    std::reverse(values.begin(), values.end());
    auto expectedList = createList(values);

    EXPECT_EQ(0, compareLists(*expectedList, *actualList));
}

auto ReverseConcatenatedList::getTestName(
    const ::testing::TestParamInfo<ReverseConcatenatedList_TestCase> &testInfo)
    -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

// --- FindNLastNode
// ------------------------------------------------------------------------------

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

// --- TraverseList
// -------------------------------------------------------------------------------

struct TraverseList_TestCase {
    std::vector<std::string> values{};
};

class TraverseList : public ::testing::TestWithParam<TraverseList_TestCase> {
   public:
    using TestCase = TraverseList_TestCase;

    static auto getTestName(
        const ::testing::TestParamInfo<TraverseList_TestCase> &testInfo)
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
    const ::testing::TestParamInfo<TraverseList_TestCase> &testInfo)
    -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

// --- RemoveDuplicates
// -------------------------------------------------------------------------------

struct RemoveDuplicates_TestCase {
    std::vector<std::string> values{};
    std::vector<std::string> expectedResult{};
};

class RemoveDuplicates
    : public ::testing::TestWithParam<RemoveDuplicates_TestCase> {
   public:
    using TestCase = RemoveDuplicates_TestCase;

    static auto getTestName(
        const ::testing::TestParamInfo<RemoveDuplicates_TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(
    RemoveDuplicates, RemoveDuplicates,
    testing::Values(

        RemoveDuplicates::TestCase{{"a", "b", "c"}, {"a", "b", "c"}},
        RemoveDuplicates::TestCase{{"a", "a", "b"}, {"a", "b"}},
        RemoveDuplicates::TestCase{{"a", "b", "b"}, {"a", "b"}},
        RemoveDuplicates::TestCase{{"a", "b", "a"}, {"a", "b"}},
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

auto RemoveDuplicates::getTestName(
    const ::testing::TestParamInfo<RemoveDuplicates_TestCase> &testInfo)
    -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

}  // namespace concatenated_list
