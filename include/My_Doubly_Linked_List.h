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
        explicit Node(const T& info, Node* llink= nullptr, Node*rlink=nullptr) : m_info {info}, m_llink {llink}, m_rlink {rlink} {}
        T m_info {};
        Node* m_llink {};
        Node* m_rlink {};
    };
    //constructors

    My_Doubly_Linked_List()=default;

    My_Doubly_Linked_List(const std::initializer_list<T>& l) {
        for (auto it {l.begin()}; it!=l.end(); ++it) {
            push_back(*it);
        }
    }

    My_Doubly_Linked_List(const My_Doubly_Linked_List<T>& rhs) {
        for (auto it {rhs.begin()}; it != nullptr; it=it->m_rlink) {
            push_back(it->m_info);
        }
    }

    My_Doubly_Linked_List(My_Doubly_Linked_List<T>&& rhs)  noexcept {
        m_head = rhs.m_head;
        m_tail = rhs.m_tail;
        rhs.m_head = nullptr;
        rhs.m_tail = nullptr;
    }

    //destructor
    ~My_Doubly_Linked_List() {
        while (m_head) {
            Node* tmp {m_head};
            m_head = m_head->m_rlink;
            delete tmp;
        }
    }

    //operations
    My_Doubly_Linked_List<T>& operator=(const My_Doubly_Linked_List<T>& rhs) {
        if(this == &rhs) {
            return *this;
        }
        destroy();
        for (auto it{rhs.begin()}; it != nullptr; it=it->m_rlink) {
            push_back(it->m_info);
        }
        return *this;
    }

    My_Doubly_Linked_List<T>& operator=(My_Doubly_Linked_List<T>&& rhs)  noexcept {
        if (this == &rhs) {
            return *this;
        }
        destroy();
        m_head = rhs.m_head;
        m_tail = rhs.m_tail;
        rhs.m_head = nullptr;
        rhs.m_tail = nullptr;
        return *this;
    }

    //modifier methods
    //insertions
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

    //deletions
    void pop_front() {
        if (empty()) {
            return;
        }
        if (m_head == m_tail) {
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
            return;
        }
        Node* tmp {m_head};
        m_head = m_head->m_rlink;
        m_head->m_llink = nullptr;
        delete tmp;
    }

    void pop_back() {
        if (empty()) {
            return;
        }
        if (m_head == m_tail) {
            pop_front();
            return;
        }
        Node* tmp {m_tail};
        m_tail = m_tail->m_llink;
        m_tail->m_rlink = nullptr;
        delete tmp;
    }

    void erase(Node* pos) {
        if (!pos) {
            return;
        }
        if (empty()) {
            return;
        } else if (pos == m_head) {
            pop_front();
            return;
        } else if (pos == m_tail) {
            pop_back();
            return;
        }
        pos->m_rlink->m_llink = pos->m_llink;
        pos->m_llink->m_rlink = pos->m_rlink;
        delete pos;
    }

    //other
    void sort(bool(*pred)(const T& l, const T& r)) {
        if (empty()) {
            return;
        }
        m_head = mergeSort(m_head, pred);
        if (!m_head) {
            return;
        }
        Node* it {m_head};
        while (it->m_rlink) {
            it = it->m_rlink;
        }
        m_tail = it;
    }

    Node* find(const T& val, bool (*pred)(const T& l, const T& r)) {
        for (auto it {m_head}; it != nullptr; it = it->m_rlink) {
            if (pred(val, it->m_info)) {
                return it;
            }
        }
        return nullptr;
    }

    //methods for capacity
    [[nodiscard]] bool empty() const {
        return (!m_tail);
    }

    //iterators
    using iterator = Node*;
    iterator begin() const {
        return m_head;
    }
    iterator end() const {
        return m_tail;
    }

    iterator begin() {
        return m_head;
    }
    iterator end() {
        return m_tail;
    }

private:
    Node* m_head {};
    Node* m_tail {};

    Node* mergeSort(Node* head, bool(*pred)(const T& l, const T& r)) {
        if (!head || !head->m_rlink) {
            return head;
        }
        Node* slow {head}, *fast{head->m_rlink};
        while (fast && fast->m_rlink) {
            slow = slow->m_rlink;
            fast = fast->m_rlink;
        }
        Node* l {head}, *r{slow->m_rlink};
        slow->m_rlink = nullptr;
        l = mergeSort(l, pred);
        r = mergeSort(r, pred);
        return merge(l, r, pred);
    }

    Node* merge(Node* l, Node* r, bool(*pred)(const T& l, const T& r)) {
        if (!l) {
            return r;
        }
        if (!r) {
            return l;
        }
        Node* merged {};
        if (pred(l->m_info, r->m_info)) {
            merged = l;
            l = l->m_rlink;
            merged->m_rlink = nullptr;
            merged->m_llink = nullptr;
        } else {
            merged = r;
            r = r->m_rlink;
            merged->m_rlink = nullptr;
            merged->m_llink = nullptr;
        }
        Node* mergedIt{merged};
        while (l && r) {
            if (pred(l->m_info, r->m_info)) {
                mergedIt->m_rlink = l;
                l->m_llink = mergedIt;
                l = l->m_rlink;
                mergedIt = mergedIt->m_rlink;
                mergedIt->m_rlink = nullptr;
            } else {
                mergedIt->m_rlink = r;
                r->m_llink = mergedIt;
                r = r->m_rlink;
                mergedIt = mergedIt->m_rlink;
                mergedIt->m_rlink = nullptr;
            }
        }
        if (l) {
            mergedIt->m_rlink = l;
            l->m_llink = mergedIt;
        }
        if (r) {
            mergedIt->m_rlink = r;
            r->m_llink = mergedIt;
        }
        return merged;
    }

    void destroy() {
        while (m_head) {
            Node* tmp {m_head};
            m_head = m_head->m_rlink;
            delete tmp;
        }
        m_head = nullptr;
        m_tail = nullptr;
    }

};

#endif //DATA_STRUCTURES_MY_DOUBLY_LINKED_LIST_H
