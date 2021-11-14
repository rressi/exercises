
#include "concatenated_list.h"

#include <gtest/gtest.h>

#include <algorithm>

namespace concatenated_list {

struct ReverseConcatenatedList_TestCase {
    std::vector<std::string> values{};
};


class ReverseConcatenatedList : public ::testing::TestWithParam<ReverseConcatenatedList_TestCase> {
public:
    using TestCase = ReverseConcatenatedList_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<ReverseConcatenatedList_TestCase> &testInfo) -> std::string;
};

INSTANTIATE_TEST_SUITE_P(ReverseConcatenatedList,
                         ReverseConcatenatedList,
                         testing::Values(

                                 ReverseConcatenatedList::TestCase{{"a", "b", "c", "d"}},
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
        const ::testing::TestParamInfo<ReverseConcatenatedList_TestCase> &testInfo) -> std::string {
    auto name = std::string("case");

    for (auto &value: testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

class FindNLastNode : public ::testing::Test {
};

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

} // namespace concatenated_list
