//
// Created by HORIA on 03.01.2024.
//

#ifndef DATA_STRUCTURES_AVL_H
#define DATA_STRUCTURES_AVL_H

#include <algorithm>

template<typename T>
class AVL {
public:
    struct Node {
        Node(T _inf,Node* _left,Node*_right,int _balance) : info{_inf},left{_left},right{_right},balance{_balance} {}
        Node()=default;
        T info {};
        Node* left {};
        Node* right {};
        int balance {};
    };

    Node* search(const T& val) {
        Node* it{m_head};
        while (it && it->info != val) {
            if (val < it->info) {
                it = it->left;
            } else {
                it = it->right;
            }
        }
        return it;
    }

    bool insert(Node*& p, const T& val) {
        if (!p) {
            p = new Node{val,nullptr,nullptr,0};
            return true;
        }
        if (p->info == val) {
            return false;
        }
        if (p->info > val) {
            if (insert(p->left,val)) {
                --p->balance;
            } else {
                return false;
            }
        } else {
            if (insert(p->right,val)) {
                ++p->balance;
            } else {
                return false;
            }
        }
        if (p->balance==0) {
            return false;
        } else if (p->balance==1 || p->balance==-1) {
            return true;
        } else {
            echilibreaza(p);
            return false;
        }
    }

    Node* minim(Node* x) {
        while (x->left) {
            x = x->left;
        }
        return x;
    }

    bool cauta_si_sterge_rec(Node*& p, const T& val) {
        if (!p) {
            return false;
        }
        if (p->info>val) {
            if (cauta_si_sterge_rec(p->left,val)) {
                p->balance += 1;
            } else {
                return false;
            }
        } else if (p->info<val) {
            if (cauta_si_sterge_rec(p->right,val)) {
                p->balance -= 1;
            } else {
                return false;
            }
        } else {
            if (!p->left || !p->right) {
                if (p->left) {
                    p->info = p->left->info;
                    delete p->left;
                    p->left = nullptr;
                    p->balance += 1;
                    return true;
                } else if (p->right) {
                    p->info = p->right->info;
                    delete p->right;
                    p->right = nullptr;
                    p->balance -= 1;
                    return true;
                } else {
                    delete p;
                    p = nullptr;
                    return true;
                }
            } else {
                auto y {minim(p->right)};
                p->info = y->info;
                if (cauta_si_sterge_rec(p->right,y->info)) {
                    p->balance -= 1;
                } else {
                    return false;
                }
            }
        }
        if (p->balance == 2 || p->balance == -2) {
            echilibreaza(p);
        }
        if (p->balance == 0) {
            return true;
        } else {
            return false;
        }
    }

    Node*& get_head() {
        return m_head;
    }

private:
    Node* m_head {};
    void echilibreaza(Node*& p) {
        if (p->balance==-2) {
            if (p->left->balance==1) {
                rotatie_stanga_dreapta(p);
            } else {
                rotatie_dreapta(p);
            }
        } else if (p->balance==2) {
            if (p->right->balance==-1) {
                rotatie_dreapta_stanga(p);
            } else {
                rotatie_stanga(p);
            }
        }
    }
    void rotatie_dreapta(Node*& x) {
        auto tmp {x->left};
        x->left=tmp->right;
        tmp->right=x;
        x->balance+=(1-std::min(tmp->balance,0));
        tmp->balance+=(1+std::max(x->balance,0));
        x=tmp;
    }
    void rotatie_stanga(Node*& x) {
        auto tmp {x->right};
        x->right=tmp->left;
        tmp->left=x;
        x->balance=x->balance-(1+std::max(tmp->balance,0));
        tmp->balance=tmp->balance-(1-std::min(x->balance,0));
        x=tmp;
    }
    void rotatie_stanga_dreapta(Node*& x) {
        rotatie_stanga(x->left);
        rotatie_dreapta(x);
    }
    void rotatie_dreapta_stanga(Node*& x) {
        rotatie_dreapta(x->right);
        rotatie_stanga(x);
    }
};

#endif //DATA_STRUCTURES_AVL_H
