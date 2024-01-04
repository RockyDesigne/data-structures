//
// Created by HORIA on 04.01.2024.
//

#ifndef DATA_STRUCTURES_HEAP_H
#define DATA_STRUCTURES_HEAP_H

#include <vector>
#include <functional>
#include <stdexcept>

template <typename T, typename Cmp = std::greater<T>>
class Heap {
public:
    Heap(const std::vector<T>& tree, Cmp f = Cmp()) : m_heap{tree}, m_f{f} {
        for (int i=m_heap.size()-1;i>=0;--i){
            heapify_down(i);
        }
    }
    void insert(const T& x) {
        m_heap.push_back(x);
        if (m_heap.size() > 1)
            heapify_down(m_heap.size()-1);
    }

    T pop() {
        if (is_empty()) {
            throw std::runtime_error("UNDERFLOW! HEAP IS EMPTY!\n");
        }
        std::swap(m_heap[0],m_heap.back());
        auto obj {m_heap.back()};
        m_heap.pop_back();
        heapify_down(0);
        return obj;
    }

    [[nodiscard]] bool is_empty() const {return m_heap.empty();}

private:
    std::vector<T> m_heap {};
    Cmp m_f {};

    int left_node(int i) {return 2*i+1;}
    int right_node(int i) {return 2*i + 2;}

    void heapify_down(int i) {
        auto max {i}, l {left_node(i)}, r {right_node(i)};
        if (l < m_heap.size() && m_f(m_heap[l], m_heap[max])) {
            max = l;
        }
        if (r < m_heap.size() && m_f(m_heap[r], m_heap[max])) {
            max = r;
        }
        if (max != i) {
            std::swap(m_heap[i], m_heap[max]);
            heapify_down(max);
        }
    }

};

#endif //DATA_STRUCTURES_HEAP_H
