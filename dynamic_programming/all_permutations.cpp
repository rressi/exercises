#include "all_permutations.h"

#include <algorithm>
#include <cassert>
#include <map>
#include <vector>

namespace dp {
namespace {

using CharacterSet = std::string;

bool haveAllCharactersUnique(const std::string &input) {
    auto charSet = std::set<char>(input.begin(), input.end());
    return bool(charSet.size() == input.size());
}

template <class N>
auto createFirstPermutation(N numItems) -> std::vector<N> {
    auto permutation = std::vector<N>();
    permutation.reserve(numItems);

    for (auto i = N(); i < numItems; i++) {
        permutation.emplace_back(i);
    }

    return permutation;
}

template <class Container>
using Memo = std::map<Container, AllPermutations<Container>>;

template <class Container>
auto extractAllPermutationsRecursively(const Container &firstPermutation,
                                       Memo<Container> *memo)
    -> const AllPermutations<Container> & {
    auto memoIt = memo->find(firstPermutation);
    if (memoIt != memo->end()) {
        return memoIt->second;
    }

    auto allPermutations = AllPermutations<Container>();
    if (firstPermutation.size() == 1) {
        allPermutations.insert(firstPermutation);
    } else if (firstPermutation.size() > 1) {
        for (auto i = 0; i < firstPermutation.size(); i++) {
            auto selectedItem = firstPermutation[i];
            auto subPermutation = firstPermutation;
            subPermutation.erase(subPermutation.begin() + i);
            for (auto permutation :
                 extractAllPermutationsRecursively(subPermutation, memo)) {
                permutation.insert(permutation.begin(), selectedItem);
                allPermutations.emplace(std::move(permutation));
            }
        }
    }

    auto [it, _] = memo->emplace(firstPermutation, std::move(allPermutations));
    return it->second;
}

template <class Permutation, class IndexPermutation>
auto createPermutationFromIndices(const Permutation &firstPermutation,
                                  const IndexPermutation &indexPermutation)
    -> Permutation {
    auto newPermutation = Permutation();
    newPermutation.reserve(firstPermutation.size());

    for (auto index : indexPermutation) {
        assert(index < firstPermutation.size());
        newPermutation.push_back(firstPermutation[index]);
    }
    return newPermutation;
}

}  // namespace

auto extractAllPermutations(const std::string &input)
    -> AllPermutations<std::string> {
    if (haveAllCharactersUnique(input)) {
        auto memo = Memo<std::string>();
        extractAllPermutationsRecursively(input, &memo);
        return std::move(memo.at(input));
    }

    auto firstPermutation = createFirstPermutation(input.size());

    using Index = std::string::size_type;
    auto memo = Memo<std::vector<Index>>();
    const auto &indexPermutations =
        extractAllPermutationsRecursively(firstPermutation, &memo);

    auto allPermutations = AllPermutations<std::string>();
    for (const auto &indexPermutation : indexPermutations) {
        allPermutations.emplace(
            createPermutationFromIndices(input, indexPermutation));
    }

    return allPermutations;
}

}  // namespace dp
