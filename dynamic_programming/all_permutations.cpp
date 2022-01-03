#include "all_permutations.h"

#include <algorithm>
#include <unordered_map>

namespace dp {
namespace {

using CharacterSet = std::string;

auto buildCharacterSet(const std::string &input) -> CharacterSet {
    auto characters = CharacterSet(input);
    std::sort(characters.begin(), characters.end());
    auto it = std::unique(characters.begin(), characters.end());
    characters.resize(std::distance(characters.begin(), it));
    return characters;
}

using Memo = std::unordered_map<CharacterSet, AllPermutations>;

auto extractAllPermutationsRecursion(const CharacterSet &characterSet,
                                     Memo *memo) -> const AllPermutations & {
    auto memoIt = memo->find(characterSet);
    if (memoIt != memo->end()) {
        return memoIt->second;
    }

    auto allPermutations = AllPermutations();
    if (characterSet.size() == 1) {
        allPermutations.insert(characterSet);
    } else if (characterSet.size() > 1) {
        for (auto i = 0; i < characterSet.size(); i++) {
            auto selectedChar = characterSet[i];
            auto otherChars = characterSet.substr(0, i) +
                              characterSet.substr(i + 1, std::string::npos);
            for (const auto &permutation :
                 extractAllPermutationsRecursion(otherChars, memo)) {
                allPermutations.emplace(std::string{selectedChar} +
                                        permutation);
            }
        }
    }

    auto [it, _] = memo->emplace(characterSet, std::move(allPermutations));
    return it->second;
}

}  // namespace

auto extractAllPermutations(const std::string &input) -> AllPermutations {
    auto characterSet = buildCharacterSet(input);
    auto memo = Memo();
    extractAllPermutationsRecursion(characterSet, &memo);
    return std::move(memo.at(characterSet));
}

}  // namespace dp
