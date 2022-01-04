#pragma once

#include <algorithm>
#include <queue>
#include <type_traits>
#include <vector>

namespace queues {

template <class Container>
auto findBiggestItems(Container &&values, std::size_t numBest)
    -> std::vector<typename std::decay<Container>::type::value_type> {
  using Value = typename std::decay<Container>::type::value_type;

  using PriorityQueue =
      std::priority_queue<Value, std::vector<Value>, std::greater<Value>>;
  auto priorityQueue = PriorityQueue();
  for (const Value &x : values) {
    priorityQueue.push(x);
    if (priorityQueue.size() > numBest) {
      priorityQueue.pop();
    }
  }

  using Results = std::vector<Value>;
  auto results = Results();
  results.reserve(priorityQueue.size());
  while (!priorityQueue.empty()) {
    results.emplace_back(std::move(priorityQueue.top()));
    priorityQueue.pop();
  }
  std::reverse(results.begin(), results.end());

  return results;
}

template <class Container>
auto findBiggestItemsWithHeap(Container &&values, std::size_t numBest)
    -> std::vector<typename std::decay<Container>::type::value_type> {
  using Value = typename std::decay<Container>::type::value_type;

  using HeapQueue = std::vector<Value>;
  auto heapQueue = HeapQueue();
  heapQueue.reserve(numBest);

  for (const Value &x : values) {
    heapQueue.emplace_back(x);
    std::push_heap(heapQueue.begin(), heapQueue.end(), std::greater<Value>());
    if (heapQueue.size() > numBest) {
      std::pop_heap(heapQueue.begin(), heapQueue.end(), std::greater<Value>());
      heapQueue.pop_back();
    }
  }

  std::sort_heap(heapQueue.begin(), heapQueue.end(), std::greater<Value>());

  return heapQueue;
}

}  // namespace queues