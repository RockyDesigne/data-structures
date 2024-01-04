//
// Created by HORIA on 11.12.2023.
//

#ifndef DATA_STRUCTURES_MY_BT_H
#define DATA_STRUCTURES_MY_BT_H
#include "My_Doubly_Linked_List.h"
#include "TreeNode.h"
#include <cmath>
#include <iostream>

template<typename T>
class Bt {
public:
    //destructor
    ~Bt() {
        destroy_tree(m_root);
    }

    //methods
    void push_back(const T& val) {
        int i {(m_size + 1)/2};
        int ctr {};
        TreeNode<T>* x {};
        if (m_root) {
            My_Doubly_Linked_List<TreeNode<T>*> q {m_root};
            while (!q.empty() && ctr < i) {
                x = q.top();
                q.pop_front();
                ++ctr;
                if (x->m_left) {
                    q.push_back(x->m_left);
                }
                if (x->m_right) {
                    q.push_back(x->m_right);
                }
            }
        }
        auto node {new TreeNode{val}};
        if (!ctr) {
            m_root = node;
        } else {
            if ((m_size+1)%2) {
                x->m_right = node;
            } else {
                x->m_left = node;
            }
        }
        ++m_size;
        //m_height = std::log2(m_size);
    }

    void preorder_print() {
        preorder(m_root);
    }

    void inorder_print() {
        inorder(m_root);
    }

    void postorder_print() {
        postorder(m_root);
    }

    //getters
    [[nodiscard]] int get_height() const {
        return m_height;
    }

private:
    TreeNode<T>* m_root {};
    int m_height {};
    int m_size {};

    void preorder(TreeNode<T>* root) {
        if (!root) {
            return;
        }
        std::cout << root->m_info << " ";
        preorder(root->m_left);
        preorder(root->m_right);
    }

    void inorder(TreeNode<T>* root) {
        if (!root) {
            return;
        }
        preorder(root->m_left);
        std::cout << root->m_info << " ";
        preorder(root->m_right);
    }

    void postorder(TreeNode<T>* root) {
        if (!root) {
            return;
        }
        postorder(root->m_left);
        postorder(root->m_right);
        std::cout << root->m_info << " ";
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

#endif //DATA_STRUCTURES_MY_BT_H
