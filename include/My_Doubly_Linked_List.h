//
// Created by HORIA on 20.11.2023.
//

#ifndef DATA_STRUCTURES_MY_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURES_MY_DOUBLY_LINKED_LIST_H

#include <initializer_list>

template <typename T>
class My_Doubly_Linked_List {
public:
    struct Node {
        Node(const T& info, Node* llink= nullptr, Node*rlink=nullptr) : m_info {info}, m_llink {llink}, m_rlink {rlink} {}
        T m_info {};
        Node* m_llink {};
        Node* m_rlink {};
    };
    //constructors
    My_Doubly_Linked_List(std::initializer_list<T> l) {
        for (auto it {l.begin()}; it!=l.end(); ++it) {
            push_back(*it);
        }
    }
    //destructor
    ~My_Doubly_Linked_List() {
        while (m_head) {
            Node* tmp {m_head};
            m_head = m_head->m_rlink;
            delete tmp;
        }
    }
    //modifier methods
    void push_front(const T& val) {
        Node* p {new Node {val}};
        if (empty()) {
            m_head = p;
            m_tail = p;
            return;
        }
        if (m_head == m_tail) {
            m_tail->m_llink = m_head;
            m_head->m_llink = p;
            p->m_rlink = m_head;
            m_head = p;
            return;
        }
        m_head->m_llink = p;
        p->m_rlink = m_head;
        m_head = p;
    }
    void push_back(const T& val) {
        if (empty()) {
            push_front(val);
            return;
        }
        Node* p {new Node{val, m_tail}};
        m_tail->m_rlink = p;
        m_tail = p;
    }
    //methods for capacity
    [[nodiscard]] bool empty() const {
        return (!m_tail);
    }

    //iterators
    using iterator = Node*;
    iterator begin() {
        return m_head;
    }
    iterator end() {
        return m_tail;
    }
private:
    Node* m_head {};
    Node* m_tail {};
};

#endif //DATA_STRUCTURES_MY_DOUBLY_LINKED_LIST_H
