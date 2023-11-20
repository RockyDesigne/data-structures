//
// Created by HORIA on 18.11.2023.
//

#ifndef DATA_STRUCTURES_MY_SINGLE_LINKED_LIST_H
#define DATA_STRUCTURES_MY_SINGLE_LINKED_LIST_H

#include <ostream>
#include <initializer_list>

template<typename T>
class My_Single_Linked_List {
public:
    struct Node {
        Node(T info, Node* next) : m_info{info}, m_next{next} {}
        Node(const Node& nod) {
            m_info = nod.m_info;
            m_next = nod.m_next;
        }
        T m_info {};
        Node* m_next {};
    };

    //constructors
    My_Single_Linked_List(std::initializer_list<T> l) {
        auto it {l.begin()};
        push_front(*it);
        ++it;
        Node* tail {m_head};
        for (; it != l.end(); ++it) {
            insert_after(tail, *it);
            tail = tail->m_next;
        }
    };
    My_Single_Linked_List() : m_head {nullptr} {}

    My_Single_Linked_List(const My_Single_Linked_List& lhs) {
        destroy(); // deletes current linked list
        if (!lhs.m_head) {
            m_head = nullptr;
            return;
        }
        push_front(lhs.m_head->m_info);
        Node* it {m_head};
        for (auto curr {lhs.m_head->m_next}; curr!= nullptr; curr=curr->m_next) {
            insert_after(it, curr->m_info);
            it = it->m_next;
        }
    }

    //destructor
    ~My_Single_Linked_List() {
        while (m_head) {
            Node* temp {m_head};
            m_head = m_head->m_next;
            delete temp;
        }
    }

    //methods
    void push_front(T info) {
        Node* node {new Node{info, nullptr}};
        node->m_next = m_head;
        m_head = node;
    }
    void pop_front() {
        if (!m_head) {
            return;
        }
        Node* temp {m_head};
        m_head = m_head->m_next;
        delete temp;
    }
    void insert_after(Node* pos, T info) {
        if (!pos) {
            return;
        }
        Node* node {new Node{info, pos->m_next}};
        pos->m_next = node;
    }
    void erase_after(Node* pos) {
        if (!m_head->m_next) {
            return;
        }
        Node* temp {pos->m_next};
        pos->m_next = temp->m_next;
        delete temp;
    }

    void reverse() {
        if (!m_head) {
            return;
        }
        Node* prev {};
        while (m_head) {
            Node* temp {m_head};
            m_head = m_head->m_next;
            temp->m_next = prev;
            prev = temp;
        }
        m_head = prev;
    }

    /*
     * removes elements that meet a certain criteria
     * Complexity: N applications of the predicate function
     */
    unsigned long long remove_if(bool(*pred)(T info)) {
        if (!m_head) {
            return 0;
        }
        unsigned long long counter {};
        while (pred(m_head->m_info)) {
            pop_front();
            ++counter;
        }
        Node* prev {m_head};
        Node* it {m_head->m_next};
        while (it) {
            if (pred(it->m_info)) {
                erase_after(prev);
                it = prev;
                ++counter;
            } else {
                prev = prev->m_next;
            }
            it = it->m_next;
        }
        return counter;
    }

    /*
     * Returns the nth element of the list
     * Zero indexed
     * Complexity: O(n)
     */
    Node* find(unsigned long long index) {
        unsigned long long i {};
        Node* it {m_head};
        while (it && i != index) {
            it = it->m_next;
            ++i;
        }
        return it;
    }

    /*
     *@param a pointer to a predicate function that has two params of type T and compares them
     * Complexity: O(nlogn) time, O(logn) space
     */
    void sort(bool(*pred)(T l, T r)) {
        m_head = mergeSort(m_head, pred);
    }

    /*
     * merges two linked lists that are in sorted order
     * if not sorted order then undefined behaviour
     * Complexity: (min(n,m))
     * the list that is merged into this object will be emptied
     */
    void merge(My_Single_Linked_List& other) {
        if (!m_head || !other.m_head) {
            return;
        }
        Node* iter {m_head};
        Node* merged {};
        if (iter->m_info < other.m_head->m_info) {
            merged = iter;
            iter = iter->m_next;
            merged->m_next = nullptr;
        } else {
            merged = other.m_head;
            other.m_head = other.m_head->m_next;
            merged->m_next = nullptr;
        }
        Node* mergedIt {merged};
        while (iter && other.m_head) {
            if (iter->m_info < other.m_head->m_info) {
                mergedIt->m_next = iter;
                iter = iter->m_next;
                mergedIt = mergedIt->m_next;
                mergedIt->m_next = nullptr;
            } else {
                mergedIt->m_next = other.m_head;
                other.m_head = other.m_head->m_next;
                mergedIt = mergedIt->m_next;
                mergedIt->m_next = nullptr;
            }
        }
        if (iter) {
            mergedIt->m_next = iter;
        }
        if (other.m_head) {
            mergedIt->m_next = other.m_head;
        }
        m_head = merged;
    }

    //operations
    friend std::ostream& operator<<(std::ostream& out, const My_Single_Linked_List<T>& rhs) {
        for(Node* curr {rhs.m_head}; curr != nullptr; curr=curr->m_next) {
            out << curr->m_info << "->";
        }
        out << "NULL\n";
        return out;
    }

    My_Single_Linked_List& operator=(const My_Single_Linked_List& rhs) {
        if (this == &rhs) {
            return *this;
        }
        destroy();
        if (!rhs.m_head) {
            m_head = nullptr;
            return *this;
        }
        push_front(rhs.m_head->m_info);
        Node* it {m_head};
        for (auto curr {rhs.m_head->m_next}; curr!= nullptr; curr=curr->m_next) {
            insert_after(it, curr->m_info);
            it = it->m_next;
        }
        return *this;
    }

private:
    Node* m_head {};

    void destroy() {
        while (m_head) {
            Node* temp {m_head};
            m_head = m_head->m_next;
            delete temp;
        }
    }

    Node* mergeSort(Node* head, bool(*pred)(T l, T r)) {
        if(!head || !head->m_next)
            return head;
        Node* slow {head}, *fast {head->m_next};
        while (fast && fast->m_next) {
            slow = slow->m_next;
            fast = fast->m_next->m_next;
        }
        Node* l {head}, *r {slow->m_next};
        slow->m_next = nullptr;
        l = mergeSort(l, pred);
        r = mergeSort(r, pred);
        return merge(l, r, pred);
    }

    Node* merge(Node* l, Node* r, bool(*pred)(T l, T r)) {
        if (!l)
            return r;
        if (!r)
            return l;
        Node* rez {};
        if (pred(l->m_info, r->m_info)) {
            rez = l;
            rez->m_next = merge(l->m_next, r, pred);
        } else {
            rez = r;
            rez->m_next = merge(l, r->m_next, pred);
        }
        return rez;
    }
};

#endif //DATA_STRUCTURES_MY_SINGLE_LINKED_LIST_H
