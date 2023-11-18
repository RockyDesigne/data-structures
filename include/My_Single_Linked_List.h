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
        for (auto it {l.begin()}; it != l.end(); ++it) {
            push_front(*it);
        }
    };
    My_Single_Linked_List() : m_head {nullptr} {}

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

    //operations
    friend std::ostream& operator<<(std::ostream& out, const My_Single_Linked_List<T>& rhs) {
        for(Node* curr {rhs.m_head}; curr != nullptr; curr=curr->m_next) {
            out << curr->m_info << "->";
        }
        out << "NULL\n";
        return out;
    }

private:
    Node* m_head {};

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
