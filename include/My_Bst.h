//
// Created by HORIA on 12.12.2023.
//

#ifndef DATA_STRUCTURES_MY_BST_H
#define DATA_STRUCTURES_MY_BST_H

#include "TreeNode.h"
#include <cmath>
#include <cstring>
#include <vector>
#include <string>
#include <string_view>

template<typename T>
class Bst {
public:
    void insert(const T& val, bool (*f) (const T& a, const T& b)) {
        TreeNode<T>* y {};
        TreeNode<T>* x {m_root};
        while (x) {
            y = x;
            if (f(val, x->m_info)) {
                x = x->m_left;
            } else {
                x = x->m_right;
            }
        }
        auto z {new TreeNode<T> {val}};
        z->m_parent = y;
        if (!y) {
            m_root = z;
        } else {
            if (f(val, y->m_info)) {
                y->m_left = z;
            } else {
                y->m_right = z;
            }
        }
        ++m_size;
        //m_height = log2(m_size);
    }

    ~Bst() {
        destroy_tree(m_root);
    }

    void sort_int(int v[], int rez[], int n, int i) {
        Bst tmp {};
        //get min
        int min {0};
        for (int k{0};k<n;++k){
            if (v[min] < v[k]) {
                min = k;
            }
        }
        std::swap(v[0], v[min]);
        for (int k{0}; k <n;++k) {
            tmp.insert(v[k], [](const T& a, const T& b) {return (a<b);});
        }
        inorder_sort(tmp.m_root, rez, i);
    }

    void sort_words(const std::vector<std::string_view>& words, std::vector<std::string>& rez) {
        auto getBiggestWord {[](const std::vector<std::string_view>& words) {
            int biggest {};
            for (int i = 1; i < words.size(); ++i) {
                if (std::lexicographical_compare(words[biggest].begin(), words[biggest].end(),
                                                 words[i].begin(), words[i].end()))
                {
                    biggest = i;
                }
            }
            return biggest;
        }};
        auto f {[](const std::string& a, const std::string& b) {
            return !std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
        }};
        int biggest {getBiggestWord(words)};
        Bst<std::string> tmp {};
        tmp.insert(std::string {words[biggest]}, f);
        for (int i=0; i < words.size(); ++i) {
            if (i != biggest) {
                tmp.insert(std::string {words[i]}, f);
            }
        }
        inorder_sort(tmp.m_root, rez);
    }

    void sterge(TreeNode<T>* z) {
        if (!z->m_left) {
            transplant(z, z->m_right);
        } else {
            if (!z->m_right) {
                transplant(z, z->m_left);
            } else {
                auto y {minim(z->m_right)};
                if (y->m_parent != z) {
                    transplant(y, y->m_right);
                    y->m_right = z->m_right;
                    y->m_right->m_parent=y;
                }
                transplant(z, y);
                y->m_left=z->m_left;
                y->m_left->m_parent=y;
            }
        }
    }

    TreeNode<T>* search(const T& val, bool (*f)(const T& a, const T* b)) {
        return look(m_root,val ,f);
    }

    TreeNode<T>* find_max() {
        return maxim(m_root);
    }

    TreeNode<T>* minim(TreeNode<T>* x) {
        while (x->m_left) {
            x = x->m_left;
        }
        return x;
    }
    TreeNode<T>* maxim(TreeNode<T>* x) {
        while (x->m_right) {
            x = x->m_right;
        }
        return x;
    }

    [[nodiscard]] TreeNode<T>* get_root() const {
        return m_root;
    }

private:
    TreeNode<T>* m_root {};
    TreeNode<T>* m_height {};
    TreeNode<T>* m_size {};

    void inorder_sort(TreeNode<T>* root, int arr[], int& i) {
        if (!root) {
            return;
        }
        inorder_sort(root->m_left, arr,  i);
        arr[i++] = root->m_info;
        inorder_sort(root->m_right, arr, i);
    }

    void inorder_sort(TreeNode<T>* root, std::vector<std::string>& arr) {
        if (!root) {
            return;
        }
        inorder_sort(root->m_left, arr);
        arr.push_back(root->m_info);
        inorder_sort(root->m_right, arr);
    }

    TreeNode<T>* look(TreeNode<T>* root, const T& val, bool (*f)(const T& a, const T* b)) {
        if (!root) {
            return nullptr;
        }
        if (root->m_info == val) {
            return root;
        }
        if (f(val, root->m_info)) {
            return look(root->m_left, val, f);
        } else {
            return look(root->m_right, val, f);
        }
    }

    void transplant(TreeNode<T>* u, TreeNode<T>* v) {
        if (!u->m_parent) {
            m_root = v;
        } else {
            if (u == (u->m_parent)->m_left) {
                u->m_parent->m_left = v;
            } else {
                u->m_parent->m_right = v;
            }
        }
        if (v) {
            v->m_parent = u->m_parent;
        }
        delete u;
    }

    void destroy_tree(TreeNode<T>* root) {
        if (!root) {
            return;
        }
        destroy_tree(root->m_left);
        destroy_tree(root->m_right);
        delete root;
    }
};

#endif //DATA_STRUCTURES_MY_BST_H
