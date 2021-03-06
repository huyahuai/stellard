//  Copyright (c) 2013, Facebook, Inc.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.
//

#pragma once
#include <queue>

#include "../include/rocksdb/comparator.h"
#include "iterator_wrapper.h"

namespace rocksdb {

// Return the max of two keys.
class MaxIteratorComparator {
 public:
  MaxIteratorComparator(const Comparator* comparator) :
    comparator_(comparator) {}

  bool operator()(IteratorWrapper* a, IteratorWrapper* b) {
    return comparator_->Compare(a->key(), b->key()) <= 0;
  }
 private:
  const Comparator* comparator_;
};

// Return the max of two keys.
class MinIteratorComparator {
 public:
  // if maxHeap is set comparator returns the max value.
  // else returns the min Value.
  // Can use to create a minHeap or a maxHeap.
  MinIteratorComparator(const Comparator* comparator) :
    comparator_(comparator) {}

  bool operator()(IteratorWrapper* a, IteratorWrapper* b) {
    return comparator_->Compare(a->key(), b->key()) > 0;
  }
 private:
  const Comparator* comparator_;
};

typedef std::priority_queue<
          IteratorWrapper*,
          std::vector<IteratorWrapper*>,
          MaxIteratorComparator> MaxIterHeap;

typedef std::priority_queue<
          IteratorWrapper*,
          std::vector<IteratorWrapper*>,
          MinIteratorComparator> MinIterHeap;

// Return's a new MaxHeap of IteratorWrapper's using the provided Comparator.
MaxIterHeap NewMaxIterHeap(const Comparator* comparator) {
  return MaxIterHeap(MaxIteratorComparator(comparator));
}

// Return's a new MinHeap of IteratorWrapper's using the provided Comparator.
MinIterHeap NewMinIterHeap(const Comparator* comparator) {
  return MinIterHeap(MinIteratorComparator(comparator));
}

}  // namespace rocksdb
