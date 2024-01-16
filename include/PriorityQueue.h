//
// Created by HORIA on 04.01.2024.
//

#ifndef DATA_STRUCTURES_PRIORITYQUEUE_H
#define DATA_STRUCTURES_PRIORITYQUEUE_H

#include "Heap.h"
#include <vector>
#include <functional>

template <typename T, typename Cmp = std::greater<T>>
class PriorityQueue : public Heap<T> {
public:
    PriorityQueue(const std::vector<T>& tree, Cmp f = Cmp()) : Heap<T>{tree, f} {}
    PriorityQueue()=default;
    T& top() {
        return Heap<T>::m_heap[0];
    }
private:
};

#endif //DATA_STRUCTURES_PRIORITYQUEUE_H
