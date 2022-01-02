
#include <gtest/gtest.h>

#include <algorithm>
#include <ostream>

#include "tree.h"

namespace tree {
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

// --- TestTree ---

struct TestTree_TestCase {
    std::vector<std::string> values{};
};

class TestTree : public ::testing::TestWithParam<TestTree_TestCase> {
   public:
    using TestCase = TestTree_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(TestList, TestTree,
                         testing::Values(

                             TestTree::TestCase{{"a", "b", "c", "d"}},
                             TestTree::TestCase{{"a", "b", "c"}},
                             TestTree::TestCase{{"a", "b"}},
                             TestTree::TestCase{{"a"}}, TestTree::TestCase{{}}

                             ),
                         &TestTree::getTestName);

TEST_P(TestTree, testListFoo) {
    //
}

auto TestTree::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
    -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.values) {
        name.append("_").append(value);
    }

    return name;
}

auto operator<<(std::ostream &out, const TestTree::TestCase &testCase)
    -> std::ostream & {
    out << "{ \"values\": \"" << toString(testCase.values) << "\"}";
    return out;
}

}  // namespace tree
