//
// Created by HORIA on 12.12.2023.
//

#ifndef DATA_STRUCTURES_TREENODE_H
#define DATA_STRUCTURES_TREENODE_H

template<typename T>
struct TreeNode {
    TreeNode()=default;
    explicit TreeNode(const T& info, TreeNode* parent=nullptr,TreeNode* left= nullptr, TreeNode* right= nullptr)
            : m_info{info}, m_parent{parent},m_left {left}, m_right{right} {}
    T m_info {};
    TreeNode* m_parent {};
    TreeNode* m_left {};
    TreeNode* m_right {};
};

#endif //DATA_STRUCTURES_TREENODE_H
