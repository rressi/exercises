
#include "reverse_concatenated_list.h"

#include <gtest/gtest.h>

#include <algorithm>

namespace reverse_concatenated_list {

struct TestCase {
    std::vector<std::string> values{};
};


class ReverseConcatenatedList : public ::testing::TestWithParam<TestCase> {
public:
    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string;
};

INSTANTIATE_TEST_SUITE_P(ReverseConcatenatedList,
                         ReverseConcatenatedList,
                         testing::Values(

                                 TestCase{{"a", "b", "c", "d"}},
                                 TestCase{{"a", "b", "c"}},
                                 TestCase{{"a", "b"}},
                                 TestCase{{"a"}},
                                 TestCase{}

                         ),
                         &ReverseConcatenatedList::getTestName);

TEST_P(ReverseConcatenatedList, testReverseList) {

    auto values = ReverseConcatenatedList::GetParam().values;

    auto actualList = reverseList(createList(values));

    std::reverse(values.begin(), values.end());
    auto expectedList = createList(values);

    EXPECT_EQ(0, compareLists(*expectedList, *actualList));
}

auto ReverseConcatenatedList::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    auto name = std::string("case");

    for (auto &value: testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}


} // namespace hex_bin_match
